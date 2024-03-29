
//-===============================================
//-
//-	各種情報の処理[data.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "data.h"

//-------------------------------------
//-	Intデータ用のコンストラクタ
//-------------------------------------
CDataInt::CDataInt()
{
	m_data = 0;
}

//-------------------------------------
//-	Intデータ用のデストラクタ
//-------------------------------------
CDataInt::~CDataInt()
{
}

//-------------------------------------
//-	Intデータ用の設定処理
//-------------------------------------
void CDataInt::Set(int data)
{
	m_data = data;
}

//-------------------------------------
//-	Intデータ用の取得処理
//-------------------------------------
int CDataInt::Get(void)
{
	return m_data;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

//-------------------------------------
//-	Floatデータ用のコンストラクタ
//-------------------------------------
CDataFloat::CDataFloat()
{
	m_data = 0.0f;
}

//-------------------------------------
//-	Floatデータ用のデストラクタ
//-------------------------------------
CDataFloat::~CDataFloat()
{
}

//-------------------------------------
//-	Floatデータ用の設定処理
//-------------------------------------
void CDataFloat::Set(float data)
{
	m_data = data;
}

//-------------------------------------
//-	Floatデータ用の取得処理
//-------------------------------------
float CDataFloat::Get(void)
{
	return m_data;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

//-------------------------------------
//-	Boolデータ用のコンストラクタ
//-------------------------------------
CDataBool::CDataBool()
{
	m_data = 0.0f;
}

//-------------------------------------
//-	Boolデータ用のデストラクタ
//-------------------------------------
CDataBool::~CDataBool()
{
}

//-------------------------------------
//-	Boolデータ用の設定処理
//-------------------------------------
void CDataBool::Set(bool data)
{
	m_data = data;
}

//-------------------------------------
//-	Boolデータ用の取得処理
//-------------------------------------
bool CDataBool::Get(void)
{
	return m_data;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-------------------------------------
//-	D3DXVECTOR2データ用のコンストラクタ
//-------------------------------------
CDataD3DXVECTOR2::CDataD3DXVECTOR2()
{
	m_data = D3DXVECTOR2(0.0f, 0.0f);
}

//-------------------------------------
//-	D3DXVECTOR2データ用のデストラクタ
//-------------------------------------
CDataD3DXVECTOR2::~CDataD3DXVECTOR2()
{
}

//-------------------------------------
//- D3DXVECTOR2データ用の設定
//-------------------------------------
void CDataD3DXVECTOR2::Set(D3DXVECTOR2 data)
{
	// 位置情報を代入
	m_data = data;
}

//-------------------------------------
//- D3DXVECTOR2データ用の取得
//-------------------------------------
D3DXVECTOR2 CDataD3DXVECTOR2::Get(void)
{
	// 位置情報を返す
	return m_data;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

//-------------------------------------
//-	D3DXVECTOR3データ用のコンストラクタ
//-------------------------------------
CDataD3DXVECTOR3::CDataD3DXVECTOR3()
{
	m_data = D3DXVECTOR3(0.0f,0.0f,0.0f);
}

//-------------------------------------
//-	D3DXVECTOR3データ用のデストラクタ
//-------------------------------------
CDataD3DXVECTOR3::~CDataD3DXVECTOR3()
{
}

//-------------------------------------
//- D3DXVECTOR3データ用の設定
//-------------------------------------
void CDataD3DXVECTOR3::Set(D3DXVECTOR3 data)
{
	// 位置情報を代入
	m_data = data;
}

//-------------------------------------
//- D3DXVECTOR3データ用の取得
//-------------------------------------
D3DXVECTOR3 CDataD3DXVECTOR3::Get(void)
{
	// 位置情報を返す
	return m_data;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

//-------------------------------------
//-	D3DXCOLORデータ用のコンストラクタ
//-------------------------------------
CDataD3DXCOLOR::CDataD3DXCOLOR()
{
	m_data = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
}

//-------------------------------------
//-	D3DXCOLORデータ用のデストラクタ
//-------------------------------------
CDataD3DXCOLOR::~CDataD3DXCOLOR()
{
}

//-------------------------------------
//- D3DXCOLORデータ用の設定処理
//-------------------------------------
void CDataD3DXCOLOR::Set(D3DXCOLOR data)
{
	// 位置情報を代入
	m_data = data;
}

//-------------------------------------
//- D3DXCOLORデータ用の取得処理
//-------------------------------------
D3DXCOLOR CDataD3DXCOLOR::Get(void)
{
	// 位置情報を返す
	return m_data;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

