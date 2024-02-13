
//-===============================================
//-
//-	体力処理[life.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "life.h"

#include "renderer.h"
#include "manager.h"

#include "obj_2d_none.h"
#include "obj_2d_gage.h"

#include "main.h"

#include "game.h"
#include "state_game.h"

//-======================================
//-	マクロ定義
//-======================================

#define LIFE_MAX	(50)	// 体力の最大数

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	体力のコンストラクタ
//-------------------------------------
CLife::CLife()
{
	// 値のクリア
	m_pObj2dNone = NULL;
	m_pObj2dGage = NULL;
}

//-------------------------------------
//-	体力のデストラクタ
//-------------------------------------
CLife::~CLife()
{
	
}

//-------------------------------------
//- 体力の初期化処理
//-------------------------------------
HRESULT CLife::Init(void)
{
	// 初期設定
	InitSet();

	// 情報取得
	D3DXVECTOR3 pos = m_dataPos.Get();		// 位置
	D3DXVECTOR3 size = m_dataSize.Get();	// サイズ

	// 通常2Dオブジェクトの生成処理
	if (m_pObj2dNone == NULL)
	{
		if (FAILED(m_pObj2dNone = CObj2dNone::Create(CObj2dNone::TEX_NULL)))
		{
			// 失敗を返す
			return E_FAIL;
		}
	}
	else
	{
		// 失敗を返す
		return E_FAIL;
	}

	// ゲージの生成処理
	if (m_pObj2dGage == NULL)
	{
		if (FAILED(m_pObj2dGage = CObj2dGage::Create(CObj2dGage::TEX_NULL)))
		{
			// 失敗を返す
			return E_FAIL;
		}
	}
	else
	{
		// 失敗を返す
		return E_FAIL;
	}

	// 設定処理
	m_pObj2dNone->Set(pos,size);
	m_pObj2dGage->Set(pos, size,D3DXCOLOR(1.0f,0.0f,0.0f,1.0f),CObj2dGage::TYPE_LEFT);

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 体力の終了処理
//-------------------------------------
void CLife::Uninit(void)
{
	// 通常2Dオブジェクトの有無を判定
	if (m_pObj2dNone != NULL)
	{
		// 通常2Dオブジェクトのポインタ初期化処理
		m_pObj2dNone->Uninit();
		m_pObj2dNone = NULL;
	}

	// ゲージの有無を判定
	if (m_pObj2dGage != NULL)
	{
		// ゲージのポインタ初期化処理
		m_pObj2dGage->Uninit();
		m_pObj2dGage = NULL;
	}
}

//-------------------------------------
//- 体力の更新処理
//-------------------------------------
void CLife::Update(void)
{
	// ゲームステータスの情報を取得
	CStateGame *pStateGame = CGame::GetStateGame();

	// ゲームステータス取得の有無を判定
	if (pStateGame == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 変数宣言（情報取得）
	D3DXVECTOR3 gage = m_pObj2dGage->m_dataGage.Get();	// ゲージの位置
	D3DXVECTOR3 size = m_dataSize.Get();				// サイズ
	int nLife = m_nDataLife.Get();						// 体力の値

	// ゲージの消費量を計算
	gage.x = ((1.0f / LIFE_MAX) * ((LIFE_MAX - nLife) * 2)) * size.x;

	// 体力値の有無を判定
	if (nLife <= 0)
	{
		// ゲームの終了状態の設定
		pStateGame->SetEndState(CStateGame::END_STATE_DIED);
	}

	// 情報更新
	m_pObj2dGage->m_dataGage.Set(gage);	// ゲージの位置
}

//-------------------------------------
//- 体力の描画処理
//-------------------------------------
void CLife::Draw(void)
{

}

//-------------------------------------
//- 体力の生成処理
//-------------------------------------
CLife *CLife::Create(void)
{
	// 体力の生成
	CLife *pLife = DBG_NEW CLife;

	// 生成の成功の有無を判定
	if (pLife != NULL)
	{
		// 初期化処理
		if (FAILED(pLife->Init()))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pLife == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// 体力のポインタを返す
	return pLife;
}

//-------------------------------------
//- 体力の初期設定処理
//-------------------------------------
void CLife::InitSet(void)
{
	m_nDataLife.Set(LIFE_MAX);

	m_dataPos.Set(D3DXVECTOR3(
		SCREEN_WIDTH * 0.87f, 
		SCREEN_HEIGHT * 0.15f,
		0.0f));

	m_dataSize.Set(D3DXVECTOR3(
		150.0f, 
		25.0f, 
		0.0f));
}