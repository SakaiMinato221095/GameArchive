
//-===============================================
//-
//-	�w���v���C���[����[player_shop.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "player_shop.h"

#include "renderer.h"
#include "manager.h"
#include "game.h"

#include "manager_object.h"
#include "sys_game_phase.h"

#include "Input.h"
#include "sound.h"
#include "debugproc.h"

#include "item.h"
#include "obj_2d_item_info.h"

#include "mgr_sys_obj.h"

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
CPlayerShop::CPlayerShop()
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
CPlayerShop::~CPlayerShop()
{

}

//-------------------------------------
//- �w���v���C���[�̏���������
//-------------------------------------
HRESULT CPlayerShop::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CObjectModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax)
{
	// �v���C���[�̐ݒ菈��
	Set(pos, rot);
	
	// �v���C���[�̏���������
	CPlayer::Init(modelType, motionType, nStateMax);

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �w���v���C���[�̏I������
//-------------------------------------
void CPlayerShop::Uninit(void)
{
	// �v���C���[�̏I������
	CPlayer::Uninit();
}

//-------------------------------------
//- �w���v���C���[�̍X�V����
//-------------------------------------
void CPlayerShop::Update(void)
{
	// ���ݒ�i�O��̏��j
	m_dataPosOld.Set(m_dataPos.Get());	// �ʒu
	m_stateTypeOld = m_stateType;		// ���

	// �Q�[�����[�h�̔���
	if (CGame::GetSysGamePhase()->GetType() == CSysGamePhase::TYPE_SHOP)
	{
		// �v���C���[�̍X�V����
		CPlayer::Update();
		
		// �C�x���g�̍X�V����
		UpdateItem();

		// ���[�V�����̍X�V����
		UpdateMotion();
	}
}

//-------------------------------------
//- �w���v���C���[�̕`�揈��
//-------------------------------------
void CPlayerShop::Draw(void)
{
	// �v���C���[�̕`�揈��
	CPlayer::Draw();
}

//-------------------------------------
//- �w���v���C���[�̐�������
//-------------------------------------
CPlayerShop * CPlayerShop::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CObjectModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType)
{
	// �w���v���C���[�̃|�C���^��錾
	CPlayerShop *pCPlayerShop = new CPlayerShop;

	// �����̐����̗L���𔻒�
	if (pCPlayerShop != NULL)
	{
		// ����������
		if (FAILED(pCPlayerShop->Init(pos, rot, modelType, motionType, STATE_TYPE_MAX)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCPlayerShop == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// ��ނ�ݒ�
	pCPlayerShop->SetType(TYPE_PLAYER);

	// �w���v���C���[�̃|�C���^��Ԃ�
	return pCPlayerShop;
}

//-------------------------------------
//- �w���v���C���[�̐ݒ菈��
//-------------------------------------
void CPlayerShop::Set(D3DXVECTOR3 pos,  D3DXVECTOR3 rot)
{
	// ���X�V
	m_dataPos.Set(pos);		// �ʒu
	m_dataPosOld.Set(pos);	// �O��̈ʒu

	m_dataSize.Set(D3DXVECTOR3(50.0f, 50.0f, 50.0f));	// �傫��

	m_dataRot.Set(rot);		// �ړ���
	m_dataRotDest.Set(rot);	// �ړI�̌���
}

//-------------------------------------
//- �w���v���C���[�̃C�x���g�̍X�V����
//-------------------------------------
void CPlayerShop::UpdateItem(void)
{
	// �C�x���g�Ƃ̓����蔻��
	CollisionItem();
}

//-------------------------------------
//- �w���v���C���[�̃C�x���g�Ƃ̓����蔻�菈��
//-------------------------------------
void CPlayerShop::CollisionItem(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();		// �ʒu
	D3DXVECTOR3 size = m_dataSize.Get();	// �傫��

	// �ϐ��錾
	bool bCol = false;	// �����蔻��̗L��

	// �ϐ��錾
	for (int nCutItemObject = 0; nCutItemObject < ITEM_NUM_MAX; nCutItemObject++)
	{
		CItem *pItem = CManagerObject::GetItem(nCutItemObject);

		if (pItem != NULL)
		{
			// �ϐ��錾�i���擾�j
			D3DXVECTOR3 eventObjectPos = pItem->m_dataPos.Get();	// �ʒu
			D3DXVECTOR3 eventObjectSize = pItem->m_dataSize.Get();	// �傫��
			bool bUse = pItem->m_bDataUse.Get();					// �g�p�̗L��

			// �g�p�̗L���𔻒�
			if (bUse == false)
			{
				if (CHit::hitRectangle(pos, size, eventObjectPos, eventObjectSize) == true)
				{
					// �C�x���g�A�N�V��������
					InputItemAction(pItem);

					if (pItem->GetBuyUse() == true)
					{
						// �������UI�̗L���𔻒�
						if (m_pUiOprDesc == NULL)
						{
							// �������UI�𐶐�
							m_pUiOprDesc = CUiOprDesc::Create(CUiOprDesc::TEX_SPACE);

							// �������UI�̐ݒ菈��
							m_pUiOprDesc->Set(
								D3DXVECTOR3(
									SCREEN_WIDTH * 0.8f,
									SCREEN_HEIGHT * 0.7f,
									0.0f),
								D3DXVECTOR3(
									100.0f,
									50.0f,
									0.0f),
								D3DXVECTOR3(
									5.0f,
									5.0f,
									0.0f),
								D3DXVECTOR3(
									0.5f,
									0.5f,
									0.0f)
							);
						}

						// ���������UI�̗L���𔻒�
						if (m_pUiTextDesc == NULL)
						{
							// ���������UI�𐶐�
							m_pUiTextDesc = CUiTextDesc::Create(CUiTextDesc::TEX_PUSH);

							// ���������UI�̐ݒ菈��
							m_pUiTextDesc->Set(
								D3DXVECTOR3(
									SCREEN_WIDTH * 0.77f,
									SCREEN_HEIGHT * 0.64f,
									0.0f),
								D3DXVECTOR3(
									90.0f,
									40.0f,
									0.0f),
								D3DXVECTOR3(
									5.0f,
									5.0f,
									0.0f),
								D3DXVECTOR3(
									0.5f,
									0.5f,
									0.0f)
							);
						}
					}

					// �����蔻�肪���݂���
					bCol = true;
				}
			}

		}

	}

	if (bCol == false)
	{
		if (m_pUiOprDesc != NULL)
		{
			// �I������
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
//- �w���v���C���[�̃C�x���g�A�N�V��������
//-------------------------------------
void CPlayerShop::InputItemAction(CItem *pItem)
{
	// �L�[�{�[�h�̏��擾����
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

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

	// �A�C�e���̕`���t����
	pItem->GetItemInfo()->m_bDataDraw.Set(true);

	// ���͂̔���
	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true)
	{// SPACE�L�[

		// �v���C���[�̏�Ԃ�G��ɕύX
		m_stateType = STATE_TYPE_BUY;

		// �A�C�e���w������
		pItem->Execution();
	}
}

//-------------------------------------
//- �w���v���C���[�̃��[�V�����X�V����
//-------------------------------------
void CPlayerShop::UpdateMotion(void)
{
	// �ϐ��錾
	CMotion *pMotion = GetMotion();			// ���[�V���������擾
	D3DXVECTOR3 move = m_dataMove.Get();	// �ړ��ʂ��擾

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

		case STATE_TYPE_BUY:

			// �w�����[�V�����̐ݒ�
			pMotion->Set(STATE_TYPE_BUY);

			break;
		}
	}

}