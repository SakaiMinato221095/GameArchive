
//-===============================================
//-
//-	�Q�[�g�̏���[gate.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "gate.h"

#include "renderer.h"
#include "manager.h"
#include "game.h"

#include "sound.h"

#include "manager_model.h"
#include "manager_object.h"
#include "time_stop.h"

#include "mgr_sys_obj.h"
#include "sys_game_phase.h"

#include "effect.h"
#include "particle.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�R���X�g��`
//=======================================

// �Q�[�g�̃��f���̃R���X�g��`
const char *pModelGate[] =
{
	"data\\MODEL\\gate.x",			// �Q�[�g�̃��f��
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

CDataInt CGate::m_nDataModelNldx[MODEL_MAX] = {};

//-------------------------------------
//-	�Q�[�g�̃R���X�g���N�^
//-------------------------------------
CGate::CGate(int nPriority) : CObjectX(nPriority)
{
	m_model = (MODEL)0;
}

//-------------------------------------
//-	�Q�[�g�̃f�X�g���N�^
//-------------------------------------
CGate::~CGate()
{

}

//-------------------------------------
//- �Q�[�g�̃��f���ǂݍ���
//-------------------------------------
HRESULT CGate::Load(void)
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
		nModelNldx = pManagerModel->Regist(pModelGate[nCount]);

		// ���f���̓ǂݍ��ݐ����̗L�����m�F
		if (nModelNldx == -1)
		{
			// ���s���ɏ����������𔲂���
			return E_FAIL;
		}

		// ���f���ԍ���ݒ�
		m_nDataModelNldx[nCount].Set(nModelNldx);
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �Q�[�g�̓ǂݍ��񂾃��f���j��
//-------------------------------------
void CGate::Unload(void)
{

}

//-------------------------------------
//- �Q�[�g�̏���������
//-------------------------------------
HRESULT CGate::Init(MODEL model)
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
//- �Q�[�g�̏I������
//-------------------------------------
void CGate::Uninit(void)
{
	// X�t�@�C���I�u�W�F�N�g�̏I��
	CObjectX::Uninit();
}

//-------------------------------------
//- �Q�[�g�̍X�V����
//-------------------------------------
void CGate::Update(void)
{
	// �t�F�[�Y�����擾
	CSysGamePhase::TYPE pPhaseType = CGame::GetSysGamePhase()->GetType();

	if (pPhaseType == CSysGamePhase::TYPE_SEARCH || 
		pPhaseType == CSysGamePhase::TYPE_BATTLE)
	{
		// �g�p�\�\������
		AvailableDisplay();
	}

	// X�t�@�C���I�u�W�F�N�g�̍X�V����
	CObjectX::Update();
}

//-------------------------------------
//- �Q�[�g�̕`�揈��
//-------------------------------------
void CGate::Draw(void)
{
	// �Q�[�g�̕`�揈��
	CObjectX::Draw();
}

//-------------------------------------
//- �Q�[�g�̐�������
//-------------------------------------
CGate *CGate::Create(MODEL model)
{
	// �Q�[�g�̐���
	CGate *pCGate = DBG_NEW CGate;

	// �����̐����̗L���𔻒�
	if (pCGate != NULL)
	{
		// ����������
		if (FAILED(pCGate->Init(model)))
		{// ���s��

		 // �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCGate == NULL)
	{// ���s��

	 // �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// ��ނ�ݒ�
	pCGate->SetType(TYPE_ENEMY);

	// �Q�[�g�̃|�C���^��Ԃ�
	return pCGate;
}

//-------------------------------------
//-	���f���̐ݒ菈��
//-------------------------------------
int CGate::GetModel(void)
{
	// ���f���ݒ�
	return(int)m_model;
}

//-------------------------------------
//-	���f���̐ݒ菈��
//-------------------------------------
void CGate::SetModel(int nModelNldx)
{
	// ���f���ݒ�
	m_model = (MODEL)nModelNldx;
}

//-------------------------------------
//- �Q�[�g�̎��s����
//-------------------------------------
void CGate::Execution()
{
	// �T�E���h�̎擾����
	CSound *pSound = CManager::GetSound();

	// �T�E���h�̗L���𔻒�
	if (pSound == NULL)
	{
		return;
	}

	// SE�̍Đ��i�e���|�j
	pSound->Play(CSound::LABEL_SE_TLEPORT_000);

	return;
}

//-------------------------------------
//- �Q�[�g�̏����ݒ菈��
//-------------------------------------
void CGate::InitSet(MODEL model)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();	// �ʒu
	D3DXVECTOR3 rot = m_dataRot.Get();	// ����

	// ���X�V
	m_dataPosOld.Set(pos);				// �O��̈ʒu
	m_dataRotDest.Set(rot);				// �ړI�̌���

	m_dataSize.Set(D3DXVECTOR3(100.0f,100.0f,100.0f));
}

//-------------------------------------
//- �Q�[�g�̎g�p�\�\��
//-------------------------------------
void CGate::AvailableDisplay(void)
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
