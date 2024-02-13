
//-===============================================
//-
//-	探索プレイヤー処理のヘッダー[player_search.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _PLAYER_SEARCH_H_		// このマクロが定義されなかったら
#define _PLAYER_SEARCH_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "player.h"

#include "data.h"

#include "object_model.h"
#include "motion.h"

//=======================================
//=	マクロ定義
//=======================================

#define GARBAGE_SCORE_STOCK_MAX	(10)	// ゴミスコアのストック最大数

//-======================================
//-	前方宣言
//-======================================

class CEventObject;
class CGarbage;
class CGarbageCollect;
class CGate;

class CUiOprDesc;
class CUiTextDesc;

//-======================================
//-	クラス定義
//-======================================

class CPlayerSearch : public CPlayer
{

public:

	typedef enum
	{
		STATE_TYPE_NEUTRAL = 0,	// 待機
		STATE_TYPE_MOVE,		// 移動
		STATE_TYPE_TOUCH,		// 触る
		STATE_TYPE_EAT,			// 食べる
		STATE_TYPE_MAX
	}STATE_TYPE;

	CPlayerSearch();
	~CPlayerSearch();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CObjectModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayerSearch * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CObjectModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	CDataInt m_nDataStateTime;		// 状態時間
	CDataInt m_nDataStateCount;		// 状態時間のカウント

private:

	void UpdateEvent(void);
	void CollisionEvent(void);
	void InputEventAction(CEventObject *pEventObject);
	void InputGarbageAction(CGarbage * pGarbage, int nNum);
	void InputGateAction(CGate * pGate);

	void UpdateMotion(void);

	STATE_TYPE m_stateType;		// 状態の種類
	STATE_TYPE m_stateTypeOld;	// 前回の状態の種類

	CUiOprDesc *m_pUiOprDesc;	// 操作説明UIのポインタ
	CUiTextDesc *m_pUiTextDesc;	// 操作説明文UIのポインタ
};


#endif	// 二重インクルード防止の終了
