
//-===============================================
//-
//-	�����̏���[explosion.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "explosion.h"

#include "renderer.h"
#include "manager.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CExplosion::CExplosion()
{
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CExplosion::~CExplosion()
{

}

//-------------------------------------
//- �����̃e�N�X�`���̓ǂݍ���
//-------------------------------------
HRESULT CExplosion::Load(void)
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
		"data\\TEXTURE\\explosion000.png",
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
//- �����̓ǂݍ��񂾃e�N�X�`���̔j��
//-------------------------------------
void CExplosion::Unload(void)
{

}

//-------------------------------------
//- �����̏���������
//-------------------------------------
HRESULT CExplosion::Init(void)
{
	// �A�j���[�V�����I�u�W�F�N�g�̏���������
	CObjectAnima::Init();

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �����̏I������
//-------------------------------------
void CExplosion::Uninit(void)
{
	// �A�j���[�V�����I�u�W�F�N�g�̏I������
	CObjectAnima::Uninit();
}

//-------------------------------------
//- �����̍X�V����
//-------------------------------------
void CExplosion::Update(void)
{
	// �A�j���[�V�����I�u�W�F�N�g�̍X�V����
	CObjectAnima::Update();

	// ��������
	if (Sub() == true)
	{
		return;
	}
}

//-------------------------------------
//- �����̕`�揈��
//-------------------------------------
void CExplosion::Draw(void)
{
	// �A�j���[�V�����I�u�W�F�N�g�̕`�揈��
	CObjectAnima::Draw();
}

//-------------------------------------
//- �����̐�������
//-------------------------------------
CExplosion *CExplosion::Create(void)
{
	// �����̐���
	CExplosion *pCExplosion = DBG_NEW CExplosion;

	// �����̐����̗L���𔻒�
	if (pCExplosion != NULL)
	{
		// ����������
		if (FAILED(pCExplosion->Init()))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCExplosion == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// ��ނ̐ݒ�
	pCExplosion->SetType(TYPE_EXPLOSION);

	//// �����̃e�N�X�`����ݒ�
	//pCExplosion->BindTexture(m_pTexture);

	// �����̃|�C���^��Ԃ�
	return pCExplosion;
}

//-------------------------------------
//- �����̌�������
//-------------------------------------
bool CExplosion::Sub(void)
{
	// �ϐ��錾�i�擾�����j
	int nLife = m_nDataLife.Get();

	// �̗͂����炷
	nLife--;

	// �̗͂̔���
	if (nLife <= 0)
	{
		// �I������
		Uninit();

		// ������Ԃ�
		return true;
	}

	// ���̍X�V
	m_nDataLife.Set(nLife);	// �̗�

	// ���s��Ԃ�
	return false;
}

//-------------------------------------
//- �����̎����ݒ菈���i�A�j���[�V�����ˑ��j
//-------------------------------------
void CExplosion::SetAnimaLife(void)
{
	// �ϐ��錾�i���擾�j
	int nLife = m_nDataLife.Get();					// �̗�
	int nLine = m_nDataLine.Get();					// �A�j���[�V�����̍s��
	int nColumn = m_nDataColumn.Get();				// �A�j���[�V�����̗�
	int nChangeFrame = m_nDataChangeFrame.Get();	// �A�j���[�V�����̐؂�ւ��t���[����

	// �����̐ݒ�
	nLife = nChangeFrame * (nLine * nColumn);

	// ���̍X�V
	m_nDataLife.Set(nLife);	// �̗�

}
