
//-===============================================
//-
//-	2D�̃A�C�e�����̏���[obj_2d_item_info.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "obj_2d_item_info.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"
#include "manager_object.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//= �R���X�g��`
//=======================================

// �A�C�e�����̃R���X�g��`
const char *pTextureItemInfo[] =
{
	"data\\TEXTURE\\item_info_gun.png",		// �e�̃e�N�X�`��
	"data\\TEXTURE\\item_info_gun.png",		// �e�̃e�N�X�`��
	"data\\TEXTURE\\item_info_gun.png",		// �e�̃e�N�X�`��
	"data\\TEXTURE\\item_info_bomb.png",	// �{���̃e�N�X�`��
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

int CObj2dItemInfo::m_nTextureNldx[CItem::MODEL_MAX] = {};	// �e�N�X�`��

//-------------------------------------
//-	2D�̃A�C�e�����̃R���X�g���N�^
//-------------------------------------
CObj2dItemInfo::CObj2dItemInfo(int nPriority) : CObject2d(nPriority)
{

}

//-------------------------------------
//-	2D�̃A�C�e�����̃f�X�g���N�^
//-------------------------------------
CObj2dItemInfo::~CObj2dItemInfo()
{

}

//-------------------------------------
//- 2D�̃A�C�e�����̃e�N�X�`���̓ǂݍ���
//-------------------------------------
HRESULT CObj2dItemInfo::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

	 // �����������𔲂���
		return E_FAIL;
	}

	// �e�N�X�`���Ǘ��̐���
	CManagerTexture *pManagerTexture = CManager::GetManagerTexture();

	// �e�N�X�`���Ǘ��̗L���𔻒�
	if (pManagerTexture == NULL)
	{
		// �����������𔲂���
		return E_FAIL;
	}

	// �e�N�X�`���ݒ�
	for (int nCount = 0; nCount < CItem::MODEL_MAX; nCount++)
	{
		// �e�N�X�`���ԍ��̎擾�i�e�N�X�`���̊����j
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureItemInfo[nCount]);

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
//- 2D�̃A�C�e�����̓ǂݍ��񂾃e�N�X�`���̔j��
//-------------------------------------
void CObj2dItemInfo::Unload(void)
{

}

//-------------------------------------
//- 2D�̃A�C�e�����̏���������
//-------------------------------------
HRESULT CObj2dItemInfo::Init(CItem::MODEL nModel)
{
	// �e�N�X�`������
	BindTexture(m_nTextureNldx[nModel]);

	// �����ݒ�
	InitSet();

	// 2D�I�u�W�F�N�g�̏�����
	CObject2d::Init();

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- 2D�̃A�C�e�����̏I������
//-------------------------------------
void CObj2dItemInfo::Uninit(void)
{
	// 2D�I�u�W�F�N�g�̏I��
	CObject2d::Uninit();
}

//-------------------------------------
//- 2D�̃A�C�e�����̍X�V����
//-------------------------------------
void CObj2dItemInfo::Update(void)
{
	// 2D�I�u�W�F�N�g�̍X�V����
	CObject2d::Update();
}

//-------------------------------------
//- 2D�̃A�C�e�����̕`�揈��
//-------------------------------------
void CObj2dItemInfo::Draw(void)
{
	// �ϐ��錾�i���擾�j
	bool bDraw = m_bDataDraw.Get();	// �`��̗L��

	if (bDraw == true)
	{
		// 2d�I�u�W�F�N�g�̕`�揈��
		CObject2d::Draw();

		// �`���~������
		bDraw = false;
	}

	// ���X�V
	m_bDataDraw.Set(bDraw);	// �`��̗L��
}

//-------------------------------------
//- 2D�̃A�C�e�����̐�������
//-------------------------------------
CObj2dItemInfo *CObj2dItemInfo::Create(CItem::MODEL nModel)
{
	// 2D�̃A�C�e�����̃|�C���^��錾
	CObj2dItemInfo *pCObj2dItemInfo = DBG_NEW CObj2dItemInfo(7);

	// �����̐����̗L���𔻒�
	if (pCObj2dItemInfo != NULL)
	{
		// ���������� if(�����������̗L���𔻒�)
		if (FAILED(pCObj2dItemInfo->Init(nModel)))
		{// ���s��

		 // �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCObj2dItemInfo == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// ��ނ�ݒ�
	pCObj2dItemInfo->SetType(TYPE_BLOCK);

	// 2D�̃A�C�e�����̃|�C���^��Ԃ�
	return pCObj2dItemInfo;
}

//-------------------------------------
//- 2D�̃A�C�e�����̐ݒ菈��
//-------------------------------------
void CObj2dItemInfo::Set(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_dataPos.Set(pos);
	m_dataSize.Set(size);
}

//-------------------------------------
//- 2D�̃A�C�e�����̏����ݒ菈��
//-------------------------------------
void CObj2dItemInfo::InitSet(void)
{
	m_dataPos.Set(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.85f, 0.0f));
	m_dataSize.Set(D3DXVECTOR3(SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.1f, 0.0f));
}