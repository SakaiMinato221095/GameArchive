
//-===============================================
//-
//-	���ʂȂ��I�u�W�F�N�g�̏���[item.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "objectx_none.h"

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

// ���ʂȂ��I�u�W�F�N�g�̃��f���̃R���X�g��`
const char *pModelObjectXNone[] =
{
	"data\\MODEL\\none\\obarafood.x",			// ���X�X�i�H���j
	"data\\MODEL\\none\\obamart.x",				// ���X�X�i���z�X�j
	"data\\MODEL\\none\\obarastation.x",		// ���X�X�i�Q�[���Z���^�[�j
	"data\\MODEL\\none\\obarakurabu000.x",		// ���X�X�i�G�ݓX�j	
	"data\\MODEL\\none\\obarameat000.x",		// ���X�X�i�����X�j	
	"data\\MODEL\\none\\obaravegetable000.x",	// ���X�X�i�ʓX�j	
	"data\\MODEL\\none\\obaraflour000.x",		// ���X�X�i�ԉ��j	
	"data\\MODEL\\none\\obaraclothes000.x",		// ���X�X�i�����j	

	"data\\MODEL\\none\\sunaba001.x",			// �����i����j
	"data\\MODEL\\none\\Toilet001.x",			// �����i�g�C���j
	"data\\MODEL\\none\\suidou.x",				// �����i�����j
	"data\\MODEL\\none\\gomibako001.x",			// �����i�S�~���j
	"data\\MODEL\\none\\benti001.x",			// �����i�x���`�j
	"data\\MODEL\\none\\gaitou001.x",			// �����i�X���j
	"data\\MODEL\\none\\tetubou001.x",			// �����i�S�_�j
	"data\\MODEL\\none\\suberidai001.x",		// �����i�����j

	"data\\MODEL\\none\\House001.x",			// �Ɓi1�j
	"data\\MODEL\\none\\House002.x",			// �Ɓi2�j
	"data\\MODEL\\none\\House003.x",			// �Ɓi3�j

	"data\\MODEL\\none\\street_stall_dark.x",	// �ŘI�X
	"data\\MODEL\\none\\house_blood.x",			// ���t���̉�

	"data\\MODEL\\none\\zinja.x",				// �_��
	"data\\MODEL\\none\\omikuji.x",				// ���݂���

	"data\\MODEL\\none\\yakisoba.x",			// �₫����
	"data\\MODEL\\none\\kakigoori.x",			// �����X
	"data\\MODEL\\none\\wanage.x",				// �֓���
	"data\\MODEL\\none\\takoyaki.x",			// �����₫
	"data\\MODEL\\none\\yo-yo-turi.x",			// ��[��[�ނ�

	"data\\MODEL\\none\\tree.x",				// ��
	"data\\MODEL\\none\\bld_torii.x",			// ����

	"data\\MODEL\\none\\NinjaMansion000.x",		// ���~
	"data\\MODEL\\none\\Scarecrow000.x",		// ������
	"data\\MODEL\\none\\sisiodosi000.x",		// �������ǂ�
	"data\\MODEL\\none\\Sakura000.x",			// ��

	"data\\MODEL\\none\\plant.x",				// �H��

	

};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

CDataInt CObjectXNone::m_nDataModelNldx[MODEL_MAX] = {};		// ���f���̔ԍ�

//-------------------------------------
//-	���ʂȂ��I�u�W�F�N�g�̃R���X�g���N�^
//-------------------------------------
CObjectXNone::CObjectXNone()
{
	m_model = MODEL(0);
}

//-------------------------------------
//-	���ʂȂ��I�u�W�F�N�g�̃f�X�g���N�^
//-------------------------------------
CObjectXNone::~CObjectXNone()
{

}

//-------------------------------------
//- �G�̃��f���ǂݍ���
//-------------------------------------
HRESULT CObjectXNone::Load(void)
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
		nModelNldx = pManagerModel->Regist(pModelObjectXNone[nCount]);

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
void CObjectXNone::Unload(void)
{

}

//-------------------------------------
//- ���ʂȂ��I�u�W�F�N�g�̏����������iX�t�@�C���I�u�W�F�N�g�ݒ�j
//-------------------------------------
HRESULT CObjectXNone::Init(MODEL model)
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
	BindModel(nModelNldx,model);

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
void CObjectXNone::Uninit(void)
{
	// X�t�@�C���I�u�W�F�N�g�̏I��
	CObjectX::Uninit();
}

//-------------------------------------
//- ���ʂȂ��I�u�W�F�N�g�̍X�V����
//-------------------------------------
void CObjectXNone::Update(void)
{
	// X�t�@�C���I�u�W�F�N�g�̍X�V����
	CObjectX::Update();
}

//-------------------------------------
//- ���ʂȂ��I�u�W�F�N�g�̕`�揈��
//-------------------------------------
void CObjectXNone::Draw(void)
{
	// X�t�@�C���I�u�W�F�N�g�̕`�揈��
	CObjectX::Draw();
}

//-------------------------------------
//- ���ʂȂ��I�u�W�F�N�g�̐��������iX�t�@�C���I�u�W�F�N�g�ݒ�j
//-------------------------------------
CObjectXNone * CObjectXNone::Create(MODEL model)
{
	// ���ʂȂ��I�u�W�F�N�g�̃|�C���^��錾
	CObjectXNone *pCObjectXNone = new CObjectXNone;

	// �����̐����̗L���𔻒�
	if (pCObjectXNone != NULL)
	{
		// ����������
		if (FAILED(pCObjectXNone->Init(model)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCObjectXNone == NULL)
	{// ���s��

	 // �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// ���ʂȂ��I�u�W�F�N�g�̃|�C���^��Ԃ�
	return pCObjectXNone;
}

//-------------------------------------
//-	���f���̐ݒ菈��
//-------------------------------------
int CObjectXNone::GetModel(void)
{
	// ���f���ݒ�
	return(int)m_model;
}

//-------------------------------------
//-	���f���̐ݒ菈��
//-------------------------------------
void CObjectXNone::SetModel(int nModelNldx)
{
	// ���f���ݒ�
	m_model = (MODEL)nModelNldx;
}

//-------------------------------------
//- ���ʂȂ��I�u�W�F�N�g�̐ݒ菈��
//-------------------------------------
void CObjectXNone::Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	// ���X�V
	m_dataPos.Set(pos);		// �ʒu
	m_dataPosOld.Set(pos);	// �O��̈ʒu

	m_dataSize.Set(size);	// �傫��

	m_dataRot.Set(rot);		// �ړ���
	m_dataRotDest.Set(rot);	// �ړI�̌���
}