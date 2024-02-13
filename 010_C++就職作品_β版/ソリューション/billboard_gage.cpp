
//================================================
//=
//= �Q�[�W�̃r���{�[�h�̏���[billboard_gage.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "billboard_gage.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

//=======================================
//=	�}�N����`
//=======================================

//------------------------------------
//- �r���{�[�h�I�u�W�F�N�g�̃R���X�g���N�^
//------------------------------------
CBillboardGage::CBillboardGage(int nPriority) : CBillboard(nPriority)
{
	// �l���N���A
	ZeroMemory(&m_info, sizeof(m_info));
}

//------------------------------------
//- �r���{�[�h�I�u�W�F�N�g�̃f�X�g���N�^
//------------------------------------
CBillboardGage::~CBillboardGage()
{
}

//------------------------------------
//- �r���{�[�h�I�u�W�F�N�g�̏���������
//------------------------------------
HRESULT CBillboardGage::Init(void)
{
	CBillboard::Init();

	// �����̕Ԃ�
	return S_OK;
}

//-------------------------------------
//- �r���{�[�h�I�u�W�F�N�g�̏I������
//-------------------------------------
void CBillboardGage::Uninit(void)
{
	CBillboard::Uninit();
}

//-------------------------------------
//- �r���{�[�h�I�u�W�F�N�g�̍X�V����
//-------------------------------------
void CBillboardGage::Update(void)
{
	CBillboard::Update();

	// ���_����ݒ�
	SetVtx();
}

//-------------------------------------
//- �r���{�[�h�I�u�W�F�N�g�̕`�揈��
//-------------------------------------
void CBillboardGage::Draw(void)
{
	CBillboard::Draw();
}

//-------------------------------------
//-	�r���{�[�h�I�u�W�F�N�g�̐�������
//-------------------------------------
CBillboardGage* CBillboardGage::Create(void)
{
	// �|�C���^��錾
	CBillboardGage* pBillboardGage = NULL;

	// ����
	pBillboardGage = DBG_NEW CBillboardGage;

	// �����̐����̗L���𔻒�
	if (pBillboardGage != NULL)
	{
		// ����������
		if (FAILED(pBillboardGage->Init()))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pBillboardGage == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �|�C���^��Ԃ�
	return pBillboardGage;
}

//-------------------------------------
//- �r���{�[�h�I�u�W�F�N�g�̒��_���ݒ�
//-------------------------------------
void CBillboardGage::SetVtx(void)
{
	if (GetVtxBuff() != nullptr)
	{
		// ���擾
		D3DXVECTOR3 size = GetSize();
		D3DXCOLOR color = GetColor();

		// 3D���_���̃|�C���^��錾
		VERTEX_3D* pVtx = nullptr;

		// ���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
		GetVtxBuff()->Lock(
			0,
			0,
			(void**)&pVtx,
			0);
		
		//���_���W��ݒ�
		pVtx[0].pos = D3DXVECTOR3(-size.x, size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3( size.x * (-1.0f + (m_info.fRateData * 2)), size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-size.x, -size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3( size.x * (-1.0f + (m_info.fRateData * 2)), -size.y, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�o�b�t�@���A�����b�N����
		GetVtxBuff()->Unlock();
	}
}