
//-===============================================
//-
//-	ポーズの処理のヘッダー[pause.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _PAUSE_H_		// このマクロが定義されなかったら
#define _PAUSE_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object.h"

//=======================================
//=	マクロ定義
//=======================================

//-======================================
//-	前方宣言
//-======================================

class CObject2d;

//-======================================
//-	クラス定義
//-======================================

class CPause
{

public:

	enum TEX
	{
		TEX_BG = 0,	// 背景
		TEX_GAME,	// ゲーム
		TEX_RETRY,	// リトライ
		TEX_TITLE,	// タイトル
		TEX_CURSOR,	// カーソル
		TEX_MAX
	};

	enum TYPE
	{
		TYPE_BG = 0,	// 背景
		TYPE_GAME,		// ゲーム
		TYPE_RETRY,		// リトライ
		TYPE_TITLE,		// タイトル
		TYPE_CURSOR,	// カーソル
		TYPE_MAX
	};

	typedef enum
	{
		TYPE_SELECT_GAME = 0,	// ゲーム
		TYPE_SELECT_RETRY,		// リトライ
		TYPE_SELECT_TITLE,		// タイトル
		TYPE_SELECT_MAX,
	}TYPE_SELECT;

	CPause();
	~CPause();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPause * Create(void);

	bool GetOk(void) { return m_bOk; }
	TYPE_SELECT GetTypeSelect(void) { return m_typeSelect; }

private:

	// 見た目の情報
	struct InfoVisual
	{
		CObject2d* apObj2d[TYPE_MAX];		// 2Dオブジェクトのポインタ
	};

	InfoVisual m_infoVisual;			// 見た目の情報
	TYPE_SELECT m_typeSelect;			// 現在の選択の種類

	bool m_bOk;

	static int m_nTextureNldx[TEX_MAX];

};

#endif	// 二重インクルード防止の終了

