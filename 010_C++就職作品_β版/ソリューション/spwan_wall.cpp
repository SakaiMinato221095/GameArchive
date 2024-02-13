
//-===============================================
//-
//-	�o���Ǐ���[spwan_wall.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "spwan_wall.h"

#include "renderer.h"
#include "manager.h"

#include "game.h"

#include "manager_texture.h"

#include "obj_3d_wall.h"
#include "coll.h"

#include "model.h"
#include "motion.h"

#include "enemy_minion.h"
#include "enemy_boss.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�R���X�g��`
//=======================================

// �o���ǂ̃e�N�X�`��
const char* DataTexture[] =
{
	nullptr,											// �e�N�X�`���Ȃ�
	"data\\TEXTURE\\SpwanWall\\SpawnWall000.png",		// �o���ǂ̃e�N�X�`��
	"data\\TEXTURE\\SpwanWall\\BlockWall000.jpg",		// �����ǂ̃e�N�X�`��
};

// �t�F�[�Y2�̓G�̈ʒu
const D3DXVECTOR3 ENEMY_POS_PHASE_TWO[3] =
{
	D3DXVECTOR3(-300.0f,0.0f,300.0f),
	D3DXVECTOR3(0.0f,0.0f,400.0f),
	D3DXVECTOR3(500.0f,0.0f,700.0f),
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

int CSpwanWall::m_nTextureNldx[TEX_MAX] = {};

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CSpwanWall::CSpwanWall(int nPriority) : CObject(nPriority)
{
	ZeroMemory(&m_info, sizeof(m_info));
	ZeroMemory(&m_infoVisual, sizeof(m_infoVisual));
	ZeroMemory(&m_infoAttach, sizeof(m_infoAttach));
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CSpwanWall::~CSpwanWall()
{

}

//-------------------------------------
//- �w�i�̃e�N�X�`���̓ǂݍ���
//-------------------------------------
HRESULT CSpwanWall::Load(void)
{
	// ���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	CManagerTexture* pManagerTexture = CManager::GetInstance()->GetManagerTexture();

	// ���擾�̐����𔻒�
	if (pDevice == nullptr ||
		pManagerTexture == nullptr)
	{// ���s��

		// �����������𔲂���
		return E_FAIL;
	}

	// �e�N�X�`���ݒ�
	for (int nCount = 0; nCount < TEX_MAX; nCount++)
	{
		// �e�N�X�`���ԍ��̎擾�i�e�N�X�`���̊����j
		m_nTextureNldx[nCount] = pManagerTexture->Regist(DataTexture[nCount]);

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
//- �w�i�̓ǂݍ��񂾃e�N�X�`���̔j��
//-------------------------------------
void CSpwanWall::Unload(void)
{

}
//-------------------------------------
//- �����������i3D�I�u�W�F�N�g�ݒ�j
//-------------------------------------
HRESULT CSpwanWall::Init(void)
{
	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �I������
//-------------------------------------
void CSpwanWall::Uninit(void)
{
	if (m_infoVisual.pObj3dWall != NULL)
	{
		// �����蔻��̏I������
		m_infoVisual.pObj3dWall->Uninit();
		m_infoVisual.pObj3dWall = NULL;
	}

	if (m_infoAttach.pColl != NULL)
	{
		// �����蔻��̏I������
		m_infoAttach.pColl->Uninit();

		delete m_infoAttach.pColl;
		m_infoAttach.pColl = NULL;
	}

	// �J������
	Release();
}

//-------------------------------------
//- �X�V����
//-------------------------------------
void CSpwanWall::Update(void)
{
	if (m_infoAttach.pColl != nullptr)
	{
		// �����蔻��̏��X�V����
		m_infoAttach.pColl->UpdateData(
			GetPos(),
			GetSize());
	}

	// ��ނ̍X�V����
	UpdateType();
}

//-------------------------------------
//- �`�揈��
//-------------------------------------
void CSpwanWall::Draw(void)
{

}

//-------------------------------------
//- �ڐG����
//-------------------------------------
void CSpwanWall::Hit(void)
{
	// �G�̐�������
	SetPhase();

	// �^�[�Q�b�g���̐ݒ菈��
	CPhaseManager* pPhaseManager = CGame::GetPhaseManager();

	if (pPhaseManager != nullptr)
	{
		pPhaseManager->SetTargetCompNum(m_info.nNumTarget);
	}
	
	// �I������
	Uninit();
}

//-------------------------------------
//-	�����ݒ菈��
//-------------------------------------
void CSpwanWall::InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR color, D3DXVECTOR2 texPos)
{
	SetPos(pos);
	SetSize(size);
	SetRot(rot);
	SetColor(color);
	SetTexPos(texPos);

	if (m_infoVisual.pObj3dWall == nullptr)
	{
		// �ǂ̐����E�ݒ菈��
		m_infoVisual.pObj3dWall = CObj3dWall::Create(CObj3dWall::TEX_NULL);
		m_infoVisual.pObj3dWall->InitSet(m_info.pos, m_info.size, m_info.rot, m_info.color, m_info.texPos);
	}

	if (m_infoAttach.pColl == nullptr)
	{
		// �����蔻��ݒ�
		m_infoAttach.pColl = CColl::Create(
			CMgrColl::TAG_SPAWN_ENEMY_WALL,
			this,
			m_info.pos,
			m_info.size);
	}

	// ��ނ̍X�V
	UpdateType();
}

//-------------------------------------
//- ��������
//-------------------------------------
CSpwanWall* CSpwanWall::Create(void)
{
	// �|�C���^��錾
	CSpwanWall* pCSpwanWall = DBG_NEW CSpwanWall(1);

	// �����̐����̗L���𔻒�
	if (pCSpwanWall != NULL)
	{
		// ����������
		if (FAILED(pCSpwanWall->Init()))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCSpwanWall == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �|�C���^��Ԃ�
	return pCSpwanWall;
}

//-------------------------------------
//- ��ސݒ菈��
//-------------------------------------
void CSpwanWall::UpdateType(void)
{
	// �t�F�[�Y�Ǘ����擾
	CPhaseManager* pPhaseManager = CGame::GetPhaseManager();

	if (pPhaseManager != nullptr)
	{
		if (m_info.typePhase == pPhaseManager->GetTypePhase())
		{
			if (m_infoVisual.pObj3dWall != nullptr)
			{
				m_infoVisual.pObj3dWall->BindTexture(m_nTextureNldx[TEX_SPWAN_000]);

				CColl::Data data = m_infoVisual.pObj3dWall->GetColl()->GetData();
				data.tag = CMgrColl::TAG_NONE;
				m_infoVisual.pObj3dWall->GetColl()->SetData(data);
			}
		}
		else
		{
			if (m_infoVisual.pObj3dWall != nullptr)
			{
				// �����̃e�N�X�`����ݒ�
				m_infoVisual.pObj3dWall->BindTexture(m_nTextureNldx[TEX_BLOCK_000]);
			}
		}

	}
}

//-------------------------------------
//- �t�F�[�Y1�̓G�̐�������
//-------------------------------------
void CSpwanWall::SetPhase(void)
{
	// �t�F�[�Y1�̐�������
	switch (m_info.typePhase)
	{
	case CPhaseManager::TYPE_PHASE_ONE:

		SpwanEnemyPhaseOne();

		break;

	case CPhaseManager::TYPE_PHASE_TWO:

		SpwanEnemyPhaseTwo();

		break;

	case CPhaseManager::TYPE_PHASE_THREE:

		SpwanEnemyPhaseThree();

		break;
	}
}
//-------------------------------------
//- �t�F�[�Y1�̓G�̐�������
//-------------------------------------
void CSpwanWall::SpwanEnemyPhaseOne(void)
{
	CEnemyMinion* pEnemy = CEnemyMinion::Create(
		CModel::MODEL_TYPE_ALIEN_000,
		CMotion::MOTION_TYPE_ALIEN_000);

	pEnemy->SetInit(
		D3DXVECTOR3(m_info.pos.x, 0.0f, m_info.pos.z) + D3DXVECTOR3(0.0f, 0.0f, 500.0f),
		D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
		(16 * 3),
		(16 * 3));

	pEnemy->SetIsPhaseTarget(true);

	m_info.nNumTarget++;

}

//-------------------------------------
//- �t�F�[�Y2�̓G�̐�������
//-------------------------------------
void CSpwanWall::SpwanEnemyPhaseTwo(void)
{
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		CEnemyMinion* pEnemy = CEnemyMinion::Create(
			CModel::MODEL_TYPE_ALIEN_000,
			CMotion::MOTION_TYPE_ALIEN_000);

		pEnemy->SetInit(
			D3DXVECTOR3(m_info.pos.x, 0.0f, m_info.pos.z) + ENEMY_POS_PHASE_TWO[nCnt],
			D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
			(9 * 3),
			(9 * 3));

		pEnemy->SetIsPhaseTarget(true);

		m_info.nNumTarget++;
	}
}

//-------------------------------------
//- �t�F�[�Y3�̓G�̐�������
//-------------------------------------
void CSpwanWall::SpwanEnemyPhaseThree(void)
{
	CEnemyBoss* pEnemyBoss = CEnemyBoss::Create(
		CModel::MODEL_TYPE_ENEMY_BOSS,
		CMotion::MOTION_TYPE_ENEMY_BOSS);

	pEnemyBoss->SetInit(
		D3DXVECTOR3(m_info.pos.x, 0.0f, m_info.pos.z) + D3DXVECTOR3(0.0f, 0.0f, 500.0f),
		D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
		(16 * 7));

	pEnemyBoss->SetIsPhaseTarget(true);

	m_info.nNumTarget++;
}