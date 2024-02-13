
//-===============================================
//-
//-	2Dオブジェクト処理のヘッダー[object2d.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _OBJECT_2D_H_		// このマクロが定義されなかったら
#define _OBJECT_2D_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object.h"

#include "data.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	クラス定義
//-======================================

class CObject2d : public CObject
{

public:

	CObject2d(int nPriority = 3);
	~CObject2d();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void BindTexture(int nTextureNldx);

	static CObject2d *CObject2d::Create(int nPriority = 3);

	virtual void SetVtx(void);

	CDataD3DXVECTOR3 m_dataPos;		// 位置
	CDataD3DXVECTOR3 m_dataPosOld;	// 前回の位置
	CDataD3DXVECTOR3 m_dataSize;	// 大きさ
	CDataD3DXCOLOR m_dataColor;		// 色

	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void);

	CObject2d *GetObject2d(void);

private:

	int m_nTextureNldxUse;						// テクスチャの番号

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// 頂点バッファを格納
};

//-======================================
//- プロトタイプ宣言
//-======================================

#endif	// 二重インクルード防止の終了
