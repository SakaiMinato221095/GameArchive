
//-===============================================
//-
//-	攻撃の処理のヘッダー[attack.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _ATTACK_H_		// このマクロが定義されなかったら
#define _ATTACK_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object.h"

#include "mgr_coll.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//=	前方宣言
//=======================================

class CColl;

//-======================================
//-	クラス定義
//-======================================

class CAttack : public CObject
{

public:

	// 情報値
	typedef struct
	{
		D3DXVECTOR3 pos;		// 位置
		D3DXVECTOR3 size;		// 大きさ

		D3DXVECTOR3 posPlus;	// 追加位置

		int nDamage;			// ダメージ

		CMgrColl::TAG tagTgt;	// ターゲットのタグ
	}Info;

	CAttack();
	virtual ~CAttack();

	HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nDamage, CMgrColl::TAG tagTgt);

	static CAttack* Create(void);

	void UpdateHit(void);

	void Debug(void);

	void UpdateData(D3DXVECTOR3 pos, D3DXVECTOR3 size) { m_info.pos = pos, m_info.size = size; }

	CColl* GetColl(void) { return m_pColl; }

	D3DXVECTOR3 GetPos(void) { return m_info.pos; }
	D3DXVECTOR3 GetSize(void) { return m_info.size; }

	void SetPosPlus(D3DXVECTOR3 posPlus) { m_info.posPlus = posPlus; }
	D3DXVECTOR3 GetPosPlus(void) { return m_info.posPlus; }

	void SetDamage(int nDamage) { m_info.nDamage = nDamage; }
	int GetDamage(void) { return m_info.nDamage; }

	void SetTagTgt(CMgrColl::TAG tagTgt) { m_info.tagTgt = tagTgt; }
	CMgrColl::TAG GetTagTgt(void) { return m_info.tagTgt; }

private:

	Info m_info;			// 値情報

	CColl* m_pColl;			// 当たり判定の情報
};

#endif	// 二重インクルード防止の終了
