
//-===============================================
//-
//-	敵の処理のヘッダー[enemy.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _ENEMY_H_		// このマクロが定義されなかったら
#define _ENEMY_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	前方宣言
//=======================================

class CColl;

//-======================================
//-	クラス定義
//-======================================

// 敵のクラス
class CEnemy : public CObject
{

public:

	CEnemy();
	~CEnemy();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEnemy* Create(void);
	
	virtual void HitDamage(int nDamage);

	void SetInit(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nLife);

	void Damage(int nDamage);
	bool Dead(void);
	void AddDeadNum(void);

	// 前方に移動
	void SetMoveForward(float fSpeed) { m_data.move = D3DXVECTOR3(-sinf(m_data.rot.y) * fSpeed, 0.0f, -cosf(m_data.rot.y) * fSpeed); }

	void SetPos(D3DXVECTOR3 pos) { m_data.pos = pos; }
	D3DXVECTOR3 GetPos(void) { return m_data.pos; }

	void SetPosOld(D3DXVECTOR3 posOld) { m_data.posOld = posOld; }
	D3DXVECTOR3 GetPosOld(void) { return m_data.posOld; }

	void SetRot(D3DXVECTOR3 rot) { m_data.rot = rot; }
	D3DXVECTOR3 GetRot(void) { return m_data.rot; }

	void SetSize(D3DXVECTOR3 size) { m_data.size = size; }
	D3DXVECTOR3 GetSize(void) { return m_data.size; }

	void SetMove(D3DXVECTOR3 move) { m_data.move = move; }
	D3DXVECTOR3 GetMove(void) { return m_data.move; }

	void SetLife(int nLife) { m_data.nLife = nLife; }
	int GetLife(void) { return m_data.nLife; }

	void SetHit(bool bHit) { m_data.bHit = bHit; }
	bool GetHit(void) { return m_data.bHit; }

	D3DXVECTOR3 GetTargetRot(void) { return m_infoTarger.rot; }
	float GetTargetLength(void) { return m_infoTarger.fLength; }

	CColl* GetColl(void) { return m_pColl; }

	void SetIsPhaseTarget(bool bIsPhaseTarget) { m_data.bIsPhaseTarget = bIsPhaseTarget; }
	bool GetIsPhaseTarget(void) { return m_data.bIsPhaseTarget; }

protected:

	void UpdatePos(void);
	void UpdateTargetPlayer(void);
	void UpdateCollision(void);
	void UpdateCollisionPlayer(void);

private:

	// モデル情報
	typedef struct
	{
		D3DXVECTOR3 pos;		// 位置
		D3DXVECTOR3 posOld;		// 前回の位置
		D3DXVECTOR3 rot;		// 向き
		D3DXVECTOR3 size;		// 大きさ

		D3DXVECTOR3 move;		// 移動量

		int nLife;				// 体力
		bool bHit;				// ヒットの有無

		bool bIsPhaseTarget;	// フェーズターゲット

	}Data;

	// ターゲットとの情報
	struct InfoTarget
	{
		D3DXVECTOR3 rot;	// ターゲットへの向き
		float fLength;		// 距離
	};

	Data m_data;				// 情報
	InfoTarget m_infoTarger;	// ターゲットとの情報

	CColl* m_pColl;		// 当たり判定の情報
};

#endif	// 二重インクルード防止の終了
