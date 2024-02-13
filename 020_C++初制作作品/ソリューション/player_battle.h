
//-===============================================
//-
//-	戦闘プレイヤー処理のヘッダー[player_battle.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _PLAYER_BATTLE_H_		// このマクロが定義されなかったら
#define _PLAYER_BATTLE_H_		// 二重インクルード帽子のマクロを定義

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

//=======================================
//=	前方宣言
//=======================================

class CGate;

class CChaosAttack;

class CUiOprDesc;
class CUiTextDesc;

//-======================================
//-	クラス定義
//-======================================

class CPlayerBattle : public CPlayer
{

public:

	typedef enum
	{
		STATE_TYPE_NEUTRAL = 0,		// 待機
		STATE_TYPE_MOVE,			// 移動
		STATE_TYPE_ATTACK,			// 攻撃
		STATE_TYPE_NOR_ATTACK,		// 通常チャージ攻撃
		STATE_TYPE_CHAOS_ATTACK,	// 闇チャージ攻撃 
		STATE_TYPE_DAMAGE,			// ダメージ
		STATE_TYPE_DEAD,			// 死亡状態
		STATE_TYPE_MAX			
	}STATE_TYPE;

	CPlayerBattle();
	~CPlayerBattle();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CObjectModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayerBattle * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CObjectModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	void ColGate(void);

	void Hit(int nDamage);

	CDataInt nDataShotIntervalCount;	// 弾の間隔のカウント
	CDataBool bDataShot;				// 射撃の有無
	CDataBool bDataShotAgain;			// 再射撃
	CDataBool m_bDataCharge;			// チャージの有無
	CDataInt m_nDataChargeCut;			// チャージカウント
	CDataInt m_nDataChargeMax;			// チャージの最大値

	CDataInt m_nDataCoolTime;			// クールタイム
private:

	void InputAttack(void);

	void InputGateAction(CGate * pGate);

	void UpdateAttack(void);
	void UpdateMotion(void);

	void ShotNor(void);
	void ShotNorCharge(void);
	void ShotChaosCharge(void);

	STATE_TYPE m_stateType;			// 状態の種類
	STATE_TYPE m_stateTypeNew;		// 最新の状態の種類

	CUiOprDesc *m_pUiOprDesc;		// 操作説明UIのポインタ
	CUiTextDesc *m_pUiTextDesc;		// 操作説明文UIのポインタ

	CChaosAttack *m_pChaosAttack;	// 闇の攻撃
};

#endif	// 二重インクルード防止の終了
