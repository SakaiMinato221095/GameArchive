
//-===============================================
//-
//-	購入フェーズシステム処理[sys_game_shop.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "sys_phase_shop.h"

#include "game.h"
#include "manager_object.h"
#include "mgr_sys_obj.h"
#include "timer.h"

#include "Input.h"

#include "camera.h"

#include "player_shop.h"

#include "file_item.h"

#include "ui_mission.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	静的変数宣言
//-======================================

CPlayer *CSysPhaseShop::m_pPlayerShop = NULL;
CManagerObject *CSysPhaseShop::m_pManagerObject = NULL;
CUiMission *CSysPhaseShop::m_pUiMission = NULL;

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CSysPhaseShop::CSysPhaseShop()
{

}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CSysPhaseShop::~CSysPhaseShop()
{

}

//-------------------------------------
//- 購入フェーズの初期化処理
//-------------------------------------
HRESULT CSysPhaseShop::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// システムオブジェクト管理の取得処理
	CMgrSysObj *pMgrSysObj = CGame::GetMgrSysObj();

	//  システムオブジェクト管理の取得の有無を判定
	if (pMgrSysObj == NULL)
	{
		// 生成処理を抜ける
		return E_FAIL;
	}

	// 数値系の設定
	pMgrSysObj->SetNumber();

	// カメラの取得処理
	CCamera *pCamera = CManager::GetCamera();

	// カメラの取得成功の有無を判定
	if (pCamera == NULL)
	{
		// 生成処理を抜ける
		return E_FAIL;
	}

	// カメラを店視点に変更
	pCamera->SetMode(CCamera::MODE_SHOP);

	// 購入プレイヤーの初期化
	{
		// 購入プレイヤーの有無を判定
		if (m_pPlayerShop != NULL)
		{
			// 処理を抜ける
			return E_FAIL;
		}

		// 購入プレイヤーの生成
		m_pPlayerShop = CPlayerShop::Create(
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// 位置
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// 向き
			CObjectModel::MODEL_TYPE_PLAYER_SEARCH,		// モデル
			CMotion::MOTION_TYPE_PLAYER_SEARCH);		// モーション

		// 購入プレイヤーの初期化処理
		if (m_pPlayerShop == NULL)
		{// 失敗時

			// 失敗メッセージ
			MessageBox(hWnd, "購入プレイヤーの生成", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}
	}

	// オブジェクト管理の初期化
	{
		// オブジェクト管理の有無を判定
		if (m_pManagerObject == NULL)
		{
			// オブジェクト管理の生成
			m_pManagerObject = DBG_NEW CManagerObject;

			// オブジェクト管理の初期化処理
			if (FAILED(m_pManagerObject->Init(hInstance, hWnd, bWindow)))
			{// 失敗時

				// 失敗メッセージ
				MessageBox(hWnd, "オブジェクト管理の生成", "初期処理失敗！", MB_ICONWARNING);

				// 初期化を抜ける
				return E_FAIL;
			}
		}
		else
		{// ゴミが入っているとき

		 // 初期化を抜ける
			return E_FAIL;
		}
	}

	// 目的UIの設定処理
	{
		// 目的UIの有無を判定
		if (m_pUiMission == NULL)
		{
			// 目的UIの生成
			m_pUiMission = CUiMission::Create(CUiMission::TEX_SHOP);

			// 目的UIの初期化処理
			if (m_pUiMission == NULL)
			{// 失敗時

			 // 失敗メッセージ
				MessageBox(hWnd, "目的UIの初期化", "初期処理失敗！", MB_ICONWARNING);

				// 初期化を抜ける
				return E_FAIL;
			}
		}
		else
		{// ゴミが入っているとき

		 // 失敗メッセージ
			MessageBox(hWnd, "目的UIの初期化", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}
	}

	// アイテム読み込み設定処理
	CFileItem::Load(CFileItem::TXT_NORMAL_000);

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 購入フェーズの終了処理
//-------------------------------------
void CSysPhaseShop::Uninit(void)
{
	// システムオブジェクト管理の取得処理
	CMgrSysObj *pMgrSysObj = CGame::GetMgrSysObj();

	//  システムオブジェクト管理の取得の有無を判定
	if (pMgrSysObj != NULL)
	{
		// 数字のポインタ初期化処理
		pMgrSysObj->NullAllNumber();
	}

	// 購入プレイヤーの有無を判定
	if (m_pPlayerShop != NULL)
	{
		// 購入プレイヤーの終了処理
		m_pPlayerShop->Uninit();

		// 購入プレイヤーのポインタ初期化処理
		m_pPlayerShop = NULL;
	}

	// オブジェクト管理の有無を判定
	if (m_pManagerObject != NULL)
	{
		// オブジェクトの終了
		m_pManagerObject->Uninit();

		// オブジェクト管理の開放処理
		delete m_pManagerObject;
		m_pManagerObject = NULL;
	}

	// 目的UIの有無を判定
	if (m_pUiMission != NULL)
	{
		// 目的UIの終了処理
		m_pUiMission->Uninit();

		// 目的UIのポインタの初期
		m_pUiMission = NULL;
	}

	// オブジェクトの全開放処理
	CObject::ReleaseAll();
}

//-------------------------------------
//- 購入フェーズの更新処理
//-------------------------------------
void CSysPhaseShop::Update(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

	 // 処理を抜ける
		return;
	}

#if _DEBUG
	//　入力の判定 if（Cキーのトリガー）
	if (pInputKeyboard->GetTrigger(DIK_C) != NULL)
	{
		CGame::SetPhase(TYPE::TYPE_BATTLE);
	}
#endif

}

//-------------------------------------
//- 購入フェーズの描画処理
//-------------------------------------
void CSysPhaseShop::Draw(void)
{

}

//-------------------------------------
//-	購入プレイヤーの情報を取得
//-------------------------------------
CPlayer *CSysPhaseShop::GetPlayer(void)
{
	// 探索プレイヤーの情報を返す
	return m_pPlayerShop;
}

//-------------------------------------
//- 購入フェーズのオブジェクト管理の取得処理
//-------------------------------------
CManagerObject * CSysPhaseShop::GetManagerObject(void)
{
	return m_pManagerObject;
}