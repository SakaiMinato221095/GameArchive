
//================================================
//=
//= ビルボードオブジェクト処理のヘッター[object_billboard.h]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	二重インクルード防止
//=======================================

#ifndef _OBJECT_BILLBOARD_H_	// このマクロが定義されなかったら
#define _OBJECT_BILLBOARD_H_	// 二重インクルード帽子のマクロを定義

//=======================================
//=	インクルード
//=======================================

#include "object.h"

#include "data.h"

//=======================================
//=	クラス定義
//=======================================

// ビルボードオブジェクトのクラス
class CObjectBillboard : public CObject
{
public:
	CObjectBillboard(int nPriority = 3);
	~CObjectBillboard();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjectBillboard *Create(void);

	void BindTexture(int nTextureNldx);

	void SetVtx(void);

	CDataD3DXVECTOR3 m_dataPos;		// 位置
	CDataD3DXVECTOR3 m_dataSize;	// 大きさ
	CDataD3DXVECTOR3 m_dataMove;	// 移動量
	CDataD3DXCOLOR m_dataColor;		// 色情報

private:

	int m_nTextureNldxUse;				// テクスチャの番号

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファのポインタ
	
	D3DXMATRIX m_mtxWorld;				// ワールドマトリックス
};

#endif 