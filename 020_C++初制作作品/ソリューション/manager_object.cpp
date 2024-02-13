
//-===============================================
//-
//-	オブジェクト管理処理[manager_object.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "manager_object.h"

#include "object3d.h"
#include "obj_3d_field.h"
#include "obj_3d_wall.h"

#include "object_billboard.h"
#include "bullet.h"
#include "effect.h"

#include "object_x.h"
#include "objectx_none.h"
#include "item.h"
#include "enemy_normal.h"
#include "enemy_boss.h"
#include "event_object.h"
#include "garbage.h"
#include "garbage_collect.h"
#include "gate.h"

#include "skybox.h"

#include "obj_3d_wall.h"

#include "player_search.h"
#include "player_battle.h"
#include "player_shop.h"

#include "score.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	静的変数宣言
//-======================================

CObjectXNone *CManagerObject::m_apObjectXNone[OBJECTX_NONE_NUM_MAX] = {};
CEventObject *CManagerObject::m_apEventObject[EVENT_OBJECT_NUM_MAX] = {};
CGarbage *CManagerObject::m_apGarbage[GARBAGE_NUM_MAX] = {};
CGarbageCollect *CManagerObject::m_apGarbageCollect[GARBAGE_COLLECT_NUM_MAX] = {};

CItem *CManagerObject::m_apItem[ITEM_NUM_MAX] = {};
CEnemyNormal *CManagerObject::m_apEnemyNormal[ENEMY_NORMAL_NUM_MAX] = {};
CEnemyBoss *CManagerObject::m_pEnemyBoss = NULL;

CObj3dField *CManagerObject::m_pField[FIELD_NUM_MAX] = {};
CObj3dWall *CManagerObject::m_pWall[WALL_NUM_MAX] = {};

CGate *CManagerObject::m_pGate = NULL;
CSkybox *CManagerObject::m_pSkybox = NULL;

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CManagerObject::CManagerObject()
{
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CManagerObject::~CManagerObject()
{

}

//-------------------------------------
//- オブジェクト管理の初期化処理
//-------------------------------------
HRESULT CManagerObject::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// 全生成処理
	if (FAILED(CreateAll(hWnd)))
	{
		// 初期化処理を抜ける
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- オブジェクト管理の終了処理
//-------------------------------------
void CManagerObject::Uninit(void)
{
	for (int nCount = 0; nCount < OBJECTX_NONE_NUM_MAX; nCount++)
	{
		if (m_apObjectXNone[nCount] != NULL)
		{
			// 効果なしオブジェクトの開放処理
			m_apObjectXNone[nCount]->Uninit();
			m_apObjectXNone[nCount] = NULL;
		}
	}

	for (int nCount = 0; nCount < EVENT_OBJECT_NUM_MAX; nCount++)
	{
		if (m_apEventObject[nCount] != NULL)
		{
			// イベントオブジェクトの開放処理
			m_apEventObject[nCount]->Uninit();
			m_apEventObject[nCount] = NULL;
		}
	}

	for (int nCount = 0; nCount < EVENT_OBJECT_NUM_MAX; nCount++)
	{
		if (m_apGarbage[nCount] != NULL)
		{
			// ゴミの開放処理
			m_apGarbage[nCount]->Uninit();
			m_apGarbage[nCount] = NULL;
		}
	}

	for (int nCount = 0; nCount < EVENT_OBJECT_NUM_MAX; nCount++)
	{
		if (m_apGarbageCollect[nCount] != NULL)
		{
			// ゴミ収集の開放処理
			m_apGarbageCollect[nCount]->Uninit();
			m_apGarbageCollect[nCount] = NULL;
		}

	}
	for (int nCount = 0; nCount < ITEM_NUM_MAX; nCount++)
	{
		if (m_apItem[nCount] != NULL)
		{
			// アイテムの開放処理
			m_apItem[nCount]->Uninit();
			m_apItem[nCount] = NULL;
		}
	}

	for (int nCount = 0; nCount < ENEMY_NORMAL_NUM_MAX; nCount++)
	{
		if (m_apEnemyNormal[nCount] != NULL)
		{
			// 通常敵の開放処理
			m_apEnemyNormal[nCount]->Uninit();
			m_apEnemyNormal[nCount] = NULL;
		}
	}

	// ボスの有無を判定
	if (m_pEnemyBoss != NULL)
	{
		// ボス敵の開放処理
		m_pEnemyBoss->Uninit();
		m_pEnemyBoss = NULL;
	}

	for (int nCount = 0; nCount < FIELD_NUM_MAX; nCount++)
	{
		if (m_pField[nCount] != NULL)
		{
			// フィールドの開放処理
			m_pField[nCount]->Uninit();
			m_pField[nCount] = NULL;
		}
	}

	for (int nCount = 0; nCount < WALL_NUM_MAX; nCount++)
	{
		if (m_pWall[nCount] != NULL)
		{
			// 壁の開放処理
			m_pWall[nCount]->Uninit();
			m_pWall[nCount] = NULL;
		}
	}

	// ゲートの有無を判定
	if (m_pGate != NULL)
	{
		// ゲートの開放処理
		m_pGate->Uninit();
		m_pGate = NULL;
	}

	// スカイボックスの有無を判定
	if (m_pSkybox != NULL)
	{
		// スカイボックスの開放処理
		m_pSkybox->Uninit();
		m_pSkybox = NULL;
	}
}

//-------------------------------------
//- オブジェクト管理の更新処理
//-------------------------------------
void CManagerObject::Update(void)
{

}

//-------------------------------------
//- オブジェクト管理の描画処理
//-------------------------------------
void CManagerObject::Draw(void)
{

}

//-------------------------------------
//-	効果なしオブジェクトの情報を取得
//-------------------------------------
CObjectXNone * CManagerObject::GetObjectNone(int nNum)
{
	// 指定の効果なしオブジェクトのポインタを返す
	return m_apObjectXNone[nNum];
}

//-------------------------------------
//-	効果なしオブジェクトの設定処理
//-------------------------------------
void CManagerObject::SetObjectNone(int nNum, CObjectXNone * pObjectXNone)
{
	// 効果なしオブジェクトのポインタを代入
	m_apObjectXNone[nNum] = pObjectXNone;
}

//-------------------------------------
//-	効果なしオブジェクトの情報を開放処理
//-------------------------------------
void CManagerObject::ReleaseObjectNone(int nNum)
{
	// 効果なしオブジェクトのポインタを初期化
	m_apObjectXNone[nNum] = NULL;
}

//-------------------------------------
//-	イベントオブジェクトの情報を取得
//-------------------------------------
CEventObject * CManagerObject::GetEventObject(int nNum)
{
	// イベントオブジェクトを返す
	return m_apEventObject[nNum];
}

//-------------------------------------
//-	イベントオブジェクトの設定処理
//-------------------------------------
void CManagerObject::SetEventObject(int nNum, CEventObject * pEventObject)
{
	// イベントオブジェクトのポインタを代入
	m_apEventObject[nNum] = pEventObject;
}

//-------------------------------------
//-	イベントオブジェクトの情報を開放処理
//-------------------------------------
void CManagerObject::ReleaseEventObject(int nNum)
{
	// イベントオブジェクトのポインタを初期化
	m_apEnemyNormal[nNum] = NULL;
}

//-------------------------------------
//-	ゴミの情報を取得
//-------------------------------------
CGarbage *CManagerObject::GetGarbage(int nNum)
{
	//ゴミを返す
	return m_apGarbage[nNum];
}

//-------------------------------------
//-	ゴミの設定処理
//-------------------------------------
void CManagerObject::SetGarbage(int nNum, CGarbage *pGarbage)
{
	// ゴミのポインタを代入
	m_apGarbage[nNum] = pGarbage;
}

//-------------------------------------
//-	ゴミの情報を開放処理
//-------------------------------------
void CManagerObject::ReleaseGarbage(int nNum)
{
	// ゴミのポインタを初期化
	m_apGarbage[nNum] = NULL;
}

//-------------------------------------
//-	ゴミ収集の情報を取得
//-------------------------------------
CGarbageCollect *CManagerObject::GetGarbageCollect(int nNum)
{
	//ゴミ収集を返す
	return m_apGarbageCollect[nNum];
}

//-------------------------------------
//-	ゴミ収集の設定処理
//-------------------------------------
void CManagerObject::SetGarbageCollect(int nNum, CGarbageCollect *pGarbageCollect)
{
	// ゴミ収集のポインタを代入
	m_apGarbageCollect[nNum] = pGarbageCollect;
}

//-------------------------------------
//-	ゴミ収集の情報を開放処理
//-------------------------------------
void CManagerObject::ReleaseGarbageCollect(int nNum)
{
	// ゴミ収集のポインタを初期化
	m_apGarbageCollect[nNum] = NULL;
}

//-------------------------------------
//-	アイテムの情報を取得
//-------------------------------------
CItem * CManagerObject::GetItem(int nNum)
{
	// アイテムの情報を返す
	return m_apItem[nNum];
}

//-------------------------------------
//-	アイテムの設定処理
//-------------------------------------
void CManagerObject::SetItem(int nNum, CItem * pItem)
{
	// アイテムの情報をポインタを代入
	m_apItem[nNum] = pItem;
}

//-------------------------------------
//-	アイテムの情報を開放処理
//-------------------------------------
void CManagerObject::ReleaseItem(int nNum)
{
	// アイテムのポインタを初期化
	m_apItem[nNum] = NULL;
}

//-------------------------------------
//-	通常敵の情報を取得
//-------------------------------------
CEnemyNormal * CManagerObject::GetEnemyNormal(int nNum)
{
	// 通常敵の情報を返す
	return m_apEnemyNormal[nNum];
}

//-------------------------------------
//-	通常敵の設定処理
//-------------------------------------
void CManagerObject::SetEnemyNormal(int nNum, CEnemyNormal * pEnemyNormal)
{
	// 通常敵の情報をポインタを代入
	m_apEnemyNormal[nNum] = pEnemyNormal;
}

//-------------------------------------
//-	通常敵の情報を開放処理
//-------------------------------------
void CManagerObject::ReleaseEnemyNormal(int nNum)
{
	// 通常敵のポインタを初期化
	m_apEnemyNormal[nNum] = NULL;
}

//-------------------------------------
//-	ボス敵の情報を取得
//-------------------------------------
CEnemyBoss *CManagerObject::GetEnemyBoss(void)
{
	// ボス敵の情報を返す
	return m_pEnemyBoss;
}

//-------------------------------------
//-	ボス敵の設定処理
//-------------------------------------
void CManagerObject::SetEnemyBoss(CEnemyBoss *pEnemyBoss)
{
	// ボス敵の情報をポインタを代入
	m_pEnemyBoss = pEnemyBoss;
}

//-------------------------------------
//-	ボス敵の情報を開放処理
//-------------------------------------
void CManagerObject::ReleaseEnemyBoss(void)
{
	// ボス敵のポインタを初期化
	m_pEnemyBoss = NULL;
}

//-------------------------------------
//-	ゲートの情報を取得
//-------------------------------------
CGate *CManagerObject::GetGate(void)
{
	// ゲートの情報を返す
	return m_pGate;
}

//-------------------------------------
//-	ゲートの設定処理
//-------------------------------------
void CManagerObject::SetGate(CGate *pGate)
{
	// ゲートの情報をポインタを代入
	m_pGate = pGate;
}

//-------------------------------------
//-	ゲートの情報を開放処理
//-------------------------------------
void CManagerObject::ReleaseGate(void)
{
	// ゲートのポインタを初期化
	m_pGate = NULL;
}

//-------------------------------------
//-	スカイボックスの設定処理
//-------------------------------------
void CManagerObject::SetSkybox(CSkybox *pSkybox)
{
	// スカイボックスの情報をポインタを代入
	m_pSkybox = pSkybox;
}

//-------------------------------------
//-	スカイボックスの情報を取得
//-------------------------------------
CSkybox *CManagerObject::GetSkybox(void)
{
	// スカイボックスの情報を返す
	return m_pSkybox;
}

//-------------------------------------
//-	スカイボックスの情報を開放処理
//-------------------------------------
void CManagerObject::ReleaseSkybox(void)
{
	// スカイボックスのポインタを初期化
	m_pSkybox = NULL;
}

//-------------------------------------
//-	壁の情報を取得
//-------------------------------------
CObj3dWall *CManagerObject::GetWall(int nNum)
{
	// 通常敵の情報を返す
	return m_pWall[nNum];
}

//-------------------------------------
//-	壁の設定処理
//-------------------------------------
void CManagerObject::SetWall(int nNum, CObj3dWall * pWall)
{
	// 通常敵の情報をポインタを代入
	m_pWall[nNum] = pWall;
}

//-------------------------------------
//- オブジェクト管理の全生成処理
//-------------------------------------
HRESULT CManagerObject::CreateAll(HWND hWnd)
{
	int nCount = 0;

	for (int nCut = 0; nCut < 4; nCut++)
	{
		nCount++;

		// フィールドの生成
		m_pField[nCount] = CObj3dField::Create(CObj3dField::TEX_ROAD_000);

		if (m_pField[nCount] == NULL)
		{
			// 失敗メッセージ
			MessageBox(hWnd, "フィールドの生成", "初期処理失敗！", MB_ICONWARNING);

			// 生成処理を抜ける
			return E_FAIL;
		}

		m_pField[nCount]->Set(
			D3DXVECTOR3(-6000.0f + (nCut * 4000.0f), 0.0f, 0.0f),
			D3DXVECTOR3(250.0f, 0.0f, 6250.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	for (int nCut = 0; nCut < 4; nCut++)
	{
		nCount++;

		// フィールドの生成
		m_pField[nCount] = CObj3dField::Create(CObj3dField::TEX_ROAD_000);

		if (m_pField[nCount] == NULL)
		{
			// 失敗メッセージ
			MessageBox(hWnd, "フィールドの生成", "初期処理失敗！", MB_ICONWARNING);

			// 生成処理を抜ける
			return E_FAIL;
		}

		m_pField[nCount]->Set(
			D3DXVECTOR3(0.0f, 0.0f, -6000.0f + ((nCut) * 4000.0f)),
			D3DXVECTOR3(250.0f, 0.0f, 6250.0f),
			D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	}

	for (int nCut1 = 0; nCut1 < 3; nCut1++)
	{
		for (int nCut2 = 0; nCut2 < 3; nCut2++)
		{
			nCount++;

			// フィールドの生成
			m_pField[nCount] = CObj3dField::Create(CObj3dField::TEX_ASPHALT_000);

			if (m_pField[nCount] == NULL)
			{
				// 失敗メッセージ
				MessageBox(hWnd, "フィールドの生成", "初期処理失敗！", MB_ICONWARNING);

				// 生成処理を抜ける
				return E_FAIL;
			}

			m_pField[nCount]->Set(
				D3DXVECTOR3(4000.0f - (4000.0f * nCut1), 0.0f, 4000.0f - (4000.0f * nCut2)),
				D3DXVECTOR3(1750.0f, 0.0f, 1750.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}

	int nCountWall = 0;

	for (int nCut = 0; nCut < 8; nCut++)
	{
		nCountWall++;

		// ウォールの生成
		m_pWall[nCountWall] = CObj3dWall::Create(CObj3dWall::TEX_BLOCKADE_WALL_000);

		if (m_pWall[nCountWall] == NULL)
		{
			// 失敗メッセージ
			MessageBox(hWnd, "ウォールの生成", "初期処理失敗！", MB_ICONWARNING);

			// 生成処理を抜ける
			return E_FAIL;
		}

		m_pWall[nCountWall]->Set(
			D3DXVECTOR3(6250.0f - (6250.0f / 8) - ((6250.0f / 4) * nCut), 150.0f, 6250.0f),
			D3DXVECTOR3(6250.0f / 8, 100.0f, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	for (int nCut = 0; nCut < 8; nCut++)
	{
		nCountWall++;

		// ウォールの生成
		m_pWall[nCountWall] = CObj3dWall::Create(CObj3dWall::TEX_BLOCKADE_WALL_000);

		if (m_pWall[nCountWall] == NULL)
		{
			// 失敗メッセージ
			MessageBox(hWnd, "ウォールの生成", "初期処理失敗！", MB_ICONWARNING);

			// 生成処理を抜ける
			return E_FAIL;
		}

		m_pWall[nCountWall]->Set(
			D3DXVECTOR3(6250.0f - (6250.0f / 8) - ((6250.0f / 4) * nCut), 150.0f, -6250.0f),
			D3DXVECTOR3(6250.0f / 8, 100.0f, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		// 色の透明化
		m_pWall[nCountWall]->m_dataColor.Set(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	}

	for (int nCut = 0; nCut < 8; nCut++)
	{
		nCountWall++;

		// ウォールの生成
		m_pWall[nCountWall] = CObj3dWall::Create(CObj3dWall::TEX_BLOCKADE_WALL_000);

		if (m_pWall[nCountWall] == NULL)
		{
			// 失敗メッセージ
			MessageBox(hWnd, "ウォールの生成", "初期処理失敗！", MB_ICONWARNING);

			// 生成処理を抜ける
			return E_FAIL;
		}

		m_pWall[nCountWall]->Set(
			D3DXVECTOR3(-6250.0f, 150.0f, 6250.0f - (6250.0f / 8) - ((6250.0f / 4) * nCut)),
			D3DXVECTOR3(6250.0f / 8, 100.0f, 0.0f),
			D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));

	}

	for (int nCut = 0; nCut < 8; nCut++)
	{
		nCountWall++;

		// ウォールの生成
		m_pWall[nCountWall] = CObj3dWall::Create(CObj3dWall::TEX_BLOCKADE_WALL_000);

		if (m_pWall[nCountWall] == NULL)
		{
			// 失敗メッセージ
			MessageBox(hWnd, "ウォールの生成", "初期処理失敗！", MB_ICONWARNING);

			// 生成処理を抜ける
			return E_FAIL;
		}

		m_pWall[nCountWall]->Set(
			D3DXVECTOR3(6250.0f, 150.0f, 6250.0f - (6250.0f / 8) - ((6250.0f / 4) * nCut)),
			D3DXVECTOR3(6250.0f / 8, 100.0f, 0.0f),
			D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	}

	// スカイブロックの生成
	m_pSkybox = CSkybox::Create(CSkybox::MODEL_SKYBOX_000);

	if (m_pSkybox == NULL)
	{
		// 失敗メッセージ
		MessageBox(hWnd, "スカイボックスの生成", "初期処理失敗！", MB_ICONWARNING);

		// 生成処理を抜ける
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}