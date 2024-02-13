
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
#include "object_x.h"

#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "manager_object.h"

#include "manager_model.h"
#include "time_stop.h"
#include "sys_game_phase.h"

#include "player_battle.h"
#include "sys_phase_battle.h"

#include "particle.h"
#include "effect_object.h"	

#include "mgr_sys_obj.h"
#include "score.h"

#include "effect_game.h"

#include "object_col.h"

#include "state_game.h"

#include "hit.h"

//-======================================
//-	�}�N����`
//-======================================

#define EMY_BOSS_SEARCH_RANGE	(2000.0f)	// ���G�͈�
#define EMY_BOSS_TARGET_RANGE	(3000.0f)	// �ǔ��͈�
#define EMY_BOSS_ATTACK_RANGE	(200.0f)	// �U���͈�

#define EMY_BOSS_LIFE			(800)		// �̗�
#define EMY_BOSS_SPEED			(6.0f)		// ���x

#define EMY_BOSS_ATTACK_DAMAGE	(10)		// �U����

#define EMY_BOSS_ATTACK_TIME	(60)		// �U���^�C�~���O

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	�{�X�G�̃R���X�g���N�^
//-------------------------------------
CEnemyBoss::CEnemyBoss()
{
	state = STATE_NORMAL;
	m_pObjCol = NULL;
}

//-------------------------------------
//-	�{�X�G�̃f�X�g���N�^
//-------------------------------------
CEnemyBoss::~CEnemyBoss()
{

}

//-------------------------------------
//- �{�X�G�̏���������
//-------------------------------------
HRESULT CEnemyBoss::Init(MODEL_TYPE modelType)
{
	// �G�̏����� if(�����������̗L���𔻒�)
	if (FAILED(CEnemy::Init(modelType)))
	{
		// ���s��Ԃ�
		return E_FAIL;
	}

	// �����ݒ菈��
	InitSet();

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �{�X�G�̏I������
//-------------------------------------
void CEnemyBoss::Uninit(void)
{
	// �����蔻��I�u�W�F�N�g�̗L���𔻒�
	if (m_pObjCol != NULL)
	{
		// �����蔻��I�u�W�F�N�g�̏I������
		m_pObjCol->Uninit();

		// �����蔻��I�u�W�F�N�g�̊J������
		delete m_pObjCol;
		m_pObjCol = NULL;
	}

	// �G�̏I������
	CEnemy::Uninit();
}

//-------------------------------------
//- �{�X�G�̍X�V����
//-------------------------------------
void CEnemyBoss::Update(void)
{
	// �Q�[���̏�Ԃ̔���
	switch (state)
	{
	case STATE_NORMAL:

		// �T�mAI
		AiSearch();

		break;
	case STATE_TARGET:

		// �ǔ�AI
		AiTarget();

		break;
	case STATE_ATTACK:

		// �U��AI
		AiAttack();

		break;

	case STATE_COOL_TIME:

		// �N�[���^�C��AI
		AiCoolTime();

		break;
	}

	// �����蔻��I�u�W�F�N�g�̗L���𔻒�
	if (m_pObjCol != NULL)
	{
		// �����蔻��I�u�W�F�N�g�̍X�V
		m_pObjCol->Update();
	}

	// �G�̍X�V����
	CEnemy::Update();
}

//-------------------------------------
//- �{�X�G�̕`�揈��
//-------------------------------------
void CEnemyBoss::Draw(void)
{
	// �G�̕`�揈��
	CEnemy::Draw();
}

//-------------------------------------
//- �{�X�G�̐�������
//-------------------------------------
CEnemyBoss *CEnemyBoss::Create(MODEL_TYPE modelType)
{
	// �{�X�G�̐���
	CEnemyBoss *pCEnemyBoss = DBG_NEW CEnemyBoss;

	// �����̐����̗L���𔻒�
	if (pCEnemyBoss != NULL)
	{
		// ����������
		if (FAILED(pCEnemyBoss->Init(modelType)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCEnemyBoss == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// ��ނ�ݒ�
	pCEnemyBoss->SetType(TYPE_ENEMY);

	// �{�X�G�̃|�C���^��Ԃ�
	return pCEnemyBoss;
}

//-------------------------------------
//- �{�X�G�̓����蔻��I�u�W�F�N�g�擾��������
//-------------------------------------
CObjectCol *CEnemyBoss::GetObjectCol(void)
{
	return m_pObjCol;
}

//-------------------------------------
//- �{�X�G�̃_���[�W����
//-------------------------------------
void CEnemyBoss::Hit(int nDamage)
{
	// �X�R�A�̃|�C���^��錾
	CScore *pScore = CGame::GetMgrSysObj()->GetScore();

	// �X�R�A�̗L���𔻒�
	if (pScore == NULL)
	{
		// �����𔲂���
		return;
	}

	// �Q�[���G�t�F�N�g�̃|�C���^��錾
	CEffectGame *pEffectGame = CManager::GetEffectGame();

	// �Q�[���G�t�F�N�g�̗L���𔻒�
	if (pEffectGame == NULL)
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

	// �Q�[���X�e�[�^�X�̏����擾
	CStateGame *pStateGame = CGame::GetStateGame();

	// �Q�[���X�e�[�^�X�擾�̗L���𔻒�
	if (pStateGame == NULL)
	{
		// �����𔲂���
		return;
	}

	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();		// �ʒu
	D3DXVECTOR3 move = m_dataMove.Get();	// �ړ���

	int nLife = m_nDataLife.Get();			// �̗͂̎擾����

	// �_���[�W�̒l�����Z
	nLife -= nDamage;

	if (nLife <= 0)
	{
		// �Q�[���̏I����Ԃ̐ݒ�
		pStateGame->SetEndState(CStateGame::END_STATE_BOSS);
		
		// �I�u�W�F�N�g�G�t�F�N�g�̐���
		CEffectObject *pEffectObject = CEffectObject::Create(CEffectObject::MODEL_COIN_000);

		// �I�u�W�F�N�g�G�t�F�N�g�̐��������̗L���𔻒�
		if (pEffectObject != NULL)
		{
			// �I�u�W�F�N�g�G�t�F�N�g�ݒ�
			pEffectObject->Set(
				D3DXVECTOR3(pos.x, pos.y + 30.0f, pos.z),
				D3DXVECTOR3(5.0f, 5.0f, 5.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 6.0f, 0.0f),
				D3DXVECTOR3(0.0f, 150.0f, 0.0f));
		}

		// �X�R�A�̉��Z����
		pScore->Add(CScore::GET_TYPE_NORMAL, 50000);

		// �p�[�e�B�N���̐���
		CParticle::SetParticle(
			32,
			pos,
			D3DXVECTOR3(20.0f, 20.0f, 0.0f),
			D3DXVECTOR3(30.0f, 30.0f, 0.0f),
			D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
			60);

		// ��ʗh��
		pEffectGame->Set(
			D3DXVECTOR3(0.0f, 0.5f, 0.0f),
			D3DXVECTOR3(4.0f, 4.0f, 4.0f),
			4,
			8);

		// �q�b�g�X�g�b�v
		pManagerTime->Set(0.0f, 10);

		// �I�u�W�F�N�g�Ǘ��̃|�C���^��������
		CManagerObject::ReleaseEnemyBoss();

		// �����̏I������
		Uninit();

		// �����𔲂���
		return;
	}
	else
	{
		// �p�[�e�B�N���̐���
		CParticle::SetParticle(
			8,
			pos,
			D3DXVECTOR3(30.0f, 30.0f, 0.0f),
			D3DXVECTOR3(70.0f, 70.0f, 0.0f),
			D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
			30);

		// �q�b�g�X�g�b�v
		pManagerTime->Set(0.5f, 4);
	}

	// ���X�V
	m_nDataLife.Set(nLife);		// �̗�
}

//-------------------------------------
//- �{�X�G�̏����ݒ菈��
//-------------------------------------
void CEnemyBoss::InitSet(void)
{
	m_nDataLife.Set(EMY_BOSS_LIFE);	// �̗�
}

//-------------------------------------
//- �{�X�G�̍��GAI����
//-------------------------------------
void CEnemyBoss::AiSearch(void)
{
	// �v���C���[�̏����擾
	CPlayer *pPlayer = CSysPhaseBattle::GetPlayer();

	// ���擾�̗L���𔻒�
	if (pPlayer == NULL)
	{
		// �����𔲂���
		return;
	}

	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();		// �ʒu

	// �ϐ��錾�i�v���C���[�̏��擾�j
	D3DXVECTOR3 posPlayer = pPlayer->m_dataPos.Get();											// �v���C���[�̈ʒu
	D3DXVECTOR3 searchEnemyRange = D3DXVECTOR3(EMY_BOSS_SEARCH_RANGE,0.0f, EMY_BOSS_SEARCH_RANGE);	// �G�{�X�̍��G�͈�

	// ��`�̓����蔻��
	if (CHit::hitRectangle(posPlayer, D3DXVECTOR3(0.0f,0.0f,0.0f), pos, searchEnemyRange) == true)
	{// �v���C���[�����͈͂ɂ���ꍇ���m

		// ��Ԃ�ύX
		state = STATE_TARGET;
	}

	// ���X�V
	m_dataPos.Set(pos);		// �ʒu
}

//-------------------------------------
//- �{�X�G�̒ǔ�AI����
//-------------------------------------
void CEnemyBoss::AiTarget(void)
{
	// ���ԊǗ��̏����擾
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// ���ԊǗ��擾�̗L���𔻒�
	if (pManagerTime == NULL)
	{
		// �����𔲂���
		return;
	}

	// �v���C���[�̏����擾
	CPlayer *pPlayer = CSysPhaseBattle::GetPlayer();

	// ���擾�̗L���𔻒�
	if (pPlayer == NULL)
	{
		// �����𔲂���
		return;
	}

	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();		// �ʒu
	D3DXVECTOR3 rot = m_dataRot.Get();		// ����
	D3DXVECTOR3 move = m_dataMove.Get();	// �ړ���

	D3DXVECTOR3 posPlayer = pPlayer->m_dataPos.Get();	// �v���C���[�̈ʒu
	D3DXVECTOR3 rotPlayer = pPlayer->m_dataRot.Get();	// �v���C���[�̌���
	D3DXVECTOR3 sizePlayer = pPlayer->m_dataRot.Get();	// �v���C���[�̑傫��
	D3DXVECTOR3 targetEnemyRange = D3DXVECTOR3(			// �G�{�X�̒ǔ��͈�
		EMY_BOSS_TARGET_RANGE, 
		0.0f, 
		EMY_BOSS_SEARCH_RANGE);
	D3DXVECTOR3 attackEnemyRange = D3DXVECTOR3(			// �G�{�X�̍U���J�n�͈�
		EMY_BOSS_ATTACK_RANGE,
		0.0f,
		EMY_BOSS_ATTACK_RANGE);

	// ���Ԕ{���̌v�Z
	D3DXVECTOR3 moveTime = pManagerTime->CalRate(move);

	// ��`�̓����蔻��i�v���C���[�̈ʒu�ƃ{�X�̒ǔ��͈́j
	if (CHit::hitRectangle(posPlayer, D3DXVECTOR3(0.0f, 0.0f, 0.0f), pos, targetEnemyRange) == true)
	{
		// ��`�̓����蔻��i�v���C���[�̈ʒu�ƃ{�X�̍U���J�n�͈́j
		if (CHit::hitRectangle(posPlayer, D3DXVECTOR3(0.0f, 0.0f, 0.0f), pos, attackEnemyRange) == true)
		{
			// ��Ԃ�ύX
			state = STATE_ATTACK;

			// �����蔻��I�u�W�F�N�g�̗L���𔻒�
			if (m_pObjCol == NULL)
			{
				//�v���C���[�ɐU�����
				rot.y = atan2f(pos.x - posPlayer.x, pos.z - posPlayer.z);

				// �����蔻��I�u�W�F�N�g�̐�������
				m_pObjCol = CObjectCol::Create();

				// �����蔻��I�u�W�F�N�g�̐ݒ菈��
				m_pObjCol->Set(
					D3DXVECTOR3(
						pos.x + (-sinf(rot.y)) * 200.0f,
						pos.y,
						pos.z + (-cosf(rot.y)) * 200.0f),

					D3DXVECTOR3(200.0f, 50.0f, 200.0f),
					rot);

				// �����蔻��I�u�W�F�N�g�̐F�̐ݒ�
				m_pObjCol->m_dataColor.Set(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			}
		}
		else
		{
			//�v���C���[�ɐU�����
			rot.y = atan2f(pos.x - posPlayer.x, pos.z - posPlayer.z);

			// ���Ԕ{���̌v�Z
			float fEnemySpeedTime = pManagerTime->CalRate(EMY_BOSS_SPEED);

			// �ړ��ʂ�ݒ�
			move.x = -sinf(rot.y) * fEnemySpeedTime;
			move.z = -cosf(rot.y) * fEnemySpeedTime;
		}

	}
	else
	{
		// ��Ԃ�ύX
		state = STATE_NORMAL;
	}

	// �ʒu���X�V
	pos += moveTime;

	// ���Ԕ{���̌v�Z
	float moveReduceTimeX = pManagerTime->CalRate((0.0f - move.x) * 0.3f);
	float moveReduceTimeZ = pManagerTime->CalRate((0.0f - move.z) * 0.3f);

	// �ړ��ʂ�����
	move.x += moveReduceTimeX;
	move.z += moveReduceTimeZ;

	// ���X�V
	m_dataPos.Set(pos);		// �ʒu
	m_dataRot.Set(rot);		// ����
	m_dataMove.Set(move);	// �ړ���
}

//-------------------------------------
//- �{�X�G�̍U��Ai����
//-------------------------------------
void CEnemyBoss::AiAttack(void)
{
	// �ϐ��錾�i�v���C���[�̏��擾�j
	CPlayer *pPlayer = CSysPhaseBattle::GetPlayer();

	// ���擾�̗L���𔻒�
	if (pPlayer == NULL)
	{
		// �����𔲂���
		return;
	}

	// �ϐ��錾�i�v���C���[�̏��擾�j
	D3DXVECTOR3 posPlayer = pPlayer->m_dataPos.Get();	// �v���C���[�̈ʒu
	D3DXVECTOR3 rotPlayer = pPlayer->m_dataRot.Get();	// �v���C���[�̌���
	D3DXVECTOR3 sizePlayer = pPlayer->m_dataRot.Get();	// �v���C���[�̑傫��

	// �ϐ��錾
	int nAtkCut = m_nDataAtkCnt.Get();				// �U���J�E���g
	int nCoolTimeCut = m_nDataCoolTimeCnt.Get();	// �N�[���^�C���J�E���g

	// �U���J�E���g�����Z
	nAtkCut++;

	// �U���J�E���g�̔���
	if (nAtkCut >= EMY_BOSS_ATTACK_TIME)
	{
		// �N�[���^�C�����Ԃ�ݒ�
		nCoolTimeCut = 30;

		// �N�[���^�C����ԂɕύX
		state = STATE_COOL_TIME;

		// �U���J�E���g�̏�����
		nAtkCut = 0;

		if (m_pObjCol != NULL)
		{
			// �v���C���[�ƍU���̓����蔻��
			if (m_pObjCol->Collision(posPlayer, sizePlayer) == true)
			{
				// �v���C���[�̃_���[�W����
				pPlayer->Hit(EMY_BOSS_ATTACK_DAMAGE);
			}

			// �����蔻��I�u�W�F�N�g�̏I������
			m_pObjCol->Uninit();

			// �����蔻��I�u�W�F�N�g�̊J������
			delete m_pObjCol;
			m_pObjCol = NULL;
		}

	}
	else if (nAtkCut == (EMY_BOSS_ATTACK_TIME * 0.9f))
	{
		if (m_pObjCol != NULL)
		{
			// �����蔻��I�u�W�F�N�g�̐F�ύX
			m_pObjCol->m_dataColor.Set(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
	}
	else if (nAtkCut == (EMY_BOSS_ATTACK_TIME * 0.5f))
	{
		if (m_pObjCol != NULL)
		{
			// �����蔻��I�u�W�F�N�g�̐F�ύX
			m_pObjCol->m_dataColor.Set(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f));
		}
	}

	// ���X�V
	m_nDataAtkCnt.Set(nAtkCut);				// �U���J�E���g
	m_nDataCoolTimeCnt.Set(nCoolTimeCut);	// �N�[���^�C���J�E���g
}

//-------------------------------------
//- �{�X�G�̃N�[���^�C��Ai����
//-------------------------------------
void CEnemyBoss::AiCoolTime(void)
{
	// �ϐ��錾�i���擾�j
	int nCoolTimeCut = m_nDataCoolTimeCnt.Get();	// �N�[���^�C���J�E���g

	// �N�[���^�C�������Z
	nCoolTimeCut--;

	// �N�[���^�C���J�E���g�̔���
	if (nCoolTimeCut == 0)
	{
		// ��Ԃ�ʏ�ɕύX
		state = STATE_NORMAL;
	}

	// ���X�V
	m_nDataCoolTimeCnt.Set(nCoolTimeCut);		// �N�[���^�C���J�E���g
}