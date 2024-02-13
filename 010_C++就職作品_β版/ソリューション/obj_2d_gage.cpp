
//================================================
//=
//=	ゲージ処理[obj_2d_gage.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "obj_2d_gage.h"

#include "manager.h"
#include "renderer.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//= コンスト定義
//=======================================

//=======================================
//=	静的変数宣言
//=======================================

//-------------------------------------
//-	ゲージのコンストラクタ
//-------------------------------------
CObj2dGage::CObj2dGage(int nPriority) : CObject2d(nPriority)
{

}

//-------------------------------------
//-	ゲージのデストラクタ
//-------------------------------------
CObj2dGage::~CObj2dGage()
{

}

//-------------------------------------
//- ゲージの初期化処理
//-------------------------------------
HRESULT CObj2dGage::Init(void)
{
	// 2Dオブジェクトの初期化
	CObject2d::Init();

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- ゲージの終了処理
//-------------------------------------
void CObj2dGage::Uninit(void)
{
	// 2Dオブジェクトの終了処理
	CObject2d::Uninit();
}

//-------------------------------------
//- ゲージの更新処理
//-------------------------------------
void CObj2dGage::Update(void)
{
	// 頂点情報の設定処理
	SetVtx();
}

//-------------------------------------
//- ゲージの描画処理
//-------------------------------------
void CObj2dGage::Draw(void)
{
	// 2Dオブジェクトの描画処理
	CObject2d::Draw();
}

//-------------------------------------
//-	ゲージの生成処理
//-------------------------------------
CObj2dGage* CObj2dGage::Create(void)
{
	// ゲージの生成
	CObj2dGage *pNumber = DBG_NEW CObj2dGage(7);

	// 生成の成功の有無を判定
	if (pNumber != NULL)
	{
		// 初期化処理
		if (FAILED(pNumber->Init()))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pNumber == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// ゲージのポインタを返す
	return pNumber;
}

//-------------------------------------
//- ゲージの頂点情報設定
//-------------------------------------
void CObj2dGage::SetVtx(void)
{
	// 頂点バッファをポインタを宣言
	LPDIRECT3DVERTEXBUFFER9 vtxBuff = GetVtxBuff();

	// 頂点バッファ取得成功の有無を判定
	if (vtxBuff == NULL)
	{// 失敗時

	 // 頂点情報設定を抜ける
		return;
	}

	// 情報取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize();
	D3DXCOLOR color = GetColor();

	// 2D頂点情報のポインタを宣言
	VERTEX_2D* pVtx = NULL;

	// 頂点バッファをロックし、頂点情報のポインタを取得
	vtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	pVtx[0].pos = D3DXVECTOR3(-size.x, size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3( size.x * (-1.0f + (m_info.fRateData * 2)), size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-size.x, -size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3( size.x * (-1.0f + (m_info.fRateData * 2)), -size.y, 0.0f);
	
	  
	pVtx[0].pos = D3DXVECTOR3(pos.x -  size.x,										pos.y - size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + (size.x * (-1.0f + (m_info.fRateData * 2))),	pos.y - size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x -  size.x,										pos.y + size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + (size.x * (-1.0f + (m_info.fRateData * 2))),	pos.y + size.y, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーを設定
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	// テクスチャの座標を設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	vtxBuff->Unlock();
}


