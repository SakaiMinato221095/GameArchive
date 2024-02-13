
//-===============================================
//-
//-	時間管理処理[manager_time.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "manager_time.h"

#include "renderer.h"
#include "manager.h"

//-======================================
//-	マクロ定義
//-======================================

//-------------------------------------
//-	時間管理のコンストラクタ
//-------------------------------------
CManagerTime::CManagerTime()
{

}

//-------------------------------------
//-	時間管理のデストラクタ
//-------------------------------------
CManagerTime::~CManagerTime()
{

}

//-------------------------------------
//- 時間管理の初期化処理
//-------------------------------------
void CManagerTime::Init(void)
{
	m_fDataTimeRate.Set(1.0f);		// 時間倍率
	m_nDataTimeCount.Set(0);		// 時間カウント
	m_nDataTimeCountMax.Set(0);		// 時間カウントの最大値
	m_bDataIntCount.Set(true);	// 整数カウント条件の有無
}

//-------------------------------------
//- 時間管理の終了処理
//-------------------------------------
void CManagerTime::Uninit(void)
{

}

//-------------------------------------
//- 時間管理の更新処理
//-------------------------------------
void CManagerTime::Update(void)
{
	// 変数宣言（情報取得）
	float nTimeRate = m_fDataTimeRate.Get();		// 時間倍率
	int nTimeCount = m_nDataTimeCount.Get();		// 時間カウント
	int nTimeCountMax = m_nDataTimeCountMax.Get();	// 時間カウントの最大値
	bool bIntCount = m_bDataIntCount.Get();			// 整数のカウントの有無

	// 時間カウント前の判定計算
	float fCalTimeOld = ((1.0f * 0.5f) * nTimeCount);			// 時間カウント前の判定計算
	float fValueIntOld;											// 時間カウント前の判定計算の整数
	float fValueFloatOld = modff(fCalTimeOld, &fValueIntOld);	// 時間カウント前の判定計算の小数（整数と小数の分別）

	// 時間カウントの最大値がある
	if (nTimeCountMax != 0)
	{
		// 時間カウントを加算
		nTimeCount++;

		// 判定計算
		float fCalTime = ((1.0f * 0.5f) * nTimeCount);		// 判定計算
		float fValueInt;										// 判定計算の整数
		float fValueFloat = modff(fCalTime, &fValueInt);		// 判定計算の小数（整数と小数の分別）

		// 時間カウントの判定 if（整数のカウント条件）
		if (fValueInt == fValueIntOld)
		{
			// 整数カウントを設定
			bIntCount = true;
		}
		else
		{
			// 整数カウントを設定
			bIntCount = false;
		}

		// 時間カウントの判定 if（等倍化条件）
		if (nTimeCount == nTimeCountMax)
		{
			nTimeRate = 1.0f;
			nTimeCount = 0;
			nTimeCountMax = 0;
			bIntCount = true;
		}
	}

	// 情報更新
	m_fDataTimeRate.Set(nTimeRate);			// 時間倍率
	m_nDataTimeCount.Set(nTimeCount);		// 時間カウント
	m_nDataTimeCountMax.Set(nTimeCountMax);	// 時間カウントの最大値
	m_bDataIntCount.Set(bIntCount);			// 整数カウント条件の有無

}

//-------------------------------------
//- 時間管理の生成処理
//-------------------------------------
CManagerTime *CManagerTime::Create(void)
{
	// アイテムのポインタを宣言
	CManagerTime *pCManagerTime = new CManagerTime;

	// 生成の成功の有無を判定
	if (pCManagerTime != NULL)
	{
		// 初期化処理
		pCManagerTime->Init();
	}
	else if (pCManagerTime == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// アイテムのポインタを返す
	return pCManagerTime;
}

//-------------------------------------
//- 時間管理の計算処理（Float）
//-------------------------------------
float CManagerTime::CalRate(float data)
{
	// 変数宣言（情報取得）
	float nTimeRate = m_fDataTimeRate.Get();			// 時間倍率

	data *= nTimeRate;

	return data;
}

//-------------------------------------
//- 時間管理の計算処理（D3DXVECTOR3）
//-------------------------------------
D3DXVECTOR3 CManagerTime::CalRate(D3DXVECTOR3 data)
{
	// 変数宣言（情報取得）
	float nTimeRate = m_fDataTimeRate.Get();			// 時間倍率

	data.x *= nTimeRate;
	data.y *= nTimeRate;
	data.z *= nTimeRate;

	return data;
}

//-------------------------------------
//- 時間管理の設定処理
//-------------------------------------
void CManagerTime::Set(float fTimeRate, int nTimeMax)
{
	m_fDataTimeRate.Set(fTimeRate);		// 時間倍率
	m_nDataTimeCountMax.Set(nTimeMax);	// 時間カウントの最大値
}
