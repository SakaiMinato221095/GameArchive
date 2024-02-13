
//-===============================================
//-
//-	開始説明文UIの処理[ui_start_text.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "ui_start_text.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//= コンスト定義
//=======================================

// 開始説明文UIテクスチャのコンスト定義
const char *pTextureUiStartText[] =
{
	"data\\TEXTURE\\state_text_000.png",		// スタートテキスト000のテクスチャ
	"data\\TEXTURE\\state_text_001.png",		// スタートテキスト001のテクスチャ
};

//-======================================
//-	静的変数宣言
//-======================================

int CUiStartText::m_nTextureNldx[TEX_MAX] = {};	// テクスチャ

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CUiStartText::CUiStartText(int nPriority) : CObject2d(nPriority)
{

}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CUiStartText::~CUiStartText()
{

}

//-------------------------------------
//- 開始説明文UIのテクスチャの読み込み
//-------------------------------------
HRESULT CUiStartText::Load(void)
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
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureUiStartText[nCount]);

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
//- 開始説明文UIの読み込んだテクスチャの破棄
//-------------------------------------
void CUiStartText::Unload(void)
{

}

//-------------------------------------
//- 開始説明文UIの初期化処理
//-------------------------------------
HRESULT CUiStartText::Init(TEX tex)
{
	// テクスチャ割当
	BindTexture(m_nTextureNldx[tex]);

	// 2Dオブジェクトの初期化
	CObject2d::Init();

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 開始説明文UIの終了処理
//-------------------------------------
void CUiStartText::Uninit(void)
{
	// 2Dオブジェクトの終了
	CObject2d::Uninit();
}

//-------------------------------------
//- 開始説明文UIの更新処理
//-------------------------------------
void CUiStartText::Update(void)
{
	// 変数宣言（情報取得）
	bool bMoveStop = m_bDataMoveStop.Get();				// 移動停止の有無
	D3DXVECTOR3 sizeMove = m_dataMoveSpeed.Get();		// 移動量の速度

	// 移動停止の有無を判定
	if (bMoveStop == false)
	{
		if (sizeMove.x >= 0.0f)
		{
			// 加算処理
			AddSizeMove();
		}
		else
		{
			// 減算処理
			SubSizeMove();
		}
	}

	// 後回し描画のオン
	m_bDataAfterDraw.Set(true);

	// 頂点情報の設定処理
	CObject2d::Update();
}

//-------------------------------------
//- 開始説明文UIの描画処理
//-------------------------------------
void CUiStartText::Draw(void)
{
	// 2Dオブジェクトの描画処理
	CObject2d::Draw();
}

//-------------------------------------
//- 開始説明文UIの生成処理
//-------------------------------------
CUiStartText *CUiStartText::Create(TEX tex)
{
	// 開始説明文UIのポインタを宣言
	CUiStartText *pCUiStartText = DBG_NEW CUiStartText(7);

	// 生成の成功の有無を判定
	if (pCUiStartText != NULL)
	{
		// 初期化処理 if(開始説明文UIの初期化成功の有無を判定)
		if (FAILED(pCUiStartText->Init(tex)))
		{// 失敗時

		 // 「なし」を返す
			return NULL;
		}
	}
	else if (pCUiStartText == NULL)
	{// 失敗時

	 // 「なし」を返す
		return NULL;
	}

	// 開始説明文UIのポインタを返す
	return pCUiStartText;
}

//-------------------------------------
//- 開始説明文UIの設定処理
//-------------------------------------
void CUiStartText::Set(D3DXVECTOR3 pos, D3DXVECTOR3 posTarget, D3DXVECTOR3 size, D3DXVECTOR3 move)
{
	// 情報代入
	m_dataPos.Set(pos);
	m_dataPosTarget.Set(posTarget);
	m_dataSize.Set(size);
	m_dataMoveSpeed.Set(move);
}

//-------------------------------------
//- 操作説明UIの加算処理
//-------------------------------------
void CUiStartText::AddSizeMove(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();					// 位置
	D3DXVECTOR3 posTarget = m_dataPosTarget.Get();		// 目的の位置
	D3DXVECTOR3 move = m_dataMoveSpeed.Get();			// 移動量の速度
	bool bMoveStop = m_bDataMoveStop.Get();				// 移動停止の有無

	// 移動量の蓄積値を加算
	pos += move;

	if (pos.x >= posTarget.x &&
		pos.y >= posTarget.y &&
		pos.z >= posTarget.z)
	{
		// 移動をなくす
		bMoveStop = true;
	}

	// 情報更新
	m_dataPos.Set(pos);					// 位置
	m_dataPosTarget.Set(posTarget);		// 目的の位置
	m_dataMoveSpeed.Set(move);			// 移動量の速度
	m_bDataMoveStop.Set(bMoveStop);		// 移動停止の有無
}

//-------------------------------------
//- 操作説明UIの減算処理
//-------------------------------------
void CUiStartText::SubSizeMove(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();					// 位置
	D3DXVECTOR3 posTarget = m_dataPosTarget.Get();		// 目的の位置
	D3DXVECTOR3 move = m_dataMoveSpeed.Get();			// 移動量の速度
	bool bMoveStop = m_bDataMoveStop.Get();				// 移動停止の有無

	// 移動量の蓄積値を加算
	pos += move;

	if (pos.x <= posTarget.x &&
		pos.y <= posTarget.y &&
		pos.z <= posTarget.z)
	{
		// 移動をなくす
		bMoveStop = true;
	}

	// 情報更新
	m_dataPos.Set(pos);					// 位置
	m_dataPosTarget.Set(posTarget);		// 目的の位置
	m_dataMoveSpeed.Set(move);			// 移動量の速度
	m_bDataMoveStop.Set(bMoveStop);		// 移動停止の有無
}