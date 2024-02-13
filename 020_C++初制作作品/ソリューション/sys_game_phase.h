
//-===============================================
//-
//-	�Q�[���t�F�[�Y�V�X�e�������̃w�b�_�[[sys_game_phase.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _SYS_GAME_PHASE_H_		// ���̃}�N������`����Ȃ�������
#define _SYS_GAME_PHASE_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "data.h"
#include "sys_game_phase.h"

//-======================================
//-	�O���錾
//-======================================

class CPlayer;

//-======================================
//-	�N���X��`
//-======================================

class CSysGamePhase
{

public:

	typedef enum
	{
		TYPE_SEARCH = 0,	// �T���t�F�[�Y
		TYPE_SHOP,			// �w���t�F�[�Y
		TYPE_BATTLE,		// �퓬�t�F�[�Y
		TYPE_MAX
	}TYPE;

	CSysGamePhase();
	virtual ~CSysGamePhase();

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static CSysGamePhase *Create(TYPE type, HINSTANCE hInstance = NULL, HWND hWnd = 0, BOOL bWindow = true);

	static void SetType(TYPE type);
	static TYPE GetType(void);

	static void SetTypeNext(TYPE typeNext);
	static TYPE GetTypeNext(void);

	static CPlayer *GetPlayer(void);

private:

	static TYPE m_type;		// �Q�[���t�F�[�Y�̎��
	static TYPE m_typeNext;	// ���̃t�F�[�Y�̐ݒ�
};

#endif	// ��d�C���N���[�h�h�~�̏I��
