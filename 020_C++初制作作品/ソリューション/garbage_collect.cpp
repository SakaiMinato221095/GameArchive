
//-===============================================
//-
//-	�S�~���W�̏���[garbage_collect.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "garbage_collect.h"

#include "renderer.h"
#include "manager.h"
#include "game.h"

#include "manager_model.h"
#include "manager_object.h"
#include "time_stop.h"

#include "mgr_sys_obj.h"
#include "sys_game_phase.h"

#include "effect.h"
#include "particle.h"

#include "file_data_garbage_collect.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�R���X�g��`
//=======================================

// �S�~���W�̃��f���̃R���X�g��`
const char *pModelGarbageCollect[] =
{
	"data\\MODEL\\garbage_car000.x",			// �S�~���W�Ԃ̃��f��
	"data\\MODEL\\dark_garbage_car000.x",		// �ł̃S�~���W�Ԃ̃��f��
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

CDataInt CGarbageCollect::m_nDataModelNldx[MODEL_MAX] = {};

CGarbageCollect::ModelData CGarbageCollect::m_modelData[MODEL_MAX] = {};		// ���f�����

//-------------------------------------
//-	�S�~�̃R���X�g���N�^
//-------------------------------------
CGarbageCollect::CGarbageCollect(int nPriority) : CObjectX(nPriority)
{
	m_model = (MODEL)0;
}

//-------------------------------------
//-	�S�~�̃f�X�g���N�^
//-------------------------------------
CGarbageCollect::~CGarbageCollect()
{

}

//-------------------------------------
//- �S�~�̃��f���ǂݍ���
//-------------------------------------
HRESULT CGarbageCollect::Load(void)
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
		nModelNldx = pManagerModel->Regist(pModelGarbageCollect[nCount]);

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
	CFileDataGarbageCollect::Load();

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �S�~�̓ǂݍ��񂾃��f���j��
//-------------------------------------
void CGarbageCollect::Unload(void)
{

}

//-------------------------------------
//- �S�~�̏���������
//-------------------------------------
HRESULT CGarbageCollect::Init(MODEL model)
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

	// �f�[�^�ݒ�
	m_dataSize.Set(m_modelData[model].size);

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
void CGarbageCollect::Uninit(void)
{
	// X�t�@�C���I�u�W�F�N�g�̏I��
	CObjectX::Uninit();
}

//-------------------------------------
//- �S�~�̍X�V����
//-------------------------------------
void CGarbageCollect::Update(void)
{
	// �t�F�[�Y�����擾
	CSysGamePhase::TYPE pPhaseType = CGame::GetSysGamePhase()->GetType();

	if (pPhaseType == CSysGamePhase::TYPE_SEARCH)
	{
		// �g�p�\�\������
		AvailableDisplay();
	}

	// X�t�@�C���I�u�W�F�N�g�̍X�V����
	CObjectX::Update();
}

//-------------------------------------
//- �S�~�̕`�揈��
//-------------------------------------
void CGarbageCollect::Draw(void)
{
	// �S�~�̕`�揈��
	CObjectX::Draw();
}

//-------------------------------------
//- �S�~�̐�������
//-------------------------------------
CGarbageCollect *CGarbageCollect::Create(MODEL model)
{
	// �S�~�̐���
	CGarbageCollect *pCGarbageCollect = DBG_NEW CGarbageCollect;

	// �����̐����̗L���𔻒�
	if (pCGarbageCollect != NULL)
	{
		// ����������
		if (FAILED(pCGarbageCollect->Init(model)))
		{// ���s��

		 // �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCGarbageCollect == NULL)
	{// ���s��

	 // �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// ��ނ�ݒ�
	pCGarbageCollect->SetType(TYPE_ENEMY);

	// �S�~�̃|�C���^��Ԃ�
	return pCGarbageCollect;
}

//-------------------------------------
//-	���f���̐ݒ菈��
//-------------------------------------
int CGarbageCollect::GetModel(void)
{
	// ���f���ݒ�
	return(int)m_model;
}

//-------------------------------------
//-	���f���̐ݒ菈��
//-------------------------------------
void CGarbageCollect::SetModel(int nModelNldx)
{
	// ���f���ݒ�
	m_model = (MODEL)nModelNldx;
}

//-------------------------------------
//-	���f���̏��̐ݒ菈��
//-------------------------------------
void CGarbageCollect::SetModelData(int nNum, CGarbageCollect::ModelData modelData)
{
	// ���f�����̑��
	m_modelData[nNum] = modelData;	// �傫��
}

//-------------------------------------
//-	���f���̏��̎擾����
//-------------------------------------
CGarbageCollect::ModelData CGarbageCollect::GetModelData(int nNum)
{
	// ���f������Ԃ�
	return m_modelData[nNum];
}

//-------------------------------------
//- �S�~�̎��s����
//-------------------------------------
void CGarbageCollect::Execution()
{
	return;
}

//-------------------------------------
//- �S�~�̏����ݒ菈��
//-------------------------------------
void CGarbageCollect::InitSet(MODEL model)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();	// �ʒu
	D3DXVECTOR3 rot = m_dataRot.Get();	// ����

	// ���X�V
	m_dataPosOld.Set(pos);				// �O��̈ʒu
	m_dataRotDest.Set(rot);				// �ړI�̌���
}

//-------------------------------------
//- �S�~�̎g�p�\�\��
//-------------------------------------
void CGarbageCollect::AvailableDisplay(void)
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

				// �F��ݒ�i��{�F�j
				pEffect->m_dataColor.Set(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

				// �G�t�F�N�g�̐ݒ菈��
				pEffect->m_nDataLife.Set(60);
			}

		}
	}

	// ���X�V
	m_dataPos.Set(pos);						// �ʒu
	m_nDataEffectCount.Set(nEffectCount);	// �G�t�F�N�g�o���̃J�E���g
}
