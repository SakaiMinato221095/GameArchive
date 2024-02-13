
//-===============================================
//-
//-	3D壁処理[obj_3d_wall.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "obj_3d_wall.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

#include "coll.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	コンスト定義
//=======================================

// 3D壁のテクスチャのコンスト定義
const char *pTextureWall[] =
{
	NULL,										// テクスチャなし
	"data\\TEXTURE\\blockade_wall000.jpg",		// 封鎖壁のテクスチャ
	"data\\TEXTURE\\dark_wall000.png",			// 闇壁のテクスチャ
};

//-======================================
//-	静的変数宣言
//-======================================

int CObj3dWall::m_nTextureNldx[TEX_MAX] = {};

//-------------------------------------
//-	3D壁のコンストラクタ
//-------------------------------------
CObj3dWall::CObj3dWall(int nPriority) : CObject3d(nPriority)
{
	m_pColl = nullptr;
}

//-------------------------------------
//-	3D壁のデストラクタ
//-------------------------------------
CObj3dWall::~CObj3dWall()
{

}

//-------------------------------------
//- 背景のテクスチャの読み込み
//-------------------------------------
HRESULT CObj3dWall::Load(void)
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
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureWall[nCount]);

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
void CObj3dWall::Unload(void)
{

}
//-------------------------------------
//- 3D壁の初期化処理（3Dオブジェクト設定）
//-------------------------------------
HRESULT CObj3dWall::Init(TEX tex)
{
	// テクスチャ割当
	BindTexture(m_nTextureNldx[tex]);

	// 3Dオブジェクトの初期化
	CObject3d::Init();

	if (m_pColl == NULL)
	{
		// 当たり判定設定
		m_pColl = CColl::Create(
			CMgrColl::TAG_WALL_X,
			this,
			GetVtxData().pos,
			GetVtxData().size);
	}
	else
	{
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 3D壁の終了処理
//-------------------------------------
void CObj3dWall::Uninit(void)
{
	if (m_pColl != NULL)
	{
		// 当たり判定の終了処理
		m_pColl->Uninit();
		delete m_pColl;
		m_pColl = NULL;
	}

	// 3Dオブジェクトの終了
	CObject3d::Uninit();
}

//-------------------------------------
//- 3D壁の更新処理
//-------------------------------------
void CObj3dWall::Update(void)
{
	if (m_pColl != nullptr)
	{
		// 当たり判定の情報更新処理
		m_pColl->UpdateData(
			GetVtxData().pos,
			GetVtxData().size);
	}

	// 3Dオブジェクトの更新処理
	CObject3d::Update();
}

//-------------------------------------
//- 3D壁の描画処理
//-------------------------------------
void CObj3dWall::Draw(void)
{
	// 3Dオブジェクトの描画処理
	CObject3d::Draw();
}


//-------------------------------------
//-	3Dオブジェクトの頂点情報設定処理
//-------------------------------------
void CObj3dWall::InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR color, D3DXVECTOR2 texPos)
{
	CObject3d::InitSet(pos,size,rot,color,texPos);

	if (rot.y == 0.0f)
	{
		CColl::Data data = m_pColl->GetData();
		data.tag = CMgrColl::TAG_WALL_Z;

		m_pColl->SetData(data);
	}
	else if (rot.y == (D3DX_PI * 0.5f))
	{
		CColl::Data data = m_pColl->GetData();
		data.tag = CMgrColl::TAG_WALL_X;

		m_pColl->SetData(data);
	}
}

//-------------------------------------
//- 3D壁の生成処理
//-------------------------------------
CObj3dWall * CObj3dWall::Create(TEX tex)
{
	// フィールドのポインタを宣言
	CObj3dWall *pCObj3dWall = DBG_NEW CObj3dWall(1);

	// 生成の成功の有無を判定
	if (pCObj3dWall != NULL)
	{
		// 初期化処理
		if (FAILED(pCObj3dWall->Init(tex)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCObj3dWall == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// フィールドのポインタを返す
	return pCObj3dWall;
}

//-------------------------------------
//-	3Dオブジェクトの頂点情報設定処理
//-------------------------------------
void CObj3dWall::SetVtx(void)
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
			pVtx[0].pos = D3DXVECTOR3(-size.x,	size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3( size.x,	size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-size.x, -size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3( size.x, -size.y, 0.0f);
		}
		else if (rot.y == (D3DX_PI * 0.5f))
		{
			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(-size.z,  size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3( size.z,  size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-size.z, -size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3( size.z, -size.y, 0.0f);
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