
//-===============================================
//-
//-	ゲームフェーズシステム処理[sys_game_phase.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "sys_game_phase.h"

#include "sys_phase_search.h"
#include "sys_phase_shop.h"
#include "sys_phase_battle.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	静的変数宣言
//-======================================

CSysGamePhase::TYPE CSysGamePhase::m_type = (CSysGamePhase::TYPE)0;
CSysGamePhase::TYPE CSysGamePhase::m_typeNext = (CSysGamePhase::TYPE)0;

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CSysGamePhase::CSysGamePhase()
{
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CSysGamePhase::~CSysGamePhase()
{

}

//-------------------------------------
//- ゲームフェーズ初期化処理
//-------------------------------------
HRESULT CSysGamePhase::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- ゲームフェーズ終了処理
//-------------------------------------
void CSysGamePhase::Uninit(void)
{

}

//-------------------------------------
//- ゲームフェーズ更新処理
//-------------------------------------
void CSysGamePhase::Update(void)
{

}

//-------------------------------------
//- ゲームフェーズ描画処理
//-------------------------------------
void CSysGamePhase::Draw(void)
{

}

//-------------------------------------
//- ゲームフェーズ生成処理
//-------------------------------------
CSysGamePhase *CSysGamePhase::Create(TYPE type, HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// 変数宣言
	CSysGamePhase *pSysGamePhase = NULL;

	// 指定されたモードの生成
	switch (type)
	{
	case TYPE::TYPE_SEARCH:

		pSysGamePhase = DBG_NEW CSysPhaseSearch;

		break;

	case TYPE::TYPE_SHOP:

		pSysGamePhase = DBG_NEW CSysPhaseShop;

		break;

	case TYPE::TYPE_BATTLE:

		pSysGamePhase = DBG_NEW CSysPhaseBattle;

		break;
	}

	// 生成の成功の有無を判定
	if (pSysGamePhase != NULL)
	{
		// モード設定処理
		pSysGamePhase->SetType(type);
		pSysGamePhase->SetTypeNext(type);

		// 初期化処理
		if (FAILED(pSysGamePhase->Init(hInstance, hWnd, bWindow)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pSysGamePhase == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// シーンの情報を返す
	return pSysGamePhase;

}

//-------------------------------------
//- ゲームフェーズの取得処理
//-------------------------------------
CPlayer *CSysGamePhase::GetPlayer(void)
{
	switch (m_type)
	{
	case TYPE_SEARCH:

		return CSysPhaseSearch::GetPlayer();

		break;

	case TYPE_SHOP:

		return CSysPhaseShop::GetPlayer();

		break;

	case TYPE_BATTLE:

		return CSysPhaseBattle::GetPlayer();

		break;
	}

	return NULL;
}

//-------------------------------------
//- ゲームフェーズの設定処理
//-------------------------------------
void CSysGamePhase::SetType(TYPE type)
{
	// モード代入
	m_type = type;
}

//-------------------------------------
//- ゲームフェーズの取得処理
//-------------------------------------
CSysGamePhase::TYPE CSysGamePhase::GetType(void)
{
	// モードを返す
	return m_type;
}

//-------------------------------------
//- 次のゲームフェーズの設定処理
//-------------------------------------
void CSysGamePhase::SetTypeNext(TYPE typeNext)
{
	// モード代入
	m_typeNext = typeNext;
}

//-------------------------------------
//- 次のゲームフェーズの取得処理
//-------------------------------------
CSysGamePhase::TYPE CSysGamePhase::GetTypeNext(void)
{
	// モードを返す
	return m_typeNext;
}