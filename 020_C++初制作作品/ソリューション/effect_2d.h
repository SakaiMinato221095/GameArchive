
//-===============================================
//-
//-	2Dエフェクトの処理のヘッダー[effect_2d.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _EFFECT_2D_H_		// このマクロが定義されなかったら
#define _EFFECT_2D_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object2d.h"

#include "data.h"

//-======================================
//-	クラス定義
//-======================================

class CEffect2d : public CObject2d
{

public:

	// エフェクトのテクスチャ列挙型
	typedef enum
	{
		TEX_NORMAL_000 = 0,		// 通常エフェクト000のテクスチャ
		TEX_MAX
	}TEX;

	CEffect2d(int nPriority = 3);
	~CEffect2d();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(TEX tex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR color, int nLife, bool bZTest);

	static CEffect2d *Create(TEX tex);

	CDataD3DXVECTOR3 m_dataMove;		// 移動量

	CDataD3DXVECTOR3 m_dataSizeHold;	// サイズを保持
	CDataD3DXCOLOR m_dataColorHold;		// 色を保持

	CDataInt m_nDataLife;				// 体力

	CDataBool m_bDataZTestOff;			// Zテストの有無

private:

	void Add(void);
	bool Sub(void);

	static int m_nTextureNldx[TEX_MAX];		// テクスチャ番号

};

#endif	// 二重インクルード防止の終了
