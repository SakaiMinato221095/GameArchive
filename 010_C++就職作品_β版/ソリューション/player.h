
//-===============================================
//-
//-	プレイヤー処理のヘッダー[player.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _PLAYER_H_		// このマクロが定義されなかったら
#define _PLAYER_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object.h"

#include "model.h"
#include "motion.h"

#include "command.h"

//=======================================
//=	マクロ定義
//=======================================

#define INSTANCE_MAX	(8)		// 自身のポインタの最大数

//-======================================
//-	前方宣言
//-======================================

class CObjectX;
class CObject3d;
class CColl;
class CAttack;

class CObj2dGage;

//-======================================
//-	クラス定義
//-======================================

class CPlayer : public CObject
{

public:

	// モーション状態
	typedef enum
	{
		MOTION_STATE_NEUTRAL = 0,	// 待機
		MOTION_STATE_MOVE,			// 移動
		MOTION_STATE_PUNCH,			// パンチ
		MOTION_STATE_KICK,			// キック
		MOTION_STATE_PUNCH_FINISH,	// パンチ基本フィニッシュ
		MOTION_STATE_KICK_FINISH,	// キック基本フィニッシュ
		MOTION_STATE_MAX
	}MOTION_STATE;

	// モーション状態
	typedef enum
	{
		STATE_NEUTRAL = 0,	// 待機
		STATE_BATTLE,		// 戦闘中
		STATE_FINISH,		// フィニッシュ
		STATE_MAX
	}STATE;

	// 追加値の情報
	typedef struct
	{
		float speedRate;	// 速度追加の倍率
		int sppedPlusTime;	// 速度追加の時間

	}DataPlus;

	// 情報値
	typedef struct
	{
		D3DXVECTOR3 pos;		// 位置
		D3DXVECTOR3 posOld;		// 前回の位置
		D3DXVECTOR3 posTgt;		// ターゲットの位置

		D3DXVECTOR3 rot;		// 向き
		D3DXVECTOR3 rotDest;	// 目的の向き

		D3DXVECTOR3 move;		// 移動量
		D3DXVECTOR3 moveHold;	// 保持した移動量

		D3DXVECTOR3 size;		// 大きさ

		int nLife;				// 体力

		DataPlus plus;			// 追加値

		STATE state;				// 情報の種類
		MOTION_STATE motionState;	// モーション状態の種類

		bool bIsTarget;				// ターゲットの有無

		int nAttackPartsNldx;		// 攻撃の部位
	}Data;

	CPlayer();
	~CPlayer();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax);

	void Uninit(void);
	void Update(void);
	void Draw(void);

	virtual void HitDamage(int nDamage);

	static CPlayer * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType);

	CMotion* GetMotion(void) { return m_pMotion; }

	CModel* GetModel(int nNumParts) { return m_apModel[nNumParts]; }

	void SetData(Data data) { m_data = data; }
	Data GetData(void) { return m_data; }

	MOTION_STATE GetMotionState(void) { return m_data.motionState; }

	void SetPlus(float fRate, int nTime) { m_data.plus.speedRate = fRate, m_data.plus.sppedPlusTime = nTime; }

private:

	// 当たり判定の種類
	typedef enum
	{
		COLL_TYPE_NEUTRAL = 0,	// 通常
		COLL_TYPE_SEARCH,		// 索敵
		COLL_TYPE_MAX
	}COLL_TYPE;

	void InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	void UpdatePos(void);
	void UpdateBattle(void);
	void UpdateRot(void);
	void UpdatePlusData(void);
	void UpdateAttack(void);
	void UpdateCommand(void);
	void UpdateCollision(void);
	void UpdateMotionNone(void);

	void InputMove(void);
	void InputCombo(void);

	void SetAttack(CCommand::INPUT_TYPE inputType);

	void SetAttackFinish(void);
	void SetAttackFinishKick(void);

	void DebugPlayer(void);

	Data m_data;							// 値を格納
	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス

	CModel *m_apModel[MODEL_PARTS_MAX];		// モデル（パーツ）のポインタ
	int m_nNumModel;						// モデル（パーツ）の総数

	CColl* m_apColl[COLL_TYPE_MAX];			// 当たり判定情報
	CMotion *m_pMotion;						// モーションのポインタ
	CAttack* m_pAttack;						// 攻撃のポインタ
	CCommand* m_pCommand;					// コマンドのポインタ
	CObj2dGage* m_pLife2dGage;				// 体力表示のポインタ
};

#endif	// 二重インクルード防止の終了
