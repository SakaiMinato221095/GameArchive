
//-===============================================
//-
//-	キックのフィニッシュ攻撃処理のヘッダー[finish_kick.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _FINISH_KICK_H_		// このマクロが定義されなかったら
#define _FINISH_KICK_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "attack.h"

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

class CFinishKick : public CAttack
{

public:

	CFinishKick();
	~CFinishKick();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nDamage, CMgrColl::TAG tagTgt);

	static CFinishKick* Create(void);

private:

};

#endif	// 二重インクルード防止の終了
