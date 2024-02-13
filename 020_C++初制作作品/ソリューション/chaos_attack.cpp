
//-===============================================
//-
//-	�ł̍U���̏���[chaos_attack.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "chaos_attack.h"

#include "renderer.h"
#include "manager.h"
#include "game.h"

#include "sound.h"

#include "time_stop.h"

#include "enemy_normal.h"
#include "enemy_boss.h"

#include "hit.h"

#include "object_col.h"

#include "effect.h"
#include "particle.h"

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
//-	�ł̍U���̃R���X�g���N�^
//-------------------------------------
CChaosAttack::CChaosAttack(int nPriority) : CObject(nPriority)
{
	ZeroMemory(&m_aCol, sizeof(m_aCol[COLLISION_NUM_MAX]));

	for (int nCount = 0; nCount < ENEMY_NORMAL_NUM_MAX; nCount++)
	{
		m_aEnemyDamageCut[nCount] = 0;
	}

	m_nEnemyBossDmageCut = 0;

	m_nDamageTime.Set(10);
}

//-------------------------------------
//-	�ł̍U���̃f�X�g���N�^
//-------------------------------------
CChaosAttack::~CChaosAttack()
{

}

//-------------------------------------
//- �ł̍U���̏���������
//-------------------------------------
HRESULT CChaosAttack::Init(void)
{
	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �ł̍U���̏I������
//-------------------------------------
void CChaosAttack::Uninit(void)
{
	// �T�E���h�̃|�C���^��錾
	CSound *pSound = CManager::GetSound();

	// �T�E���h�̏��擾�̐����𔻒�
	if (pSound == NULL)
	{
		// �����𔲂���
		return;
	}

	// ���ʉ�BGM�̍Đ��i�ł̍U��000�j
	pSound->Stop(CSound::LABEL_BGM_CHAOS_CHARGE_SHOT);

	// �������g�̃|�C���^�̊J��
	Release();
}

//-------------------------------------
//- �ł̍U���̍X�V����
//-------------------------------------
void CChaosAttack::Update(void)
{
	// �G�̓����蔻��
	CollisionEnemy();

	Add();

	Sub();
}

//-------------------------------------
//- �ł̍U���̕`�揈��
//-------------------------------------
void CChaosAttack::Draw(void)
{

}

//-------------------------------------
//- �ł̍U���̐ݒ菈��
//-------------------------------------
void CChaosAttack::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nDamage)
{
	// ���ݒ�
	m_dataPos.Set(pos);			// �ʒu
	m_dataRot.Set(rot);			// ����
	m_nDataDamage.Set(nDamage);	// �_���[�W

	// �����ݒ菈��
	InitSet();
}

//-------------------------------------
//- �ł̍U���̐�������
//-------------------------------------
CChaosAttack *CChaosAttack::Create()
{
	// �ł̍U���̐���
	CChaosAttack *pCChaosAttack = DBG_NEW CChaosAttack;

	// �����̐����̗L���𔻒�
	if (pCChaosAttack != NULL)
	{
		// ����������
		if (FAILED(pCChaosAttack->Init()))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCChaosAttack == NULL)
	{// ���s��

	 // �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// ��ނ�ݒ�
	pCChaosAttack->SetType(TYPE_ENEMY);

	// �ł̍U���̃|�C���^��Ԃ�
	return pCChaosAttack;
}

///-------------------------------------
//- �ł̍U���̉��Z����
//-------------------------------------
void CChaosAttack::Add(void)
{
	for (int nCount = 0; nCount < COLLISION_NUM_MAX; nCount++)
	{
		// �ϐ��錾�i���擾�j
		D3DXVECTOR3 pos = m_aCol[nCount].pos;		// �ʒu
		D3DXVECTOR3 size = m_aCol[nCount].size;		// �傫��
		D3DXVECTOR3 rot = m_dataRot.Get();			// ����

		CParticle::SetRange(
			12,
			size,
			rot,
			pos,
			D3DXVECTOR3(10.0f,10.0f,10.0f),
			D3DXVECTOR3(0.0f, 5.0f, 0.0f),
			D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
			10);
	}
}

//-------------------------------------
//- �ł̍U���̌��Z����
//-------------------------------------
void CChaosAttack::Sub(void)
{
	for (int nCutEnemy = 0; nCutEnemy < ENEMY_NORMAL_NUM_MAX; nCutEnemy++)
	{
		// ���݂̔ԍ��̒ʏ�G�̎擾����
		CEnemyNormal *pEnemy = CManagerObject::GetEnemyNormal(nCutEnemy);

		// �ʏ�G�̗L���𔻒�
		if (pEnemy != NULL)
		{
			// �G�̃_���[�W�J�E���g�𔻒�
			if (m_aEnemyDamageCut[nCutEnemy] != 0)
			{
				m_aEnemyDamageCut[nCutEnemy]--;
			}
		}
	}

	CEnemyBoss *pEnemyBoss = CManagerObject::GetEnemyBoss();

	// �ʏ�G�̗L���𔻒�
	if (pEnemyBoss != NULL)
	{
		// �G�̃_���[�W�J�E���g�𔻒�
		if (m_nEnemyBossDmageCut != 0)
		{
			m_nEnemyBossDmageCut--;
		}
	}
}

//-------------------------------------
//- �ł̍U���̓G�Ƃ̓����蔻�菈��
//-------------------------------------
bool CChaosAttack::CollisionEnemy(void)
{
	// �ϐ��錾�i���擾�j
	int nDamage = m_nDataDamage.Get();		// �_���[�W�l

	for (int nCutEnemy = 0; nCutEnemy < ENEMY_NORMAL_NUM_MAX; nCutEnemy++)
	{
		// ���݂̔ԍ��̒ʏ�G�̎擾����
		CEnemyNormal *pEnemy = CManagerObject::GetEnemyNormal(nCutEnemy);

		// �ʏ�G�̗L���𔻒�
		if (pEnemy != NULL)
		{
			for (int nCutCol = 0; nCutCol < COLLISION_NUM_MAX; nCutCol++)
			{
				// �ϐ��錾�i���擾�j
				D3DXVECTOR3 pos = m_aCol[nCutCol].pos;		// �ʒu
				D3DXVECTOR3 size = m_aCol[nCutCol].size;	// �傫��
				D3DXVECTOR3 rot = m_dataRot.Get();			// ����

				// �ϐ��錾�i���擾�j
				D3DXVECTOR3 enemyPos = pEnemy->m_dataPos.Get();		// �ʒu
				D3DXVECTOR3 enemySize = pEnemy->m_dataSize.Get();	// �傫��
				D3DXVECTOR3 enemyRot = pEnemy->m_dataRot.Get();		// ����

				// ��`�̓����蔻��
				if (CHit::hitRectangleRot(pos, size,rot,enemyPos, enemySize,enemyRot) == true)
				{
					// �G�̃_���[�W�J�E���g�𔻒�
					if (m_aEnemyDamageCut[nCutEnemy] == 0)
					{
						// �G�Ƀ_���[�W�J�E���g��ݒ�
						m_aEnemyDamageCut[nCutEnemy] = m_nDamageTime.Get();

						// �G�l�~�[�̃_���[�W����
						pEnemy->Hit(nCutEnemy, nDamage);
					}
				}
			}

		}
	}

	// �{�X�G�̎擾����
	CEnemyBoss *pEnemyBoss = CManagerObject::GetEnemyBoss();

	if (pEnemyBoss != NULL)
	{
		for (int nCutCol = 0; nCutCol < COLLISION_NUM_MAX; nCutCol++)
		{
			// �ϐ��錾�i���擾�j
			D3DXVECTOR3 pos = m_aCol[nCutCol].pos;		// �ʒu
			D3DXVECTOR3 size = m_aCol[nCutCol].size;	// �傫��
			D3DXVECTOR3 rot = m_dataRot.Get();			// ����

			// �ϐ��錾�i�{�X�G�̏��擾�j
			D3DXVECTOR3 enemyPos = pEnemyBoss->m_dataPos.Get();		// �ʒu
			D3DXVECTOR3 enemySize = pEnemyBoss->m_dataSize.Get();	// �傫��
			D3DXVECTOR3 enemyRot = pEnemyBoss->m_dataRot.Get();		// ����

			// ��`�̓����蔻��
			if (CHit::hitRectangleRot(pos, size, rot,enemyPos, enemySize, enemyRot) == true)
			{
				// �G�̃_���[�W�J�E���g�𔻒�
				if (m_nEnemyBossDmageCut == 0)
				{
					// �G�Ƀ_���[�W�J�E���g��ݒ�
					m_nEnemyBossDmageCut = m_nDamageTime.Get();

					// �G�l�~�[�̃_���[�W����
					pEnemyBoss->Hit(nDamage);
				}
			}
		}
	}

	// �u�Ȃ��v��Ԃ�
	return false;
}

//-------------------------------------
//- �ł̍U���̏����ݒ菈��
//-------------------------------------
void CChaosAttack::InitSet(void)
{
	// �T�E���h�̃|�C���^��錾
	CSound *pSound = CManager::GetSound();

	// �T�E���h�̏��擾�̐����𔻒�
	if (pSound == NULL)
	{
		// �����𔲂���
		return;
	}

	// ���ʉ�BGM�̍Đ��i�ł̍U��000�j
	pSound->Play(CSound::LABEL_BGM_CHAOS_CHARGE_SHOT);

	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();	// �ʒu
	D3DXVECTOR3 rot = m_dataRot.Get();	// ����

	float fdata0 = sinf(rot.y) * 1.0f;
	float fdata1 = cosf(rot.y) * 1.0f;

	m_aCol[0].pos = D3DXVECTOR3(pos.x + (sinf(rot.y) * -50.0f), 125.0f, pos.z + (cosf(rot.y) * -10.0f));
	m_aCol[0].size = D3DXVECTOR3(50.0f, 0.0f, 50.0f);

	m_aCol[1].pos = D3DXVECTOR3(pos.x + (sinf(rot.y) * -100.0f), 125.0f, pos.z + (cosf(rot.y) * -100.0f));
	m_aCol[1].size = D3DXVECTOR3(100.0f, 0.0f, 50.0f);

	m_aCol[2].pos = D3DXVECTOR3(pos.x + (sinf(rot.y) * -200.0f), 125.0f, pos.z + (cosf(rot.y) * -200.0f));
	m_aCol[2].size = D3DXVECTOR3(150.0f, 0.0f, 50.0f);

	m_aCol[3].pos = D3DXVECTOR3(pos.x + (sinf(rot.y) * -300.0f), 125.0f, pos.z + (cosf(rot.y) * -300.0f));
	m_aCol[3].size = D3DXVECTOR3(200.0f, 0.0f, 50.0f);
}