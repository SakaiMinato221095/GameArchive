
//-===============================================
//-
//-	オブジェクトイベントの処理[event_object.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "event_object.h"

#include "renderer.h"
#include "manager.h"
#include "game.h"

#include "manager_model.h"
#include "time_stop.h"

#include "mgr_sys_obj.h"
#include "sys_game_phase.h"

#include "effect.h"
#include "particle.h"

#include "effect_object.h"	

#include "file_data_evt_obj.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	コンスト定義
//=======================================

// オブジェクトイベントのモデルのコンスト定義
const char *pModelEventObject[] =
{
	"data\\MODEL\\DrinkShop000.x",			// 自販機_000のモデル
	"data\\MODEL\\obaravegetable000.x",		// 八百屋_000のモデル
};

//-======================================
//-	静的変数宣言
//-======================================

CDataInt CEventObject::m_nDataModelNldx[MODEL_MAX] = {};
int CEventObject::m_nEventObjectNum = 0;

CEventObject::ModelData CEventObject::m_modelData[MODEL_MAX] = {};		// モデル情報

//-------------------------------------
//-	オブジェクトイベントのコンストラクタ
//-------------------------------------
CEventObject::CEventObject(int nPriority) : CObjectX(nPriority)
{
	m_model = (MODEL)0;
	m_scoreGetType = CScore::GET_TYPE_NORMAL;
}

//-------------------------------------
//-	オブジェクトイベントのデストラクタ
//-------------------------------------
CEventObject::~CEventObject()
{

}

//-------------------------------------
//- オブジェクトイベントのモデル読み込み
//-------------------------------------
HRESULT CEventObject::Load(void)
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
		nModelNldx = pManagerModel->Regist(pModelEventObject[nCount]);

		// モデルの読み込み成功の有無を確認
		if (nModelNldx == -1)
		{
			// 失敗時に初期化処理を抜ける
			return E_FAIL;
		}

		// モデル番号を設定
		m_nDataModelNldx[nCount].Set(nModelNldx);
	}

	// イベントオブジェクト
	CFileDataEvtObj::Load();

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- オブジェクトイベントの読み込んだモデル破棄
//-------------------------------------
void CEventObject::Unload(void)
{

}

//-------------------------------------
//- オブジェクトイベントの初期化処理
//-------------------------------------
HRESULT CEventObject::Init(MODEL model)
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

	// 敵のモデル割当
	BindModel(nModelNldx, model);

	// データ設定
	m_dataSize.Set(m_modelData[model].size);

	// 初期設定処理
	InitSet(model);

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
//- オブジェクトイベントの終了処理
//-------------------------------------
void CEventObject::Uninit(void)
{
	// Xファイルオブジェクトの終了
	CObjectX::Uninit();
}

//-------------------------------------
//- オブジェクトイベントの更新処理
//-------------------------------------
void CEventObject::Update(void)
{
	// フェーズ情報を取得
	CSysGamePhase::TYPE pPhaseType = CGame::GetSysGamePhase()->GetType();

	if(pPhaseType == CSysGamePhase::TYPE_SEARCH)
	{
		// 変数宣言（情報取得）
		bool bUse = m_bDataUse.Get();	// 使用の有無

		// 使用の有無を判定
		if (bUse == true)
		{
			// 再使用の処理
			UpdateReuse();
		}
		else
		{
			// 使用可能表示処理
			AvailableDisplay();
		}
	}

	// Xファイルオブジェクトの更新処理
	CObjectX::Update();
}

//-------------------------------------
//- オブジェクトイベントの描画処理
//-------------------------------------
void CEventObject::Draw(void)
{
	// オブジェクトイベントの描画処理
	CObjectX::Draw();
}

//-------------------------------------
//- オブジェクトイベントの生成処理
//-------------------------------------
CEventObject *CEventObject::Create(MODEL model)
{
	// オブジェクトイベントの生成
	CEventObject *pCEventObject = DBG_NEW CEventObject;

	// 生成の成功の有無を判定
	if (pCEventObject != NULL)
	{
		// 初期化処理
		if (FAILED(pCEventObject->Init(model)))
		{// 失敗時

		 // 「なし」を返す
			return NULL;
		}
	}
	else if (pCEventObject == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// 種類を設定
	pCEventObject->SetType(TYPE_ENEMY);

	// オブジェクトイベントのポインタを返す
	return pCEventObject;
}

//-------------------------------------
//-	モデルの設定処理
//-------------------------------------
int CEventObject::GetModel(void)
{
	// モデル設定
	return(int)m_model;
}

//-------------------------------------
//-	モデルの設定処理
//-------------------------------------
void CEventObject::SetModel(int nModelNldx)
{
	// モデル設定
	m_model = (MODEL)nModelNldx;
}

//-------------------------------------
//-	モデルの情報の設定処理
//-------------------------------------
void CEventObject::SetModelData(int nNum, CEventObject::ModelData modelData)
{
	// モデル情報の代入
	m_modelData[nNum] = modelData;	// 大きさ
}

//-------------------------------------
//-	モデルの情報の取得処理
//-------------------------------------
CEventObject::ModelData CEventObject::GetModelData(int nNum)
{
	// モデル情報を返す
	return m_modelData[nNum];
}

//-------------------------------------
//- オブジェクトイベントの実行処理
//-------------------------------------
void CEventObject::Execution(void)
{
	// スコアの情報を取得
	CScore *pScore = CGame::GetMgrSysObj()->GetScore();

	// スコア情報の有無を判定
	if (pScore == NULL)
	{
		return;
	}

	// 変数宣言（情報取得）
 	D3DXVECTOR3 pos = m_dataPos.Get();	// 位置
	int nGetScore = m_nGetScore.Get();	// 取得スコア

	// 使用状況を更新
	m_bDataUse.Set(true);

	// オブジェクトエフェクトの生成
	CEffectObject *pEffectObject = CEffectObject::Create(CEffectObject::MODEL_COIN_000);

	// オブジェクトエフェクトの生成成功の有無を判定
	if (pEffectObject != NULL)
	{
		// オブジェクトエフェクト設定
		pEffectObject->Set(
			D3DXVECTOR3(pos.x,pos.y + 30.0f,pos.z),
			D3DXVECTOR3(5.0f, 5.0f, 5.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(0.0f, 10.0f, 0.0f),
			D3DXVECTOR3(0.0f, 200.0f, 0.0f));
	}

	// スコアの取得処理
	pScore->Add(m_scoreGetType, nGetScore);
}

//-------------------------------------
//- オブジェクトイベントの初期設定処理
//-------------------------------------
void CEventObject::InitSet(MODEL model)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();	// 位置
	D3DXVECTOR3 rot = m_dataRot.Get();	// 向き

	// 情報更新
	m_dataPosOld.Set(pos);				// 前回の位置
	m_dataRotDest.Set(rot);				// 目的の向き

	m_nDataReuseTime.Set(1200);					// 再使用時間

	m_scoreGetType = CScore::GET_TYPE_RANDOM;	// スコアの取得系統

	m_nGetScore.Set(0);							// スコアの入手量
}

//-------------------------------------
//- オブジェクトイベントの再使用の処理
//-------------------------------------
void CEventObject::UpdateReuse(void)
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
	int nReuseTime = m_nDataReuseTime.Get();	// 再使用時間
	int nReuseCount = m_nDataReuseCount.Get();	// 再使用カウント
	bool bUse = m_bDataUse.Get();				// 使用の有無

	if (pManagerTime->m_bDataIntCount.Get() == true)
	{
		// 再使用カウントを加算
		nReuseCount++;

		// 再使用カウントの判定
		if (nReuseCount >= nReuseTime)
		{
			// 再使用カウントを初期化
			nReuseCount = 0;

			// 使用可能
			bUse = false;
		}
	}

	// 情報更新
	m_nDataReuseCount.Set(nReuseTime);	// 再使用時間
	m_nDataReuseCount.Set(nReuseCount);	// 再使用カウント
	m_bDataUse.Set(bUse);				// 使用の有無
}

//-------------------------------------
//- オブジェクトイベントの使用可能表示
//-------------------------------------
void CEventObject::AvailableDisplay(void)
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
	D3DXVECTOR3 pos = m_dataPos.Get();				// 位置
	int nEffectCount = m_nDataEffectCount.Get();	// エフェクト出現のカウント

	if (pManagerTime->m_bDataIntCount.Get() == true)
	{
		// エフェクトのポインタを宣言
		CEffect *pEffect = NULL;

		// エフェクトカウントを加算
		nEffectCount++;

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
				pEffect->m_dataSize.Set(D3DXVECTOR3(30.0f, 30.0f, 0.0f));

				// 移動量を設定
				pEffect->m_dataMove.Set(D3DXVECTOR3(0.0f, 3.0f, 0.0f));

				// 色を設定（基本色）
				pEffect->m_dataColor.Set(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

				// エフェクトの設定処理
				pEffect->m_nDataLife.Set(60);
			}

		}
	}

	// 情報更新
	m_dataPos.Set(pos);						// 位置
	m_nDataEffectCount.Set(nEffectCount);	// エフェクト出現のカウント
}
