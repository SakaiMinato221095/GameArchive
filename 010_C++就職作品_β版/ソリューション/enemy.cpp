
//-===============================================
//-
//-	�G�̏���[enemy.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "enemy.h"

#include "renderer.h"
#include "manager.h"

#include "helper_sakai.h"

#include "fade.h"

#include "coll.h"

#include "particle.h"

#include "player.h"
#include "game.h"

#include "helper_sakai.h"

#include "spwan_wall.h"

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
//-	�G�̃R���X�g���N�^
//-------------------------------------
CEnemy::CEnemy()
{
	m_pColl = NULL;

	ZeroMemory(&m_data, sizeof(m_data));
	ZeroMemory(&m_infoTarger, sizeof(m_infoTarger));
}

//-------------------------------------
//-	�G�̃f�X�g���N�^
//-------------------------------------
CEnemy::~CEnemy()
{

}

//-------------------------------------
//- �G�̏���������
//-------------------------------------
HRESULT CEnemy::Init(void)
{
	if (m_pColl == NULL)
	{
		// �����蔻��ݒ�
		m_pColl = CColl::Create(
			CMgrColl::TAG_ENEMY,
			this,
			m_data.pos,
			m_data.size);
	}
	else
	{
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �G�̏I������
//-------------------------------------
void CEnemy::Uninit(void)
{
	if (m_pColl != NULL)
	{
		// �����蔻��̏I������
		m_pColl->Uninit();
		delete m_pColl;
		m_pColl = NULL;
	}

	// �������g�̃|�C���^�̊J��
	Release();
}

//-------------------------------------
//- �G�̍X�V����
//-------------------------------------
void CEnemy::Update(void)
{
	// �ʒu�X�V����
	UpdatePos();

	// �^�[�Q�b�g�Ƃ̏��X�V����
	UpdateTargetPlayer();

	// �����蔻��X�V����
	UpdateCollision();
}

//-------------------------------------
//- �G�̕`�揈��
//-------------------------------------
void CEnemy::Draw(void)
{

}

//-------------------------------------
//- �ʏ�G�̐�������
//-------------------------------------
CEnemy * CEnemy::Create(void)
{
	// �ʏ�G�̐���
	CEnemy *pEnemy = DBG_NEW CEnemy;

	// �����̐����̗L���𔻒�
	if (pEnemy != NULL)
	{
		// ����������
		if (FAILED(pEnemy->Init()))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pEnemy == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �ʏ�G�̃|�C���^��Ԃ�
	return pEnemy;
}

//-------------------------------------
//- �ʏ�G�̐ڐG�_���[�W����
//-------------------------------------
void CEnemy::HitDamage(int nDamage)
{
	// �_���[�W����
	Damage(nDamage);
}

//-------------------------------------
//-	�G�̃��f���̏����ݒ�
//-------------------------------------
void CEnemy::SetInit(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	// �f�[�^�̑��
	m_data.pos = pos;										// �ʒu
	m_data.rot = rot;										// ����
	m_data.size = D3DXVECTOR3(40.0f, 200.0f, 40.0f);		// �T�C�Y

	m_data.nLife = nLife;
}

//-------------------------------------
//- �ʏ�G�̃_���[�W����
//-------------------------------------
void CEnemy::Damage(int nDamage)
{
	m_data.nLife -= nDamage;
	m_data.bHit = true;
}

//-------------------------------------
//- �ʏ�G�̎��S����
//-------------------------------------
bool CEnemy::Dead(void)
{
	if (GetLife() <= 0)
	{
		if (GetIsPhaseTarget())
		{
			// �^�[�Q�b�g�̌��j�����Z����
			AddDeadNum();

			return true;
		}
	}

	return false;
}

//-------------------------------------
//- �ʏ�G�̌��j�����Z����
//-------------------------------------
void CEnemy::AddDeadNum(void)
{
	CPhaseManager* pPhaseManager = CGame::GetPhaseManager();

	if (pPhaseManager != nullptr)
	{
		pPhaseManager->AddDeadEnemy();
	}
}

//-------------------------------------
//- �v���C���[�̈ړ�����
//-------------------------------------
void CEnemy::UpdatePos(void)
{
	// �ʒu���Ɉړ��ʂ����Z
	m_data.pos += m_data.move;

	// �ړ��ʂ�����
	m_data.move.x += (0.0f - m_data.move.x) * 0.3f;
	m_data.move.z += (0.0f - m_data.move.z) * 0.3f;
}


//-------------------------------------
//-	�v���C���[�^�[�Q�b�g����
//-------------------------------------
void CEnemy::UpdateTargetPlayer(void)
{
	// �v���C���[�̏��擾
	CPlayer* pPlayer = CGame::GetPlayer();

	// �v���C���[�̏��擾�̐����𔻒�
	if (pPlayer == NULL)
	{// ���s��

		// �ǔ������𔲂���
		return;
	}

	// �^�[�Q�b�g�̈ʒu
	D3DXVECTOR3 posTgt = pPlayer->GetData().pos;

	// �^�[�Q�b�g�ւ̌������Z�o
	m_infoTarger.rot.y = atan2f(GetPos().x - posTgt.x, GetPos().z - posTgt.z);

	// �^�[�Q�b�g�Ƃ̋������Z�o
	m_infoTarger.fLength = HelperSakai::CalculateLength(GetPos(), posTgt);
}

//-------------------------------------
//- �ǂƂ̓����蔻��X�V����
//-------------------------------------
void CEnemy::UpdateCollision(void)
{
	if (m_pColl != nullptr)
	{
		// �����蔻��̏��X�V����
		m_pColl->UpdateData(
			m_data.pos,
			m_data.size);

		// �ǂƂ̓����蔻��
		if (m_pColl->HitSide(CMgrColl::TAG_WALL_X, CMgrColl::EVENT_TYPE_PRESS, CMgrColl::TYPE_SXIS_X) == true)
		{
			// �ړ��ʂ��Ȃ���
			m_data.move.x = 0.0f;

			// �v���C���[��Y���W�ړ����~
			m_data.pos.x = m_data.posOld.x;
		}

		// �ǂƂ̓����蔻��
		if (m_pColl->HitSide(CMgrColl::TAG_WALL_Z, CMgrColl::EVENT_TYPE_PRESS, CMgrColl::TYPE_SXIS_Z) == true)
		{
			// �ړ��ʂ��Ȃ���
			m_data.move.z = 0.0f;

			// �v���C���[��Y���W�ړ����~
			m_data.pos.z = m_data.posOld.z;
		}
	}
}

//-------------------------------------
//- �v���C���[�Ƃ̓����蔻��X�V����
//-------------------------------------
void CEnemy::UpdateCollisionPlayer(void)
{
	if (m_pColl != nullptr)
	{
		// �����蔻��̏��X�V����
		m_pColl->UpdateData(
			m_data.pos,
			m_data.size);

		if (m_pColl->Hit(CMgrColl::TAG_PLAYER, CMgrColl::EVENT_TYPE_PRESS) == true)
		{
			float fSpeed = -5.0f;

			if (HelperSakai::IfRangeFloat(GetTargetLength(),0.0f,10.0f))
			{
				fSpeed *= 5.0f;
			}
			else if (HelperSakai::IfRangeFloat(GetTargetLength(), 10.0f, 50.0f))
			{
				fSpeed *= 3.0f;
			}
			else if (HelperSakai::IfRangeFloat(GetTargetLength(), 50.0f, 100.0f))
			{
				fSpeed *= 2.0f;
			}

			// �^�[�Q�b�g���痣���
			SetRot(GetTargetRot());
			SetMoveForward(fSpeed);

		}
	}
}