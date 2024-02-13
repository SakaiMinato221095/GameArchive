
//-===============================================
//-
//-	�G���G�̏���[enemy_minion.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "enemy_minion.h"

#include "character.h"
#include "billboard_gage.h"

#include "renderer.h"
#include "manager.h"

#include "debugproc.h"
#include "helper_sakai.h"

#include "manager_model.h"
#include "manager_texture.h"

#include "coll.h"

#include "particle.h"

#include "attack.h"
#include "charge.h"


#include "game.h"

#include "spwan_wall.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�R���X�g��`
//=======================================

const int PARTS_BODY = 0;
const int PARTS_FOOT_R = 3;
const int PARTS_FOOT_L = 4;

const D3DXVECTOR3 PARTS_POS[5]
{
	D3DXVECTOR3(0.0f,0.0f,0.0f),
	D3DXVECTOR3(0.0f,0.0f,0.0f),
	D3DXVECTOR3(0.0f,0.0f,0.0f),
	D3DXVECTOR3(0.0f,0.0f,0.0f),
	D3DXVECTOR3(0.0f,0.0f,0.0f),
};

const D3DXVECTOR3 PARTS_SIZE[5]
{
	D3DXVECTOR3(50.0f,30.0f,50.0f),
	D3DXVECTOR3(25.0f,100.0f,25.0f),
	D3DXVECTOR3(25.0f,100.0f,25.0f),
	D3DXVECTOR3(20.0f,20.0f,20.0f),
	D3DXVECTOR3(20.0f,20.0f,20.0f),
};

const int AI_COUNT_CHANGE[CEnemyMinion::MOTION_STATE_MAX]
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

const char* pTexture[CEnemyMinion::TEX_MAX]
{
	nullptr,
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

int CEnemyMinion::m_nTextureNldx[CEnemyMinion::TEX_MAX] = {};

//-------------------------------------
//- �G�t�F�N�g�̃e�N�X�`���̓ǂݍ���
//-------------------------------------
HRESULT CEnemyMinion::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

	 // �����������𔲂���
		return E_FAIL;
	}

	// �e�N�X�`���Ǘ��̐���
	CManagerTexture* pManagerTexture = CManager::GetInstance()->GetManagerTexture();

	// �e�N�X�`���Ǘ��̗L���𔻒�
	if (pManagerTexture == NULL)
	{
		// �����������𔲂���
		return E_FAIL;
	}

	// �e�N�X�`���ݒ�
	for (int nCount = 0; nCount < TEX_MAX; nCount++)
	{
		// �e�N�X�`���ԍ��̎擾�i�e�N�X�`���̊����j
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTexture[nCount]);

		// �e�N�X�`���̓ǂݍ��ݐ����̗L�����m�F
		if (m_nTextureNldx[nCount] == -1)
		{
			// ���s���ɏ����������𔲂���
			return E_FAIL;
		}
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �G�t�F�N�g�̓ǂݍ��񂾃e�N�X�`���̔j��
//-------------------------------------
void CEnemyMinion::Unload(void)
{

}

//-------------------------------------
//-	�G�̃R���X�g���N�^
//-------------------------------------
CEnemyMinion::CEnemyMinion()
{
	ZeroMemory(&m_info, sizeof(m_info));
	ZeroMemory(&m_infoVisual, sizeof(m_infoVisual));
	ZeroMemory(&m_infoAi, sizeof(m_infoAi));
	ZeroMemory(&m_infoAttach, sizeof(m_infoAttach));
}

//-------------------------------------
//-	�G�̃f�X�g���N�^
//-------------------------------------
CEnemyMinion::~CEnemyMinion()
{

}

//-------------------------------------
//- �G�̏���������
//-------------------------------------
HRESULT CEnemyMinion::Init(CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType)
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
			SetState(CEnemyMinion::MOTION_STATE_NEUTRAL);
		}
		else
		{
			return E_FAIL;
		}
	}

	if (m_infoVisual.pLifeBillGage == nullptr)
	{
		// �L�����N�^�[�̐�������
		m_infoVisual.pLifeBillGage = CBillboardGage::Create();

		if (m_infoVisual.pLifeBillGage == nullptr)
		{
			return E_FAIL;
		}
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �G�̏I������
//-------------------------------------
void CEnemyMinion::Uninit(void)
{
	if (m_infoVisual.pCharacter != nullptr)
	{
		m_infoVisual.pCharacter->Uninit();
		m_infoVisual.pCharacter = nullptr;
	}

	if (m_infoVisual.pLifeBillGage != nullptr)
	{
		m_infoVisual.pLifeBillGage->Uninit();
		m_infoVisual.pLifeBillGage = nullptr;
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
void CEnemyMinion::Update(void)
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

	if (m_infoAi.state != AI_STATE_KICK_1)
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
void CEnemyMinion::Draw(void)
{
	// X�t�@�C���I�u�W�F�N�g�̕`�揈��
	CEnemy::Draw();
}

//-------------------------------------
//- �ʏ�G�̐�������
//-------------------------------------
CEnemyMinion* CEnemyMinion::Create(CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType)
{
	// �ʏ�G�̐���
	CEnemyMinion* pEnemyWeak = DBG_NEW CEnemyMinion;

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
void CEnemyMinion::HitDamage(int nDamage)
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
void CEnemyMinion::SetInit(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, int nMaxLife)
{
	CEnemy::SetInit(pos, rot, nLife);

	if (m_infoVisual.pCharacter != nullptr)
	{
		// �L�����N�^�[�̐�������
		m_infoVisual.pCharacter->UpdateData(pos, rot);
	}

	if (m_infoVisual.pLifeBillGage != nullptr)
	{
		m_infoVisual.pLifeBillGage->SetInit(
			GetPos() + D3DXVECTOR3(0.0f, 30.0f, 0.0f),
			D3DXVECTOR3(50.0f,10.0f,0.0f),
			D3DXCOLOR(1.0f, 0.0f, 0.0f,1.0f),
			nLife,
			nMaxLife);
	}
}

//-------------------------------------
//-	���[�V�����̍X�V����
//-------------------------------------
void CEnemyMinion::UpdateMotion(void)
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
			// �ʏ��ԂɕύX
			SetState(MOTION_STATE_NEUTRAL);
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
void CEnemyMinion::UpdateVisual(void)
{
	if (m_infoVisual.pCharacter != nullptr)
	{
		// �L�����N�^�[�̍X�V����
		m_infoVisual.pCharacter->UpdateData(
			GetPos(),
			GetRot());
	}

	if (m_infoVisual.pLifeBillGage != nullptr)
	{
		m_infoVisual.pLifeBillGage->UpdateInfo(
			GetPos() + D3DXVECTOR3(0.0f, 150.0f, 0.0f),
			m_infoVisual.pLifeBillGage->GetSize(),
			m_infoVisual.pLifeBillGage->GetColor(),
			GetLife());
	}
}

//-------------------------------------
//-	AI�X�V����
//-------------------------------------
void CEnemyMinion::UpdateAi(void)
{
	switch (m_infoAi.state)
	{
	case CEnemyMinion::AI_STATE_WAIT:

		// �ҋ@AI
		AiWait();

		break;

	case CEnemyMinion::AI_STATE_KICK_1:

		// �L�b�N�R���{AI
		AiKickCombo();

		break;

	case CEnemyMinion::AI_STATE_CHARGE:

		// �ːi
		AiCharge();

		break;
	}
}

//-------------------------------------
//- �ʏ��ԃv���C���[�̍U���̍X�V����
//-------------------------------------
void CEnemyMinion::UpdateAttack(void)
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
			posParts + PARTS_POS[m_infoAttach.nPartsIdx],
			m_infoAttach.pAttack->GetSize());
	}
}

//-------------------------------------
//-	�ҋ@AI
//-------------------------------------
void CEnemyMinion::AiWait(void)
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
void CEnemyMinion::AiKickCombo(void)
{
	float fLength = GetTargetLength() * 0.03f;

	// �^�[�Q�b�g�������E�߂Â�
	SetRot(GetTargetRot());
	SetMoveForward(fLength);
}

//-------------------------------------
//-	�ːiAI
//-------------------------------------
void CEnemyMinion::AiCharge(void)
{
	if (HelperSakai::IfRangeFloat(GetTargetLength(), 0.0f, 200.0f))
	{
		// ��Ԑݒ�
		SetAiActiv();
	}
	else
	{
		// �^�[�Q�b�g�������E�߂Â�
		SetRot(GetTargetRot());
		SetMoveForward(10.0f);
	}
}

//-------------------------------------
//-	�s��AI�ݒ菈��
//-------------------------------------
void CEnemyMinion::SetAiActiv(void)
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
void CEnemyMinion::UpdateDamage(void)
{
	// �^�[�Q�b�g������
	SetRot(GetTargetRot());

	// �����
	SetMoveForward(-3.0f);
}

//-------------------------------------
//-	������΂��_���[�W�̍X�V����
//-------------------------------------
void CEnemyMinion::UpdateBigDamage(void)
{
	// �^�[�Q�b�g������
	SetRot(GetTargetRot());

	// �����
	SetMoveForward(-10.0f);
}

//-------------------------------------
//-	�R���{�ݒ菈��
//-------------------------------------
void CEnemyMinion::SetCombo(void)
{
	// ��Ԑݒ�
	SetState(MOTION_STATE_KICK_1);
}

//-------------------------------------
//-	�s��AI�ݒ菈��
//-------------------------------------
void CEnemyMinion::SetAttack(int nPartsNum)
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
					posBody + PARTS_POS[nPartsNum],
					PARTS_SIZE[nPartsNum],
					10,
					CMgrColl::TAG_PLAYER);
			}

		}
	}
}

//-------------------------------------
//-	�s����Ԑݒ菈��
//-------------------------------------
void CEnemyMinion::SetState(MOTION_STATE motionState)
{
	// ���݂̏�ԃ��Z�b�g����
	ReSetState();

	// ���[�V������Ԃ̐ݒ�
	m_infoVisual.motionState = motionState;
	m_infoAi.nCntChange = AI_COUNT_CHANGE[motionState];

	switch (motionState)
	{
	case CEnemyMinion::MOTION_STATE_NEUTRAL:

		m_infoAi.state = AI_STATE_WAIT;
		m_info.state = STATE_NORMAL;

		break;
	case CEnemyMinion::MOTION_STATE_MOVE:
		break;
	case CEnemyMinion::MOTION_STATE_KICK_1:

		m_infoAi.state = AI_STATE_KICK_1;
		m_info.state = STATE_ATTACK;
		SetAttack(PARTS_FOOT_L);

		break;

	case CEnemyMinion::MOTION_STATE_CHARGE:

		m_infoAi.state = AI_STATE_CHARGE;
		m_info.state = STATE_NORMAL;

		break;

	case CEnemyMinion::MOTION_STATE_DAMAGE:

		m_info.state = STATE_DAMAGE;

		if (m_infoVisual.pCharacter != nullptr)
		{
			m_infoVisual.pCharacter->SetColorAll(D3DXCOLOR(1.0f, 0.0f, 0.0, 1.0f));
		}

		break;
	case CEnemyMinion::MOTION_STATE_BIG_DAMAGE:

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
void CEnemyMinion::ReSetState(void)
{
	m_infoAi.nCnt = 0;
	m_infoAi.nCntChange = 0;
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
void CEnemyMinion::Debug(void)
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