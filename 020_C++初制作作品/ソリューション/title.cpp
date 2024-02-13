
//================================================
//=
//=	タイトル画面処理[title.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "title.h"

#include "camera.h"

#include "fade.h"

#include "Input.h"
#include "xinput.h"
#include "sound.h"

#include "manager_object.h"
#include "obj_2d_none.h"

#include "file_obj_none.h"
#include "file_evt_obj.h"
#include "file_garbage.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//=	静的変数宣言
//=======================================

CManagerObject *CTitle::m_pManagerObject = {};
CObj2dNone *CTitle::m_apObj2dNone[CTitle::TYPE_NONE_2D_MAX] = {};

//-------------------------------------
//-	タイトルのコンストラクタ
//-------------------------------------
CTitle::CTitle()
{

}

//-------------------------------------
//-	タイトルのデストラクタ
//-------------------------------------
CTitle::~CTitle()
{

}

//-------------------------------------
//- タイトルの初期化処理
//-------------------------------------
HRESULT CTitle::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
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

	// オブジェクト管理の有無を判定
	if (m_apObj2dNone[TYPE_NONE_2D_LOGO] == NULL)
	{
		// オブジェクト管理の生成
		m_apObj2dNone[TYPE_NONE_2D_LOGO] = CObj2dNone::Create(CObj2dNone::TEX_TITLE_LOGO);

		// オブジェクト管理の初期化処理
		if (m_apObj2dNone[TYPE_NONE_2D_LOGO] == NULL)
		{// 失敗時

			// 失敗メッセージ
			MessageBox(hWnd, "効果なし2Dオブジェクトの生成", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}

		m_apObj2dNone[TYPE_NONE_2D_LOGO]->Set(
			D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.4f,0.0f),
			D3DXVECTOR3(400.0f,200.0f,0.0f));
	}
	else
	{// ゴミが入っているとき

		// 初期化を抜ける
		return E_FAIL;
	}

	// オブジェクト管理の有無を判定
	if (m_apObj2dNone[TYPE_NONE_2D_BUTTON] == NULL)
	{
		// オブジェクト管理の生成
		m_apObj2dNone[TYPE_NONE_2D_BUTTON] = CObj2dNone::Create(CObj2dNone::TEX_TITLE_BUTTON);

		// オブジェクト管理の初期化処理
		if (m_apObj2dNone[TYPE_NONE_2D_BUTTON] == NULL)
		{// 失敗時

			// 失敗メッセージ
			MessageBox(hWnd, "効果なし2Dオブジェクトの生成", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}

		m_apObj2dNone[TYPE_NONE_2D_BUTTON]->Set(
			D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.8f, 0.0f),
			D3DXVECTOR3(200.0f, 100.0f, 0.0f));
	}
	else
	{// ゴミが入っているとき

		// 初期化を抜ける
		return E_FAIL;
	}

	// 効果なしオブジェクト読み込み設定処理
	CFileObjNone::Load(CFileObjNone::TXT_NORMAL_000);

	// イベントオブジェクト読み込み設定処理
	CFileEvtObj::Load(CFileEvtObj::TXT_NORMAL_000);

	// カメラの設定処理
	CManager::GetCamera()->SetMode(CCamera::MODE_TITLE);

	// サウンドのポインタを宣言
	CSound *pSound = CManager::GetSound();

	// サウンドの情報取得の成功を判定
	if (pSound == NULL)
	{
		// 処理を抜ける
		return E_FAIL;
	}

	// 発射音SEの再生
	pSound->Play(CSound::LABEL_BGM_TITLE);

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- タイトルの終了処理
//-------------------------------------
void CTitle::Uninit(void)
{
	// オブジェクト管理の有無を判定
	if (m_pManagerObject != NULL)
	{
		// オブジェクトの終了
		m_pManagerObject->Uninit();

		// オブジェクト管理の開放処理
		delete m_pManagerObject;
		m_pManagerObject = NULL;
	}

	for (int nCount = 0; nCount < TYPE_NONE_2D_MAX; nCount++)
	{
		if (m_apObj2dNone[nCount] != NULL)
		{
			// 効果なし2Dオブジェクトの開放処理
			m_apObj2dNone[nCount]->Uninit();
			m_apObj2dNone[nCount] = NULL;
		}
	}

	// オブジェクトの全開放処理
	CObject::ReleaseAll();
}

//-------------------------------------
//- タイトルの更新処理
//-------------------------------------
void CTitle::Update(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

		// 更新処理を抜ける
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

	// 遷移ボタン（えんたー）
	if (pInputKeyboard->GetTrigger(DIK_RETURN) != NULL || 
		pXInput->GetTrigger(XINPUT_GAMEPAD_A,CXInput::TYPE_INPUT_BUTTON))
	{
		// ゲームモード
		CManager::GetFade()->SetFade(CScene::MODE_GAME);
	}
}

//-------------------------------------
//- タイトルの描画処理
//-------------------------------------
void CTitle::Draw(void)
{

}

//-------------------------------------
//-	オブジェクト管理の情報を取得
//-------------------------------------
CManagerObject * CTitle::GetManagerObject(void)
{
	return m_pManagerObject;
}

//-------------------------------------
//-	効果なし2dオブジェクトの情報を取得
//-------------------------------------
CObj2dNone * CTitle::GetObj2dNone(int nNum)
{
	return m_apObj2dNone[nNum];
}
