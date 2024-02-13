
//-===============================================
//-
//-	効果なしオブジェクトの処理[item.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "objectx_none.h"

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

// 効果なしオブジェクトのモデルのコンスト定義
const char *pModelObjectXNone[] =
{
	"data\\MODEL\\none\\obarafood.x",			// 商店街（食堂）
	"data\\MODEL\\none\\obamart.x",				// 商店街（半額店）
	"data\\MODEL\\none\\obarastation.x",		// 商店街（ゲームセンター）
	"data\\MODEL\\none\\obarakurabu000.x",		// 商店街（雑貨店）	
	"data\\MODEL\\none\\obarameat000.x",		// 商店街（精肉店）	
	"data\\MODEL\\none\\obaravegetable000.x",	// 商店街（青果店）	
	"data\\MODEL\\none\\obaraflour000.x",		// 商店街（花屋）	
	"data\\MODEL\\none\\obaraclothes000.x",		// 商店街（服屋）	

	"data\\MODEL\\none\\sunaba001.x",			// 公園（砂場）
	"data\\MODEL\\none\\Toilet001.x",			// 公園（トイレ）
	"data\\MODEL\\none\\suidou.x",				// 公園（水道）
	"data\\MODEL\\none\\gomibako001.x",			// 公園（ゴミ箱）
	"data\\MODEL\\none\\benti001.x",			// 公園（ベンチ）
	"data\\MODEL\\none\\gaitou001.x",			// 公園（街灯）
	"data\\MODEL\\none\\tetubou001.x",			// 公園（鉄棒）
	"data\\MODEL\\none\\suberidai001.x",		// 公園（滑り台）

	"data\\MODEL\\none\\House001.x",			// 家（1）
	"data\\MODEL\\none\\House002.x",			// 家（2）
	"data\\MODEL\\none\\House003.x",			// 家（3）

	"data\\MODEL\\none\\street_stall_dark.x",	// 闇露店
	"data\\MODEL\\none\\house_blood.x",			// 血付きの家

	"data\\MODEL\\none\\zinja.x",				// 神社
	"data\\MODEL\\none\\omikuji.x",				// おみくじ

	"data\\MODEL\\none\\yakisoba.x",			// やきそば
	"data\\MODEL\\none\\kakigoori.x",			// かき氷
	"data\\MODEL\\none\\wanage.x",				// 輪投げ
	"data\\MODEL\\none\\takoyaki.x",			// たこやき
	"data\\MODEL\\none\\yo-yo-turi.x",			// よーよー釣り

	"data\\MODEL\\none\\tree.x",				// 木
	"data\\MODEL\\none\\bld_torii.x",			// 鳥居

	"data\\MODEL\\none\\NinjaMansion000.x",		// 屋敷
	"data\\MODEL\\none\\Scarecrow000.x",		// かかし
	"data\\MODEL\\none\\sisiodosi000.x",		// ししおどし
	"data\\MODEL\\none\\Sakura000.x",			// 桜

	"data\\MODEL\\none\\plant.x",				// 工場

	

};

//-======================================
//-	静的変数宣言
//-======================================

CDataInt CObjectXNone::m_nDataModelNldx[MODEL_MAX] = {};		// モデルの番号

//-------------------------------------
//-	効果なしオブジェクトのコンストラクタ
//-------------------------------------
CObjectXNone::CObjectXNone()
{
	m_model = MODEL(0);
}

//-------------------------------------
//-	効果なしオブジェクトのデストラクタ
//-------------------------------------
CObjectXNone::~CObjectXNone()
{

}

//-------------------------------------
//- 敵のモデル読み込み
//-------------------------------------
HRESULT CObjectXNone::Load(void)
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
		nModelNldx = pManagerModel->Regist(pModelObjectXNone[nCount]);

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
void CObjectXNone::Unload(void)
{

}

//-------------------------------------
//- 効果なしオブジェクトの初期化処理（Xファイルオブジェクト設定）
//-------------------------------------
HRESULT CObjectXNone::Init(MODEL model)
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
//- 効果なしオブジェクトの終了処理
//-------------------------------------
void CObjectXNone::Uninit(void)
{
	// Xファイルオブジェクトの終了
	CObjectX::Uninit();
}

//-------------------------------------
//- 効果なしオブジェクトの更新処理
//-------------------------------------
void CObjectXNone::Update(void)
{
	// Xファイルオブジェクトの更新処理
	CObjectX::Update();
}

//-------------------------------------
//- 効果なしオブジェクトの描画処理
//-------------------------------------
void CObjectXNone::Draw(void)
{
	// Xファイルオブジェクトの描画処理
	CObjectX::Draw();
}

//-------------------------------------
//- 効果なしオブジェクトの生成処理（Xファイルオブジェクト設定）
//-------------------------------------
CObjectXNone * CObjectXNone::Create(MODEL model)
{
	// 効果なしオブジェクトのポインタを宣言
	CObjectXNone *pCObjectXNone = new CObjectXNone;

	// 生成の成功の有無を判定
	if (pCObjectXNone != NULL)
	{
		// 初期化処理
		if (FAILED(pCObjectXNone->Init(model)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCObjectXNone == NULL)
	{// 失敗時

	 // 「なし」を返す
		return NULL;
	}

	// 効果なしオブジェクトのポインタを返す
	return pCObjectXNone;
}

//-------------------------------------
//-	モデルの設定処理
//-------------------------------------
int CObjectXNone::GetModel(void)
{
	// モデル設定
	return(int)m_model;
}

//-------------------------------------
//-	モデルの設定処理
//-------------------------------------
void CObjectXNone::SetModel(int nModelNldx)
{
	// モデル設定
	m_model = (MODEL)nModelNldx;
}

//-------------------------------------
//- 効果なしオブジェクトの設定処理
//-------------------------------------
void CObjectXNone::Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	// 情報更新
	m_dataPos.Set(pos);		// 位置
	m_dataPosOld.Set(pos);	// 前回の位置

	m_dataSize.Set(size);	// 大きさ

	m_dataRot.Set(rot);		// 移動量
	m_dataRotDest.Set(rot);	// 目的の向き
}