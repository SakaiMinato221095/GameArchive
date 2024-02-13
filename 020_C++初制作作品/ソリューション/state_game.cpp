
//-===============================================
//-
//-	�Q�[���X�e�[�^�X����[state_game.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "state_game.h"

#include "renderer.h"
#include "manager.h"
#include "state_game.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	�Q�[���X�e�[�^�X�̃R���X�g���N�^
//-------------------------------------
CStateGame::CStateGame()
{
	m_endState = END_STATE_NONE;
}

//-------------------------------------
//-	�Q�[���X�e�[�^�X�̃f�X�g���N�^
//-------------------------------------
CStateGame::~CStateGame()
{

}

//-------------------------------------
//- �Q�[���X�e�[�^�X�̏���������
//-------------------------------------
void CStateGame::Init(void)
{
	// �����ݒ菈��
	InitSet();
}

//-------------------------------------
//- �Q�[���X�e�[�^�X�̏I������
//-------------------------------------
void CStateGame::Uninit(void)
{

}

//-------------------------------------
//- �Q�[���X�e�[�^�X�̐�������
//-------------------------------------
CStateGame *CStateGame::Create(void)
{
	// �A�C�e���̃|�C���^��錾
	CStateGame *pCStateGame = DBG_NEW CStateGame;

	// �����̐����̗L���𔻒�
	if (pCStateGame != NULL)
	{
		// ����������
		pCStateGame->Init();
	}
	else if (pCStateGame == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �A�C�e���̃|�C���^��Ԃ�
	return pCStateGame;
}

//-------------------------------------
//- �Q�[���X�e�[�^�X�̓G�̎��S
//-------------------------------------
void CStateGame::AddEnemyDeath(void)
{
	// �ϐ��錾�i���擾�j
	int nEnemyDeathCut = m_nDataEnemyDeathCut.Get();	// �G�̎��S���J�E���g

	// �G�̎��S���𑝂₷
	nEnemyDeathCut++;

	// ���X�V
	m_nDataEnemyDeathCut.Set(nEnemyDeathCut);			// �G�̎��S���J�E���g
}

//-------------------------------------
//- �Q�[���X�e�[�^�X�̏I����Ԃ̐ݒ菈��
//-------------------------------------
void CStateGame::SetEndState(END_STATE endState)
{
	// �I����Ԃ̑��
	m_endState = endState;
}

//-------------------------------------
//- �Q�[���X�e�[�^�X�̏I����Ԃ̎擾����
//-------------------------------------
CStateGame::END_STATE CStateGame::GetEndState(void)
{
	return m_endState;
}

//-------------------------------------
//- �Q�[���X�e�[�^�X�̏����ݒ菈��
//-------------------------------------
void CStateGame::InitSet(void)
{
	m_nDataEnemyDeathTarget.Set(10);	// �G�̖ڕW���S��
}