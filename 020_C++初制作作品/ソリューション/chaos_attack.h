
//-===============================================
//-
//-	闇の攻撃の処理のヘッダー[chaos_attack.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _CHAOS_ATTACK_H_		// このマクロが定義されなかったら
#define _CHAOS_ATTACK_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object.h"

#include "data.h"

#include "manager_object.h"

//-======================================
//-	マクロ定義
//-======================================

#define COLLISION_NUM_MAX	(4)	// 当たり判定の最大数

//-======================================
//-	前方宣言
//-======================================

class CObjectCol;

//-======================================
//-	クラス定義
//-======================================

class CChaosAttack : public CObject
{

public:

	// 闇の攻撃の当たり判定の構造体
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 size;
	}Collision;

	CChaosAttack(int nPriority = 3);
	~CChaosAttack();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nDamage);

	static CChaosAttack * Create(void);

	CDataInt m_nDataDamage;
	CDataInt m_nDamageTime;

	CDataD3DXVECTOR3 m_dataPos;
	CDataD3DXVECTOR3 m_dataRot;

private:

	void Add(void);
	void Sub(void);

	bool CollisionEnemy(void);

	void InitSet(void);

	Collision m_aCol[COLLISION_NUM_MAX];			// 当たり判定

	int m_aEnemyDamageCut[ENEMY_NORMAL_NUM_MAX];	// 敵のダメージカウント 
	int m_nEnemyBossDmageCut;						// ボスのダメージカウント
};

#endif	// 二重インクルード防止の終了
