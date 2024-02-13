
//================================================
//=
//= ゲージのビルボードの処理[billboard_gage.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "billboard_gage.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

//=======================================
//=	マクロ定義
//=======================================

//------------------------------------
//- ビルボードオブジェクトのコンストラクタ
//------------------------------------
CBillboardGage::CBillboardGage(int nPriority) : CBillboard(nPriority)
{
	// 値をクリア
	ZeroMemory(&m_info, sizeof(m_info));
}

//------------------------------------
//- ビルボードオブジェクトのデストラクタ
//------------------------------------
CBillboardGage::~CBillboardGage()
{
}

//------------------------------------
//- ビルボードオブジェクトの初期化処理
//------------------------------------
HRESULT CBillboardGage::Init(void)
{
	CBillboard::Init();

	// 成功の返す
	return S_OK;
}

//-------------------------------------
//- ビルボードオブジェクトの終了処理
//-------------------------------------
void CBillboardGage::Uninit(void)
{
	CBillboard::Uninit();
}

//-------------------------------------
//- ビルボードオブジェクトの更新処理
//-------------------------------------
void CBillboardGage::Update(void)
{
	CBillboard::Update();

	// 頂点情報を設定
	SetVtx();
}

//-------------------------------------
//- ビルボードオブジェクトの描画処理
//-------------------------------------
void CBillboardGage::Draw(void)
{
	CBillboard::Draw();
}

//-------------------------------------
//-	ビルボードオブジェクトの生成処理
//-------------------------------------
CBillboardGage* CBillboardGage::Create(void)
{
	// ポインタを宣言
	CBillboardGage* pBillboardGage = NULL;

	// 生成
	pBillboardGage = DBG_NEW CBillboardGage;

	// 生成の成功の有無を判定
	if (pBillboardGage != NULL)
	{
		// 初期化処理
		if (FAILED(pBillboardGage->Init()))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pBillboardGage == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// ポインタを返す
	return pBillboardGage;
}

//-------------------------------------
//- ビルボードオブジェクトの頂点情報設定
//-------------------------------------
void CBillboardGage::SetVtx(void)
{
	if (GetVtxBuff() != nullptr)
	{
		// 情報取得
		D3DXVECTOR3 size = GetSize();
		D3DXCOLOR color = GetColor();

		// 3D頂点情報のポインタを宣言
		VERTEX_3D* pVtx = nullptr;

		// 頂点バッファをロックし、頂点情報のポインタを取得
		GetVtxBuff()->Lock(
			0,
			0,
			(void**)&pVtx,
			0);
		
		//頂点座標を設定
		pVtx[0].pos = D3DXVECTOR3(-size.x, size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3( size.x * (-1.0f + (m_info.fRateData * 2)), size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-size.x, -size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3( size.x * (-1.0f + (m_info.fRateData * 2)), -size.y, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点バッファをアンロックする
		GetVtxBuff()->Unlock();
	}
}