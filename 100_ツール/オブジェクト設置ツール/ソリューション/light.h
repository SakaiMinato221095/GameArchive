
//================================================
//=
//= ライトのヘッター[light.h]
//= Author Sakai Minato
//=
//================================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _LIGHT_H_	// このマクロが定義されなかったら
#define _LIGHT_H_	// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

//=======================================
//=	マクロ定義
//=======================================

#define LIGHT_MAX	(3)			// ライトの最大数

//-======================================
//-	クラス定義
//-======================================

// ライトのクラス
class CLight
{

public:

	CLight();
	~CLight();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:

	D3DLIGHT9 m_light[LIGHT_MAX];	// ライトの情報

};

#endif	// 二重インクルード防止の終了
