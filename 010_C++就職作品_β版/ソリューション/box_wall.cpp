
//-===============================================
//-
//-	�����蔻��Ǐ���[box_wall.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "box_wall.h"

#include "renderer.h"
#include "manager.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�R���X�g��`
//=======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	3D�n�ʂ̃R���X�g���N�^
//-------------------------------------
CBoxWall::CBoxWall(int nPriority) : CObject3d(nPriority)
{

}

//-------------------------------------
//-	3D�n�ʂ̃f�X�g���N�^
//-------------------------------------
CBoxWall::~CBoxWall()
{

}


//-------------------------------------
//- 3D�n�ʂ̏����������i3D�I�u�W�F�N�g�ݒ�j
//-------------------------------------
HRESULT CBoxWall::Init(void)
{
	// 3D�I�u�W�F�N�g�̏�����
	CObject3d::Init();

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- 3D�n�ʂ̏I������
//-------------------------------------
void CBoxWall::Uninit(void)
{
	// 3D�I�u�W�F�N�g�̏I��
	CObject3d::Uninit();
}

//-------------------------------------
//- 3D�n�ʂ̍X�V����
//-------------------------------------
void CBoxWall::Update(void)
{
	// 3D�I�u�W�F�N�g�̍X�V����
	CObject3d::Update();
}

//-------------------------------------
//- 3D�n�ʂ̕`�揈��
//-------------------------------------
void CBoxWall::Draw(void)
{
	// 3D�I�u�W�F�N�g�̕`�揈��
	CObject3d::Draw();
}

//-------------------------------------
//- 3D�n�ʂ̐�������
//-------------------------------------
CBoxWall* CBoxWall::Create(void)
{
	// �t�B�[���h�̃|�C���^��錾
	CBoxWall* pCBoxWall = DBG_NEW CBoxWall(2);

	// �����̐����̗L���𔻒�
	if (pCBoxWall != NULL)
	{
		// ����������
		if (FAILED(pCBoxWall->Init()))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCBoxWall == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �t�B�[���h�̃|�C���^��Ԃ�
	return pCBoxWall;
}

//-------------------------------------
//-	3D�I�u�W�F�N�g�̒��_���ݒ菈��
//-------------------------------------
void CBoxWall::SetVtx(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 size = GetVtxData().size;		// �T�C�Y
	D3DXCOLOR color = GetVtxData().color;		// �F
	D3DXVECTOR2 texPos = GetVtxData().texPos;	// �e�N�X�`���ʒu

	D3DXVECTOR3 rot = GetVtxData().rot;			// �e�N�X�`���ʒu

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

		if (rot.y == 0.0f)
		{
			//���_���W
			pVtx[0].pos = D3DXVECTOR3(-size.x, size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(size.x, size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-size.x, -size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(size.x, -size.y, 0.0f);
		}
		else if (rot.y == (D3DX_PI * 0.5f))
		{
			//���_���W
			pVtx[0].pos = D3DXVECTOR3(-size.z, size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(size.z, size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-size.z, -size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(size.z, -size.y, 0.0f);
		}

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

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