
//-===============================================
//-
//-	爆弾弾の処理のヘッダー[bullet_bomb.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _BULLET_BOMB_H_		// このマクロが定義されなかったら
#define _BULLET_BOMB_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "bullet.h"

#include "data.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	クラス定義
//-======================================

class CBulletBomb : public CBullet
{

public:

	CBulletBomb(int nPriority = 3);
	~CBulletBomb();

	HRESULT Init(TEX tex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBulletBomb * Create(TEX tex);

	CDataInt m_nDataBlastDamage;

private:

	void InitSet(void);

	void Move(void);

	void Add(void);
	bool Sub(void);

	bool CollisionEnemy(void);
	void CollisionEnemyBlast(int nRawEmyNum);
	bool CollisionObject(void);

};

#endif	// 二重インクルード防止の終了
