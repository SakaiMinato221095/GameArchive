
//-===============================================
//-
//-	2Dのアイテム情報の処理[obj_2d_item_info.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "obj_2d_item_info.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"
#include "manager_object.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//= コンスト定義
//=======================================

// アイテム情報のコンスト定義
const char *pTextureItemInfo[] =
{
	"data\\TEXTURE\\item_info_gun.png",		// 弾のテクスチャ
	"data\\TEXTURE\\item_info_gun.png",		// 弾のテクスチャ
	"data\\TEXTURE\\item_info_gun.png",		// 弾のテクスチャ
	"data\\TEXTURE\\item_info_bomb.png",	// ボムのテクスチャ
};

//-======================================
//-	静的変数宣言
//-======================================

int CObj2dItemInfo::m_nTextureNldx[CItem::MODEL_MAX] = {};	// テクスチャ

//-------------------------------------
//-	2Dのアイテム情報のコンストラクタ
//-------------------------------------
CObj2dItemInfo::CObj2dItemInfo(int nPriority) : CObject2d(nPriority)
{

}

//-------------------------------------
//-	2Dのアイテム情報のデストラクタ
//-------------------------------------
CObj2dItemInfo::~CObj2dItemInfo()
{

}

//-------------------------------------
//- 2Dのアイテム情報のテクスチャの読み込み
//-------------------------------------
HRESULT CObj2dItemInfo::Load(void)
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
	for (int nCount = 0; nCount < CItem::MODEL_MAX; nCount++)
	{
		// テクスチャ番号の取得（テクスチャの割当）
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureItemInfo[nCount]);

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
//- 2Dのアイテム情報の読み込んだテクスチャの破棄
//-------------------------------------
void CObj2dItemInfo::Unload(void)
{

}

//-------------------------------------
//- 2Dのアイテム情報の初期化処理
//-------------------------------------
HRESULT CObj2dItemInfo::Init(CItem::MODEL nModel)
{
	// テクスチャ割当
	BindTexture(m_nTextureNldx[nModel]);

	// 初期設定
	InitSet();

	// 2Dオブジェクトの初期化
	CObject2d::Init();

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 2Dのアイテム情報の終了処理
//-------------------------------------
void CObj2dItemInfo::Uninit(void)
{
	// 2Dオブジェクトの終了
	CObject2d::Uninit();
}

//-------------------------------------
//- 2Dのアイテム情報の更新処理
//-------------------------------------
void CObj2dItemInfo::Update(void)
{
	// 2Dオブジェクトの更新処理
	CObject2d::Update();
}

//-------------------------------------
//- 2Dのアイテム情報の描画処理
//-------------------------------------
void CObj2dItemInfo::Draw(void)
{
	// 変数宣言（情報取得）
	bool bDraw = m_bDataDraw.Get();	// 描画の有無

	if (bDraw == true)
	{
		// 2dオブジェクトの描画処理
		CObject2d::Draw();

		// 描画停止を解除
		bDraw = false;
	}

	// 情報更新
	m_bDataDraw.Set(bDraw);	// 描画の有無
}

//-------------------------------------
//- 2Dのアイテム情報の生成処理
//-------------------------------------
CObj2dItemInfo *CObj2dItemInfo::Create(CItem::MODEL nModel)
{
	// 2Dのアイテム情報のポインタを宣言
	CObj2dItemInfo *pCObj2dItemInfo = DBG_NEW CObj2dItemInfo(7);

	// 生成の成功の有無を判定
	if (pCObj2dItemInfo != NULL)
	{
		// 初期化処理 if(初期化成功の有無を判定)
		if (FAILED(pCObj2dItemInfo->Init(nModel)))
		{// 失敗時

		 // 「なし」を返す
			return NULL;
		}
	}
	else if (pCObj2dItemInfo == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// 種類を設定
	pCObj2dItemInfo->SetType(TYPE_BLOCK);

	// 2Dのアイテム情報のポインタを返す
	return pCObj2dItemInfo;
}

//-------------------------------------
//- 2Dのアイテム情報の設定処理
//-------------------------------------
void CObj2dItemInfo::Set(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_dataPos.Set(pos);
	m_dataSize.Set(size);
}

//-------------------------------------
//- 2Dのアイテム情報の初期設定処理
//-------------------------------------
void CObj2dItemInfo::InitSet(void)
{
	m_dataPos.Set(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.85f, 0.0f));
	m_dataSize.Set(D3DXVECTOR3(SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.1f, 0.0f));
}