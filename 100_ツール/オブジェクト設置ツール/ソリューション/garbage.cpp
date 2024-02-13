
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

#include "manager_model.h"
#include "manager_object.h"

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
CGarbage::CGarbage()
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
	CGarbage *pCGarbage = new CGarbage;
	
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

	m_dataSize.Set(
		D3DXVECTOR3(10.0f, 0.0f, 10.0f));		// �傫��

	m_scoreGetType = CScore::GET_TYPE_RANDOM;	// �X�R�A�̎擾�n��

	m_nGetScore.Set(0);							// �X�R�A�̓����	
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

	m_scoreGetType = CScore::GET_TYPE_RANDOM;	// �X�R�A�̎擾�n��

	m_nGetScore.Set(0);							// �X�R�A�̓����
}