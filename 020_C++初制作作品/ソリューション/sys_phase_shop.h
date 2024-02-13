
//-===============================================
//-
//-	購入フェーズシステム処理のヘッダー[sys_phase_shop.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _SYS_PHASE_SHOP_H_		// このマクロが定義されなかったら
#define _SYS_PHASE_SHOP_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "sys_game_phase.h"

//-======================================
//-	前方宣言
//-======================================

class CPlayer;

class CManagerObject;

class CUiMission;

//-======================================
//-	クラス定義
//-======================================

class CSysPhaseShop : public CSysGamePhase
{

public:

	CSysPhaseShop();
	~CSysPhaseShop();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer *GetPlayer(void);

	static CManagerObject *GetManagerObject(void);

	static CUiMission *GetUiMission(void);

private:

	static CPlayer *m_pPlayerShop;				// 探索プレイヤー

	static CManagerObject *m_pManagerObject;	// オブジェクト管理のポインタ

	static CUiMission *m_pUiMission;			// 目的UIのポインタ

};

#endif	// 二重インクルード防止の終了
