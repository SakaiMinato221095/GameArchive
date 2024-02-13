
//-===============================================
//-
//-	効果なしオブジェクトの処理[item.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "objectx_test.h"

#include "renderer.h"
#include "manager.h"

#include "manager_object.h"

#include "manager_model.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	コンスト定義
//=======================================

// テスト用オブジェクトのモデルのコンスト定義
const char *pModelObjectXTest[] =
{
	"data\\MODEL\\human_box.x",		// 人型の基準モデル
};

//-======================================
//-	静的変数宣言
//-======================================

CDataInt CObjectXTest::m_nDataModelNldx[MODEL_MAX] = {};		// モデルの番号

//-------------------------------------
//-	効果なしオブジェクトのコンストラクタ
//-------------------------------------
CObjectXTest::CObjectXTest()
{
	m_model = MODEL_HUMAN_BOX_000;
}

//-------------------------------------
//-	効果なしオブジェクトのデストラクタ
//-------------------------------------
CObjectXTest::~CObjectXTest()
{

}

//-------------------------------------
//- 敵のモデル読み込み
//-------------------------------------
HRESULT CObjectXTest::Load(void)
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
		nModelNldx = pManagerModel->Regist(pModelObjectXTest[nCount]);

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
void CObjectXTest::Unload(void)
{

}

//-------------------------------------
//- 効果なしオブジェクトの初期化処理（Xファイルオブジェクト設定）
//-------------------------------------
HRESULT CObjectXTest::Init(MODEL model)
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
//- 効果なしオブジェクトの終了処理
//-------------------------------------
void CObjectXTest::Uninit(void)
{
	// Xファイルオブジェクトの終了
	CObjectX::Uninit();
}

//-------------------------------------
//- 効果なしオブジェクトの更新処理
//-------------------------------------
void CObjectXTest::Update(void)
{
	// Xファイルオブジェクトの更新処理
	CObjectX::Update();
}

//-------------------------------------
//- 効果なしオブジェクトの描画処理
//-------------------------------------
void CObjectXTest::Draw(void)
{
	// Xファイルオブジェクトの描画処理
	CObjectX::Draw();
}

//-------------------------------------
//- 効果なしオブジェクトの生成処理（Xファイルオブジェクト設定）
//-------------------------------------
CObjectXTest * CObjectXTest::Create(MODEL model)
{
	// 効果なしオブジェクトのポインタを宣言
	CObjectXTest *pCObjectXTest = new CObjectXTest;

	// 生成の成功の有無を判定
	if (pCObjectXTest != NULL)
	{
		// 初期化処理
		if (FAILED(pCObjectXTest->Init(model)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCObjectXTest == NULL)
	{// 失敗時

	 // 「なし」を返す
		return NULL;
	}

	// 効果なしオブジェクトのポインタを返す
	return pCObjectXTest;
}

//-------------------------------------
//-	モデルの設定処理
//-------------------------------------
int CObjectXTest::GetModel(void)
{
	// モデル設定
	return(int)m_model;
}

//-------------------------------------
//-	モデルの設定処理
//-------------------------------------
void CObjectXTest::SetModel(int nModelNldx)
{
	// モデル設定
	m_model = (MODEL)nModelNldx;
}

//-------------------------------------
//- 効果なしオブジェクトの設定処理
//-------------------------------------
void CObjectXTest::Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	// 情報更新
	m_dataPos.Set(pos);		// 位置
	m_dataPosOld.Set(pos);	// 前回の位置

	m_dataSize.Set(size);	// 大きさ

	m_dataRot.Set(rot);		// 移動量
	m_dataRotDest.Set(rot);	// 目的の向き
}