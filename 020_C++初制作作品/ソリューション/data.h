
//================================================
//=
//= 各種情報のヘッター[data.h]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	二重インクルード防止
//=======================================

#ifndef _DATA_H_	//このマクロが定義されなかったら
#define _DATA_H_	//二重インクルード帽子のマクロを定義

//=======================================
//=	インクルード
//=======================================

//=======================================
//=	クラス定義
//=======================================

// Intデータ用のクラス
class CDataInt
{
public:

	CDataInt();
	~CDataInt();

	void Set(int data = 0);
	int Get(void);

private:

	int m_data;

};

// floatデータ用のクラス
class CDataFloat
{
public:
	
	CDataFloat();
	~CDataFloat();

	void Set(float data = 0);
	float Get(void);

private:

	float m_data;

};

// Boolデータ用のクラス
class CDataBool
{
public:

	CDataBool();
	~CDataBool();

	void Set(bool data = false);
	bool Get(void);

private:

	bool m_data;

};

// D3DXVECTOR2データ用のクラス
class CDataD3DXVECTOR2
{
public:

	CDataD3DXVECTOR2();
	~CDataD3DXVECTOR2();

	void Set(D3DXVECTOR2 data = D3DXVECTOR2(0.0f, 0.0f));
	D3DXVECTOR2 Get(void);

private:

	D3DXVECTOR2 m_data;

};

// D3DXVECTOR3データ用のクラス
class CDataD3DXVECTOR3
{
public:

	CDataD3DXVECTOR3();
	~CDataD3DXVECTOR3();

	void Set(D3DXVECTOR3 data = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	D3DXVECTOR3 Get(void);
	
private:

	D3DXVECTOR3 m_data;

};

// D3DXCOLORデータ用のクラス
class CDataD3DXCOLOR
{
public:

	CDataD3DXCOLOR();
	~CDataD3DXCOLOR();

	void Set(D3DXCOLOR data = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
	D3DXCOLOR Get(void);

private:

	D3DXCOLOR m_data;

};

#endif	// 二重インクルード防止の終了