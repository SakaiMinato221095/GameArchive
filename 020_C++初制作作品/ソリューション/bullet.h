
//-===============================================
//-
//-	弾の処理のヘッダー[bullet.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _BULLET_H_		// このマクロが定義されなかったら
#define _BULLET_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object_billboard.h"

#include "data.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	クラス定義
//-======================================

class CBullet : public CObjectBillboard
{

public:

	// 弾のテクスチャ列挙型
	typedef enum
	{
		TEX_RED_000 = 0,		// 赤の弾000のテクスチャ
		TEX_BLUE_000,			// 青の弾000のテクスチャ
		TEX_MAX
	}TEX;

	CBullet(int nPriority = 3);
	~CBullet();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(TEX tex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBullet * Create(TEX tex);

	CDataInt m_nDataLife;
	CDataInt m_nDataDamage;

private:

	void Move(void);

	void Add(void);
	bool Sub(void);

	bool CollisionEnemy(void);
	bool CollisionObject(void);

	static int m_nTextureNldx[TEX_MAX];		// テクスチャの番号

};

#endif	// 二重インクルード防止の終了
