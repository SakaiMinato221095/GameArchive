
//================================================
//=
//= �e����̃w�b�^�[[data.h]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	��d�C���N���[�h�h�~
//=======================================

#ifndef _DATA_H_	//���̃}�N������`����Ȃ�������
#define _DATA_H_	//��d�C���N���[�h�X�q�̃}�N�����`

//=======================================
//=	�C���N���[�h
//=======================================

//=======================================
//=	�N���X��`
//=======================================

// Int�f�[�^�p�̃N���X
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

// float�f�[�^�p�̃N���X
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

// Bool�f�[�^�p�̃N���X
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

// D3DXVECTOR2�f�[�^�p�̃N���X
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

// D3DXVECTOR3�f�[�^�p�̃N���X
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

// D3DXCOLOR�f�[�^�p�̃N���X
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

#endif	// ��d�C���N���[�h�h�~�̏I��