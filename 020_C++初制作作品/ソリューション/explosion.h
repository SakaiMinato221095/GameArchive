
//-===============================================
//-
//-	爆発処理のヘッダー[explosion.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _EXPLOSION_H_		// このマクロが定義されなかったら
#define _EXPLOSION_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object_anima.h"

#include "data.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	クラス定義
//-======================================

class CExplosion : public CObjectAnima
{

public:

	CExplosion();
	~CExplosion();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CExplosion *Create(void);

	bool Sub(void);

	void SetAnimaLife(void);

	CDataInt m_nDataLife;

private:

	static LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャ
};

#endif	// 二重インクルード防止の終了
