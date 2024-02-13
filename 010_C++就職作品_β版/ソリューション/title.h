
//-===============================================
//-
//-	�^�C�g���̏����̃w�b�_�[[title.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _TITLE_H_		// ���̃}�N������`����Ȃ�������
#define _TITLE_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "manager.h"

//=======================================
//=	�}�N����`
//=======================================

//-======================================
//-	�O���錾
//-======================================

class CCharacter;

class CObject2d;

//-======================================
//-	�N���X��`
//-======================================

class CTitle : public CScene
{

public:

	typedef enum
	{
		TEX_NULL = 0,		// �Ȃ�
		TEX_LOGO_000,		// �^�C�g�����S
		TEX_BUTTON_000,		// �^�C�g���{�^��
		TEX_MAX
	}TEX;

	typedef enum
	{
		TYPE_2D_LOGO = 0,	// �^�C�g�����S
		TYPE_2D_BUTTON,	// �^�C�g���{�^��
		TYPE_2D_MAX
	}TYPE_2D;

	CTitle();
	~CTitle();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	static CCharacter *m_pCharacter;
	static CObject2d *m_apObj2d[TYPE_2D_MAX];

	static int m_aTextureNldx[TEX_MAX];		// �e�N�X�`���ԍ�
};

#endif	// ��d�C���N���[�h�h�~�̏I��
