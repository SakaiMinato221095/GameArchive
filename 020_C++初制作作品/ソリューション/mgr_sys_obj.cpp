
//-===============================================
//-
//-	システムオブジェクト管理処理[mgr_sys_obj.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "mgr_sys_obj.h"

#include "main.h"

#include "timer.h"

#include "score.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	静的変数宣言
//-======================================

CTimer *CMgrSysObj::m_pTimer = NULL;
CScore *CMgrSysObj::m_pScore = NULL;

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CMgrSysObj::CMgrSysObj()
{
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CMgrSysObj::~CMgrSysObj()
{

}

//-------------------------------------
//- システムオブジェクト管理の初期化処理
//-------------------------------------
HRESULT CMgrSysObj::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// 時間の生成処理
	{
		// 時間の生成
		m_pTimer = CTimer::Create();

		// 時間の生成成功の有無を判定
		if (m_pTimer == NULL)
		{// 失敗時

			// 失敗メッセージ
			MessageBox(hWnd, "時間の生成", "初期処理失敗！", MB_ICONWARNING);

			// 初期化処理を抜ける
			return E_FAIL;
		}

		// 時間の設定処理
		{
			m_pTimer->SetPos(
				D3DXVECTOR3(SCREEN_WIDTH * 0.05f, SCREEN_HEIGHT * 0.10f, 0.0f),
				D3DXVECTOR3(60.0f, 0.0f, 0.0f),
				D3DXVECTOR3(60.0f, 0.0f, 0.0f));

			m_pTimer->SetSize(
				D3DXVECTOR3(40.0f, 50.0f, 0.0f));
		}
	}

	// スコアの生成処理
	{
		// スコアの生成
		m_pScore = CScore::Create();

		// スコアの生成成功の有無を判定
		if (m_pScore == NULL)
		{// 失敗時

		 // 失敗メッセージ
			MessageBox(hWnd, "スコアの生成", "初期処理失敗！", MB_ICONWARNING);

			// 初期化処理を抜ける
			return E_FAIL;
		}

		// スコアの設定処理
		{
			m_pScore->SetPosition(
				D3DXVECTOR3(SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.05f, 0.0f),
				D3DXVECTOR3(40.0f, 0.0f, 0.0f));

			m_pScore->SetSize(
				D3DXVECTOR3(25.0f, 25.0f, 0.0f));
		}
	}



	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- システムオブジェクト管理の終了処理
//-------------------------------------
void CMgrSysObj::Uninit(void)
{
	// 時間の破棄
	if (m_pTimer != NULL)
	{
		// 時間の終了処理
		m_pTimer->Uninit();

		// 時間の開放処理
		delete m_pTimer;
		m_pTimer = NULL;
	}

	// スコアの破棄
	if (m_pScore != NULL)
	{
		// スコアの終了処理
		m_pScore->Uninit();

		// スコアの開放処理
		delete m_pScore;
		m_pScore = NULL;
	}
}

//-------------------------------------
//- システムオブジェクト管理の更新処理
//-------------------------------------
void CMgrSysObj::Update(void)
{
	// 時間の有無を判定
	if (m_pTimer != NULL)
	{
		// 時間の更新処理
		m_pTimer->Update();
	}

	// スコアの有無を判定
	if (m_pScore != NULL)
	{
		// スコアの更新処理
		m_pScore->Update();
	}
}

//-------------------------------------
//- システムオブジェクト管理の描画処理
//-------------------------------------
void CMgrSysObj::Draw(void)
{
	// 時間の有無を判定
	if (m_pTimer != NULL)
	{
		// 時間の描画処理
		m_pTimer->Draw();
	}

	// スコアの有無を判定
	if (m_pScore != NULL)
	{
		// スコアの描画処理
		m_pScore->Draw();
	}
}

//-------------------------------------
//- システムオブジェクト管理の数字設定処理
//-------------------------------------
void CMgrSysObj::SetNumber(void)
{
	// 時間の設定
	m_pTimer->CreateNumber();		// 数字の生成
	m_pTimer->SetNumber();			// 数字設定処理

	// スコアの設定
	m_pScore->CreateNumber();		// 数字の生成
	m_pScore->SetNumber();			// 数字設定処理
}

//-------------------------------------
//- システムオブジェクト管理の数字ポインタ初期化処理
//-------------------------------------
void CMgrSysObj::NullAllNumber(void)
{
	// 時間の設定
	m_pTimer->NullAllNumber();		// 数字のポインタ初期化処理
	m_pScore->NullAllNumber();		// 数字のポインタ初期化処理
}

//-------------------------------------
//-	時間の情報を取得
//-------------------------------------
CTimer *CMgrSysObj::GetTimer(void)
{
	// 時間のポインタを返す
	return m_pTimer;
}

//-------------------------------------
//-	スコアの情報を取得
//-------------------------------------
CScore *CMgrSysObj::GetScore(void)
{
	// スコアのポインタを返す
	return m_pScore;
}