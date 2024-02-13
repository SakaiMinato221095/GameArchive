
//-===============================================
//-
//-	�U���̏���[attack.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "bullet.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"
#include "manager_object.h"
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

#define BULLET_EFFECT_SIZE	(10.0f)									// �e�̃G�t�F�N�g�̑傫��
#define BULLET_EFFECT_LIFE	(30)									// �e�̃G�t�F�N�g�̗̑�
#define BULLET_EFFECT_COLOR	(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f))		// �e�̃G�t�F�N�g�̐F

//=======================================
//= �R���X�g��`
//=======================================

// �e�e�N�X�`���̃R���X�g��`
const char *pTextureBullet[] =
{
	"data\\TEXTURE\\BulletRed.png",		// �Ԓe_000�̃e�N�X�`��
	"data\\TEXTURE\\BulletBlue.png",	// �e_000�̃e�N�X�`��
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

int CBullet::m_nTextureNldx[TEX_MAX] = {};	// �e�N�X�`��
										
//-------------------------------------
//-	�e�̃R���X�g���N�^
//-------------------------------------
CBullet::CBullet(int nPriority) : CObjectBillboard(nPriority)
{

}

//-------------------------------------
//-	�e�̃f�X�g���N�^
//-------------------------------------
CBullet::~CBullet()
{

}

//-------------------------------------
//- �e�̃e�N�X�`���̓ǂݍ���
//-------------------------------------
HRESULT CBullet::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

	 // �����������𔲂���
		return E_FAIL;
	}

	// �e�N�X�`���Ǘ��̐���
	CManagerTexture *pManagerTexture = CManager::GetManagerTexture();

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
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureBullet[nCount]);

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
//- �e�̓ǂݍ��񂾃e�N�X�`���̔j��
//-------------------------------------
void CBullet::Unload(void)
{

}

//-------------------------------------
//- �e�̏���������
//-------------------------------------
HRESULT CBullet::Init(TEX tex)
{
	// ���ԊǗ��̏����擾
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// ���ԊǗ��擾�̗L���𔻒�
	if (pManagerTime == NULL)
	{
		// �����𔲂���
		return E_FAIL;
	}

	// �e�N�X�`������
	BindTexture(m_nTextureNldx[tex]);

	// �r���{�[�h�I�u�W�F�N�g�̏�����
	CObjectBillboard::Init();

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �e�̏I������
//-------------------------------------
void CBullet::Uninit(void)
{
	// �r���{�[�h�I�u�W�F�N�g�̏I��
	CObjectBillboard::Uninit();
}

//-------------------------------------
//- �e�̍X�V����
//-------------------------------------
void CBullet::Update(void)
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
//- �e�̕`�揈��
//-------------------------------------
void CBullet::Draw(void)
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

	// �e�̕`�揈��
	CObjectBillboard::Draw();

	// Z�e�X�g�̉���
	pRenderer->SetZTest(false);

	// �A���t�@�e�X�g�̉���
	pRenderer->SetAlphaTest(false);
}

//-------------------------------------
//- �e�̐�������
//-------------------------------------
CBullet *CBullet::Create(TEX tex)
{
	// �e�̐���
	CBullet *pCBullet = DBG_NEW CBullet(5);

	// �����̐����̗L���𔻒�
	if (pCBullet != NULL)
	{
		// ����������
		if (FAILED(pCBullet->Init(tex)))
		{// ���s��

		 // �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCBullet == NULL)
	{// ���s��

	 // �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// ��ނ�ݒ�
	pCBullet->SetType(TYPE_BULLET);

	// �e�̃|�C���^��Ԃ�
	return pCBullet;
}

//-------------------------------------
//- �e�̈ړ�����
//-------------------------------------
void CBullet::Move(void)
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
//- �e�̉��Z����
//-------------------------------------
void CBullet::Add(void)
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
			pEffect->m_dataSize.Set(D3DXVECTOR3(BULLET_EFFECT_SIZE, BULLET_EFFECT_SIZE, 0.0f));

			// �ړ��ʂ�ݒ�
			pEffect->m_dataMove.Set();

			// �F��ݒ�
			pEffect->m_dataColor.Set(BULLET_EFFECT_COLOR);

			// �G�t�F�N�g�̐ݒ菈��
			pEffect->m_nDataLife.Set(BULLET_EFFECT_LIFE);
		}
	}
}

//-------------------------------------
//- �e�̌��Z����
//-------------------------------------
bool CBullet::Sub(void)
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
//- �G�Ƃ̓����蔻�菈��
//-------------------------------------
bool CBullet::CollisionEnemy(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();		// �ʒu
	D3DXVECTOR3 size = m_dataSize.Get();	// �傫��

	int nDamage = m_nDataDamage.Get();		// �_���[�W�l

	for (int nCutEnemy = 0; nCutEnemy < ENEMY_NORMAL_NUM_MAX; nCutEnemy++)
	{
		CEnemyNormal *pEnemy = CManagerObject::GetEnemyNormal(nCutEnemy);

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

				// �����̏I������
				Uninit();

				// ������Ԃ�
				return true;
			}

		}
	}

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
//- �e�̃I�u�W�F�N�g�Ƃ̓����蔻��
//-------------------------------------
bool CBullet::CollisionObject(void)
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