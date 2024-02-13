
//-===============================================
//-
//-	�T���v���C���[����[player_search.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "player_search.h"

#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "time_stop.h"
#include "sys_game_phase.h"
#include "sys_phase_search.h"
#include "manager_object.h"

#include "Input.h"
#include "xinput.h"
#include "sound.h"
#include "debugproc.h"

#include "mgr_sys_obj.h"
#include "score.h"

#include "event_object.h"
#include "garbage.h"
#include "garbage_collect.h"

#include "gate.h"

#include "effect_object.h"

#include "ui_opr_desc.h"
#include "ui_text_desc.h"

#include "hit.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CPlayerSearch::CPlayerSearch()
{
	// �l���N���A
	m_stateType = STATE_TYPE_NEUTRAL;
	m_stateTypeOld = m_stateType;

	m_pUiOprDesc = NULL;
	m_pUiTextDesc = NULL;
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CPlayerSearch::~CPlayerSearch()
{

}

//-------------------------------------
//- �T���v���C���[�̏���������
//-------------------------------------
HRESULT CPlayerSearch::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CObjectModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax)
{
	// �v���C���[�̐ݒ菈��
	Set(pos,rot);

	// �v���C���[�̏���������
	CPlayer::Init(modelType, motionType,nStateMax);

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �T���v���C���[�̏I������
//-------------------------------------
void CPlayerSearch::Uninit(void)
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
//- �T���v���C���[�̍X�V����
//-------------------------------------
void CPlayerSearch::Update(void)
{
	// �X�R�A�̏��擾����
	CScore *pScore = CGame::GetMgrSysObj()->GetScore();

	// �X�R�A�̏��擾�̐����𔻒�
	if (pScore == NULL)
	{// ���s��

	 // �����𔲂���
		return;
	}

	// ���ݒ�i�O��̏��j
	m_dataPosOld.Set(m_dataPos.Get());	// �ʒu
	m_stateTypeOld = m_stateType;		// ���

	// �Q�[�����[�h�̔���
	if (CGame::GetSysGamePhase()->GetType() == CSysGamePhase::TYPE_SEARCH)
	{
		if (m_stateType != STATE_TYPE_TOUCH &&
			m_stateType != STATE_TYPE_EAT)
		{
			// �v���C���[�̍X�V����
  			CPlayer::Update();
		}

		// �C�x���g�̍X�V����
		UpdateEvent();

		// ���[�V�����̍X�V����
		UpdateMotion();
	}
}

//-------------------------------------
//- �T���v���C���[�̕`�揈��
//-------------------------------------
void CPlayerSearch::Draw(void)
{
	// �v���C���[�̕`�揈��
	CPlayer::Draw();
}

//-------------------------------------
//- �T���v���C���[�̐�������
//-------------------------------------
CPlayerSearch * CPlayerSearch::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CObjectModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType)
{
	// �T���v���C���[�̃|�C���^��錾
	CPlayerSearch *pCPlayerSearch = new CPlayerSearch;

	// �����̐����̗L���𔻒�
	if (pCPlayerSearch != NULL)
	{
		// ����������
		if (FAILED(pCPlayerSearch->Init(pos, rot, modelType, motionType,STATE_TYPE_MAX)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCPlayerSearch == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// ��ނ�ݒ�
	pCPlayerSearch->SetType(TYPE_PLAYER);

	// �T���v���C���[�̃|�C���^��Ԃ�
	return pCPlayerSearch;
}

//-------------------------------------
//- �T���v���C���[�̐ݒ菈��
//-------------------------------------
void CPlayerSearch::Set(D3DXVECTOR3 pos,  D3DXVECTOR3 rot)
{
	// ���X�V
	m_dataPos.Set(pos);		// �ʒu
	m_dataPosOld.Set(pos);	// �O��̈ʒu

	m_dataSize.Set(D3DXVECTOR3(50.0f,50.0f,50.0f));	// �傫��

	m_dataRot.Set(rot);		// �ړ���
	m_dataRotDest.Set(rot);	// �ړI�̌���
}

//-------------------------------------
//- �T���v���C���[�̃C�x���g�̍X�V����
//-------------------------------------
void CPlayerSearch::UpdateEvent(void)
{
	// ���ԊǗ��̏����擾
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// ���ԊǗ��擾�̗L���𔻒�
	if (pManagerTime == NULL)
	{
		// �����𔲂���
		return;
	}

	// �ϐ��錾�i���擾�j
	int nStateTime = m_nDataStateTime.Get();	// ��Ԏ���
	int nStateCount = m_nDataStateCount.Get();	// ��ԃJ�E���g

	// ��Ԃ̔���
	if (m_stateType == STATE_TYPE_TOUCH ||
		m_stateType == STATE_TYPE_EAT)
	{
		// �����J�E���g�̗L���𔻒�
		if (pManagerTime->m_bDataIntCount.Get() == true)
		{
			// �G��J�E���g�����Z
			nStateCount++;
		}

		// �G��J�E���g�𔻒�
		if (nStateCount >= nStateTime)
		{
			// �G��J�E���g��������
			nStateCount = 0;

			// ��Ԃ�ʏ�ɕύX
			m_stateType = STATE_TYPE_NEUTRAL;
		}

		// ���X�V
		m_nDataStateTime.Set(nStateTime);	// ��Ԏ���
		m_nDataStateCount.Set(nStateCount);	// ��ԃJ�E���g
	}
	else
	{
		// �C�x���g�Ƃ̓����蔻��
		CollisionEvent();
	}
}

//-------------------------------------
//- �T���v���C���[�̃C�x���g�Ƃ̓����蔻�菈��
//-------------------------------------
void CPlayerSearch::CollisionEvent(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();		// �ʒu
	D3DXVECTOR3 size = m_dataSize.Get();	// �傫��

	// �ϐ��錾
	bool bCol = false;	// �����蔻��̗L��

	for (int nCutEventObject = 0; nCutEventObject < EVENT_OBJECT_NUM_MAX; nCutEventObject++)
	{
		// �C�x���g�I�u�W�F�N�g�̏����擾
		CEventObject *pEventObject = CManagerObject::GetEventObject(nCutEventObject);

		// �C�x���g�I�u�W�F�N�g�̗L���𔻒�
		if (pEventObject != NULL)
		{
			// �ϐ��錾�i���擾�j
			D3DXVECTOR3 eventObjectPos = pEventObject->m_dataPos.Get();		// �ʒu
			D3DXVECTOR3 eventObjectSize = pEventObject->m_dataSize.Get();	// �傫��
			D3DXVECTOR3 colSizeAdd = D3DXVECTOR3(10.0f, 0.0f, 10.0f);	// �ǉ��̓����蔻��̑傫��
			bool bEventObjectUse = pEventObject->m_bDataUse.Get();			// �g�p�̗L��

			// �I�u�W�F�N�g�C�x���g���g�p�\
			if (bEventObjectUse == false)
			{
				if (CHit::hitRectangle(pos, size, eventObjectPos, eventObjectSize + colSizeAdd) == true)
				{
					// �C�x���g�A�N�V��������
					InputEventAction(pEventObject);

					// �������UI�̗L���𔻒�
					if (m_pUiOprDesc == NULL)
					{
						// �������UI�𐶐�
						m_pUiOprDesc = CUiOprDesc::Create(CUiOprDesc::TEX_SPACE);

						// �������UI�̐ݒ菈��
						m_pUiOprDesc->Set(
							D3DXVECTOR3(SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT * 0.9f, 0.0f),
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
							D3DXVECTOR3(SCREEN_WIDTH * 0.12f, SCREEN_HEIGHT * 0.825f, 0.0f),
							D3DXVECTOR3(90.0f, 40.0f, 0.0f),
							D3DXVECTOR3(5.0f, 5.0f, 0.0f),
							D3DXVECTOR3(0.5f, 0.5f, 0.0f)
						);
					}

					// �����蔻�肪���݂���
					bCol = true;
				}
			}
		}
	}

	for (int nCutGarbage = 0; nCutGarbage < GARBAGE_NUM_MAX; nCutGarbage++)
	{
		// �S�~�̏����擾
		CGarbage *pGarbage = CManagerObject::GetGarbage(nCutGarbage);

		// �S�~�̗L���𔻒�
		if (pGarbage != NULL)
		{
			// �ϐ��錾�i���擾�j
			D3DXVECTOR3 grabagePos = pGarbage->m_dataPos.Get();			// �ʒu
			D3DXVECTOR3 grabageSize = pGarbage->m_dataSize.Get();		// �傫��
			D3DXVECTOR3 colSizeAdd = D3DXVECTOR3(10.0f, 0.0f, 10.0f);	// �ǉ��̓����蔻��̑傫��
			bool bEat = pGarbage->m_bDataEat.Get();

			// ��`�����蔻�� && �H�ׂĂȂ�
			if (CHit::hitRectangle(pos, size, grabagePos, grabageSize + colSizeAdd) == true &&
				bEat == false)
			{
				// �S�~�A�N�V��������
				InputGarbageAction(pGarbage, nCutGarbage);

				// �������UI�̗L���𔻒�
				if (m_pUiOprDesc == NULL)
				{
					// �������UI�𐶐�
					m_pUiOprDesc = CUiOprDesc::Create(CUiOprDesc::TEX_SPACE);

					// �������UI�̐ݒ菈��
					m_pUiOprDesc->Set(
						D3DXVECTOR3(SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT * 0.9f, 0.0f),
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
						D3DXVECTOR3(SCREEN_WIDTH * 0.12f, SCREEN_HEIGHT * 0.825f, 0.0f),
						D3DXVECTOR3(90.0f, 40.0f, 0.0f),
						D3DXVECTOR3(5.0f, 5.0f, 0.0f),
						D3DXVECTOR3(0.5f, 0.5f, 0.0f)
					);
				}

				// �����蔻�肪���݂���
				bCol = true;
			}
		}
	}

	// �Q�[�g�̏����擾
	CGate *pGate = CManagerObject::GetGate();

	// �Q�[�g�̗L���𔻒�
	if (pGate != NULL)
	{
		// �ϐ��錾�i���擾�j
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
					D3DXVECTOR3(SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT * 0.9f, 0.0f),
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
					D3DXVECTOR3(SCREEN_WIDTH * 0.12f, SCREEN_HEIGHT * 0.825f, 0.0f),
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
//- �T���v���C���[�̃C�x���g�A�N�V��������
//-------------------------------------
void CPlayerSearch::InputEventAction(CEventObject *pEventObject)
{
	// �L�[�{�[�h�̏��擾����
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

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

	// �X�R�A�̏��擾����
	CScore *pScore = CGame::GetMgrSysObj()->GetScore();

	// �X�R�A�̏��擾�̐����𔻒�
	if (pScore == NULL)
	{// ���s��

		// �����𔲂���
		return;
	}

	// ���͂̔���
	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true ||
		pXInput->GetTrigger(XINPUT_GAMEPAD_A, CXInput::TYPE_INPUT_BUTTON))
	{// SPACE�L�[

		// �N�C�b�N�^�C���C�x���g�̐ݒ�
		CSysPhaseSearch::SetQte(CQte::TYPE_QTE_TIMING);

		// �v���C���[�̏�Ԃ�G��ɕύX
		m_stateType = STATE_TYPE_TOUCH;

		// ��Ԏ��Ԃ���
		m_nDataStateTime.Set(90);

		// �C�x���g�I�u�W�F�N�g�̎��s����
		pEventObject->Execution();
	}
}

//-------------------------------------
//- �T���v���C���[�̃S�~�̃A�N�V��������
//-------------------------------------
void CPlayerSearch::InputGarbageAction(CGarbage *pGarbage, int nNum)
{
	// �L�[�{�[�h�̏��擾����
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

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
		pXInput->GetTrigger(XINPUT_GAMEPAD_A, CXInput::TYPE_INPUT_BUTTON))
	{// SPACE�L�[

		// �v���C���[�̏�Ԃ�H�ׂ�ɕύX
		m_stateType = STATE_TYPE_EAT;

		// ��Ԏ��Ԃ���
		m_nDataStateTime.Set(60);

		// �I�u�W�F�N�g�Ǘ��̃|�C���^��������
		CManagerObject::ReleaseGarbage(nNum);

		// �C�x���g�I�u�W�F�N�g�̎��s����
		pGarbage->Execution(60);
	}
}

//-------------------------------------
//- �T���v���C���[�̃Q�[�g�̃A�N�V��������
//-------------------------------------
void CPlayerSearch::InputGateAction(CGate *pGate)
{
	// �L�[�{�[�h�̏��擾����
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

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
		pXInput->GetTrigger(XINPUT_GAMEPAD_A, CXInput::TYPE_INPUT_BUTTON))
	{// SPACE�L�[

		// �v���C���[�̏�Ԃ�G��ɕύX
		m_stateType = STATE_TYPE_TOUCH;

		// �C�x���g�I�u�W�F�N�g�̎��s����
		pGate->Execution();

		// ���̃t�F�[�Y�̑���i�퓬�j
		CSysGamePhase::SetTypeNext(CSysGamePhase::TYPE_BATTLE);

		return;
	}
}

//-------------------------------------
//- �T���v���C���[�̃��[�V�����X�V����
//-------------------------------------
void CPlayerSearch::UpdateMotion(void)
{
	// �ϐ��錾
	CMotion *pMotion = GetMotion();			// ���[�V���������擾
	D3DXVECTOR3 move = m_dataMove.Get();	// �ړ��ʂ��擾

	if (m_stateType != STATE_TYPE_TOUCH &&
		m_stateType != STATE_TYPE_EAT)
	{
		// �ړ��ʂŏ�Ԃ�ύX
		if (move.x >= 0.3f ||
			move.x <= -0.3f ||
			move.z >= 0.3f ||
			move.z <= -0.3f)
		{
			m_stateType = STATE_TYPE_MOVE;
		}
		else
		{
			m_stateType = STATE_TYPE_NEUTRAL;
		}
	}

	// ���[�V�����̏I���󋵂𔻒�
	if (pMotion->IsFinsih() == true)
	{
		// ���[�V�����̍X�V
		pMotion->Update();
	}

	// ���[�V�����̐ݒ菈��
	if (m_stateType != m_stateTypeOld)
	{
		// ��Ԃ̔���
		switch (m_stateType)
		{
		case STATE_TYPE_NEUTRAL:

			// �ҋ@���[�V�����̐ݒ�
			pMotion->Set(STATE_TYPE_NEUTRAL);

			break;

		case STATE_TYPE_MOVE:

			// �ړ����[�V�����̐ݒ�
			pMotion->Set(STATE_TYPE_MOVE);

			break;

		case STATE_TYPE_TOUCH:

			// �G�郂�[�V�����̐ݒ�
			pMotion->Set(STATE_TYPE_TOUCH);

			break;

		case STATE_TYPE_EAT:

			// �G�郂�[�V�����̐ݒ�
			pMotion->Set(STATE_TYPE_EAT);

			break;
		}
	}
}