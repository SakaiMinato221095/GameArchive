
//-===============================================
//-
//-	当たり判定地面のヘッダー[box_field.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _BOX_FIELD_H_		// このマクロが定義されなかったら
#define _BOX_FIELD_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object3d.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	クラス定義
//-======================================

// アイテムのクラス
class CBoxField : public CObject3d
{

public:

	CBoxField(int nPriority = 3);;
	~CBoxField();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBoxField* Create(void);

private:

};

#endif	// 二重インクルード防止の終了
