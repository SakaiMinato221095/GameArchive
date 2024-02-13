
//-===============================================
//-
//-	�A�C�e���̏���[item.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "item.h"

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

// �A�C�e���̃��f���̃R���X�g��`
const char *pModelItem[] =
{
	"data\\MODEL\\gun_copper.x",	// �e�̃��f��
	"data\\MODEL\\gun_silver.x",	// �e�̃��f��
	"data\\MODEL\\gun_gold.x",		// �e�̃��f��

	"data\\MODEL\\Bomb.x",			// �{���̃��f��
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

CDataInt CItem::m_nDataModelNldx[MODEL_MAX] = {};		// ���f���̔ԍ�

//-------------------------------------
//-	�A�C�e���̃R���X�g���N�^
//-------------------------------------
CItem::CItem()
{

}

//-------------------------------------
//-	�A�C�e���̃f�X�g���N�^
//-------------------------------------
CItem::~CItem()
{

}

//-------------------------------------
//- �G�̃��f���ǂݍ���
//-------------------------------------
HRESULT CItem::Load(void)
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
		nModelNldx = pManagerModel->Regist(pModelItem[nCount]);

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
void CItem::Unload(void)
{

}

//-------------------------------------
//- �A�C�e���̏����������iX�t�@�C���I�u�W�F�N�g�ݒ�j
//-------------------------------------
HRESULT CItem::Init(MODEL model)
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

	// ��ނ̔���
	switch (model)
	{
	case MODEL_GUN_000:

		// �ő�w���񐔂̐ݒ�
		m_nBuyMax.Set(1);	

		break;

	case MODEL_BOMB_000:

		// �ő�w���񐔂̐ݒ�
		m_nBuyMax.Set(5);	

		break;
	}

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
//- �A�C�e���̏I������
//-------------------------------------
void CItem::Uninit(void)
{
	// X�t�@�C���I�u�W�F�N�g�̏I��
	CObjectX::Uninit();
}

//-------------------------------------
//- �A�C�e���̍X�V����
//-------------------------------------
void CItem::Update(void)
{
	// ���ԊǗ��̏����擾
	CManagerTime *pManagerTime = CManager::GetManagerTime();

	// ���ԊǗ��擾�̗L���𔻒�
	if (pManagerTime == NULL)
	{
		// �����𔲂���
		return;
	}

	// �ϐ��錾�i���擾�j
	bool bUse = m_bDataUse.Get();				// �g�p�̗L��
	D3DXVECTOR3 rotAdd = m_dataRotAdd.Get();	// ��]��

	// ���Ԕ{���̌v�Z
	D3DXVECTOR3 rotAddTime = pManagerTime->CalRate(rotAdd);

	// ��]����
	AddRot(rotAddTime);

	// X�t�@�C���I�u�W�F�N�g�̍X�V����
	CObjectX::Update();
}

//-------------------------------------
//- �A�C�e���̕`�揈��
//-------------------------------------
void CItem::Draw(void)
{
	// X�t�@�C���I�u�W�F�N�g�̕`�揈��
	CObjectX::Draw();
}

//-------------------------------------
//- �A�C�e���̐��������iX�t�@�C���I�u�W�F�N�g�ݒ�j
//-------------------------------------
CItem * CItem::Create(MODEL model)
{
	// �A�C�e���̃|�C���^��錾
	CItem *pCItem = new CItem;

	// �����̐����̗L���𔻒�
	if (pCItem != NULL)
	{
		// ����������
		if (FAILED(pCItem->Init(model)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCItem == NULL)
	{// ���s��

	 // �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �A�C�e���̃|�C���^��Ԃ�
	return pCItem;
}

//-------------------------------------
//-	���f���̐ݒ菈��
//-------------------------------------
int CItem::GetModel(void)
{
	// ���f���ݒ�
	return(int)m_model;
}

//-------------------------------------
//-	���f���̐ݒ菈��
//-------------------------------------
void CItem::SetModel(int nModelNldx)
{
	// ���f���ݒ�
	m_model = (MODEL)nModelNldx;
}

//-------------------------------------
//- �A�C�e���̐ݒ菈��
//-------------------------------------
void CItem::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���X�V
	m_dataPos.Set(pos);		// �ʒu
	m_dataPosOld.Set(pos);	// �O��̈ʒu

	m_dataRot.Set(rot);		// �ړ���
	m_dataRotDest.Set(rot);	// �ړI�̌���

	m_dataSize.Set(D3DXVECTOR3(0.0f, 0.01f, 0.0f));	// �傫��

	m_dataRotAdd.Set(D3DXVECTOR3(0.0f,0.01f,0.0f));	// ��]��
}