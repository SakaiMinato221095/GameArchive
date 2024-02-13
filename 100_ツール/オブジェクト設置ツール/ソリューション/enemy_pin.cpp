
//-===============================================
//-
//-	エネミーピンの処理[enemy_pin.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "enemy_pin.h"

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

// エネミーピンのモデルのコンスト定義
const char *pModelEnemyPin[] =
{
	"data\\MODEL\\enemy_pin.x",				// エネミーピンのモデル
};

//-======================================
//-	静的変数宣言
//-======================================

CDataInt CEnemyPin::m_nDataModelNldx[MODEL_MAX] = {};

//-------------------------------------
//-	オブジェクトイベントのコンストラクタ
//-------------------------------------
CEnemyPin::CEnemyPin()
{
}

//-------------------------------------
//-	オブジェクトイベントのデストラクタ
//-------------------------------------
CEnemyPin::~CEnemyPin()
{

}

//-------------------------------------
//- オブジェクトイベントのモデル読み込み
//-------------------------------------
HRESULT CEnemyPin::Load(void)
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
		nModelNldx = pManagerModel->Regist(pModelEnemyPin[nCount]);

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
void CEnemyPin::Unload(void)
{

}

//-------------------------------------
//- オブジェクトイベントの初期化処理
//-------------------------------------
HRESULT CEnemyPin::Init(MODEL model)
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
void CEnemyPin::Uninit(void)
{
	// Xファイルオブジェクトの終了
	CObjectX::Uninit();
}

//-------------------------------------
//- オブジェクトイベントの更新処理
//-------------------------------------
void CEnemyPin::Update(void)
{
	// Xファイルオブジェクトの更新処理
	CObjectX::Update();
}

//-------------------------------------
//- オブジェクトイベントの描画処理
//-------------------------------------
void CEnemyPin::Draw(void)
{
	// オブジェクトイベントの描画処理
	CObjectX::Draw();
}

//-------------------------------------
//- オブジェクトイベントの生成処理
//-------------------------------------
CEnemyPin *CEnemyPin::Create(MODEL model)
{
	// オブジェクトイベントの生成
	CEnemyPin *pCEnemyPin = new CEnemyPin;

	// 生成の成功の有無を判定
	if (pCEnemyPin != NULL)
	{
		// 初期化処理
		if (FAILED(pCEnemyPin->Init(model)))
		{// 失敗時

		 // 「なし」を返す
			return NULL;
		}
	}
	else if (pCEnemyPin == NULL)
	{// 失敗時

	 // 「なし」を返す
		return NULL;
	}

	// オブジェクトイベントのポインタを返す
	return pCEnemyPin;
}

//-------------------------------------
//- オブジェクトイベントの設定処理
//-------------------------------------
void CEnemyPin::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 情報更新
	m_dataPos.Set(pos);							// 位置
	m_dataPosOld.Set(pos);						// 前回の位置

	m_dataRot.Set(rot);							// 向き
	m_dataRotDest.Set(rot);						// 目的の向き

	m_dataSize.Set(
		D3DXVECTOR3(10.0f, 0.0f, 10.0f));		// 大きさ
}

//-------------------------------------
//-	モデルの設定処理
//-------------------------------------
int CEnemyPin::GetModel(void)
{
	// モデル設定
	return(int)m_model;
}

//-------------------------------------
//-	モデルの設定処理
//-------------------------------------
void CEnemyPin::SetModel(int nModelNldx)
{
	// モデル設定
	m_model = (MODEL)nModelNldx;
}