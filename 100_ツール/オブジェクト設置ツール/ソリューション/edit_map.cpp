
//-===============================================
//-
//-	マップエディタの処理[item.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "edit_map.h"

#include "renderer.h"
#include "manager.h"

#include "Input.h"
#include "debugproc.h"

#include "objectx_none.h"
#include "event_object.h"
#include "garbage.h"
#include "garbage_collect.h"
#include "item.h"
#include "enemy_normal.h"
#include "enemy_pin.h"

#include "file_obj_none.h"
#include "file_evt_obj.h"
#include "file_garbage.h"
#include "file_garbage_collect.h"
#include "file_item.h"
#include "file_emy_nor.h"
#include "file_enemy_pin.h"

#include "manager_object.h"
#include "camera.h"

//-======================================
//-	マクロ定義
//-======================================

#define MAP_EDIT_MOVE_SPEED	(10.0f);

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	マップエディタのコンストラクタ
//-------------------------------------
CEditMap::CEditMap()
{
	// 値クリア
	m_pObject = NULL;
	m_nModelNum = 0;
	m_nModelMax = 0;

	m_typeSelect = TYPE(0);
}

//-------------------------------------
//-	マップエディタのデストラクタ
//-------------------------------------
CEditMap::~CEditMap()
{

}

//-------------------------------------
//- マップエディタの初期化処理（Xファイルオブジェクト設定）
//-------------------------------------
HRESULT CEditMap::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// 初期設定
	m_typeSelect = TYPE_OBJECTX_NONE;	// 選択種類を効果なしオブジェクトに変更

	// 生成処理
	m_pObject = CObjectXNone::Create(CObjectXNone::MODEL(0));

	// モデルの最大数を設定
	m_nModelMax = CObjectXNone::MODEL_MAX;

	// 生成成功の有無を判定
	if (m_pObject == NULL)
	{// 失敗時

		// 処理を抜ける
		return E_FAIL;
	}

	// モデル設定処理
	SetModel();

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- マップエディタの初期化処理
//-------------------------------------
bool CEditMap::Init(void)
{
	// モデル番号を初期化
	m_nModelNum = 0;

	switch (m_typeSelect)
	{
		// 効果なしオブジェクト
	case TYPE_OBJECTX_NONE:

		// 生成処理
		m_pObject = CObjectXNone::Create(CObjectXNone::MODEL(0));

		m_pObject->m_bDataColor.Set(true);

		// モデルの最大数を設定
		m_nModelMax = CObjectXNone::MODEL_MAX;

		break;

		// イベントオブジェクト
	case TYPE_EVENT_OBJECT:

		// 生成処理
		m_pObject = CEventObject::Create(CEventObject::MODEL(0));

		// モデルの最大数を設定
		m_nModelMax = CEventObject::MODEL_MAX;

		break;

		// ゴミ
	case TYPE_GARBAGE:

		// 生成処理
		m_pObject = CGarbage::Create(CGarbage::MODEL(0));

		// モデルの最大数を設定
		m_nModelMax = CGarbage::MODEL_MAX;

		break;

		// ゴミ回収
	case TYPE_GARBAGE_COLLECT:

		// 生成処理
		m_pObject = CGarbageCollect::Create(CGarbageCollect::MODEL(0));

		// モデルの最大数を設定
		m_nModelMax = CGarbageCollect::MODEL_MAX;

		break;

		// イベントオブジェクト
	case TYPE_ITEM:

		// 生成処理
		m_pObject = CItem::Create(CItem::MODEL(0));

		// モデルの最大数を設定
		m_nModelMax = CItem::MODEL_MAX;

		break;

		// 通常敵のオブジェクト
	case TYPE_ENEMY_NORMAL:

		// 生成処理
		m_pObject = CEnemyNormal::Create(CEnemyNormal::MODEL(0));

		// モデルの最大数を設定
		m_nModelMax = CEnemyNormal::MODEL_MAX;

		break;

		// エネミーピンのオブジェクト
	case TYPE_ENEMY_PIN:

		// 生成処理
		m_pObject = CEnemyPin::Create(CEnemyPin::MODEL(0));

		// モデルの最大数を設定
		m_nModelMax = CEnemyPin::MODEL_MAX;

		break;
	}

	// 生成成功の有無を判定
	if (m_pObject == NULL)
	{// 失敗時

		// 処理を抜ける
		return true;
	}

	// モデル設定処理
	SetModel();

	// 成功を返す
	return false;
}

//-------------------------------------
//- マップエディタの終了処理
//-------------------------------------
void CEditMap::Uninit(void)
{

}

//-------------------------------------
//- マップエディタの更新処理
//-------------------------------------
void CEditMap::Update(void)
{
	// 移動処理
	Move();

	// 向き変更処理
	Rot();

	// オブジェクトの情報設定処理
	SetObjectData();

	// モデルの種類切り替え処理
	ChangeModel();

	// 種類を切り替え
	ChangeType();

	// オブジェクト生成
	SetObject();

	// ファイル書き出し処理
	SaveFile();

	// マップエディタ情報の表示
	DrawDebug();
}

//-------------------------------------
//- マップエディタの描画処理
//-------------------------------------
void CEditMap::Draw(void)
{

}

//-------------------------------------
//- マップエディタの生成処理（Xファイルオブジェクト設定）
//-------------------------------------
CEditMap * CEditMap::Create(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// アイテムのポインタを宣言
	CEditMap *pCEditMap = new CEditMap;

	// 生成の成功の有無を判定
	if (pCEditMap != NULL)
	{
		// 初期化処理
		if (FAILED(pCEditMap->Init(hInstance, hWnd, bWindow)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCEditMap == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// アイテムのポインタを返す
	return pCEditMap;
}

//-------------------------------------
//- マップエディタの移動処理
//-------------------------------------
void CEditMap::Move(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

		// 移動処理を抜ける
		return;
	}

	// カメラの情報を取得
	CCamera *pCamera = CManager::GetCamera();

	// カメラ取得の有無を判定
	if (pCamera == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();		// 位置
	D3DXVECTOR3 move = m_dataMove.Get();	// 移動量

	// 変数宣言（カメラの情報取得）
	D3DXVECTOR3 rotCamera = pCamera->m_dataRot.Get();	// カメラの向き

	// キーボードの入力判定 if（Wキーの入力）
	if (pInputKeyboard->GetPress(DIK_W) == true)
	{
		// キーボードの入力判定 if（Aキーの入力）
		if (pInputKeyboard->GetPress(DIK_A) == true)
		{
			// 左上移動
			move.x -= sinf((D3DX_PI * 0.75f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
			move.z -= cosf((D3DX_PI * 0.75f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
		}
		// キーボードの入力判定 if（Aキーの入力）
		else if (pInputKeyboard->GetPress(DIK_D) == true)
		{
			// 右上移動
			move.x += sinf((D3DX_PI * 0.25f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
			move.z += cosf((D3DX_PI * 0.25f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
		}
		// Wキー以外の入力なし
		else
		{
			// 上移動
			move.x += sinf((D3DX_PI * 0.0f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
			move.z += cosf((D3DX_PI * 0.0f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
		}
	}
	// キーボードの入力判定 if（Sキーの入力）
	else if (pInputKeyboard->GetPress(DIK_S) == true)
	{
		// キーボードの入力判定 if（Aキーの入力）
		if (pInputKeyboard->GetPress(DIK_A) == true)
		{
			// 左下移動
			move.x -= sinf((D3DX_PI * 0.25f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
			move.z -= cosf((D3DX_PI * 0.25f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
		}
		// キーボードの入力判定 if（Dキーの入力）
		else if (pInputKeyboard->GetPress(DIK_D) == true)
		{
			// 右下移動
			move.x += sinf((D3DX_PI * 0.75f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
			move.z += cosf((D3DX_PI * 0.75f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
		}
		// Sキー以外の入力なし
		else
		{
			// 下移動
			move.x += sinf((D3DX_PI * 1.0f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
			move.z += cosf((D3DX_PI * 1.0f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
		}
	}
	// キーボードの入力判定 if（Aキーの入力）
	else if (pInputKeyboard->GetPress(DIK_A) == true)
	{
		// 左移動
		move.x -= sinf((D3DX_PI * 0.5f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
		move.z -= cosf((D3DX_PI * 0.5f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
	}
	// キーボードの入力判定 if（Dキーの入力）
	else if (pInputKeyboard->GetPress(DIK_D) == true)
	{
		// 右移動
		move.x += sinf((D3DX_PI * 0.5f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
		move.z += cosf((D3DX_PI * 0.5f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
	}

	if (pInputKeyboard->GetPress(DIK_LSHIFT) == true)
	{
		// キーボードの入力判定 if（Aキーの入力）
		if (pInputKeyboard->GetTrigger(DIK_R) == true)
		{
			// 左移動
			move.y += 100.0f;
		}
		// キーボードの入力判定 if（Dキーの入力）
		else if (pInputKeyboard->GetTrigger(DIK_F) == true)
		{
			// 右移動
			move.y -= 100.0f;
		}
	}

	// 移動量の減数
	if (pInputKeyboard->GetPress(DIK_LSHIFT) == true)
	{
		move *= 0.1f;
	}

	// 位置情報に移動量を加算
	pos += move;

	// 移動量を減衰
	move.x += (0.0f - move.x) * 0.7f;
	move.y += (0.0f - move.y) * 0.7f;
	move.z += (0.0f - move.z) * 0.7f;

	// 情報更新
	m_dataPos.Set(pos);		// 位置
	m_dataMove.Set(move);	// 移動量
}

//-------------------------------------
//- マップエディタの向き変更処理
//-------------------------------------
void CEditMap::Rot(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

		// 移動処理を抜ける
		return;
	}

	// 変数宣言（情報取得）
	D3DXVECTOR3 rot = m_dataRot.Get();		// 向き

	// キーボードの入力判定 if（Rキーの入力）
	if (pInputKeyboard->GetTrigger(DIK_T) == true)
	{
		// 36度向きを加算
		rot.y += D3DX_PI * 0.1f;
	}
	// キーボードの入力判定 if（Fキーの入力）
	else if (pInputKeyboard->GetTrigger(DIK_G) == true)
	{
		// 36度向きを減算
		rot.y -= D3DX_PI * 0.1f;
	}

	//角度の修正
	if (rot.y > D3DX_PI)
	{
		rot.y = (-D3DX_PI);
	}
	else if (rot.y < -D3DX_PI)
	{
		rot.y = (D3DX_PI);
	}

	// 情報更新
	m_dataRot.Set(rot);		// 向き
}

//-------------------------------------
//- マップエディタの位置を代入処理
//-------------------------------------
void CEditMap::SetObjectData(void)
{
	// 効果なしオブジェクトの位置を代入
	m_pObject->m_dataPos.Set(m_dataPos.Get());
	m_pObject->m_dataRot.Set(m_dataRot.Get());
}

//-------------------------------------
//- マップエディタのモデル切り替え処理
//-------------------------------------
void CEditMap::ChangeModel(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

		// 移動処理を抜ける
		return;
	}

	if (pInputKeyboard->GetTrigger(DIK_TAB) == true &&
		pInputKeyboard->GetPress(DIK_LSHIFT) == true)
	{
		// モデル番号を加算
		m_nModelNum--;

		// モデル番号が最大数と同じとき
		if (m_nModelNum < 0)
		{
			// モデル番号を初期化
			m_nModelNum = m_nModelMax - 1;
		}

		// モデル設定
		SetModel();
	}
	// 入力の判定 if(TABキー)
	else if (pInputKeyboard->GetTrigger(DIK_TAB) == true)
	{
		// モデル番号を加算
		m_nModelNum++;

		// モデル番号が最大数と同じとき
		if (m_nModelNum == m_nModelMax)
		{
			// モデル番号を初期化
			m_nModelNum = 0;
		}

		// モデル設定
		SetModel();
	}


}

//-------------------------------------
//- マップエディタの種類切り替え処理
//-------------------------------------
void CEditMap::ChangeType(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

		// 移動処理を抜ける
		return;
	}

	// 入力の判定 if(LCONTROLキー)
	if (pInputKeyboard->GetTrigger(DIK_LCONTROL) == true)
	{
		// 種類を加算
		m_typeSelect = (TYPE)(m_typeSelect + 1);

		if (m_typeSelect == TYPE_MAX)
		{
			// 種類を初期化
			m_typeSelect = (TYPE)(0);
		}

		// 終了処理
		m_pObject->Uninit();
		m_pObject = NULL;

		// 切り替えた種類の初期化処理 if(成功の有無を判定)
		if (Init() == true)
		{
			return;
		}

		// 位置情報を代入
		SetObjectData();
	}
}

//-------------------------------------
//- マップエディタの設定処理
//-------------------------------------
void CEditMap::SetObject(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

		// 移動処理を抜ける
		return;
	}

	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();		// 位置
	D3DXVECTOR3 rot = m_dataRot.Get();		// 向き

	// 入力の判定 if(スペースキー)
	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true)
	{
		switch (m_typeSelect)
		{
			// 効果なしオブジェクト
		case TYPE_OBJECTX_NONE:

			for (int nCount = 0; nCount < OBJECTX_NONE_NUM_MAX; nCount++)
			{
				// 効果なしオブジェクトの有無を判定
				if (CManagerObject::GetObjectNone(nCount) == NULL)
				{
					// 効果なしオブジェクトを生成
					CObjectXNone *pObjectXNone = CObjectXNone::Create((CObjectXNone::MODEL)m_nModelNum);

					// 効果なしオブジェクトの設定
					pObjectXNone->Set(
						pos,
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						rot);

					// オブジェクトのポインタを代入
					CManagerObject::SetObjectNone(nCount, pObjectXNone);

					break;
				}
			}

			break;

			// イベントオブジェクト
		case TYPE_EVENT_OBJECT:

			for (int nCount = 0; nCount < EVENT_OBJECT_NUM_MAX; nCount++)
			{
				// イベントオブジェクトの有無を判定
				if (CManagerObject::GetEventObject(nCount) == NULL)
				{
					// イベントオブジェクトを生成
					CEventObject *pEventObject = CEventObject::Create((CEventObject::MODEL)m_nModelNum);

					// イベントオブジェクトの設定
					pEventObject->Set(
						pos,
						rot);

					// オブジェクトのポインタを代入
					CManagerObject::SetEventObject(nCount, pEventObject);

					break;
				}
			}

			break;

			// ゴミ
		case TYPE_GARBAGE:

			for (int nCount = 0; nCount < GARBAGE_NUM_MAX; nCount++)
			{
				// イベントオブジェクトの有無を判定
				if (CManagerObject::GetGarbage(nCount) == NULL)
				{
					// イベントオブジェクトを生成
					CGarbage *pGarbage = CGarbage::Create((CGarbage::MODEL)m_nModelNum);

					// イベントオブジェクトの設定
					pGarbage->Set(
						pos,
						rot);

					// オブジェクトのポインタを代入
					CManagerObject::SetGarbage(nCount, pGarbage);

					break;
				}
			}

			break;

			// ゴミ
		case TYPE_GARBAGE_COLLECT:

			for (int nCount = 0; nCount < GARBAGE_COLLECT_NUM_MAX; nCount++)
			{
				// イベントオブジェクトの有無を判定
				if (CManagerObject::GetGarbageCollect(nCount) == NULL)
				{
					// イベントオブジェクトを生成
					CGarbageCollect *pGarbageCollect = CGarbageCollect::Create((CGarbageCollect::MODEL)m_nModelNum);

					// イベントオブジェクトの設定
					pGarbageCollect->Set(
						pos,
						rot);

					// オブジェクトのポインタを代入
					CManagerObject::SetGarbageCollect(nCount, pGarbageCollect);

					break;
				}
			}

			break;

			// アイテム
		case TYPE_ITEM:

			for (int nCount = 0; nCount < EVENT_OBJECT_NUM_MAX; nCount++)
			{
				// イベントオブジェクトの有無を判定
				if (CManagerObject::GetItem(nCount) == NULL)
				{
					// イベントオブジェクトを生成
					CItem *pItem = CItem::Create((CItem::MODEL)m_nModelNum);

					// イベントオブジェクトの設定
					pItem->Set(
						pos,
						rot);

					// オブジェクトのポインタを代入
					CManagerObject::SetItem(nCount, pItem);

					break;
				}
			}

			break;

			// 通常敵
		case TYPE_ENEMY_NORMAL:

			for (int nCount = 0; nCount < EVENT_OBJECT_NUM_MAX; nCount++)
			{
				// 通常敵の有無を判定
				if (CManagerObject::GetEnemyNormal(nCount) == NULL)
				{
					// 通常敵を生成
					CEnemyNormal *pEnemyNormal = CEnemyNormal::Create((CEnemyNormal::MODEL)m_nModelNum);

					// 通常敵の設定
					pEnemyNormal->Set(
						pos,
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						rot,
						0);

					// 通常敵のポインタを代入
					CManagerObject::SetEnemyNormal(nCount, pEnemyNormal);

					break;
				}
			}

			break;

			// エネミーピン
		case TYPE_ENEMY_PIN:

			for (int nCount = 0; nCount < EVENT_OBJECT_NUM_MAX; nCount++)
			{
				// 通常敵の有無を判定
				if (CManagerObject::GetEnemyPin(nCount) == NULL)
				{
					// 通常敵を生成
					CEnemyPin *pEnemyPin = CEnemyPin::Create((CEnemyPin::MODEL)m_nModelNum);

					// 通常敵の設定
					pEnemyPin->Set(
						pos,
						rot);

					// 通常敵のポインタを代入
					CManagerObject::SetEnemyPin(nCount, pEnemyPin);

					break;
				}
			}

			break;
		}
	}

}

//-------------------------------------
//- マップエディタのモデル設定処理
//-------------------------------------
void CEditMap::SetModel(void)
{
	// 変数宣言
	int nModelNldx = 0;	// モデル番号

	switch (m_typeSelect)
	{
		// 効果なしオブジェクト
	case TYPE_OBJECTX_NONE:

		// モデル番号を取得
		nModelNldx = CObjectXNone::m_nDataModelNldx[m_nModelNum].Get();

		break;

		// イベントオブジェクト
	case TYPE_EVENT_OBJECT:

		// モデル番号を取得
		nModelNldx = CEventObject::m_nDataModelNldx[m_nModelNum].Get();

		break;

		// ゴミオブジェクト
	case TYPE_GARBAGE:

		// モデル番号を取得
		nModelNldx = CGarbage::m_nDataModelNldx[m_nModelNum].Get();

		break;

		// ゴミ回収オブジェクト
	case TYPE_GARBAGE_COLLECT:

		// モデル番号を取得
		nModelNldx = CGarbageCollect::m_nDataModelNldx[m_nModelNum].Get();


		break;
		// アイテムオブジェクト
	case TYPE_ITEM:

		// モデル番号を取得
		nModelNldx = CItem::m_nDataModelNldx[m_nModelNum].Get();

		break;

		// 通常敵
	case TYPE_ENEMY_NORMAL:

		// モデル番号を取得
		nModelNldx = CEnemyNormal::m_nDataModelNldx[m_nModelNum].Get();

		break;

		// エネミーピン
	case TYPE_ENEMY_PIN:

		// モデル番号を取得
		nModelNldx = CEnemyPin::m_nDataModelNldx[m_nModelNum].Get();

		break;
	}

	// モデル割当
	m_pObject->BindModel(nModelNldx, m_nModelNum);
}

//-------------------------------------
//- マップエディタのファイル書き出し処理
//-------------------------------------
void CEditMap::SaveFile(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

		// 移動処理を抜ける
		return;
	}

	// 入力の判定 if(F5キー)
	if (pInputKeyboard->GetTrigger(DIK_F5) == true)
	{
		switch (m_typeSelect)
		{
		case TYPE_OBJECTX_NONE:

			// 効果なしオブジェクト書き出し処理
			CFileObjNone::Save(CFileObjNone::TXT_NORMAL_000);

			break;

		case TYPE_EVENT_OBJECT:

			// イベントオブジェクト書き出し処理
			CFileEvtObj::Save(CFileEvtObj::TXT_NORMAL_000);

			break;

		case TYPE_GARBAGE:

			// ゴミ書き出し処理
			CFileGarbage::Save(CFileGarbage::TXT_NORMAL_000);

			break;

		case TYPE_GARBAGE_COLLECT:

			// ゴミ書き出し処理
			CFileGarbageCollect::Save(CFileGarbageCollect::TXT_NORMAL_000);

			break;

		case TYPE_ITEM:

			// アイテム書き出し処理
			CFileItem::Save(CFileItem::TXT_NORMAL_000);

			break;

		case TYPE_ENEMY_NORMAL:

			// 通常敵書き出し処理
			CFileEmyNor::Save(CFileEmyNor::TXT_NORMAL_000);

			break;

		case TYPE_ENEMY_PIN:

			// 通常敵書き出し処理
			CFileEnemyPin::Save(CFileEnemyPin::TXT_ENEMY_PIN_000);

			break;
		}

	}
}

//-------------------------------------
//- マップエディタのデバック表示
//-------------------------------------
void CEditMap::DrawDebug(void)
{
	// デバックプロックの取得
	CDebugProc *pDebugProc = CManager::GetDbugProc();

	// デバックプロック取得の有無を判定
	if (pDebugProc == NULL)
	{
		return;
	}

	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();	// 位置
	D3DXVECTOR3 rot = m_dataRot.Get();	// 向き

	//見出し
	pDebugProc->Print(" ----- マップエディタの情報 -----");
	pDebugProc->Print("\n");

	// 情報表示
	pDebugProc->Print(" 位置情報 : %f %f %f", pos.x, pos.y, pos.z);
	pDebugProc->Print("\n");

	pDebugProc->Print(" 向き情報 : %f %f %f", rot.x, rot.y, rot.z);
	pDebugProc->Print("\n");

	switch (m_typeSelect)
	{
	case TYPE_OBJECTX_NONE:

		pDebugProc->Print(" 種類情報 [効果なしオブジェクト]");
		pDebugProc->Print("\n");

		break;

	case TYPE_EVENT_OBJECT:

		pDebugProc->Print(" 種類情報 [イベントオブジェクト]");
		pDebugProc->Print("\n");

		break;

	case TYPE_GARBAGE:

		pDebugProc->Print(" 種類情報 [ゴミ]");
		pDebugProc->Print("\n");

		break;

	case TYPE_GARBAGE_COLLECT:

		pDebugProc->Print(" 種類情報 [ゴミ回収]");
		pDebugProc->Print("\n");

		break;

	case TYPE_ITEM:

		pDebugProc->Print(" 種類情報 [アイテム]");
		pDebugProc->Print("\n");

		break;

	case TYPE_ENEMY_NORMAL:

		pDebugProc->Print(" 種類情報 [通常敵]");
		pDebugProc->Print("\n");

		break;

	case TYPE_ENEMY_PIN:

		pDebugProc->Print(" 種類情報 [エネミーピン]");
		pDebugProc->Print("\n");

		break;
	}

	pDebugProc->Print(" モデル番号 : %d", m_nModelNum);
	pDebugProc->Print("\n");

	//見出し
	pDebugProc->Print("\n");
	pDebugProc->Print(" ----- 操作情報 -----");
	pDebugProc->Print("\n");

	pDebugProc->Print(" 移動 : WASDキー");
	pDebugProc->Print("\n");
	pDebugProc->Print("  + 減衰移動 : LSHIFTキー");
	pDebugProc->Print("\n");
	pDebugProc->Print(" 上下移動 : LSHIFT + RFキー");
	pDebugProc->Print("\n");
	pDebugProc->Print(" 向き変更（15度） : TGキー");
	pDebugProc->Print("\n");
	pDebugProc->Print(" モデルの種類変更 : TABキー");
	pDebugProc->Print("\n");
	pDebugProc->Print(" オブジェクトカテゴリ種類変更 : LCONTROLキー");
	pDebugProc->Print("\n");
	pDebugProc->Print(" 設置 : SPACEキー");
	pDebugProc->Print("\n");
	pDebugProc->Print(" 保存 : F5キー");
	pDebugProc->Print("\n");
}