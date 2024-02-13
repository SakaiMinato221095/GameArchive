
//================================================
//=
//=	�Q�[�W����[obj_2d_gage.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "obj_2d_gage.h"

#include "manager.h"
#include "renderer.h"

#include "manager_texture.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//= �R���X�g��`
//=======================================

// �Q�[�W�e�N�X�`���̃R���X�g��`
const char *pTextureObj2dGage[] =
{
	NULL	// �Ȃ�
};

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

int CObj2dGage::m_nTextureNldx[TEX_MAX] = {};

//-------------------------------------
//-	�Q�[�W�̃R���X�g���N�^
//-------------------------------------
CObj2dGage::CObj2dGage(int nPriority) : CObject2d(nPriority)
{

}

//-------------------------------------
//-	�Q�[�W�̃f�X�g���N�^
//-------------------------------------
CObj2dGage::~CObj2dGage()
{

}

//-------------------------------------
//- �Q�[�W�̓ǂݍ��ݏ���
//-------------------------------------
HRESULT CObj2dGage::Load(void)
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
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureObj2dGage[nCount]);

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
//- �w�i�̓ǂݍ��񂾃e�N�X�`���̔j��
//-------------------------------------
void CObj2dGage::Unload(void)
{

}

//-------------------------------------
//- �Q�[�W�̏���������
//-------------------------------------
HRESULT CObj2dGage::Init(TEX tex)
{
	// �g�p�e�N�X�`���̐ݒ�
	BindTexture(m_nTextureNldx[tex]);

	// 2D�I�u�W�F�N�g�̏�����
	CObject2d::Init();

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �Q�[�W�̏I������
//-------------------------------------
void CObj2dGage::Uninit(void)
{
	// 2D�I�u�W�F�N�g�̏I������
	CObject2d::Uninit();
}

//-------------------------------------
//- �Q�[�W�̍X�V����
//-------------------------------------
void CObj2dGage::Update(void)
{
	// ���_���̐ݒ菈��
	SetVtx();
}

//-------------------------------------
//- �Q�[�W�̕`�揈��
//-------------------------------------
void CObj2dGage::Draw(void)
{
	// 2D�I�u�W�F�N�g�̕`�揈��
	CObject2d::Draw();
}

//-------------------------------------
//-	�Q�[�W�̐�������
//-------------------------------------
CObj2dGage *CObj2dGage::Create(TEX tex)
{
	// �Q�[�W�̐���
	CObj2dGage *pNumber = DBG_NEW CObj2dGage(7);

	// �����̐����̗L���𔻒�
	if (pNumber != NULL)
	{
		// ����������
		if (FAILED(pNumber->Init(tex)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pNumber == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �Q�[�W�̃|�C���^��Ԃ�
	return pNumber;
}

//-------------------------------------
//- �Q�[�W�̒��_���ݒ�
//-------------------------------------
void CObj2dGage::SetVtx(void)
{
	// �ϐ��錾�i���̎擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();		// �ʒu���
	D3DXVECTOR3 size = m_dataSize.Get();	// �傫��
	D3DXVECTOR3 gage = m_dataGage.Get();	// �Q�[�W
	D3DXCOLOR color = m_dataColor.Get();	// �F

	// ���_�o�b�t�@���|�C���^��錾
	LPDIRECT3DVERTEXBUFFER9 vtxBuff = GetVtxBuff();

	// ���_�o�b�t�@�擾�����̗L���𔻒�
	if (vtxBuff == NULL)
	{// ���s��

	 // ���_���ݒ�𔲂���
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
	switch (m_type)
	{
	case TYPE_LEFT:
		pVtx[0].pos = D3DXVECTOR3(pos.x - size.x, pos.y - size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pos.x + size.x - gage.x, pos.y - size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pos.x - size.x, pos.y + size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pos.x + size.x - gage.x, pos.y + size.y, 0.0f);
		break;
	case TYPE_RIGHT:
		pVtx[0].pos = D3DXVECTOR3(pos.x - size.x + gage.x, pos.y - size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pos.x + size.x, pos.y - size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pos.x - size.x + gage.x, pos.y + size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, 0.0f);
		break;
	case TYPE_CENTER:
		pVtx[0].pos = D3DXVECTOR3(pos.x - size.x + gage.x, pos.y - size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pos.x + size.x - gage.x, pos.y - size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pos.x - size.x + gage.x, pos.y + size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pos.x + size.x - gage.x, pos.y + size.y, 0.0f);
		break;
	}


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
}

//-------------------------------------
//- �Q�[�W�̐ݒ菈��
//-------------------------------------
void CObj2dGage::Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color,TYPE type)
{
	m_dataPos.Set(pos);
	m_dataSize.Set(size);
	m_dataColor.Set(color);
	m_type = type;
}
