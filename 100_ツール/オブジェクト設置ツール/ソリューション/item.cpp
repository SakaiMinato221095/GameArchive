
//-===============================================
//-
//-	アイテムの処理[item.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "item.h"

#include "renderer.h"
#include "manager.h"

#include "manager_model.h"
#include "manager_time.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	コンスト定義
//=======================================

// アイテムのモデルのコンスト定義
const char *pModelItem[] =
{
	"data\\MODEL\\gun_copper.x",	// 銃のモデル
	"data\\MODEL\\gun_silver.x",	// 銃のモデル
	"data\\MODEL\\gun_gold.x",		// 銃のモデル

	"data\\MODEL\\Bomb.x",			// ボムのモデル
};

//-======================================
//-	静的変数宣言
//-======================================

CDataInt CItem::m_nDataModelNldx[MODEL_MAX] = {};		// モデルの番号

//-------------------------------------
//-	アイテムのコンストラクタ
//-------------------------------------
CItem::CItem()
{

}

//-------------------------------------
//-	アイテムのデストラクタ
//-------------------------------------
CItem::~CItem()
{

}

//-------------------------------------
//- 敵のモデル読み込み
//-------------------------------------
HRESULT CItem::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// デバイスの情報取得の成功を判定
	if (pDevice == NULL)
	{// 失敗時

		// 初期化処理を抜ける
		return E_FAIL;
	}

	// モデル管理の生成
	CManagerModel *pManagerModel = CManager::GetManagerModel();

	// モデル管理の有無を判定
	if (pManagerModel == NULL)
	{
		// 初期化処理を抜ける
		return E_FAIL;
	}

	// テクスチャ設定
	for (int nCount = 0; nCount < MODEL_MAX; nCount++)
	{
		// モデル番号を取得
		int nModelNldx = m_nDataModelNldx[nCount].Get();

		// モデル番号の取得（モデルの割当）
		nModelNldx = pManagerModel->Regist(pModelItem[nCount]);

		// モデルの読み込み成功の有無を確認
		if (nModelNldx == -1)
		{
			// 失敗時に初期化処理を抜ける
			return E_FAIL;
		}

		// モデル番号を設定
		m_nDataModelNldx[nCount].Set(nModelNldx);
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 敵の読み込んだモデル破棄
//-------------------------------------
void CItem::Unload(void)
{

}

//-------------------------------------
//- アイテムの初期化処理（Xファイルオブジェクト設定）
//-------------------------------------
HRESULT CItem::Init(MODEL model)
{
	// モデル管理の生成
	CManagerModel *pManagerModel = CManager::GetManagerModel();

	// モデル管理の有無を判定
	if (pManagerModel == NULL)
	{
		// 処理を抜ける
		return E_FAIL;
	}

	// モデル番号を取得
	int nModelNldx = m_nDataModelNldx[model].Get();

	// 効果なしオブジェクトのモデル割当
	BindModel(nModelNldx, model);

	// 種類の判定
	switch (model)
	{
	case MODEL_GUN_000:

		// 最大購入回数の設定
		m_nBuyMax.Set(1);	

		break;

	case MODEL_BOMB_000:

		// 最大購入回数の設定
		m_nBuyMax.Set(5);	

		break;
	}

	// Xファイルオブジェクトの初期化 if(初期化成功の有無を判定)
	if (FAILED(CObjectX::Init()))
	{
		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- アイテムの終了処理
//-------------------------------------
void CItem::Uninit(void)
{
	// Xファイルオブジェクトの終了
	CObjectX::Uninit();
}

//-------------------------------------
//- アイテムの更新処理
//-------------------------------------
void CItem::Update(void)
{
	// 時間管理の情報を取得
	CManagerTime *pManagerTime = CManager::GetManagerTime();

	// 時間管理取得の有無を判定
	if (pManagerTime == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 変数宣言（情報取得）
	bool bUse = m_bDataUse.Get();				// 使用の有無
	D3DXVECTOR3 rotAdd = m_dataRotAdd.Get();	// 回転量

	// 時間倍率の計算
	D3DXVECTOR3 rotAddTime = pManagerTime->CalRate(rotAdd);

	// 回転処理
	AddRot(rotAddTime);

	// Xファイルオブジェクトの更新処理
	CObjectX::Update();
}

//-------------------------------------
//- アイテムの描画処理
//-------------------------------------
void CItem::Draw(void)
{
	// Xファイルオブジェクトの描画処理
	CObjectX::Draw();
}

//-------------------------------------
//- アイテムの生成処理（Xファイルオブジェクト設定）
//-------------------------------------
CItem * CItem::Create(MODEL model)
{
	// アイテムのポインタを宣言
	CItem *pCItem = new CItem;

	// 生成の成功の有無を判定
	if (pCItem != NULL)
	{
		// 初期化処理
		if (FAILED(pCItem->Init(model)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCItem == NULL)
	{// 失敗時

	 // 「なし」を返す
		return NULL;
	}

	// アイテムのポインタを返す
	return pCItem;
}

//-------------------------------------
//-	モデルの設定処理
//-------------------------------------
int CItem::GetModel(void)
{
	// モデル設定
	return(int)m_model;
}

//-------------------------------------
//-	モデルの設定処理
//-------------------------------------
void CItem::SetModel(int nModelNldx)
{
	// モデル設定
	m_model = (MODEL)nModelNldx;
}

//-------------------------------------
//- アイテムの設定処理
//-------------------------------------
void CItem::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 情報更新
	m_dataPos.Set(pos);		// 位置
	m_dataPosOld.Set(pos);	// 前回の位置

	m_dataRot.Set(rot);		// 移動量
	m_dataRotDest.Set(rot);	// 目的の向き

	m_dataSize.Set(D3DXVECTOR3(0.0f, 0.01f, 0.0f));	// 大きさ

	m_dataRotAdd.Set(D3DXVECTOR3(0.0f,0.01f,0.0f));	// 回転量
}