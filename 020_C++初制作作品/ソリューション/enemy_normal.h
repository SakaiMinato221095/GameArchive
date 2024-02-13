
//-===============================================
//-
//-	通常敵の処理のヘッダー[enemy_normal.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _ENEMY_NORMAL_H_		// このマクロが定義されなかったら
#define _ENEMY_NORMAL_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "enemy.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	前方宣言
//-======================================

class CObjectCol;

//-======================================
//-	クラス定義
//-======================================

// 通常敵のクラス
class CEnemyNormal : public CEnemy
{

public:

	typedef enum
	{
		STATE_NORMAL = 0,	// 通常状態
		STATE_TARGET,		// 追尾状態
		STATE_ATTACK,		// 攻撃状態
		STATE_COOL_TIME,	// クールタイム状態
		STATE_MAX
	}STATE;

	CEnemyNormal();
	~CEnemyNormal();

	HRESULT Init(MODEL_TYPE model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEnemyNormal *Create(MODEL_TYPE modelType);

	void Hit(int nCutEnemy, int nDamage);

	CObjectCol *GetObjectCol(void);

	CDataFloat m_fDataSpeed;	// 速度
	CDataFloat m_fDataSpeedNor;	// 強化中の速度
	CDataFloat m_fDataSpeedStr;	// 強化中の速度

	CDataD3DXVECTOR3 m_dataSearchRange;		// 索敵範囲
	CDataD3DXVECTOR3 m_dataSearchRangeNor;	// 通常の索敵範囲
	CDataD3DXVECTOR3 m_dataSearchRangeStr;	// 強化中の索敵範囲

	CDataD3DXVECTOR3 m_dataAttackRange;		// 攻撃範囲
	CDataD3DXVECTOR3 m_dataAttackRangeNor;	// 通常の攻撃範囲
	CDataD3DXVECTOR3 m_dataAttackRangeStr;	// 強化中の攻撃範囲

	CDataInt m_nDataAtkCnt;			// 攻撃カウント
	CDataInt m_nDataCoolTimeCnt;	// クールタイムカウント
	CDataInt m_nDataStrTime;		// 強化時間
	CDataInt m_nDataStrTimeCut;		// 強化時間カウント

private:

	STATE state;
	CObjectCol *m_pObjCol;

	void InitSet(void);

	void AiSearch(void);
	void AiTarget(void);
	void AiAttack(void);
	void AiCoolTime(void);

};

#endif	// 二重インクルード防止の終了
