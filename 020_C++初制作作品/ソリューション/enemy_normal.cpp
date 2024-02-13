
//-===============================================
//-
//-	�ʏ�G�̏���[enemy_normal.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "enemy_normal.h"
#include "object_x.h"

#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "manager_object.h"

#include "manager_model.h"
#include "time_stop.h"
#include "sys_game_phase.h"

#include "sound.h"

#include "player_battle.h"
#include "sys_phase_battle.h"

#include "particle.h"
#include "effect_object.h"	

#include "mgr_sys_obj.h"
#include "score.h"

#include "effect_game.h"

#include "object_col.h"

#include "state_game.h"
#include "state_battle.h"

#include "hit.h"

//-======================================
//-	�}�N����`
//-======================================

#define EMY_NOR_LIFE			(100)		// �̗�
#define EMY_NOR_SPEED			(6.0f)		// ���x

#define EMY_NOR_ATTACK_DAMAGE	(5)			// �U����

#define EMY_NOR_ATTACK_TIME		(45)		// �U���^�C�~���O

#define EMY_NOR_SCORE			(1000)		// �����Ă���X�R�A�l

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	�ʏ�G�̃R���X�g���N�^
//-------------------------------------
CEnemyNormal::CEnemyNormal()
{
	state = STATE_NORMAL;
	m_pObjCol = NULL;
}

//-------------------------------------
//-	�ʏ�G�̃f�X�g���N�^
//-------------------------------------
CEnemyNormal::~CEnemyNormal()
{

}

//-------------------------------------
//- �ʏ�G�̏���������
//-------------------------------------
HRESULT CEnemyNormal::Init(MODEL_TYPE modelType)
{
	// �G�̏����� if(�����������̗L���𔻒�)
	if (FAILED(CEnemy::Init(modelType)))
	{
		// ���s��Ԃ�
		return E_FAIL;
	}

	// �����ݒ�
	InitSet();

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �ʏ�G�̏I������
//-------------------------------------
void CEnemyNormal::Uninit(void)
{
	// �����蔻��I�u�W�F�N�g�̗L���𔻒�
	if (m_pObjCol != NULL)
	{
		// �����蔻��I�u�W�F�N�g�̍X�V
		m_pObjCol->Uninit();

		// �����蔻��I�u�W�F�N�g�̊J������
		delete m_pObjCol;
		m_pObjCol = NULL;
	}

	// �G�̏I������
	CEnemy::Uninit();
}

//-------------------------------------
//- �ʏ�G�̍X�V����
//-------------------------------------
void CEnemyNormal::Update(void)
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
//- �ʏ�G�̕`�揈��
//-------------------------------------
void CEnemyNormal::Draw(void)
{
	// �G�̕`�揈��
	CEnemy::Draw();
}

//-------------------------------------
//- �ʏ�G�̐�������
//-------------------------------------
CEnemyNormal *CEnemyNormal::Create(MODEL_TYPE modelType)
{
	// �ʏ�G�̐���
	CEnemyNormal *pCEnemyNormal = DBG_NEW CEnemyNormal;

	// �����̐����̗L���𔻒�
	if (pCEnemyNormal != NULL)
	{
		// ����������
		if (FAILED(pCEnemyNormal->Init(modelType)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCEnemyNormal == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// ��ނ�ݒ�
	pCEnemyNormal->SetType(TYPE_ENEMY);

	// �ʏ�G�̃|�C���^��Ԃ�
	return pCEnemyNormal;
}

//-------------------------------------
//- �ʏ�G�̓����蔻��I�u�W�F�N�g�擾��������
//-------------------------------------
CObjectCol *CEnemyNormal::GetObjectCol(void)
{
	return m_pObjCol;
}

//-------------------------------------
//- �ʏ�G�̐ݒ菈��
//-------------------------------------
void CEnemyNormal::InitSet(void)
{
	// ���X�V
	m_nDataLife.Set(EMY_NOR_LIFE);			// �̗�

	m_fDataSpeedNor.Set(EMY_NOR_SPEED);
	m_fDataSpeedStr.Set(10.0f);
	m_fDataSpeed.Set(m_fDataSpeedNor.Get());

	m_dataSearchRangeNor.Set(D3DXVECTOR3(1500.0f, 0.0f, 1500.0f));
	m_dataSearchRangeStr.Set(D3DXVECTOR3(2000.0f, 0.0f, 2000.0f));
	m_dataSearchRange.Set(m_dataSearchRangeNor.Get());

	m_dataAttackRangeNor.Set(D3DXVECTOR3(200.0f, 0.0f, 200.0f));
	m_dataAttackRange.Set(m_dataAttackRangeNor.Get());

	m_nDataStrTime.Set(60);
}

//-------------------------------------
//- �ʏ�G�̃_���[�W����
//-------------------------------------
void CEnemyNormal::Hit(int nCutEnemy, int nDamage)
{
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

	// �X�R�A�̃|�C���^��錾
	CScore *pScore = CGame::GetMgrSysObj()->GetScore();

	// �X�R�A�̗L���𔻒�
	if (pScore == NULL)
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

	// �퓬�X�e�[�^�X�̏����擾
	CStateBattle *pStateBattle = CGame::GetStateBattle();

	// �퓬�X�e�[�^�X�擾�̗L���𔻒�
	if (pStateBattle == NULL)
	{
		// �����𔲂���
		return;
	}

	// �T�E���h�̃|�C���^��錾
	CSound *pSound = CManager::GetSound();

	// �T�E���h�̏��擾�̐����𔻒�
	if (pSound == NULL)
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
				D3DXVECTOR3(0.0f, 3.0f, 0.0f),
				D3DXVECTOR3(0.0f, 75.0f, 0.0f));
		}

		// �X�R�A�̉��Z����
		pScore->Add(CScore::GET_TYPE_NORMAL, EMY_NOR_SCORE);

		// �G�̎��S�������Z
		pStateGame->AddEnemyDeath();

		// �p�[�e�B�N���̐���
		CParticle::SetParticle(
			32,
			pos,
			D3DXVECTOR3(40.0f, 40.0f, 0.0f),
			D3DXVECTOR3(30.0f, 30.0f, 0.0f),
			D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
			60);

		// ��ʗh��
		pEffectGame->Set(
			D3DXVECTOR3(0.0f,0.5f,0.0f),
			D3DXVECTOR3(4.0f,4.0f,4.0f),
			4,
			8);

		// �q�b�g�X�g�b�v
		pManagerTime->Set(0.0f,10);

		// SE�̍Đ��i�G�̎��S��000�j
		pSound->Play(CSound::LABEL_SE_DIED_ENEMY_000);

		// �I�u�W�F�N�g�Ǘ��̃|�C���^��������
		CManagerObject::ReleaseEnemyNormal(nCutEnemy);

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
			D3DXVECTOR3(40.0f, 40.0f, 0.0f),
			D3DXVECTOR3(70.0f, 70.0f, 0.0f),
			D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
			30);

		// ��ʗh��
		pEffectGame->Set(
			D3DXVECTOR3(0.0f, 0.5f, 0.0f),
			D3DXVECTOR3(2.0f, 2.0f, 2.0f),
			2,
			2);

		// �q�b�g�X�g�b�v
		pManagerTime->Set(0.5f, 4);

		// �����𔻒�
		switch (pStateBattle->GetElemType())
		{
		case CStateBattle::ELEM_TYPE_NORMAL:

			// SE�̍Đ��i�G�̃_���[�W��000�j
			pSound->Play(CSound::LABEL_SE_DAMAGE_ENEMY_000);

			break;

		case CStateBattle::ELEM_TYPE_CHAOS:

			// SE�̍Đ��i�G�̃_���[�W��001�j
			pSound->Play(CSound::LABEL_SE_DAMAGE_ENEMY_001);

			break;
		}

	}

	// ���X�V
	m_nDataLife.Set(nLife);		// �̗�
}

//-------------------------------------
//- �ʏ�G�̍��GAI����
//-------------------------------------
void CEnemyNormal::AiSearch(void)
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
	D3DXVECTOR3 pos = m_dataPos.Get();					// �ʒu
	D3DXVECTOR3 searchRange = m_dataSearchRange.Get();	// ���G�͈�

	// �ϐ��錾�i�v���C���[�̏��擾�j
	D3DXVECTOR3 posPlayer = pPlayer->m_dataPos.Get();	// �v���C���[�̈ʒu

	// ��`�̓����蔻��i���G�͈͂ƃv���C���[�̈ʒu�j
	if (CHit::hitRectangle(posPlayer, D3DXVECTOR3(0.0f, 0.0f, 0.0f), pos, searchRange) == true)
	{// �v���C���[�����͈͂ɂ���ꍇ���m
		
		// ��Ԃ�ύX
		state = STATE_TARGET;
	}

	// ���X�V
	m_dataPos.Set(pos);		// �ʒu
}

//-------------------------------------
//- �ʏ�G�̒ǔ�AI����
//-------------------------------------
void CEnemyNormal::AiTarget(void)
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
	D3DXVECTOR3 pos = m_dataPos.Get();						// �ʒu
	D3DXVECTOR3 rot = m_dataRot.Get();						// ����
	D3DXVECTOR3 move = m_dataMove.Get();					// �ړ���
	float speed = m_fDataSpeed.Get();						// ���x
	D3DXVECTOR3 searchRange = m_dataSearchRange.Get();		// �ǔ����G�͈�
	D3DXVECTOR3 attackRange = m_dataAttackRange.Get();		// �U���J�n�͈�

	D3DXVECTOR3 posPlayer = pPlayer->m_dataPos.Get();		// �v���C���[�̈ʒu
	D3DXVECTOR3 sizePlayer = pPlayer->m_dataRot.Get();		// �v���C���[�̑傫��

	// ���Ԕ{���̌v�Z
	D3DXVECTOR3 moveTime = pManagerTime->CalRate(move);

	// ��`�̓����蔻��i�ǔ����G�͈͂ƃv���C���[�̈ʒu�j
	if (CHit::hitRectangle(posPlayer, D3DXVECTOR3(0.0f, 0.0f, 0.0f), pos, searchRange) == true)
	{//�v���C���[�����͈͂ɂ���ꍇ���m

		if (CHit::hitRectangle(posPlayer, D3DXVECTOR3(0.0f, 0.0f, 0.0f), pos, attackRange) == true)
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
					D3DXVECTOR3(150.0f,50.0f, 150.0f),
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
			float fEnemySpeedTime = pManagerTime->CalRate(speed);

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
//- �ʏ�G�̍U��Ai����
//-------------------------------------
void CEnemyNormal::AiAttack(void)
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
	D3DXVECTOR3 sizePlayer = pPlayer->m_dataRot.Get();	// �v���C���[�̑傫��

	// �ϐ��錾�i���擾�j
	int nAtkCut = m_nDataAtkCnt.Get();				// �U���J�E���g
	int nCoolTimeCut = m_nDataCoolTimeCnt.Get();	// �N�[���^�C���J�E���g

	// �U���J�E���g�����Z
	nAtkCut++;

	// �U���J�E���g�̔���
	if (nAtkCut >= EMY_NOR_ATTACK_TIME)
	{
		// �N�[���^�C�����Ԃ�ݒ�
		nCoolTimeCut = 60;

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
				pPlayer->Hit(5);
			}

			// �����蔻��I�u�W�F�N�g�̏I������
			m_pObjCol->Uninit();

			// �����蔻��I�u�W�F�N�g�̊J������
			delete m_pObjCol;
			m_pObjCol = NULL;
		}
	}
	else if (nAtkCut == EMY_NOR_ATTACK_TIME * 0.9f)
	{
		if (m_pObjCol != NULL)
		{
			// �����蔻��I�u�W�F�N�g�̐F�̕ύX
			m_pObjCol->m_dataColor.Set(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
	}
	else if (nAtkCut == EMY_NOR_ATTACK_TIME * 0.5f)
	{
		if (m_pObjCol != NULL)
		{
			// �����蔻��I�u�W�F�N�g�̐F�̕ύX
			m_pObjCol->m_dataColor.Set(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f));
		}
	}

	// ���X�V
	m_nDataAtkCnt.Set(nAtkCut);
	m_nDataCoolTimeCnt.Set(nCoolTimeCut);
}

//-------------------------------------
//- �ʏ�G�̃N�[���^�C��Ai����
//-------------------------------------
void CEnemyNormal::AiCoolTime(void)
{
	// �ϐ��錾�i���擾�j
	int nCoolTimeCut = m_nDataCoolTimeCnt.Get();	// �N�[���^�C���J�E���g

	// �N�[���^�C�������Z
	nCoolTimeCut--;

	if (nCoolTimeCut == 0)
	{
		// ��Ԃ�ʏ�ɕύX
		state = STATE_NORMAL;
	}

	// ���X�V
	m_nDataCoolTimeCnt.Set(nCoolTimeCut);
}