
//-===============================================
//-
//-	フェーズ管理の処理のヘッダー[phase_manager.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _PHASE_MANAGER_H_		// このマクロが定義されなかったら
#define _PHASE_MANAGER_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	コンスト定義
//=======================================

//=======================================
//=	前方宣言
//=======================================

class CColl;
class CObj3dWall;

//-======================================
//-	クラス定義
//-======================================

class CPhaseManager
{

public:

	enum TYPE_PHASE
	{
		TYPE_PHASE_ONE = 0,		// フェーズ1
		TYPE_PHASE_TWO,			// フェーズ2
		TYPE_PHASE_THREE,		// フェーズ3
		TYPE_PHASE_COMP,		// コンプリート
		TYPE_PHASE_MAX
	};

	CPhaseManager(int nPriority);
	~CPhaseManager();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void AddDeadEnemy(void);

	static CPhaseManager* Create(void);
	
	void SetTargetCompNum(int nTargetCompNum) { m_info.nTargetCompNum = nTargetCompNum; }

	TYPE_PHASE GetTypePhase(void) { return m_info.typePhaseNew; }
	

private:

	void SetComp(void);

	struct Info
	{
		int nTargetCompNum;			// ターゲットの最大数
		int nTargetCompCnt;			// ターゲットの撃破数
		TYPE_PHASE typePhaseNew;	// 現在のフェーズ
	};

	Info m_info;

};

#endif	// 二重インクルード防止の終了
