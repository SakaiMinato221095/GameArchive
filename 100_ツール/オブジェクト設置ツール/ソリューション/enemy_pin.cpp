
//-===============================================
//-
//-	�G�l�~�[�s���̏���[enemy_pin.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "enemy_pin.h"

#include "renderer.h"
#include "manager.h"

#include "manager_model.h"
#include "manager_time.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�R���X�g��`
//=======================================

// �G�l�~�[�s���̃��f���̃R���X�g��`
const char *pModelEnemyPin[] =
{
	"data\\MODEL\\enemy_pin.x",				// �G�l�~�[�s���̃��f��
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

CDataInt CEnemyPin::m_nDataModelNldx[MODEL_MAX] = {};

//-------------------------------------
//-	�I�u�W�F�N�g�C�x���g�̃R���X�g���N�^
//-------------------------------------
CEnemyPin::CEnemyPin()
{
}

//-------------------------------------
//-	�I�u�W�F�N�g�C�x���g�̃f�X�g���N�^
//-------------------------------------
CEnemyPin::~CEnemyPin()
{

}

//-------------------------------------
//- �I�u�W�F�N�g�C�x���g�̃��f���ǂݍ���
//-------------------------------------
HRESULT CEnemyPin::Load(void)
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
		nModelNldx = pManagerModel->Regist(pModelEnemyPin[nCount]);

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
//- �I�u�W�F�N�g�C�x���g�̓ǂݍ��񂾃��f���j��
//-------------------------------------
void CEnemyPin::Unload(void)
{

}

//-------------------------------------
//- �I�u�W�F�N�g�C�x���g�̏���������
//-------------------------------------
HRESULT CEnemyPin::Init(MODEL model)
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
//- �I�u�W�F�N�g�C�x���g�̏I������
//-------------------------------------
void CEnemyPin::Uninit(void)
{
	// X�t�@�C���I�u�W�F�N�g�̏I��
	CObjectX::Uninit();
}

//-------------------------------------
//- �I�u�W�F�N�g�C�x���g�̍X�V����
//-------------------------------------
void CEnemyPin::Update(void)
{
	// X�t�@�C���I�u�W�F�N�g�̍X�V����
	CObjectX::Update();
}

//-------------------------------------
//- �I�u�W�F�N�g�C�x���g�̕`�揈��
//-------------------------------------
void CEnemyPin::Draw(void)
{
	// �I�u�W�F�N�g�C�x���g�̕`�揈��
	CObjectX::Draw();
}

//-------------------------------------
//- �I�u�W�F�N�g�C�x���g�̐�������
//-------------------------------------
CEnemyPin *CEnemyPin::Create(MODEL model)
{
	// �I�u�W�F�N�g�C�x���g�̐���
	CEnemyPin *pCEnemyPin = new CEnemyPin;

	// �����̐����̗L���𔻒�
	if (pCEnemyPin != NULL)
	{
		// ����������
		if (FAILED(pCEnemyPin->Init(model)))
		{// ���s��

		 // �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCEnemyPin == NULL)
	{// ���s��

	 // �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �I�u�W�F�N�g�C�x���g�̃|�C���^��Ԃ�
	return pCEnemyPin;
}

//-------------------------------------
//- �I�u�W�F�N�g�C�x���g�̐ݒ菈��
//-------------------------------------
void CEnemyPin::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���X�V
	m_dataPos.Set(pos);							// �ʒu
	m_dataPosOld.Set(pos);						// �O��̈ʒu

	m_dataRot.Set(rot);							// ����
	m_dataRotDest.Set(rot);						// �ړI�̌���

	m_dataSize.Set(
		D3DXVECTOR3(10.0f, 0.0f, 10.0f));		// �傫��
}

//-------------------------------------
//-	���f���̐ݒ菈��
//-------------------------------------
int CEnemyPin::GetModel(void)
{
	// ���f���ݒ�
	return(int)m_model;
}

//-------------------------------------
//-	���f���̐ݒ菈��
//-------------------------------------
void CEnemyPin::SetModel(int nModelNldx)
{
	// ���f���ݒ�
	m_model = (MODEL)nModelNldx;
}