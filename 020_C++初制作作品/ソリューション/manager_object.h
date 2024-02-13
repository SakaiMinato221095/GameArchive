
//-===============================================
//-
//-	オブジェクト管理処理のヘッダー[manager_object.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _MANAGER_OBJECT_H_		// このマクロが定義されなかったら
#define _MANAGER_OBJECT_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "data.h"

//-======================================
//-	マクロ定義
//-======================================

#define FIELD_NUM_MAX			(64)	// 地面の最大使用数
#define WALL_NUM_MAX			(64)	// 壁の最大使用数
#define OBJECTX_NONE_NUM_MAX	(512)	// 効果なしオブジェクトの最大使用数
#define EVENT_OBJECT_NUM_MAX	(512)	// イベントオブジェクトの最大使用数
#define GARBAGE_NUM_MAX			(512)	// ゴミの最大使用数
#define GARBAGE_COLLECT_NUM_MAX	(512)	// ゴミ収集の最大使用数
#define ITEM_NUM_MAX			(512)	// アイテムの最大数
#define ENEMY_NORMAL_NUM_MAX	(512)	// 通常敵の最大格納数

//-======================================
//-	前方宣言
//-======================================

class CBgManager;

class CObjectXNone;
class CEventObject;
class CGarbage;
class CGarbageCollect;
class CItem;
class CEnemyNormal;
class CEnemyBoss;
class CObj3dField;
class CObj3dWall;
class CGate;
class CSkybox;

//-======================================
//-	クラス定義
//-======================================

class CManagerObject
{

public:

	CManagerObject();
	virtual ~CManagerObject();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjectXNone * GetObjectNone(int nNum);
	static void SetObjectNone(int nNum, CObjectXNone *pObjectXNone);
	static void ReleaseObjectNone(int nNum);

	static CEventObject * GetEventObject(int nNum);
	static void SetEventObject(int nNum, CEventObject *pEventObject);
	static void ReleaseEventObject(int nNum);

	static CGarbage * GetGarbage(int nNum);
	static void SetGarbage(int nNum, CGarbage * pGarbage);
	static void ReleaseGarbage(int nNum);

	static CGarbageCollect * GetGarbageCollect(int nNum);
	static void SetGarbageCollect(int nNum, CGarbageCollect *pGarbageCollect);
	static void ReleaseGarbageCollect(int nNum);

	static CItem * GetItem(int nNum);
	static void SetItem(int nNum, CItem *pItem);
	static void ReleaseItem(int nNum);

	static void SetEnemyNormal(int nNum, CEnemyNormal *pEnemyNormal);
	static CEnemyNormal * GetEnemyNormal(int nNum);
	static void ReleaseEnemyNormal(int nNum);

	static void SetEnemyBoss(CEnemyBoss *pEnemyBoss);
	static CEnemyBoss * GetEnemyBoss(void);
	static void ReleaseEnemyBoss(void);

	static void SetGate(CGate *pGate);
	static CGate * GetGate(void);
	static void ReleaseGate(void);

	static void SetSkybox(CSkybox *pSkybox);
	static CSkybox *GetSkybox(void);
	static void ReleaseSkybox(void);

	static CObj3dWall * GetWall(int nNum);
	static void SetWall(int nNum, CObj3dWall * pWall);

private:

	HRESULT CreateAll(HWND hWnd);

	static CObjectXNone *m_apObjectXNone[OBJECTX_NONE_NUM_MAX];				// 効果なしオブジェクト
	static CEventObject *m_apEventObject[EVENT_OBJECT_NUM_MAX];				// イベントオブジェクト
	static CGarbage *m_apGarbage[GARBAGE_NUM_MAX];							// ゴミ
	static CGarbageCollect *m_apGarbageCollect[GARBAGE_COLLECT_NUM_MAX];	// ゴミ収集
	static CItem *m_apItem[ITEM_NUM_MAX];									// アイテム
	static CEnemyNormal *m_apEnemyNormal[ENEMY_NORMAL_NUM_MAX];				// 通常敵
	static CEnemyBoss *m_pEnemyBoss;										// ボス敵

	static CObj3dField *m_pField[FIELD_NUM_MAX];							// フィールド
	static CObj3dWall *m_pWall[WALL_NUM_MAX];								// ウォール

	static CGate *m_pGate;													// ゲート
	static CSkybox *m_pSkybox;												// スカイボックス

};

#endif	// 二重インクルード防止の終了
