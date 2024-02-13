
//-===============================================
//-
//-	戦闘フェーズシステム処理のヘッダー[sys_phase_battle.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _SYS_PHASE_BATTLE_H_		// このマクロが定義されなかったら
#define _SYS_PHASE_BATTLE_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "sys_game_phase.h"

//-======================================
//-	前方宣言
//-======================================

class CPlayer;
class CManagerObject;
class CLife;
class CUiMission;
class CObj2dNone;

class CEnemyBoss;

//-======================================
//-	クラス定義
//-======================================

class CSysPhaseBattle : public CSysGamePhase
{

public:

	CSysPhaseBattle();
	~CSysPhaseBattle();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CLife *GetLife(void);
	static CPlayer *GetPlayer(void);
	static CManagerObject *GetManagerObject(void);
	static CUiMission *GetUiMission(void);

	static CObj2dNone *GetObj2DNone(void);

	CDataInt m_dataEffectCut;

private:

	static CLife *m_pLife;						// 体力
	static CPlayer *m_pPlayerBattle;			// 戦闘プレイヤー
	static CManagerObject *m_pManagerObject;	// オブジェクト管理のポインタ
	static CUiMission *m_pUiMission;			// 目的UIのポインタ

	static CObj2dNone *m_pObj2dNone;			// 効果なし2Dオブジェクト

};

#endif	// 二重インクルード防止の終了
