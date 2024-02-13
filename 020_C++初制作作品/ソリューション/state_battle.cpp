
//-===============================================
//-
//-	戦闘ステータス処理[state_battle.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "state_battle.h"

#include "renderer.h"
#include "manager.h"

#include "debugproc.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	戦闘ステータスのコンストラクタ
//-------------------------------------
CStateBattle::CStateBattle()
{
	// 値をクリア
	m_subWeaponType = SUB_WEAPON_TYPE_BOMB;
	m_elemType = ELEM_TYPE_NORMAL;
}

//-------------------------------------
//-	戦闘ステータスのデストラクタ
//-------------------------------------
CStateBattle::~CStateBattle()
{

}

//-------------------------------------
//- 戦闘ステータスの初期化処理
//-------------------------------------
void CStateBattle::Init(void)
{
	// 情報の初期値設定
	m_bDataWeaponEarlyShot.Set(false);	// 早打ち装備の有無
	m_nDataShotInterval.Set(60);		// 弾の間隔

	m_elemType = ELEM_TYPE_NORMAL;
}

//-------------------------------------
//- 戦闘ステータスの終了処理
//-------------------------------------
void CStateBattle::Uninit(void)
{

}

//-------------------------------------
//- 戦闘ステータスの更新処理
//-------------------------------------
void CStateBattle::Update(void)
{
	// デバック表示
	Debug();
}

//-------------------------------------
//- 戦闘ステータスの生成処理
//-------------------------------------
CStateBattle *CStateBattle::Create(void)
{
	// アイテムのポインタを宣言
	CStateBattle *pCStateBattle = DBG_NEW CStateBattle;

	// 生成の成功の有無を判定
	if (pCStateBattle != NULL)
	{
		// 初期化処理
		pCStateBattle->Init();
	}
	else if (pCStateBattle == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// アイテムのポインタを返す
	return pCStateBattle;
}

//-------------------------------------
//- 戦闘ステータスの銅装備の設定
//-------------------------------------
void CStateBattle::SetWeaponCopper(bool bUse)
{
	// 装備の有無
	if (bUse == true)
	{
		m_bDataWeaponEarlyShot.Set(true);	// 早打ち装備を設定
		m_nDataShotInterval.Set(50);		// 弾の間隔
	}
	else if (bUse == false)
	{
		m_bDataWeaponEarlyShot.Set(false);	// 早打ち装備の設定を外す
		m_nDataShotInterval.Set(60);		// 弾の間隔
	}
}

//-------------------------------------
//- 戦闘ステータスの銀装備の設定
//-------------------------------------
void CStateBattle::SetWeaponSilver(bool bUse)
{
	// 装備の有無
	if (bUse == true)
	{
		m_bDataWeaponEarlyShot.Set(true);	// 早打ち装備を設定
		m_nDataShotInterval.Set(40);		// 弾の間隔
	}
	else if (bUse == false)
	{
		m_bDataWeaponEarlyShot.Set(false);	// 早打ち装備の設定を外す
		m_nDataShotInterval.Set(60);		// 弾の間隔
	}
}

//-------------------------------------
//- 戦闘ステータスの金装備の設定
//-------------------------------------
void CStateBattle::SetWeaponGold(bool bUse)
{
	// 装備の有無
	if (bUse == true)
	{
		m_bDataWeaponEarlyShot.Set(true);	// 早打ち装備を設定
		m_nDataShotInterval.Set(20);		// 弾の間隔
	}
	else if (bUse == false)
	{
		m_bDataWeaponEarlyShot.Set(false);	// 早打ち装備の設定を外す
		m_nDataShotInterval.Set(60);		// 弾の間隔
	}
}

//-------------------------------------
//- 戦闘ステータスのサブ武器の設定
//-------------------------------------
void CStateBattle::SetSubWeaponBomb(bool bUse)
{
	// 変数宣言（情報取得）
	int nSubWeaponNum = m_nSubWeaponNum.Get();	// サブ武器の回数

	// 装備の有無
	if (bUse == true)
	{
		// サブ武器の回数を加算
		nSubWeaponNum++;
	}
	else if (bUse == false)
	{
		// サブ武器の回数を減算
		nSubWeaponNum--;
	}

	// 情報更新
	m_nSubWeaponNum.Set(nSubWeaponNum);	// サブ武器の回数
}

//-------------------------------------
//- 戦闘ステータスの属性加算処理
//-------------------------------------
void CStateBattle::AddElem(int nNor, int nLow, int nChaos)
{
	// 変数宣言（情報取得）
	int nElemNor = m_nDataElemNor.Get();		// 通常属性
	int nElemLow = m_nDataElemLow.Get();		// 聖属性
	int nElemChaos = m_nDataElemChaos.Get();	// 悪属性

	nElemNor += nNor;		// 通常属性を加算
	nElemLow += nLow;		// 聖属性を加算
	nElemChaos += nChaos;	// 悪属性を加算

	if (nElemNor < 0)
	{
		// 通常属性の値を初期化
		nElemNor = 0;
	}

	if (nElemLow < 0)
	{
		// 聖属性の値を初期化
		nElemLow = 0;
	}

	if (nElemChaos < 0)
	{
		// 悪属性の値を初期化
		nElemChaos = 0;
	}

	// 属性種類設定処理
	if (nElemNor > nElemLow &&
		nElemNor > nElemChaos)
	{
		// 通常属性に設定
		m_elemType = ELEM_TYPE_NORMAL;
	}
	else if(
		nElemLow > nElemNor &&
		nElemLow > nElemChaos)
	{
		// 聖属性に設定
		m_elemType = ELEM_TYPE_LOW;
	}
	else if (
		nElemChaos > nElemNor &&
		nElemChaos > nElemLow)
	{
		// 悪属性に設定
		m_elemType = ELEM_TYPE_CHAOS;
	}
	else
	{
		// 通常属性に設定
		m_elemType = ELEM_TYPE_NORMAL;
	}

	// 情報更新
	m_nDataElemNor.Set(nElemNor);		// 通常属性
	m_nDataElemLow.Set(nElemLow);		// 聖属性
	m_nDataElemChaos.Set(nElemChaos);	// 悪属性

	// ランク設定処理
	SetElemRank();
}

//-------------------------------------
//- 戦闘ステータスのサブ武器の種類取得処理
//-------------------------------------
CStateBattle::SUB_WEAPON_TYPE CStateBattle::GetWeaponType(void)
{
	// サブ武器の種類を返す
	return m_subWeaponType;
}

//-------------------------------------
//- 戦闘ステータスの属性の取得処理
//-------------------------------------
CStateBattle::ELEM_TYPE CStateBattle::GetElemType(void)
{
	return m_elemType;
}

//-------------------------------------
//- 戦闘ステータスの属性ランク設定処理
//-------------------------------------
void CStateBattle::SetElemRank(void)
{
	int aElem[ELEM_TYPE_MAX] = {};

	aElem[ELEM_TYPE_NORMAL] = m_nDataElemNor.Get();
	aElem[ELEM_TYPE_LOW] = m_nDataElemLow.Get();
	aElem[ELEM_TYPE_CHAOS] = m_nDataElemChaos.Get();

	for (int nCutElem = 0; nCutElem < ELEM_TYPE_MAX; nCutElem++)
	{
		if (aElem[nCutElem] >= 30)
		{
			m_aDataElemRank[nCutElem].Set(3);
		}
		else if (aElem[nCutElem] >= 15)
		{
			m_aDataElemRank[nCutElem].Set(2);
		}
		else if (aElem[nCutElem] >= 5)
		{
			m_aDataElemRank[nCutElem].Set(1);
		}
	}
}

//-------------------------------------
//- 戦闘ステータスのデバック表示
//-------------------------------------
void CStateBattle::Debug(void)
{
	// デバックプロックの取得
	CDebugProc *pDebugProc = CManager::GetDbugProc();

	// デバックプロック取得の有無を判定
	if (pDebugProc == NULL)
	{
		return;
	}

	pDebugProc->Print("\n");
	pDebugProc->Print("属性ステータス\n");
	pDebugProc->Print("NOR:%d \n", m_nDataElemNor.Get());
	pDebugProc->Print("LOW:%d \n", m_nDataElemLow.Get());
	pDebugProc->Print("CHAOS:%d \n", m_nDataElemChaos.Get());
	pDebugProc->Print("\n");
}