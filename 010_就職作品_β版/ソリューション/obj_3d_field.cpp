
//-===============================================
//-
//-	�n�ʏ���[obj_3d_field.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "obj_3d_field.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�R���X�g��`
//=======================================

// 3D�n�ʂ̃e�N�X�`���̃R���X�g��`
const char *pTextureField[] =
{
	NULL,										// �e�N�X�`���Ȃ�
	"data\\TEXTURE\\WhiteTile000.jpg",			// �t�B�[���h�̃e�N�X�`��
	"data\\TEXTURE\\road000.png",				// ���H�̃e�N�X�`��
	"data\\TEXTURE\\asphalt000.jpg",			// �A�X�t�@���g�̃e�N�X�`��
	"data\\TEXTURE\\field_glass000.jpg",		// �����̃e�N�X�`��
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

int CObj3dField::m_nTextureNldx[TEX_MAX] = {};

//-------------------------------------
//-	3D�n�ʂ̃R���X�g���N�^
//-------------------------------------
CObj3dField::CObj3dField(int nPriority) : CObject3d(nPriority)
{

}

//-------------------------------------
//-	3D�n�ʂ̃f�X�g���N�^
//-------------------------------------
CObj3dField::~CObj3dField()
{

}

//-------------------------------------
//- 3D�n�ʂ̃e�N�X�`���̓ǂݍ���
//-------------------------------------
HRESULT CObj3dField::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

	 // �����������𔲂���
		return E_FAIL;
	}

	// �e�N�X�`���Ǘ��̐���
	CManagerTexture *pManagerTexture = CManager::GetInstance()->GetManagerTexture();

	// �e�N�X�`���Ǘ��̗L���𔻒�
	if (pManagerTexture == NULL)
	{
		// �����������𔲂���
		return E_FAIL;
	}

	// �e�N�X�`���ݒ�
	for (int nCount = 0; nCount < TEX_MAX; nCount++)
	{
		// �e�N�X�`���ԍ��̎擾�i�e�N�X�`���̊����j
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureField[nCount]);

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
//- 3D�n�ʂ̓ǂݍ��񂾃e�N�X�`���̔j��
//-------------------------------------
void CObj3dField::Unload(void)
{

}
//-------------------------------------
//- 3D�n�ʂ̏����������i3D�I�u�W�F�N�g�ݒ�j
//-------------------------------------
HRESULT CObj3dField::Init(TEX tex)
{
	// �e�N�X�`������
	BindTexture(m_nTextureNldx[tex]);

	// 3D�I�u�W�F�N�g�̏�����
	CObject3d::Init();

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- 3D�n�ʂ̏I������
//-------------------------------------
void CObj3dField::Uninit(void)
{
	// 3D�I�u�W�F�N�g�̏I��
	CObject3d::Uninit();
}

//-------------------------------------
//- 3D�n�ʂ̍X�V����
//-------------------------------------
void CObj3dField::Update(void)
{
	// 3D�I�u�W�F�N�g�̍X�V����
	CObject3d::Update();
}

//-------------------------------------
//- 3D�n�ʂ̕`�揈��
//-------------------------------------
void CObj3dField::Draw(void)
{
	// 3D�I�u�W�F�N�g�̕`�揈��
	CObject3d::Draw();
}

//-------------------------------------
//- 3D�n�ʂ̐�������
//-------------------------------------
CObj3dField *CObj3dField::Create(TEX tex)
{
	// �t�B�[���h�̃|�C���^��錾
	CObj3dField *pCObj3dField = DBG_NEW CObj3dField(4);

	// �����̐����̗L���𔻒�
	if (pCObj3dField != NULL)
	{
		// ����������
		if (FAILED(pCObj3dField->Init(tex)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCObj3dField == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �t�B�[���h�̃|�C���^��Ԃ�
	return pCObj3dField;
}

//-------------------------------------
//-	3D�I�u�W�F�N�g�̒��_���ݒ菈��
//-------------------------------------
void CObj3dField::SetVtx(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 size = GetVtxData().size;		// �T�C�Y
	D3DXCOLOR color = GetVtxData().color;		// �F
	D3DXVECTOR2 texPos = GetVtxData().texPos;	// �e�N�X�`���ʒu

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

	 // �����������𔲂���
		return;
	}
	
	if (GetVtxBuff() != nullptr)
	{
		// 3D���_���̃|�C���^��錾
		VERTEX_3D* pVtx;

		//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
		GetVtxBuff()->Lock(
			0,
			0,
			(void**)&pVtx,
			0);

		//���_���W
		pVtx[0].pos = D3DXVECTOR3(-size.x, 0.0f, size.z);
		pVtx[1].pos = D3DXVECTOR3(size.x, 0.0f, size.z);
		pVtx[2].pos = D3DXVECTOR3(-size.x, 0.0f, -size.z);
		pVtx[3].pos = D3DXVECTOR3(size.x, 0.0f, -size.z);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[��ݒ�
		pVtx[0].col = color;
		pVtx[1].col = color;
		pVtx[2].col = color;
		pVtx[3].col = color;

		//�e�N�X�`���̍��W��ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(texPos.x, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, texPos.y);
		pVtx[3].tex = D3DXVECTOR2(texPos.x, texPos.y);

		//���_�o�b�t�@���A�����b�N����
		GetVtxBuff()->Unlock();
	}
}