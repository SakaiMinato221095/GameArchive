
//-===============================================
//-
//-	地面処理[obj_3d_field.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "obj_3d_field.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	コンスト定義
//=======================================

// 3D地面のテクスチャのコンスト定義
const char *pTextureField[] =
{
	NULL,										// テクスチャなし
	"data\\TEXTURE\\WhiteTile000.jpg",			// フィールドのテクスチャ
	"data\\TEXTURE\\road000.png",				// 道路のテクスチャ
	"data\\TEXTURE\\asphalt000.jpg",			// アスファルトのテクスチャ
	"data\\TEXTURE\\field_glass000.jpg",		// 草床のテクスチャ
};

//-======================================
//-	静的変数宣言
//-======================================

int CObj3dField::m_nTextureNldx[TEX_MAX] = {};

//-------------------------------------
//-	3D地面のコンストラクタ
//-------------------------------------
CObj3dField::CObj3dField(int nPriority) : CObject3d(nPriority)
{

}

//-------------------------------------
//-	3D地面のデストラクタ
//-------------------------------------
CObj3dField::~CObj3dField()
{

}

//-------------------------------------
//- 3D地面のテクスチャの読み込み
//-------------------------------------
HRESULT CObj3dField::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// デバイスの情報取得の成功を判定
	if (pDevice == NULL)
	{// 失敗時

	 // 初期化処理を抜ける
		return E_FAIL;
	}

	// テクスチャ管理の生成
	CManagerTexture *pManagerTexture = CManager::GetInstance()->GetManagerTexture();

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
//- 3D地面の読み込んだテクスチャの破棄
//-------------------------------------
void CObj3dField::Unload(void)
{

}
//-------------------------------------
//- 3D地面の初期化処理（3Dオブジェクト設定）
//-------------------------------------
HRESULT CObj3dField::Init(TEX tex)
{
	// テクスチャ割当
	BindTexture(m_nTextureNldx[tex]);

	// 3Dオブジェクトの初期化
	CObject3d::Init();

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 3D地面の終了処理
//-------------------------------------
void CObj3dField::Uninit(void)
{
	// 3Dオブジェクトの終了
	CObject3d::Uninit();
}

//-------------------------------------
//- 3D地面の更新処理
//-------------------------------------
void CObj3dField::Update(void)
{
	// 3Dオブジェクトの更新処理
	CObject3d::Update();
}

//-------------------------------------
//- 3D地面の描画処理
//-------------------------------------
void CObj3dField::Draw(void)
{
	// 3Dオブジェクトの描画処理
	CObject3d::Draw();
}

//-------------------------------------
//- 3D地面の生成処理
//-------------------------------------
CObj3dField *CObj3dField::Create(TEX tex)
{
	// フィールドのポインタを宣言
	CObj3dField *pCObj3dField = DBG_NEW CObj3dField(4);

	// 生成の成功の有無を判定
	if (pCObj3dField != NULL)
	{
		// 初期化処理
		if (FAILED(pCObj3dField->Init(tex)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCObj3dField == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// フィールドのポインタを返す
	return pCObj3dField;
}

//-------------------------------------
//-	3Dオブジェクトの頂点情報設定処理
//-------------------------------------
void CObj3dField::SetVtx(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 size = GetVtxData().size;		// サイズ
	D3DXCOLOR color = GetVtxData().color;		// 色
	D3DXVECTOR2 texPos = GetVtxData().texPos;	// テクスチャ位置

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// デバイスの情報取得の成功を判定
	if (pDevice == NULL)
	{// 失敗時

	 // 初期化処理を抜ける
		return;
	}
	
	if (GetVtxBuff() != nullptr)
	{
		// 3D頂点情報のポインタを宣言
		VERTEX_3D* pVtx;

		//頂点バッファをロックし、頂点データのポインタを取得
		GetVtxBuff()->Lock(
			0,
			0,
			(void**)&pVtx,
			0);

		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(-size.x, 0.0f, size.z);
		pVtx[1].pos = D3DXVECTOR3(size.x, 0.0f, size.z);
		pVtx[2].pos = D3DXVECTOR3(-size.x, 0.0f, -size.z);
		pVtx[3].pos = D3DXVECTOR3(size.x, 0.0f, -size.z);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーを設定
		pVtx[0].col = color;
		pVtx[1].col = color;
		pVtx[2].col = color;
		pVtx[3].col = color;

		//テクスチャの座標を設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(texPos.x, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, texPos.y);
		pVtx[3].tex = D3DXVECTOR2(texPos.x, texPos.y);

		//頂点バッファをアンロックする
		GetVtxBuff()->Unlock();
	}
}