
//-===============================================
//-
//-	操作説明文UIの処理[ui_text_desc.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "ui_text_desc.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//= コンスト定義
//=======================================

// 操作説明文UIテクスチャのコンスト定義
const char *pTextureUiTextDesc[] =
{
	"data\\TEXTURE\\ui_text_push.png",		// スペースキーのテクスチャ
};

//-======================================
//-	静的変数宣言
//-======================================

int CUiTextDesc::m_nTextureNldx[TEX_MAX] = {};	// テクスチャ

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CUiTextDesc::CUiTextDesc(int nPriority) : CObject2d(nPriority)
{

}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CUiTextDesc::~CUiTextDesc()
{

}

//-------------------------------------
//- 操作説明文UIのテクスチャの読み込み
//-------------------------------------
HRESULT CUiTextDesc::Load(void)
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
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureUiTextDesc[nCount]);

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
//- 操作説明文UIの読み込んだテクスチャの破棄
//-------------------------------------
void CUiTextDesc::Unload(void)
{

}

//-------------------------------------
//- 操作説明文UIの初期化処理
//-------------------------------------
HRESULT CUiTextDesc::Init(TEX tex)
{
	// テクスチャ割当
	BindTexture(m_nTextureNldx[tex]);

	// サイズの増減方向を設定
	m_bDataSizeMove.Set(true);

	// 2Dオブジェクトの初期化
	CObject2d::Init();

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 操作説明文UIの終了処理
//-------------------------------------
void CUiTextDesc::Uninit(void)
{
	// 2Dオブジェクトの終了
	CObject2d::Uninit();
}

//-------------------------------------
//- 操作説明文UIの更新処理
//-------------------------------------
void CUiTextDesc::Update(void)
{
	// 変数宣言（情報取得）
	bool bSizeMove = m_bDataSizeMove.Get();	// 増減方向

	if (bSizeMove == true)
	{
		// 加算処理
		AddSizeMove();
	}
	else
	{
		// 減算処理
		SubSizeMove();
	}

	// 後回し描画のオン
	m_bDataAfterDraw.Set(true);

	// 頂点情報の設定処理
	SetVtx();
}

//-------------------------------------
//- 操作説明文UIの描画処理
//-------------------------------------
void CUiTextDesc::Draw(void)
{
	// 2Dオブジェクトの描画処理
	CObject2d::Draw();
}

//-------------------------------------
//- 操作説明文UIの生成処理
//-------------------------------------
CUiTextDesc *CUiTextDesc::Create(TEX tex)
{
	// 操作説明文UIのポインタを宣言
	CUiTextDesc *pCUiTextDesc = DBG_NEW CUiTextDesc(7);

	// 生成の成功の有無を判定
	if (pCUiTextDesc != NULL)
	{
		// 初期化処理 if(操作説明文UIの初期化成功の有無を判定)
		if (FAILED(pCUiTextDesc->Init(tex)))
		{// 失敗時

		 // 「なし」を返す
			return NULL;
		}
	}
	else if (pCUiTextDesc == NULL)
	{// 失敗時

	 // 「なし」を返す
		return NULL;
	}

	// 操作説明文UIのポインタを返す
	return pCUiTextDesc;
}

//-------------------------------------
//- 操作説明文UIの設定処理
//-------------------------------------
void CUiTextDesc::Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 sizeMoveMax, D3DXVECTOR3 sizeMoveSpeed)
{
	// 情報代入
	m_dataPos.Set(pos);
	m_dataSize.Set(size);
	m_dataSizeMoveMax.Set(sizeMoveMax);
	m_dataSizeMoveSpeed.Set(sizeMoveSpeed);
}

//-------------------------------------
//- 操作説明文UIの頂点情報設定
//-------------------------------------
void CUiTextDesc::SetVtx(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();					// 位置
	D3DXVECTOR3 size = m_dataSize.Get();				// 大きさ
	D3DXVECTOR3 sizeMoveAcu = m_dataSizeMoveAcu.Get();	// サイズの移動量の蓄積値
	D3DCOLOR color = m_dataColor.Get();					// 色

	// 頂点バッファをポインタを宣言
	LPDIRECT3DVERTEXBUFFER9 vtxBuff = GetVtxBuff();

	// 頂点バッファ取得成功の有無を判定
	if (vtxBuff == NULL)
	{// 失敗時
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
	pVtx[0].pos = D3DXVECTOR3(pos.x - (size.x + sizeMoveAcu.x), pos.y - (size.y + sizeMoveAcu.y), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + (size.x + sizeMoveAcu.x), pos.y - (size.y + sizeMoveAcu.y), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - (size.x + sizeMoveAcu.x), pos.y + (size.y + sizeMoveAcu.y), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + (size.x + sizeMoveAcu.x), pos.y + (size.y + sizeMoveAcu.y), 0.0f);

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

	// 情報更新
	m_dataPos.Set(pos);			// 位置
	m_dataSize.Set(size);		// 大きさ
	m_dataColor.Set(color);		// 色
}

//-------------------------------------
//- 操作説明UIの加算処理
//-------------------------------------
void CUiTextDesc::AddSizeMove(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 sizeMoveAcu = m_dataSizeMoveAcu.Get();		// 大きさの移動量の蓄積値
	D3DXVECTOR3 sizeMoveMax = m_dataSizeMoveMax.Get();		// 大きさの移動量の最大値
	D3DXVECTOR3 sizeMoveSpeed = m_dataSizeMoveSpeed.Get();	// 大きさの移動量の速度
	bool bSizeMove = m_bDataSizeMove.Get();					// 増減方向

	// 移動量の蓄積値を加算
	sizeMoveAcu += sizeMoveSpeed;

	if (sizeMoveAcu.x >= sizeMoveMax.x &&
		sizeMoveAcu.y >= sizeMoveMax.y &&
		sizeMoveAcu.z >= sizeMoveMax.z)
	{
		// 減算方向に設定
		bSizeMove = false;
	}

	// 情報更新
	m_dataSizeMoveAcu.Set(sizeMoveAcu);		// 大きさの移動量の蓄積値
	m_bDataSizeMove.Set(bSizeMove);			// 大きさの移動量の増減方向
}

//-------------------------------------
//- 操作説明UIの減算処理
//-------------------------------------
void CUiTextDesc::SubSizeMove(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 sizeMoveAcu = m_dataSizeMoveAcu.Get();		// 大きさの移動量の蓄積値
	D3DXVECTOR3 sizeMoveMax = m_dataSizeMoveMax.Get();		// 大きさの移動量の最大値
	D3DXVECTOR3 sizeMoveSpeed = m_dataSizeMoveSpeed.Get();	// 大きさの移動量の速度
	bool bSizeMove = m_bDataSizeMove.Get();					// 増減方向

	// 移動量の蓄積値を増減
	sizeMoveAcu -= sizeMoveSpeed;

	if (sizeMoveAcu.x <= -sizeMoveMax.x &&
		sizeMoveAcu.y <= -sizeMoveMax.y &&
		sizeMoveAcu.z <= -sizeMoveMax.z)
	{
		// 加算方向に設定
		bSizeMove = true;
	}

	// 情報更新
	m_dataSizeMoveAcu.Set(sizeMoveAcu);		// 大きさの移動量の蓄積値
	m_bDataSizeMove.Set(bSizeMove);			// 大きさの移動量の増減方向
}