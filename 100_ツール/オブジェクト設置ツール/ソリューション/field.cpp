
//-===============================================
//-
//-	地面処理[field.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "field.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	コンスト定義
//=======================================

// フィールドのテクスチャのコンスト定義
const char *pTextureField[] =
{
	"data\\TEXTURE\\WhiteTile000.jpg",			// フィールドのテクスチャ
	"data\\TEXTURE\\road000.png",				// 道路のテクスチャ
	"data\\TEXTURE\\asphalt000.jpg",			// アスファルトのテクスチャ
	"data\\TEXTURE\\field_glass000.jpg",		// 草床のテクスチャ
	"data\\TEXTURE\\0128_tile.jpg",
};

//-======================================
//-	静的変数宣言
//-======================================

int CField::m_nTextureNldx[TEX_MAX] = {};

//-------------------------------------
//-	フィールドのコンストラクタ
//-------------------------------------
CField::CField()
{

}

//-------------------------------------
//-	フィールドのデストラクタ
//-------------------------------------
CField::~CField()
{

}

//-------------------------------------
//- 背景のテクスチャの読み込み
//-------------------------------------
HRESULT CField::Load(void)
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
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureField[nCount]);

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
//- 背景の読み込んだテクスチャの破棄
//-------------------------------------
void CField::Unload(void)
{

}
//-------------------------------------
//- フィールドの初期化処理（3Dオブジェクト設定）
//-------------------------------------
HRESULT CField::Init(TEX tex)
{
	// テクスチャ割当
	BindTexture(m_nTextureNldx[tex]);

	// 3Dオブジェクトの初期化
	CObject3d::Init();

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- フィールドの終了処理
//-------------------------------------
void CField::Uninit(void)
{
	// 3Dオブジェクトの終了
	CObject3d::Uninit();
}

//-------------------------------------
//- フィールドの更新処理
//-------------------------------------
void CField::Update(void)
{
	// 3Dオブジェクトの更新処理
	CObject3d::Update();
}

//-------------------------------------
//- フィールドの描画処理
//-------------------------------------
void CField::Draw(void)
{
	// 3Dオブジェクトの描画処理
	CObject3d::Draw();
}

//-------------------------------------
//- フィールドの生成処理
//-------------------------------------
CField *CField::Create(TEX tex)
{
	// フィールドのポインタを宣言
	CField *pCField = new CField;

	// 生成の成功の有無を判定
	if (pCField != NULL)
	{
		// 初期化処理
		if (FAILED(pCField->Init(tex)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCField == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// フィールドのポインタを返す
	return pCField;
}

//-------------------------------------
//- フィールドの設定処理
//-------------------------------------
void CField::Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	// 情報更新
	m_dataPos.Set(pos);		// 位置

	m_dataSize.Set(size);	// 大きさ

	m_dataRot.Set(rot);		// 移動量

	CObject3d::SetVtx();
}
