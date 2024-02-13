
//-===============================================
//-
//-	ブロックの処理のヘッダー[block.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _BLOCK_H_		// このマクロが定義されなかったら
#define _BLOCK_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object2d.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	クラス定義
//-======================================

class CBlock : public CObject2d
{

public:

	CBlock(int nPriority = 3);
	~CBlock();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBlock *Create(void);

private:

	static LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャ

};

#endif	// 二重インクルード防止の終了
