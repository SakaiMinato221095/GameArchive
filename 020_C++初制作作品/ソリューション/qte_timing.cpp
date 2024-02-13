
//-===============================================
//-
//-	クイックタイムイベント（タイミング）処理[qte_timing.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "qte_timing.h"

#include "renderer.h"
#include "manager.h"

#include "Input.h"
#include "xinput.h"

#include "obj_2d_none.h"
#include "obj_2d_gage.h"

#include "main.h"

#include "particle.h"

#include "sys_phase_search.h"

//-======================================
//-	マクロ定義
//-======================================

#define GAGE_RANGE_MAX	(50)	// ゲージの長さの最大

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	クイックタイムイベント（タイミング）のコンストラクタ
//-------------------------------------
CQteTiming::CQteTiming()
{
	// 値のクリア
	m_pObj2dNone = NULL;
	m_pObj2dGageTarget = NULL;
	m_pObj2dGagePlayer = NULL;
}

//-------------------------------------
//-	クイックタイムイベント（タイミング）のデストラクタ
//-------------------------------------
CQteTiming::~CQteTiming()
{

}

//-------------------------------------
//- クイックタイムイベント（タイミング）の初期化処理
//-------------------------------------
HRESULT CQteTiming::Init(void)
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
	if (m_pObj2dGageTarget == NULL)
	{
		if (FAILED(m_pObj2dGageTarget = CObj2dGage::Create(CObj2dGage::TEX_NULL)))
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
	if (m_pObj2dGagePlayer == NULL)
	{
		if (FAILED(m_pObj2dGagePlayer = CObj2dGage::Create(CObj2dGage::TEX_NULL)))
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
	
	float fRotData = (float)((rand() % 3000) - 1000) * 0.1f;	// 向き

	// 設定処理
	m_pObj2dNone->Set(pos, size);

	// 目的ゲージの設定
	m_pObj2dGageTarget->Set(
		D3DXVECTOR3(pos.x + fRotData, pos.y, pos.z),
		size,
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
		CObj2dGage::TYPE_CENTER);

	// プレイヤーゲージの設定
	m_pObj2dGagePlayer->Set(
		D3DXVECTOR3(pos.x - size.x,pos.y,pos.z),
		 size,
		D3DXCOLOR(1.0f, 0.95f, 0.0f, 1.0f),
		CObj2dGage::TYPE_CENTER);

	// ゲージの更新処理
	UpdateGage();

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- クイックタイムイベント（タイミング）の終了処理
//-------------------------------------
void CQteTiming::Uninit(void)
{
	// 通常2Dオブジェクトの有無を判定
	if (m_pObj2dNone != NULL)
	{
		// 通常2Dオブジェクトのポインタ初期化処理
		m_pObj2dNone->Uninit();
		m_pObj2dNone = NULL;
	}

	// ゲージの有無を判定
	if (m_pObj2dGageTarget != NULL)
	{
		// ゲージのポインタ初期化処理
		m_pObj2dGageTarget->Uninit();
		m_pObj2dGageTarget = NULL;
	}

	// ゲージの有無を判定
	if (m_pObj2dGagePlayer != NULL)
	{
		// ゲージのポインタ初期化処理
		m_pObj2dGagePlayer->Uninit();
		m_pObj2dGagePlayer = NULL;
	}
}

//-------------------------------------
//- クイックタイムイベント（タイミング）の更新処理
//-------------------------------------
void CQteTiming::Update(void)
{
	// キーボードの情報取得処理
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

	 // 処理を抜ける
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

	// ゲージの更新処理
	UpdateGage();

	// 変数宣言（情報取得）
	bool bMove = m_bDataGageMoveDirect.Get();							// 移動方向

	if (bMove == true)
	{
		// 加算処理
		AddGage();
	}
	else
	{
		// 終了処理
		CSysPhaseSearch::ReleaseQte();

		return;
	}

	// 入力の判定
	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true ||
		pXInput->GetTrigger(XINPUT_GAMEPAD_A, CXInput::TYPE_INPUT_BUTTON))
	{// SPACEキー

		// 判定処理
		Decision();

		return;
	}

}

//-------------------------------------
//- クイックタイムイベント（タイミング）の描画処理
//-------------------------------------
void CQteTiming::Draw(void)
{

}

//-------------------------------------
//- クイックタイムイベント（タイミング）の生成処理
//-------------------------------------
CQteTiming *CQteTiming::Create(void)
{
	// クイックタイムイベント（タイミング）の生成
	CQteTiming *pLife = DBG_NEW CQteTiming;

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

	// クイックタイムイベント（タイミング）のポインタを返す
	return pLife;
}

//-------------------------------------
//- クイックタイムイベント（タイミング）の初期設定処理
//-------------------------------------
void CQteTiming::InitSet(void)
{
	m_dataPos.Set(D3DXVECTOR3(
		SCREEN_WIDTH * 0.5f,
		SCREEN_HEIGHT * 0.85f,
		0.0f));

	m_dataSize.Set(D3DXVECTOR3(
		250.0f,
		50.0f,
		0.0f));

	m_nDataGageTarget.Set(10);
	m_nDataGagePlayer.Set(2);

	m_bDataGageMoveDirect.Set(true);
}

//-------------------------------------
//- クイックタイムイベント（タイミング）のゲージ表示
//-------------------------------------
void CQteTiming::UpdateGage(void)
{
	// 変数宣言（情報更新）
	D3DXVECTOR3 size = m_dataSize.Get();
	int nGageTarget = m_nDataGageTarget.Get();
	int nGagePlayer = m_nDataGagePlayer.Get();
	D3DXVECTOR3 gageTarget = m_pObj2dGageTarget->m_dataGage.Get();	// 目的のゲージ
	D3DXVECTOR3 gagePlayer = m_pObj2dGagePlayer->m_dataGage.Get();	// プレイヤーのゲージ

	// ゲージの消費量を計算
	gageTarget.x = ((1.0f / GAGE_RANGE_MAX) * (GAGE_RANGE_MAX - nGageTarget)) * size.x;
	gagePlayer.x = ((1.0f / GAGE_RANGE_MAX) * (GAGE_RANGE_MAX - nGagePlayer)) * size.x;

	// 情報更新
	m_pObj2dGageTarget->m_dataGage.Set(gageTarget);	// 目的のゲージ
	m_pObj2dGagePlayer->m_dataGage.Set(gagePlayer);	// プレイヤーのゲージ
}

//-------------------------------------
//- クイックタイムイベント（タイミング）の加算
//-------------------------------------
void CQteTiming::AddGage(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 posGagePlayer = m_pObj2dGagePlayer->m_dataPos.Get();	// プレイヤーゲージの位置
	bool bMove = m_bDataGageMoveDirect.Get();							// 移動方向
	D3DXVECTOR3 pos = m_dataPos.Get();									// 位置
	D3DXVECTOR3 size = m_dataSize.Get();								// サイズ

	// プレイヤーゲージの位置を加算
	posGagePlayer.x += 5.0f;

	if (posGagePlayer.x == pos.x + size.x)
	{
		// 移動方向を減算に
		bMove = false;
	}

	// 情報更新
	m_pObj2dGagePlayer->m_dataPos.Set(posGagePlayer);	// プレイヤーゲージの位置
	m_bDataGageMoveDirect.Set(bMove);					// 移動方向
}

//-------------------------------------
//- クイックタイムイベント（タイミング）の減算
//-------------------------------------
void CQteTiming::SubGage(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 posGagePlayer = m_pObj2dGagePlayer->m_dataPos.Get();	// プレイヤーゲージの位置
	bool bMove = m_bDataGageMoveDirect.Get();							// 移動方向
	D3DXVECTOR3 pos = m_dataPos.Get();									// 位置
	D3DXVECTOR3 size = m_dataSize.Get();								// サイズ

	// プレイヤーゲージの位置を減算
	posGagePlayer.x -= 5.0f;

	if (posGagePlayer.x == pos.x - size.x)
	{
		// 移動方向を加算に
		bMove = true;
	}

	// 情報更新
	m_pObj2dGagePlayer->m_dataPos.Set(posGagePlayer);	// プレイヤーゲージの位置
	m_bDataGageMoveDirect.Set(bMove);					// 移動方向

}

//-------------------------------------
//- クイックタイムイベント（タイミング）の判定処理
//-------------------------------------
void CQteTiming::Decision(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 posGagePlayer = m_pObj2dGagePlayer->m_dataPos.Get();	// プレイヤーゲージの位置
	D3DXVECTOR3 posGageTarget = m_pObj2dGageTarget->m_dataPos.Get();	// 目的ゲージの位置
	D3DXVECTOR3 gageTarget = m_pObj2dGageTarget->m_dataGage.Get();		// 目的ゲージ
	D3DXVECTOR3 size = m_dataSize.Get();

	if (posGagePlayer.x <= posGageTarget.x + size.x - gageTarget.x &&
		posGagePlayer.x >= posGageTarget.x - size.x + gageTarget.x)
	{
		// 終了処理
		CSysPhaseSearch::ReleaseQte();
		
		return;
	}
}