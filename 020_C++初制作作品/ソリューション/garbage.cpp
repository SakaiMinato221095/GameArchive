
//-===============================================
//-
//-	�S�~�̏���[garbage.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "garbage.h"

#include "renderer.h"
#include "manager.h"
#include "game.h"

#include "sound.h"

#include "manager_model.h"
#include "manager_object.h"
#include "time_stop.h"

#include "mgr_sys_obj.h"
#include "sys_game_phase.h"

#include "player.h"

#include "effect.h"
#include "particle.h"

#include "file_data_garbage.h"

#include "state_battle.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�R���X�g��`
//=======================================

// �S�~�̃��f���̃R���X�g��`
const char *pModelGarbage[] =
{
	"data\\MODEL\\garbage\\bin.x",					// �r�̃��f��

	"data\\MODEL\\garbage\\blood_knife.x",			// ���t���̃i�C�t
	"data\\MODEL\\garbage\\organ_bottle_none.x",	// ���g�Ȃ�����ۊǕr
	"data\\MODEL\\garbage\\syringe_none.x",			// ���g�Ȃ����ˊ�

	"data\\MODEL\\garbage\\ice_cup.x",				// �����X������
	"data\\MODEL\\garbage\\omikuji.x",				// ���݂���
	"data\\MODEL\\garbage\\puragomi.x",				// �Ղ炲��
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

CDataInt CGarbage::m_nDataModelNldx[MODEL_MAX] = {};

CGarbage::ModelData CGarbage::m_modelData[MODEL_MAX] = {};		// ���f�����

//-------------------------------------
//-	�S�~�̃R���X�g���N�^
//-------------------------------------
CGarbage::CGarbage(int nPriority) : CObjectX(nPriority)
{
	m_model = (MODEL)0;
	m_scoreGetType = CScore::GET_TYPE_NORMAL;
}

//-------------------------------------
//-	�S�~�̃f�X�g���N�^
//-------------------------------------
CGarbage::~CGarbage()
{

}

//-------------------------------------
//- �S�~�̃��f���ǂݍ���
//-------------------------------------
HRESULT CGarbage::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

	 // �����������𔲂���
		return E_FAIL;
	}

	// ���f���Ǘ��̐���
	CManagerModel *pManagerModel = CManager::GetManagerModel();

	// ���f���Ǘ��̗L���𔻒�
	if (pManagerModel == NULL)
	{
		// �����������𔲂���
		return E_FAIL;
	}

	// �e�N�X�`���ݒ�
	for (int nCount = 0; nCount < MODEL_MAX; nCount++)
	{
		// ���f���ԍ����擾
		int nModelNldx = m_nDataModelNldx[nCount].Get();

		// ���f���ԍ��̎擾�i���f���̊����j
		nModelNldx = pManagerModel->Regist(pModelGarbage[nCount]);

		// ���f���̓ǂݍ��ݐ����̗L�����m�F
		if (nModelNldx == -1)
		{
			// ���s���ɏ����������𔲂���
			return E_FAIL;
		}

		// ���f���ԍ���ݒ�
		m_nDataModelNldx[nCount].Set(nModelNldx);
	}

	// �S�~
	CFileDataGarbage::Load();

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �S�~�̓ǂݍ��񂾃��f���j��
//-------------------------------------
void CGarbage::Unload(void)
{

}

//-------------------------------------
//- �S�~�̏���������
//-------------------------------------
HRESULT CGarbage::Init(MODEL model)
{
	// ���f���Ǘ��̐���
	CManagerModel *pManagerModel = CManager::GetManagerModel();

	// ���f���Ǘ��̗L���𔻒�
	if (pManagerModel == NULL)
	{
		// �����𔲂���
		return E_FAIL;
	}

	// ���f���ԍ����擾
	int nModelNldx = m_nDataModelNldx[model].Get();

	// �G�̃��f������
	BindModel(nModelNldx, model);

	// �����ݒ菈��
	InitSet(model);

	// X�t�@�C���I�u�W�F�N�g�̏����� if(�����������̗L���𔻒�)
	if (FAILED(CObjectX::Init()))
	{
		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �S�~�̏I������
//-------------------------------------
void CGarbage::Uninit(void)
{
	// X�t�@�C���I�u�W�F�N�g�̏I��
	CObjectX::Uninit();
}

//-------------------------------------
//- �S�~�̍X�V����
//-------------------------------------
void CGarbage::Update(void)
{
	// �t�F�[�Y�����擾
	CSysGamePhase::TYPE pPhaseType = CGame::GetSysGamePhase()->GetType();

	if (pPhaseType == CSysGamePhase::TYPE_SEARCH)
	{
		// �ϐ��錾�i���擾�j
		bool bEat = m_bDataEat.Get();

		if (bEat == true)
		{
			// �H�ׂ��Ԏ��̏���
			UpdateEat();
		}
		else
		{
			// �g�p�\�\������
			AvailableDisplay();
		}

	}

	// X�t�@�C���I�u�W�F�N�g�̍X�V����
	CObjectX::Update();
}

//-------------------------------------
//- �S�~�̕`�揈��
//-------------------------------------
void CGarbage::Draw(void)
{
	// �S�~�̕`�揈��
	CObjectX::Draw();
}

//-------------------------------------
//- �S�~�̐�������
//-------------------------------------
CGarbage *CGarbage::Create(MODEL model)
{
	// �S�~�̐���
	CGarbage *pCGarbage = DBG_NEW CGarbage;

	// �����̐����̗L���𔻒�
	if (pCGarbage != NULL)
	{
		// ����������
		if (FAILED(pCGarbage->Init(model)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCGarbage == NULL)
	{// ���s��

	 // �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// ��ނ�ݒ�
	pCGarbage->SetType(TYPE_ENEMY);

	// �S�~�̃|�C���^��Ԃ�
	return pCGarbage;
}

//-------------------------------------
//-	�S�~�̐ݒ菈��
//-------------------------------------
void CGarbage::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���X�V
	m_dataPos.Set(pos);							// �ʒu
	m_dataPosOld.Set(pos);						// �O��̈ʒu

	m_dataRot.Set(rot);							// ����
	m_dataRotDest.Set(rot);						// �ړI�̌���
}

//-------------------------------------
//-	���f���̐ݒ菈��
//-------------------------------------
int CGarbage::GetModel(void)
{
	// ���f���ݒ�
	return(int)m_model;
}

//-------------------------------------
//-	���f���̐ݒ菈��
//-------------------------------------
void CGarbage::SetModel(int nModelNldx)
{
	// ���f���ݒ�
	m_model = (MODEL)nModelNldx;
}

//-------------------------------------
//-	���f���̏��̐ݒ菈��
//-------------------------------------
void CGarbage::SetModelData(int nNum, CGarbage::ModelData modelData)
{
	// ���f�����̑��
	m_modelData[nNum] = modelData;	// �傫��
}

//-------------------------------------
//-	���f���̏��̎擾����
//-------------------------------------
CGarbage::ModelData CGarbage::GetModelData(int nNum)
{
	// ���f������Ԃ�
	return m_modelData[nNum];
}

//-------------------------------------
//- �S�~�̎��s����
//-------------------------------------
void CGarbage::Execution(int nEatTime)
{
	// �T�E���h�̎擾����
	CSound *pSound = CManager::GetSound();

	// �T�E���h�̗L���𔻒�
	if (pSound == NULL)
	{
		return;
	}

	// SE�̍Đ��i�e���|�j
	pSound->Play(CSound::LABEL_SE_EAT_000);

	// ���X�V
	m_bDataEat.Set(true);			// �H�ׂ�̗L��
	m_nDataEatTime.Set(nEatTime);	// �H�ׂ鎞��
	m_nDataEatCut.Set(0);			// �H�ׂ�J�E���g��������
}

//-------------------------------------
//- �S�~�̏����ݒ菈��
//-------------------------------------
void CGarbage::InitSet(MODEL model)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();	// �ʒu
	D3DXVECTOR3 rot = m_dataRot.Get();	// ����

	// ���X�V
	m_dataPosOld.Set(pos);				// �O��̈ʒu
	m_dataRotDest.Set(rot);				// �ړI�̌���

	// �f�[�^�ݒ�
	m_dataSize.Set(m_modelData[model].size);
	m_nGetScore.Set(m_modelData[model].nScoreHave);
	m_nType.Set(m_modelData[model].nType);
}

//-------------------------------------
//- �S�~�̎g�p�\�\��
//-------------------------------------
void CGarbage::AvailableDisplay(void)
{
	// ���ԊǗ��̏����擾
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// ���ԊǗ��擾�̗L���𔻒�
	if (pManagerTime == NULL)
	{
		// �����𔲂���
		return;
	}

	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();				// �ʒu
	int nEffectCount = m_nDataEffectCount.Get();	// �G�t�F�N�g�o���̃J�E���g

	if (pManagerTime->m_bDataIntCount.Get() == true)
	{
		// �G�t�F�N�g�̃|�C���^��錾
		CEffect *pEffect = NULL;

		// �G�t�F�N�g�J�E���g�����Z
		nEffectCount++;

		// �G�t�F�N�g�J�E���g�̔���
		if (nEffectCount >= 10)
		{
			// �G�t�F�N�g�̐���
			pEffect = CEffect::Create(CEffect::TEX_NORMAL_000);

			// �G�t�F�N�g�̗L���𔻒�
			if (pEffect != NULL)
			{
				// �G�t�F�N�g�J�E���g�̏�����
				nEffectCount = 0;

				// �ʒu����ݒ�
				pEffect->m_dataPos.Set(D3DXVECTOR3(pos.x, pos.y + 20.0f, pos.z));

				// �傫����ݒ�
				pEffect->m_dataSize.Set(D3DXVECTOR3(10.0f, 10.0f, 0.0f));

				// �ړ��ʂ�ݒ�
				pEffect->m_dataMove.Set(D3DXVECTOR3(0.0f, 1.0f, 0.0f));

				if (m_modelData[m_model].nType == 0)
				{
					// �F��ݒ�i��{�F�j
					pEffect->m_dataColor.Set(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
				else if (m_modelData[m_model].nType == 1)
				{
					// �F��ݒ�i��{�F�j
					pEffect->m_dataColor.Set(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
				}

				// �G�t�F�N�g�̐ݒ菈��
				pEffect->m_nDataLife.Set(60);
			}

		}
	}

	// ���X�V
	m_dataPos.Set(pos);						// �ʒu
	m_nDataEffectCount.Set(nEffectCount);	// �G�t�F�N�g�o���̃J�E���g
}

//-------------------------------------
//- �S�~�̐H�ׂ��Ă���Ƃ��̏���
//-------------------------------------
void CGarbage::UpdateEat(void)
{
	// �v���C���[�̃|�C���^���擾
	CPlayer *pPlayer = CSysGamePhase::GetPlayer();

	// �v���C���[�̃|�C���^�̗L���𔻒�
	if (pPlayer == NULL)
	{
		// �����𔲂���
		return;
	}

	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();		// �ʒu
	int nEatTime = m_nDataEatTime.Get();	// �H�ׂ鎞��
	int nEatCut = m_nDataEatCut.Get();		// �H�ׂ�J�E���g

	// ��̈ʒu�����i�ԍ��x�^�ł�[4]�ԁj
	pos.x = pPlayer->GetObjectModel(4)->GetMtxWorld()._41;
	pos.y = pPlayer->GetObjectModel(4)->GetMtxWorld()._42;
	pos.z = pPlayer->GetObjectModel(4)->GetMtxWorld()._43;

	// �H�ׂ�J�E���g�����Z
	nEatCut++;

	if (nEatCut >= nEatTime)
	{
		// �H�ׂ�I������
		EatEnd();
	}

	// ���X�V
	m_dataPos.Set(pos);					// �ʒu
	m_nDataEatCut.Set(nEatCut);			// �H�ׂ�J�E���g
}

//-------------------------------------
//- �S�~�̐H�ׂ�I������
//-------------------------------------
void CGarbage::EatEnd(void)
{
	// �퓬�X�e�[�^�X�̎擾����
	CStateBattle *pStateBattle = CGame::GetStateBattle();

	// �퓬�X�e�[�^�X�̃|�C���^�̗L���𔻒�
	if (pStateBattle == NULL)
	{
		return;
	}

	// �������Z����
	pStateBattle->AddElem(
		m_modelData[m_model].nNor,
		m_modelData[m_model].nLow,
		m_modelData[m_model].nChaos);

	// �I������
	Uninit();
}