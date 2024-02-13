
//-===============================================
//-
//-	���ʂȂ��I�u�W�F�N�g�̏���[item.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "objectx_test.h"

#include "renderer.h"
#include "manager.h"

#include "manager_object.h"

#include "manager_model.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�R���X�g��`
//=======================================

// �e�X�g�p�I�u�W�F�N�g�̃��f���̃R���X�g��`
const char *pModelObjectXTest[] =
{
	"data\\MODEL\\human_box.x",		// �l�^�̊���f��
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

CDataInt CObjectXTest::m_nDataModelNldx[MODEL_MAX] = {};		// ���f���̔ԍ�

//-------------------------------------
//-	���ʂȂ��I�u�W�F�N�g�̃R���X�g���N�^
//-------------------------------------
CObjectXTest::CObjectXTest()
{
	m_model = MODEL_HUMAN_BOX_000;
}

//-------------------------------------
//-	���ʂȂ��I�u�W�F�N�g�̃f�X�g���N�^
//-------------------------------------
CObjectXTest::~CObjectXTest()
{

}

//-------------------------------------
//- �G�̃��f���ǂݍ���
//-------------------------------------
HRESULT CObjectXTest::Load(void)
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
		nModelNldx = pManagerModel->Regist(pModelObjectXTest[nCount]);

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
//- �G�̓ǂݍ��񂾃��f���j��
//-------------------------------------
void CObjectXTest::Unload(void)
{

}

//-------------------------------------
//- ���ʂȂ��I�u�W�F�N�g�̏����������iX�t�@�C���I�u�W�F�N�g�ݒ�j
//-------------------------------------
HRESULT CObjectXTest::Init(MODEL model)
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

	// ���ʂȂ��I�u�W�F�N�g�̃��f������
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
//- ���ʂȂ��I�u�W�F�N�g�̏I������
//-------------------------------------
void CObjectXTest::Uninit(void)
{
	// X�t�@�C���I�u�W�F�N�g�̏I��
	CObjectX::Uninit();
}

//-------------------------------------
//- ���ʂȂ��I�u�W�F�N�g�̍X�V����
//-------------------------------------
void CObjectXTest::Update(void)
{
	// X�t�@�C���I�u�W�F�N�g�̍X�V����
	CObjectX::Update();
}

//-------------------------------------
//- ���ʂȂ��I�u�W�F�N�g�̕`�揈��
//-------------------------------------
void CObjectXTest::Draw(void)
{
	// X�t�@�C���I�u�W�F�N�g�̕`�揈��
	CObjectX::Draw();
}

//-------------------------------------
//- ���ʂȂ��I�u�W�F�N�g�̐��������iX�t�@�C���I�u�W�F�N�g�ݒ�j
//-------------------------------------
CObjectXTest * CObjectXTest::Create(MODEL model)
{
	// ���ʂȂ��I�u�W�F�N�g�̃|�C���^��錾
	CObjectXTest *pCObjectXTest = new CObjectXTest;

	// �����̐����̗L���𔻒�
	if (pCObjectXTest != NULL)
	{
		// ����������
		if (FAILED(pCObjectXTest->Init(model)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCObjectXTest == NULL)
	{// ���s��

	 // �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// ���ʂȂ��I�u�W�F�N�g�̃|�C���^��Ԃ�
	return pCObjectXTest;
}

//-------------------------------------
//-	���f���̐ݒ菈��
//-------------------------------------
int CObjectXTest::GetModel(void)
{
	// ���f���ݒ�
	return(int)m_model;
}

//-------------------------------------
//-	���f���̐ݒ菈��
//-------------------------------------
void CObjectXTest::SetModel(int nModelNldx)
{
	// ���f���ݒ�
	m_model = (MODEL)nModelNldx;
}

//-------------------------------------
//- ���ʂȂ��I�u�W�F�N�g�̐ݒ菈��
//-------------------------------------
void CObjectXTest::Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	// ���X�V
	m_dataPos.Set(pos);		// �ʒu
	m_dataPosOld.Set(pos);	// �O��̈ʒu

	m_dataSize.Set(size);	// �傫��

	m_dataRot.Set(rot);		// �ړ���
	m_dataRotDest.Set(rot);	// �ړI�̌���
}