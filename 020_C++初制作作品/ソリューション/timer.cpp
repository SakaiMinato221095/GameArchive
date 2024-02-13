
//================================================
//=
//=	タイマー処理[timer.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "timer.h"

#include "renderer.h"
#include "game.h"

#include "manager_texture.h"

#include "time_stop.h"

#include "sys_game_phase.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//=	静的変数宣言
//=======================================

//-------------------------------------
//-	タイマーのコンストラクタ
//-------------------------------------
CTimer::CTimer()
{
	// 値のクリア
	for (int nCount = 0; nCount < TIMER_NUM_MAX; nCount++)
	{
		m_apNumber[nCount] = NULL;
	}
}

//-------------------------------------
//-	タイマーのデストラクタ
//-------------------------------------
CTimer::~CTimer()
{

}

//-------------------------------------
//- タイマーの初期化処理
//-------------------------------------
HRESULT CTimer::Init(void)
{
	// 数字の生成処理
	if (FAILED(CreateNumber()))
	{
		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- タイマーの終了処理
//-------------------------------------
void CTimer::Uninit(void)
{
	for (int nCount = 0; nCount < TIMER_NUM_MAX; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			// 数字の初期化
			m_apNumber[nCount] = NULL;
		}
	}
}

//-------------------------------------
//- タイマーの更新処理
//-------------------------------------
void CTimer::Update(void)
{
	// 加算処理
	Elapsed();

	for (int nCount = 0; nCount < TIMER_NUM_MAX; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			// 後回し描画のオン
			m_apNumber[nCount]->m_bDataAfterDraw.Set(true);
		}
	}

	// テクスチャの桁ごと設定処理
	NumberTex();
}

//-------------------------------------
//- タイマーの描画処理
//-------------------------------------
void CTimer::Draw(void)
{

}

//-------------------------------------
//- タイマーの生成処理
//-------------------------------------
CTimer *CTimer::Create(void)
{
	// タイマーの生成
	CTimer *pScore = DBG_NEW CTimer;;

	// 生成の成功の有無を判定
	if (pScore != NULL)
	{
		// 初期化処理
		if (FAILED(pScore->Init()))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pScore == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// パーティクルのポインタを返す
	return pScore;
}

//-------------------------------------
//- タイマーの数字生成処理
//-------------------------------------
HRESULT CTimer::CreateNumber(void)
{
	// タイマーの数字設定
	for (int nCount = 0; nCount < TIMER_NUM_MAX; nCount++)
	{
		if (m_apNumber[nCount] == NULL)
		{
			// 数字の生成処理
			m_apNumber[nCount] = CNumber::Create(CNumber::TEX_DARK_GREEN_001);

			// 数字の生成成功の有無を判定
			if (m_apNumber[nCount] == NULL)
			{
				// 「なし」を返す
				return E_FAIL;
			}
		}
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- タイマーの数字ポインタ初期化処理
//-------------------------------------
void CTimer::NullAllNumber(void)
{
	for (int nCount = 0; nCount < TIMER_NUM_MAX; nCount++)
	{
		// 数字の有無を判定
		if (m_apNumber[nCount] != NULL)
		{
			// 数字のポインタ初期化処理
			m_apNumber[nCount] = NULL;
		}
	}
}

//-------------------------------------
//-	タイマーの桁ごとテクスチャの設定処理
//-------------------------------------
void CTimer::NumberTex(void)
{
	// 変数宣言（情報取得）
	int nTime = m_nDataTime.Get();	// スコア

	// 変数宣言
	int aTexU[4];	// 各桁の数字を格納

	int nSeconds = (nTime % 60);
	int nMinutes = (nTime / 60);

	// 桁ごとの数値を代入
	aTexU[0] = ((nMinutes % 100) / 10);
	aTexU[1] = ((nMinutes % 10));
	aTexU[2] = ((nSeconds % 100) / 10);
	aTexU[3] =  (nSeconds % 10);

	for (int nCount = 0; nCount < TIMER_NUM_MAX; nCount++)
	{
		// タイマーの更新処理
		m_apNumber[nCount]->m_nDataDigits.Set(aTexU[nCount]);
	}

	// 情報更新
	m_nDataTime.Set(nTime);	// スコア
}

//-------------------------------------
//-	タイマーの時間経過処理
//-------------------------------------
void CTimer::Elapsed(void)
{
	// 時間停止の情報取得
	CTimeStop *pTimeStop = CManager::GetManagerTime();

	// 時間停止の情報取得の成功を判定
	if (pTimeStop == NULL)
	{// 失敗時

	 // 更新処理を抜ける
		return;
	}

	// 変数宣言（情報取得）
	int nTimeCount = m_nTimerCount.Get();	// カウンター
	int nTime = m_nDataTime.Get();			// 時間

	// 時間の有無を判定
	if (nTime > 0)
	{
		if (pTimeStop->m_bDataIntCount.Get() == true)
		{
			// カウンターを加算
			nTimeCount++;

			// カウンターの判定
			if (nTimeCount % 60 == 0)
			{// 60フレームに一回

				// 時間を加算
				nTime--;
			}
		}
	}

	// 情報更新
	m_nTimerCount.Set(nTimeCount);	// カウンター
	m_nDataTime.Set(nTime);			// 時間
}

//-------------------------------------
//- タイマーの位置情報の設定
//-------------------------------------
void CTimer::SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 interval, D3DXVECTOR3 between)
{
	// 情報代入
	m_dataPos.Set(pos);				// 位置
	m_dataInterval.Set(interval);	// 間隔
	m_dataBetween.Set(between);		// 区切りの間隔

	for (int nCount = 0; nCount < TIMER_NUM_MAX; nCount++)
	{
		if (nCount <= (TIMER_NUM_MAX / 2) - 1)
		{
			// 数字の有無を判定
			if (m_apNumber[nCount] != NULL)
			{
				// 数字の位置情報を代入
				m_apNumber[nCount]->GetObject2d()->m_dataPos.Set(D3DXVECTOR3(
					pos.x + (interval.x * nCount),
					pos.y + (interval.y * nCount),
					pos.z + (interval.z * nCount)));
			}
		}
		else
		{
			// 数字の有無を判定
			if (m_apNumber[nCount] != NULL)
			{
				// 数字の位置情報を代入
				m_apNumber[nCount]->GetObject2d()->m_dataPos.Set(D3DXVECTOR3(
					(pos.x + between.x) + (interval.x * nCount),
					(pos.y + between.y) + (interval.y * nCount),
					(pos.z + between.z) + (interval.z * nCount)));
			}
		}

	}
}

//-------------------------------------
//- タイマーのサイズの設定
//-------------------------------------
void CTimer::SetSize(D3DXVECTOR3 size)
{
	// 情報代入
	m_dataSize.Set(size);	// サイズ

	for (int nCount = 0; nCount < TIMER_NUM_MAX; nCount++)
	{
		// 数字の有無を判定
		if (m_apNumber[nCount] != NULL)
		{
			// 数字の位置情報を代入
			m_apNumber[nCount]->GetObject2d()->m_dataSize.Set(size);
		}
	}
}

//-------------------------------------
//- タイマーの数字の設定
//-------------------------------------
void CTimer::SetNumber(void)
{
	// 情報取得
	D3DXVECTOR3 pos = m_dataPos.Get();				// 位置
	D3DXVECTOR3 interval = m_dataInterval.Get();	// 間隔
	D3DXVECTOR3 between = m_dataBetween.Get();		// 区切りの間隔
	D3DXVECTOR3 size = m_dataSize.Get();			// サイズ

	for (int nCount = 0; nCount < TIMER_NUM_MAX; nCount++)
	{			
		// 数字の有無を判定
		if (m_apNumber[nCount] != NULL)
		{
			if (nCount <= (TIMER_NUM_MAX / 2) - 1)
			{
				// 数字の位置情報を代入
				m_apNumber[nCount]->GetObject2d()->m_dataPos.Set(D3DXVECTOR3(
					pos.x + (interval.x * nCount),
					pos.y + (interval.y * nCount),
					pos.z + (interval.z * nCount)));
			}
			else
			{
				// 数字の位置情報を代入
				m_apNumber[nCount]->GetObject2d()->m_dataPos.Set(D3DXVECTOR3(
					(pos.x + between.x) + (interval.x * nCount),
					(pos.y + between.y) + (interval.y * nCount),
					(pos.z + between.z) + (interval.z * nCount)));
			}
		}

		// 数字の位置情報を代入
		m_apNumber[nCount]->GetObject2d()->m_dataSize.Set(size);
	}
}

//-------------------------------------
//- タイマーの時間設定
//-------------------------------------
void CTimer::SetTime(int nTime)
{
	// 時間設定
	m_nDataTime.Set(nTime);

	// テクスチャの桁ごと設定処理
	NumberTex();
}