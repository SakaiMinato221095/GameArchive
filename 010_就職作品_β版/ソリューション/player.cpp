
//-===============================================
//-
//-	�v���C���[����[player.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "player.h"

#include "renderer.h"
#include "manager.h"

#include "fade.h"

#include "Input.h"
#include "xinput.h"

#include "sound.h"
#include "debugproc.h"

#include "helper_sakai.h"

#include "camera.h"

#include "coll.h"
#include "enemy.h"

#include "command.h"

#include "attack.h"
#include "punch.h"

#include "finish_punch.h"
#include "finish_kick.h"

#include "particle.h"

#include "obj_2d_gage.h"

//-======================================
//-	�}�N����`
//-======================================

#define PLAYER_SPEED		(3.0f)	// �v���C���[�̑��x

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-======================================
//-	�R���X�g��`
//-======================================

// ��Ԃ̎���
const int STATE_TIME[CPlayer::STATE_MAX]
{
	0,
	180,
	0,
};

const int PARTS_NUM_PUNCH = 4;
const int PARTS_NUM_PUNCH_FINISH = 7;
const int PARTS_NUM_KICK = 11;
const int PARTS_NUM_KICK_FINISH = 0;

// �t�B�j�b�V�����̈ʒu�̒ǉ���
const D3DXVECTOR3 FINISH_POS_PLUS[CCommand::COMMAND_TYPE_MAX]
{
	D3DXVECTOR3(0.0f,0.0f,0.0f),
	D3DXVECTOR3(0.0f,50.0f,0.0f),
};

// �t�B�j�b�V�����̑傫��
const D3DXVECTOR3 FINISH_SIZE[CCommand::COMMAND_TYPE_MAX]
{
	D3DXVECTOR3(20.0f, 20.0f, 20.0f),
	D3DXVECTOR3(100.0f, 40.0f, 100.0f),
};

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CPlayer::CPlayer()
{
	// �l���N���A
	ZeroMemory(&m_data, sizeof(m_data));
	ZeroMemory(&m_mtxWorld, sizeof(m_mtxWorld));


	ZeroMemory(&m_apModel, sizeof(m_apModel));
	m_nNumModel = 0;

	ZeroMemory(&m_apColl, sizeof(m_apColl));
	m_pMotion = nullptr;
	m_pAttack = nullptr;
	m_pCommand = nullptr;
	m_pLife2dGage = nullptr;
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CPlayer::~CPlayer()
{

}

//-------------------------------------
//- �v���C���[�̏���������
//-------------------------------------
HRESULT CPlayer::Init(D3DXVECTOR3 pos , D3DXVECTOR3 rot,CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax)
{
	// ���f���̃p�[�c�����擾
	m_nNumModel = CModel::GetPartsNum(modelType);

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		// �K�w�\��X�I�u�W�F�N�g�̗L���𔻒�
		if (m_apModel[nCount] == NULL)
		{
			// �K�w�\��X�I�u�W�F�N�g�̐���
			m_apModel[nCount] = CModel::Create(modelType, nCount);

			if (m_apModel[nCount] == nullptr)
			{
				return E_FAIL;
			}

			// �K�w�\��X�I�u�W�F�N�g�̐ݒ�
			m_apModel[nCount]->SetParent(m_apModel, modelType, nCount);
		}
	}

	if (m_pMotion == NULL)
	{
		// ���[�V�����̐���
		m_pMotion = CMotion::Create(m_nNumModel, nStateMax);

		if (m_pMotion == nullptr)
		{
			return E_FAIL;
		}

		// �t�@�C����ǂݍ���
		m_pMotion->SetFile(motionType);

		// ���f���̐ݒ�
		m_pMotion->SetModel(m_apModel, 0);

		// �ҋ@���[�V������ݒ�
		m_pMotion->Set(0);
	}

	// �R�}���h
	if (m_pCommand == nullptr)
	{
		// �R�}���h�̐���
		m_pCommand = CCommand::Create();

		if (m_pCommand == nullptr)
		{
			return E_FAIL;
		}
	}

	// �̗�
	if (m_pLife2dGage == nullptr)
	{
		// �̗͂̐���
		m_pLife2dGage = CObj2dGage::Create();

		if (m_pLife2dGage == nullptr)
		{
			return E_FAIL;
		}
	}

	// �퓬�v���C���[�̐ݒ菈��
	InitSet(pos, rot);

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �v���C���[�̏I������
//-------------------------------------
void CPlayer::Uninit(void)
{
	for (int nCount = 0; nCount < COLL_TYPE_MAX; nCount++)
	{
		if (m_apColl[nCount] != NULL)
		{
			// �����蔻��̏I������
			m_apColl[nCount]->Uninit();

			delete m_apColl[nCount];
			m_apColl[nCount] = NULL;
		}
	}

	// ���f���̏I������
	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{
			// ���f���̊J������
			m_apModel[nCount]->Uninit();

			delete m_apModel[nCount];
			m_apModel[nCount] = NULL;
		}
	}

	// ���[�V�����̏I������
	if (m_pMotion != NULL)
	{
		// ���[�V�����̊J��
		m_pMotion->Uninit();

		delete m_pMotion;
		m_pMotion = NULL;
	}

	// �R�}���h�̏I������
	if (m_pCommand != NULL)
	{
		// ���[�V�����̊J��
		m_pCommand->Uninit();

		delete m_pCommand;
		m_pCommand = NULL;
	}

	// �U���̏I������
	if (m_pAttack != nullptr)
	{
		m_pAttack->Uninit();
		m_pAttack = nullptr;
	}

	// �̗͕\���̏I������
	if (m_pLife2dGage != nullptr)
	{
		m_pLife2dGage->Uninit();
		m_pLife2dGage = nullptr;
	}

	// �������g�̃|�C���^�̊J��
	Release();
}

//-------------------------------------
//- �v���C���[�̍X�V����
//-------------------------------------
void CPlayer::Update(void)
{
	// �O��̈ʒu���X�V
	m_data.posOld = m_data.pos;

	if (m_data.state == STATE_NEUTRAL)
	{
		// �ړ��̓��͏���
		InputMove();
	}
	else if (m_data.state == STATE_BATTLE ||
			 m_data.state == STATE_FINISH)
	{
		// �U������
		UpdateBattle();
	}

	// �R���{���͏���
	InputCombo();

	// �����̍X�V����
	UpdateRot();

	// �ʒu���̍X�V����
	UpdatePos();

	// �ǉ����̍X�V����
	UpdatePlusData();

	// �ʏ탂�[�V�����̍X�V����
	UpdateMotionNone();

	// �U���̍X�V����
	UpdateAttack();

	// �R�}���h�̍X�V����
	UpdateCommand();

	// �����蔻��̍X�V����
	UpdateCollision();

	if (m_pLife2dGage != nullptr)
	{
		m_pLife2dGage->UpdateInfo(
			m_pLife2dGage->GetPos(),
			m_pLife2dGage->GetSize(),
			m_pLife2dGage->GetColor(),
			m_data.nLife);
	}

	// �f�o�b�N�\��
	DebugPlayer();
}

//-------------------------------------
//- �v���C���[�̕`�揈��
//-------------------------------------
void CPlayer::Draw(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_data.pos;	// �ʒu���
	D3DXVECTOR3 rot = m_data.rot;	// �������

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

	 // �����������𔲂���
		return;
	}

	// �ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu���f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(
		D3DTS_WORLD,
		&m_mtxWorld);

	// �p�[�c���̕`�揈��
	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_apModel[nCount] != nullptr)
		{
			m_apModel[nCount]->Draw();
		}
	}

	if (m_pCommand != NULL)
	{
		// �R�}���h�̕`�揈��
		m_pCommand->Draw();
	}
}
//-------------------------------------
//- �v���C���[�̃L�b�N�U���ݒ菈��
//-------------------------------------
void CPlayer::HitDamage(int nDamage)
{
	m_data.nLife -= nDamage;

	// �p�[�e�B�N���̐ݒ�
	SetParticle(
		8,
		m_data.pos,
		D3DXVECTOR3(10.0f, 10.0f, 0.0f),
		D3DXVECTOR3(10.0f, 10.0f, 0.0f),
		D3DXCOLOR(1.0f, 0.0, 0.0f, 1.0f),
		30);

	if (m_data.nLife < 0)
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
}

//-------------------------------------
//- �v���C���[�̐�������
//-------------------------------------
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType)
{
	// �v���C���[�̃|�C���^��錾
	CPlayer *pPlayer = DBG_NEW CPlayer;

	// �����̐����̗L���𔻒�
	if (pPlayer != NULL)
	{
		// ����������
		if (FAILED(pPlayer->Init(pos, rot, modelType, motionType, MOTION_STATE_MAX)))
		{// ���s��

		 // �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pPlayer == NULL)
	{// ���s��

	 // �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �v���C���[�̃|�C���^��Ԃ�
	return pPlayer;
}

//-------------------------------------
//- �v���C���[�̏����ݒ菈��
//-------------------------------------
void CPlayer::InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_data.pos = pos;
	m_data.posOld = pos;
	m_data.rot = rot;
	m_data.rotDest = rot;

	m_data.size = D3DXVECTOR3(40.0f, 200.0f, 40.0f);

	m_data.nLife = 50;

	for (int nCount = 0; nCount < COLL_TYPE_MAX; nCount++)
	{
		if (m_apColl[nCount] == NULL)
		{
			switch (nCount)
			{
			case COLL_TYPE_NEUTRAL:
				
				// �����蔻��ݒ�
				m_apColl[nCount] = CColl::Create(
					CMgrColl::TAG_PLAYER,
					this,
					m_data.pos,
					m_data.size);

				break;

			case COLL_TYPE_SEARCH:

				// �����蔻��ݒ�
				m_apColl[nCount] = CColl::Create(
					CMgrColl::TAG_NONE,
					this,
					m_data.pos,
					m_data.size + D3DXVECTOR3(100.0f,0.0f,100.0f));

				break;
			}

		}
	}

	if (m_pLife2dGage != NULL)
	{
		m_pLife2dGage->SetInit(
			D3DXVECTOR3(SCREEN_WIDTH * 0.2f,SCREEN_HEIGHT * 0.1f,0.0f),
			D3DXVECTOR3(150.0f, 15.0f, 0.0f),
			D3DXCOLOR(0.0f,1.0f,0.0f,1.0f),
			m_data.nLife,
			m_data.nLife);
	}
	
	m_data.plus.speedRate = 1.0f;
}

//-------------------------------------
//- �v���C���[�̈ړ�����
//-------------------------------------
void CPlayer::UpdatePos(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_data.pos;	// �ʒu
	D3DXVECTOR3 move = m_data.move;	// �ړ���

	// �ʒu���Ɉړ��ʂ����Z
	pos += move;

	// �ړ��ʂ�����
	move.x += (0.0f - move.x) * 0.3f;
	move.z += (0.0f - move.z) * 0.3f;

	// ���X�V
	m_data.pos = pos;
	m_data.move = move;
}

//-------------------------------------
//- �v���C���[�̍U���X�V����
//-------------------------------------
void CPlayer::UpdateBattle(void)
{
	if (m_data.bIsTarget)
	{
		// �ʒu���Ɉړ��ʂ����Z
		float rotTgt = atan2f(m_data.pos.x - m_data.posTgt.x, m_data.pos.z - m_data.posTgt.z);

		m_data.rotDest.y = rotTgt;
	}

	m_data.pos += D3DXVECTOR3(-sinf(m_data.rot.y) * 3.0f, 0.0f, -cosf(m_data.rot.y) * 3.0f);

	// �ړ��ʂ�����
	m_data.move.x += (0.0f - m_data.move.x) * 0.3f;
	m_data.move.z += (0.0f - m_data.move.z) * 0.3f;

}

//-------------------------------------
//- �v���C���[�̌�������
//-------------------------------------
void CPlayer::UpdateRot(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 rot = m_data.rot;			// ����
	D3DXVECTOR3 rotDest = m_data.rotDest;	// �ړI�̌���

	HelperSakai::NormalizeAngle(&rot, &rotDest, 0.15f);

	// ���X�V
	m_data.rot = rot;			// ����
	m_data.rotDest = rotDest;	// �ړI�̌���
}

//-------------------------------------
//- �v���C���[�̒ǉ��f�[�^�̍X�V����
//-------------------------------------
void CPlayer::UpdatePlusData(void)
{
	if (m_data.plus.sppedPlusTime != 0)
	{
		m_data.plus.sppedPlusTime--;
		
		if (m_data.plus.sppedPlusTime <= 0)
		{
			m_data.plus.speedRate = 1.0f;
		}
	}	
}

//-------------------------------------
//- �ʏ��ԃv���C���[�̍U���̍X�V����
//-------------------------------------
void CPlayer::UpdateAttack(void)
{
	// �U���̏��X�V����
	if (m_pAttack != nullptr)
	{
		D3DXVECTOR3 posParts = {};
		
		// �p�[�c�̈ʒu
		posParts = D3DXVECTOR3(
			GetModel(m_data.nAttackPartsNldx)->GetMtxWorld()._41,
			GetModel(m_data.nAttackPartsNldx)->GetMtxWorld()._42,
			GetModel(m_data.nAttackPartsNldx)->GetMtxWorld()._43);

		if (m_pAttack->GetColl() != nullptr)
		{
			D3DXVECTOR3 size = m_pAttack->GetSize();

			m_pAttack->UpdateData(posParts, size);
		}
	}
}

//-------------------------------------
//- �ʏ��ԃv���C���[�̃R�}���h�̍X�V����
//-------------------------------------
void CPlayer::UpdateCommand(void)
{
	if (m_pCommand != NULL)
	{
		// �R�}���h�̍X�V����
		m_pCommand->Update();
	}
}

//-------------------------------------
//- �ʏ��ԃv���C���[�̓����蔻��̍X�V����
//-------------------------------------
void CPlayer::UpdateCollision(void)
{
	for (int nCntColl = 0; nCntColl < COLL_TYPE_MAX; nCntColl++)
	{
		if (m_apColl[nCntColl] != NULL)
		{
			CManager* pManager = CManager::GetInstance();

			if (pManager == nullptr)
			{
				return;
			}

			CMgrColl* pMgrColl = pManager->GetMgrColl();

			if (pMgrColl == nullptr)
			{
				return;
			}

			switch (nCntColl)
			{
			case COLL_TYPE_NEUTRAL:

				// �����蔻��̏��X�V����
				m_apColl[nCntColl]->UpdateData(
					m_data.pos,
					m_data.posOld,
					m_data.size);

				// �v���C���[�̓����蔻��
				if (m_apColl[nCntColl]->HitSide(CMgrColl::TAG_WALL_X, CMgrColl::EVENT_TYPE_PRESS, CMgrColl::TYPE_SXIS_X) == true)
				{
					// �ړ��ʂ��Ȃ���
					m_data.move.x = 0.0f;

					// �v���C���[��Y���W�ړ����~
					m_data.pos.x = m_data.posOld.x;
				}

				// �v���C���[�̓����蔻��
				if (m_apColl[nCntColl]->HitSide(CMgrColl::TAG_WALL_Z, CMgrColl::EVENT_TYPE_PRESS, CMgrColl::TYPE_SXIS_Z) == true)
				{
					// �ړ��ʂ��Ȃ���
					m_data.move.z = 0.0f;

					// �v���C���[��Y���W�ړ����~
					m_data.pos.z = m_data.posOld.z;
				}

				// �o���ǂƂ̓����蔻��
				if (m_apColl[nCntColl]->HitSide(CMgrColl::TAG_SPAWN_ENEMY_WALL, CMgrColl::EVENT_TYPE_TRIGGER, CMgrColl::TYPE_SXIS_X) == true)
				{
					// �ő�ڐG�����擾
					CColl::Data data = m_apColl[nCntColl]->GetData();
					int nHitNldxMax = data.nHitNldxMax;

					// �ڐG�����G�̃_���[�W����
					for (int nCount = 0; nCount < nHitNldxMax; nCount++)
					{
						CColl* pColl = pMgrColl->GetColl(data.hitData[nCount].nNldx);

						if (pColl != nullptr)
						{
							CObject* pObj = pColl->GetData().pObj;

							if (pObj != nullptr)
							{
								pObj->Hit();
							}
						}
					}
				}

				break;

			case COLL_TYPE_SEARCH:

				if (m_data.rot.y >= 0.0f && m_data.rot.y <= (D3DX_PI * 0.25f) ||
					m_data.rot.y <= 0.0f && m_data.rot.y >= -(D3DX_PI * 0.25f) ||
					m_data.rot.y >= (D3DX_PI * 0.75f) && m_data.rot.y <= D3DX_PI ||
					m_data.rot.y <= -(D3DX_PI * 0.75f) && m_data.rot.y >= -D3DX_PI)
				{
					// �����蔻��̏��X�V����
					m_apColl[nCntColl]->UpdateData(
						m_data.pos + D3DXVECTOR3((-sinf(m_data.rot.y) * m_data.size.x), 0.0f, (-cosf(m_data.rot.y) * m_data.size.z)),
						m_data.posOld,
						D3DXVECTOR3(200.0f, 50.0f, 100.0f));
				}
				else if (
					m_data.rot.y >= (D3DX_PI * 0.25f) && m_data.rot.y <= (D3DX_PI * 0.75f) ||
					m_data.rot.y <= -(D3DX_PI * 0.25f) && m_data.rot.y >= -(D3DX_PI * 0.75f))
				{
					// �����蔻��̏��X�V����
					m_apColl[nCntColl]->UpdateData(
						m_data.pos + D3DXVECTOR3((-sinf(m_data.rot.y) * m_data.size.x), 0.0f, (-cosf(m_data.rot.y) * m_data.size.z)),
						m_data.posOld,
						D3DXVECTOR3(100.0f, 50.0f, 200.0f));
				}

				// �v���C���[�̓����蔻��
				if (m_apColl[nCntColl]->Hit(CMgrColl::TAG_ENEMY, CMgrColl::EVENT_TYPE_PRESS))
				{
					float fLengthNear = 100000.0f;
					int nHitNldxMaxTemp = m_apColl[nCntColl]->GetData().nHitNldxMaxTemp;

					for (int nCntLength = 0; nCntLength < nHitNldxMaxTemp; nCntLength++)
					{
						float fLength = m_apColl[nCntColl]->GetData().hitDataTemp[nCntLength].fLength;

						if (fLength < fLengthNear)
						{
							fLengthNear = fLength;

							int hitNldx = m_apColl[nCntColl]->GetData().hitDataTemp[nCntLength].nNldx;

							CColl* pCollPair = pMgrColl->GetColl(hitNldx);

							if (pCollPair != nullptr)
							{
								m_data.posTgt = pCollPair->GetData().pos;

								m_data.bIsTarget = true;
							}
						}
					}
				}
				else
				{
					m_data.bIsTarget = false;
				}

				break;
			}

		}

	}
}

//-------------------------------------
//- �ʏ��ԃv���C���[�̃��[�V�����X�V����
//-------------------------------------
void CPlayer::UpdateMotionNone(void)
{
	// �ϐ��錾�i���擾�j
	CMotion* pMotion = GetMotion();		// ���[�V����
	D3DXVECTOR3 move = GetData().move;	// �ړ���

	// ��Ԃ𔻒�
	if (m_data.motionState == MOTION_STATE_NEUTRAL ||
		m_data.motionState == MOTION_STATE_MOVE)
	{
		// �ړ��ʂŏ�Ԃ�ύX
		if (move.x >= 0.3f ||
			move.x <= -0.3f ||
			move.z >= 0.3f ||
			move.z <= -0.3f)
		{
			// �ړ���ԂɕύX
			m_data.motionState = MOTION_STATE_MOVE;
		}
		else
		{
			// �ҋ@��Ԃ̕ύX
			m_data.motionState = MOTION_STATE_NEUTRAL;
		}
	}

	if (pMotion->GetType() == MOTION_STATE_PUNCH && m_data.motionState != MOTION_STATE_PUNCH ||
		pMotion->GetType() == MOTION_STATE_KICK && m_data.motionState != MOTION_STATE_KICK ||
		pMotion->GetType() == MOTION_STATE_PUNCH_FINISH && m_data.motionState != MOTION_STATE_PUNCH_FINISH ||
		pMotion->GetType() == MOTION_STATE_KICK_FINISH && m_data.motionState != MOTION_STATE_KICK_FINISH)
	{
		if (m_pAttack != nullptr)
		{
			// �I������
			m_pAttack->Uninit();
			m_pAttack = nullptr;
		}

		m_data.state = STATE_NEUTRAL;
	}

	if (m_data.motionState != pMotion->GetType())
	{
		pMotion->Set(m_data.motionState);
	}

	// ���[�V�����̏I���󋵂𔻒�
	if (pMotion->IsFinsih())
	{
		// ���[�V�����̍X�V
		pMotion->Update();
	}
	else
	{
		// �ҋ@��Ԃ�ݒ�
		m_data.motionState = MOTION_STATE_NEUTRAL;
	}
}

//-------------------------------------
//- �v���C���[�̈ړ�����
//-------------------------------------
void CPlayer::InputMove(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInstance()->GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

	 // �ړ������𔲂���
		return;
	}

	// X���͂̃|�C���^��錾
	CXInput *pXInput = CManager::GetInstance()->GetXInput();

	// X���͂̏��擾�̐����𔻒�
	if (pXInput == NULL)
	{
		// �����𔲂���
		return;
	}

	// �ϐ��錾
	D3DXVECTOR3 move = m_data.move;					// �ړ��ʂ��擾
	D3DXVECTOR3 rotDest = m_data.rotDest;			// �ړI�̉�]�ʂ��擾
	float speedRate = m_data.plus.speedRate;		// ���x�̔{��

	D3DXVECTOR3 speed = D3DXVECTOR3(PLAYER_SPEED, 0.0f, PLAYER_SPEED);
	speed *= speedRate;

	// �J�����̏����擾
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	// �J�����̌������擾
	D3DXVECTOR3 rotCamera = pCamera->GetData().rot;

	// �ړ�
	if (pInputKeyboard->GetPress(DIK_W) == true ||
		pXInput->GetPress(CXInput::TYPE_STICK_UP, CXInput::TYPE_INPUT_STICK_L) == true)
	{//W�L�[�������ꂽ�Ƃ�
		if (pInputKeyboard->GetPress(DIK_A) == true ||
			pXInput->GetPress(CXInput::TYPE_STICK_LEFT, CXInput::TYPE_INPUT_STICK_L) == true)
		{//����ړ�

			move.x -= sinf((D3DX_PI * 0.75f) + rotCamera.y) * speed.x;
			move.z -= cosf((D3DX_PI * 0.75f) + rotCamera.y) * speed.z;

			rotDest.y = (D3DX_PI * 0.75f) + rotCamera.y;
		}
		else if (
			pInputKeyboard->GetPress(DIK_D) == true ||
			pXInput->GetPress(CXInput::TYPE_STICK_RIGHT, CXInput::TYPE_INPUT_STICK_L) == true)
		{//�E��ړ�

			move.x += sinf((D3DX_PI * 0.25f) + rotCamera.y) * speed.x;
			move.z += cosf((D3DX_PI * 0.25f) + rotCamera.y) * speed.z;

			rotDest.y = -(D3DX_PI * 0.75f) + rotCamera.y;
		}
		else
		{

			move.x += sinf((D3DX_PI * 0.0f) + rotCamera.y) * speed.x;
			move.z += cosf((D3DX_PI * 0.0f) + rotCamera.y) * speed.z;

			rotDest.y = D3DX_PI + rotCamera.y;

		}
	}

	else if (
		pInputKeyboard->GetPress(DIK_S) == true ||
		pXInput->GetPress(CXInput::TYPE_STICK_DOWN, CXInput::TYPE_INPUT_STICK_L) == true)
	{//S�L�[�������ꂽ�Ƃ�
		if (
			pInputKeyboard->GetPress(DIK_A) == true ||
			pXInput->GetPress(CXInput::TYPE_STICK_LEFT, CXInput::TYPE_INPUT_STICK_L) == true)
		{//�����ړ�

			move.x -= sinf((D3DX_PI * 0.25f) + rotCamera.y) * speed.x;
			move.z -= cosf((D3DX_PI * 0.25f) + rotCamera.y) * speed.z;

			rotDest.y = (D3DX_PI * 0.25f) + rotCamera.y;
		}
		else  if (
			pInputKeyboard->GetPress(DIK_D) == true ||
			pXInput->GetPress(CXInput::TYPE_STICK_RIGHT, CXInput::TYPE_INPUT_STICK_L) == true)
		{//�E���ړ�

			move.x += sinf((D3DX_PI * 0.75f) + rotCamera.y) * speed.x;
			move.z += cosf((D3DX_PI * 0.75f) + rotCamera.y) * speed.z;

			rotDest.y = -(D3DX_PI * 0.25f) + rotCamera.y;
		}
		else
		{
			//�ړ���
			move.x += sinf((D3DX_PI * 1.0f) + rotCamera.y) * speed.x;
			move.z += cosf((D3DX_PI * 1.0f) + rotCamera.y) * speed.z;

			rotDest.y = (D3DX_PI * 0.0f) + rotCamera.y;
		}
	}

	else  if (
		pInputKeyboard->GetPress(DIK_A) == true ||
		pXInput->GetPress(CXInput::TYPE_STICK_LEFT, CXInput::TYPE_INPUT_STICK_L) == true)
	{//A�L�[�������ꂽ�Ƃ�

		move.x -= sinf((D3DX_PI * 0.5f) + rotCamera.y) * speed.x;
		move.z -= cosf((D3DX_PI * 0.5f) + rotCamera.y) * speed.z;

		rotDest.y = (D3DX_PI * 0.5f) + rotCamera.y;
	}
	else if (
		pInputKeyboard->GetPress(DIK_D) == true ||
		pXInput->GetPress(CXInput::TYPE_STICK_RIGHT, CXInput::TYPE_INPUT_STICK_L) == true)
	{//D�L�[�������ꂽ�Ƃ�

		move.x += sinf((D3DX_PI * 0.5f) + rotCamera.y) * speed.x;
		move.z += cosf((D3DX_PI * 0.5f) + rotCamera.y) * speed.z;

		rotDest.y = -(D3DX_PI * 0.5f) + rotCamera.y;
	}

	// ���X�V
	m_data.move = move;			// �ړ���
	m_data.rotDest = rotDest;	// �ړI�̌���
}

//-------------------------------------
//- �v���C���[�̃R���{���͏���
//-------------------------------------
void CPlayer::InputCombo(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInstance()->GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

	 // �ړ������𔲂���
		return;
	}

	// X���͂̃|�C���^��錾
	CXInput* pXInput = CManager::GetInstance()->GetXInput();

	// X���͂̏��擾�̐����𔻒�
	if (pXInput == NULL)
	{
		// �����𔲂���
		return;
	}

	// ���͎�ޏ����i�[
	CCommand::INPUT_TYPE inputType = CCommand::INPUT_TYPE_NONE;

	if (m_data.motionState == MOTION_STATE_NEUTRAL ||
		m_data.motionState == MOTION_STATE_MOVE)
	{
		if (
			pInputKeyboard->GetTrigger(DIK_J) == true ||
			pXInput->GetTrigger(XINPUT_GAMEPAD_A, CXInput::TYPE_INPUT_BUTTON) == true)
		{
			// �p���`
			inputType = CCommand::INPUT_TYPE_PUNCH;
		}
		else if (
			pInputKeyboard->GetTrigger(DIK_K) == true ||
			pXInput->GetTrigger(XINPUT_GAMEPAD_B, CXInput::TYPE_INPUT_BUTTON) == true)
		{
			// �L�b�N
			inputType = CCommand::INPUT_TYPE_KICK;
		}
	}

	if (m_pCommand != nullptr &&
		inputType != CCommand::INPUT_TYPE_NONE)
	{
		// �R�}���h�̓��͏�����ݒ�o�t�B�j�b�V���̗L�����擾�p
		bool bFinish = m_pCommand->SetInput(inputType);

		if (bFinish)
		{
			// ��Ԑݒ�
			m_data.state = STATE_FINISH;
			 
			// �t�B�j�b�V���U��
			SetAttackFinish();
		}
		else
		{
			// ��Ԑݒ�
			m_data.state = STATE_BATTLE;

			// ���͂̐ݒ菈��
			SetAttack(inputType);
		}
	}
}

//-------------------------------------
//- �v���C���[�̃p���`�U���ݒ菈��
//-------------------------------------
void CPlayer::SetAttack(CCommand::INPUT_TYPE inputType)
{
	switch (inputType)
	{
	case CCommand::INPUT_TYPE_PUNCH:

		// ���[�V�����̐ݒ�i�p���`�j
		m_data.motionState = MOTION_STATE_PUNCH;
		m_data.nAttackPartsNldx = PARTS_NUM_PUNCH;

		break;
	case CCommand::INPUT_TYPE_KICK:

		// ���[�V�����̐ݒ�i�p���`�j
		m_data.motionState = MOTION_STATE_KICK;
		m_data.nAttackPartsNldx = PARTS_NUM_KICK;

		break;
	}

	if (m_pAttack == nullptr)
	{
		m_pAttack = CAttack::Create();

		if (m_pAttack != nullptr)
		{
			// �p�[�c�̈ʒu
			D3DXVECTOR3 posParts = D3DXVECTOR3(
				GetModel(m_data.nAttackPartsNldx)->GetMtxWorld()._41,
				GetModel(m_data.nAttackPartsNldx)->GetMtxWorld()._42,
				GetModel(m_data.nAttackPartsNldx)->GetMtxWorld()._43);

			// �U���̏����ݒ菈��
			m_pAttack->InitSet(
				posParts,
				D3DXVECTOR3(20.0f,20.0f,20.0f),
				3,
				CMgrColl::TAG_ENEMY);
		}
	}
}

//-------------------------------------
//- �v���C���[�̃t�B�j�b�V���U���ݒ菈��
//-------------------------------------
void CPlayer::SetAttackFinish(void)
{
	CCommand::InfoFinish infoFinish = m_pCommand->GetInfoFinish();

	switch (infoFinish.type)
	{
	case CCommand::COMMAND_TYPE_PUNCH_NOR:

		m_pAttack = CFinishPunch::Create();

		if (m_pAttack != nullptr)
		{
			// ���[�V�����̐ݒ�i�p���`�t�B�j�b�V���j
			m_data.motionState = MOTION_STATE_PUNCH_FINISH;

			// �p�[�c�ʒu
			m_data.nAttackPartsNldx = PARTS_NUM_PUNCH_FINISH;
		}

		break;

	case CCommand::COMMAND_TYPE_KICK_NOR:

		m_pAttack = CFinishKick::Create();

		if (m_pAttack != nullptr)
		{
			// ���[�V�����̐ݒ�i�p���`�t�B�j�b�V���j
			m_data.motionState = MOTION_STATE_KICK_FINISH;

			// �p�[�c�ʒu
			m_data.nAttackPartsNldx = PARTS_NUM_KICK_FINISH;
		}

		break;
	}

	if (m_pAttack != nullptr)
	{
		// �p�[�c�̈ʒu
		D3DXVECTOR3 posParts = D3DXVECTOR3(
			GetModel(m_data.nAttackPartsNldx)->GetMtxWorld()._41,
			GetModel(m_data.nAttackPartsNldx)->GetMtxWorld()._42,
			GetModel(m_data.nAttackPartsNldx)->GetMtxWorld()._43);

		// �U���̏����ݒ菈��
		m_pAttack->InitSet(
			posParts,
			FINISH_SIZE[infoFinish.type],
			10,
			CMgrColl::TAG_ENEMY);

		// �ǉ��̈ʒu�ݒ�
		m_pAttack->SetPosPlus(FINISH_POS_PLUS[infoFinish.type]);
	}
}

//-------------------------------------
//- �v���C���[�̃f�o�b�N�\��
//-------------------------------------
void CPlayer::DebugPlayer(void)
{
	// �f�o�b�N�v���b�N�̎擾
	CDebugProc *pDebugProc = CManager::GetInstance()->GetDbugProc();

	// �f�o�b�N�v���b�N�擾�̗L���𔻒�
	if (pDebugProc == NULL)
	{
		return;
	}

	pDebugProc->Print("\n");
	pDebugProc->Print("�v���C���[�̏��");
	pDebugProc->Print("\n");
	pDebugProc->Print("%d", m_data.state);
	pDebugProc->Print("\n");
}