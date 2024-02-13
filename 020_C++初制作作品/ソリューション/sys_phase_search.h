
//-===============================================
//-
//-	探索フェーズシステム処理のヘッダー[sys_phase_search.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _SYS_PHASE_SEARCH_H_		// このマクロが定義されなかったら
#define _SYS_PHASE_SEARCH_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "sys_game_phase.h"

#include "qte.h"
//-======================================
//-	前方宣言
//-======================================

class CPlayer;

class CManagerObject;

class CUiMission;
class CUiStartText;

class CObj2dNone;

//-======================================
//-	クラス定義
//-======================================

class CSysPhaseSearch : public CSysGamePhase
{

public:

	typedef enum
	{
		STATE_TEXT_000 = 0,
		STATE_TEXT_001,
		STATE_TEXT_MAX,
	}STATE_TEXT;

	CSysPhaseSearch();
	~CSysPhaseSearch();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer *GetPlayer(void);
	static CManagerObject *GetManagerObject(void);
	static CUiMission *GetUiMission(void);

	static CObj2dNone *GetObj2DNone(void);

	static void SetQte(CQte::TYPE_QTE typeQte);
	static void ReleaseQte(void);
		
	CDataInt m_dataEffectCut;

private:

	static CPlayer *m_pPlayerSearch;			// 探索プレイヤー
	static CManagerObject *m_pManagerObject;	// オブジェクト管理のポインタ
	static CUiMission *m_pUiMission;			// 目的UIのポインタ
	static CUiStartText *m_apUiStartText[2];	// スタートテキスト	

	static CQte *m_pQte;						// クイックタイムイベント

	static CObj2dNone *m_pObj2dNone;			// 効果なし2Dオブジェクト

	bool bState;								// スタートの有無

};

#endif	// 二重インクルード防止の終了
