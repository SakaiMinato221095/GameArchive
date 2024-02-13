
//-===============================================
//-
//-	モードステータス処理のヘッダー[state_mode.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _STATE_MODE_H_		// このマクロが定義されなかったら
#define _STATE_MODE_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "data.h"

//-======================================
//-	クラス定義
//-======================================

class CStateMode
{
public:

	typedef enum
	{
		RESULT_STATE_NONE = 0,
		RESULT_STATE_WIN,		// 勝利リザルト
		RESULT_STATE_END,		// 通常リザルト
		RESULT_STATE_LOOSE,		// 負けリザルト
		RESULT_STATE_MAX
	}RESULT_STATE;

	CStateMode();
	~CStateMode();

	void Init(void);
	void Uninit(void);

	void ResetResultState(void);

	static CStateMode *Create();

	void SetResultState(RESULT_STATE resultState);
	RESULT_STATE GetResultState(void);

private:

	
	RESULT_STATE m_resultState;	// リザルト状態
};

#endif	// 二重インクルード防止の終了

