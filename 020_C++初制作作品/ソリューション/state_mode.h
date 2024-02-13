
//-===============================================
//-
//-	���[�h�X�e�[�^�X�����̃w�b�_�[[state_mode.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _STATE_MODE_H_		// ���̃}�N������`����Ȃ�������
#define _STATE_MODE_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "data.h"

//-======================================
//-	�N���X��`
//-======================================

class CStateMode
{
public:

	typedef enum
	{
		RESULT_STATE_NONE = 0,
		RESULT_STATE_WIN,		// �������U���g
		RESULT_STATE_END,		// �ʏ탊�U���g
		RESULT_STATE_LOOSE,		// �������U���g
		RESULT_STATE_MAX
	}RESULT_STATE;

	CStateMode();
	~CStateMode();

	void Init(void);
	void Uninit(void);

	void ResetResultState(void);

	static CStateMode *Create();

	void SetResultState(RESULT_STATE resultState);
	RESULT_STATE GetResultState(void);

private:

	
	RESULT_STATE m_resultState;	// ���U���g���
};

#endif	// ��d�C���N���[�h�h�~�̏I��

