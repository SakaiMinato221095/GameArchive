
//================================================
//=
//= 3Dオブジェクト処理のヘッター[object3d.h]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	二重インクルード防止
//=======================================

#ifndef _OBJECT_3D_H_	//このマクロが定義されなかったら
#define _OBJECT_3D_H_	//二重インクルード帽子のマクロを定義

//=======================================
//=	インクルード
//=======================================

#include "object.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//=	クラス定義
//=======================================

class CObject3d : public CObject
{
public:

	typedef struct
	{
		D3DXVECTOR3 pos;	// 位置
		D3DXVECTOR3 rot;	// 向き
		D3DXVECTOR3 size;	// 大きさ
		D3DXCOLOR color;	// 色
		D3DXVECTOR2 texPos;	// テクスチャ位置
	}VtxData;

	CObject3d(int nPriority = 3);
	~CObject3d();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR color, D3DXVECTOR2 texPos);

	static CObject3d *Create(void);

	virtual void SetVtx(void);

	void SetVtxTex(D3DXVECTOR2 texPos) { m_vtxData.texPos = texPos; }

	void BindTexture(int nTextureNldx) {m_nTextureNldxUse = nTextureNldx;}

	void SetVtxData(VtxData vtxData) { m_vtxData = vtxData; }
	VtxData GetVtxData(void) { return m_vtxData; }

	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }

private:

	VtxData m_vtxData;					// 頂点値情報

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファのポインタ
	D3DXMATRIX m_mtxWorld;				// ワールドマトリックス

	int m_nTextureNldxUse;				// テクスチャの番号
};

#endif	// 二重インクルード防止の終了