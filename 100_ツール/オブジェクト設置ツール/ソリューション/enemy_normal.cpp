
//-===============================================
//-
//-	通常敵の処理[enemy_normal.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "enemy_normal.h"
#include "object_x.h"

#include "renderer.h"
#include "manager.h"
#include "manager_object.h"

#include "manager_model.h"

#include "score.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	通常敵のコンストラクタ
//-------------------------------------
CEnemyNormal::CEnemyNormal()
{

}

//-------------------------------------
//-	通常敵のデストラクタ
//-------------------------------------
CEnemyNormal::~CEnemyNormal()
{

}

//-------------------------------------
//- 通常敵の初期化処理
//-------------------------------------
HRESULT CEnemyNormal::Init(MODEL model)
{
	// Xファイルオブジェクトの初期化 if(初期化成功の有無を判定)
	if (FAILED(CEnemy::Init(model)))
	{
		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 通常敵の終了処理
//-------------------------------------
void CEnemyNormal::Uninit(void)
{
	// 敵の終了処理
	CEnemy::Uninit();
}

//-------------------------------------
//- 通常敵の更新処理
//-------------------------------------
void CEnemyNormal::Update(void)
{
	// 敵の更新処理
	CEnemy::Update();
}

//-------------------------------------
//- 通常敵の描画処理
//-------------------------------------
void CEnemyNormal::Draw(void)
{
	// 敵の描画処理
	CEnemy::Draw();
}

//-------------------------------------
//- 通常敵の生成処理
//-------------------------------------
CEnemyNormal *CEnemyNormal::Create(MODEL model)
{
	// 通常敵の生成
	CEnemyNormal *pCEnemyNormal = new CEnemyNormal;

	// 生成の成功の有無を判定
	if (pCEnemyNormal != NULL)
	{
		// 初期化処理
		if (FAILED(pCEnemyNormal->Init(model)))
		{// 失敗時

		 // 「なし」を返す
			return NULL;
		}
	}
	else if (pCEnemyNormal == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// 通常敵のポインタを返す
	return pCEnemyNormal;
}

//-------------------------------------
//- 通常敵の設定処理
//-------------------------------------
void CEnemyNormal::Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot , int nLife)
{
	// 情報更新
	m_dataPos.Set(pos);		// 位置
	m_dataPosOld.Set(pos);	// 前回の位置

	m_dataSize.Set(size);	// 大きさ

	m_dataRot.Set(rot);		// 移動量
	m_dataRotDest.Set(rot);	// 目的の向き

	m_nDataLife.Set(nLife);	// 体力
}