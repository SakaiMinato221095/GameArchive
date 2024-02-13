
//-===============================================
//-
//-	エフェクトの処理のヘッダー[effect.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _EFFECT_H_		// このマクロが定義されなかったら
#define _EFFECT_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object_billboard.h"

#include "data.h"

//-======================================
//-	クラス定義
//-======================================

class CEffect : public CObjectBillboard
{

public:


	// エフェクトのテクスチャ列挙型
	typedef enum
	{
		TEX_NORMAL_000 = 0,		// 通常エフェクト000のテクスチャ
		TEX_MAX
	}TEX;

	CEffect(int nPriority = 3);
	~CEffect();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(TEX tex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR color, int nLife, bool bZTest);

	static CEffect *Create(TEX tex);

	CDataD3DXVECTOR3 m_dataSizeHold;	// サイズを保持
	CDataD3DXCOLOR m_dataColorHold;		// 色を保持

	CDataInt m_nDataLife;				// 体力

	CDataBool m_bDataZTestOff;			// Zテストの有無

private:

	void Add(void);
	bool Sub(void);

	static int m_nTextureNldx[TEX_MAX];		// テクスチャ番号

};

//-======================================
//- プロトタイプ宣言
//-======================================

#endif	// 二重インクルード防止の終了
