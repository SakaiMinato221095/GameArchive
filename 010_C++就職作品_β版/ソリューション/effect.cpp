
//-===============================================
//-
//-	エフェクトの処理[effect.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "effect.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//= コンスト定義
//=======================================

// エフェクトテクスチャのコンスト定義
const char *pTextureEffect[] =
{
	"data\\TEXTURE\\effect000.jpg"	// 通常エフェクト_000のテクスチャ
};

//-======================================
//-	静的変数宣言
//-======================================

int CEffect::m_nTextureNldx[TEX_MAX] = {};	// テクスチャ

//-------------------------------------
//-	エフェクトのコンストラクタ
//-------------------------------------
 CEffect::CEffect(int nPriority) : CBillboard(nPriority)
{
	 ZeroMemory(&m_data,sizeof(m_data));
}

//-------------------------------------
//-	エフェクトのデストラクタ
//-------------------------------------
CEffect::~CEffect()
{

}

//-------------------------------------
//- エフェクトのテクスチャの読み込み
//-------------------------------------
HRESULT CEffect::Load(void)
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
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureEffect[nCount]);

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
//- エフェクトの読み込んだテクスチャの破棄
//-------------------------------------
void CEffect::Unload(void)
{

}

//-------------------------------------
//- エフェクトの初期化処理
//-------------------------------------
HRESULT CEffect::Init(TEX tex)
{
	// テクスチャ割当
	BindTexture(m_nTextureNldx[tex]);

	// ビルボードオブジェクトの初期化
	CBillboard::Init();

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- エフェクトの終了処理
//-------------------------------------
void CEffect::Uninit(void)
{
	// ビルボードオブジェクトの終了
	CBillboard::Uninit();
}

//-------------------------------------
//- エフェクトの更新処理
//-------------------------------------
void CEffect::Update(void)
{
	// エフェクトの加算処理
	Add();

	// エフェクトの減少処理
	if (Sub() == true)
	{
		return;
	}

	// ビルボードオブジェクトの更新処理
	CBillboard::Update();
}

//-------------------------------------
//- エフェクトの描画処理
//-------------------------------------
void CEffect::Draw(void)
{
	// デバイスを取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	// デバイスの情報取得の成功を判定
	if (pRenderer == NULL)
	{// 失敗時

		// 初期化処理を抜ける
		return;
	}

	// アルファブレディングの設定
	pRenderer->SetAlphaBlend(true);

	// アルファテストの設定
	pRenderer->SetAlphaTest(true);

	if (m_data.bIsZTestStop == false)
	{
		// Zテストの設定
		pRenderer->SetZTest(true);
	}

	// エフェクトの描画処理
	CBillboard::Draw();

	if (m_data.bIsZTestStop == false)
	{
		// Zテストの解除
		pRenderer->SetZTest(false);
	}

	// アルファブレディングの解除
	pRenderer->SetAlphaBlend(false);

	// アルファテストの解除
	pRenderer->SetAlphaTest(false);
}

//-------------------------------------
//- エフェクトの減少処理
//-------------------------------------
void CEffect::Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR color, int nLife, bool bZTest)
{
	SetPos(pos);
	SetSize(size);
	SetColor(color);
	
	m_data.move = move;
	m_data.nLife = nLife;
	m_data.bIsZTestStop = bZTest;
}

//-------------------------------------
//- エフェクトの生成処理
//-------------------------------------
CEffect *CEffect::Create(TEX tex)
{
	// エフェクトのポインタを宣言
	CEffect *pCEffect = DBG_NEW CEffect(3);

	// 生成の成功の有無を判定
	if (pCEffect != NULL)
	{
		// 初期化処理
		if (FAILED(pCEffect->Init(tex)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCEffect == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// エフェクトのポインタを返す
	return pCEffect;
}

//-------------------------------------
//- エフェクトの加算処理
//-------------------------------------
void CEffect::Add(void)
{
	// 位置の更新
	SetPos(GetPos() + m_data.move);
}

//-------------------------------------
//- エフェクトの減少処理
//-------------------------------------
bool CEffect::Sub(void)
{	
	D3DXVECTOR3 size = GetSize();
	D3DXCOLOR color = GetColor();

	// 大きさを減らす
	size.x -= (m_data.sizeHold.x / m_data.nLife);
	size.z -= (m_data.sizeHold.z / m_data.nLife);
	SetSize(size);

	// α値を減らす
	color.a -= (m_data.colorHold.a / m_data.nLife);
	SetColor(color);

	// 体力を減らす
	m_data.nLife--;

	// 体力の判定
	if (m_data.nLife <= 0)
	{
		// 終了処理
		Uninit();

		// 成功を返す
		return true;
	}

	// 失敗を返す
	return false;
}
