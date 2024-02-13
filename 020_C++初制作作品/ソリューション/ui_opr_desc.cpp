
//-===============================================
//-
//-	����\��UI�̏���[ui_opr_desc.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "ui_opr_desc.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//= �R���X�g��`
//=======================================

// �������UI�e�N�X�`���̃R���X�g��`
const char *pTextureUiOprDesc[] =
{
	"data\\TEXTURE\\key_space.png",		// �X�y�[�X�L�[�̃e�N�X�`��
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

int CUiOprDesc::m_nTextureNldx[TEX_MAX] = {};	// �e�N�X�`��

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CUiOprDesc::CUiOprDesc(int nPriority) : CObject2d(nPriority)
{

}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CUiOprDesc::~CUiOprDesc()
{

}

//-------------------------------------
//- �������UI�̃e�N�X�`���̓ǂݍ���
//-------------------------------------
HRESULT CUiOprDesc::Load(void)
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
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureUiOprDesc[nCount]);

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
//- �������UI�̓ǂݍ��񂾃e�N�X�`���̔j��
//-------------------------------------
void CUiOprDesc::Unload(void)
{

}

//-------------------------------------
//- �������UI�̏���������
//-------------------------------------
HRESULT CUiOprDesc::Init(TEX tex)
{
	// �e�N�X�`������
	BindTexture(m_nTextureNldx[tex]);

	// �T�C�Y�̑���������ݒ�
	m_bDataSizeMove.Set(true);

	// 2D�I�u�W�F�N�g�̏�����
	CObject2d::Init();

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �������UI�̏I������
//-------------------------------------
void CUiOprDesc::Uninit(void)
{
	// 2D�I�u�W�F�N�g�̏I��
	CObject2d::Uninit();
}

//-------------------------------------
//- �������UI�̍X�V����
//-------------------------------------
void CUiOprDesc::Update(void)
{
	// �ϐ��錾�i���擾�j
	bool bSizeMove = m_bDataSizeMove.Get();	// ��������

	if (bSizeMove == true)
	{
		// ���Z����
		AddSizeMove();
	}
	else
	{
		// ���Z����
		SubSizeMove();
	}

	// ��񂵕`��̃I��
	m_bDataAfterDraw.Set(true);

	// ���_���̐ݒ菈��
	SetVtx();
}

//-------------------------------------
//- �������UI�̕`�揈��
//-------------------------------------
void CUiOprDesc::Draw(void)
{
	// 2D�I�u�W�F�N�g�̕`�揈��
	CObject2d::Draw();
}

//-------------------------------------
//- �������UI�̐�������
//-------------------------------------
CUiOprDesc *CUiOprDesc::Create(TEX tex)
{
	// �������UI�̃|�C���^��錾
	CUiOprDesc *pCUiOprDesc = DBG_NEW CUiOprDesc(7);

	// �����̐����̗L���𔻒�
	if (pCUiOprDesc != NULL)
	{
		// ���������� if(�������UI�̏����������̗L���𔻒�)
		if (FAILED(pCUiOprDesc->Init(tex)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCUiOprDesc == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �������UI�̃|�C���^��Ԃ�
	return pCUiOprDesc;
}

//-------------------------------------
//- �������UI�̐ݒ菈��
//-------------------------------------
void CUiOprDesc::Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 sizeMoveMax,D3DXVECTOR3 sizeMoveSpeed)
{
	// �����
	m_dataPos.Set(pos);
	m_dataSize.Set(size);
	m_dataSizeMoveMax.Set(sizeMoveMax);
	m_dataSizeMoveSpeed.Set(sizeMoveSpeed);
}

//-------------------------------------
//- 2D�I�u�W�F�N�g�̒��_���ݒ�
//-------------------------------------
void CUiOprDesc::SetVtx(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();					// �ʒu
	D3DXVECTOR3 size = m_dataSize.Get();				// �傫��
	D3DXVECTOR3 sizeMoveAcu = m_dataSizeMoveAcu.Get();	// �T�C�Y�̈ړ��ʂ̒~�ϒl
	D3DCOLOR color = m_dataColor.Get();					// �F

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
	pVtx[0].pos = D3DXVECTOR3(pos.x - (size.x + sizeMoveAcu.x), pos.y - (size.y + sizeMoveAcu.y), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + (size.x + sizeMoveAcu.x), pos.y - (size.y + sizeMoveAcu.y), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - (size.x + sizeMoveAcu.x), pos.y + (size.y + sizeMoveAcu.y), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + (size.x + sizeMoveAcu.x), pos.y + (size.y + sizeMoveAcu.y), 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[��ݒ�
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	// �e�N�X�`���̍��W��ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	vtxBuff->Unlock();

	// ���X�V
	m_dataPos.Set(pos);			// �ʒu
	m_dataSize.Set(size);		// �傫��
	m_dataColor.Set(color);		// �F
}

//-------------------------------------
//- �������UI�̉��Z����
//-------------------------------------
void CUiOprDesc::AddSizeMove(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 sizeMoveAcu = m_dataSizeMoveAcu.Get();		// �傫���̈ړ��ʂ̒~�ϒl
	D3DXVECTOR3 sizeMoveMax = m_dataSizeMoveMax.Get();		// �傫���̈ړ��ʂ̍ő�l
	D3DXVECTOR3 sizeMoveSpeed = m_dataSizeMoveSpeed.Get();	// �傫���̈ړ��ʂ̑��x
	bool bSizeMove = m_bDataSizeMove.Get();					// ��������

	// �ړ��ʂ̒~�ϒl�����Z
	sizeMoveAcu += sizeMoveSpeed;

	if (sizeMoveAcu.x >= sizeMoveMax.x &&
		sizeMoveAcu.y >= sizeMoveMax.y &&
		sizeMoveAcu.z >= sizeMoveMax.z)
	{
		// ���Z�����ɐݒ�
		bSizeMove = false;
	}

	// ���X�V
	m_dataSizeMoveAcu.Set(sizeMoveAcu);		// �傫���̈ړ��ʂ̒~�ϒl
	m_bDataSizeMove.Set(bSizeMove);			// �傫���̈ړ��ʂ̑�������
}

//-------------------------------------
//- �������UI�̌��Z����
//-------------------------------------
void CUiOprDesc::SubSizeMove(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 sizeMoveAcu = m_dataSizeMoveAcu.Get();		// �傫���̈ړ��ʂ̒~�ϒl
	D3DXVECTOR3 sizeMoveMax = m_dataSizeMoveMax.Get();		// �傫���̈ړ��ʂ̍ő�l
	D3DXVECTOR3 sizeMoveSpeed = m_dataSizeMoveSpeed.Get();	// �傫���̈ړ��ʂ̑��x
	bool bSizeMove = m_bDataSizeMove.Get();					// ��������

	// �ړ��ʂ̒~�ϒl�𑝌�
	sizeMoveAcu -= sizeMoveSpeed;

	if (sizeMoveAcu.x <= -sizeMoveMax.x &&
		sizeMoveAcu.y <= -sizeMoveMax.y &&
		sizeMoveAcu.z <= -sizeMoveMax.z)
	{
		// ���Z�����ɐݒ�
		bSizeMove = true;
	}

	// ���X�V
	m_dataSizeMoveAcu.Set(sizeMoveAcu);		// �傫���̈ړ��ʂ̒~�ϒl
	m_bDataSizeMove.Set(bSizeMove);			// �傫���̈ړ��ʂ̑�������
}