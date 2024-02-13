
//-===============================================
//-
//-	目標UIの処理[ui_mission.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "ui_mission.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//= コンスト定義
//=======================================

// 目標UIテクスチャのコンスト定義
const char *pTextureUiMission[] =
{
	"data\\TEXTURE\\mission_search.png",			// 探索のテクスチャ
	"data\\TEXTURE\\mission_shop.png",				// 購入のテクスチャ
	"data\\TEXTURE\\mission_battle_normal.png",		// 戦闘（雑魚）のテクスチャ
	"data\\TEXTURE\\mission_battle_boss.png",		// 戦闘（ボス）のテクスチャ
};

//-======================================
//-	静的変数宣言
//-======================================

int CUiMission::m_nTextureNldx[TEX_MAX] = {};	// テクスチャ

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CUiMission::CUiMission(int nPriority) : CObject2d(nPriority)
{

}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CUiMission::~CUiMission()
{

}

//-------------------------------------
//- 目標UIのテクスチャの読み込み
//-------------------------------------
HRESULT CUiMission::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// デバイスの情報取得の成功を判定
	if (pDevice == NULL)
	{// 失敗時

	 // 初期化処理を抜ける
		return E_FAIL;
	}

	// テクスチャ管理の生成
	CManagerTexture *pManagerTexture = CManager::GetManagerTexture();

	// テクスチャ管理の有無を判定
	if (pManagerTexture == NULL)
	{
		// 初期化処理を抜ける
		return E_FAIL;
	}

	// テクスチャ設定
	for (int nCount = 0; nCount < TEX_MAX; nCount++)
	{
		// テクスチャ番号の取得（テクスチャの割当）
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureUiMission[nCount]);

		// テクスチャの読み込み成功の有無を確認
		if (m_nTextureNldx[nCount] == -1)
		{
			// 失敗時に初期化処理を抜ける
			return E_FAIL;
		}
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 目標UIの読み込んだテクスチャの破棄
//-------------------------------------
void CUiMission::Unload(void)
{

}

//-------------------------------------
//- 目標UIの初期化処理
//-------------------------------------
HRESULT CUiMission::Init(TEX tex)
{
	// テクスチャ割当
	BindTexture(m_nTextureNldx[tex]);

	// 2Dオブジェクトの初期化
	CObject2d::Init();

	// 初期設定処理
	InitSet();

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 目標UIの終了処理
//-------------------------------------
void CUiMission::Uninit(void)
{
	// 2Dオブジェクトの終了
	CObject2d::Uninit();
}

//-------------------------------------
//- 目標UIの更新処理
//-------------------------------------
void CUiMission::Update(void)
{
	// 後回し描画のオン
	m_bDataAfterDraw.Set(true);

	// 頂点情報の設定処理
	CObject2d::Update();
}

//-------------------------------------
//- 目標UIの描画処理
//-------------------------------------
void CUiMission::Draw(void)
{
	// 2Dオブジェクトの描画処理
	CObject2d::Draw();
}

//-------------------------------------
//- 目標UIの生成処理
//-------------------------------------
CUiMission *CUiMission::Create(TEX tex)
{
	// 目標UIのポインタを宣言
	CUiMission *pCUiMission = DBG_NEW CUiMission(7);

	// 生成の成功の有無を判定
	if (pCUiMission != NULL)
	{
		// 初期化処理 if(目標UIの初期化成功の有無を判定)
		if (FAILED(pCUiMission->Init(tex)))
		{// 失敗時

		 // 「なし」を返す
			return NULL;
		}
	}
	else if (pCUiMission == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// 目標UIのポインタを返す
	return pCUiMission;
}

//-------------------------------------
//- 目標UIの設定処理
//-------------------------------------
void CUiMission::Set(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 情報代入
	m_dataPos.Set(pos);
	m_dataSize.Set(size);
}

//-------------------------------------
//- 目標UIのテクスチャ番号を返す
//-------------------------------------
int CUiMission::GetTexNldx(TEX tex)
{
	return m_nTextureNldx[tex];
}

//-------------------------------------
//- 目標UIの初期設定処理
//-------------------------------------
void CUiMission::InitSet(void)
{
	m_dataPos.Set(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.1f, 0.0f));
	m_dataSize.Set(D3DXVECTOR3(200.0f, 50.0f, 0.0f));
}