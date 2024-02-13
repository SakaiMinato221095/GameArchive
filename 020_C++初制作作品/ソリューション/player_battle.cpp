
//-===============================================
//-
//-	�퓬�v���C���[����[player_battle.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "player_battle.h"

#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "sys_game_phase.h"
#include "sys_phase_battle.h"

#include "Input.h"
#include "xinput.h"
#include "sound.h"
#include "debugproc.h"

#include "state_battle.h"
#include "life.h"

#include "bullet.h"
#include "bullet_bomb.h"
#include "chaos_attack.h"

#include "effect.h"

#include "time_stop.h"

#include "hit.h"

#include "manager_object.h"
#include "gate.h"

#include "ui_opr_desc.h"
#include "ui_text_desc.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CPlayerBattle::CPlayerBattle()
{
	// �l���N���A
	m_stateType = STATE_TYPE_NEUTRAL;
	m_stateTypeNew = m_stateType;

	m_pUiOprDesc = NULL;
	m_pUiTextDesc = NULL;

	m_pChaosAttack = NULL;
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CPlayerBattle::~CPlayerBattle()
{

}

//-------------------------------------
//- �퓬�v���C���[�̏���������
//-------------------------------------
HRESULT CPlayerBattle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CObjectModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax)
{
	// �퓬�v���C���[�̐ݒ菈��
	Set(pos,rot);

	// �v���C���[�̏���������
	CPlayer::Init(modelType, motionType,STATE_TYPE_MAX);

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �퓬�v���C���[�̏I������
//-------------------------------------
void CPlayerBattle::Uninit(void)
{
	if (m_pUiOprDesc != NULL)
	{
		// ����UI�̏I������
		m_pUiOprDesc->Uninit();
		m_pUiOprDesc = NULL;
	}

	if (m_pUiTextDesc != NULL)
	{
		// ������UI�̏I������
		m_pUiTextDesc->Uninit();
		m_pUiTextDesc = NULL;
	}

	// �v���C���[�̏I������
	CPlayer::Uninit();
}

//-------------------------------------
//- �퓬�v���C���[�̍X�V����
//-------------------------------------
void CPlayerBattle::Update(void)
{
	// ���ݒ�i�O��̏��j
	m_dataPosOld.Set(m_dataPos.Get());		// �ʒu
	int nCollTime = m_nDataCoolTime.Get();	// �N�[���^�C��

	if (nCollTime > 0)
	{
		nCollTime--;

		m_nDataCoolTime.Set(nCollTime);
	}
	else
	{
		// �v���C���[�̍X�V����
		CPlayer::Update();
	}


	// �U���̓��͏���
	InputAttack();

	// �Q�[�g�Ƃ̓����蔻��
	ColGate();

	// �U���̍X�V����
	UpdateAttack();

	// ���[�V�����̍X�V����
	UpdateMotion();
}

//-------------------------------------
//- �퓬�v���C���[�̕`�揈��
//-------------------------------------
void CPlayerBattle::Draw(void)
{
	// �v���C���[�̕`�揈��
	CPlayer::Draw();
}

//-------------------------------------
//- �퓬�v���C���[�̐�������
//-------------------------------------
CPlayerBattle *CPlayerBattle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CObjectModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType)
{
	// �퓬�v���C���[�̃|�C���^��錾
	CPlayerBattle *pCPlayerBattle = new CPlayerBattle;

	// �����̐����̗L���𔻒�
	if (pCPlayerBattle != NULL)
	{
		// ����������
		if (FAILED(pCPlayerBattle->Init(pos, rot,modelType,motionType,STATE_TYPE_MAX)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCPlayerBattle == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// ��ނ�ݒ�
	pCPlayerBattle->SetType(TYPE_PLAYER);

	// �퓬�v���C���[�̃|�C���^��Ԃ�
	return pCPlayerBattle;
}

//-------------------------------------
//- �퓬�v���C���[�̐ݒ菈��
//-------------------------------------
void CPlayerBattle::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���X�V
	m_dataPos.Set(pos);		// �ʒu
	m_dataPosOld.Set(pos);	// �O��̈ʒu

	m_dataSize.Set(D3DXVECTOR3(50.0f, 50.0f, 50.0f));	// �傫��

	m_dataRot.Set(rot);			// �ړ���
	m_dataRotDest.Set(rot);		// �ړI�̌���

	m_nDataChargeMax.Set(60);	// �`���[�W�̍ő吔��ݒ�
}

//-------------------------------------
//- �퓬�v���C���[�̃Q�[�g�Ƃ̓����蔻�菈��
//-------------------------------------
void CPlayerBattle::ColGate(void)
{
	// �ϐ��錾
	bool bCol = false;	// �����蔻��̗L��

	// �Q�[�g�̏����擾
	CGate *pGate = CManagerObject::GetGate();

	// �Q�[�g�̗L���𔻒�
	if (pGate != NULL)
	{
		// �ϐ��錾�i���擾�j
		D3DXVECTOR3 pos = m_dataPos.Get();		// �ʒu
		D3DXVECTOR3 size = m_dataSize.Get();	// �傫��

		// �ϐ��錾�i�I�u�W�F�N�g�̏��擾�j
		D3DXVECTOR3 pGatePos = pGate->m_dataPos.Get();				// �ʒu
		D3DXVECTOR3 pGateSize = pGate->m_dataSize.Get();			// �傫��
		D3DXVECTOR3 colSizeAdd = D3DXVECTOR3(10.0f, 0.0f, 10.0f);	// �ǉ��̓����蔻��̑傫��

		if (CHit::hitRectangle(pos, size, pGatePos, pGateSize + colSizeAdd) == true)
		{
			// �Q�[�g�A�N�V��������
			InputGateAction(pGate);

			// �������UI�̗L���𔻒�
			if (m_pUiOprDesc == NULL)
			{
				// �������UI�𐶐�
				m_pUiOprDesc = CUiOprDesc::Create(CUiOprDesc::TEX_SPACE);

				// �������UI�̐ݒ菈��
				m_pUiOprDesc->Set(
					D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.7f, 0.0f),
					D3DXVECTOR3(100.0f, 50.0f, 0.0f),
					D3DXVECTOR3(5.0f, 5.0f, 0.0f),
					D3DXVECTOR3(0.5f, 0.5f, 0.0f)
				);
			}

			// ���������UI�̗L���𔻒�
			if (m_pUiTextDesc == NULL)
			{
				// ���������UI�𐶐�
				m_pUiTextDesc = CUiTextDesc::Create(CUiTextDesc::TEX_PUSH);

				// ���������UI�̐ݒ菈��
				m_pUiTextDesc->Set(
					D3DXVECTOR3(SCREEN_WIDTH * 0.47f, SCREEN_HEIGHT * 0.625f, 0.0f),
					D3DXVECTOR3(90.0f, 40.0f, 0.0f),
					D3DXVECTOR3(5.0f, 5.0f, 0.0f),
					D3DXVECTOR3(0.5f, 0.5f, 0.0f)
				);
			}

			// �����蔻�肪���݂���
			bCol = true;
		}
	}

	if (bCol == false)
	{
		if (m_pUiOprDesc != NULL)
		{
			// ����UI�̏I������
			m_pUiOprDesc->Uninit();
			m_pUiOprDesc = NULL;
		}

		if (m_pUiTextDesc != NULL)
		{
			// ������UI�̏I������
			m_pUiTextDesc->Uninit();
			m_pUiTextDesc = NULL;
		}
	}
}
//-------------------------------------
//- �퓬�v���C���[�̃_���[�W����
//-------------------------------------
void CPlayerBattle::Hit(int nDamage)
{
	// �̗͂̎擾����
	CLife *pSysPhaseBattle = CSysPhaseBattle::GetLife();

	// �̗͎擾�����̗L���𔻒�
	if (pSysPhaseBattle == NULL)
	{
		return;
	}

	// �T�E���h�̃|�C���^��錾
	CSound *pSound = CManager::GetSound();

	// �T�E���h�̏��擾�̐����𔻒�
	if (pSound == NULL)
	{
		// �����𔲂���
		return;
	}

	// �ϐ��錾�i�̗͂̏��j
	int nLife = pSysPhaseBattle->m_nDataLife.Get();	// �̗͒l

	// �̗͂̔���
	if (nLife <= 0)
	{
		// ��Ԃ�ύX
		m_stateTypeNew = STATE_TYPE_DEAD;
	}
	else
	{
		// ���ʉ�BGM�̍Đ��i�ł̍U��000�j
		pSound->Play(CSound::LABEL_SE_DAMAGE_PLAYER);

		// �̗͂̌��Z
		nLife -= nDamage;

		// ��Ԃ�ύX
		m_stateTypeNew = STATE_TYPE_DAMAGE;
	}

	// ���X�V�i�̗͂̏��j
	pSysPhaseBattle->m_nDataLife.Set(nLife);	// �̗͒l
}

//-------------------------------------
//- �퓬�v���C���[�̍U������
//-------------------------------------
void CPlayerBattle::InputAttack(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{
		// �����𔲂���
		return;
	}

	// X���͂̃|�C���^��錾
	CXInput *pXInput = CManager::GetXInput();

	// X���͂̏��擾�̐����𔻒�
	if (pXInput == NULL)
	{
		// �����𔲂���
		return;
	}

	// �퓬�X�e�[�^�X�̃|�C���^��錾
	CStateBattle *pStateBattle = CGame::GetStateBattle();

	// �퓬�X�e�[�^�X�̏��擾�̐����𔻒�
	if (pStateBattle == NULL)
	{
		// �����𔲂���
		return;
	}

	// ���ԊǗ��̏����擾
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// ���ԊǗ��擾�̗L���𔻒�
	if (pManagerTime == NULL)
	{
		// �����𔲂���
		return;
	}

	// �ϐ��錾�i���̎擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();								// �ʒu���
	D3DXVECTOR3 rot = m_dataRot.Get();								// �������

	bool bShot = bDataShot.Get();									// �ˌ��̗L��
	bool bShotAgain = bDataShotAgain.Get();							// �Ďˌ����
	int nShotIntervalCount = nDataShotIntervalCount.Get();			// �e�̊Ԋu�J�E���g
	int nShotInterval = pStateBattle->m_nDataShotInterval.Get();	// �e�̊Ԋu
	int nSubWeponNum = pStateBattle->m_nSubWeaponNum.Get();			// �T�u����̎g�p��
	int nChargeCut = m_nDataChargeCut.Get();						// �`���[�W�J�E���g
	bool bCharge = m_bDataCharge.Get();								// �`���[�W�̗L��

	// �ϐ��錾�i�퓬�X�e�[�^�X�̏��擾�j
	CStateBattle::ELEM_TYPE elemType = pStateBattle->GetElemType();

	// �e�Ԋu�̔���
	if (nShotIntervalCount >= nShotInterval)
	{
		// ���͂̔���
		if (pInputKeyboard->GetTrigger(DIK_SPACE) == true || 
			pXInput->GetTrigger(XINPUT_GAMEPAD_A,CXInput::TYPE_INPUT_BUTTON) == true)
		{// SPACE�L�[

			// �ړ���~
			m_bDataStopMove.Set(true);

			if (elemType == CStateBattle::ELEM_TYPE_CHAOS)
			{
				// �ړ���~
				m_bDataStopMoveRot.Set(true);
			}

			// �e�̊Ԋu�J�E���g��������
			nShotIntervalCount = 0;

			// �`���[�W��������
			nChargeCut = 0;

			// ��Ԃ̔���
			if (m_stateTypeNew != STATE_TYPE_ATTACK)
			{
				// ��Ԃ�ݒ�
				m_stateTypeNew = STATE_TYPE_ATTACK;

				// �ˌ���ԂɕύX
				bShot = true;

				// �`���[�W��ԂɕύX
				bCharge = true;
			}
			else
			{
				// �Ďˌ��̗L��
				bShotAgain = true;

				// �`���[�W��ԂɕύX
				bCharge = true;
			}

		}
	}
	else
	{
		if (pManagerTime->m_bDataIntCount.Get() == true)
		{
			// �e�̊Ԋu�J�E���g�����Z
			nShotIntervalCount++;
		}
	}

	if (elemType == CStateBattle::ELEM_TYPE_CHAOS)
	{
		if (m_pChaosAttack != NULL &&
			bCharge == false)
		{
			// �ł̍U���̏I������
			m_pChaosAttack->Uninit();
			m_pChaosAttack = NULL;
		}
	}

	if (nSubWeponNum > 0)
	{
		// ���͂̔���
		if (pInputKeyboard->GetTrigger(DIK_J) == true)
		{// K�L�[

			// �e�̃|�C���^��錾
			CBulletBomb *pBullet = pBullet->Create(CBulletBomb::TEX_BLUE_000);

			// �T�u����̎g�p�񐔂����Z
			nSubWeponNum--;

			// �ʒu����ݒ�
			pBullet->m_dataPos.Set(pos);

			// �傫����ݒ�
			pBullet->m_dataSize.Set(D3DXVECTOR3(100.0f, 100.0f, 0.0f));

			// �ړ��ʂ�ݒ�
			pBullet->m_dataMove.Set(D3DXVECTOR3(sinf(rot.y) * -10.0f, 0.0f, cosf(rot.y) * -10.0f));

			// �̗͂̐ݒ�
			pBullet->m_nDataLife.Set(120);

			// �_���[�W�̐ݒ�
			pBullet->m_nDataDamage.Set(10);

			// ��Ԃ�ݒ�
			m_stateTypeNew = STATE_TYPE_ATTACK;
		}
	}

	// ���X�V
	bDataShot.Set(bShot);								// �ˌ��̗L��
	bDataShotAgain.Set(bShotAgain);						// �Ďˌ��̗L��
	nDataShotIntervalCount.Set(nShotIntervalCount);		// �e�̊Ԋu�J�E���g
	pStateBattle->m_nSubWeaponNum.Set(nSubWeponNum);	// �T�u����̎g�p��
	m_bDataCharge.Set(bCharge);							// �`���[�W�̗L��
	m_nDataChargeCut.Set(nChargeCut);					// �`���[�W�J�E���g
}

//-------------------------------------
//- �퓬�v���C���[�̃Q�[�g�̃A�N�V��������
//-------------------------------------
void CPlayerBattle::InputGateAction(CGate *pGate)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{
		// �����𔲂���
		return;
	}

	// X���͂̃|�C���^��錾
	CXInput *pXInput = CManager::GetXInput();

	// X���͂̏��擾�̐����𔻒�
	if (pXInput == NULL)
	{
		// �����𔲂���
		return;
	}

	// ���͂̔���
	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true || 
		pXInput->GetTrigger(XINPUT_GAMEPAD_A,CXInput::TYPE_INPUT_BUTTON))
	{// SPACE�L�[

		// �C�x���g�I�u�W�F�N�g�̎��s����
		pGate->Execution();

		// ���̃t�F�[�Y�̑���i�퓬�j
		CSysGamePhase::SetTypeNext(CSysGamePhase::TYPE_SEARCH);

		return;
	}
}

//-------------------------------------
//- �퓬�v���C���[�̍U���̍X�V����
//-------------------------------------
void CPlayerBattle::UpdateAttack(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{
		// �����𔲂���
		return;
	}

	// X���͂̃|�C���^��錾
	CXInput *pXInput = CManager::GetXInput();

	// X���͂̏��擾�̐����𔻒�
	if (pXInput == NULL)
	{
		// �����𔲂���
		return;
	}

	// �퓬�X�e�[�^�X�̃|�C���^��錾
	CStateBattle *pStateBattle = CGame::GetStateBattle();

	// �퓬�X�e�[�^�X�̏��擾�̐����𔻒�
	if (pStateBattle == NULL)
	{
		// �����𔲂���
		return;
	}

	// �ϐ��錾�i���擾�j
	int nChargeCut = m_nDataChargeCut.Get();	// �`���[�W�̃J�E���g
	int nChargeMax = m_nDataChargeMax.Get();	// �`���[�W�̍ő�l
	bool bCharge = m_bDataCharge.Get();			// �`���[�W�̗L��

	// �ϐ��錾�i�퓬�X�e�[�^�X�̏��擾�j
	CStateBattle::ELEM_TYPE elemType = pStateBattle->GetElemType();

	// �ϐ��錾
	D3DXVECTOR3 posHead = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �e�̈ʒu�����i�ԍ��x�^�ł�[15]�ԁj
	posHead.x = GetObjectModel(0)->GetMtxWorld()._41;
	posHead.y = GetObjectModel(0)->GetMtxWorld()._42;
	posHead.z = GetObjectModel(0)->GetMtxWorld()._43;

	// ���͂̔���
	if (pInputKeyboard->GetPress(DIK_SPACE) == true ||
		pXInput->GetPress(XINPUT_GAMEPAD_A, CXInput::TYPE_INPUT_BUTTON) == true)
	{// SPACE�L�[

		if (nChargeCut <= nChargeMax)
		{
			// �`���[�W�J�E���g�̉��Z
			nChargeCut++;

			// �G�t�F�N�g�̐���
			CEffect *pEffect = CEffect::Create(CEffect::TEX_NORMAL_000);

			// �G�t�F�N�g�̗L���𔻒�
			if (pEffect != NULL)
			{
				// �ʒu����ݒ�
				pEffect->m_dataPos.Set(posHead);

				// �傫����ݒ�
				pEffect->m_dataSize.Set(D3DXVECTOR3(10.0f, 10.0f, 0.0f));

				// �ړ��ʂ�ݒ�
				pEffect->m_dataMove.Set(D3DXVECTOR3(0.0f, 5.0f, 0.0f));

				// �F��ݒ�
				pEffect->m_dataColor.Set(D3DXCOLOR(0.5f, 0.0f, 0.5f, 1.0f));

				// �G�t�F�N�g�̐ݒ菈��
				pEffect->m_nDataLife.Set(2);
			}
		}
		else
		{
			// �G�t�F�N�g�̐���
			CEffect *pEffect = CEffect::Create(CEffect::TEX_NORMAL_000);

			// �G�t�F�N�g�̗L���𔻒�
			if (pEffect != NULL)
			{
				// �ʒu����ݒ�
				pEffect->m_dataPos.Set(posHead);

				// �傫����ݒ�
				pEffect->m_dataSize.Set(D3DXVECTOR3(30.0f, 30.0f, 0.0f));

				// �ړ��ʂ�ݒ�
				pEffect->m_dataMove.Set(D3DXVECTOR3(0.0f, 5.0f, 0.0f));

				// �F��ݒ�
				pEffect->m_dataColor.Set(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

				// �G�t�F�N�g�̐ݒ菈��
				pEffect->m_nDataLife.Set(2);
			}
		}
	}
	else
	{
		// �`���[�W�̗L����ύX
		bCharge = false;

		// �ړ���~���I��
		m_bDataStopMove.Set(false);

		if (elemType == CStateBattle::ELEM_TYPE_CHAOS)
		{
			// �ړ���~
			m_bDataStopMoveRot.Set(false);
		}
	}

	// ���X�V
	m_nDataChargeCut.Set(nChargeCut);	// �`���[�W�̃J�E���g
	m_nDataChargeMax.Set(nChargeMax);	// �`���[�W�̍ő�l
	m_bDataCharge.Set(bCharge);			// �`���[�W�̗L��
}

//-------------------------------------
//- �퓬�v���C���[�̃��[�V�����X�V����
//-------------------------------------
void CPlayerBattle::UpdateMotion(void)
{
	// ���ԊǗ��̏����擾
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// ���ԊǗ��擾�̗L���𔻒�
	if (pManagerTime == NULL)
	{
		// �����𔲂���
		return;
	}

	// �퓬�X�e�[�^�X�̃|�C���^��錾
	CStateBattle *pStateBattle = CGame::GetStateBattle();

	// �퓬�X�e�[�^�X�̏��擾�̐����𔻒�
	if (pStateBattle == NULL)
	{
		// �����𔲂���
		return;
	}

	// �ϐ��錾�i���擾�j
	bool bShot = bDataShot.Get();				// �ˌ��̗L��
	bool bShotAgain = bDataShotAgain.Get();		// �Ďˌ����
	int nChargeCut = m_nDataChargeCut.Get();	// �`���[�W�̃J�E���g
	int nChargeMax = m_nDataChargeMax.Get();	// �`���[�W�̍ő�l
	bool bCharge = m_bDataCharge.Get();			// �`���[�W�̗L��

	// �ϐ��錾�i�퓬�X�e�[�^�X�̏��擾�j
	CStateBattle::ELEM_TYPE elemType = pStateBattle->GetElemType();

	// �ϐ��錾�i���擾�j
	CMotion *pMotion = GetMotion();			// ���[�V����
	D3DXVECTOR3 move = m_dataMove.Get();	// �ړ���

	// ���Ԕ{���𔻒�
	if (pManagerTime->m_fDataTimeRate.Get() >= 0.5f)
	{
		// ��Ԃ𔻒�
		if (m_stateTypeNew == STATE_TYPE_NEUTRAL ||
			m_stateTypeNew == STATE_TYPE_MOVE)
		{
			// �ړ��ʂŏ�Ԃ�ύX
			if (move.x >= 0.3f ||
				move.x <= -0.3f ||
				move.z >= 0.3f ||
				move.z <= -0.3f)
			{
				// �ړ���ԂɕύX
				m_stateTypeNew = STATE_TYPE_MOVE;
			}
			else
			{
				// �ҋ@��Ԃ̕ύX
				m_stateTypeNew = STATE_TYPE_NEUTRAL;
			}
		}
	}

	// ���[�V�����̏I���󋵂𔻒�
	if (pMotion->IsFinsih() == true)
	{
		// ���[�V�����̍X�V
		pMotion->Update();
	}
	else
	{
		// �ҋ@��Ԃ�ݒ�
		m_stateTypeNew = STATE_TYPE_NEUTRAL;
	}

	// ��Ԃ𔻒�
	if (m_stateType == STATE_TYPE_ATTACK)
	{
		// �ˌ��̗L���ƃL�[�̔���i�ׂ�����[�e��O�ɏo�����Ƃ�]�j
		if (bShot == true &&
			GetMotion()->GetKey() == 1)
		{
			if (bCharge == false)
			{
				// �ʏ�ˌ�
				ShotNor();
				
				// �ˌ���Ԃ�����
				bShot = false;
			}
			else
			{
				switch (elemType)
				{
				case CStateBattle::ELEM_TYPE_NORMAL:

					// ��Ԃ��`���[�W�ɕύX
					m_stateTypeNew = STATE_TYPE_NOR_ATTACK;

					break;

				case CStateBattle::ELEM_TYPE_CHAOS:

					// ��Ԃ��`���[�W�ɕύX
					m_stateTypeNew = STATE_TYPE_CHAOS_ATTACK;

					break;
				}

			}
		}

		// �Ďˌ��̗L���𔻒�
		if (bShotAgain == true &&
			GetMotion()->GetKey() >= 2)
		{
			// �U�����[�V�����̐ݒ�
			pMotion->BlendSet();

			// �ˌ���Ԃ�ݒ�
			bShot = true;

			// �Ďˌ����Ȃ���
			bShotAgain = false;
		}
	}

	// ��Ԃ𔻒�
	if (m_stateType == STATE_TYPE_NOR_ATTACK || 
		m_stateType == STATE_TYPE_CHAOS_ATTACK)
	{
		if (bCharge == false)
		{
			if (nChargeCut >= nChargeMax)
			{
				if (m_stateType == STATE_TYPE_NOR_ATTACK)
				{
					// �ʏ�`���[�W�ˌ�
					ShotNorCharge();
				}
			}
			else
			{
				// �ʏ�ˌ�
				ShotNor();
			}

			// �`���[�W�J�E���g�̏�����
			nChargeCut = 0;

			// �ˌ���Ԃ�����
			bShot = false;

			// �ҋ@��Ԃ�ݒ�
			m_stateTypeNew = STATE_TYPE_NEUTRAL;
		}
		else if (bCharge == true)
		{
			if (nChargeCut >= nChargeMax)
			{
				// �ł̍U��
				ShotChaosCharge();
			}
		}
	}

	// ���[�V�����̐ݒ菈��
	if (m_stateType != m_stateTypeNew)
	{
		// ��Ԃ̍X�V
		m_stateType = m_stateTypeNew;

		// ��Ԃ̔���
		if (m_stateType == STATE_TYPE_NEUTRAL)
		{
			// �ҋ@���[�V�����̐ݒ�
			pMotion->Set(STATE_TYPE_NEUTRAL);

			// �Ďˌ����Ȃ���
			bShotAgain = false;
		}
		else if (m_stateType == STATE_TYPE_MOVE)
		{
			// �ړ����[�V�����̐ݒ�
			pMotion->Set(STATE_TYPE_MOVE);

			// �Ďˌ����Ȃ���
			bShotAgain = false;
		}
		else if (m_stateType == STATE_TYPE_ATTACK)
		{
			// �U�����[�V�����̐ݒ�
			pMotion->Set(STATE_TYPE_ATTACK);
		}
		else if (m_stateType == STATE_TYPE_NOR_ATTACK)
		{
			// �ʏ�U�����[�V�����̐ݒ�
			pMotion->Set(STATE_TYPE_NOR_ATTACK);
		}
		else if (m_stateType == STATE_TYPE_CHAOS_ATTACK)
		{
			// �ł̍U�����[�V�����̐ݒ�
   			pMotion->Set(STATE_TYPE_CHAOS_ATTACK);
		}
		else if (m_stateType == STATE_TYPE_DAMAGE)
		{
			// �_���[�W���[�V�����̐ݒ�
			pMotion->Set(STATE_TYPE_DAMAGE);
		}
		else if (m_stateType == STATE_TYPE_DEAD)
		{
			// ���S���[�V�����̐ݒ�
			pMotion->Set(STATE_TYPE_DEAD);
		}
	}

	// ���X�V
	bDataShot.Set(bShot);				// �ˌ��̗L��
	bDataShotAgain.Set(bShotAgain);		// �Ďˌ��̗L��
	m_nDataChargeCut.Set(nChargeCut);	// �`���[�W�J�E���g
}

//-------------------------------------
//- �퓬�v���C���[�̒ʏ푮���̏e�̔��ˏ���
//-------------------------------------
void CPlayerBattle::ShotNor(void)
{
	// �T�E���h�̃|�C���^��錾
	CSound *pSound = CManager::GetSound();

	// �T�E���h�̏��擾�̐����𔻒�
	if (pSound == NULL)
	{
		// �����𔲂���
		return;
	}

	// �퓬�X�e�[�^�X�̃|�C���^��錾
	CStateBattle *pStateBattle = CGame::GetStateBattle();

	// �퓬�X�e�[�^�X�̏��擾�̐����𔻒�
	if (pStateBattle == NULL)
	{
		// �����𔲂���
		return;
	}

	// ���ԊǗ��̏����擾
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// ���ԊǗ��擾�̗L���𔻒�
	if (pManagerTime == NULL)
	{
		// �����𔲂���
		return;
	}

	// �ϐ��錾�i���̎擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();		// �ʒu���
	D3DXVECTOR3 rot = m_dataRot.Get();		// �������

	// ���[�V�����̃L�[�����擾
	int nKey = GetMotion()->GetKey();

	// �ϐ��錾
	D3DXVECTOR3 posGun = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �e�̈ʒu�����i�ԍ��x�^�ł�[15]�ԁj
	posGun.x = GetObjectModel(15)->GetMtxWorld()._41;
	posGun.y = GetObjectModel(15)->GetMtxWorld()._42;
	posGun.z = GetObjectModel(15)->GetMtxWorld()._43;

	// �e�̐���
	CBullet *pBullet = pBullet->Create(CBullet::TEX_RED_000);

	// �e�̐��������̗L�����擾
	if (pBullet != NULL)
	{
		// �ʒu����ݒ�
		pBullet->m_dataPos.Set(posGun);

		// �傫����ݒ�
		pBullet->m_dataSize.Set(D3DXVECTOR3(10.0f, 10.0f, 0.0f));

		// �ړ��ʂ�ݒ�
		pBullet->m_dataMove.Set(D3DXVECTOR3(sinf(rot.y) * -25.0f, 0.0f, cosf(rot.y) * -25.0f));

		// �̗͂̐ݒ�
		pBullet->m_nDataLife.Set(60);

		// �_���[�W�̐ݒ�
		pBullet->m_nDataDamage.Set(10);

		// ���ˉ�SE�̍Đ�
		pSound->Play(CSound::LABEL_SE_SHOT_000);
	}
}

//-------------------------------------
//- �퓬�v���C���[�̒ʏ푮���̏e�̃`���[�W���ˏ���
//-------------------------------------
void CPlayerBattle::ShotNorCharge(void)
{
	// �T�E���h�̃|�C���^��錾
	CSound *pSound = CManager::GetSound();

	// �T�E���h�̏��擾�̐����𔻒�
	if (pSound == NULL)
	{
		// �����𔲂���
		return;
	}

	// �퓬�X�e�[�^�X�̃|�C���^��錾
	CStateBattle *pStateBattle = CGame::GetStateBattle();

	// �퓬�X�e�[�^�X�̏��擾�̐����𔻒�
	if (pStateBattle == NULL)
	{
		// �����𔲂���
		return;
	}

	// ���ԊǗ��̏����擾
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// ���ԊǗ��擾�̗L���𔻒�
	if (pManagerTime == NULL)
	{
		// �����𔲂���
		return;
	}

	// �ϐ��錾�i���̎擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();		// �ʒu���
	D3DXVECTOR3 rot = m_dataRot.Get();		// �������

	// �ϐ��錾
	D3DXVECTOR3 posGun = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �e�̈ʒu�����i�ԍ��x�^�ł�[15]�ԁj
	posGun.x = GetObjectModel(15)->GetMtxWorld()._41;
	posGun.y = GetObjectModel(15)->GetMtxWorld()._42;
	posGun.z = GetObjectModel(15)->GetMtxWorld()._43;

	// �e�̐���
	CBullet *pBullet = pBullet->Create(CBullet::TEX_RED_000);

	// �e�̐��������̗L�����擾
	if (pBullet != NULL)
	{
		// �ʒu����ݒ�
		pBullet->m_dataPos.Set(posGun);

		// �傫����ݒ�
		pBullet->m_dataSize.Set(D3DXVECTOR3(30.0f, 30.0f, 0.0f));

		// �ړ��ʂ�ݒ�
		pBullet->m_dataMove.Set(D3DXVECTOR3(sinf(rot.y) * -50.0f, 0.0f, cosf(rot.y) * -50.0f));

		// �̗͂̐ݒ�
		pBullet->m_nDataLife.Set(30);

		// �N�[���^�C���̐ݒ�
		m_nDataCoolTime.Set(30);

		// ���擾�i�퓬�X�e�[�^�X�j
		CStateBattle::ELEM_TYPE elemType = pStateBattle->GetElemType();		// �������
		int nElemRank = pStateBattle->m_aDataElemRank[elemType].Get();		// ���������N

		if (nElemRank == 0)
		{
			// �_���[�W�̐ݒ�
			pBullet->m_nDataDamage.Set(25);
		}
		else if (nElemRank == 1)
		{
			// �_���[�W�̐ݒ�
			pBullet->m_nDataDamage.Set(30);
		}
		else if (nElemRank == 2)
		{
			// �_���[�W�̐ݒ�
			pBullet->m_nDataDamage.Set(50);
		}
		else if (nElemRank == 3)
		{
			// �_���[�W�̐ݒ�
			pBullet->m_nDataDamage.Set(100);
		}

		// ���ˉ�SE�̍Đ�
		pSound->Play(CSound::LABEL_SE_NOR_CHARGE_SHOT);
	}
}

//-------------------------------------
//- �퓬�v���C���[�̈ő����̏e�̃`���[�W���ˏ���
//-------------------------------------
void CPlayerBattle::ShotChaosCharge(void)
{
	// �T�E���h�̃|�C���^��錾
	CSound *pSound = CManager::GetSound();

	// �T�E���h�̏��擾�̐����𔻒�
	if (pSound == NULL)
	{
		// �����𔲂���
		return;
	}

	// �퓬�X�e�[�^�X�̃|�C���^��錾
	CStateBattle *pStateBattle = CGame::GetStateBattle();

	// �퓬�X�e�[�^�X�̏��擾�̐����𔻒�
	if (pStateBattle == NULL)
	{
		// �����𔲂���
		return;
	}

	// ���ԊǗ��̏����擾
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// ���ԊǗ��擾�̗L���𔻒�
	if (pManagerTime == NULL)
	{
		// �����𔲂���
		return;
	}

	// �ϐ��錾�i���̎擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();		// �ʒu���
	D3DXVECTOR3 rot = m_dataRot.Get();		// �������

	CMotion *pMotion = GetMotion();			// ���[�V����

	// ���[�V�����̃L�[�����擾
	int nKey = GetMotion()->GetKey();

	// �ϐ��錾
	D3DXVECTOR3 posGun = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �e�̈ʒu�����i�ԍ��x�^�ł�[15]�ԁj
	posGun.x = GetObjectModel(15)->GetMtxWorld()._41;
	posGun.y = GetObjectModel(15)->GetMtxWorld()._42;
	posGun.z = GetObjectModel(15)->GetMtxWorld()._43;

	// ���擾�i�퓬�X�e�[�^�X�j
   	CStateBattle::ELEM_TYPE elemType = pStateBattle->GetElemType();		// �������
	int nElemRank = pStateBattle->m_aDataElemRank[elemType].Get();		// ���������N

	if (m_pChaosAttack == NULL &&
		m_stateType == STATE_TYPE_CHAOS_ATTACK)
	{
		// �ł̍U���̐���
		m_pChaosAttack = CChaosAttack::Create();

		// �ł̍U���̐��������̗L�����擾
		if (m_pChaosAttack != NULL)
		{
			if (nElemRank == 0)
			{
				// �ݒ菈��
				m_pChaosAttack->Set(
					D3DXVECTOR3(pos.x + (sinf(rot.y) * -75.0f), 125.0f, pos.z + (cosf(rot.y) * -75.0f)),
					rot,
					5);
			}
			else if (nElemRank == 1)
			{
				// �ݒ菈��
				m_pChaosAttack->Set(
					D3DXVECTOR3(pos.x + (sinf(rot.y) * -75.0f), 125.0f, pos.z + (cosf(rot.y) * -75.0f)),
					rot,
					7);
			}
			else if (nElemRank == 2)
			{
				// �ݒ菈��
				m_pChaosAttack->Set(
					D3DXVECTOR3(pos.x + (sinf(rot.y) * -75.0f), 125.0f, pos.z + (cosf(rot.y) * -75.0f)),
					rot,
					10);
			}
			else if (nElemRank == 3)
			{
				// �ݒ菈��
				m_pChaosAttack->Set(
					D3DXVECTOR3(pos.x + (sinf(rot.y) * -75.0f), 125.0f, pos.z + (cosf(rot.y) * -75.0f)),
					rot,
					15);
			}


		}
	}

}