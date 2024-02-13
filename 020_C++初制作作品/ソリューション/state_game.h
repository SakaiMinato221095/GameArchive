
//-===============================================
//-
//-	ゲームステータス処理のヘッダー[state_game.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _STATE_GAME_H_		// このマクロが定義されなかったら
#define _STATE_GAME_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "data.h"

//-======================================
//-	クラス定義
//-======================================

class CStateGame
{
public:

	// 終了の状態
	typedef enum
	{
		END_STATE_NONE = 0,	// なし
		END_STATE_BOSS,		// ボス撃破
		END_STATE_TIME,		// 時間経過
		END_STATE_DIED,		// 死亡
		END_STATE_MAX
	}END_STATE;

	CStateGame();
	~CStateGame();

	void Init(void);
	void Uninit(void);

	static CStateGame *Create();

	void AddEnemyDeath(void);

	void SetEndState(END_STATE endState);
	END_STATE GetEndState(void);

	CDataInt m_nDataEnemyDeathCut;		// 敵の死亡カウント
	CDataInt m_nDataEnemyDeathTarget;	// 敵の目標死亡数

	CDataBool m_bDataStart;				// 開始の有無
private:

	void InitSet(void);

	END_STATE m_endState;				// 終了の状態

};

#endif	// 二重インクルード防止の終了

