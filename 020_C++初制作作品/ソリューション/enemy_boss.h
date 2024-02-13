
//-===============================================
//-
//-	ボス敵の処理のヘッダー[enemy_boss.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _ENEMY_BOSS_H_		// このマクロが定義されなかったら
#define _ENEMY_BOSS_H_		// 二重インクルード帽子のマクロを定義

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
class CEnemyBoss : public CEnemy
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

	CEnemyBoss();
	~CEnemyBoss();

	HRESULT Init(MODEL_TYPE model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEnemyBoss *Create(MODEL_TYPE modelType);

	void Hit(int nDamage);

	CObjectCol *GetObjectCol(void);

	CDataInt m_nDataAtkCnt;		// 攻撃カウント

	CDataInt m_nDataCoolTimeCnt;	// クールタイムカウント

private:

	STATE state;				// 状態
	CObjectCol *m_pObjCol;		// コリジョンオブジェクトのポインタ

	void InitSet(void);

	void AiSearch(void);
	void AiTarget(void);
	void AiAttack(void);

	void AiCoolTime(void);

};

#endif	// 二重インクルード防止の終了
