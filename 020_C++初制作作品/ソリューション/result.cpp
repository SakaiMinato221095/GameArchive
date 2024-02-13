
//================================================
//=
//=	リザルト画面処理[result.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "result.h"

#include "fade.h"

#include "Input.h"
#include "xinput.h"

#include "bg.h"

#include "manager.h"
#include "state_mode.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//=	静的変数宣言
//=======================================

CBg *CResult::m_apBg[BG_RESULT_NUM_MAX] = {};

//-------------------------------------
//-	リザルトのコンストラクタ
//-------------------------------------
CResult::CResult()
{

}

//-------------------------------------
//-	リザルトのデストラクタ
//-------------------------------------
CResult::~CResult()
{

}

//-------------------------------------
//- リザルトの初期化処理
//-------------------------------------
HRESULT CResult::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// モードステータスの情報取得
	CStateMode *pStateMode = CManager::GetStateMode();;

	// モードステータスの情報取得の成功を判定
	if (pStateMode == NULL)
	{// 失敗時

		// 更新処理を抜ける
		return E_FAIL;
	}

	// リザルト状態を取得
	CStateMode::RESULT_STATE resultState = pStateMode->GetResultState();

	// 背景の有無を判定
	if (m_apBg[0] == NULL)
	{
		switch (resultState)
		{
		case CStateMode::RESULT_STATE_WIN:

			// 背景の生成処理
			m_apBg[0] = CBg::Create(CBg::TEX_RESULT_WIN);

			break;

		case CStateMode::RESULT_STATE_END:

			// 背景の生成処理
			m_apBg[0] = CBg::Create(CBg::TEX_RESULT_END);

			break;

		case CStateMode::RESULT_STATE_LOOSE:

			// 背景の生成処理
			m_apBg[0] = CBg::Create(CBg::TEX_RESULT_LOOSE);

			break;
		}


		// 背景の有無を判定
		if (m_apBg[0] == NULL)
		{
			// 失敗を返す
			return E_FAIL;
		}

		// 背景の設定
		m_apBg[0]->Set();
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- リザルトの終了処理
//-------------------------------------
void CResult::Uninit(void)
{
	for (int nCount = 0; nCount < BG_RESULT_NUM_MAX; nCount++)
	{
		// 背景の有無を判定
		if (m_apBg[nCount] != NULL)
		{
			// 背景のポインタ初期化処理
			m_apBg[nCount] = NULL;
		}
	}

	// オブジェクトの全開放処理
	CObject::ReleaseAll();
}

//-------------------------------------
//- リザルトの更新処理
//-------------------------------------
void CResult::Update(void)
{
	// キーボードの情報取得
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
		pXInput->GetTrigger(XINPUT_GAMEPAD_A, CXInput::TYPE_INPUT_BUTTON))
	{
		// ゲームモード
		CManager::GetFade()->SetFade(CScene::MODE_TITEL);
	}

}

//-------------------------------------
//- リザルトの描画処理
//-------------------------------------
void CResult::Draw(void)
{

}
