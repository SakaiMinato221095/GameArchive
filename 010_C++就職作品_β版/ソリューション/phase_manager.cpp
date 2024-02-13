
//-===============================================
//-
//-	フェーズ管理処理[phase_manager.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "phase_manager.h"

#include "manager.h"
#include "renderer.h"

#include "fade.h"

#include "helper_sakai.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	コンスト定義
//=======================================

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CPhaseManager::CPhaseManager(int nPriority)
{
	ZeroMemory(&m_info, sizeof(m_info));
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CPhaseManager::~CPhaseManager()
{

}

//-------------------------------------
//- 背景のテクスチャの読み込み
//-------------------------------------
HRESULT CPhaseManager::Load(void)
{
	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 背景の読み込んだテクスチャの破棄
//-------------------------------------
void CPhaseManager::Unload(void)
{

}
//-------------------------------------
//- 初期化処理（3Dオブジェクト設定）
//-------------------------------------
HRESULT CPhaseManager::Init(void)
{
	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 終了処理
//-------------------------------------
void CPhaseManager::Uninit(void)
{

}

//-------------------------------------
//- 更新処理
//-------------------------------------
void CPhaseManager::Update(void)
{
}

//-------------------------------------
//- 描画処理
//-------------------------------------
void CPhaseManager::Draw(void)
{

}

//-------------------------------------
//- 敵死亡数加算の設定
//-------------------------------------
void CPhaseManager::AddDeadEnemy(void)
{
	// ターゲット数を加算
	m_info.nTargetCompCnt++;

	if (m_info.nTargetCompCnt >= m_info.nTargetCompNum)
	{
		// ターゲットカウントを初期化
		m_info.nTargetCompCnt = 0;

		// 加算処理
		m_info.typePhaseNew = (TYPE_PHASE)HelperSakai::AddLimitStop(m_info.typePhaseNew, 1, TYPE_PHASE_ONE, TYPE_PHASE_COMP);

		// コンプリート状況を確認
		if (m_info.typePhaseNew >= TYPE_PHASE_COMP)
		{
			// コンプリートを設定
			SetComp();
		}
	}
}

//-------------------------------------
//- 生成処理
//-------------------------------------
CPhaseManager* CPhaseManager::Create(void)
{
	// ポインタを宣言
	CPhaseManager* pCPhaseManager = DBG_NEW CPhaseManager(1);

	// 生成の成功の有無を判定
	if (pCPhaseManager != NULL)
	{
		// 初期化処理
		if (FAILED(pCPhaseManager->Init()))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCPhaseManager == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// ポインタを返す
	return pCPhaseManager;
}

//-------------------------------------
//- コンプリート設定処理
//-------------------------------------
void CPhaseManager::SetComp(void)
{
	if (CManager::GetInstance() != nullptr)
	{
		if (CManager::GetInstance()->GetFade() != nullptr)
		{
			// ゲームモード
			CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_RESULT);
		}
	}
}