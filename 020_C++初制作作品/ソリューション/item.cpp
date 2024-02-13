
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
#include "obj_2d_item_info.h"

#include "renderer.h"
#include "manager.h"

#include "manager_model.h"
#include "time_stop.h"

#include "effect.h"
#include "particle.h"
#include "state_battle.h"

#include "file_data_item.h"

#include "game.h"
#include "mgr_sys_obj.h"
#include "score.h"

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
CItem::ModelData CItem::m_modelData[MODEL_MAX] = {};	// モデル情報

//-------------------------------------
//-	アイテムのコンストラクタ
//-------------------------------------
CItem::CItem()
{
	m_model = (MODEL)0;
	m_pItemInfo = NULL;
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

	// モデル情報
	CFileDataItem::Load();

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

	// 初期設定
	InitSet(model);

	// 2Dのアイテム情報
	{
		// 2Dのアイテム情報の有無を判定
		if (m_pItemInfo == NULL)
		{
			// 2Dのアイテム情報の生成
			m_pItemInfo = CObj2dItemInfo::Create(m_model);

			// 2Dのアイテム情報の生成成功の有無を判定
			if (m_pItemInfo == NULL)
			{
				// 生成処理を抜ける
				return E_FAIL;
			}
		}
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
	// 2Dアイテム情報のポインタを初期化
	m_pItemInfo = NULL;

	// Xファイルオブジェクトの終了
	CObjectX::Uninit();
}

//-------------------------------------
//- アイテムの更新処理
//-------------------------------------
void CItem::Update(void)
{
	// 時間管理の情報を取得
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// 時間管理取得の有無を判定
	if (pManagerTime == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 変数宣言（情報取得）
	bool bUse = m_bDataUse.Get();				// 使用の有無
	D3DXVECTOR3 rotAdd = m_dataRotAdd.Get();	// 回転量

	// 使用の有無を判定
	if (bUse == false)
	{// 使用可能

		// 使用可能表示処理
		AvailableDisplay();
	}

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
//-	モデルの情報の設定処理
//-------------------------------------
void CItem::SetModelData(int nNum, CItem::ModelData modelData)
{
	// モデル情報の代入
	m_modelData[nNum] = modelData;	// 大きさ
}

//-------------------------------------
//-	モデルの情報の取得処理
//-------------------------------------
CItem::ModelData CItem::GetModelData(int nNum)
{
	// モデル情報を返す
	return m_modelData[nNum];
}

//-------------------------------------
//- アイテムの設定処理
//-------------------------------------
void CItem::InitSet(MODEL model)
{
	// 情報更新
	m_dataRotAdd.Set(D3DXVECTOR3(0.0f, 0.01f, 0.0f));	// 回転量

	// データ設定
	m_dataSize.Set(m_modelData[model].size);
}

//-------------------------------------
//- アイテムの実行処理
//-------------------------------------
void CItem::Execution(void)
{
	// 戦闘ステータスの情報を取得
	CStateBattle *pStateBattle = CGame::GetStateBattle();

	// 戦闘ステータス取得成功の有無を判定
	if (pStateBattle == NULL)
	{
		// 処理を抜ける
		return;
	}

	// スコアの情報を取得
	CScore *pScore = CGame::GetMgrSysObj()->GetScore();

	//  スコアの取得成功の有無を判定
	if (pScore == NULL)
	{
		// 初期化処理を抜ける
		return;
	}

	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();	// 位置情報

	int nBuyCount = m_nBuyCount.Get();	// 購入カウント

	// 変数宣言（スコアの情報）
	int nScore = pScore->m_nDataScore.Get();	// スコアの値

	// スコアと値段を判定
	if (nScore >= m_modelData[m_model].nPrice)
	{
		// スコアの減算
		nScore -= m_modelData[m_model].nPrice;

		// 購入カウントを加算
		nBuyCount++;

		// 購入回数の判定
		if (nBuyCount == m_modelData[m_model].nBuyMax)
		{
			// 使用を設定
			m_bDataUse.Set(true);
		}

		// パーティクルの生成
		CParticle::SetParticle(
			32,
			pos,
			D3DXVECTOR3(20.0f, 20.0f, 0.0f),
			D3DXVECTOR3(30.0f,30.0f,0.0f),
			D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f),
			60);

		switch (m_model)
		{
		case MODEL_GUN_000:

			// 銅装備の設定
			pStateBattle->SetWeaponCopper(true);

			break;

		case MODEL_GUN_001:

			// 銀装備の設定
			pStateBattle->SetWeaponSilver(true);

			break;

		case MODEL_GUN_002:

			// 金装備の設定
			pStateBattle->SetWeaponGold(true);

			break;

		case MODEL_BOMB_000:

			// ボム（サブ武器）の設定
			pStateBattle->SetSubWeaponBomb(true);

			break;
		}
	}

	// 情報更新
	m_nBuyCount.Set(nBuyCount);			// 購入カウント

	// 情報更新（スコア）
	pScore->m_nDataScore.Set(nScore);	// スコア
}

//-------------------------------------
//- アイテムの使用可能表示
//-------------------------------------
void CItem::AvailableDisplay(void)
{
	// 時間管理の情報を取得
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// 時間管理取得の有無を判定
	if (pManagerTime == NULL)
	{
		// 処理を抜ける
		return;
	}

	// スコアの情報を取得
	CScore *pScore = CGame::GetMgrSysObj()->GetScore();

	//  スコアの取得成功の有無を判定
	if (pScore == NULL)
	{
		// 初期化処理を抜ける
		return;
	}

	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();				// 位置
	int nEffectCount = m_nDataEffectCount.Get();	// エフェクト出現のカウント

	// 変数宣言（スコアの情報）
	int nScore = pScore->m_nDataScore.Get();		// スコアの値

	// 整数カウントの有無を判定
	if (pManagerTime->m_bDataIntCount.Get() == true)
	{
		// エフェクトのポインタを宣言
		CEffect *pEffect = NULL;

		// エフェクトカウントを加算
		nEffectCount++;

		if (nScore >= m_modelData[m_model].nPrice)
		{
			// エフェクトカウントの判定
			if (nEffectCount >= 10)
			{
				// エフェクトの生成
				pEffect = CEffect::Create(CEffect::TEX_NORMAL_000);

				// エフェクトの有無を判定
				if (pEffect != NULL)
				{
					// エフェクトカウントの初期化
					nEffectCount = 0;

					// 位置情報を設定
					pEffect->m_dataPos.Set(D3DXVECTOR3(pos.x, pos.y + 20.0f, pos.z));

					// 大きさを設定
					pEffect->m_dataSize.Set(D3DXVECTOR3(15.0f, 15.0f, 0.0f));

					// 移動量を設定
					pEffect->m_dataMove.Set(D3DXVECTOR3(0.0f, 1.0f, 0.0f));

					// 色を設定
					pEffect->m_dataColor.Set(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

					// 体力設定
					pEffect->m_nDataLife.Set(60);
				}
			}
		}
		else
		{
			// エフェクトカウントの判定
			if (nEffectCount >= 10)
			{
				// エフェクトの生成
				pEffect = CEffect::Create(CEffect::TEX_NORMAL_000);

				// エフェクトの有無を判定
				if (pEffect != NULL)
				{
					// エフェクトカウントの初期化
					nEffectCount = 0;

					// 位置情報を設定
					pEffect->m_dataPos.Set(D3DXVECTOR3(pos.x, pos.y + 20.0f, pos.z));

					// 大きさを設定
					pEffect->m_dataSize.Set(D3DXVECTOR3(15.0f, 15.0f, 0.0f));

					// 移動量を設定
					pEffect->m_dataMove.Set(D3DXVECTOR3(0.0f, 1.0f, 0.0f));

					// 色を設定
					pEffect->m_dataColor.Set(D3DXCOLOR(0.5f, 0.0f, 0.0f, 0.5f));

					// 体力設定
					pEffect->m_nDataLife.Set(60);
				}
			}
		}
	}

	// 情報更新
	m_dataPos.Set(pos);						// 位置
	m_nDataEffectCount.Set(nEffectCount);	// エフェクト出現のカウント
}

//-------------------------------------
//- アイテムの購入可能の有無を判定
//-------------------------------------
bool CItem::GetBuyUse(void)
{
	// スコアの情報を取得
	CScore *pScore = CGame::GetMgrSysObj()->GetScore();

	//  スコアの取得成功の有無を判定
	if (pScore == NULL)
	{
		// 初期化処理を抜ける
		return false;
	}

	// 変数宣言（スコアの情報）
	int nScore = pScore->m_nDataScore.Get();	// スコアの値

	// スコアとアイテムの価格を判定
	if (nScore >= m_modelData[m_model].nPrice)
	{
		// 購入可能を返す
		return true;
	}

	// 購入不可を返す
	return false;
}

//-------------------------------------
//- アイテム情報の取得処理
//-------------------------------------
CObj2dItemInfo *CItem::GetItemInfo(void)
{
	return m_pItemInfo;
}
