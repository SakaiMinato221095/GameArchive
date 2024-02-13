
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

#define OBJECTX_NONE_NUM_MAX	(256)	// 効果なしオブジェクトの最大格納数
#define EVENT_OBJECT_NUM_MAX	(256)	// イベントオブジェクトの最大格納数
#define GARBAGE_NUM_MAX			(256)	// ゴミの最大格納数
#define GARBAGE_COLLECT_NUM_MAX	(256)	// ゴミ収集の最大使用数
#define ITEM_NUM_MAX			(256)	// アイテムの最大格納数
#define ENEMY_NORMAL_NUM_MAX	(256)	// 通常敵の最大格納数
#define ENEMY_PIN_NUM_MAX		(256)	// エネミーピンの最大格納数
#define FIELD_NUM_MAX			(64)	// 地面の最大使用数

//-======================================
//-	前方宣言
//-======================================

class CField;

class CObjectXNone;
class CEventObject;
class CGarbage;
class CGarbageCollect;
class CItem;
class CEnemyNormal;
class CEnemyPin;

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

	static CField *GetField(void);

	static CObjectXNone * GetObjectNone(int nNum);
	static void SetObjectNone(int nNum, CObjectXNone *pObjectXNone);
	static CEventObject * GetEventObject(int nNum);
	static void SetEventObject(int nNum, CEventObject *pEventObject);
	static CItem * GetItem(int nNum);
	static void SetGarbage(int nNum, CGarbage *pGarbage);
	static CGarbage * GetGarbage(int nNum);

	static CGarbageCollect * GetGarbageCollect(int nNum);
	static void SetGarbageCollect(int nNum, CGarbageCollect *pGarbageCollect);
	static void ReleaseGarbageCollect(int nNum);

	static void SetItem(int nNum, CItem *pItem);
	static CEnemyNormal * GetEnemyNormal(int nNum);
	static void SetEnemyNormal(int nNum, CEnemyNormal *pEnemyNormal);
	static CEnemyPin * GetEnemyPin(int nNum);
	static void SetEnemyPin(int nNum, CEnemyPin *pEnemyPin);
private:

	HRESULT CreateAll(HWND hWnd);

	static CField *m_pField[FIELD_NUM_MAX];									// フィールド
	static CObjectXNone *m_apObjectXNone[OBJECTX_NONE_NUM_MAX];				// 効果なしオブジェクト
	static CEventObject *m_apEventObject[EVENT_OBJECT_NUM_MAX];				// イベントオブジェクト
	static CGarbage *m_apGarbage[GARBAGE_NUM_MAX];							// ゴミ
	static CGarbageCollect *m_apGarbageCollect[GARBAGE_COLLECT_NUM_MAX];	// ゴミ収集
	static CItem *m_apItem[ITEM_NUM_MAX];									// アイテム
	static CEnemyNormal *m_apEnemyNormal[ENEMY_NORMAL_NUM_MAX];				// 通常敵
	static CEnemyPin *m_apEnemyPin[ENEMY_PIN_NUM_MAX];						// エネミーピン
};

#endif	// 二重インクルード防止の終了
