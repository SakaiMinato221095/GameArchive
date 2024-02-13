
//-===============================================
//-
//-	オブジェクト処理[object.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "object.h"

#include "manager.h"
#include "debugproc.h"

#include "Input.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	静的変数宣言
//-======================================

int CObject::m_nNumAll = 0;
bool CObject::m_bIsUpdateAllStop = false;

CObject* CObject::m_apTop[OBJECT_PRIORITY_MAX] = {};
CObject* CObject::m_apCur[OBJECT_PRIORITY_MAX] = {};

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CObject::CObject(int nPriority)
{
	CObject* pObject = m_apTop[nPriority];

	if (pObject != nullptr)
	{
		while (pObject != nullptr)
		{
			CObject* pObjectNext = pObject->m_pNext;

			if (pObjectNext == nullptr)
			{
				// 最後尾ポインタを更新
				pObject->m_pNext = this;
				pObject->m_pNext->m_pNext = nullptr;
				pObject->m_pNext->m_pPrev = pObject;
				m_apCur[nPriority] = this;

				m_nNumAll++;

				break;
			}
			else
			{
				pObject = pObjectNext;
			}
		}
	}
	else
	{
		m_apTop[nPriority] = this;

		m_pPrev = nullptr;		// 前のオブジェクトへのポインタ
		m_pNext = nullptr;		// 次のオブジェクトへのポインタ

		m_nNumAll++;
	}

	m_nPriority = nPriority;	// 自身の優先順位を保存
	m_bIsUpdateStop = false;	// 更新の有無
	m_bIsUpdatePause = false;	// ポーズの更新の有無
	m_bIsDrawStop = false;		// 描画の有無
	m_bIsDeath = false;			// 死亡の有無
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CObject::~CObject()
{
}

//-------------------------------------
//-	全開放処理
//-------------------------------------
void CObject::ReleaseAll(void)
{
	for (int nCount = 0; nCount < OBJECT_PRIORITY_MAX; nCount++)
	{
		// 先頭のオブジェクトポインタを代入
		CObject* pObject = m_apTop[nCount];

		while (pObject != nullptr)
		{
			CObject* pObjectNext = pObject->m_pNext;

			// オブジェクトの更新処理
			pObject->Uninit();

			// 次のオブジェクトを代入
			pObject = pObjectNext;
		}
	}

	// 全死亡フラグ確認開放処理
	DeathAllCheckRelease();
}

//-------------------------------------
//-	全更新処理
//-------------------------------------
void CObject::UpdateAll(void)
{
	for (int nCount = 0; nCount < OBJECT_PRIORITY_MAX; nCount++)
	{
		// 先頭のオブジェクトポインタを代入
		CObject* pObject = m_apTop[nCount];

		while (pObject != nullptr)
		{
			CObject* pObjectNext = pObject->m_pNext;

			if (pObject->CheckFlagUpdate())
			{
				// オブジェクトの更新処理
				pObject->Update();
			}

			// 次のオブジェクトを代入
			pObject = pObjectNext;
		}
	}

	// 全死亡フラグ確認開放処理
	DeathAllCheckRelease();

	// デバック表示
	Debug();
}

//-------------------------------------
//-	全描画処理
//-------------------------------------
void CObject::DrawAll(void)
{
	for (int nCount = 0; nCount < OBJECT_PRIORITY_MAX; nCount++)
	{
		// 先頭のオブジェクトポインタを代入
		CObject* pObject = m_apTop[nCount];

		while (pObject != nullptr)
		{
			CObject* pObjectNext = pObject->m_pNext;

			if (pObject->m_bIsDrawStop == false)
			{
				// オブジェクトの更新処理
				pObject->Draw();
			}

			// 次のオブジェクトを代入
			pObject = pObjectNext;
		}
	}
}

CObject* CObject::GetTop(int nPriority)
{
	return nullptr;
}

CObject* CObject::GetNext(void)
{
	return nullptr;
}

//-------------------------------------
//-	開放設定処理
//-------------------------------------
void CObject::Release(void)
{
	m_bIsDeath = true;
}

//-------------------------------------
//- 更新フラグ確認処理
//-------------------------------------
bool CObject::CheckFlagUpdate(void)
{
	if (m_bIsUpdateStop ||
		m_bIsUpdateAllStop && m_bIsUpdatePause == false)
	{
		return false;
	}

	return true;
}

//-------------------------------------
//-	オブジェクトの開放処理
//-------------------------------------
void CObject::ReleaseObj(void)
{
	// 自身が先頭のオブジェクト
	if (m_apTop[m_nPriority] == this)
	{
		// 次のオブジェクトポインタを先頭に設定
		m_apTop[m_nPriority] = m_pNext;

		if (m_pNext != nullptr)
		{
			m_pNext->m_pPrev = nullptr;
		}
	}
	// 自身が最後尾のオブジェクト
	else if (m_apCur[m_nPriority] == this)
	{
		// 前のオブジェクトポインタを最後尾に設定
		m_apCur[m_nPriority] = m_pPrev;

		if (m_pPrev != nullptr)
		{
			m_pPrev->m_pNext = nullptr;
		}
	}
	else
	{
		m_pPrev->m_pNext = m_pNext;
		m_pNext->m_pPrev = m_pPrev;
	}

	m_nNumAll--;

	delete this;

}

//-------------------------------------
//-	オブジェクトの全死亡フラグ確認開放処理
//-------------------------------------
void CObject::DeathAllCheckRelease(void)
{
	for (int nCount = 0; nCount < OBJECT_PRIORITY_MAX; nCount++)
	{
		// 先頭のオブジェクトポインタを代入
		CObject* pObject = m_apTop[nCount];

		while (pObject != nullptr)
		{
			CObject* pObjectNext = pObject->m_pNext;

			// 死亡の有無
			if (pObject->m_bIsDeath)
			{
				pObject->ReleaseObj();
			}

			// 次のオブジェクトを代入
			pObject = pObjectNext;
		}
	}
}

//-------------------------------------
//- プレイヤーのデバック表示
//-------------------------------------
void CObject::Debug(void)
{
	// デバックプロックの取得
	CDebugProc *pDebugProc = CManager::GetInstance()->GetDbugProc();

	// デバックプロック取得の有無を判定
	if (pDebugProc == NULL)
	{
		return;
	}

	pDebugProc->Print("\n");
	pDebugProc->Print("オブジェクト総数\n");
	pDebugProc->Print("%d", m_nNumAll);
	pDebugProc->Print("\n");
}