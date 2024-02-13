
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

#include "billboard.h"

//-======================================
//-	クラス定義
//-======================================

class CEffect : public CBillboard
{

public:

	// エフェクトのテクスチャ列挙型
	typedef enum
	{
		TEX_NORMAL_000 = 0,		// 通常エフェクト000のテクスチャ
		TEX_MAX
	}TEX;

	// 情報
	struct Data
	{
		D3DXVECTOR3 move;		// 移動量
		D3DXVECTOR3 sizeHold;	// 大きさ
		D3DXCOLOR colorHold;	// 色

		int nLife;				// 体力
		bool bIsZTestStop;		// Zテストの有無
	};

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

	void SetData(Data data) { m_data = data; }


private:

	void Add(void);
	bool Sub(void);

	Data m_data;							// 情報

	static int m_nTextureNldx[TEX_MAX];		// テクスチャ番号
};

#endif	// 二重インクルード防止の終了
