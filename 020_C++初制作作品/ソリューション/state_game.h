
//-===============================================
//-
//-	�Q�[���X�e�[�^�X�����̃w�b�_�[[state_game.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _STATE_GAME_H_		// ���̃}�N������`����Ȃ�������
#define _STATE_GAME_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "data.h"

//-======================================
//-	�N���X��`
//-======================================

class CStateGame
{
public:

	// �I���̏��
	typedef enum
	{
		END_STATE_NONE = 0,	// �Ȃ�
		END_STATE_BOSS,		// �{�X���j
		END_STATE_TIME,		// ���Ԍo��
		END_STATE_DIED,		// ���S
		END_STATE_MAX
	}END_STATE;

	CStateGame();
	~CStateGame();

	void Init(void);
	void Uninit(void);

	static CStateGame *Create();

	void AddEnemyDeath(void);

	void SetEndState(END_STATE endState);
	END_STATE GetEndState(void);

	CDataInt m_nDataEnemyDeathCut;		// �G�̎��S�J�E���g
	CDataInt m_nDataEnemyDeathTarget;	// �G�̖ڕW���S��

	CDataBool m_bDataStart;				// �J�n�̗L��
private:

	void InitSet(void);

	END_STATE m_endState;				// �I���̏��

};

#endif	// ��d�C���N���[�h�h�~�̏I��

