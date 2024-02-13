
//-===============================================
//-
//-	�|�[�Y�̏����̃w�b�_�[[pause.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _PAUSE_H_		// ���̃}�N������`����Ȃ�������
#define _PAUSE_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object.h"

//=======================================
//=	�}�N����`
//=======================================

//-======================================
//-	�O���錾
//-======================================

class CObject2d;

//-======================================
//-	�N���X��`
//-======================================

class CPause
{

public:

	enum TEX
	{
		TEX_BG = 0,	// �w�i
		TEX_GAME,	// �Q�[��
		TEX_RETRY,	// ���g���C
		TEX_TITLE,	// �^�C�g��
		TEX_CURSOR,	// �J�[�\��
		TEX_MAX
	};

	enum TYPE
	{
		TYPE_BG = 0,	// �w�i
		TYPE_GAME,		// �Q�[��
		TYPE_RETRY,		// ���g���C
		TYPE_TITLE,		// �^�C�g��
		TYPE_CURSOR,	// �J�[�\��
		TYPE_MAX
	};

	typedef enum
	{
		TYPE_SELECT_GAME = 0,	// �Q�[��
		TYPE_SELECT_RETRY,		// ���g���C
		TYPE_SELECT_TITLE,		// �^�C�g��
		TYPE_SELECT_MAX,
	}TYPE_SELECT;

	CPause();
	~CPause();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPause * Create(void);

	bool GetOk(void) { return m_bOk; }
	TYPE_SELECT GetTypeSelect(void) { return m_typeSelect; }

private:

	// �����ڂ̏��
	struct InfoVisual
	{
		CObject2d* apObj2d[TYPE_MAX];		// 2D�I�u�W�F�N�g�̃|�C���^
	};

	InfoVisual m_infoVisual;			// �����ڂ̏��
	TYPE_SELECT m_typeSelect;			// ���݂̑I���̎��

	bool m_bOk;

	static int m_nTextureNldx[TEX_MAX];

};

#endif	// ��d�C���N���[�h�h�~�̏I��

