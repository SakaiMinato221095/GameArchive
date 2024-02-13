
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

#include "renderer.h"
#include "manager.h"
#include "manager_object.h"

#include "input.h"

#include "manager_time.h"

#include "debugproc.h"

//=======================================
//=	マクロ定義
//=======================================

#define CAMERA_MOVE_SPEED	(50.0f)	// カメラの移動速度

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	カメラのコンストラクタ
//-------------------------------------
CCamera::CCamera()
{
	ZeroMemory(m_mtxProjectien, sizeof(D3DXMATRIX));
	ZeroMemory(m_mtxView, sizeof(D3DXMATRIX));

	m_mode = MODE_NORMAL;
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
	// グローバル変数の初期化
	{
		m_dataPosV.Set(D3DXVECTOR3(-750.0f, 2000.0f, -800.0f));	// 視点
		m_dataPosVDest.Set(m_dataPosV.Get());					// 目的の視点

		m_dataPosR.Set(D3DXVECTOR3(-750.0f, 0.0f, -800.0f));	// 注視点
		m_dataPosRDest.Set(m_dataPosR.Get());					// 目的の注視点

		m_dataVecU.Set(D3DXVECTOR3(0.0f, 1.0f, 0.0f));			// 上方向のベクトル

		m_fDataLength.Set(2000.0f);								// カメラとの長さ

		m_dataRot.Set(D3DXVECTOR3(0.0f, 0.72f, 0.0f));			// 向き
		m_dataRotDest.Set(m_dataRot.Get());						// 目的の向き

		// 変数宣言（情報取得）
		D3DXVECTOR3 posR = m_dataPosR.Get();	// 視点
		D3DXVECTOR3 posV = m_dataPosV.Get();	// 注視点
		D3DXVECTOR3 rot = m_dataRot.Get();		// 向き
		float fLength = m_fDataLength.Get();	// カメラとの長さ

		//注視点の位置を更新
		posR.x = posV.x + sinf(rot.y) * fLength;
		posR.z = posV.z + cosf(rot.y) * fLength;

		// 情報更新
		m_dataPosR.Set(posR);		// 視点
		m_dataPosV.Set(posV);		// 注視点
		m_dataRot.Set(rot);			// 向き
		m_fDataLength.Set(fLength);	// カメラとの長さ
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
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

		// 更新処理を抜ける
		return;
	}

	if (pInputKeyboard->GetTrigger(DIK_F2) != NULL)
	{
		// モード設定処理
		SetMode();
	}

	// カメラのモード
	switch (m_mode)
	{
	case MODE_NORMAL:

		// カメラの移動処理
		UpdateOperation();

		break;

	case MODE_SHOP:

		// カメラの移動処理
		UpdateOperation();

		break;
	}
}

//-------------------------------------
//-	カメラの操作処理
//-------------------------------------
void CCamera::UpdateOperation(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 posV = m_dataPosV.Get();	// 視点
	D3DXVECTOR3 posR = m_dataPosR.Get();	// 注視点
	D3DXVECTOR3 rot = m_dataRot.Get();		// 向き
	float fLength = m_fDataLength.Get();	// カメラとの距離

	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

		// 更新処理を抜ける
		return;
	}

	// 時間管理の情報を取得
	CManagerTime *pManagerTime = CManager::GetManagerTime();

	// 時間管理取得の有無を判定
	if (pManagerTime == NULL)
	{
		// 処理を抜ける
		return;
	}

	//移動
	if (pInputKeyboard->GetPress(DIK_LEFT) == true)
	{//左の移動[Aキーが押されたとき]

		posV.x -= CAMERA_MOVE_SPEED;
		posR.x -= CAMERA_MOVE_SPEED;

	}
	if (pInputKeyboard->GetPress(DIK_RIGHT) == true)
	{//右の移動[Dキーが押されたとき]

		posV.x += CAMERA_MOVE_SPEED;
		posR.x += CAMERA_MOVE_SPEED;

	}
	if (pInputKeyboard->GetPress(DIK_UP) == true)
	{//右の移動[Wキーが押されたとき]

		posV.z += CAMERA_MOVE_SPEED;
		posR.z += CAMERA_MOVE_SPEED;

	}
	if (pInputKeyboard->GetPress(DIK_DOWN) == true)
	{//右の移動[Sキーが押されたとき]

		posV.z -= CAMERA_MOVE_SPEED;
		posR.z -= CAMERA_MOVE_SPEED;

	}

	//角度の修正
	if (rot.y > D3DX_PI)
	{
		rot.y = (-D3DX_PI);
	}
	else if (rot.y < -D3DX_PI)
	{
		rot.y = (D3DX_PI);
	}

	// 情報更新
	m_dataPosV.Set(posV);		// 視点
	m_dataPosR.Set(posR);		// 注視点
	m_dataRot.Set(rot);			// カメラの向き
	m_fDataLength.Set(fLength);	// カメラとの距離

}

//-------------------------------------
//-	カメラの設定処理
//-------------------------------------
void CCamera::SetCamera(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 posV = m_dataPosV.Get();	// 視点
	D3DXVECTOR3 posR = m_dataPosR.Get();	// 注視点
	D3DXVECTOR3 vecU = m_dataVecU.Get();	// 上方向のベクトル

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

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
		20000.0f);

	//// プロジェションマトリックスを生成（平行投影）
	//D3DXMatrixOrthoLH(
	//	&m_mtxProjectien,
	//	(float)SCREEN_WIDTH,
	//	(float)SCREEN_HEIGHT,
	//	10.0f,
	//	1000.0f);

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
	m_dataPosV.Set(posV);	// 視点
	m_dataPosR.Set(posR);	// 注視点
	m_dataVecU.Set(vecU);	// 上方向のベクトル
}

//-------------------------------------
//-	カメラの各モードの設定処理
//-------------------------------------
void CCamera::SetMode(void)
{
	// 種類を加算
	m_mode = (MODE)(m_mode + 1);

	if (m_mode == MODE_MAX)
	{
		// 種類を初期化
		m_mode = (MODE)(0);
	}

	switch (m_mode)
	{
	case MODE_NORMAL:

		m_dataPosV.Set(D3DXVECTOR3(-750.0f, 2000.0f, -800.0f));	// 視点
		m_dataPosR.Set(D3DXVECTOR3(-750.0f, 0.0f, -800.0f));	// 注視点
		m_fDataLength.Set(2000.0f);								// カメラとの長さ
		m_dataRot.Set(D3DXVECTOR3(0.0f, 0.72f, 0.0f));			// 向き

		break;

	case MODE_SHOP:

		m_dataPosV.Set(D3DXVECTOR3(0.0f, 1250.0f, -500.0f));	// 視点
		m_dataPosR.Set(D3DXVECTOR3(0.0f, 0.0f, 500.0f));		// 注視点
		m_fDataLength.Set(1250.0f);								// カメラとの長さ
		m_dataRot.Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f));			// 向き

		break;
	}

	// 変数宣言（情報取得）
	D3DXVECTOR3 posR = m_dataPosR.Get();	// 視点
	D3DXVECTOR3 posV = m_dataPosV.Get();	// 注視点
	D3DXVECTOR3 rot = m_dataRot.Get();		// 向き
	float fLength = m_fDataLength.Get();	// カメラとの長さ

	//注視点の位置を更新
	posR.x = posV.x + sinf(rot.y) * fLength;
	posR.z = posV.z + cosf(rot.y) * fLength;

	// 情報更新
	m_dataPosR.Set(posR);		// 視点
	m_dataPosV.Set(posV);		// 注視点
	m_dataRot.Set(rot);			// 向き
	m_fDataLength.Set(fLength);	// カメラとの長さ

	// 目的の情報の更新
	m_dataPosVDest.Set(m_dataPosV.Get());	// 目的の視点
	m_dataPosRDest.Set(m_dataPosR.Get());	// 目的の注視点
	m_dataRotDest.Set(m_dataRot.Get());		// 目的の向き
}