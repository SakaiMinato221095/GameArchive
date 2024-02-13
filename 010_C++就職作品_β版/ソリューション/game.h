
//-===============================================
//-
//-	ゲームの処理のヘッダー[game.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _GAME_H_		// このマクロが定義されなかったら
#define _GAME_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "manager.h"

//=======================================
//=	コンスト定義
//=======================================

namespace GAME
{
	const int FIELD_NUM = 2;
	const int WALL_NUM = 4;
}

//-======================================
//-	前方宣言
//-======================================

class CTimer;
class CPause;
class CPhaseManager;

class CPlayer;

class CSkybox;
class CObj3dField;
class CObj3dWall;

//-======================================
//-	クラス定義
//-======================================

class CGame : public CScene
{

public:

	typedef enum
	{
		GAME_STATE_NONE = 0,	// ゲームの通常状態
		GAME_STATE_PAUSE,		// ポーズ状態
		GAME_STATE_MAX
	}GAME_STATE;

	CGame();
	~CGame();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPause* GetPause(void) { return m_infoPoint.pPause; }
	static CPhaseManager* GetPhaseManager(void) { return m_infoPoint.pPhaseManager; }
	static CSkybox* GetSkyBox(int nNum) { return m_infoPoint.pSkyBox; }
	static CObj3dField* GetField(int nNum) { return m_infoPoint.apField[nNum]; }
	static CObj3dWall* GetWall(int nNum) { return m_infoPoint.apWall[nNum]; }
	static CPlayer* GetPlayer(void) { return m_infoPoint.pPlayer; }

private:

	// ポインタ情報
	struct InfoPoint
	{
		CPause* pPause;					// ポーズ
		CPhaseManager* pPhaseManager;	// フェーズ管理

		CSkybox* pSkyBox;						// スカイボックス
		CObj3dField* apField[GAME::FIELD_NUM];	// 床
		CObj3dWall* apWall[GAME::WALL_NUM];		// 壁

		CPlayer* pPlayer;					// プレイヤー
	};

	static InfoPoint m_infoPoint;		// ポインタの情報

	GAME_STATE m_gameState;				// ゲーム状態
};

#endif	// 二重インクルード防止の終了
