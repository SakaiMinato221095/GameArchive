
//-===============================================
//-
//-	当たり判定壁処理[box_wall.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "box_wall.h"

#include "renderer.h"
#include "manager.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	コンスト定義
//=======================================

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	3D地面のコンストラクタ
//-------------------------------------
CBoxWall::CBoxWall(int nPriority) : CObject3d(nPriority)
{

}

//-------------------------------------
//-	3D地面のデストラクタ
//-------------------------------------
CBoxWall::~CBoxWall()
{

}


//-------------------------------------
//- 3D地面の初期化処理（3Dオブジェクト設定）
//-------------------------------------
HRESULT CBoxWall::Init(void)
{
	// 3Dオブジェクトの初期化
	CObject3d::Init();

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 3D地面の終了処理
//-------------------------------------
void CBoxWall::Uninit(void)
{
	// 3Dオブジェクトの終了
	CObject3d::Uninit();
}

//-------------------------------------
//- 3D地面の更新処理
//-------------------------------------
void CBoxWall::Update(void)
{
	// 3Dオブジェクトの更新処理
	CObject3d::Update();
}

//-------------------------------------
//- 3D地面の描画処理
//-------------------------------------
void CBoxWall::Draw(void)
{
	// 3Dオブジェクトの描画処理
	CObject3d::Draw();
}

//-------------------------------------
//- 3D地面の生成処理
//-------------------------------------
CBoxWall* CBoxWall::Create(void)
{
	// フィールドのポインタを宣言
	CBoxWall* pCBoxWall = DBG_NEW CBoxWall(2);

	// 生成の成功の有無を判定
	if (pCBoxWall != NULL)
	{
		// 初期化処理
		if (FAILED(pCBoxWall->Init()))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCBoxWall == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// フィールドのポインタを返す
	return pCBoxWall;
}

//-------------------------------------
//-	3Dオブジェクトの頂点情報設定処理
//-------------------------------------
void CBoxWall::SetVtx(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 size = GetVtxData().size;		// サイズ
	D3DXCOLOR color = GetVtxData().color;		// 色
	D3DXVECTOR2 texPos = GetVtxData().texPos;	// テクスチャ位置

	D3DXVECTOR3 rot = GetVtxData().rot;			// テクスチャ位置

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

		if (rot.y == 0.0f)
		{
			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(-size.x, size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(size.x, size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-size.x, -size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(size.x, -size.y, 0.0f);
		}
		else if (rot.y == (D3DX_PI * 0.5f))
		{
			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(-size.z, size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(size.z, size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-size.z, -size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(size.z, -size.y, 0.0f);
		}

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

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