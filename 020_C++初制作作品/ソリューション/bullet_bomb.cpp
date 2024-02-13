
//-===============================================
//-
//-	�����e�̏���[bullet_bomb.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "bullet_bomb.h"

#include "renderer.h"
#include "manager.h"

#include "time_stop.h"

#include "effect.h"

#include "manager_object.h"
#include "objectx_none.h"
#include "event_object.h"

#include "enemy_normal.h"
#include "enemy_boss.h"

#include "hit.h"

//-======================================
//-	�}�N����`
//-======================================

#define ENEMY_BOSS_NUM	(-1)		// �{�X�p�̔ԍ�
#define BLAST_DAMAGE	(5)			// �����_���[�W
#define BLAST_RANGE		(800.0f)	// �����͈�

#define BLT_BOMB_EFCT_SIZE	(10.0f)									// �����e�̃G�t�F�N�g�̃T�C�Y
#define BLT_BOMB_EFCT_LIFE	(30)									// �����e�̃G�t�F�N�g�̗̑�
#define BLT_BOMB_EFCT_COLOR	(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f))		// �����e�̃G�t�F�N�g�̐F

//=======================================
//= �R���X�g��`
//=======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	�����e�̃R���X�g���N�^
//-------------------------------------
CBulletBomb::CBulletBomb(int nPriority) : CBullet(nPriority)
{

}

//-------------------------------------
//-	�����e�̃f�X�g���N�^
//-------------------------------------
CBulletBomb::~CBulletBomb()
{

}

//-------------------------------------
//- �����e�̏���������
//-------------------------------------
HRESULT CBulletBomb::Init(TEX tex)
{
	// �e�̏�����
	CBullet::Init(tex);

	// �����ݒ菈��
	InitSet();

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �����e�̏I������
//-------------------------------------
void CBulletBomb::Uninit(void)
{
	// �e�̏I��
	CBullet::Uninit();
}

//-------------------------------------
//- �����e�̍X�V����
//-------------------------------------
void CBulletBomb::Update(void)
{
	// �ړ�����
	Move();

	// ���Z����
	Add();

	// �G�Ƃ̓����蔻�菈��
	if (CollisionEnemy() == true ||
		CollisionObject() == true)
	{
		return;
	}

	// ���Z����
	if (Sub() == true)
	{
		return;
	}

	// �r���{�[�h�I�u�W�F�N�g�̍X�V����
	CObjectBillboard::Update();
}

//-------------------------------------
//- �����e�̕`�揈��
//-------------------------------------
void CBulletBomb::Draw(void)
{
	// �f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pRenderer == NULL)
	{// ���s��

		// �����������𔲂���
		return;
	}

	// Z�e�X�g�̐ݒ�
	pRenderer->SetZTest(true);

	// �A���t�@�e�X�g�̐ݒ�
	pRenderer->SetAlphaTest(true);

	// �����e�̕`�揈��
	CBullet::Draw();

	// Z�e�X�g�̉���
	pRenderer->SetZTest(false);

	// �A���t�@�e�X�g�̉���
	pRenderer->SetAlphaTest(false);
}

//-------------------------------------
//- �����e�̐�������
//-------------------------------------
CBulletBomb *CBulletBomb::Create(TEX tex)
{
	// �����e�̐���
	CBulletBomb *pCBulletBomb = DBG_NEW CBulletBomb(5);

	// �����̐����̗L���𔻒�
	if (pCBulletBomb != NULL)
	{
		// ����������
		if (FAILED(pCBulletBomb->Init(tex)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCBulletBomb == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// ��ނ�ݒ�
	pCBulletBomb->SetType(TYPE_BULLET);

	// �����e�̃|�C���^��Ԃ�
	return pCBulletBomb;
}

//-------------------------------------
//- �����e�̏����ݒ菈��
//-------------------------------------
void CBulletBomb::InitSet(void)
{
	m_nDataBlastDamage.Set(BLAST_DAMAGE);	// �����_���[�W
}

//-------------------------------------
//- �����e�̈ړ�����
//-------------------------------------
void CBulletBomb::Move(void)
{
	// ���ԊǗ��̏����擾
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// ���ԊǗ��擾�̗L���𔻒�
	if (pManagerTime == NULL)
	{
		// �����𔲂���
		return;
	}

	// �ϐ���錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();		// �ʒu���
	D3DXVECTOR3 move = m_dataMove.Get();	// �ړ���

	// ���Ԕ{���̌v�Z
	D3DXVECTOR3 moveTime = pManagerTime->CalRate(move);

	// �ʒu���X�V
	pos += moveTime;

	// ���X�V
	m_dataPos.Set(pos);		// �ʒu���
	m_dataMove.Set(move);	// �ړ���
}

//-------------------------------------
//- �����e�̉��Z����
//-------------------------------------
void CBulletBomb::Add(void)
{
	// ���ԊǗ��̏����擾
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// ���ԊǗ��擾�̗L���𔻒�
	if (pManagerTime == NULL)
	{
		// �����𔲂���
		return;
	}

	// �����J�E���g�̗L���𔻒�
	if (pManagerTime->m_bDataIntCount.Get() == true)
	{
		// �ϐ���錾�i���擾�j
		D3DXVECTOR3 pos = m_dataPos.Get();		// �ʒu���

		// �G�t�F�N�g�̐���
		CEffect *pEffect = CEffect::Create(CEffect::TEX_NORMAL_000);

		// �G�t�F�N�g�̗L���𔻒�
		if (pEffect != NULL)
		{
			// �ʒu����ݒ�
			pEffect->m_dataPos.Set(pos);

			// �傫����ݒ�
			pEffect->m_dataSize.Set(D3DXVECTOR3(BLT_BOMB_EFCT_SIZE, BLT_BOMB_EFCT_SIZE, 0.0f));

			// �ړ��ʂ�ݒ�
			pEffect->m_dataMove.Set();

			// �F��ݒ�
			pEffect->m_dataColor.Set(BLT_BOMB_EFCT_COLOR);

			// �G�t�F�N�g�̐ݒ菈��
			pEffect->m_nDataLife.Set(BLT_BOMB_EFCT_LIFE);
		}
	}
}

//-------------------------------------
//- �����e�̌��Z����
//-------------------------------------
bool CBulletBomb::Sub(void)
{
	// ���ԊǗ��̏����擾
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// ���ԊǗ��擾�̗L���𔻒�
	if (pManagerTime == NULL)
	{
		// �����𔲂���
		return false;
	}

	// �ϐ��錾�i���擾�j
	int nLife = m_nDataLife.Get();	// �̗�

	// �����J�E���g�̗L���𔻒�
	if (pManagerTime->m_bDataIntCount.Get() == true)
	{
		// �̗͂����炷
		nLife--;
	}

	// �̗͂̔���
	if (nLife <= 0)
	{
		// �I������
		Uninit();

		// ������Ԃ�
		return true;
	}

	// �����X�V
	m_nDataLife.Set(nLife);		// �̗�

	// ���s��Ԃ�
	return false;
}

//-------------------------------------
//- �����e�̓G�Ƃ̓����蔻�菈��
//-------------------------------------
bool CBulletBomb::CollisionEnemy(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();		// �ʒu
	D3DXVECTOR3 size = m_dataSize.Get();	// �傫��

	int nDamage = m_nDataDamage.Get();		// �_���[�W�l

	for (int nCutEnemy = 0; nCutEnemy < ENEMY_NORMAL_NUM_MAX; nCutEnemy++)
	{
		// ���݂̔ԍ��̒ʏ�G�̎擾����
		CEnemyNormal *pEnemy = CManagerObject::GetEnemyNormal(nCutEnemy);

		// �ʏ�G�̗L���𔻒�
		if (pEnemy != NULL)
		{
			// �ϐ��錾�i���擾�j
			D3DXVECTOR3 enemyPos = pEnemy->m_dataPos.Get();		// �ʒu
			D3DXVECTOR3 enemySize = pEnemy->m_dataSize.Get();	// �傫��

			// ��`�̓����蔻��
			if (CHit::hitRectangle(pos, size, enemyPos, enemySize) == true)
			{
				// �G�l�~�[�̃_���[�W����
				pEnemy->Hit(nCutEnemy, nDamage);

				// �����_���[�W
				CollisionEnemyBlast(nCutEnemy);

				// �����̏I������
				Uninit();

				// ������Ԃ�
				return true;
			}

		}
	}

	// �{�X�G�̎擾����
	CEnemyBoss *pEnemyBoss = CManagerObject::GetEnemyBoss();

	if (pEnemyBoss != NULL)
	{
		// �ϐ��錾�i���擾�j
		D3DXVECTOR3 enemyPos = pEnemyBoss->m_dataPos.Get();		// �ʒu
		D3DXVECTOR3 enemySize = pEnemyBoss->m_dataSize.Get();	// �傫��

		// ��`�̓����蔻��
		if (CHit::hitRectangle(pos, size, enemyPos, enemySize) == true)
		{
			// �G�l�~�[�̃_���[�W����
			pEnemyBoss->Hit(nDamage);

			// �����_���[�W
			CollisionEnemyBlast(ENEMY_BOSS_NUM);

			// �����̏I������
			Uninit();

			// ������Ԃ�
			return true;
		}

	}

	// ���X�V
	m_dataPos.Set(pos);				// �ʒu
	m_dataSize.Set(size);			// �傫��

	m_nDataDamage.Set(nDamage);		// �_���[�W�l

	// �u�Ȃ��v��Ԃ�
	return false;
}

//-------------------------------------
//- �����e�̔����ƓG�̓����蔻�菈��
//-------------------------------------
void CBulletBomb::CollisionEnemyBlast(int nRawEmyNum)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();		// �ʒu
	D3DXVECTOR3 size = m_dataSize.Get();	// �傫��

	int nBlastDamage = m_nDataBlastDamage.Get();		// �����_���[�W�l

	for (int nCutEnemy = 0; nCutEnemy < ENEMY_NORMAL_NUM_MAX; nCutEnemy++)
	{
		// �e�̓��������G�̔ԍ��𔻒�
		if (nCutEnemy != nRawEmyNum)
		{
			CEnemyNormal *pEnemy = CManagerObject::GetEnemyNormal(nCutEnemy);

			if (pEnemy != NULL)
			{
				// �ϐ��錾�i���擾�j
				D3DXVECTOR3 enemyPos = pEnemy->m_dataPos.Get();		// �ʒu
				D3DXVECTOR3 enemySize = pEnemy->m_dataSize.Get();	// �傫��

				D3DXVECTOR3 blastSize = D3DXVECTOR3(BLAST_RANGE, 0.0f, BLAST_RANGE);	// �����͈̔�

				// ��`�̓����蔻��
				if (CHit::hitRectangle(pos, size + blastSize, enemyPos, enemySize) == true)
				{
					// �G�l�~�[�̃_���[�W����
					pEnemy->Hit(nCutEnemy, nBlastDamage);
				}

			}
		}
	}

	// �e�̓��������G�̔ԍ��𔻒�i-1 = boss�j
	if (ENEMY_BOSS_NUM != nRawEmyNum)
	{
		CEnemyBoss *pEnemyBoss = CManagerObject::GetEnemyBoss();

		if (pEnemyBoss != NULL)
		{
			// �ϐ��錾�i���擾�j
			D3DXVECTOR3 enemyPos = pEnemyBoss->m_dataPos.Get();		// �ʒu
			D3DXVECTOR3 enemySize = pEnemyBoss->m_dataSize.Get();	// �傫��

			D3DXVECTOR3 blastSize = D3DXVECTOR3(BLAST_RANGE, 0.0f, BLAST_RANGE);	// �����͈̔�

			// ��`�̓����蔻��
			if (CHit::hitRectangle(pos, size + blastSize, enemyPos, enemySize) == true)
			{
				// �G�l�~�[�̃_���[�W����
				pEnemyBoss->Hit(nBlastDamage);
			}

		}
	}
}

//-------------------------------------
//- �����e�̃I�u�W�F�N�g�Ƃ̓����蔻��
//-------------------------------------
bool CBulletBomb::CollisionObject(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();			// �ʒu
	D3DXVECTOR3 size = m_dataSize.Get();		// �傫��
	D3DXVECTOR3 move = m_dataMove.Get();		// �ړ���

	for (int nCutObjectNone = 0; nCutObjectNone < OBJECTX_NONE_NUM_MAX; nCutObjectNone++)
	{
		// �C�x���g�I�u�W�F�N�g�̏����擾
		CObjectXNone *pObjectNone = CManagerObject::GetObjectNone(nCutObjectNone);

		// �C�x���g�I�u�W�F�N�g�̗L���𔻒�
		if (pObjectNone != NULL)
		{
			// �ϐ��錾�i���擾�j
			D3DXVECTOR3 evtObjPos = pObjectNone->m_dataPos.Get();	// �ʒu
			D3DXVECTOR3 evtObjSize = pObjectNone->m_dataSize.Get();	// �傫��

			// ��`�̓����蔻��
			if (CHit::hitRectangle(pos, size, evtObjPos, evtObjSize) == true)
			{
				// �����̏I������
				Uninit();

				// ������Ԃ�
				return true;
			}
		}
	}

	for (int nCutEventObject = 0; nCutEventObject < EVENT_OBJECT_NUM_MAX; nCutEventObject++)
	{
		// �C�x���g�I�u�W�F�N�g�̏����擾
		CEventObject *pEventObject = CManagerObject::GetEventObject(nCutEventObject);

		// �C�x���g�I�u�W�F�N�g�̗L���𔻒�
		if (pEventObject != NULL)
		{
			// �ϐ��錾�i���擾�j
			D3DXVECTOR3 evtObjPos = pEventObject->m_dataPos.Get();		// �ʒu
			D3DXVECTOR3 evtObjSize = pEventObject->m_dataSize.Get();	// �傫��

			// ��`�̓����蔻��
			if (CHit::hitRectangle(pos, size, evtObjPos, evtObjSize) == true)
			{
				// �����̏I������
				Uninit();

				// ������Ԃ�
				return true;
			}
		}
	}

	return false;
}