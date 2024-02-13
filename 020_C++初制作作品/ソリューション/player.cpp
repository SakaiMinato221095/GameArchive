
//-===============================================
//-
//-	プレイヤー処理[player_battle.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "player.h"

#include "renderer.h"
#include "manager.h"

#include "Input.h"
#include "xinput.h"

#include "sound.h"
#include "debugproc.h"

#include "manager_object.h"
#include "time_stop.h"

#include "camera.h"

#include "event_object.h"
#include "objectx_none.h"
#include "garbage_collect.h"
#include "gate.h"

#include "object3d.h"
#include "obj_3d_wall.h"

#include "sys_game_phase.h"
#include "effect.h"

#include "hit.h"

//-======================================
//-	マクロ定義
//-======================================

#define PLAYER_SPEED	(4.0f)	//プレイヤーの速度

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CPlayer::CPlayer()
{
	//// 値をクリア
	ZeroMemory(m_mtxWorld, sizeof(D3DXMATRIX));

	ZeroMemory(m_apObjectModel, sizeof(m_apObjectModel));

	m_nNumModel = 0;

	m_pMotion = NULL;
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CPlayer::~CPlayer()
{

}

//-------------------------------------
//- プレイヤーの初期化処理
//-------------------------------------
HRESULT CPlayer::Init(CObjectModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax)
{
	// モデルのパーツ数を取得
	m_nNumModel = CObjectModel::GetPartsNum(modelType);

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_nNumModel - 1 == nCount)
		{
			int nData = 0;
		}

		// 階層構造Xオブジェクトの有無を判定
		if (m_apObjectModel[nCount] == NULL)
		{
			// 階層構造Xオブジェクトの生成
			m_apObjectModel[nCount] = CObjectModel::Create(modelType, nCount);

			// 階層構造Xオブジェクトの設定
			m_apObjectModel[nCount]->SetParent(m_apObjectModel, modelType, nCount);
		}
	}

	if (m_pMotion == NULL)
	{
		// モーションの生成
		m_pMotion = CMotion::Create(m_nNumModel, nStateMax);

		// ファイルを読み込み
		m_pMotion->SetFile(motionType);

		// モデルの設定
		m_pMotion->SetModel(m_apObjectModel, 0);

		// 待機モーションを設定
		m_pMotion->Set(0);
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- プレイヤーの終了処理
//-------------------------------------
void CPlayer::Uninit(void)
{
	// モデルの終了処理
	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_nNumModel - 1 == nCount)
		{
			int nData = 0;
		}

		if (m_apObjectModel[nCount] != NULL)
		{
			// モデルの開放処理
			m_apObjectModel[nCount]->Uninit();

			delete m_apObjectModel[nCount];
			m_apObjectModel[nCount] = NULL;
		}
	}

	// モーションの終了処理
	if (m_pMotion != NULL)
	{
		// モーションの開放
		m_pMotion->Uninit();

		delete m_pMotion;
		m_pMotion = NULL;
	}

	// 自分自身のポインタの開放
	Release();
}

//-------------------------------------
//- プレイヤーの更新処理
//-------------------------------------
void CPlayer::Update(void)
{
	// 情報設定（前回の情報）
	m_dataPosOld.Set(m_dataPos.Get());	// 位置
	
	// 移動の入力処理
	InputMove();

	// 向きの更新処理
	UpdateRot();

	// 位置情報の更新処理
	UpdatePos();

	// オブジェクトとの当たり判定
	CollisionObject();

	// デバック表示
	DebugPlayer();
}

//-------------------------------------
//- プレイヤーの描画処理
//-------------------------------------
void CPlayer::Draw(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();	// 位置情報
	D3DXVECTOR3 rot = m_dataRot.Get();	// 向き情報

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// デバイスの情報取得の成功を判定
	if (pDevice == NULL)
	{// 失敗時

	 // 初期化処理を抜ける
		return;
	}

	// 変数宣言
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(
		D3DTS_WORLD,
		&m_mtxWorld);

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		m_apObjectModel[nCount]->Draw();
	}
}

//-------------------------------------
//- プレイヤーのモーション情報取得処理
//-------------------------------------
void CPlayer::Hit(int nDamage)
{

}

//-------------------------------------
//- プレイヤーのモーション情報取得処理
//-------------------------------------
CMotion *CPlayer::GetMotion(void)
{
	// モーションを返す
	return m_pMotion;
}

//-------------------------------------
//- プレイヤーのモデルの情報取得
//-------------------------------------
CObjectModel *CPlayer::GetObjectModel(int nNumParts)
{
	return m_apObjectModel[nNumParts];
}

//-------------------------------------
//- プレイヤーの移動処理
//-------------------------------------
void CPlayer::UpdatePos(void)
{
	// 時間管理の情報を取得
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// 時間管理取得の有無を判定
	if (pManagerTime == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();				// 位置
	D3DXVECTOR3 move = m_dataMove.Get();			// 移動量

	// 時間倍率の計算
	D3DXVECTOR3 moveTime = pManagerTime->CalRate(move);

	// 位置情報に移動量を加算
	pos += moveTime;

	// 移動量を減衰
	move.x += (0.0f - move.x) * 0.3f;
	move.y += (0.0f - move.y) * 0.3f;
	move.z += (0.0f - move.z) * 0.3f;

	// 情報更新
	m_dataPos.Set(pos);		// 位置
	m_dataMove.Set(move);	// 移動量
}

//-------------------------------------
//- プレイヤーの向き処理
//-------------------------------------
void CPlayer::UpdateRot(void)
{
	// 時間管理の情報を取得
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// 時間管理取得の有無を判定
	if (pManagerTime == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 変数宣言（情報取得）
	D3DXVECTOR3 rot = m_dataRot.Get();			// 向き
	D3DXVECTOR3 rotDest = m_dataRotDest.Get();	// 目的の向き

	// 目的の向きの補正
	if (rotDest.y > D3DX_PI)
	{
		rotDest.y += -D3DX_PI * 2;
	}
	else if (rotDest.y < -D3DX_PI)
	{
		rotDest.y += D3DX_PI * 2;
	}

	// 差分の向きを算出
	float rotDiff = rotDest.y - rot.y;

	// 差分の向きを補正
	if (rotDiff > D3DX_PI)
	{
		rotDiff += -D3DX_PI * 2;
	}
	else if (rotDiff < -D3DX_PI)
	{
		rotDiff += D3DX_PI * 2;
	}

	// 時間倍率の計算
	float fRotCorreTime = pManagerTime->CalRate(0.15f);

	//移動方向（角度）の補正
	rot.y += rotDiff * fRotCorreTime;

	// 向きの補正
	if (rot.y > D3DX_PI)
	{
		rot.y += -D3DX_PI * 2;
	}
	else if (rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2;
	}

	// 情報更新
	m_dataRot.Set(rot);				// 向き
	m_dataRotDest.Set(rotDest);		// 目的の向き
}

//-------------------------------------
//- プレイヤーの移動処理
//-------------------------------------
void CPlayer::InputMove(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

	 // 移動処理を抜ける
		return;
	}

	// X入力のポインタを宣言
	CXInput *pXInput = CManager::GetXInput();

	// X入力の情報取得の成功を判定
	if (pXInput == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 時間管理の情報を取得
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// 時間管理取得の有無を判定
	if (pManagerTime == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 変数宣言
	D3DXVECTOR3 move = m_dataMove.Get();		// 移動量を取得
	D3DXVECTOR3 rotDest = m_dataRotDest.Get();	// 目的の回転量を取得

	bool bMoveStop = m_bDataStopMove.Get();				// 移動停止の有無
	bool bMoveRotStop = m_bDataStopMoveRot.Get();		// 向き移動停止の有無

	// カメラの情報を取得
	CCamera *pCamera = CManager::GetCamera();

	// カメラの向きを取得
	D3DXVECTOR3 rotCamera = pCamera->m_dataRot.Get();

	// 時間倍率の計算
	float fPlayerSpeedTime = pManagerTime->CalRate(PLAYER_SPEED);

	// 移動
	if (pInputKeyboard->GetPress(DIK_W) == true ||
		pXInput->GetPress(CXInput::TYPE_STICK_UP, CXInput::TYPE_INPUT_STICK_L) == true)
	{//Wキーが押されたとき
		if (pInputKeyboard->GetPress(DIK_A) == true ||
			pXInput->GetPress(CXInput::TYPE_STICK_LEFT, CXInput::TYPE_INPUT_STICK_L) == true)
		{//左上移動

			move.x -= sinf((D3DX_PI * 0.75f) + rotCamera.y) * fPlayerSpeedTime;
			move.z -= cosf((D3DX_PI * 0.75f) + rotCamera.y) * fPlayerSpeedTime;

			rotDest.y = (D3DX_PI * 0.75f) + rotCamera.y;
		}
		else if (
			pInputKeyboard->GetPress(DIK_D) == true ||
			pXInput->GetPress(CXInput::TYPE_STICK_RIGHT, CXInput::TYPE_INPUT_STICK_L) == true)
		{//右上移動

			move.x += sinf((D3DX_PI * 0.25f) + rotCamera.y) * fPlayerSpeedTime;
			move.z += cosf((D3DX_PI * 0.25f) + rotCamera.y) * fPlayerSpeedTime;

			rotDest.y = -(D3DX_PI * 0.75f) + rotCamera.y;
		}
		else
		{

			move.x += sinf((D3DX_PI * 0.0f) + rotCamera.y) * fPlayerSpeedTime;
			move.z += cosf((D3DX_PI * 0.0f) + rotCamera.y) * fPlayerSpeedTime;

			rotDest.y = D3DX_PI + rotCamera.y;

		}
	}

	else if (
		pInputKeyboard->GetPress(DIK_S) == true ||
		pXInput->GetPress(CXInput::TYPE_STICK_DOWN, CXInput::TYPE_INPUT_STICK_L) == true)
	{//Sキーが押されたとき
		if (
			pInputKeyboard->GetPress(DIK_A) == true ||
			pXInput->GetPress(CXInput::TYPE_STICK_LEFT, CXInput::TYPE_INPUT_STICK_L) == true)
		{//左下移動

			move.x -= sinf((D3DX_PI * 0.25f) + rotCamera.y) * fPlayerSpeedTime;
			move.z -= cosf((D3DX_PI * 0.25f) + rotCamera.y) * fPlayerSpeedTime;

			rotDest.y = (D3DX_PI * 0.25f) + rotCamera.y;
		}
		else  if (
			pInputKeyboard->GetPress(DIK_D) == true ||
			pXInput->GetPress(CXInput::TYPE_STICK_RIGHT, CXInput::TYPE_INPUT_STICK_L) == true)
		{//右下移動

			move.x += sinf((D3DX_PI * 0.75f) + rotCamera.y) * fPlayerSpeedTime;
			move.z += cosf((D3DX_PI * 0.75f) + rotCamera.y) * fPlayerSpeedTime;

			rotDest.y = -(D3DX_PI * 0.25f) + rotCamera.y;
		}
		else
		{
			//移動量
			move.x += sinf((D3DX_PI * 1.0f) + rotCamera.y) * fPlayerSpeedTime;
			move.z += cosf((D3DX_PI * 1.0f) + rotCamera.y) * fPlayerSpeedTime;

			rotDest.y = (D3DX_PI * 0.0f) + rotCamera.y;
		}
	}

	else  if (
		pInputKeyboard->GetPress(DIK_A) == true ||
		pXInput->GetPress(CXInput::TYPE_STICK_LEFT, CXInput::TYPE_INPUT_STICK_L) == true)
	{//Aキーが押されたとき

		move.x -= sinf((D3DX_PI * 0.5f) + rotCamera.y) * fPlayerSpeedTime;
		move.z -= cosf((D3DX_PI * 0.5f) + rotCamera.y) * fPlayerSpeedTime;

		rotDest.y = (D3DX_PI * 0.5f) + rotCamera.y;
	}
	else if (
		pInputKeyboard->GetPress(DIK_D) == true ||
		pXInput->GetPress(CXInput::TYPE_STICK_RIGHT, CXInput::TYPE_INPUT_STICK_L) == true)
	{//Dキーが押されたとき

		move.x += sinf((D3DX_PI * 0.5f) + rotCamera.y) * fPlayerSpeedTime;
		move.z += cosf((D3DX_PI * 0.5f) + rotCamera.y) * fPlayerSpeedTime;

		rotDest.y = -(D3DX_PI * 0.5f) + rotCamera.y;
	}

	if (bMoveRotStop != true)
	{
		// 目的の向きを更新
		m_dataRotDest.Set(rotDest);
	}

	if (bMoveStop != true)
	{
		// 移動量の更新
		m_dataMove.Set(move);
	}
}

//-------------------------------------
//- プレイヤーのオブジェクトとの当たり判定
//-------------------------------------
void CPlayer::CollisionObject(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();			// 位置
	D3DXVECTOR3 posOld = m_dataPosOld.Get();	// 前回の位置
	D3DXVECTOR3 size = m_dataSize.Get();		// 大きさ
	D3DXVECTOR3 move = m_dataMove.Get();		// 移動量

	for (int nCutObjectNone = 0; nCutObjectNone < OBJECTX_NONE_NUM_MAX; nCutObjectNone++)
	{
		// イベントオブジェクトの情報を取得
		CObjectX *pObjectNone = CManagerObject::GetObjectNone(nCutObjectNone);

		// イベントオブジェクトの有無を判定
		if (pObjectNone != NULL)
		{
			CollisionMove(pObjectNone);
		}
	}

	for (int nCutEventObject = 0; nCutEventObject < EVENT_OBJECT_NUM_MAX; nCutEventObject++)
	{
		// イベントオブジェクトの情報を取得
		CObjectX *pEventObject = CManagerObject::GetEventObject(nCutEventObject);

		// イベントオブジェクトの有無を判定
		if (pEventObject != NULL)
		{
			CollisionMove(pEventObject);
		}
	}

	for (int nCount = 0; nCount < GARBAGE_COLLECT_NUM_MAX; nCount++)
	{
		// イベントオブジェクトの情報を取得
		CObjectX *pGarbageCollect = CManagerObject::GetGarbageCollect(nCount);

		// イベントオブジェクトの有無を判定
		if (pGarbageCollect != NULL)
		{
			CollisionMove(pGarbageCollect);
		}
	}

	// イベントオブジェクトの情報を取得
	CObjectX *pGate = CManagerObject::GetGate();

	// イベントオブジェクトの有無を判定
	if (pGate != NULL)
	{
		CollisionMove(pGate);
	}

	for (int nCount = 0; nCount < WALL_NUM_MAX; nCount++)
	{
		// 壁の情報を取得
		CObject3d *pWall = CManagerObject::GetWall(nCount);

		// イベントオブジェクトの有無を判定
		if (pWall != NULL)
		{
			CollisionMove(pWall);
		}
	}
}

//-------------------------------------
//- プレイヤーの当たり判定の移動制御
//-------------------------------------
void CPlayer::CollisionMove(CObjectX *pObjX)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();			// 位置
	D3DXVECTOR3 posOld = m_dataPosOld.Get();	// 前回の位置
	D3DXVECTOR3 size = m_dataSize.Get();		// 大きさ
	D3DXVECTOR3 move = m_dataMove.Get();		// 移動量

	// 変数宣言（オブジェクト情報取得）
	D3DXVECTOR3 objPos = pObjX->m_dataPos.Get();	// 位置
	D3DXVECTOR3 objSize = pObjX->m_dataSize.Get();	// 大きさ

	// 変数宣言
	bool bX = false;
	bool bZ = false;

	//当たり判定
	if (CHit::hitRectangle(pos, size, objPos, objSize) == true)
	{
		//横の当たり判定
		if (CHit::hitRectangleSide(pos.x, size.x, objPos.x, objSize.x) == true)
		{
			//前回の位置が縦の範囲内にいる場合
			if (CHit::hitRectangleSide(posOld.z, size.z, objPos.z, objSize.z) == true)
			{
				bX = true;
			}
		}

		//縦の当たり判定
		if (CHit::hitRectangleSide(pos.z, size.z, objPos.z, objSize.z) == true)
		{
			//前回の位置が横の範囲内にいる場合
			if (CHit::hitRectangleSide(posOld.x, size.x, objPos.x, objSize.x) == true)
			{
				bZ = true;
			}
		}

		if (bX == true &&
			bZ == true)
		{
			pos.x = posOld.x;
			pos.z = posOld.z;

			m_dataPos.Set(pos);			// 位置
			m_dataMove.Set(move);		// 移動量
		}
		else if (bX == true)
		{
			// プレイヤーのY座標移動を停止
			move.x = 0.0f;

			pos.x = posOld.x;

			m_dataPos.Set(pos);			// 位置
			m_dataMove.Set(move);		// 移動量
		}
		else if (bZ == true)
		{
			// プレイヤーのY座標移動を停止
			move.z = 0.0f;

			pos.z = posOld.z;

			m_dataPos.Set(pos);			// 位置
			m_dataMove.Set(move);		// 移動量
		}
	}
}

//-------------------------------------
//- プレイヤーの当たり判定の移動制御（壁）
//-------------------------------------
void CPlayer::CollisionMove(CObject3d *pObj3d)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();			// 位置
	D3DXVECTOR3 posOld = m_dataPosOld.Get();	// 前回の位置
	D3DXVECTOR3 size = m_dataSize.Get();		// 大きさ
	D3DXVECTOR3 move = m_dataMove.Get();		// 移動量

	// 変数宣言（オブジェクト情報取得）
	D3DXVECTOR3 objPos = pObj3d->m_dataPos.Get();	// 位置
	D3DXVECTOR3 objSize = pObj3d->m_dataSize.Get();	// 大きさ
	D3DXVECTOR3 objRot = pObj3d->m_dataRot.Get();	// 向き

	// 変数宣言
	bool bX = false;
	bool bZ = false;

	//当たり判定
	if (objRot.y == D3DX_PI * 0.5f ||
		objRot.y == -D3DX_PI * 0.5f)
	{
		//横の当たり判定
		if (CHit::hitRectangleSide(pos.x, size.x, objPos.x, objSize.z) == true)
		{
			//前回の位置が縦の範囲内にいる場合
			if (CHit::hitRectangleSide(posOld.z, size.z, objPos.z, objSize.x) == true)
			{
				bX = true;
			}
		}
	}

	if (objRot.y == 0.0f ||
		objRot.y == D3DX_PI)
	{
		//縦の当たり判定
		if (CHit::hitRectangleSide(pos.z, size.z, objPos.z, objSize.z) == true)
		{
			//前回の位置が横の範囲内にいる場合
			if (CHit::hitRectangleSide(posOld.x, size.x, objPos.x, objSize.x) == true)
			{
				bZ = true;
			}
		}
	}

	if (bX == true &&
		bZ == true)
	{
		pos.x = posOld.x;
		pos.z = posOld.z;

		m_dataPos.Set(pos);			// 位置
		m_dataMove.Set(move);		// 移動量
	}
	else if (bX == true)
	{
		// プレイヤーのY座標移動を停止
		move.x = 0.0f;

		pos.x = posOld.x;

		m_dataPos.Set(pos);			// 位置
		m_dataMove.Set(move);		// 移動量
	}
	else if (bZ == true)
	{
		// プレイヤーのY座標移動を停止
		move.z = 0.0f;

		pos.z = posOld.z;

		m_dataPos.Set(pos);			// 位置
		m_dataMove.Set(move);		// 移動量
	}
}

//-------------------------------------
//- プレイヤーのデバック表示
//-------------------------------------
void CPlayer::DebugPlayer(void)
{
	// デバックプロックの取得
	CDebugProc *pDebugProc = CManager::GetDbugProc();

	// デバックプロック取得の有無を判定
	if (pDebugProc == NULL)
	{
		return;
	}

	pDebugProc->Print("\n");
	pDebugProc->Print("プレイヤーの位置\n");
	pDebugProc->Print("%f,%f,%f",m_dataPos.Get().x,m_dataPos.Get().y,m_dataPos.Get().z);
	pDebugProc->Print("\n");
}