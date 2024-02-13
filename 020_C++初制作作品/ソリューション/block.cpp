
//-===============================================
//-
//-	�u���b�N�̏���[block.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "block.h"

#include "renderer.h"
#include "manager.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

LPDIRECT3DTEXTURE9 CBlock::m_pTexture = NULL;

//-------------------------------------
//-	�u���b�N�̃R���X�g���N�^
//-------------------------------------
CBlock::CBlock(int nPriority) : CObject2d(nPriority)
{

}

//-------------------------------------
//-	�u���b�N�̃f�X�g���N�^
//-------------------------------------
CBlock::~CBlock()
{

}

//-------------------------------------
//- �u���b�N�̃e�N�X�`���̓ǂݍ���
//-------------------------------------
HRESULT CBlock::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

		// �����������𔲂���
		return E_FAIL;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\block000.jpg",
		&m_pTexture);

	// �e�N�X�`���̓ǂݍ��ݐ����̗L�����m�F
	if (m_pTexture == NULL)
	{
		// ���s���ɏ����������𔲂���
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �u���b�N�̓ǂݍ��񂾃e�N�X�`���̔j��
//-------------------------------------
void CBlock::Unload(void)
{

}

//-------------------------------------
//- �u���b�N�̏���������
//-------------------------------------
HRESULT CBlock::Init(void)
{
	// 2D�I�u�W�F�N�g�̏�����
	CObject2d::Init();

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �u���b�N�̏I������
//-------------------------------------
void CBlock::Uninit(void)
{
	// 2D�I�u�W�F�N�g�̏I��
	CObject2d::Uninit();
}

//-------------------------------------
//- �u���b�N�̍X�V����
//-------------------------------------
void CBlock::Update(void)
{
	// 2D�I�u�W�F�N�g�̍X�V����
	CObject2d::Update();
}

//-------------------------------------
//- �u���b�N�̕`�揈��
//-------------------------------------
void CBlock::Draw(void)
{
	// �u���b�N�̕`�揈��
	CObject2d::Draw();
}

//-------------------------------------
//- �u���b�N�̐�������
//-------------------------------------
CBlock *CBlock::Create(void)
{
	// �u���b�N�̃|�C���^��錾
	CBlock *pCBlock = DBG_NEW CBlock;

	// �����̐����̗L���𔻒�
	if (pCBlock != NULL)
	{
		// ���������� if(�����������̗L���𔻒�)
		if (FAILED(pCBlock->Init()))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCBlock == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// ��ނ�ݒ�
	pCBlock->SetType(TYPE_BLOCK);

	//// �e�N�X�`���̊���
	//pCBlock->BindTexture(m_pTexture);

	// �u���b�N�̃|�C���^��Ԃ�
	return pCBlock;
}