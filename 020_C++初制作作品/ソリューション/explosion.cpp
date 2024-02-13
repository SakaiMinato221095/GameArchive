
//-===============================================
//-
//-	爆発の処理[explosion.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "explosion.h"

#include "renderer.h"
#include "manager.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	静的変数宣言
//-======================================

LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CExplosion::CExplosion()
{
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CExplosion::~CExplosion()
{

}

//-------------------------------------
//- 爆発のテクスチャの読み込み
//-------------------------------------
HRESULT CExplosion::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// デバイスの情報取得の成功を判定
	if (pDevice == NULL)
	{// 失敗時

	 // 初期化処理を抜ける
		return E_FAIL;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\explosion000.png",
		&m_pTexture);

	// テクスチャの読み込み成功の有無を確認
	if (m_pTexture == NULL)
	{
		// 失敗時に初期化処理を抜ける
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 爆発の読み込んだテクスチャの破棄
//-------------------------------------
void CExplosion::Unload(void)
{

}

//-------------------------------------
//- 爆発の初期化処理
//-------------------------------------
HRESULT CExplosion::Init(void)
{
	// アニメーションオブジェクトの初期化処理
	CObjectAnima::Init();

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 爆発の終了処理
//-------------------------------------
void CExplosion::Uninit(void)
{
	// アニメーションオブジェクトの終了処理
	CObjectAnima::Uninit();
}

//-------------------------------------
//- 爆発の更新処理
//-------------------------------------
void CExplosion::Update(void)
{
	// アニメーションオブジェクトの更新処理
	CObjectAnima::Update();

	// 減少処理
	if (Sub() == true)
	{
		return;
	}
}

//-------------------------------------
//- 爆発の描画処理
//-------------------------------------
void CExplosion::Draw(void)
{
	// アニメーションオブジェクトの描画処理
	CObjectAnima::Draw();
}

//-------------------------------------
//- 爆発の生成処理
//-------------------------------------
CExplosion *CExplosion::Create(void)
{
	// 爆発の生成
	CExplosion *pCExplosion = DBG_NEW CExplosion;

	// 生成の成功の有無を判定
	if (pCExplosion != NULL)
	{
		// 初期化処理
		if (FAILED(pCExplosion->Init()))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCExplosion == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// 種類の設定
	pCExplosion->SetType(TYPE_EXPLOSION);

	//// 爆発のテクスチャを設定
	//pCExplosion->BindTexture(m_pTexture);

	// 爆発のポインタを返す
	return pCExplosion;
}

//-------------------------------------
//- 爆発の減少処理
//-------------------------------------
bool CExplosion::Sub(void)
{
	// 変数宣言（取得処理）
	int nLife = m_nDataLife.Get();

	// 体力を減らす
	nLife--;

	// 体力の判定
	if (nLife <= 0)
	{
		// 終了処理
		Uninit();

		// 成功を返す
		return true;
	}

	// 情報の更新
	m_nDataLife.Set(nLife);	// 体力

	// 失敗を返す
	return false;
}

//-------------------------------------
//- 爆発の寿命設定処理（アニメーション依存）
//-------------------------------------
void CExplosion::SetAnimaLife(void)
{
	// 変数宣言（情報取得）
	int nLife = m_nDataLife.Get();					// 体力
	int nLine = m_nDataLine.Get();					// アニメーションの行数
	int nColumn = m_nDataColumn.Get();				// アニメーションの列数
	int nChangeFrame = m_nDataChangeFrame.Get();	// アニメーションの切り替えフレーム数

	// 寿命の設定
	nLife = nChangeFrame * (nLine * nColumn);

	// 情報の更新
	m_nDataLife.Set(nLife);	// 体力

}
