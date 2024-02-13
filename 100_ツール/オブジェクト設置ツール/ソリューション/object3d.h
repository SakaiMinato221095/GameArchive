
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

#include "data.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//=	クラス定義
//=======================================

class CObject3d : public CObject
{
public:

	typedef enum
	{
		TYPE_BLOCK_001 = 0,		// フィールド
		TYPE_MAX
	}TYPE;

	CObject3d();
	~CObject3d();

	HRESULT Init(void);
	HRESULT Init(TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObject3d *Create(void);
	static CObject3d *Create(TYPE type);

	void BindTexture(int nTextureNldx);

	virtual void SetVtx(void);

	CDataD3DXVECTOR3 m_dataPos;		// 位置
	CDataD3DXVECTOR3 m_dataRot;		// 向き
	CDataD3DXVECTOR3 m_dataSize;	// 大きさ

private:

	int m_nTextureNldxUse;				// テクスチャの番号

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファのポインタ

	D3DXMATRIX m_mtxWorld;				// ワールドマトリックス
};

#endif	// 二重インクルード防止の終了