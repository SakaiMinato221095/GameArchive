
//-===============================================
//-
//-	�J�n������UI�̏���[ui_start_text.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "ui_start_text.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//= �R���X�g��`
//=======================================

// �J�n������UI�e�N�X�`���̃R���X�g��`
const char *pTextureUiStartText[] =
{
	"data\\TEXTURE\\state_text_000.png",		// �X�^�[�g�e�L�X�g000�̃e�N�X�`��
	"data\\TEXTURE\\state_text_001.png",		// �X�^�[�g�e�L�X�g001�̃e�N�X�`��
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

int CUiStartText::m_nTextureNldx[TEX_MAX] = {};	// �e�N�X�`��

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CUiStartText::CUiStartText(int nPriority) : CObject2d(nPriority)
{

}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CUiStartText::~CUiStartText()
{

}

//-------------------------------------
//- �J�n������UI�̃e�N�X�`���̓ǂݍ���
//-------------------------------------
HRESULT CUiStartText::Load(void)
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
	for (int nCount = 0; nCount < TEX_MAX; nCount++)
	{
		// �e�N�X�`���ԍ��̎擾�i�e�N�X�`���̊����j
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureUiStartText[nCount]);

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
//- �J�n������UI�̓ǂݍ��񂾃e�N�X�`���̔j��
//-------------------------------------
void CUiStartText::Unload(void)
{

}

//-------------------------------------
//- �J�n������UI�̏���������
//-------------------------------------
HRESULT CUiStartText::Init(TEX tex)
{
	// �e�N�X�`������
	BindTexture(m_nTextureNldx[tex]);

	// 2D�I�u�W�F�N�g�̏�����
	CObject2d::Init();

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �J�n������UI�̏I������
//-------------------------------------
void CUiStartText::Uninit(void)
{
	// 2D�I�u�W�F�N�g�̏I��
	CObject2d::Uninit();
}

//-------------------------------------
//- �J�n������UI�̍X�V����
//-------------------------------------
void CUiStartText::Update(void)
{
	// �ϐ��錾�i���擾�j
	bool bMoveStop = m_bDataMoveStop.Get();				// �ړ���~�̗L��
	D3DXVECTOR3 sizeMove = m_dataMoveSpeed.Get();		// �ړ��ʂ̑��x

	// �ړ���~�̗L���𔻒�
	if (bMoveStop == false)
	{
		if (sizeMove.x >= 0.0f)
		{
			// ���Z����
			AddSizeMove();
		}
		else
		{
			// ���Z����
			SubSizeMove();
		}
	}

	// ��񂵕`��̃I��
	m_bDataAfterDraw.Set(true);

	// ���_���̐ݒ菈��
	CObject2d::Update();
}

//-------------------------------------
//- �J�n������UI�̕`�揈��
//-------------------------------------
void CUiStartText::Draw(void)
{
	// 2D�I�u�W�F�N�g�̕`�揈��
	CObject2d::Draw();
}

//-------------------------------------
//- �J�n������UI�̐�������
//-------------------------------------
CUiStartText *CUiStartText::Create(TEX tex)
{
	// �J�n������UI�̃|�C���^��錾
	CUiStartText *pCUiStartText = DBG_NEW CUiStartText(7);

	// �����̐����̗L���𔻒�
	if (pCUiStartText != NULL)
	{
		// ���������� if(�J�n������UI�̏����������̗L���𔻒�)
		if (FAILED(pCUiStartText->Init(tex)))
		{// ���s��

		 // �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCUiStartText == NULL)
	{// ���s��

	 // �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �J�n������UI�̃|�C���^��Ԃ�
	return pCUiStartText;
}

//-------------------------------------
//- �J�n������UI�̐ݒ菈��
//-------------------------------------
void CUiStartText::Set(D3DXVECTOR3 pos, D3DXVECTOR3 posTarget, D3DXVECTOR3 size, D3DXVECTOR3 move)
{
	// �����
	m_dataPos.Set(pos);
	m_dataPosTarget.Set(posTarget);
	m_dataSize.Set(size);
	m_dataMoveSpeed.Set(move);
}

//-------------------------------------
//- �������UI�̉��Z����
//-------------------------------------
void CUiStartText::AddSizeMove(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();					// �ʒu
	D3DXVECTOR3 posTarget = m_dataPosTarget.Get();		// �ړI�̈ʒu
	D3DXVECTOR3 move = m_dataMoveSpeed.Get();			// �ړ��ʂ̑��x
	bool bMoveStop = m_bDataMoveStop.Get();				// �ړ���~�̗L��

	// �ړ��ʂ̒~�ϒl�����Z
	pos += move;

	if (pos.x >= posTarget.x &&
		pos.y >= posTarget.y &&
		pos.z >= posTarget.z)
	{
		// �ړ����Ȃ���
		bMoveStop = true;
	}

	// ���X�V
	m_dataPos.Set(pos);					// �ʒu
	m_dataPosTarget.Set(posTarget);		// �ړI�̈ʒu
	m_dataMoveSpeed.Set(move);			// �ړ��ʂ̑��x
	m_bDataMoveStop.Set(bMoveStop);		// �ړ���~�̗L��
}

//-------------------------------------
//- �������UI�̌��Z����
//-------------------------------------
void CUiStartText::SubSizeMove(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();					// �ʒu
	D3DXVECTOR3 posTarget = m_dataPosTarget.Get();		// �ړI�̈ʒu
	D3DXVECTOR3 move = m_dataMoveSpeed.Get();			// �ړ��ʂ̑��x
	bool bMoveStop = m_bDataMoveStop.Get();				// �ړ���~�̗L��

	// �ړ��ʂ̒~�ϒl�����Z
	pos += move;

	if (pos.x <= posTarget.x &&
		pos.y <= posTarget.y &&
		pos.z <= posTarget.z)
	{
		// �ړ����Ȃ���
		bMoveStop = true;
	}

	// ���X�V
	m_dataPos.Set(pos);					// �ʒu
	m_dataPosTarget.Set(posTarget);		// �ړI�̈ʒu
	m_dataMoveSpeed.Set(move);			// �ړ��ʂ̑��x
	m_bDataMoveStop.Set(bMoveStop);		// �ړ���~�̗L��
}