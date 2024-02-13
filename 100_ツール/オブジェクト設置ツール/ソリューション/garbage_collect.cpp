
//-===============================================
//-
//-	ゴミ回収の処理[garbage_collect.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "garbage_collect.h"

#include "renderer.h"
#include "manager.h"

#include "manager_model.h"
#include "manager_object.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	コンスト定義
//=======================================

// ゴミ回収のモデルのコンスト定義
const char *pModelGarbageCollect[] =
{
	"data\\MODEL\\garbage_car000.x",			// ゴミ回収車のモデル
	"data\\MODEL\\dark_garbage_car000.x",		// 闇のゴミ回収車のモデル
};

//-======================================
//-	静的変数宣言
//-======================================

CDataInt CGarbageCollect::m_nDataModelNldx[MODEL_MAX] = {};

CGarbageCollect::ModelData CGarbageCollect::m_modelData[MODEL_MAX] = {};		// モデル情報

//-------------------------------------
//-	ゴミ回収のコンストラクタ
//-------------------------------------
CGarbageCollect::CGarbageCollect()
{
	m_model = (MODEL)0;
}

//-------------------------------------
//-	ゴミ回収のデストラクタ
//-------------------------------------
CGarbageCollect::~CGarbageCollect()
{

}

//-------------------------------------
//- ゴミ回収のモデル読み込み
//-------------------------------------
HRESULT CGarbageCollect::Load(void)
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
		nModelNldx = pManagerModel->Regist(pModelGarbageCollect[nCount]);

		// モデルの読み込み成功の有無を確認
		if (nModelNldx == -1)
		{
			// 失敗時に初期化処理を抜ける
			return E_FAIL;
		}

		// モデル番号を設定
		m_nDataModelNldx[nCount].Set(nModelNldx);
	}

	m_modelData->size = D3DXVECTOR3(150.0f,0.0f,200.0f);

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- ゴミ回収の読み込んだモデル破棄
//-------------------------------------
void CGarbageCollect::Unload(void)
{

}

//-------------------------------------
//- ゴミ回収の初期化処理
//-------------------------------------
HRESULT CGarbageCollect::Init(MODEL model)
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
//- ゴミ回収の終了処理
//-------------------------------------
void CGarbageCollect::Uninit(void)
{
	// Xファイルオブジェクトの終了
	CObjectX::Uninit();
}

//-------------------------------------
//- ゴミ回収の更新処理
//-------------------------------------
void CGarbageCollect::Update(void)
{
	// Xファイルオブジェクトの更新処理
	CObjectX::Update();
}

//-------------------------------------
//- ゴミ回収の描画処理
//-------------------------------------
void CGarbageCollect::Draw(void)
{
	// ゴミ回収の描画処理
	CObjectX::Draw();
}

//-------------------------------------
//- ゴミ回収の生成処理
//-------------------------------------
CGarbageCollect *CGarbageCollect::Create(MODEL model)
{
	// ゴミ回収の生成
	CGarbageCollect *pCGarbageCollect = new CGarbageCollect;

	// 生成の成功の有無を判定
	if (pCGarbageCollect != NULL)
	{
		// 初期化処理
		if (FAILED(pCGarbageCollect->Init(model)))
		{// 失敗時

		 // 「なし」を返す
			return NULL;
		}
	}
	else if (pCGarbageCollect == NULL)
	{// 失敗時

	 // 「なし」を返す
		return NULL;
	}

	// ゴミ回収のポインタを返す
	return pCGarbageCollect;
}

//-------------------------------------
//-	ゴミ回収の設定処理
//-------------------------------------
void CGarbageCollect::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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
int CGarbageCollect::GetModel(void)
{
	// モデル設定
	return(int)m_model;
}

//-------------------------------------
//-	モデルの設定処理
//-------------------------------------
void CGarbageCollect::SetModel(int nModelNldx)
{
	// モデル設定
	m_model = (MODEL)nModelNldx;
}

//-------------------------------------
//-	モデルの情報の設定処理
//-------------------------------------
void CGarbageCollect::SetModelData(int nNum, CGarbageCollect::ModelData modelData)
{
	// モデル情報の代入
	m_modelData[nNum] = modelData;	// 大きさ
}

//-------------------------------------
//-	モデルの情報の取得処理
//-------------------------------------
CGarbageCollect::ModelData CGarbageCollect::GetModelData(int nNum)
{
	// モデル情報を返す
	return m_modelData[nNum];
}

//-------------------------------------
//- ゴミ回収の実行処理
//-------------------------------------
void CGarbageCollect::Execution(int nNum)
{
	return;
}

//-------------------------------------
//- ゴミ回収の初期設定処理
//-------------------------------------
void CGarbageCollect::InitSet(MODEL model)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();	// 位置
	D3DXVECTOR3 rot = m_dataRot.Get();	// 向き

	// 情報更新
	m_dataPosOld.Set(pos);				// 前回の位置
	m_dataRotDest.Set(rot);				// 目的の向き
}
