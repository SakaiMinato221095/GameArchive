
//-===============================================
//-
//-	アニメーションオブジェクト処理[object_anima.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "object_anima.h"

#include "renderer.h"
#include "manager.h"

//-======================================
//-	マクロ定義
//-======================================

//-------------------------------------
//-	アニメーションオブジェクトのコンストラクタ
//-------------------------------------
CObjectAnima::CObjectAnima()
{

}

//-------------------------------------
//-	アニメーションオブジェクトのデストラクタ
//-------------------------------------
CObjectAnima::~CObjectAnima()
{

}

//-------------------------------------
//- アニメーションオブジェクトの初期化処理
//-------------------------------------
HRESULT CObjectAnima::Init(void)
{
	// 2Dオブジェクトの終了処理
	CObject2d::Init();

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- アニメーションオブジェクトの終了処理
//-------------------------------------
void CObjectAnima::Uninit(void)
{
	// 2Dオブジェクトの終了処理
	CObject2d::Uninit();
}

//-------------------------------------
//- アニメーションオブジェクトの更新処理
//-------------------------------------
void CObjectAnima::Update(void)
{
	// アニメーションの更新
	UpdateAnima();

	// アニメーションオブジェクトの頂点情報設定
	SetVtx();
}

//-------------------------------------
//- アニメーションオブジェクトの描画処理
//-------------------------------------
void CObjectAnima::Draw(void)
{
	// 2Dオブジェクトの描画処理
	CObject2d::Draw();
}

//-------------------------------------
//- アニメーションオブジェクトの生成処理
//-------------------------------------
CObjectAnima *CObjectAnima::Create(void)
{
	// 2Dオブジェクトの生成
	CObjectAnima *pObjectAnima = new CObjectAnima;

	// 生成の成功の有無を判定
	if (pObjectAnima != NULL)
	{
		// 初期化処理
		if (FAILED(pObjectAnima->Init()))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pObjectAnima == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// アニメーションオブジェクトの頂点情報設定
	pObjectAnima->SetVtx();

	// 2Dオブジェクトのポインタを返す
	return pObjectAnima;
}

//-------------------------------------
//- アニメーションオブジェクトのアニメーション処理
//-------------------------------------
void CObjectAnima::UpdateAnima(void)
{
	// 変数宣言（情報取得）
	int nCounter = m_nDataCounter.Get();			// アニメーションカウンター
	int nChangeFrame = m_nDataChangeFrame.Get();	// アニメーションの切り替え数
	int nPattern = m_nDataPattern.Get();			// アニメーションのパターン数
	int nLife = m_nDataLine.Get();					// 体力

	// アニメーションカウンターを加算
	nCounter++;

	// アニメーション切り替えの判定
	if ((nCounter % nChangeFrame) == 0)
	{// 設定フレーム時

		// パターンNo.を更新する
		nPattern = ((nCounter / nChangeFrame) % nLife);
	}

	// 情報更新
	m_nDataCounter.Set(nCounter);			// アニメーションカウンター
	m_nDataChangeFrame.Set(nChangeFrame);	// アニメーションの切り替え数
	m_nDataPattern.Set(nPattern);			// アニメーションのパターン数
	m_nDataLine.Set(nLife);					// 体力
}

//-------------------------------------
//- アニメーションオブジェクトの頂点情報設定
//-------------------------------------
void CObjectAnima::SetVtx(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();		// 位置情報
	D3DXVECTOR3 size = m_dataSize.Get();	// 大きさ
	int nPattern = m_nDataPattern.Get();	// アニメーションのパターン数

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
	pVtx[0].pos = D3DXVECTOR3(pos.x - size.x, pos.y - size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + size.x, pos.y - size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - size.x, pos.y + size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーを設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャの座標を設定
	pVtx[0].tex = D3DXVECTOR2(
		(nPattern * 0.125f),
		0.0f);

	pVtx[1].tex = D3DXVECTOR2(
		((nPattern + 1) * 0.125f),
		0.0f);

	pVtx[2].tex = D3DXVECTOR2(
		(nPattern * 0.125f),
		1.0f);

	pVtx[3].tex = D3DXVECTOR2(
		((nPattern + 1) * 0.125f),
		1.0f);

	// 頂点バッファをアンロックする
	vtxBuff->Unlock();

	// 情報更新
	m_nDataPattern.Set(nPattern);			// アニメーションのパターン数
}

//-------------------------------------
//- アニメーションオブジェクトの切り替えフレーム数の取得
//-------------------------------------
void CObjectAnima::SetAllAnima(int nLine, int nColumn, int nChangeFrame)
{
	// 行数を代入
	m_nDataLine.Set(nLine);

	// 列数を代入
	m_nDataColumn.Set(nColumn);

	// 切り替えフレームの代入
	m_nDataChangeFrame.Set(nChangeFrame);
}
