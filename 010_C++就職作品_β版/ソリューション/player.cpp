
//-===============================================
//-
//-	プレイヤー処理[player.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "player.h"

#include "renderer.h"
#include "manager.h"

#include "fade.h"

#include "Input.h"
#include "xinput.h"

#include "sound.h"
#include "debugproc.h"

#include "helper_sakai.h"

#include "camera.h"

#include "coll.h"
#include "enemy.h"

#include "command.h"

#include "attack.h"
#include "punch.h"

#include "finish_punch.h"
#include "finish_kick.h"

#include "particle.h"

#include "obj_2d_gage.h"

//-======================================
//-	マクロ定義
//-======================================

#define PLAYER_SPEED		(3.0f)	// プレイヤーの速度

//-======================================
//-	静的変数宣言
//-======================================

//-======================================
//-	コンスト定義
//-======================================

// 状態の時間
const int STATE_TIME[CPlayer::STATE_MAX]
{
	0,
	180,
	0,
};

const int PARTS_NUM_PUNCH = 4;
const int PARTS_NUM_PUNCH_FINISH = 7;
const int PARTS_NUM_KICK = 11;
const int PARTS_NUM_KICK_FINISH = 0;

// フィニッシュ時の位置の追加量
const D3DXVECTOR3 FINISH_POS_PLUS[CCommand::COMMAND_TYPE_MAX]
{
	D3DXVECTOR3(0.0f,0.0f,0.0f),
	D3DXVECTOR3(0.0f,50.0f,0.0f),
};

// フィニッシュ時の大きさ
const D3DXVECTOR3 FINISH_SIZE[CCommand::COMMAND_TYPE_MAX]
{
	D3DXVECTOR3(20.0f, 20.0f, 20.0f),
	D3DXVECTOR3(100.0f, 40.0f, 100.0f),
};

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CPlayer::CPlayer()
{
	// 値をクリア
	ZeroMemory(&m_data, sizeof(m_data));
	ZeroMemory(&m_mtxWorld, sizeof(m_mtxWorld));


	ZeroMemory(&m_apModel, sizeof(m_apModel));
	m_nNumModel = 0;

	ZeroMemory(&m_apColl, sizeof(m_apColl));
	m_pMotion = nullptr;
	m_pAttack = nullptr;
	m_pCommand = nullptr;
	m_pLife2dGage = nullptr;
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
HRESULT CPlayer::Init(D3DXVECTOR3 pos , D3DXVECTOR3 rot,CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax)
{
	// モデルのパーツ数を取得
	m_nNumModel = CModel::GetPartsNum(modelType);

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		// 階層構造Xオブジェクトの有無を判定
		if (m_apModel[nCount] == NULL)
		{
			// 階層構造Xオブジェクトの生成
			m_apModel[nCount] = CModel::Create(modelType, nCount);

			if (m_apModel[nCount] == nullptr)
			{
				return E_FAIL;
			}

			// 階層構造Xオブジェクトの設定
			m_apModel[nCount]->SetParent(m_apModel, modelType, nCount);
		}
	}

	if (m_pMotion == NULL)
	{
		// モーションの生成
		m_pMotion = CMotion::Create(m_nNumModel, nStateMax);

		if (m_pMotion == nullptr)
		{
			return E_FAIL;
		}

		// ファイルを読み込み
		m_pMotion->SetFile(motionType);

		// モデルの設定
		m_pMotion->SetModel(m_apModel, 0);

		// 待機モーションを設定
		m_pMotion->Set(0);
	}

	// コマンド
	if (m_pCommand == nullptr)
	{
		// コマンドの生成
		m_pCommand = CCommand::Create();

		if (m_pCommand == nullptr)
		{
			return E_FAIL;
		}
	}

	// 体力
	if (m_pLife2dGage == nullptr)
	{
		// 体力の生成
		m_pLife2dGage = CObj2dGage::Create();

		if (m_pLife2dGage == nullptr)
		{
			return E_FAIL;
		}
	}

	// 戦闘プレイヤーの設定処理
	InitSet(pos, rot);

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- プレイヤーの終了処理
//-------------------------------------
void CPlayer::Uninit(void)
{
	for (int nCount = 0; nCount < COLL_TYPE_MAX; nCount++)
	{
		if (m_apColl[nCount] != NULL)
		{
			// 当たり判定の終了処理
			m_apColl[nCount]->Uninit();

			delete m_apColl[nCount];
			m_apColl[nCount] = NULL;
		}
	}

	// モデルの終了処理
	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{
			// モデルの開放処理
			m_apModel[nCount]->Uninit();

			delete m_apModel[nCount];
			m_apModel[nCount] = NULL;
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

	// コマンドの終了処理
	if (m_pCommand != NULL)
	{
		// モーションの開放
		m_pCommand->Uninit();

		delete m_pCommand;
		m_pCommand = NULL;
	}

	// 攻撃の終了処理
	if (m_pAttack != nullptr)
	{
		m_pAttack->Uninit();
		m_pAttack = nullptr;
	}

	// 体力表示の終了処理
	if (m_pLife2dGage != nullptr)
	{
		m_pLife2dGage->Uninit();
		m_pLife2dGage = nullptr;
	}

	// 自分自身のポインタの開放
	Release();
}

//-------------------------------------
//- プレイヤーの更新処理
//-------------------------------------
void CPlayer::Update(void)
{
	// 前回の位置を更新
	m_data.posOld = m_data.pos;

	if (m_data.state == STATE_NEUTRAL)
	{
		// 移動の入力処理
		InputMove();
	}
	else if (m_data.state == STATE_BATTLE ||
			 m_data.state == STATE_FINISH)
	{
		// 攻撃処理
		UpdateBattle();
	}

	// コンボ入力処理
	InputCombo();

	// 向きの更新処理
	UpdateRot();

	// 位置情報の更新処理
	UpdatePos();

	// 追加情報の更新処理
	UpdatePlusData();

	// 通常モーションの更新処理
	UpdateMotionNone();

	// 攻撃の更新処理
	UpdateAttack();

	// コマンドの更新処理
	UpdateCommand();

	// 当たり判定の更新処理
	UpdateCollision();

	if (m_pLife2dGage != nullptr)
	{
		m_pLife2dGage->UpdateInfo(
			m_pLife2dGage->GetPos(),
			m_pLife2dGage->GetSize(),
			m_pLife2dGage->GetColor(),
			m_data.nLife);
	}

	// デバック表示
	DebugPlayer();
}

//-------------------------------------
//- プレイヤーの描画処理
//-------------------------------------
void CPlayer::Draw(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_data.pos;	// 位置情報
	D3DXVECTOR3 rot = m_data.rot;	// 向き情報

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

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

	// パーツ数の描画処理
	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_apModel[nCount] != nullptr)
		{
			m_apModel[nCount]->Draw();
		}
	}

	if (m_pCommand != NULL)
	{
		// コマンドの描画処理
		m_pCommand->Draw();
	}
}
//-------------------------------------
//- プレイヤーのキック攻撃設定処理
//-------------------------------------
void CPlayer::HitDamage(int nDamage)
{
	m_data.nLife -= nDamage;

	// パーティクルの設定
	SetParticle(
		8,
		m_data.pos,
		D3DXVECTOR3(10.0f, 10.0f, 0.0f),
		D3DXVECTOR3(10.0f, 10.0f, 0.0f),
		D3DXCOLOR(1.0f, 0.0, 0.0f, 1.0f),
		30);

	if (m_data.nLife < 0)
	{
		if (CManager::GetInstance() != nullptr)
		{
			if (CManager::GetInstance()->GetFade() != nullptr)
			{
				// ゲームモード
				CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_RESULT);
			}
		}

	}
}

//-------------------------------------
//- プレイヤーの生成処理
//-------------------------------------
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType)
{
	// プレイヤーのポインタを宣言
	CPlayer *pPlayer = DBG_NEW CPlayer;

	// 生成の成功の有無を判定
	if (pPlayer != NULL)
	{
		// 初期化処理
		if (FAILED(pPlayer->Init(pos, rot, modelType, motionType, MOTION_STATE_MAX)))
		{// 失敗時

		 // 「なし」を返す
			return NULL;
		}
	}
	else if (pPlayer == NULL)
	{// 失敗時

	 // 「なし」を返す
		return NULL;
	}

	// プレイヤーのポインタを返す
	return pPlayer;
}

//-------------------------------------
//- プレイヤーの初期設定処理
//-------------------------------------
void CPlayer::InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_data.pos = pos;
	m_data.posOld = pos;
	m_data.rot = rot;
	m_data.rotDest = rot;

	m_data.size = D3DXVECTOR3(40.0f, 200.0f, 40.0f);

	m_data.nLife = 50;

	for (int nCount = 0; nCount < COLL_TYPE_MAX; nCount++)
	{
		if (m_apColl[nCount] == NULL)
		{
			switch (nCount)
			{
			case COLL_TYPE_NEUTRAL:
				
				// 当たり判定設定
				m_apColl[nCount] = CColl::Create(
					CMgrColl::TAG_PLAYER,
					this,
					m_data.pos,
					m_data.size);

				break;

			case COLL_TYPE_SEARCH:

				// 当たり判定設定
				m_apColl[nCount] = CColl::Create(
					CMgrColl::TAG_NONE,
					this,
					m_data.pos,
					m_data.size + D3DXVECTOR3(100.0f,0.0f,100.0f));

				break;
			}

		}
	}

	if (m_pLife2dGage != NULL)
	{
		m_pLife2dGage->SetInit(
			D3DXVECTOR3(SCREEN_WIDTH * 0.2f,SCREEN_HEIGHT * 0.1f,0.0f),
			D3DXVECTOR3(150.0f, 15.0f, 0.0f),
			D3DXCOLOR(0.0f,1.0f,0.0f,1.0f),
			m_data.nLife,
			m_data.nLife);
	}
	
	m_data.plus.speedRate = 1.0f;
}

//-------------------------------------
//- プレイヤーの移動処理
//-------------------------------------
void CPlayer::UpdatePos(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_data.pos;	// 位置
	D3DXVECTOR3 move = m_data.move;	// 移動量

	// 位置情報に移動量を加算
	pos += move;

	// 移動量を減衰
	move.x += (0.0f - move.x) * 0.3f;
	move.z += (0.0f - move.z) * 0.3f;

	// 情報更新
	m_data.pos = pos;
	m_data.move = move;
}

//-------------------------------------
//- プレイヤーの攻撃更新処理
//-------------------------------------
void CPlayer::UpdateBattle(void)
{
	if (m_data.bIsTarget)
	{
		// 位置情報に移動量を加算
		float rotTgt = atan2f(m_data.pos.x - m_data.posTgt.x, m_data.pos.z - m_data.posTgt.z);

		m_data.rotDest.y = rotTgt;
	}

	m_data.pos += D3DXVECTOR3(-sinf(m_data.rot.y) * 3.0f, 0.0f, -cosf(m_data.rot.y) * 3.0f);

	// 移動量を減衰
	m_data.move.x += (0.0f - m_data.move.x) * 0.3f;
	m_data.move.z += (0.0f - m_data.move.z) * 0.3f;

}

//-------------------------------------
//- プレイヤーの向き処理
//-------------------------------------
void CPlayer::UpdateRot(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 rot = m_data.rot;			// 向き
	D3DXVECTOR3 rotDest = m_data.rotDest;	// 目的の向き

	HelperSakai::NormalizeAngle(&rot, &rotDest, 0.15f);

	// 情報更新
	m_data.rot = rot;			// 向き
	m_data.rotDest = rotDest;	// 目的の向き
}

//-------------------------------------
//- プレイヤーの追加データの更新処理
//-------------------------------------
void CPlayer::UpdatePlusData(void)
{
	if (m_data.plus.sppedPlusTime != 0)
	{
		m_data.plus.sppedPlusTime--;
		
		if (m_data.plus.sppedPlusTime <= 0)
		{
			m_data.plus.speedRate = 1.0f;
		}
	}	
}

//-------------------------------------
//- 通常状態プレイヤーの攻撃の更新処理
//-------------------------------------
void CPlayer::UpdateAttack(void)
{
	// 攻撃の情報更新処理
	if (m_pAttack != nullptr)
	{
		D3DXVECTOR3 posParts = {};
		
		// パーツの位置
		posParts = D3DXVECTOR3(
			GetModel(m_data.nAttackPartsNldx)->GetMtxWorld()._41,
			GetModel(m_data.nAttackPartsNldx)->GetMtxWorld()._42,
			GetModel(m_data.nAttackPartsNldx)->GetMtxWorld()._43);

		if (m_pAttack->GetColl() != nullptr)
		{
			D3DXVECTOR3 size = m_pAttack->GetSize();

			m_pAttack->UpdateData(posParts, size);
		}
	}
}

//-------------------------------------
//- 通常状態プレイヤーのコマンドの更新処理
//-------------------------------------
void CPlayer::UpdateCommand(void)
{
	if (m_pCommand != NULL)
	{
		// コマンドの更新処理
		m_pCommand->Update();
	}
}

//-------------------------------------
//- 通常状態プレイヤーの当たり判定の更新処理
//-------------------------------------
void CPlayer::UpdateCollision(void)
{
	for (int nCntColl = 0; nCntColl < COLL_TYPE_MAX; nCntColl++)
	{
		if (m_apColl[nCntColl] != NULL)
		{
			CManager* pManager = CManager::GetInstance();

			if (pManager == nullptr)
			{
				return;
			}

			CMgrColl* pMgrColl = pManager->GetMgrColl();

			if (pMgrColl == nullptr)
			{
				return;
			}

			switch (nCntColl)
			{
			case COLL_TYPE_NEUTRAL:

				// 当たり判定の情報更新処理
				m_apColl[nCntColl]->UpdateData(
					m_data.pos,
					m_data.posOld,
					m_data.size);

				// プレイヤーの当たり判定
				if (m_apColl[nCntColl]->HitSide(CMgrColl::TAG_WALL_X, CMgrColl::EVENT_TYPE_PRESS, CMgrColl::TYPE_SXIS_X) == true)
				{
					// 移動量をなくす
					m_data.move.x = 0.0f;

					// プレイヤーのY座標移動を停止
					m_data.pos.x = m_data.posOld.x;
				}

				// プレイヤーの当たり判定
				if (m_apColl[nCntColl]->HitSide(CMgrColl::TAG_WALL_Z, CMgrColl::EVENT_TYPE_PRESS, CMgrColl::TYPE_SXIS_Z) == true)
				{
					// 移動量をなくす
					m_data.move.z = 0.0f;

					// プレイヤーのY座標移動を停止
					m_data.pos.z = m_data.posOld.z;
				}

				// 出現壁との当たり判定
				if (m_apColl[nCntColl]->HitSide(CMgrColl::TAG_SPAWN_ENEMY_WALL, CMgrColl::EVENT_TYPE_TRIGGER, CMgrColl::TYPE_SXIS_X) == true)
				{
					// 最大接触数を取得
					CColl::Data data = m_apColl[nCntColl]->GetData();
					int nHitNldxMax = data.nHitNldxMax;

					// 接触した敵のダメージ処理
					for (int nCount = 0; nCount < nHitNldxMax; nCount++)
					{
						CColl* pColl = pMgrColl->GetColl(data.hitData[nCount].nNldx);

						if (pColl != nullptr)
						{
							CObject* pObj = pColl->GetData().pObj;

							if (pObj != nullptr)
							{
								pObj->Hit();
							}
						}
					}
				}

				break;

			case COLL_TYPE_SEARCH:

				if (m_data.rot.y >= 0.0f && m_data.rot.y <= (D3DX_PI * 0.25f) ||
					m_data.rot.y <= 0.0f && m_data.rot.y >= -(D3DX_PI * 0.25f) ||
					m_data.rot.y >= (D3DX_PI * 0.75f) && m_data.rot.y <= D3DX_PI ||
					m_data.rot.y <= -(D3DX_PI * 0.75f) && m_data.rot.y >= -D3DX_PI)
				{
					// 当たり判定の情報更新処理
					m_apColl[nCntColl]->UpdateData(
						m_data.pos + D3DXVECTOR3((-sinf(m_data.rot.y) * m_data.size.x), 0.0f, (-cosf(m_data.rot.y) * m_data.size.z)),
						m_data.posOld,
						D3DXVECTOR3(200.0f, 50.0f, 100.0f));
				}
				else if (
					m_data.rot.y >= (D3DX_PI * 0.25f) && m_data.rot.y <= (D3DX_PI * 0.75f) ||
					m_data.rot.y <= -(D3DX_PI * 0.25f) && m_data.rot.y >= -(D3DX_PI * 0.75f))
				{
					// 当たり判定の情報更新処理
					m_apColl[nCntColl]->UpdateData(
						m_data.pos + D3DXVECTOR3((-sinf(m_data.rot.y) * m_data.size.x), 0.0f, (-cosf(m_data.rot.y) * m_data.size.z)),
						m_data.posOld,
						D3DXVECTOR3(100.0f, 50.0f, 200.0f));
				}

				// プレイヤーの当たり判定
				if (m_apColl[nCntColl]->Hit(CMgrColl::TAG_ENEMY, CMgrColl::EVENT_TYPE_PRESS))
				{
					float fLengthNear = 100000.0f;
					int nHitNldxMaxTemp = m_apColl[nCntColl]->GetData().nHitNldxMaxTemp;

					for (int nCntLength = 0; nCntLength < nHitNldxMaxTemp; nCntLength++)
					{
						float fLength = m_apColl[nCntColl]->GetData().hitDataTemp[nCntLength].fLength;

						if (fLength < fLengthNear)
						{
							fLengthNear = fLength;

							int hitNldx = m_apColl[nCntColl]->GetData().hitDataTemp[nCntLength].nNldx;

							CColl* pCollPair = pMgrColl->GetColl(hitNldx);

							if (pCollPair != nullptr)
							{
								m_data.posTgt = pCollPair->GetData().pos;

								m_data.bIsTarget = true;
							}
						}
					}
				}
				else
				{
					m_data.bIsTarget = false;
				}

				break;
			}

		}

	}
}

//-------------------------------------
//- 通常状態プレイヤーのモーション更新処理
//-------------------------------------
void CPlayer::UpdateMotionNone(void)
{
	// 変数宣言（情報取得）
	CMotion* pMotion = GetMotion();		// モーション
	D3DXVECTOR3 move = GetData().move;	// 移動量

	// 状態を判定
	if (m_data.motionState == MOTION_STATE_NEUTRAL ||
		m_data.motionState == MOTION_STATE_MOVE)
	{
		// 移動量で状態を変更
		if (move.x >= 0.3f ||
			move.x <= -0.3f ||
			move.z >= 0.3f ||
			move.z <= -0.3f)
		{
			// 移動状態に変更
			m_data.motionState = MOTION_STATE_MOVE;
		}
		else
		{
			// 待機状態の変更
			m_data.motionState = MOTION_STATE_NEUTRAL;
		}
	}

	if (pMotion->GetType() == MOTION_STATE_PUNCH && m_data.motionState != MOTION_STATE_PUNCH ||
		pMotion->GetType() == MOTION_STATE_KICK && m_data.motionState != MOTION_STATE_KICK ||
		pMotion->GetType() == MOTION_STATE_PUNCH_FINISH && m_data.motionState != MOTION_STATE_PUNCH_FINISH ||
		pMotion->GetType() == MOTION_STATE_KICK_FINISH && m_data.motionState != MOTION_STATE_KICK_FINISH)
	{
		if (m_pAttack != nullptr)
		{
			// 終了処理
			m_pAttack->Uninit();
			m_pAttack = nullptr;
		}

		m_data.state = STATE_NEUTRAL;
	}

	if (m_data.motionState != pMotion->GetType())
	{
		pMotion->Set(m_data.motionState);
	}

	// モーションの終了状況を判定
	if (pMotion->IsFinsih())
	{
		// モーションの更新
		pMotion->Update();
	}
	else
	{
		// 待機状態を設定
		m_data.motionState = MOTION_STATE_NEUTRAL;
	}
}

//-------------------------------------
//- プレイヤーの移動処理
//-------------------------------------
void CPlayer::InputMove(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInstance()->GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

	 // 移動処理を抜ける
		return;
	}

	// X入力のポインタを宣言
	CXInput *pXInput = CManager::GetInstance()->GetXInput();

	// X入力の情報取得の成功を判定
	if (pXInput == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 変数宣言
	D3DXVECTOR3 move = m_data.move;					// 移動量を取得
	D3DXVECTOR3 rotDest = m_data.rotDest;			// 目的の回転量を取得
	float speedRate = m_data.plus.speedRate;		// 速度の倍率

	D3DXVECTOR3 speed = D3DXVECTOR3(PLAYER_SPEED, 0.0f, PLAYER_SPEED);
	speed *= speedRate;

	// カメラの情報を取得
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	// カメラの向きを取得
	D3DXVECTOR3 rotCamera = pCamera->GetData().rot;

	// 移動
	if (pInputKeyboard->GetPress(DIK_W) == true ||
		pXInput->GetPress(CXInput::TYPE_STICK_UP, CXInput::TYPE_INPUT_STICK_L) == true)
	{//Wキーが押されたとき
		if (pInputKeyboard->GetPress(DIK_A) == true ||
			pXInput->GetPress(CXInput::TYPE_STICK_LEFT, CXInput::TYPE_INPUT_STICK_L) == true)
		{//左上移動

			move.x -= sinf((D3DX_PI * 0.75f) + rotCamera.y) * speed.x;
			move.z -= cosf((D3DX_PI * 0.75f) + rotCamera.y) * speed.z;

			rotDest.y = (D3DX_PI * 0.75f) + rotCamera.y;
		}
		else if (
			pInputKeyboard->GetPress(DIK_D) == true ||
			pXInput->GetPress(CXInput::TYPE_STICK_RIGHT, CXInput::TYPE_INPUT_STICK_L) == true)
		{//右上移動

			move.x += sinf((D3DX_PI * 0.25f) + rotCamera.y) * speed.x;
			move.z += cosf((D3DX_PI * 0.25f) + rotCamera.y) * speed.z;

			rotDest.y = -(D3DX_PI * 0.75f) + rotCamera.y;
		}
		else
		{

			move.x += sinf((D3DX_PI * 0.0f) + rotCamera.y) * speed.x;
			move.z += cosf((D3DX_PI * 0.0f) + rotCamera.y) * speed.z;

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

			move.x -= sinf((D3DX_PI * 0.25f) + rotCamera.y) * speed.x;
			move.z -= cosf((D3DX_PI * 0.25f) + rotCamera.y) * speed.z;

			rotDest.y = (D3DX_PI * 0.25f) + rotCamera.y;
		}
		else  if (
			pInputKeyboard->GetPress(DIK_D) == true ||
			pXInput->GetPress(CXInput::TYPE_STICK_RIGHT, CXInput::TYPE_INPUT_STICK_L) == true)
		{//右下移動

			move.x += sinf((D3DX_PI * 0.75f) + rotCamera.y) * speed.x;
			move.z += cosf((D3DX_PI * 0.75f) + rotCamera.y) * speed.z;

			rotDest.y = -(D3DX_PI * 0.25f) + rotCamera.y;
		}
		else
		{
			//移動量
			move.x += sinf((D3DX_PI * 1.0f) + rotCamera.y) * speed.x;
			move.z += cosf((D3DX_PI * 1.0f) + rotCamera.y) * speed.z;

			rotDest.y = (D3DX_PI * 0.0f) + rotCamera.y;
		}
	}

	else  if (
		pInputKeyboard->GetPress(DIK_A) == true ||
		pXInput->GetPress(CXInput::TYPE_STICK_LEFT, CXInput::TYPE_INPUT_STICK_L) == true)
	{//Aキーが押されたとき

		move.x -= sinf((D3DX_PI * 0.5f) + rotCamera.y) * speed.x;
		move.z -= cosf((D3DX_PI * 0.5f) + rotCamera.y) * speed.z;

		rotDest.y = (D3DX_PI * 0.5f) + rotCamera.y;
	}
	else if (
		pInputKeyboard->GetPress(DIK_D) == true ||
		pXInput->GetPress(CXInput::TYPE_STICK_RIGHT, CXInput::TYPE_INPUT_STICK_L) == true)
	{//Dキーが押されたとき

		move.x += sinf((D3DX_PI * 0.5f) + rotCamera.y) * speed.x;
		move.z += cosf((D3DX_PI * 0.5f) + rotCamera.y) * speed.z;

		rotDest.y = -(D3DX_PI * 0.5f) + rotCamera.y;
	}

	// 情報更新
	m_data.move = move;			// 移動量
	m_data.rotDest = rotDest;	// 目的の向き
}

//-------------------------------------
//- プレイヤーのコンボ入力処理
//-------------------------------------
void CPlayer::InputCombo(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInstance()->GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

	 // 移動処理を抜ける
		return;
	}

	// X入力のポインタを宣言
	CXInput* pXInput = CManager::GetInstance()->GetXInput();

	// X入力の情報取得の成功を判定
	if (pXInput == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 入力種類情報を格納
	CCommand::INPUT_TYPE inputType = CCommand::INPUT_TYPE_NONE;

	if (m_data.motionState == MOTION_STATE_NEUTRAL ||
		m_data.motionState == MOTION_STATE_MOVE)
	{
		if (
			pInputKeyboard->GetTrigger(DIK_J) == true ||
			pXInput->GetTrigger(XINPUT_GAMEPAD_A, CXInput::TYPE_INPUT_BUTTON) == true)
		{
			// パンチ
			inputType = CCommand::INPUT_TYPE_PUNCH;
		}
		else if (
			pInputKeyboard->GetTrigger(DIK_K) == true ||
			pXInput->GetTrigger(XINPUT_GAMEPAD_B, CXInput::TYPE_INPUT_BUTTON) == true)
		{
			// キック
			inputType = CCommand::INPUT_TYPE_KICK;
		}
	}

	if (m_pCommand != nullptr &&
		inputType != CCommand::INPUT_TYPE_NONE)
	{
		// コマンドの入力処理を設定｛フィニッシュの有無を取得｝
		bool bFinish = m_pCommand->SetInput(inputType);

		if (bFinish)
		{
			// 状態設定
			m_data.state = STATE_FINISH;
			 
			// フィニッシュ攻撃
			SetAttackFinish();
		}
		else
		{
			// 状態設定
			m_data.state = STATE_BATTLE;

			// 入力の設定処理
			SetAttack(inputType);
		}
	}
}

//-------------------------------------
//- プレイヤーのパンチ攻撃設定処理
//-------------------------------------
void CPlayer::SetAttack(CCommand::INPUT_TYPE inputType)
{
	switch (inputType)
	{
	case CCommand::INPUT_TYPE_PUNCH:

		// モーションの設定（パンチ）
		m_data.motionState = MOTION_STATE_PUNCH;
		m_data.nAttackPartsNldx = PARTS_NUM_PUNCH;

		break;
	case CCommand::INPUT_TYPE_KICK:

		// モーションの設定（パンチ）
		m_data.motionState = MOTION_STATE_KICK;
		m_data.nAttackPartsNldx = PARTS_NUM_KICK;

		break;
	}

	if (m_pAttack == nullptr)
	{
		m_pAttack = CAttack::Create();

		if (m_pAttack != nullptr)
		{
			// パーツの位置
			D3DXVECTOR3 posParts = D3DXVECTOR3(
				GetModel(m_data.nAttackPartsNldx)->GetMtxWorld()._41,
				GetModel(m_data.nAttackPartsNldx)->GetMtxWorld()._42,
				GetModel(m_data.nAttackPartsNldx)->GetMtxWorld()._43);

			// 攻撃の初期設定処理
			m_pAttack->InitSet(
				posParts,
				D3DXVECTOR3(20.0f,20.0f,20.0f),
				3,
				CMgrColl::TAG_ENEMY);
		}
	}
}

//-------------------------------------
//- プレイヤーのフィニッシュ攻撃設定処理
//-------------------------------------
void CPlayer::SetAttackFinish(void)
{
	CCommand::InfoFinish infoFinish = m_pCommand->GetInfoFinish();

	switch (infoFinish.type)
	{
	case CCommand::COMMAND_TYPE_PUNCH_NOR:

		m_pAttack = CFinishPunch::Create();

		if (m_pAttack != nullptr)
		{
			// モーションの設定（パンチフィニッシュ）
			m_data.motionState = MOTION_STATE_PUNCH_FINISH;

			// パーツ位置
			m_data.nAttackPartsNldx = PARTS_NUM_PUNCH_FINISH;
		}

		break;

	case CCommand::COMMAND_TYPE_KICK_NOR:

		m_pAttack = CFinishKick::Create();

		if (m_pAttack != nullptr)
		{
			// モーションの設定（パンチフィニッシュ）
			m_data.motionState = MOTION_STATE_KICK_FINISH;

			// パーツ位置
			m_data.nAttackPartsNldx = PARTS_NUM_KICK_FINISH;
		}

		break;
	}

	if (m_pAttack != nullptr)
	{
		// パーツの位置
		D3DXVECTOR3 posParts = D3DXVECTOR3(
			GetModel(m_data.nAttackPartsNldx)->GetMtxWorld()._41,
			GetModel(m_data.nAttackPartsNldx)->GetMtxWorld()._42,
			GetModel(m_data.nAttackPartsNldx)->GetMtxWorld()._43);

		// 攻撃の初期設定処理
		m_pAttack->InitSet(
			posParts,
			FINISH_SIZE[infoFinish.type],
			10,
			CMgrColl::TAG_ENEMY);

		// 追加の位置設定
		m_pAttack->SetPosPlus(FINISH_POS_PLUS[infoFinish.type]);
	}
}

//-------------------------------------
//- プレイヤーのデバック表示
//-------------------------------------
void CPlayer::DebugPlayer(void)
{
	// デバックプロックの取得
	CDebugProc *pDebugProc = CManager::GetInstance()->GetDbugProc();

	// デバックプロック取得の有無を判定
	if (pDebugProc == NULL)
	{
		return;
	}

	pDebugProc->Print("\n");
	pDebugProc->Print("プレイヤーの状態");
	pDebugProc->Print("\n");
	pDebugProc->Print("%d", m_data.state);
	pDebugProc->Print("\n");
}