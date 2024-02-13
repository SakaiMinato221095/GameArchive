
//-===============================================
//-
//-	�A�j���[�V�����I�u�W�F�N�g����[object_anima.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "object_anima.h"

#include "renderer.h"
#include "manager.h"

//-======================================
//-	�}�N����`
//-======================================

//-------------------------------------
//-	�A�j���[�V�����I�u�W�F�N�g�̃R���X�g���N�^
//-------------------------------------
CObjectAnima::CObjectAnima()
{

}

//-------------------------------------
//-	�A�j���[�V�����I�u�W�F�N�g�̃f�X�g���N�^
//-------------------------------------
CObjectAnima::~CObjectAnima()
{

}

//-------------------------------------
//- �A�j���[�V�����I�u�W�F�N�g�̏���������
//-------------------------------------
HRESULT CObjectAnima::Init(void)
{
	// 2D�I�u�W�F�N�g�̏I������
	CObject2d::Init();

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �A�j���[�V�����I�u�W�F�N�g�̏I������
//-------------------------------------
void CObjectAnima::Uninit(void)
{
	// 2D�I�u�W�F�N�g�̏I������
	CObject2d::Uninit();
}

//-------------------------------------
//- �A�j���[�V�����I�u�W�F�N�g�̍X�V����
//-------------------------------------
void CObjectAnima::Update(void)
{
	// �A�j���[�V�����̍X�V
	UpdateAnima();

	// �A�j���[�V�����I�u�W�F�N�g�̒��_���ݒ�
	SetVtx();
}

//-------------------------------------
//- �A�j���[�V�����I�u�W�F�N�g�̕`�揈��
//-------------------------------------
void CObjectAnima::Draw(void)
{
	// 2D�I�u�W�F�N�g�̕`�揈��
	CObject2d::Draw();
}

//-------------------------------------
//- �A�j���[�V�����I�u�W�F�N�g�̐�������
//-------------------------------------
CObjectAnima *CObjectAnima::Create(void)
{
	// 2D�I�u�W�F�N�g�̐���
	CObjectAnima *pObjectAnima = new CObjectAnima;

	// �����̐����̗L���𔻒�
	if (pObjectAnima != NULL)
	{
		// ����������
		if (FAILED(pObjectAnima->Init()))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pObjectAnima == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �A�j���[�V�����I�u�W�F�N�g�̒��_���ݒ�
	pObjectAnima->SetVtx();

	// 2D�I�u�W�F�N�g�̃|�C���^��Ԃ�
	return pObjectAnima;
}

//-------------------------------------
//- �A�j���[�V�����I�u�W�F�N�g�̃A�j���[�V��������
//-------------------------------------
void CObjectAnima::UpdateAnima(void)
{
	// �ϐ��錾�i���擾�j
	int nCounter = m_nDataCounter.Get();			// �A�j���[�V�����J�E���^�[
	int nChangeFrame = m_nDataChangeFrame.Get();	// �A�j���[�V�����̐؂�ւ���
	int nPattern = m_nDataPattern.Get();			// �A�j���[�V�����̃p�^�[����
	int nLife = m_nDataLine.Get();					// �̗�

	// �A�j���[�V�����J�E���^�[�����Z
	nCounter++;

	// �A�j���[�V�����؂�ւ��̔���
	if ((nCounter % nChangeFrame) == 0)
	{// �ݒ�t���[����

		// �p�^�[��No.���X�V����
		nPattern = ((nCounter / nChangeFrame) % nLife);
	}

	// ���X�V
	m_nDataCounter.Set(nCounter);			// �A�j���[�V�����J�E���^�[
	m_nDataChangeFrame.Set(nChangeFrame);	// �A�j���[�V�����̐؂�ւ���
	m_nDataPattern.Set(nPattern);			// �A�j���[�V�����̃p�^�[����
	m_nDataLine.Set(nLife);					// �̗�
}

//-------------------------------------
//- �A�j���[�V�����I�u�W�F�N�g�̒��_���ݒ�
//-------------------------------------
void CObjectAnima::SetVtx(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();		// �ʒu���
	D3DXVECTOR3 size = m_dataSize.Get();	// �傫��
	int nPattern = m_nDataPattern.Get();	// �A�j���[�V�����̃p�^�[����

	// ���_�o�b�t�@���|�C���^��錾
	LPDIRECT3DVERTEXBUFFER9 vtxBuff = GetVtxBuff();

	// ���_�o�b�t�@�擾�����̗L���𔻒�
	if (vtxBuff == NULL)
	{// ���s��
		return;
	}

	// 2D���_���̃|�C���^��錾
	VERTEX_2D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	vtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	// ���_���W��ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - size.x, pos.y - size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + size.x, pos.y - size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - size.x, pos.y + size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[��ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`���̍��W��ݒ�
	pVtx[0].tex = D3DXVECTOR2(
		(nPattern * 0.125f),
		0.0f);

	pVtx[1].tex = D3DXVECTOR2(
		((nPattern + 1) * 0.125f),
		0.0f);

	pVtx[2].tex = D3DXVECTOR2(
		(nPattern * 0.125f),
		1.0f);

	pVtx[3].tex = D3DXVECTOR2(
		((nPattern + 1) * 0.125f),
		1.0f);

	// ���_�o�b�t�@���A�����b�N����
	vtxBuff->Unlock();

	// ���X�V
	m_nDataPattern.Set(nPattern);			// �A�j���[�V�����̃p�^�[����
}

//-------------------------------------
//- �A�j���[�V�����I�u�W�F�N�g�̐؂�ւ��t���[�����̎擾
//-------------------------------------
void CObjectAnima::SetAllAnima(int nLine, int nColumn, int nChangeFrame)
{
	// �s������
	m_nDataLine.Set(nLine);

	// �񐔂���
	m_nDataColumn.Set(nColumn);

	// �؂�ւ��t���[���̑��
	m_nDataChangeFrame.Set(nChangeFrame);
}
