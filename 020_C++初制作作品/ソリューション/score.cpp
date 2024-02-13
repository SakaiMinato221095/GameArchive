
//-===============================================
//-
//-	スコア処理[score.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "score.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	スコアのコンストラクタ
//-------------------------------------
CScore::CScore()
{
	// 値のクリア
	for (int nCount = 0; nCount < DIGITS_SCORE; nCount++)
	{
		m_apNumber[nCount] = NULL;
	}
}

//-------------------------------------
//-	スコアのデストラクタ
//-------------------------------------
CScore::~CScore()
{

}

//-------------------------------------
//- スコアの初期化処理
//-------------------------------------
HRESULT CScore::Init(void)
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
//- スコアの終了処理
//-------------------------------------
void CScore::Uninit(void)
{
	for (int nCount = 0; nCount < DIGITS_SCORE; nCount++)
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
//- スコアの更新処理
//-------------------------------------
void CScore::Update(void)
{
	for (int nCount = 0; nCount < DIGITS_SCORE; nCount++)
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
//- スコアの描画処理
//-------------------------------------
void CScore::Draw(void)
{

}

//-------------------------------------
//- スコアの生成処理
//-------------------------------------
CScore *CScore::Create(void)
{
	// スコアの生成
	CScore *pScore = DBG_NEW CScore;;

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
//- スコアの数字生成処理
//-------------------------------------
HRESULT CScore::CreateNumber(void)
{
	// タイマーの数字設定
	for (int nCount = 0; nCount < DIGITS_SCORE; nCount++)
	{
		if (m_apNumber[nCount] == NULL)
		{
			// 分数の数字生成処理
			m_apNumber[nCount] = CNumber::Create(CNumber::TEX_GOLD_000);

			// 分数の数字生成成功の有無を判定
			if (m_apNumber[nCount] == NULL)
			{
				// 処理を抜ける
				return E_FAIL;
			}
		}
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- スコアの数字ポインタ初期化処理
//-------------------------------------
void CScore::NullAllNumber(void)
{
	for (int nCount = 0; nCount < DIGITS_SCORE; nCount++)
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
//-	スコアの桁ごとテクスチャの設定処理
//-------------------------------------
void CScore::NumberTex(void)
{
	// 変数宣言（情報取得）
	int nScore = m_nDataScore.Get();	// スコア

	// 変数宣言
	int aTexU[DIGITS_SCORE];	//各桁の数字を格納

	//桁ごとの数値を代入
	aTexU[0] = ( nScore / 10000000);
	aTexU[1] = ((nScore % 10000000) / 1000000);
	aTexU[2] = ((nScore % 1000000) / 100000);
	aTexU[3] = ((nScore % 100000) / 10000);
	aTexU[4] = ((nScore % 10000) / 1000);
	aTexU[5] = ((nScore % 1000) / 100);
	aTexU[6] = ((nScore % 100) / 10);
	aTexU[7] = ( nScore % 10);

	for (int nCount = 0; nCount < DIGITS_SCORE; nCount++)
	{
		m_apNumber[nCount]->m_nDataDigits.Set(aTexU[nCount]);
	}

	// 情報更新
	m_nDataScore.Set(nScore);	// スコア
}

//-------------------------------------
//-	スコアの加算処理
//-------------------------------------
void CScore::Add(GET_TYPE getType, int nAddScore)
{
	// 変数宣言（情報取得）
	int nScore = m_nDataScore.Get();	// スコア

	// スコアの取得系統
	switch (getType)
	{
	case GET_TYPE_NORMAL:

		// スコアを加算
		nScore += nAddScore;

		break;

	case GET_TYPE_RANDOM:

		nScore += CalRandom(nAddScore);

		break;
	}

	// 情報更新
	m_nDataScore.Set(nScore);	// スコア
}

//-------------------------------------
//-	スコアのランダムの計算
//-------------------------------------
int CScore::CalRandom(int nAddScore)
{
	int nBaseValue = 30 + nAddScore;		// 基礎値の値
	int nRandMulti = (rand() % (5)) + 1;	// 倍数
	int nRandLuck = (rand() % (20));		// 強運の乱数を格納

	// 強運乱数が強運（0）のとき
	if (nRandLuck == 0)
	{
		// 基礎値に倍
		nBaseValue *= 2;
	}

	// 最終スコアを算出
	nAddScore = nBaseValue * nRandMulti;

	return nAddScore;
}

//-------------------------------------
//- スコアの位置情報の設定
//-------------------------------------
void CScore::SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 interval)
{
	// 情報代入
	m_dataPos.Set(pos);				// 位置
	m_dataInterval.Set(interval);	// 間隔

	for (int nCount = 0; nCount < DIGITS_SCORE; nCount++)
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
}

//-------------------------------------
//- スコアのサイズの設定
//-------------------------------------
void CScore::SetSize(D3DXVECTOR3 size)
{
	// 情報代入
	m_dataSize.Set(size);	// 大きさ

	for (int nCount = 0; nCount < DIGITS_SCORE; nCount++)
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
//- スコアの色情報の設定（基本色）
//-------------------------------------
void CScore::SetColor(void)
{
	for (int nCount = 0; nCount < DIGITS_SCORE; nCount++)
	{
		// 数字の有無を判定
		if (m_apNumber[nCount] != NULL)
		{
			// 数字の色情報を代入
			m_apNumber[nCount]->GetObject2d()->m_dataColor.Set();
		}
	}
}

//-------------------------------------
//- スコアの数字の設定
//-------------------------------------
void CScore::SetNumber(void)
{
	// 情報取得
	D3DXVECTOR3 pos = m_dataPos.Get();				// 位置
	D3DXVECTOR3 interval = m_dataInterval.Get();	// 間隔
	D3DXVECTOR3 size = m_dataSize.Get();			// サイズ

	for (int nCount = 0; nCount < DIGITS_SCORE; nCount++)
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

		// 数字の位置情報を代入
		m_apNumber[nCount]->GetObject2d()->m_dataSize.Set(size);
	}
}