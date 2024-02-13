
//-===============================================
//-
//-	�t�F�[�Y�Ǘ�����[phase_manager.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "phase_manager.h"

#include "manager.h"
#include "renderer.h"

#include "fade.h"

#include "helper_sakai.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�R���X�g��`
//=======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CPhaseManager::CPhaseManager(int nPriority)
{
	ZeroMemory(&m_info, sizeof(m_info));
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CPhaseManager::~CPhaseManager()
{

}

//-------------------------------------
//- �w�i�̃e�N�X�`���̓ǂݍ���
//-------------------------------------
HRESULT CPhaseManager::Load(void)
{
	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �w�i�̓ǂݍ��񂾃e�N�X�`���̔j��
//-------------------------------------
void CPhaseManager::Unload(void)
{

}
//-------------------------------------
//- �����������i3D�I�u�W�F�N�g�ݒ�j
//-------------------------------------
HRESULT CPhaseManager::Init(void)
{
	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �I������
//-------------------------------------
void CPhaseManager::Uninit(void)
{

}

//-------------------------------------
//- �X�V����
//-------------------------------------
void CPhaseManager::Update(void)
{
}

//-------------------------------------
//- �`�揈��
//-------------------------------------
void CPhaseManager::Draw(void)
{

}

//-------------------------------------
//- �G���S�����Z�̐ݒ�
//-------------------------------------
void CPhaseManager::AddDeadEnemy(void)
{
	// �^�[�Q�b�g�������Z
	m_info.nTargetCompCnt++;

	if (m_info.nTargetCompCnt >= m_info.nTargetCompNum)
	{
		// �^�[�Q�b�g�J�E���g��������
		m_info.nTargetCompCnt = 0;

		// ���Z����
		m_info.typePhaseNew = (TYPE_PHASE)HelperSakai::AddLimitStop(m_info.typePhaseNew, 1, TYPE_PHASE_ONE, TYPE_PHASE_COMP);

		// �R���v���[�g�󋵂��m�F
		if (m_info.typePhaseNew >= TYPE_PHASE_COMP)
		{
			// �R���v���[�g��ݒ�
			SetComp();
		}
	}
}

//-------------------------------------
//- ��������
//-------------------------------------
CPhaseManager* CPhaseManager::Create(void)
{
	// �|�C���^��錾
	CPhaseManager* pCPhaseManager = DBG_NEW CPhaseManager(1);

	// �����̐����̗L���𔻒�
	if (pCPhaseManager != NULL)
	{
		// ����������
		if (FAILED(pCPhaseManager->Init()))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCPhaseManager == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �|�C���^��Ԃ�
	return pCPhaseManager;
}

//-------------------------------------
//- �R���v���[�g�ݒ菈��
//-------------------------------------
void CPhaseManager::SetComp(void)
{
	if (CManager::GetInstance() != nullptr)
	{
		if (CManager::GetInstance()->GetFade() != nullptr)
		{
			// �Q�[�����[�h
			CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_RESULT);
		}
	}
}