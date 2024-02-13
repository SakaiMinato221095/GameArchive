
//================================================
//=
//=	キックのフィニッシュ攻撃処理[finish_kick.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "finish_kick.h"

#include "coll.h"
#include "mgr_coll.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//=	静的変数宣言
//=======================================

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CFinishKick::CFinishKick()
{

}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CFinishKick::~CFinishKick()
{

}

//-------------------------------------
//- 初期化処理
//-------------------------------------
HRESULT CFinishKick::Init(void)
{
	// 親クラスの初期化処理
	if (CAttack::Init() == E_FAIL)
	{
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 終了処理
//-------------------------------------
void CFinishKick::Uninit(void)
{
	// 親クラスの終了処理
	CAttack::Uninit();
}

//-------------------------------------
//- 更新処理
//-------------------------------------
void CFinishKick::Update(void)
{
	// 接触更新処理
	UpdateHit();

	// デバック
	Debug();
}

//-------------------------------------
//- 描画処理
//-------------------------------------
void CFinishKick::Draw(void)
{
	// 親クラスの描画処理
	CAttack::Draw();
}

//-------------------------------------
//- 初期設定処理
//-------------------------------------
void CFinishKick::InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nDamage,CMgrColl::TAG tagTgt)
{
	// 親クラスの初期設定処理
	CAttack::InitSet(pos, size, nDamage, tagTgt);

	// ターゲットを敵に設定
	SetTagTgt(CMgrColl::TAG_ENEMY);
}

//-------------------------------------
//- 生成処理
//-------------------------------------
CFinishKick* CFinishKick::Create(void)
{
	// 生成処理
	CFinishKick* pFinishKick = DBG_NEW CFinishKick;

	// 生成の成功の有無を判定
	if (pFinishKick != NULL)
	{
		// 初期化処理
		if (FAILED(pFinishKick->Init()))
		{// 失敗時

			return NULL;
		}
	}
	else if (pFinishKick == NULL)
	{// 失敗時

		return NULL;
	}

	// ポインタを返す
	return pFinishKick;
}

