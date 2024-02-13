
//-===============================================
//-
//-	ゴミの処理[garbage.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "garbage.h"

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

// ゴミのモデルのコンスト定義
const char *pModelGarbage[] =
{
	"data\\MODEL\\garbage\\bin.x",					// 瓶のモデル

	"data\\MODEL\\garbage\\blood_knife.x",			// 血付きのナイフ
	"data\\MODEL\\garbage\\organ_bottle_none.x",	// 中身なし臓器保管瓶
	"data\\MODEL\\garbage\\syringe_none.x",			// 中身なし注射器

	"data\\MODEL\\garbage\\ice_cup.x",				// かき氷かっぷ
	"data\\MODEL\\garbage\\omikuji.x",				// おみくじ
	"data\\MODEL\\garbage\\puragomi.x",				// ぷらごみ
};

//-======================================
//-	静的変数宣言
//-======================================

CDataInt CGarbage::m_nDataModelNldx[MODEL_MAX] = {};

CGarbage::ModelData CGarbage::m_modelData[MODEL_MAX] = {};		// モデル情報

//-------------------------------------
//-	ゴミのコンストラクタ
//-------------------------------------
CGarbage::CGarbage()
{
	m_model = (MODEL)0;
	m_scoreGetType = CScore::GET_TYPE_NORMAL;
}

//-------------------------------------
//-	ゴミのデストラクタ
//-------------------------------------
CGarbage::~CGarbage()
{

}

//-------------------------------------
//- ゴミのモデル読み込み
//-------------------------------------
HRESULT CGarbage::Load(void)
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
		nModelNldx = pManagerModel->Regist(pModelGarbage[nCount]);

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
//- ゴミの読み込んだモデル破棄
//-------------------------------------
void CGarbage::Unload(void)
{

}

//-------------------------------------
//- ゴミの初期化処理
//-------------------------------------
HRESULT CGarbage::Init(MODEL model)
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
//- ゴミの終了処理
//-------------------------------------
void CGarbage::Uninit(void)
{
	// Xファイルオブジェクトの終了
	CObjectX::Uninit();
}

//-------------------------------------
//- ゴミの更新処理
//-------------------------------------
void CGarbage::Update(void)
{
	// Xファイルオブジェクトの更新処理
	CObjectX::Update();
}

//-------------------------------------
//- ゴミの描画処理
//-------------------------------------
void CGarbage::Draw(void)
{
	// ゴミの描画処理
	CObjectX::Draw();
}

//-------------------------------------
//- ゴミの生成処理
//-------------------------------------
CGarbage *CGarbage::Create(MODEL model)
{
	// ゴミの生成
	CGarbage *pCGarbage = new CGarbage;
	
	// 生成の成功の有無を判定
	if (pCGarbage != NULL)
	{
		// 初期化処理
		if (FAILED(pCGarbage->Init(model)))
		{// 失敗時

		 // 「なし」を返す
			return NULL;
		}
	}
	else if (pCGarbage == NULL)
	{// 失敗時

	 // 「なし」を返す
		return NULL;
	}

	// ゴミのポインタを返す
	return pCGarbage;
}

//-------------------------------------
//-	ゴミの設定処理
//-------------------------------------
void CGarbage::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 情報更新
	m_dataPos.Set(pos);							// 位置
	m_dataPosOld.Set(pos);						// 前回の位置

	m_dataRot.Set(rot);							// 向き
	m_dataRotDest.Set(rot);						// 目的の向き

	m_dataSize.Set(
		D3DXVECTOR3(10.0f, 0.0f, 10.0f));		// 大きさ

	m_scoreGetType = CScore::GET_TYPE_RANDOM;	// スコアの取得系統

	m_nGetScore.Set(0);							// スコアの入手量	
}

//-------------------------------------
//-	モデルの設定処理
//-------------------------------------
int CGarbage::GetModel(void)
{
	// モデル設定
	return(int)m_model;
}

//-------------------------------------
//-	モデルの設定処理
//-------------------------------------
void CGarbage::SetModel(int nModelNldx)
{
	// モデル設定
	m_model = (MODEL)nModelNldx;
}

//-------------------------------------
//-	モデルの情報の設定処理
//-------------------------------------
void CGarbage::SetModelData(int nNum, CGarbage::ModelData modelData)
{
	// モデル情報の代入
	m_modelData[nNum] = modelData;	// 大きさ
}

//-------------------------------------
//-	モデルの情報の取得処理
//-------------------------------------
CGarbage::ModelData CGarbage::GetModelData(int nNum)
{
	// モデル情報を返す
	return m_modelData[nNum];
}

//-------------------------------------
//- ゴミの初期設定処理
//-------------------------------------
void CGarbage::InitSet(MODEL model)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();	// 位置
	D3DXVECTOR3 rot = m_dataRot.Get();	// 向き

	// 情報更新
	m_dataPosOld.Set(pos);				// 前回の位置
	m_dataRotDest.Set(rot);				// 目的の向き

	m_scoreGetType = CScore::GET_TYPE_RANDOM;	// スコアの取得系統

	m_nGetScore.Set(0);							// スコアの入手量
}