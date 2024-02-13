
//-===============================================
//-
//-	戦闘ステータス処理のヘッダー[state_battle.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _STATE_BATTLE_H_		// このマクロが定義されなかったら
#define _STATE_BATTLE_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "data.h"

//-======================================
//-	クラス定義
//-======================================

class CStateBattle
{
public:

	typedef enum
	{
		SUB_WEAPON_TYPE_BOMB  = 0,	// ボム
		SUB_WEAPON_TYPE_MAX
	}SUB_WEAPON_TYPE;

	typedef enum
	{
		ELEM_TYPE_NORMAL = 0,	// 通常属性
		ELEM_TYPE_LOW,			// 聖属性
		ELEM_TYPE_CHAOS,		// 悪属性
		ELEM_TYPE_MAX
	}ELEM_TYPE;

	CStateBattle();
	~CStateBattle();
	
	void Init(void);
	void Uninit(void);
	void Update(void);

	static CStateBattle *Create();

	void SetWeaponCopper(bool bUse);
	void SetWeaponSilver(bool bUse);
	void SetWeaponGold(bool bUse);

	void SetSubWeaponBomb(bool bUse);

	void AddElem(int nNor,int nLow,int nChaos);

	SUB_WEAPON_TYPE GetWeaponType(void);
	ELEM_TYPE GetElemType(void);

	CDataInt m_nSubWeaponNum;					// サブ武器の回数

	CDataInt m_nDataShotInterval;				// 弾の発射間隔
	CDataBool m_bDataWeaponEarlyShot;			// 早打ち装備の有無 
	
	CDataInt m_nDataElemNor;					// 通常属性値
	CDataInt m_nDataElemLow;					// 聖属性値
	CDataInt m_nDataElemChaos;					// 悪属性値

	CDataInt m_aDataElemRank[ELEM_TYPE_MAX];	// 属性ランク

private:

	void SetElemRank(void);
	void Debug(void);

	SUB_WEAPON_TYPE m_subWeaponType;
	ELEM_TYPE m_elemType;
};

#endif	// 二重インクルード防止の終了

