
//-===============================================
//-
//-	購入プレイヤー処理のヘッダー[player_shop.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _PLAYER_SHOP_H_		// このマクロが定義されなかったら
#define _PLAYER_SHOP_H_		// 二重インクルード帽子のマクロを定義

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

//-======================================
//-	前方宣言
//-======================================

class CItem;

class CUiOprDesc;
class CUiTextDesc;

//-======================================
//-	クラス定義
//-======================================

class CPlayerShop : public CPlayer
{

public:

	typedef enum
	{
		STATE_TYPE_NEUTRAL = 0,	// 待機
		STATE_TYPE_MOVE,		// 移動
		STATE_TYPE_BUY,			// 購入
		STATE_TYPE_MAX			// 最大数
	}STATE_TYPE;

	CPlayerShop();
	~CPlayerShop();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CObjectModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayerShop * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CObjectModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:

	void UpdateItem(void);
	void CollisionItem(void);
	void InputItemAction(CItem *pItem);

	void UpdateMotion(void);

	STATE_TYPE m_stateType;		// 状態の種類
	STATE_TYPE m_stateTypeOld;	// 前回の状態の種類

	CUiOprDesc *m_pUiOprDesc;	// 操作説明UIのポインタ
	CUiTextDesc *m_pUiTextDesc;	// 操作説明文UIのポインタ
};

#endif	// 二重インクルード防止の終了
