
//-===============================================
//-
//-	2Dのアイテム情報の表示のヘッダー[obj_2d_item_info.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _2D_ITEM_INFO_H_		// このマクロが定義されなかったら
#define _2D_ITEM_INFO_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "main.h"

#include "object2d.h"

#include "item.h"

#include "data.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	クラス定義
//-======================================

class CObj2dItemInfo : public CObject2d
{

public:

	CObj2dItemInfo(int nPriority = 3);
	~CObj2dItemInfo();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(CItem::MODEL nModel);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObj2dItemInfo * Create(CItem::MODEL nModel);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	CDataBool m_bDataDraw;

private:

	void InitSet(void);

	static int m_nTextureNldx[CItem::MODEL_MAX];		// テクスチャ番号
};

#endif	// 二重インクルード防止の終了
