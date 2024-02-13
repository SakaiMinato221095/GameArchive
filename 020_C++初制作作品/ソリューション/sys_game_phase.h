
//-===============================================
//-
//-	ゲームフェーズシステム処理のヘッダー[sys_game_phase.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _SYS_GAME_PHASE_H_		// このマクロが定義されなかったら
#define _SYS_GAME_PHASE_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "data.h"
#include "sys_game_phase.h"

//-======================================
//-	前方宣言
//-======================================

class CPlayer;

//-======================================
//-	クラス定義
//-======================================

class CSysGamePhase
{

public:

	typedef enum
	{
		TYPE_SEARCH = 0,	// 探索フェーズ
		TYPE_SHOP,			// 購入フェーズ
		TYPE_BATTLE,		// 戦闘フェーズ
		TYPE_MAX
	}TYPE;

	CSysGamePhase();
	virtual ~CSysGamePhase();

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static CSysGamePhase *Create(TYPE type, HINSTANCE hInstance = NULL, HWND hWnd = 0, BOOL bWindow = true);

	static void SetType(TYPE type);
	static TYPE GetType(void);

	static void SetTypeNext(TYPE typeNext);
	static TYPE GetTypeNext(void);

	static CPlayer *GetPlayer(void);

private:

	static TYPE m_type;		// ゲームフェーズの種類
	static TYPE m_typeNext;	// 次のフェーズの設定
};

#endif	// 二重インクルード防止の終了
