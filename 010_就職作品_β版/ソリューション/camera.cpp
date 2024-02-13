
//================================================
//=
//= カメラの処理[camera.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "camera.h"

#include "main.h"

#include "renderer.h"
#include "manager.h"
#include "game.h"

#include "helper_sakai.h"

#include "input.h"
#include "xinput.h"

#include "player.h"

//=======================================
//=	コンスト定義
//=======================================

const D3DXVECTOR3 FOLL_POS_V = (D3DXVECTOR3(0.0f, 400.0f, 0.0f));		// 追尾状態の初期視点
const D3DXVECTOR3 FOLL_POS_R = (D3DXVECTOR3(0.0f, 200.0f, 0.0f));		// 追尾状態の初期注視点
const float FOLL_LENGTH = (600.0f);										// 追尾状態の視点と注視点の距離
const float FOLL_POS_DEST_SPEED = (0.3f);								// 追尾状態の位置補正速度

//=======================================
//=	マクロ定義
//=======================================

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	カメラのコンストラクタ
//-------------------------------------
CCamera::CCamera()
{
	ZeroMemory(&m_data, sizeof(m_data));
	ZeroMemory(m_mtxProjectien, sizeof(D3DXMATRIX));
	ZeroMemory(m_mtxView, sizeof(D3DXMATRIX));

	m_mode = MODE(0);
}

//-------------------------------------
//-	カメラのデストラクタ
//-------------------------------------
CCamera::~CCamera()
{
}

//-------------------------------------
//-	カメラの初期化処理
//-------------------------------------
HRESULT CCamera::Init(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 posV = m_data.posV;		// 視点
	D3DXVECTOR3 posR = m_data.posR;		// 注視点
	D3DXVECTOR3 vecU = m_data.vecU;		// 上方向のベクトル
	D3DXVECTOR3 rot = m_data.rot;		// 向き
	float fLength = m_data.fLength;		// カメラとの長さ
	
	m_bIsUpdateStop = false;

	// グローバル変数の初期化
	{
		// 情報設定
		posV = FOLL_POS_V;						// 視点
		posR = FOLL_POS_R;						// 注視点
		vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// 上方向のベクトル
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
		fLength = FOLL_LENGTH;					// カメラとの長さ

		// 情報更新
		m_data.posV = posV;			// 視点
		m_data.posVDest = posV;		// 目的の視点
		m_data.posR = posR;			// 注視点
		m_data.posRDest = posR;		// 目的の注視点
		m_data.vecU = vecU;			// 上方向のベクトル
		m_data.rot = rot;			// 向き
		m_data.rotDest = rot;		// 目的の向き
		m_data.fLength = fLength;	// カメラとの長さ
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//-	カメラの終了処理
//-------------------------------------
void CCamera::Uninit(void)
{

}

//-------------------------------------
//-	カメラの更新処理
//-------------------------------------
void CCamera::Update(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

		// 更新処理を抜ける
		return;
	}

	if (CManager::GetInstance()->GetMode() == CScene::MODE_GAME)
	{
		// プレイヤーカメラ処理
		CameraPlayer();

		// 向きの更新処理
		UpdateRot();
	}
	else if (CManager::GetInstance()->GetMode() == CScene::MODE_TITEL)
	{
		// タイトルの更新処理
		UpdateTitle();
	}
}

//-------------------------------------
//-	カメラの設定処理
//-------------------------------------
void CCamera::SetCamera(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 posV = m_data.posV;		// 視点
	D3DXVECTOR3 posR = m_data.posR;		// 注視点
	D3DXVECTOR3 vecU = m_data.vecU;		// 上方向のベクトル

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// デバイスの情報取得の成功を判定
	if (pDevice == NULL)
	{// 失敗時

		// 初期化処理を抜ける
		return;
	}

	// 変数宣言
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	// プロジェションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjectien);

	// プロジェションマトリックスを生成（基本カメラ）
	D3DXMatrixPerspectiveFovLH(
		&m_mtxProjectien,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH /
		(float)SCREEN_HEIGHT,
		10.0f,
		40000.0f);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(
		D3DTS_PROJECTION,
		&m_mtxProjectien);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);
		
	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(
		&m_mtxView,
		&posV,		// 視点
		&posR,		// 注視点
		&vecU);		// 上方向ベクトル

	//ビューマトリックスの設定
	pDevice->SetTransform(
		D3DTS_VIEW,
		&m_mtxView);
	
	// 情報更新
	m_data.posV = posV;			// 視点
	m_data.posR = posR;			// 注視点
	m_data.vecU = vecU;			// 上方向のベクトル
}

//-------------------------------------
//-	カメラの各モードの設定処理
//-------------------------------------
void CCamera::SetMode(CCamera::MODE mode)
{
	// モードの設定
	m_mode = mode;

	// 変数宣言（情報取得）
	D3DXVECTOR3 posV = m_data.posV;		// 視点
	D3DXVECTOR3 posR = m_data.posR;		// 注視点
	D3DXVECTOR3 vecU = m_data.vecU;		// 上方向のベクトル
	D3DXVECTOR3 rot = m_data.rot;		// 向き
	float fLength = m_data.fLength;		// カメラとの長さ

	switch (m_mode)
	{
	case MODE_NORMAL:

		// 情報設定
		posV = D3DXVECTOR3(0.0f, 1250.0f, -500.0f);		// 視点
		posR = D3DXVECTOR3(0.0f, 0.0f, 500.0f);			// 注視点
		fLength = 1250.0f;								// カメラとの長さ
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向き

		break;

	case MODE_FOLLOWING:

		// 情報設定
		posV = FOLL_POS_V;						// 視点
		posR = FOLL_POS_R;						// 注視点
		vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// 上方向のベクトル
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
		fLength = FOLL_LENGTH;					// カメラとの長さ

		break;
		
	case MODE_TITLE:

		// 情報設定
		posV = D3DXVECTOR3(0.0f, 100.0f, 0.0f);			// 視点
		posR = D3DXVECTOR3(400.0f, 100.0f, 0.0f);		// 注視点
		fLength = 800.0f;								// カメラとの長さ
		rot = D3DXVECTOR3(0.0f, 0.9f, 0.0f);			// 向き

		break;
	}

	// 情報更新
	m_data.posV = posV;			// 視点
	m_data.posVDest = posV;		// 目的の視点
	m_data.posR = posR;			// 注視点
	m_data.posRDest = posR;		// 目的の注視点
	m_data.vecU = vecU;			// 上方向のベクトル
	m_data.rot = rot;			// 向き
	m_data.rotDest = rot;		// 目的の向き
	m_data.fLength = fLength;	// カメラとの長さ
}

//-------------------------------------
//-	カメラの向き追尾処理
//-------------------------------------
void CCamera::UpdateRot(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 rot = m_data.rot;				// 向き
	D3DXVECTOR3 rotDest = m_data.rotDest;		// 目的の向き

	// 角度の正規化
	HelperSakai::NormalizeAngle(&rot, &rotDest, 0.2f);

	// 情報更新
	m_data.rot = rot;			// 向き
	m_data.rotDest = rotDest;	// 目的の向き
}

//-------------------------------------
//-	タイトルカメラの更新処理
//-------------------------------------
void CCamera::UpdateTitle(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 posV = m_data.posV;				// 視点
	D3DXVECTOR3 posVDest = m_data.posVDest;		// 目的の視点
	D3DXVECTOR3 posR = m_data.posR;				// 注視点
	D3DXVECTOR3 posRDest = m_data.posRDest;		// 目的の注視点
	D3DXVECTOR3 rot = m_data.rot;				// 向き
	D3DXVECTOR3 rotDest = m_data.rotDest;		// 目的の向き
	float fLength = m_data.fLength;				// カメラとの距離

	//視点の位置を更新
	posV.x = posR.x + sinf(rot.y) * -fLength;
	posV.z = posR.z + cosf(rot.y) * -fLength;

	//目的の視点の位置
	posVDest.x = 0.0f + (sinf(rot.y) * -fLength) + 0.0f;
	posVDest.z = 0.0f + (cosf(rot.y) * -fLength) + 0.0f;

	//目的の注視点の位置
	posRDest.x = 400.0f + 0.0f;
	posRDest.z = 0.0f + 0.0f;

	//視点の補正
	posV.x += (posVDest.x - posV.x) * 0.3f;
	posV.z += (posVDest.z - posV.z) * 0.3f;

	//注視点の補正
	posR.x += (posRDest.x - posR.x) * 0.3f;
	posR.z += (posRDest.z - posR.z) * 0.3f;

	//角度の補正
	rot.y += (rotDest.y - rot.y) * 0.3f;

	// 情報更新
	m_data.posV = posV;			// 視点
	m_data.posVDest = posV;		// 目的の視点
	m_data.posR = posR;			// 注視点
	m_data.posRDest = posR;		// 目的の注視点
	m_data.rot = rot;			// 向き
	m_data.rotDest = rot;		// 目的の向き
	m_data.fLength = fLength;	// カメラとの長さ
}

//-------------------------------------
//-	プレイヤーのカメラ処理
//-------------------------------------
void CCamera::CameraPlayer(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

	 // 更新処理を抜ける
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

	if (pInputKeyboard->GetPress(DIK_A) == true ||
		pXInput->GetPress(CXInput::TYPE_STICK_LEFT, CXInput::TYPE_INPUT_STICK_L) == true ||
		pXInput->GetPress(CXInput::TYPE_STICK_LEFT, CXInput::TYPE_INPUT_STICK_R) == true)
	{//[Eキーが押されたとき]

		m_data.rotDest.y -= 0.02f;
	}
	else if (
		pInputKeyboard->GetPress(DIK_D) == true ||
		pXInput->GetPress(CXInput::TYPE_STICK_RIGHT, CXInput::TYPE_INPUT_STICK_L) == true ||
		pXInput->GetPress(CXInput::TYPE_STICK_RIGHT, CXInput::TYPE_INPUT_STICK_R) == true)
	{
		m_data.rotDest.y += 0.02f;
	}

	if (pInputKeyboard->GetPress(DIK_Q) == true || 
		pXInput->GetPress(CXInput::TYPE_STICK_LEFT, CXInput::TYPE_INPUT_STICK_R) == true)
	{//[Eキーが押されたとき]

		m_data.rotDest.y -= 0.03f;
	}
	else if (pInputKeyboard->GetPress(DIK_E) == true ||
			 pXInput->GetPress(CXInput::TYPE_STICK_RIGHT, CXInput::TYPE_INPUT_STICK_R) == true)
	{
		m_data.rotDest.y += 0.03f;
	}

	// プレイヤーの情報取得
	CPlayer* pPlayer = CGame::GetPlayer();

	// プレイヤーの情報取得の成功を判定
	if (pPlayer == NULL)
	{// 失敗時

		// 追尾処理を抜ける
		return;
	}

	CPlayer::Data data = pPlayer->GetData();

	//注視点とプレイヤーの距離
	D3DXVECTOR3 cameraPlayer = D3DXVECTOR3(
		sinf(data.rot.y),
		30.0f,
		cosf(data.rot.y));

	//視点の位置を更新
	m_data.posV.x = m_data.posR.x + sinf(m_data.rot.y) * -m_data.fLength;
	m_data.posV.z = m_data.posR.z + cosf(m_data.rot.y) * -m_data.fLength;

	//目的の視点の位置
	m_data.posVDest.x = data.pos.x + (sinf(m_data.rot.y) * -m_data.fLength) + cameraPlayer.x;
	m_data.posVDest.z = data.pos.z + (cosf(m_data.rot.y) * -m_data.fLength) + cameraPlayer.z;

	//目的の注視点の位置
	m_data.posRDest.x = data.pos.x + cameraPlayer.x;
	m_data.posRDest.z = data.pos.z + cameraPlayer.z;

	//注視点の補正
	m_data.posR.x += (m_data.posRDest.x - m_data.posR.x) * 0.05f;
	m_data.posR.z += (m_data.posRDest.z - m_data.posR.z) * 0.05f;
}