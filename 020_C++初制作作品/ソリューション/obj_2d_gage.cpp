
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

#include "manager_texture.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//= コンスト定義
//=======================================

// ゲージテクスチャのコンスト定義
const char *pTextureObj2dGage[] =
{
	NULL	// なし
};

//=======================================
//=	静的変数宣言
//=======================================

int CObj2dGage::m_nTextureNldx[TEX_MAX] = {};

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
//- ゲージの読み込み処理
//-------------------------------------
HRESULT CObj2dGage::Load(void)
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
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureObj2dGage[nCount]);

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
void CObj2dGage::Unload(void)
{

}

//-------------------------------------
//- ゲージの初期化処理
//-------------------------------------
HRESULT CObj2dGage::Init(TEX tex)
{
	// 使用テクスチャの設定
	BindTexture(m_nTextureNldx[tex]);

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
CObj2dGage *CObj2dGage::Create(TEX tex)
{
	// ゲージの生成
	CObj2dGage *pNumber = DBG_NEW CObj2dGage(7);

	// 生成の成功の有無を判定
	if (pNumber != NULL)
	{
		// 初期化処理
		if (FAILED(pNumber->Init(tex)))
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
	// 変数宣言（情報の取得）
	D3DXVECTOR3 pos = m_dataPos.Get();		// 位置情報
	D3DXVECTOR3 size = m_dataSize.Get();	// 大きさ
	D3DXVECTOR3 gage = m_dataGage.Get();	// ゲージ
	D3DXCOLOR color = m_dataColor.Get();	// 色

	// 頂点バッファをポインタを宣言
	LPDIRECT3DVERTEXBUFFER9 vtxBuff = GetVtxBuff();

	// 頂点バッファ取得成功の有無を判定
	if (vtxBuff == NULL)
	{// 失敗時

	 // 頂点情報設定を抜ける
		return;
	}

	// 2D頂点情報のポインタを宣言
	VERTEX_2D *pVtx = NULL;

	// 頂点バッファをロックし、頂点情報のポインタを取得
	vtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	
	// 頂点座標を設定
	switch (m_type)
	{
	case TYPE_LEFT:
		pVtx[0].pos = D3DXVECTOR3(pos.x - size.x, pos.y - size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pos.x + size.x - gage.x, pos.y - size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pos.x - size.x, pos.y + size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pos.x + size.x - gage.x, pos.y + size.y, 0.0f);
		break;
	case TYPE_RIGHT:
		pVtx[0].pos = D3DXVECTOR3(pos.x - size.x + gage.x, pos.y - size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pos.x + size.x, pos.y - size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pos.x - size.x + gage.x, pos.y + size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, 0.0f);
		break;
	case TYPE_CENTER:
		pVtx[0].pos = D3DXVECTOR3(pos.x - size.x + gage.x, pos.y - size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pos.x + size.x - gage.x, pos.y - size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pos.x - size.x + gage.x, pos.y + size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pos.x + size.x - gage.x, pos.y + size.y, 0.0f);
		break;
	}


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

//-------------------------------------
//- ゲージの設定処理
//-------------------------------------
void CObj2dGage::Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color,TYPE type)
{
	m_dataPos.Set(pos);
	m_dataSize.Set(size);
	m_dataColor.Set(color);
	m_type = type;
}
