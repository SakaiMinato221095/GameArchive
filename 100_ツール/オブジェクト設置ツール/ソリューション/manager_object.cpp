
//-===============================================
//-
//-	オブジェクト管理処理[manager.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "manager_object.h"

#include "object2d.h"

#include "object3d.h"
#include "field.h"

#include "object_billboard.h"

#include "object_x.h"

#include "objectx_none.h"
#include "event_object.h"
#include "garbage.h"
#include "garbage_collect.h"
#include "item.h"
#include "enemy_normal.h"

#include "objectx_test.h"

#include "file_obj_none.h"
#include "file_evt_obj.h"
#include "file_garbage.h"
#include "file_garbage_collect.h"
#include "file_emy_nor.h"
#include "file_enemy_pin.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	静的変数宣言
//-======================================

CField *CManagerObject::m_pField[FIELD_NUM_MAX] = {};
CObjectXNone *CManagerObject::m_apObjectXNone[OBJECTX_NONE_NUM_MAX] = {};
CEventObject *CManagerObject::m_apEventObject[EVENT_OBJECT_NUM_MAX] = {};
CGarbage *CManagerObject::m_apGarbage[GARBAGE_NUM_MAX] = {};
CGarbageCollect *CManagerObject::m_apGarbageCollect[GARBAGE_COLLECT_NUM_MAX] = {};
CItem *CManagerObject::m_apItem[ITEM_NUM_MAX] = {};
CEnemyNormal *CManagerObject::m_apEnemyNormal[ENEMY_NORMAL_NUM_MAX] = {};
CEnemyPin *CManagerObject::m_apEnemyPin[ENEMY_PIN_NUM_MAX] = {};

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
//-	フィールドの情報を取得
//-------------------------------------
CField *CManagerObject::GetField(void)
{
	// フィールドのポインタを返す
	return NULL;
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
	// 効果なしオブジェクトのポインタを代入
	m_apEventObject[nNum] = pEventObject;
}

//-------------------------------------
//-	イベントオブジェクトの設定処理
//-------------------------------------
void CManagerObject::SetGarbage(int nNum, CGarbage * pGarbage)
{
	// 効果なしオブジェクトのポインタを代入
	m_apGarbage[nNum] = pGarbage;
}

//-------------------------------------
//-	イベントオブジェクトの情報を取得
//-------------------------------------
CGarbage *CManagerObject::GetGarbage(int nNum)
{
	// イベントオブジェクトを返す
	return m_apGarbage[nNum];
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
//-	エネミーピンの情報を取得
//-------------------------------------
CEnemyPin *CManagerObject::GetEnemyPin(int nNum)
{
	// 通常敵の情報を返す
	return m_apEnemyPin[nNum];
}

//-------------------------------------
//-	エネミーピンの設定処理
//-------------------------------------
void CManagerObject::SetEnemyPin(int nNum, CEnemyPin * pEnemyPin)
{
	// 通常敵の情報をポインタを代入
	m_apEnemyPin[nNum] = pEnemyPin;
}

//-------------------------------------
//- オブジェクト管理の全生成処理
//-------------------------------------
HRESULT CManagerObject::CreateAll(HWND hWnd)
{
	////フィールド
	//for (int nColumn = 0; nColumn < 4; nColumn++)
	//{
	//	for (int nRow = 0; nRow < 4; nRow++)
	//	{
	//		if (m_pField[nColumn + (nRow * 4)] == NULL)
	//		{
	//			// フィールドの生成
	//			m_pField[nColumn + (nRow * 4)] = CField::Create(CField::TEX_WHITE_TILE_000);

	//			if (m_pField[nColumn + (nRow * 4)] == NULL)
	//			{
	//				// 失敗メッセージ
	//				MessageBox(hWnd, "フィールドの生成", "初期処理失敗！", MB_ICONWARNING);

	//				// 生成処理を抜ける
	//				return E_FAIL;
	//			}

	//			m_pField[nColumn + (nRow * 4)]->Set(
	//				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	//				D3DXVECTOR3(-2000.0f + (2000.0f * nColumn), 0.0f, -2000.0f + (2000.0f * nRow)),
	//				D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//		}
	//	}
	//}

	int nCount = 0;

	for (int nCut = 0; nCut < 4; nCut++)
	{
		nCount++;

		// フィールドの生成
		m_pField[nCount] = CField::Create(CField::TEX_ROAD_000);

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
		m_pField[nCount] = CField::Create(CField::TEX_ROAD_000);

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
			m_pField[nCount] = CField::Create(CField::TEX_ASPHALT_000);

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


	// テストの生成
	CObjectXTest *m_pObjectTest = CObjectXTest::Create(CObjectXTest::MODEL_HUMAN_BOX_000);

	// 効果なしオブジェクト読み込み設定処理
	CFileObjNone::Load(CFileObjNone::TXT_NORMAL_000);

	// イベントオブジェクト読み込み設定処理
	CFileEvtObj::Load(CFileEvtObj::TXT_NORMAL_000);

	// ゴミオブジェクト読み込み設定処理
	CFileGarbage::Load(CFileGarbage::TXT_NORMAL_000);

	// ゴミ回収オブジェクト読み込み設定処理
	CFileGarbageCollect::Load(CFileGarbageCollect::TXT_NORMAL_000);

	// 敵の読み込み設定処理
	CFileEmyNor::Load(CFileEmyNor::TXT_NORMAL_000);

	// エネミーピンの読み込み設定処理
	CFileEnemyPin::Load(CFileEnemyPin::TXT_ENEMY_PIN_000);

	// 成功を返す
	return S_OK;
}