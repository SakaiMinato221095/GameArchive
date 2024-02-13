
//-===============================================
//-
//-	�T���t�F�[�Y����[sys_game_search.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "sys_phase_search.h"

#include "game.h"
#include "manager_object.h"
#include "mgr_sys_obj.h"
#include "timer.h"
#include "time_stop.h"

#include "ui_mission.h"
#include "ui_start_text.h"

#include "Input.h"

#include "camera.h"

#include "player_search.h"

#include "qte_timing.h"

#include "garbage_collect.h"

#include "gate.h"

#include "obj_2d_none.h"
#include "effect_2d.h"

#include "state_game.h"
#include "state_battle.h"

#include "file_obj_none.h"
#include "file_evt_obj.h"
#include "file_garbage.h"
#include "file_garbage_collect.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

CPlayer *CSysPhaseSearch::m_pPlayerSearch = NULL;
CManagerObject *CSysPhaseSearch::m_pManagerObject = NULL;
CUiMission *CSysPhaseSearch::m_pUiMission = NULL;
CUiStartText *CSysPhaseSearch::m_apUiStartText[STATE_TEXT_MAX] = {};
CQte *CSysPhaseSearch::m_pQte = NULL;

CObj2dNone *CSysPhaseSearch::m_pObj2dNone = NULL;

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CSysPhaseSearch::CSysPhaseSearch()
{
	bState = false;
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CSysPhaseSearch::~CSysPhaseSearch()
{

}

//-------------------------------------
//- �T���t�F�[�Y�̏���������
//-------------------------------------
HRESULT CSysPhaseSearch::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �V�X�e���I�u�W�F�N�g�Ǘ��̎擾����
	CMgrSysObj *pMgrSysObj = CGame::GetMgrSysObj();

	//  �V�X�e���I�u�W�F�N�g�Ǘ��̎擾�̗L���𔻒�
	if (pMgrSysObj == NULL)
	{
		// ���������𔲂���
		return E_FAIL;
	}

	// ���Ԏ擾����
	CTimer *pTimer = CGame::GetMgrSysObj()->GetTimer();

	// ���Ԃ̎擾�̗L���𔻒�
	if (pTimer == NULL)
	{
		// ���������𔲂���
		return E_FAIL;
	}

	// �J�����̎擾����
	CCamera *pCamera = CManager::GetCamera();

	// �J�����̎擾�����̗L���𔻒�
	if (pCamera == NULL)
	{
		// ���������𔲂���
		return E_FAIL;
	}

	// �J������ǔ����_�ɕύX
	pCamera->SetMode(CCamera::MODE_FOLLOWING);

	// �T���v���C���[�̐��������̗L���𔻒�
	if (m_pPlayerSearch != NULL)
	{
		return E_FAIL;
	}


	// ���l�n�̐ݒ�
	pMgrSysObj->SetNumber();

	// �T���v���C���[�̏�����
	{
		// �T���v���C���[�̗L���𔻒�
		if (m_pPlayerSearch != NULL)
		{
			// �����𔲂���
			return E_FAIL;
		}

		// �T���v���C���[�̐���
		m_pPlayerSearch = CPlayerSearch::Create(
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),			// �ʒu
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),			// ����
			CObjectModel::MODEL_TYPE_PLAYER_SEARCH,	// ���f��
			CMotion::MOTION_TYPE_PLAYER_SEARCH);	// ���[�V����

		// �T���v���C���[�̏���������
		if (m_pPlayerSearch == NULL)
		{// ���s��

			// ���s���b�Z�[�W
			MessageBox(hWnd, "�T���v���C���[�̐���", "�����������s�I", MB_ICONWARNING);

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
			m_pUiMission = CUiMission::Create(CUiMission::TEX_SEARCH);

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

	// ���ʂȂ��I�u�W�F�N�g�̐ݒ菈��
	{
		// ���ʂȂ��I�u�W�F�N�g�̗L���𔻒�
		if (m_pObj2dNone == NULL)
		{
			// �������ʂȂ��I�u�W�F�N�g�̐���
			m_pObj2dNone = CObj2dNone::Create(CObj2dNone::TEX_ELEM_WINDOW);

			// �������ʂȂ��I�u�W�F�N�g�̏���������
			if (m_pObj2dNone == NULL)
			{// ���s��

			 // ���s���b�Z�[�W
				MessageBox(hWnd, "���ʂȂ��I�u�W�F�N�g�̏�����", "�����������s�I", MB_ICONWARNING);

				// �������𔲂���
				return E_FAIL;
			}

			m_pObj2dNone->Set(
				D3DXVECTOR3(SCREEN_WIDTH * 0.925f, SCREEN_HEIGHT * 0.2f, 0.0f),
				D3DXVECTOR3(50.0f, 50.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{// �S�~�������Ă���Ƃ�

		 // ���s���b�Z�[�W
			MessageBox(hWnd, "���ʂȂ��I�u�W�F�N�g�̏�����", "�����������s�I", MB_ICONWARNING);

			// �������𔲂���
			return E_FAIL;
		}
	}

	// ���Ԓ�~�̏��擾
	CTimeStop *pTimeStop = CManager::GetManagerTime();

	// ���Ԓ�~�̏��擾�̐����𔻒�
	if (pTimeStop == NULL)
	{// ���s��

	 // �X�V�����𔲂���
		return E_FAIL;
	}

	// �Q�[���X�e�[�^�X�̃|�C���^��錾
	CStateGame *pStateGame = CGame::GetStateGame();

	// �Q�[���X�e�[�^�X�̏��擾�̐����𔻒�
	if (pStateGame == NULL)
	{// ���s��

		// �����𔲂���
		return E_FAIL;
	}

	if (pStateGame->m_bDataStart.Get() == false)
	{
		// �J�n�̎��Ԓ�~
		pTimeStop->Set(0.0f, 180);

		// �J�n�̐ݒ�
		bState = true;
	}

	// ���ʂȂ��I�u�W�F�N�g�ǂݍ��ݐݒ菈��
	CFileObjNone::Load(CFileObjNone::TXT_NORMAL_000);

	// �C�x���g�I�u�W�F�N�g�ǂݍ��ݐݒ菈��
	CFileEvtObj::Load(CFileEvtObj::TXT_NORMAL_000);

	// �S�~�̐ݒu
	CFileGarbage::Locate();

	// �Q�[�g�̐�������	
	CGate *pGate = CGate::Create(CGate::MODEL_GATE_000);

	if (pGate != NULL)
	{
		// �ʒu��ݒ�
		pGate->m_dataPos.Set(D3DXVECTOR3(0.0f, 0.0f, 500.0f));

		// �Q�[�g�̐ݒ菈��
		CManagerObject::SetGate(pGate);
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �T���t�F�[�Y�̏I������
//-------------------------------------
void CSysPhaseSearch::Uninit(void)
{
	// �V�X�e���I�u�W�F�N�g�Ǘ��̎擾����
	CMgrSysObj *pMgrSysObj = CGame::GetMgrSysObj();

	// �Ȃ��Ȃ����S�~���m�F
	CFileGarbage::ObjCheck();

	//  �V�X�e���I�u�W�F�N�g�Ǘ��̎擾�̗L���𔻒�
	if (pMgrSysObj != NULL)
	{
		// �����̃|�C���^����������
		pMgrSysObj->NullAllNumber();
	}

	// �T���v���C���[�̗L���𔻒�
	if (m_pPlayerSearch != NULL)
	{
		// �T���v���C���[�̏I������
		m_pPlayerSearch->Uninit();

		// �T���v���C���[�̃|�C���^����������
		m_pPlayerSearch = NULL;
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

	for (int nCount = 0; nCount < STATE_TEXT_MAX; nCount++)
	{
		// �X�^�[�g�e�L�X�g�̔j��
		if (m_apUiStartText[nCount] != NULL)
		{
			// �X�^�[�g�e�L�X�g�̏I������
			m_apUiStartText[nCount] = NULL;
		}
	}

	// �N�C�b�N�^�C���C�x���g�̗L���𔻒�
	if (m_pQte != NULL)
	{
		// �N�C�b�N�^�C���C�x���g�̏I������
		m_pQte->Uninit();

		// �N�C�b�N�^�C���C�x���g�̃|�C���^�̏���
		m_pQte = NULL;
	}

	// �Q�[���X�e�[�^�X�̔j��
	if (m_pObj2dNone != NULL)
	{
		// �Q�[���X�e�[�^�X�̏I������
		m_pObj2dNone = NULL;
	}

	// �I�u�W�F�N�g�̑S�J������
	CObject::ReleaseAll();
}

//-------------------------------------
//- �T���t�F�[�Y�̍X�V����
//-------------------------------------
void CSysPhaseSearch::Update(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

		// �����𔲂���
		return;
	}

	// ���Ԓ�~�̏��擾
	CTimeStop *pTimeStop = CManager::GetManagerTime();

	// ���Ԓ�~�̏��擾�̐����𔻒�
	if (pTimeStop == NULL)
	{// ���s��

	 // �X�V�����𔲂���
		return;
	}

	// �t�F�[�Y��Ԃ̔���
	if (CSysGamePhase::GetType() != CSysGamePhase::GetTypeNext())
	{
		// �t�F�[�Y�̐؂�ւ�
		CGame::SetPhase(CSysGamePhase::GetTypeNext());

		return;
	}

	// �Q�[���X�e�[�^�X�̃|�C���^��錾
	CStateBattle *pStateBattle = CGame::GetStateBattle();

	// �Q�[���X�e�[�^�X�̏��擾�̐����𔻒�
	if (pStateBattle == NULL)
	{// ���s��

	 // �����𔲂���
		return;
	}

	// �X�^�[�g�e�L�X�g�̐ݒ菈��
	if (bState == true)
	{
		// �X�^�[�g�e�L�X�g�̗L���𔻒�
		if (m_apUiStartText[STATE_TEXT_000] == NULL)
		{
			// �X�^�[�g�e�L�X�g�̐���
			m_apUiStartText[STATE_TEXT_000] = CUiStartText::Create(CUiStartText::TEX_START_000);

			// �X�^�[�g�e�L�X�g�̗L���̔���
			if (m_apUiStartText[STATE_TEXT_000] == NULL)
			{// ���s��

			 // �������𔲂���
				return;
			}

			// �X�^�[�g�e�L�X�g�̐ݒ菈��
			m_apUiStartText[STATE_TEXT_000]->Set(
				D3DXVECTOR3(SCREEN_WIDTH * -0.1f,SCREEN_HEIGHT * 0.4f,0.0f),
				D3DXVECTOR3(SCREEN_WIDTH *  0.35f,SCREEN_HEIGHT * 0.4f,0.0f),
				D3DXVECTOR3(250.0f,50.0f,0.0f),
				D3DXVECTOR3(15.0f,0.0f,0.0f));
		}
	}

	if (pTimeStop->m_nDataTimeCount.Get() >= 60)
	{
		// �X�^�[�g�e�L�X�g�̐ݒ菈��
		{
			// �X�^�[�g�e�L�X�g�̗L���𔻒�
			if (m_apUiStartText[STATE_TEXT_001] == NULL)
			{
				// �X�^�[�g�e�L�X�g�̐���
				m_apUiStartText[STATE_TEXT_001] = CUiStartText::Create(CUiStartText::TEX_START_001);

				// �X�^�[�g�e�L�X�g�̗L���̔���
				if (m_apUiStartText[STATE_TEXT_001] == NULL)
				{// ���s��

				 // �������𔲂���
					return;
				}

				// �X�^�[�g�e�L�X�g�̐ݒ菈��
				m_apUiStartText[STATE_TEXT_001]->Set(
					D3DXVECTOR3(SCREEN_WIDTH *  1.1f, SCREEN_HEIGHT * 0.6f, 0.0f),
					D3DXVECTOR3(SCREEN_WIDTH *  0.6f, SCREEN_HEIGHT * 0.6f, 0.0f),
					D3DXVECTOR3(350.0f, 50.0f, 0.0f),
					D3DXVECTOR3(-15.0f, 0.0f, 0.0f));
			}
		}
	}

	if (pTimeStop->m_nDataTimeCount.Get() == pTimeStop->m_nDataTimeCountMax.Get() &&
		bState == true)
	{
		// �X�^�[�g���I�����
		bState = false;

		// �Q�[���X�e�[�^�X�̃|�C���^��錾
		CStateGame *pStateGame = CGame::GetStateGame();

		// �Q�[���X�e�[�^�X�̏��擾�̐����𔻒�
		if (pStateGame == NULL)
		{// ���s��

		 // �����𔲂���
			return;
		}
		
		pStateGame->m_bDataStart.Set(true);

		for (int nCount = 0; nCount < STATE_TEXT_MAX; nCount++)
		{
			// �X�^�[�g�e�L�X�g�̔j��
			if (m_apUiStartText[nCount] != NULL)
			{
				// �X�^�[�g�e�L�X�g�̏I������
				m_apUiStartText[nCount]->Uninit();
				m_apUiStartText[nCount] = NULL;
			}
		}
	}

	if (m_pQte != NULL)
	{
		// �N�C�b�N�^�C���C�x���g�̍X�V����
		m_pQte->Update();
	}

	// ���擾
	int nEffectCut = m_dataEffectCut.Get();				// �G�t�F�N�g�J�E���g

	// ���擾�i���ʂȂ�2D�j
	D3DXVECTOR3 pos = m_pObj2dNone->m_dataPos.Get();	// �ʒu

	// ���擾�i�퓬�X�e�[�^�X�j
	CStateBattle::ELEM_TYPE elemType = pStateBattle->GetElemType();	// �������
	int nElemRank = pStateBattle->m_aDataElemRank[elemType].Get();	// ���������N

	// �G�t�F�N�g�J�E���g�̔���
	if (nEffectCut > 0)
	{
		// �G�t�F�N�g�J�E���g�̌��Z
		nEffectCut--;
	}
	else
	{
		// �ϐ��錾
		D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �T�C�Y
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ���
		D3DXCOLOR color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// �F
		int nLife = 0;

		if (nElemRank == 0)
		{
			size = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
			move = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
			nLife = 30;
		}
		else if (nElemRank == 1)
		{
			size = D3DXVECTOR3(20.0f, 20.0f, 0.0f);
			move = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
			nLife = 45;
		}
		else if (nElemRank == 2)
		{
			size = D3DXVECTOR3(30.0f, 30.0f, 0.0f);
			move = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
			nLife = 60;
		}
		else if (nElemRank == 3)
		{
			size = D3DXVECTOR3(45.0f, 45.0f, 0.0f);
			move = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
			nLife = 60;
		}

		switch (elemType)
		{
		case CStateBattle::ELEM_TYPE_NORMAL:

			color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			break;

		case CStateBattle::ELEM_TYPE_CHAOS:

			color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

			break;
		}

		// 2D�G�t�F�N�g�̐���
		CEffect2d *pEffect2d = CEffect2d::Create(CEffect2d::TEX_NORMAL_000);

		// 2D�G�t�F�N�g�̐ݒ�
		pEffect2d->Set(
			D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z),
			size,
			D3DXVECTOR3(0.0f, -1.0f, 0.0f),
			color,
			nLife,
			false);

		nEffectCut = 1;
	}

	// ���X�V�i�G�t�F�N�g2D�j
	m_dataEffectCut.Set(nEffectCut);

#if _DEBUG
	//�@���͂̔��� if�iC�L�[�̃g���K�[�j
	if (pInputKeyboard->GetTrigger(DIK_C) != NULL)
	{
		CGame::SetPhase(TYPE::TYPE_SHOP);
	}
#endif
}

//-------------------------------------
//- �T���t�F�[�Y�̕`�揈��
//-------------------------------------
void CSysPhaseSearch::Draw(void)
{

}

//-------------------------------------
//- �N�C�b�N�^�C���C�x���g�̐ݒ菈��
//-------------------------------------
void CSysPhaseSearch::SetQte(CQte::TYPE_QTE typeQte)
{
	// �N�C�b�N�^�C���C�x���g�̗L���𔻒�
	if (m_pQte == NULL)
	{
		switch (typeQte)
		{
		case CQte::TYPE_QTE_TIMING:

			// �N�C�b�N�^�C���C�x���g�̐���
			m_pQte = CQteTiming::Create();

			break;
		}

		// �N�C�b�N�^�C���C�x���g�̗L�����𔻒�
		if (m_pQte == NULL)
		{// ���s��

			// �������𔲂���
			return;
		}
	}
}

//-------------------------------------
//-	�N�C�b�N�^�C���C�x���g�̏������������擾
//-------------------------------------
void CSysPhaseSearch::ReleaseQte(void)
{
	// �N�C�b�N�^�C���C�x���g�̏I������
	m_pQte->Uninit();

	// �N�C�b�N�^�C���C�x���g�̊J������
	delete m_pQte;
	m_pQte = NULL;
}

//-------------------------------------
//-	�T���v���C���[�̏����擾
//-------------------------------------
CPlayer *CSysPhaseSearch::GetPlayer(void)
{
	// �T���v���C���[�̏���Ԃ�
	return m_pPlayerSearch;
}

//-------------------------------------
//- �T���t�F�[�Y�̃I�u�W�F�N�g�Ǘ��̎擾����
//-------------------------------------
CManagerObject *CSysPhaseSearch::GetManagerObject(void)
{
	// �I�u�W�F�N�g�Ǘ��̏���Ԃ�
	return m_pManagerObject;
}

//-------------------------------------
//-	�T���t�F�[�Y�̖ړIUI�̏����擾
//-------------------------------------
CUiMission *CSysPhaseSearch::GetUiMission(void)
{
	// �ړIUI�̏���Ԃ�
	return m_pUiMission;
}

//-------------------------------------
//-	���ʂȂ�2D�̏����擾
//-------------------------------------
CObj2dNone * CSysPhaseSearch::GetObj2DNone(void)
{
	return m_pObj2dNone;
}
