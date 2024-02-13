
//-===============================================
//-
//-	�{�X�G�̏���[enemy_boss.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "enemy_boss.h"

#include "character.h"
#include "obj_2d_gage.h"

#include "renderer.h"
#include "manager.h"
#include "fade.h"

#include "debugproc.h"

#include "helper_sakai.h"

#include "manager_model.h"

#include "coll.h"

#include "particle.h"

#include "attack.h"
#include "charge.h"


//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�R���X�g��`
//=======================================

const int PARTS_ATTACK = 15;

const D3DXVECTOR3 PARTS_SIZE = D3DXVECTOR3(10.0f, 10.0f, 10.0f);

const int AI_COUNT_CHANGE[CEnemyBoss::MOTION_STATE_MAX]
{
	120,
	0,
	0,
	0,
	0,
	0,
	30,
	0,
	0,
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	�G�̃R���X�g���N�^
//-------------------------------------
CEnemyBoss::CEnemyBoss()
{
	ZeroMemory(&m_info, sizeof(m_info));
	ZeroMemory(&m_infoVisual, sizeof(m_infoVisual));
	ZeroMemory(&m_infoAi, sizeof(m_infoAi));
	ZeroMemory(&m_infoAttach, sizeof(m_infoAttach));
}

//-------------------------------------
//-	�G�̃f�X�g���N�^
//-------------------------------------
CEnemyBoss::~CEnemyBoss()
{

}

//-------------------------------------
//- �G�̏���������
//-------------------------------------
HRESULT CEnemyBoss::Init(CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType)
{
	// X�t�@�C���I�u�W�F�N�g�̏I��
	CEnemy::Init();

	if (m_infoVisual.pCharacter == nullptr)
	{
		// �L�����N�^�[�̐�������
		m_infoVisual.pCharacter = CCharacter::Create(
			modelType,
			motionType,
			MOTION_STATE_MAX);

		if (m_infoVisual.pCharacter != nullptr)
		{
			// ������Ԃ̐ݒ�
			SetState(CEnemyBoss::MOTION_STATE_NEUTRAL);
			
			// �ҋ@���[�V������ݒ�
			m_infoVisual.pCharacter->GetMotion()->Set(0);
		}
		else if (m_infoVisual.pCharacter == nullptr)
		{
			return E_FAIL;
		}

		if (m_infoVisual.pLife2dGage == nullptr)
		{
			// 2D�̗̓Q�[�W
			m_infoVisual.pLife2dGage = CObj2dGage::Create();

			if (m_infoVisual.pLife2dGage == nullptr)
			{
				return E_FAIL;
			}
		}
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �G�̏I������
//-------------------------------------
void CEnemyBoss::Uninit(void)
{
	if (m_infoVisual.pCharacter != nullptr)
	{
		m_infoVisual.pCharacter->Uninit();
		m_infoVisual.pCharacter = nullptr;
	}

	// �U���̏I������
	if (m_infoAttach.pAttack != nullptr)
	{
		m_infoAttach.pAttack->Uninit();
		m_infoAttach.pAttack = nullptr;
	}

	// X�t�@�C���I�u�W�F�N�g�̏I��
	CEnemy::Uninit();
}

//-------------------------------------
//- �G�̍X�V����
//-------------------------------------
void CEnemyBoss::Update(void)
{
	// �O��̈ʒu���X�V
	SetPosOld(GetPos());

	if (m_info.state == STATE_DAMAGE)
	{
		// �_���[�W�̍X�V����
		UpdateDamage();
	}
	else if (m_info.state == STATE_BIG_DAMAGE)
	{
		// �_���[�W�̐�����΂��_���[�W
		UpdateBigDamage();
	}
	else
	{
		// �^�[�Q�b�g�Ƃ̏��X�V�i�v���C���[�j
		UpdateTargetPlayer();

		// AI�̍X�V����
		UpdateAi();
	}

	// �ʒu�X�V����
	UpdatePos();

	// �U���̍X�V����
	UpdateAttack();

	// �����蔻��X�V����
	UpdateCollision();

	if (m_infoAi.state != AI_STATE_CHARGE_ATTACK || 
		m_infoAi.state != AI_STATE_KICK_1 ||
		m_infoAi.state != AI_STATE_KICK_2 ||
		m_infoAi.state != AI_STATE_KICK_3)
	{
		// �����蔻��X�V����
		UpdateCollisionPlayer();
	}

	// ���[�V�����̍X�V����
	UpdateMotion();

	// �����ڂ̍X�V����
	UpdateVisual();

	// �f�o�b�N�\��
	Debug();
}

//-------------------------------------
//- �G�̕`�揈��
//-------------------------------------
void CEnemyBoss::Draw(void)
{
	// X�t�@�C���I�u�W�F�N�g�̕`�揈��
	CEnemy::Draw();
}

//-------------------------------------
//- �ʏ�G�̐�������
//-------------------------------------
CEnemyBoss* CEnemyBoss::Create(CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType)
{
	// �ʏ�G�̐���
	CEnemyBoss* pEnemyWeak = DBG_NEW CEnemyBoss;

	// �����̐����̗L���𔻒�
	if (pEnemyWeak != NULL)
	{
		// ����������
		if (FAILED(pEnemyWeak->Init(modelType, motionType)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pEnemyWeak == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �ʏ�G�̃|�C���^��Ԃ�
	return pEnemyWeak;
}

//-------------------------------------
//-	�G�̃_���[�W����
//-------------------------------------
void CEnemyBoss::HitDamage(int nDamage)
{
	// �_���[�W����
	Damage(nDamage);

	// ��Ԃ�ݒ�
	if (m_info.state == STATE_ATTACK)
	{

	}
	else if (nDamage >= 5)
	{// �傫���_���[�W

		// ��Ԑݒ�
		SetState(MOTION_STATE_BIG_DAMAGE);
	}
	else
	{
		// ��Ԑݒ�
		SetState(MOTION_STATE_DAMAGE);
	}

	// ���S���菈��
	if (Dead())
	{
		// �G�̏I������
		Uninit();
	}
}

//-------------------------------------
//-	�G�̃��f���̏����ݒ�
//-------------------------------------
void CEnemyBoss::SetInit(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	CEnemy::SetInit(pos, rot, nLife);

	if (m_infoVisual.pCharacter != nullptr)
	{
		// �L�����N�^�[�̐�������
		m_infoVisual.pCharacter->UpdateData(pos, rot);
	}

	if (m_infoVisual.pLife2dGage != nullptr)
	{
		m_infoVisual.pLife2dGage->SetInit(
			D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.9f, 0.0f),
			D3DXVECTOR3(250.0f, 25.0f, 0.0f),
			D3DXCOLOR(1.0f, 0.0f, 0.0f,1.0f),
			nLife,
			nLife);
	}
}

//-------------------------------------
//-	���[�V�����̍X�V����
//-------------------------------------
void CEnemyBoss::UpdateMotion(void)
{
	if (m_infoVisual.pCharacter == nullptr)
	{
		return;
	}

	// �ϐ��錾�i���擾�j
	CMotion* pMotion = m_infoVisual.pCharacter->GetMotion();		// ���[�V����

	if (pMotion == nullptr)
	{
		return;
	}

	// ��Ԃ𔻒�
	if (m_infoVisual.motionState == MOTION_STATE_NEUTRAL ||
		m_infoVisual.motionState == MOTION_STATE_MOVE)
	{
		// �ړ��ʂŏ�Ԃ�ύX
		if (GetMove().x >= 0.1f ||
			GetMove().x <= -0.1f ||
			GetMove().z >= 0.1f ||
			GetMove().z <= -0.1f)
		{
			// �ړ���ԂɕύX
			m_infoVisual.motionState = MOTION_STATE_MOVE;
		}
		else
		{
			// �ҋ@��Ԃ̕ύX
			m_infoVisual.motionState = MOTION_STATE_NEUTRAL;
		}
	}

	if (pMotion->GetType() == MOTION_STATE_DAMAGE && m_infoVisual.motionState != MOTION_STATE_DAMAGE ||
		pMotion->GetType() == MOTION_STATE_BIG_DAMAGE && m_infoVisual.motionState != MOTION_STATE_BIG_DAMAGE)
	{
		if (m_info.state == STATE_NORMAL)
		{
			// �ʏ��ԂɕύX
			SetState(MOTION_STATE_NEUTRAL);
		}
	}

	// ���[�V�����̏I���󋵂𔻒�
	if (pMotion->IsFinsih() == false)
	{
		if (m_info.state == STATE_NORMAL)
		{
			// �s���ݒ�
			SetAiActiv();
		}
		else if (m_info.state == STATE_ATTACK)
		{
			if (m_infoAi.bCombo)
			{
				// �s���ݒ�
				SetAiActiv();
			}
			else
			{
				// �ʏ��ԂɕύX
				SetState(MOTION_STATE_NEUTRAL);
			}
		}
		else
		{
			// �ʏ��ԂɕύX
			SetState(MOTION_STATE_NEUTRAL);
		}
	}

	// ���[�V������Ԃƌ��݂̃��[�V�������r
	if (pMotion->GetType() != m_infoVisual.motionState)
	{
		// ���[�V��������ݒ�
		pMotion->Set(m_infoVisual.motionState);
	}
}

//-------------------------------------
//-	�����ڂ̍X�V����
//-------------------------------------
void CEnemyBoss::UpdateVisual(void)
{
	if (m_infoVisual.pCharacter != nullptr)
	{
		// �L�����N�^�[�̍X�V����
		m_infoVisual.pCharacter->UpdateData(
			GetPos(),
			GetRot());
	}

	if (m_infoVisual.pLife2dGage != nullptr)
	{
		m_infoVisual.pLife2dGage->UpdateInfo(
			m_infoVisual.pLife2dGage->GetPos(),
			m_infoVisual.pLife2dGage->GetSize(),
			m_infoVisual.pLife2dGage->GetColor(),
			GetLife());
	}
}

//-------------------------------------
//-	AI�X�V����
//-------------------------------------
void CEnemyBoss::UpdateAi(void)
{
	switch (m_infoAi.state)
	{
	case CEnemyBoss::AI_STATE_WAIT:

		// �ҋ@AI
		AiWait();

		break;

	case CEnemyBoss::AI_STATE_KICK_1:

		// �L�b�N�R���{AI
		AiKickCombo();

		break;

	case CEnemyBoss::AI_STATE_KICK_2:

		// �L�b�N�R���{AI
		AiKickCombo();

		break;

	case CEnemyBoss::AI_STATE_KICK_3:

		// �L�b�N�R���{AI
		AiKickCombo();

		break;

	case CEnemyBoss::AI_STATE_CHARGE:

		// �ːi
		AiCharge();

		break;
	case CEnemyBoss::AI_STATE_CHARGE_ATTACK:

		// �ːi�U��
		AiChargeAttack();

		break;
	}
}

//-------------------------------------
//- �ʏ��ԃv���C���[�̍U���̍X�V����
//-------------------------------------
void CEnemyBoss::UpdateAttack(void)
{
	// �U���̏��X�V����
	if (m_infoAttach.pAttack != nullptr)
	{
		D3DXVECTOR3 posParts = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if (m_infoVisual.pCharacter != nullptr)
		{
			if (m_infoVisual.pCharacter->GetModel(m_infoAttach.nPartsIdx) != nullptr)
			{
				// ��̈ʒu
				posParts = D3DXVECTOR3(
					m_infoVisual.pCharacter->GetModel(m_infoAttach.nPartsIdx)->GetMtxWorld()._41,
					m_infoVisual.pCharacter->GetModel(m_infoAttach.nPartsIdx)->GetMtxWorld()._42,
					m_infoVisual.pCharacter->GetModel(m_infoAttach.nPartsIdx)->GetMtxWorld()._43);
			}
		}

		m_infoAttach.pAttack->UpdateData(
			posParts,
			m_infoAttach.pAttack->GetSize());
	}
}

//-------------------------------------
//-	�ҋ@AI
//-------------------------------------
void CEnemyBoss::AiWait(void)
{
	if (m_infoAi.nCnt >= m_infoAi.nCntChange)
	{
		m_infoAi.nCnt = 0;

		// �U���ݒ菈��
		SetAiActiv();
	}
	else
	{
		m_infoAi.nCnt++;

		// �^�[�Q�b�g������
		SetRot(GetTargetRot());
		
		// �v���C���[�Ɖ���
		if (HelperSakai::IfRangeFloat(GetTargetLength(), 500.0f, 1000.0f))
		{
			// �߂Â�
			SetMoveForward(2.0f);
		}
	}
}

//-------------------------------------
//-	�L�b�NAI
//-------------------------------------
void CEnemyBoss::AiKickCombo(void)
{
	float fLength = GetTargetLength() * 0.01f;

	// �^�[�Q�b�g�������E�߂Â�
	SetRot(GetTargetRot());
	SetMoveForward(fLength);
}

//-------------------------------------
//-	�ːiAI
//-------------------------------------
void CEnemyBoss::AiCharge(void)
{
	if (HelperSakai::IfRangeFloat(GetTargetLength(), 0.0f, 200.0f))
	{
		// ��Ԑݒ�
		SetState(MOTION_STATE_CHARGE_ATTACK);
	}
	else
	{
		// �^�[�Q�b�g�������E�߂Â�
		SetRot(GetTargetRot());
		SetMoveForward(10.0f);
	}
}

//-------------------------------------
//-	�ːi�U��AI
//-------------------------------------
void CEnemyBoss::AiChargeAttack(void)
{
	if (m_infoAi.nCnt >= m_infoAi.nCntChange)
	{
		// ��Ԑݒ�
		SetState(MOTION_STATE_NEUTRAL);

		m_infoAi.nCnt = 0;
	}
	else
	{
		m_infoAi.nCnt++;

		// �߂Â�
		SetMoveForward(17.5f);
	}
}

//-------------------------------------
//-	�s��AI�ݒ菈��
//-------------------------------------
void CEnemyBoss::SetAiActiv(void)
{
	if (HelperSakai::IfRangeFloat(GetTargetLength(), 0.0f, 500.0f))
	{
		// �R���{�ݒ菈��
		SetCombo();
	}
	else if (HelperSakai::IfRangeFloat(GetTargetLength(), 700.0f, 2000.0f))
	{
		// ��Ԑݒ�
		SetState(MOTION_STATE_CHARGE);
	}
	else
	{
		// ��Ԑݒ�
		SetState(MOTION_STATE_NEUTRAL);
	}
}

//-------------------------------------
//-	�_���[�W�̍X�V����
//-------------------------------------
void CEnemyBoss::UpdateDamage(void)
{
	// �^�[�Q�b�g������
	SetRot(GetTargetRot());

	// �����
	SetMoveForward(-3.0f);
}

//-------------------------------------
//-	������΂��_���[�W�̍X�V����
//-------------------------------------
void CEnemyBoss::UpdateBigDamage(void)
{
	// �^�[�Q�b�g������
	SetRot(GetTargetRot());

	// �����
	SetMoveForward(-10.0f);
}

//-------------------------------------
//-	�R���{�ݒ菈��
//-------------------------------------
void CEnemyBoss::SetCombo(void)
{
	if (m_infoAi.bCombo == false)
	{
		// ��Ԑݒ�
		SetState(MOTION_STATE_KICK_1);
	}
	else if (m_infoAi.state == AI_STATE_KICK_1)
	{
		// ��Ԑݒ�
		SetState(MOTION_STATE_KICK_2);
	}
	else if (m_infoAi.state == AI_STATE_KICK_2)
	{
		// ��Ԑݒ�
		SetState(MOTION_STATE_KICK_3);
	}
	else if (m_infoAi.state == AI_STATE_KICK_3)
	{
		// ��Ԑݒ�
		SetState(MOTION_STATE_NEUTRAL);
	}
}

//-------------------------------------
//-	�s��AI�ݒ菈��
//-------------------------------------
void CEnemyBoss::SetAttack(int nPartsNum)
{
	if (m_infoAttach.pAttack == nullptr)
	{
		m_infoAttach.pAttack = CAttack::Create();

		if (m_infoVisual.pCharacter != nullptr)
		{
			if (m_infoVisual.pCharacter->GetModel(nPartsNum) != nullptr)
			{
				m_infoAttach.nPartsIdx = nPartsNum;

				// �̂̈ʒu
				D3DXVECTOR3 posBody = D3DXVECTOR3(
					m_infoVisual.pCharacter->GetModel(nPartsNum)->GetMtxWorld()._41,
					m_infoVisual.pCharacter->GetModel(nPartsNum)->GetMtxWorld()._42,
					m_infoVisual.pCharacter->GetModel(nPartsNum)->GetMtxWorld()._43);

				// �U���̏����ݒ菈��
				m_infoAttach.pAttack->InitSet(
					posBody,
					PARTS_SIZE,
					10,
					CMgrColl::TAG_PLAYER);
			}

		}
	}
}

//-------------------------------------
//-	�s����Ԑݒ菈��
//-------------------------------------
void CEnemyBoss::SetState(MOTION_STATE motionState)
{
	// ���݂̏�ԃ��Z�b�g����
	ReSetState();

	// ���[�V������Ԃ̐ݒ�
	m_infoVisual.motionState = motionState;
	m_infoAi.nCntChange = AI_COUNT_CHANGE[motionState];

	switch (motionState)
	{
	case CEnemyBoss::MOTION_STATE_NEUTRAL:

		m_infoAi.state = AI_STATE_WAIT;

		break;
	case CEnemyBoss::MOTION_STATE_MOVE:
		break;
	case CEnemyBoss::MOTION_STATE_KICK_1:

		m_infoAi.state = AI_STATE_KICK_1;
		m_info.state = STATE_ATTACK;
		m_infoAi.bCombo = true;
		SetAttack(PARTS_ATTACK);

		break;
	case CEnemyBoss::MOTION_STATE_KICK_2:

		m_infoAi.state = AI_STATE_KICK_2;
		m_info.state = STATE_ATTACK;
		m_infoAi.bCombo = true;
		SetAttack(PARTS_ATTACK);

		break;
	case CEnemyBoss::MOTION_STATE_KICK_3:

		m_infoAi.state = AI_STATE_KICK_3;
		m_info.state = STATE_ATTACK;
		SetAttack(PARTS_ATTACK);

		break;
	case CEnemyBoss::MOTION_STATE_CHARGE:

		m_infoAi.state = AI_STATE_CHARGE;

		break;
	case CEnemyBoss::MOTION_STATE_CHARGE_ATTACK:

		m_infoAi.state = AI_STATE_CHARGE_ATTACK;
		m_info.state = STATE_ATTACK;
		SetAttack(PARTS_ATTACK);

		break;
	case CEnemyBoss::MOTION_STATE_DAMAGE:

		m_info.state = STATE_DAMAGE;

		if (m_infoVisual.pCharacter != nullptr)
		{
			m_infoVisual.pCharacter->SetColorAll(D3DXCOLOR(1.0f, 0.0f, 0.0, 1.0f));
		}

		break;
	case CEnemyBoss::MOTION_STATE_BIG_DAMAGE:

		m_info.state = STATE_BIG_DAMAGE;

		if (m_infoVisual.pCharacter != nullptr)
		{
			m_infoVisual.pCharacter->SetColorAll(D3DXCOLOR(1.0f, 0.0f, 0.0, 1.0f));
		}

		break;
	}
}

//-------------------------------------
//-	���݂̏�ԃ��Z�b�g����
//-------------------------------------
void CEnemyBoss::ReSetState(void)
{
	m_infoAi.nCnt = 0;
	m_infoAi.nCntChange = 0;
	m_infoAi.bCombo = false;
	m_info.state = STATE_NORMAL;
	m_infoAi.state = AI_STATE_WAIT;

	if (m_infoVisual.pCharacter != nullptr)
	{
		m_infoVisual.pCharacter->SetColorAll(D3DXCOLOR(1.0f, 1.0f, 1.0, 1.0f));
	}
	
	if (m_infoAttach.pAttack != nullptr)
	{
		// �I������
		m_infoAttach.pAttack->Uninit();
		m_infoAttach.pAttack = nullptr;
	}
}

//-------------------------------------
//- �v���C���[�̃f�o�b�N�\��
//-------------------------------------
void CEnemyBoss::Debug(void)
{
	// �f�o�b�N�v���b�N�̎擾
	CDebugProc* pDebugProc = CManager::GetInstance()->GetDbugProc();

	// �f�o�b�N�v���b�N�擾�̗L���𔻒�
	if (pDebugProc == NULL)
	{
		return;
	}

	pDebugProc->Print("\n");
	pDebugProc->Print("�v���C���[�̂Ƃ̋���");
	pDebugProc->Print("\n");
	pDebugProc->Print("%f,%f,%f", GetRot().x, GetRot().y, GetRot().z);
	pDebugProc->Print("\n");

}