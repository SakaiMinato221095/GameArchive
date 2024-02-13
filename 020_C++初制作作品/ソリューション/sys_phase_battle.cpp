
//-===============================================
//-
//-	�퓬�t�F�[�Y�̏���[sys_pase_battle.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "sys_phase_battle.h"

#include "game.h"
#include "manager_object.h"
#include "mgr_sys_obj.h"
#include "timer.h"

#include "Input.h"

#include "camera.h"

#include "player_battle.h"

#include "life.h"

#include "obj_2d_none.h"
#include "effect_2d.h"

#include "file_obj_none.h"
#include "file_evt_obj.h"
#include "file_emy_nor.h"

#include "ui_mission.h"

#include "state_game.h"
#include "state_battle.h"

#include "enemy_boss.h"

#include "gate.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

CLife *CSysPhaseBattle::m_pLife = NULL;

CPlayer *CSysPhaseBattle::m_pPlayerBattle = NULL;

CManagerObject *CSysPhaseBattle::m_pManagerObject = NULL;

CUiMission *CSysPhaseBattle::m_pUiMission = NULL;

CObj2dNone *CSysPhaseBattle::m_pObj2dNone = NULL;

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CSysPhaseBattle::CSysPhaseBattle()
{
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CSysPhaseBattle::~CSysPhaseBattle()
{
}

//-------------------------------------
//- �퓬�t�F�[�Y�̏���������
//-------------------------------------
HRESULT CSysPhaseBattle::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �V�X�e���I�u�W�F�N�g�Ǘ��̎擾����
	CMgrSysObj *pMgrSysObj = CGame::GetMgrSysObj();

	//  �V�X�e���I�u�W�F�N�g�Ǘ��̎擾�̗L���𔻒�
	if (pMgrSysObj == NULL)
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

	// ���l�n�̍Đݒ�
	pMgrSysObj->SetNumber();

	// �J������ǔ����_�ɕύX
	pCamera->SetMode(CCamera::MODE_FOLLOWING);

	// �̗͂̏�����
	{
		// �̗̗͂L���𔻒�
		if (m_pLife != NULL)
		{
			// �����𔲂���
			return E_FAIL;
		}

		// �̗͂̐���
		m_pLife = CLife::Create();

		// �̗͂̏���������
		if (m_pLife == NULL)
		{// ���s��

			// ���s���b�Z�[�W
			MessageBox(hWnd, "�̗͂̐���", "�����������s�I", MB_ICONWARNING);

			// �������𔲂���
			return E_FAIL;
		}
	}

	// �퓬�v���C���[�̏�����
	{
		// �퓬�v���C���[�̗L���𔻒�
		if (m_pPlayerBattle != NULL)
		{
			// �����𔲂���
			return E_FAIL;
		}

		// �퓬�v���C���[�̐���
		m_pPlayerBattle = CPlayerBattle::Create(
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),			// �ʒu
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),			// ����
			CObjectModel::MODEL_TYPE_PLAYER_BATTLE,	// ���f��
			CMotion::MOTION_TYPE_PLAYER_BATTLE);	// ���[�V����

		// �퓬�v���C���[�̏���������
		if (m_pPlayerBattle == NULL)
		{// ���s��

		 // ���s���b�Z�[�W
			MessageBox(hWnd, "�퓬�v���C���[�̐���", "�����������s�I", MB_ICONWARNING);

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
			m_pUiMission = CUiMission::Create(CUiMission::TEX_BATTLE_NORMAL);

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
				D3DXVECTOR3(SCREEN_WIDTH * 0.925f, SCREEN_HEIGHT * 0.3f, 0.0f),
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

	// ���ʂȂ��I�u�W�F�N�g�ǂݍ��ݐݒ菈��
	CFileObjNone::Load(CFileObjNone::TXT_NORMAL_000);

	// �C�x���g�I�u�W�F�N�g�ǂݍ��ݐݒ菈��
	CFileEvtObj::Load(CFileEvtObj::TXT_NORMAL_000);

	// �ʏ�G�̓ǂݍ��ݐݒ菈��
	CFileEmyNor::Load(CFileEmyNor::TXT_NORMAL_000);

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
//- �퓬�t�F�[�Y�̏I������
//-------------------------------------
void CSysPhaseBattle::Uninit(void)
{
	// �V�X�e���I�u�W�F�N�g�Ǘ��̎擾����
	CMgrSysObj *pMgrSysObj = CGame::GetMgrSysObj();

	//  �V�X�e���I�u�W�F�N�g�Ǘ��̎擾�̗L���𔻒�
	if (pMgrSysObj != NULL)
	{
		// �����̃|�C���^����������
		pMgrSysObj->NullAllNumber();
	}

	// �̗̗͂L���𔻒�
	if (m_pLife != NULL)
	{
		// �̗͂̏I������
		m_pLife->Uninit();

		// �̗͂̃|�C���^����������
		delete m_pLife;
		m_pLife = NULL;
	}

	// �퓬�v���C���[�̗L���𔻒�
	if (m_pPlayerBattle != NULL)
	{
		// �퓬�v���C���[�̏I������
		m_pPlayerBattle->Uninit();

		// �퓬�v���C���[�̃|�C���^����������
		m_pPlayerBattle = NULL;
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
//- �퓬�t�F�[�Y�̍X�V����
//-------------------------------------
void CSysPhaseBattle::Update(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

		// �����𔲂���
		return;
	}

	// �Q�[���X�e�[�^�X�̃|�C���^��錾
	CStateGame *pStateGame = CGame::GetStateGame();

	// �Q�[���X�e�[�^�X�̏��擾�̐����𔻒�
	if (pStateGame == NULL)
	{// ���s��

		// �����𔲂���
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

	// �{�X�̃|�C���^���擾
	CEnemyBoss *pEnemyBoss = m_pManagerObject->GetEnemyBoss();

	// �ϐ��錾�i�Q�[���X�e�[�^�X�̏��擾�j
	int nEnemyDeathCut = pStateGame->m_nDataEnemyDeathCut.Get();		// �G�̎��S���J�E���g
	int nEnemyDeathTarget = pStateGame->m_nDataEnemyDeathTarget.Get();	// �G�̖ڕW���S���J�E���g

	// �{�X�̏o������
	if (nEnemyDeathCut >= nEnemyDeathTarget && pEnemyBoss == NULL && pStateGame->GetEndState() == CStateGame::END_STATE_NONE)
	{
		// �ڕWUI�̐؂�ւ�
		m_pUiMission->BindTexture(m_pUiMission->GetTexNldx(CUiMission::TEX_BATTLE_BOSS));

		// �{�X�̐�������
		CEnemyBoss *pEnemyBoss = CEnemyBoss::Create(CEnemy::MODEL_TYPE_ALIEN_001);

		// �{�X�̐����̗L���𔻒�
		if (pEnemyBoss != NULL)
		{
			m_pManagerObject->SetEnemyBoss(pEnemyBoss);
		}
	}

	// �̗̗͂L���𔻒�
	if (m_pLife != NULL)
	{
		// �̗͂̍X�V����
		m_pLife->Update();
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
	}

	// ���X�V�i�G�t�F�N�g2D�j
	m_dataEffectCut.Set(nEffectCut);

#if _DEBUG
	//�@���͂̔��� if�iC�L�[�̃g���K�[�j
	if (pInputKeyboard->GetTrigger(DIK_C) != NULL)
	{
		CGame::SetPhase(TYPE::TYPE_SEARCH);
	}
#endif

	// �t�F�[�Y��Ԃ̔���
	if (CSysGamePhase::GetType() != CSysGamePhase::GetTypeNext())
	{
		// �t�F�[�Y�̐؂�ւ�
		CGame::SetPhase(CSysGamePhase::GetTypeNext());

		return;
	}
}

//-------------------------------------
//- �퓬�t�F�[�Y�̕`�揈��
//-------------------------------------
void CSysPhaseBattle::Draw(void)
{

}

//-------------------------------------
//-	�퓬�v���C���[�̏����擾
//-------------------------------------
CPlayer *CSysPhaseBattle::GetPlayer(void)
{
	// �T���v���C���[�̏���Ԃ�
	return m_pPlayerBattle;
}

//-------------------------------------
//- �퓬�t�F�[�Y�̃I�u�W�F�N�g�Ǘ��̎擾����
//-------------------------------------
CManagerObject * CSysPhaseBattle::GetManagerObject(void)
{
	return m_pManagerObject;
}

//-------------------------------------
//- �퓬�t�F�[�Y�̗̑͂̎擾����
//-------------------------------------
CLife * CSysPhaseBattle::GetLife(void)
{
	return m_pLife;
}

//-------------------------------------
//-	�퓬�t�F�[�Y�̖ړIUI�̏����擾
//-------------------------------------
CUiMission *CSysPhaseBattle::GetUiMission(void)
{
	// �ړIUI�̏���Ԃ�
	return m_pUiMission;
}

//-------------------------------------
//-	���ʂȂ�2D�̏����擾
//-------------------------------------
CObj2dNone * CSysPhaseBattle::GetObj2DNone(void)
{
	return m_pObj2dNone;
}
