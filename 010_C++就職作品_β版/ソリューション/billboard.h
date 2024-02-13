
//================================================
//=
//= ビルボード処理のヘッター[billboard.h]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	二重インクルード防止
//=======================================

#ifndef _BILLBOARD_H_	// このマクロが定義されなかったら
#define _BILLBOARD_H_	// 二重インクルード帽子のマクロを定義

//=======================================
//=	インクルード
//=======================================

#include "object.h"

//=======================================
//=	クラス定義
//=======================================

// ビルボードオブジェクトのクラス
class CBillboard : public CObject
{
public:

	// 情報
	typedef struct
	{
		D3DXVECTOR3 pos;	// 位置
		D3DXVECTOR3 size;	// 大きさ
		D3DXCOLOR color;	// 色
	}Info;

	CBillboard(int nPriority = 3);
	~CBillboard();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBillboard *Create(void);

	void SetInit(D3DXVECTOR3 pos,D3DXVECTOR3 size, D3DXCOLOR color);

	virtual void SetVtx(void);

	void UpdateInfo(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
	{
		m_info.pos = pos;
		m_info.size = size;
		m_info.color = color;
		SetVtx();
	}

	void BindTexture(int nTextureNldx) { m_nTextureNldxUse = nTextureNldx; };

	void SetPos(D3DXVECTOR3 pos) { m_info.pos = pos; }
	D3DXVECTOR3 GetPos(void) { return m_info.pos; }

	void SetSize(D3DXVECTOR3 size) { m_info.size = size; }
	D3DXVECTOR3 GetSize(void) { return m_info.size; }

	void SetColor(D3DXCOLOR color) { m_info.color = color; }
	D3DXCOLOR GetColor(void) { return m_info.color; }

	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }

private:

	Info m_info;						// 頂点値情報

	int m_nTextureNldxUse;				// テクスチャの番号

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファのポインタ
	
	D3DXMATRIX m_mtxWorld;				// ワールドマトリックス
};

#endif 