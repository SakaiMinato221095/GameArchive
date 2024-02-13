
//-===============================================
//-
//-	ボス敵の処理のヘッダー[enemy_boss.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _ENEMY_BOSS_H_		// このマクロが定義されなかったら
#define _ENEMY_BOSS_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "enemy.h"

#include "model.h"
#include "motion.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	前方宣言
//=======================================

class CCharacter;
class CAttack;

class CObj2dGage;

//-======================================
//-	クラス定義
//-======================================

// ボス敵のクラス
class CEnemyBoss : public CEnemy
{

public:

	// モーション状態
	enum MOTION_STATE
	{
		MOTION_STATE_NEUTRAL = 0,	// 待機
		MOTION_STATE_MOVE,			// 移動
		MOTION_STATE_KICK_1,		// キック1
		MOTION_STATE_KICK_2,		// キック2
		MOTION_STATE_KICK_3,		// キック3
		MOTION_STATE_CHARGE,		// 突進
		MOTION_STATE_CHARGE_ATTACK,	// 突進攻撃
		MOTION_STATE_DAMAGE,		// ダメージ
		MOTION_STATE_BIG_DAMAGE,	// 吹き飛び
		MOTION_STATE_MAX
	};

	// AIの状態
	enum AI_STATE
	{
		AI_STATE_WAIT = 0,		// 待機状態
		AI_STATE_KICK_1,		// 蹴り1
		AI_STATE_KICK_2,		// 蹴り2
		AI_STATE_KICK_3,		// 蹴り3
		AI_STATE_CHARGE,		// 突進
		AI_STATE_CHARGE_ATTACK,	// 突進攻撃
		AI_STATE_MAX
	};

	CEnemyBoss();
	~CEnemyBoss();

	HRESULT Init(CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEnemyBoss* Create(CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType);

	virtual void HitDamage(int nDamage);

	void SetInit(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nData);

private:

	enum STATE
	{
		STATE_NORMAL = 0,	// 通常状態
		STATE_ATTACK,		// 攻撃状態
		STATE_DAMAGE,		// ダメージ状態
		STATE_BIG_DAMAGE,	// 吹き飛び状態
		STATE_MAX
	};

	// 情報
	struct Info
	{
		STATE state;	// 状態
	};

	// 見た目の情報
	struct InfoVisual
	{
		CCharacter* pCharacter;		// キャラクターのポインタ
		MOTION_STATE motionState;	// モーション状態

		CObj2dGage* pLife2dGage;	// 2Dの体力ゲージ
	};

	// 付属情報
	struct InfoAttach
	{
		CAttack* pAttack;			// 攻撃のポインタ
		int nPartsIdx;				// パーツの番号
	};

	// AIの情報
	struct InfoAi
	{
		AI_STATE state;			// AIの状態情報
		int nCnt;				// AIの状態カウント
		int nCntChange;			// AIの状態カウントの切り替え数

		bool bCombo;			// コンボ継続の有無
	};

	void UpdateVisual(void);
	void UpdateMotion(void);
	void UpdateAi(void);
	void UpdateAttack(void);

	void UpdateDamage(void);
	void UpdateBigDamage(void);

	void AiWait(void);
	void AiKickCombo(void);
	void AiCharge(void);
	void AiChargeAttack(void);

	void SetAiActiv(void);
	void SetCombo(void);
	void SetAttack(int nPartsNum);

	void SetState(MOTION_STATE motionState);
	void ReSetState(void);

	void Debug(void);

	Info m_info;				// 情報
	InfoVisual m_infoVisual;	// 見た目情報
	InfoAttach m_infoAttach;	// 付属情報

	InfoAi m_infoAi;			// AIの情報
};

#endif	// 二重インクルード防止の終了
