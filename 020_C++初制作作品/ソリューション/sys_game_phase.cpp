
//-===============================================
//-
//-	�Q�[���t�F�[�Y�V�X�e������[sys_game_phase.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "sys_game_phase.h"

#include "sys_phase_search.h"
#include "sys_phase_shop.h"
#include "sys_phase_battle.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

CSysGamePhase::TYPE CSysGamePhase::m_type = (CSysGamePhase::TYPE)0;
CSysGamePhase::TYPE CSysGamePhase::m_typeNext = (CSysGamePhase::TYPE)0;

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CSysGamePhase::CSysGamePhase()
{
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CSysGamePhase::~CSysGamePhase()
{

}

//-------------------------------------
//- �Q�[���t�F�[�Y����������
//-------------------------------------
HRESULT CSysGamePhase::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �Q�[���t�F�[�Y�I������
//-------------------------------------
void CSysGamePhase::Uninit(void)
{

}

//-------------------------------------
//- �Q�[���t�F�[�Y�X�V����
//-------------------------------------
void CSysGamePhase::Update(void)
{

}

//-------------------------------------
//- �Q�[���t�F�[�Y�`�揈��
//-------------------------------------
void CSysGamePhase::Draw(void)
{

}

//-------------------------------------
//- �Q�[���t�F�[�Y��������
//-------------------------------------
CSysGamePhase *CSysGamePhase::Create(TYPE type, HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �ϐ��錾
	CSysGamePhase *pSysGamePhase = NULL;

	// �w�肳�ꂽ���[�h�̐���
	switch (type)
	{
	case TYPE::TYPE_SEARCH:

		pSysGamePhase = DBG_NEW CSysPhaseSearch;

		break;

	case TYPE::TYPE_SHOP:

		pSysGamePhase = DBG_NEW CSysPhaseShop;

		break;

	case TYPE::TYPE_BATTLE:

		pSysGamePhase = DBG_NEW CSysPhaseBattle;

		break;
	}

	// �����̐����̗L���𔻒�
	if (pSysGamePhase != NULL)
	{
		// ���[�h�ݒ菈��
		pSysGamePhase->SetType(type);
		pSysGamePhase->SetTypeNext(type);

		// ����������
		if (FAILED(pSysGamePhase->Init(hInstance, hWnd, bWindow)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pSysGamePhase == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �V�[���̏���Ԃ�
	return pSysGamePhase;

}

//-------------------------------------
//- �Q�[���t�F�[�Y�̎擾����
//-------------------------------------
CPlayer *CSysGamePhase::GetPlayer(void)
{
	switch (m_type)
	{
	case TYPE_SEARCH:

		return CSysPhaseSearch::GetPlayer();

		break;

	case TYPE_SHOP:

		return CSysPhaseShop::GetPlayer();

		break;

	case TYPE_BATTLE:

		return CSysPhaseBattle::GetPlayer();

		break;
	}

	return NULL;
}

//-------------------------------------
//- �Q�[���t�F�[�Y�̐ݒ菈��
//-------------------------------------
void CSysGamePhase::SetType(TYPE type)
{
	// ���[�h���
	m_type = type;
}

//-------------------------------------
//- �Q�[���t�F�[�Y�̎擾����
//-------------------------------------
CSysGamePhase::TYPE CSysGamePhase::GetType(void)
{
	// ���[�h��Ԃ�
	return m_type;
}

//-------------------------------------
//- ���̃Q�[���t�F�[�Y�̐ݒ菈��
//-------------------------------------
void CSysGamePhase::SetTypeNext(TYPE typeNext)
{
	// ���[�h���
	m_typeNext = typeNext;
}

//-------------------------------------
//- ���̃Q�[���t�F�[�Y�̎擾����
//-------------------------------------
CSysGamePhase::TYPE CSysGamePhase::GetTypeNext(void)
{
	// ���[�h��Ԃ�
	return m_typeNext;
}