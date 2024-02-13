
//================================================
//=
//=	攻撃の処理[attack.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "attack.h"

#include "manager.h"
#include "debugproc.h"

#include "coll.h"
#include "mgr_coll.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//=	静的変数宣言
//=======================================

//-------------------------------------
//-	タイマーのコンストラクタ
//-------------------------------------
CAttack::CAttack()
{
	// 値のクリア
	ZeroMemory(&m_info, sizeof(m_info));
	m_pColl = nullptr;
}

//-------------------------------------
//-	タイマーのデストラクタ
//-------------------------------------
CAttack::~CAttack()
{

}

//-------------------------------------
//- タイマーの初期化処理
//-------------------------------------
HRESULT CAttack::Init(void)
{
	if (m_pColl == NULL)
	{
		// 当たり判定設定
		m_pColl = CColl::Create(
			CMgrColl::TAG_ATTACK,
			this,
			m_info.pos + m_info.posPlus,
			m_info.size);

		m_pColl->SetIsVisualDrawStop(false);
	}
	else
	{
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- タイマーの終了処理
//-------------------------------------
void CAttack::Uninit(void)
{
	if (m_pColl != nullptr)
	{
		// 当たり判定の初期化
		m_pColl->Uninit();
		delete m_pColl;
		m_pColl = nullptr;
	}

	// 自分自身のポインタの開放
	Release();
}

//-------------------------------------
//- タイマーの更新処理
//-------------------------------------
void CAttack::Update(void)
{
	// 接触更新処理
	UpdateHit();

	// デバック
	Debug();
}

//-------------------------------------
//- タイマーの描画処理
//-------------------------------------
void CAttack::Draw(void)
{

}

//-------------------------------------
//- タイマーの位置情報の設定
//-------------------------------------
void CAttack::InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nDamage, CMgrColl::TAG tagTgt)
{
	m_info.pos = pos;
	m_info.size = size;
	m_info.nDamage = nDamage;
	m_info.tagTgt = tagTgt;
}

//-------------------------------------
//- タイマーの位置情報の設定
//-------------------------------------
CAttack* CAttack::Create(void)
{
	// 生成処理
	CAttack* pAttack = DBG_NEW CAttack;

	// 生成の成功の有無を判定
	if (pAttack != NULL)
	{
		// 初期化処理
		if (FAILED(pAttack->Init()))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pAttack == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// ポインタを返す
	return pAttack;
}

//-------------------------------------
//- 接触更新処理
//-------------------------------------
void CAttack::UpdateHit(void)
{
	CManager* pManager = CManager::GetInstance();

	if (pManager == nullptr)
	{
		return;
	}

	CMgrColl* pMgrColl = pManager->GetMgrColl();

	if (pMgrColl == nullptr)
	{
		return;
	}

	if (m_pColl != nullptr)
	{
		// 当たり判定の情報更新処理
		m_pColl->UpdateData(
			m_info.pos + m_info.posPlus,
			m_info.size);

		// ターゲットとの接触判定
		if (m_pColl->Hit(m_info.tagTgt, CMgrColl::EVENT_TYPE_TRIGGER))
		{
			// 最大接触数を取得
			CColl::Data data = m_pColl->GetData();
			int nHitNldxMax = data.nHitNldxMax;

			// 接触した敵のダメージ処理
			for (int nCount = 0; nCount < nHitNldxMax; nCount++)
			{
				CColl* pColl = pMgrColl->GetColl(data.hitData[nCount].nNldx);

				if (pColl != nullptr)
				{
					CObject* pObj = pColl->GetData().pObj;

					if (pObj != nullptr)
					{
						pObj->HitDamage(m_info.nDamage);
					}
				}
			}
		}

	}
}

//-------------------------------------
//- プレイヤーのデバック表示
//-------------------------------------
void CAttack::Debug(void)
{
	// デバックプロックの取得
	CDebugProc* pDebugProc = CManager::GetInstance()->GetDbugProc();

	// デバックプロック取得の有無を判定
	if (pDebugProc == NULL)
	{
		return;
	}

	pDebugProc->Print("\n");
	pDebugProc->Print("攻撃の位置");
	pDebugProc->Print("\n");
	pDebugProc->Print("%f,%f,%f", m_info.pos.x, m_info.pos.y, m_info.pos.z);
	pDebugProc->Print("\n");
}