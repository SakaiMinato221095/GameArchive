
//================================================
//=
//= Xファイルオブジェクト処理[object_x.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "object_x.h"

#include "renderer.h"
#include "manager.h"

#include "manager_model.h"

//=======================================
//=	コンスト定義
//=======================================

//-------------------------------------
//-	Xファイルオブジェクトのコンストラクタ
//-------------------------------------
CObjectX::CObjectX(int nPriority) : CObject(nPriority)
{
	// 値をクリア
	m_bDraw = 0;
	m_nModelNldxUse = -1;

	ZeroMemory(m_mtxWorld, sizeof(D3DXMATRIX));
}

//-------------------------------------
//-	Xファイルオブジェクトのデストラクタ
//-------------------------------------
CObjectX::~CObjectX()
{
}

//-------------------------------------
//-	Xファイルオブジェクトの初期化処理
//-------------------------------------
HRESULT CObjectX::Init()
{
	// 成功を返す
	return S_OK;
}

//-------------------------------------
//-	Xファイルオブジェクトの終了処理
//-------------------------------------
void CObjectX::Uninit(void)
{
	// 自分自身のポインタの開放
	Release();
}

//-------------------------------------
//-	Xファイルオブジェクトの更新処理
//-------------------------------------
void CObjectX::Update(void)
{

}

//-------------------------------------
//-	Xファイルオブジェクトの描画処理
//-------------------------------------
void CObjectX::Draw(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// デバイスの情報取得の成功を判定
	if (pDevice == NULL)
	{// 失敗時

		// 初期化処理を抜ける
		return;
	}

	// モデル管理の取得
	CManagerModel *pManagerModel = CManager::GetManagerModel();

	// モデル管理の情報取得の成功を判定
	if (pManagerModel == NULL)
	{// 失敗時

		// 描画処理を抜ける
		return;
	}

	// モデル情報を取得
	CManagerModel::Model model = pManagerModel->GetAddress(m_nModelNldxUse);

	// モデルの有無を判定
	if (model.m_pMesh == NULL)
	{
		// 描画処理を抜ける
		return;
	}

	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();	// 位置情報
	D3DXVECTOR3 rot = m_dataRot.Get();	// 向き情報

	// 変数宣言
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス
	D3DMATERIAL9 matDef;			// 現在のマテリアルの保存用
	D3DXMATERIAL *pMat;				// マテリアルへのポインタ

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(
		D3DTS_WORLD,
		&m_mtxWorld);

	//現在のマテリアルの取得
	pDevice->GetMaterial(&matDef);
	
	// マテリアルのポインタを取得
	pMat = (D3DXMATERIAL*)model.m_pBuffMat->GetBufferPointer();

	// マテリアルごとの描画
	for (int nCutMat = 0; nCutMat < (int)model.m_dwNumMat; nCutMat++)
	{
		// 一時的な色の保管場所
		D3DXCOLOR tempColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		// 元の色を保管
		tempColor = pMat[nCutMat].MatD3D.Diffuse;

		// 描画の有無を判定
		if (m_bDraw == true)
		{
			// 色を設定
			pMat[nCutMat].MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.15f);
		}

		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCutMat].MatD3D);

		if (m_bDraw == true)
		{
			// 元の色に戻る
			pMat[nCutMat].MatD3D.Diffuse = tempColor;
		}

		// テクスチャの設定（仮）
		pDevice->SetTexture(0, model.m_pTexture[nCutMat]);

		// Xファイルオブジェクト（パーツ）の描画
		model.m_pMesh->DrawSubset(nCutMat);
	}

	if (m_bDraw == true)
	{
		// 描画の有無を初期化
		m_bDraw = false;
	}


	// 保存していたマテリアルに戻す
	pDevice->SetMaterial(&matDef);
}

//-------------------------------------
//-	Xファイルオブジェクトの生成処理
//-------------------------------------
CObjectX *CObjectX::Create(void)
{
	// Xファイルオブジェクトのポインタを宣言
	CObjectX *pObjectX = NULL;

	// 生成
	pObjectX = DBG_NEW CObjectX;

	// 生成の成功の有無を判定
	if (pObjectX != NULL)
	{
		// 初期化処理
		if (FAILED(pObjectX->Init()))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pObjectX == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// Xファイルオブジェクトのポインタを返す
	return pObjectX;
}

//-------------------------------------
//- Xファイルオブジェクトのテクスチャ割当
//-------------------------------------
void CObjectX::BindModel(int nModelNldx, int nModelNum)
{
	// テクスチャの番号割当
	m_nModelNldxUse = nModelNldx;

	// モデルの設定
	SetModel(nModelNum);
}

//-------------------------------------
//- Xファイルオブジェクトのモデルの設定（仮想関数）
//-------------------------------------
void CObjectX::SetModel(int nModelNldx)
{
	// 失敗
}

//-------------------------------------
//-	Xファイルオブジェクトの回転処理
//-------------------------------------
void CObjectX::AddRot(D3DXVECTOR3 addRot)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 rot = m_dataRot.Get();	// 向き

	// 回転量を加算
	rot += addRot;

	// 向きの補正
	if (rot.y > D3DX_PI)
	{
		rot.y += -D3DX_PI * 2;
	}
	else if (rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2;
	}

	// 情報更新
	m_dataRot.Set(rot);	// 向き
}

//-------------------------------------
//-	Xファイルオブジェクトの描画を外す
//-------------------------------------
void CObjectX::SetDrawRemove(void)
{
	// 描画を外す
	m_bDraw = true;
}
