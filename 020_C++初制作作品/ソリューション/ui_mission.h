
//-===============================================
//-
//-	目標UIの処理のヘッダー[ui_mission.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _UI_MISSION_H_		// このマクロが定義されなかったら
#define _UI_MISSION_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "main.h"

#include "object2d.h"

#include "data.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	クラス定義
//-======================================

class CUiMission : public CObject2d
{

public:

	// 目標UIのテクスチャ列挙型
	typedef enum
	{
		TEX_SEARCH = 0,		// 探索
		TEX_SHOP,			// 購入
		TEX_BATTLE_NORMAL,	// 戦闘（雑魚戦）
		TEX_BATTLE_BOSS,	// 戦闘（ボス戦）
		TEX_MAX
	}TEX;

	CUiMission(int nPriority = 0);
	~CUiMission();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(TEX tex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CUiMission * Create(TEX tex);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	int GetTexNldx(TEX tex);

private:

	void InitSet(void);

	static int m_nTextureNldx[TEX_MAX];		// テクスチャ番号
};

#endif	// 二重インクルード防止の終了
