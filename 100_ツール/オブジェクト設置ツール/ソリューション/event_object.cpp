
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

#include "manager_model.h"
#include "manager_time.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	コンスト定義
//=======================================

// オブジェクトイベントのモデルのコンスト定義
const char *pModelEventObject[] =
{
	"data\\MODEL\\DrinkShop000.x",				// 自販機_000のモデル
	"data\\MODEL\\obaravegetable000.x",			// 八百屋_000のモデル
};

//-======================================
//-	静的変数宣言
//-======================================

CDataInt CEventObject::m_nDataModelNldx[MODEL_MAX] = {};
int CEventObject::m_nEventObjectNum = 0;

//-------------------------------------
//-	オブジェクトイベントのコンストラクタ
//-------------------------------------
CEventObject::CEventObject()
{
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
	BindModel(nModelNldx,model);

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
	CEventObject *pCEventObject = new CEventObject;

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

	// オブジェクトイベントのポインタを返す
	return pCEventObject;
}

//-------------------------------------
//- オブジェクトイベントの設定処理
//-------------------------------------
void CEventObject::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 情報更新
	m_dataPos.Set(pos);							// 位置
	m_dataPosOld.Set(pos);						// 前回の位置

	m_dataRot.Set(rot);							// 向き
	m_dataRotDest.Set(rot);						// 目的の向き

	m_dataSize.Set(
		D3DXVECTOR3(10.0f, 0.0f, 10.0f));		// 大きさ

	m_nDataReuseTime.Set(300);					// 再使用時間

	m_scoreGetType = CScore::GET_TYPE_RANDOM;	// スコアの取得系統

	m_nGetScore.Set(0);							// スコアの入手量	
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
//- オブジェクトイベントの実行処理
//-------------------------------------
void CEventObject::Execution(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();	// 位置
	int nGetScore = m_nGetScore.Get();	// 取得スコア

	// 使用状況を更新
	m_bDataUse.Set(true);

	// スコアのポインタを宣言
	CScore *pScore = NULL;
}

//-------------------------------------
//- オブジェクトイベントの再使用の処理
//-------------------------------------
void CEventObject::UpdateReuse(void)
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
	CManagerTime *pManagerTime = CManager::GetManagerTime();

	// 時間管理取得の有無を判定
	if (pManagerTime == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();				// 位置
	int nEffectCount = m_nDataEffectCount.Get();	// エフェクト出現のカウント

	// 情報更新
	m_dataPos.Set(pos);						// 位置
	m_nDataEffectCount.Set(nEffectCount);	// エフェクト出現のカウント
}
