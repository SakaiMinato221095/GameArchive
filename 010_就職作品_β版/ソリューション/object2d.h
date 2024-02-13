
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
	virtual ~CObject2d();

	HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static CObject2d *Create(void);

	virtual void SetVtx(void);

	void SetInit(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
	{
		m_info.pos = pos;
		m_info.size = size;
		m_info.color = color;
		SetVtx();
	}

	void UpdateInfo(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
	{
		m_info.pos = pos;
		m_info.size = size;
		m_info.color = color;
		SetVtx();
	}

	void SetPos(D3DXVECTOR3 pos) { m_info.pos = pos; }
	D3DXVECTOR3 GetPos(void) { return m_info.pos; }

	void SetSize(D3DXVECTOR3 size) { m_info.size = size; }
	D3DXVECTOR3 GetSize(void) { return m_info.size; }

	void SetColor(D3DXCOLOR color) { m_info.color = color; }
	D3DXCOLOR GetColor(void) { return m_info.color; }

	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }
	void BindTexture(int nTextureNldx) { m_nTextureNldxUse = nTextureNldx; }

private:

	typedef struct
	{
		D3DXVECTOR3 pos;	// 位置
		D3DXVECTOR3 size;	// 大きさ
		D3DXCOLOR color;	// 色
	}Info;

	Info m_info;								// 頂点値情報

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// 頂点バッファを格納
	int m_nTextureNldxUse;						// テクスチャの番号

};


#endif	// 二重インクルード防止の終了
