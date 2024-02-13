
//-===============================================
//-
//-	�w���t�F�[�Y�V�X�e������[sys_game_shop.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "sys_phase_shop.h"

#include "game.h"
#include "manager_object.h"
#include "mgr_sys_obj.h"
#include "timer.h"

#include "Input.h"

#include "camera.h"

#include "player_shop.h"

#include "file_item.h"

#include "ui_mission.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

CPlayer *CSysPhaseShop::m_pPlayerShop = NULL;
CManagerObject *CSysPhaseShop::m_pManagerObject = NULL;
CUiMission *CSysPhaseShop::m_pUiMission = NULL;

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CSysPhaseShop::CSysPhaseShop()
{

}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CSysPhaseShop::~CSysPhaseShop()
{

}

//-------------------------------------
//- �w���t�F�[�Y�̏���������
//-------------------------------------
HRESULT CSysPhaseShop::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �V�X�e���I�u�W�F�N�g�Ǘ��̎擾����
	CMgrSysObj *pMgrSysObj = CGame::GetMgrSysObj();

	//  �V�X�e���I�u�W�F�N�g�Ǘ��̎擾�̗L���𔻒�
	if (pMgrSysObj == NULL)
	{
		// ���������𔲂���
		return E_FAIL;
	}

	// ���l�n�̐ݒ�
	pMgrSysObj->SetNumber();

	// �J�����̎擾����
	CCamera *pCamera = CManager::GetCamera();

	// �J�����̎擾�����̗L���𔻒�
	if (pCamera == NULL)
	{
		// ���������𔲂���
		return E_FAIL;
	}

	// �J������X���_�ɕύX
	pCamera->SetMode(CCamera::MODE_SHOP);

	// �w���v���C���[�̏�����
	{
		// �w���v���C���[�̗L���𔻒�
		if (m_pPlayerShop != NULL)
		{
			// �����𔲂���
			return E_FAIL;
		}

		// �w���v���C���[�̐���
		m_pPlayerShop = CPlayerShop::Create(
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// �ʒu
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// ����
			CObjectModel::MODEL_TYPE_PLAYER_SEARCH,		// ���f��
			CMotion::MOTION_TYPE_PLAYER_SEARCH);		// ���[�V����

		// �w���v���C���[�̏���������
		if (m_pPlayerShop == NULL)
		{// ���s��

			// ���s���b�Z�[�W
			MessageBox(hWnd, "�w���v���C���[�̐���", "�����������s�I", MB_ICONWARNING);

			// �������𔲂���
			return E_FAIL;
		}
	}

	// �I�u�W�F�N�g�Ǘ��̏�����
	{
		// �I�u�W�F�N�g�Ǘ��̗L���𔻒�
		if (m_pManagerObject == NULL)
		{
			// �I�u�W�F�N�g�Ǘ��̐���
			m_pManagerObject = DBG_NEW CManagerObject;

			// �I�u�W�F�N�g�Ǘ��̏���������
			if (FAILED(m_pManagerObject->Init(hInstance, hWnd, bWindow)))
			{// ���s��

				// ���s���b�Z�[�W
				MessageBox(hWnd, "�I�u�W�F�N�g�Ǘ��̐���", "�����������s�I", MB_ICONWARNING);

				// �������𔲂���
				return E_FAIL;
			}
		}
		else
		{// �S�~�������Ă���Ƃ�

		 // �������𔲂���
			return E_FAIL;
		}
	}

	// �ړIUI�̐ݒ菈��
	{
		// �ړIUI�̗L���𔻒�
		if (m_pUiMission == NULL)
		{
			// �ړIUI�̐���
			m_pUiMission = CUiMission::Create(CUiMission::TEX_SHOP);

			// �ړIUI�̏���������
			if (m_pUiMission == NULL)
			{// ���s��

			 // ���s���b�Z�[�W
				MessageBox(hWnd, "�ړIUI�̏�����", "�����������s�I", MB_ICONWARNING);

				// �������𔲂���
				return E_FAIL;
			}
		}
		else
		{// �S�~�������Ă���Ƃ�

		 // ���s���b�Z�[�W
			MessageBox(hWnd, "�ړIUI�̏�����", "�����������s�I", MB_ICONWARNING);

			// �������𔲂���
			return E_FAIL;
		}
	}

	// �A�C�e���ǂݍ��ݐݒ菈��
	CFileItem::Load(CFileItem::TXT_NORMAL_000);

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �w���t�F�[�Y�̏I������
//-------------------------------------
void CSysPhaseShop::Uninit(void)
{
	// �V�X�e���I�u�W�F�N�g�Ǘ��̎擾����
	CMgrSysObj *pMgrSysObj = CGame::GetMgrSysObj();

	//  �V�X�e���I�u�W�F�N�g�Ǘ��̎擾�̗L���𔻒�
	if (pMgrSysObj != NULL)
	{
		// �����̃|�C���^����������
		pMgrSysObj->NullAllNumber();
	}

	// �w���v���C���[�̗L���𔻒�
	if (m_pPlayerShop != NULL)
	{
		// �w���v���C���[�̏I������
		m_pPlayerShop->Uninit();

		// �w���v���C���[�̃|�C���^����������
		m_pPlayerShop = NULL;
	}

	// �I�u�W�F�N�g�Ǘ��̗L���𔻒�
	if (m_pManagerObject != NULL)
	{
		// �I�u�W�F�N�g�̏I��
		m_pManagerObject->Uninit();

		// �I�u�W�F�N�g�Ǘ��̊J������
		delete m_pManagerObject;
		m_pManagerObject = NULL;
	}

	// �ړIUI�̗L���𔻒�
	if (m_pUiMission != NULL)
	{
		// �ړIUI�̏I������
		m_pUiMission->Uninit();

		// �ړIUI�̃|�C���^�̏���
		m_pUiMission = NULL;
	}

	// �I�u�W�F�N�g�̑S�J������
	CObject::ReleaseAll();
}

//-------------------------------------
//- �w���t�F�[�Y�̍X�V����
//-------------------------------------
void CSysPhaseShop::Update(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

	 // �����𔲂���
		return;
	}

#if _DEBUG
	//�@���͂̔��� if�iC�L�[�̃g���K�[�j
	if (pInputKeyboard->GetTrigger(DIK_C) != NULL)
	{
		CGame::SetPhase(TYPE::TYPE_BATTLE);
	}
#endif

}

//-------------------------------------
//- �w���t�F�[�Y�̕`�揈��
//-------------------------------------
void CSysPhaseShop::Draw(void)
{

}

//-------------------------------------
//-	�w���v���C���[�̏����擾
//-------------------------------------
CPlayer *CSysPhaseShop::GetPlayer(void)
{
	// �T���v���C���[�̏���Ԃ�
	return m_pPlayerShop;
}

//-------------------------------------
//- �w���t�F�[�Y�̃I�u�W�F�N�g�Ǘ��̎擾����
//-------------------------------------
CManagerObject * CSysPhaseShop::GetManagerObject(void)
{
	return m_pManagerObject;
}