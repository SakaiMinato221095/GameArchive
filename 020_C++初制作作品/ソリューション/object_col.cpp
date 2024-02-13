
//================================================
//=
//=	当たり判定オブジェクト処理[object_col.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "object_col.h"

#include "obj_3d_wall.h"
#include "obj_3d_field.h"

//=======================================
//=	マクロ定義
//=======================================

//-------------------------------------
//-	当たり判定オブジェクトのコンストラクタ
//-------------------------------------
CObjectCol::CObjectCol()
{
	ZeroMemory(m_apObj3dWall,sizeof(m_apObj3dWall));
	ZeroMemory(m_apObj3dField, sizeof(m_apObj3dField));
}

//-------------------------------------
//-	当たり判定オブジェクトのデストラクタ
//-------------------------------------
CObjectCol::~CObjectCol()
{
}

//-------------------------------------
//-	当たり判定オブジェクトの初期化
//-------------------------------------
HRESULT CObjectCol::Init(void)
{
	for (int nCount = 0; nCount < TYPE_WALL_MAX; nCount++)
	{
		// 3D壁の生成処理
		m_apObj3dWall[nCount] = CObj3dWall::Create(CObj3dWall::TEX_NULL);

		// 3D壁の生成成功の判定
		if (m_apObj3dWall[nCount] == NULL)
		{
			// 処理を抜ける
			return E_FAIL;
		}
	}

	for (int nCount = 0; nCount < TYPE_FIELD_MAX; nCount++)
	{
		// 3D地面の生成処理
		m_apObj3dField[nCount] = CObj3dField::Create(CObj3dField::TEX_NULL);

		//  3D地面の生成成功の判定
		if (m_apObj3dField[nCount] == NULL)
		{
			// 処理を抜ける
			return E_FAIL;
		}
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//-	当たり判定オブジェクトの終了処理
//-------------------------------------
void CObjectCol::Uninit(void)
{
	for (int nCount = 0; nCount < TYPE_WALL_MAX; nCount++)
	{
		// 3D壁の終了処理
		m_apObj3dWall[nCount]->Uninit();

		// 3D壁のポインタ初期化
		m_apObj3dWall[nCount] = NULL;
	}

	for (int nCount = 0; nCount < TYPE_FIELD_MAX; nCount++)
	{
		// 3D地面の終了処理
		m_apObj3dField[nCount]->Uninit();

		// 3D地面のポインタ初期化
		m_apObj3dField[nCount] = NULL;
	}
}

//-------------------------------------
//-	当たり判定オブジェクトの更新処理
//-------------------------------------
void CObjectCol::Update(void)
{
	// 3Dオブジェクトの設定
	SetObjectCol();
}

//-------------------------------------
//-	当たり判定オブジェクトの描画処理
//-------------------------------------
void CObjectCol::Draw(void)
{

}

//-------------------------------------
//-	当たり判定オブジェクトの生成処理
//-------------------------------------
CObjectCol * CObjectCol::Create(void)
{
	// 3Dオブジェクトのポインタを宣言
	CObjectCol *pObject3d = new CObjectCol;

	// 生成の成功の有無を判定
	if (pObject3d != NULL)
	{
		// 初期化処理
		if (FAILED(pObject3d->Init()))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pObject3d == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// 3Dオブジェクトのポインタを返す
	return pObject3d;
}

//-------------------------------------
//-	当たり判定オブジェクトの設定処理
//-------------------------------------
void CObjectCol::Set(D3DXVECTOR3 pos,D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	// 情報代入
	m_dataPos.Set(pos);		// 位置
	m_dataSize.Set(size);	// サイズ
	m_dataRot.Set(rot);		// 向き

	SetObjectCol();			// 3Dオブジェクトの設定
}

//-------------------------------------
//-	当たり判定オブジェクトの3Dオブジェクトの設定処理
//-------------------------------------
void CObjectCol::SetObjectCol(void)
{
	// 情報取得
	D3DXVECTOR3 pos = m_dataPos.Get();			// 位置
	D3DXVECTOR3 size = m_dataSize.Get();		// サイズ
	D3DXVECTOR3 rot = m_dataRot.Get();			// 向き
	D3DXCOLOR color = m_dataColor.Get();		// 色

	//// 3Dオブジェクト（左）の設定処理
	//m_apObj3dWall[TYPE_WALL_LEFT]->Set(
	//	D3DXVECTOR3(pos.x + 0.0f, pos.y + 0.0f, pos.z + size.z),
	//	D3DXVECTOR3(size.x, size.y, size.z),
	//	D3DXVECTOR3(0.0f, rot.y, 0.0f),
	//	D3DXCOLOR(color));

	//// 3Dオブジェクト（右）の設定処理
	//m_apObj3dWall[TYPE_WALL_RIGHT]->Set(
	//	D3DXVECTOR3(pos.x + 0.0f, pos.y + 0.0f, pos.z - size.z),
	//	D3DXVECTOR3(size.x, size.y, size.z),
	//	D3DXVECTOR3(0.0f, rot.y, 0.0f),
	//	D3DXCOLOR(color));

	//// 3Dオブジェクト（手前）の設定処理
	//m_apObj3dWall[TYPE_WALL_NEAR]->Set(
	//	D3DXVECTOR3(pos.x + size.x, pos.y + 0.0f, pos.z + 0.0f),
	//	D3DXVECTOR3(size.z, size.y, size.z),
	//	D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
	//	D3DXCOLOR(color));

	//// 3Dオブジェクト（奥）の設定処理
	//m_apObj3dWall[TYPE_WALL_BACK]->Set(
	//	D3DXVECTOR3(pos.x - size.x, pos.y + 0.0f, pos.z + 0.0f),
	//	D3DXVECTOR3(size.z, size.y, size.z),
	//	D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
	//	D3DXCOLOR(color));

	// 3Dオブジェクト（下）の設定処理
	m_apObj3dField[TYPE_FIELD_BOTTOM]->Set(
		D3DXVECTOR3(pos.x + 0.0f, pos.y + 0.0f, pos.z + 0.0f),
		D3DXVECTOR3(size.x, size.y, size.z),
		D3DXVECTOR3(0.0f, rot.y, 0.0f),
		D3DXCOLOR(color));

	//// 3Dオブジェクト（上）の設定処理
	//m_apObj3dField[TYPE_FIELD_TOP]->Set(
	//	D3DXVECTOR3(pos.x + 0.0f, pos.y + size.y, pos.z + 0.0f),
	//	D3DXVECTOR3(size.x, size.y, size.z),
	//	D3DXVECTOR3(0.0f, rot.y, 0.0f),
	//	D3DXCOLOR(color));
}

//-------------------------------------
//-	当たり判定オブジェクトの当たり判定処理
//-------------------------------------
bool CObjectCol::Collision(D3DXVECTOR3 posGet, D3DXVECTOR3 sizeGet)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();		// 位置
	D3DXVECTOR3 size = m_dataSize.Get();	// 大きさ

	// 矩形の当たり判定
	if (pos.x + size.x >= posGet.x - sizeGet.x &&
		pos.x - size.x <= posGet.x + sizeGet.x &&
		pos.z + size.z >= posGet.z - sizeGet.z &&
		pos.z - size.z <= posGet.z + sizeGet.z)
	{
		// 成功を返す
		return true;
	}

	// なしを返す
	return false;
}