
//-===============================================
//-
//-	タイトルの処理のヘッダー[title.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _TITLE_H_		// このマクロが定義されなかったら
#define _TITLE_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "manager.h"

//=======================================
//=	マクロ定義
//=======================================

//-======================================
//-	前方宣言
//-======================================

class CCharacter;

class CObject2d;

//-======================================
//-	クラス定義
//-======================================

class CTitle : public CScene
{

public:

	typedef enum
	{
		TEX_NULL = 0,		// なし
		TEX_LOGO_000,		// タイトルロゴ
		TEX_BUTTON_000,		// タイトルボタン
		TEX_MAX
	}TEX;

	typedef enum
	{
		TYPE_2D_LOGO = 0,	// タイトルロゴ
		TYPE_2D_BUTTON,	// タイトルボタン
		TYPE_2D_MAX
	}TYPE_2D;

	CTitle();
	~CTitle();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	static CCharacter *m_pCharacter;
	static CObject2d *m_apObj2d[TYPE_2D_MAX];

	static int m_aTextureNldx[TEX_MAX];		// テクスチャ番号
};

#endif	// 二重インクルード防止の終了
