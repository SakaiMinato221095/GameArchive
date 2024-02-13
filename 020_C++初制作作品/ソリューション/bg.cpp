
//-===============================================
//-
//-	�w�i����[bg.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "bg.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"
#include "manager_object.h"

#include "title.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//= �R���X�g��`
//=======================================

// �w�i�e�N�X�`���̃R���X�g��`
const char *pTextureBg[] =
{
	"data\\TEXTURE\\Title.png",			// �^�C�g���̃e�N�X�`��
	"data\\TEXTURE\\result_win.png",	// �����̃��U���g�̃e�N�X�`��
	"data\\TEXTURE\\result_end.png",	// �ʏ�̃��U���g�̃e�N�X�`��
	"data\\TEXTURE\\result_loose.png",	// �s�k�̃��U���g�̃e�N�X�`��
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

int CBg::m_nTextureNldx[TEX_MAX] = {};	// �e�N�X�`��

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CBg::CBg(int nPriority) : CObject2d(nPriority)
{

}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CBg::~CBg()
{

}

//-------------------------------------
//- �w�i�̃e�N�X�`���̓ǂݍ���
//-------------------------------------
HRESULT CBg::Load(void)
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
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureBg[nCount]);

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
void CBg::Unload(void)
{

}

//-------------------------------------
//- �w�i�̏���������
//-------------------------------------
HRESULT CBg::Init(TEX tex)
{
	// �e�N�X�`������
	BindTexture(m_nTextureNldx[tex]);

	// 2D�I�u�W�F�N�g�̏�����
	CObject2d::Init();
	
	// ���_���̐ݒ菈��
	SetVtx();

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �w�i�̏I������
//-------------------------------------
void CBg::Uninit(void)
{
	// 2D�I�u�W�F�N�g�̏I��
	CObject2d::Uninit();
}

//-------------------------------------
//- �w�i�̍X�V����
//-------------------------------------
void CBg::Update(void)
{
	// �e�N�X�`�����W�̍X�V����
	AddTexPos();

	// �e�N�X�`�����W�̕␳����
	DestTexPos();

	// ���_���̐ݒ菈��
	SetVtx();
}

//-------------------------------------
//- �w�i�̕`�揈��
//-------------------------------------
void CBg::Draw(void)
{
	// 2D�I�u�W�F�N�g�̕`�揈��
	CObject2d::Draw();
}

//-------------------------------------
//- �w�i�̐�������
//-------------------------------------
CBg *CBg::Create(TEX tex)
{
	// �w�i�̃|�C���^��錾
	CBg *pCBg = DBG_NEW CBg;

	// �����̐����̗L���𔻒�
	if (pCBg != NULL)
	{
		// ���������� if(�w�i�̏����������̗L���𔻒�)
		if (FAILED(pCBg->Init(tex)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCBg == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �w�i�̃|�C���^��Ԃ�
	return pCBg;
}

//-------------------------------------
//- �w�i�̐ݒ菈��
//-------------------------------------
void CBg::Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR2 texPos, D3DXVECTOR2 texMove)
{
	// �����
	m_dataPos.Set(pos);
	m_dataSize.Set(size);
	m_dataTexPos.Set(texPos);
	m_dataTexMove.Set(texMove);

	// ���_���̐ݒ菈��
	SetVtx();
}

//-------------------------------------
//- �w�i�̒��_���ݒ�
//-------------------------------------
void CBg::SetVtx(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();		// �ʒu
	D3DXVECTOR3 size = m_dataSize.Get();	// �傫��

	D3DXVECTOR2 texPos = m_dataTexPos.Get();	// �e�N�X�`���ʒu
	D3DXVECTOR2 texMove = m_dataTexMove.Get();	// �e�N�X�`���ړ���

	// ���_�o�b�t�@�̎擾
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
		0.0f + texPos.x,
		0.0f + texPos.y);

	pVtx[1].tex = D3DXVECTOR2(
		1.0f + texPos.x,
		0.0f + texPos.y);

	pVtx[2].tex = D3DXVECTOR2(
		0.0f + texPos.x,
		1.0f + texPos.y);

	pVtx[3].tex = D3DXVECTOR2(
		1.0f + texPos.x,
		1.0f + texPos.y);

	// ���_�o�b�t�@���A�����b�N����
	vtxBuff->Unlock();

	// ���X�V
	m_dataPos.Set(pos);		// �ʒu
	m_dataSize.Set(size);	// �傫��
}

//-------------------------------------
//- ���d�w�i�̃e�N�X�`�����W�̉��Z����
//-------------------------------------
void CBg::AddTexPos(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR2 texPos = m_dataTexPos.Get();	// �e�N�X�`���ʒu
	D3DXVECTOR2 texMove = m_dataTexMove.Get();	// �e�N�X�`���ړ���

	// �e�N�X�`���ʒu�Ɉړ��ʂ����Z
	texPos += texMove;

	// ���X�V
	m_dataTexPos.Set(texPos);		// �e�N�X�`���ʒu
	m_dataTexMove.Set(texMove);		// �e�N�X�`���ړ���
}

//-------------------------------------
//- ���d�w�i�̃e�N�X�`�����W�̕␳
//-------------------------------------
void CBg::DestTexPos(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR2 texPos = m_dataTexPos.Get();	// �e�N�X�`���ʒu

	// ���̃e�N�X�`���ʒu�̔���
	if (texPos.x > 1.0f)
	{
		// 1.0f�𒴂����ꍇ0.0f�ɂ���
		texPos.x = 0.0f;
	}
	else if (texPos.x < 0.0f)
	{
		// 0.0f����������ꍇ1.0f�ɂ���
		texPos.x = 1.0f;
	}

	// �c�̃e�N�X�`���ʒu�̔���
	if (texPos.y > 1.0f)
	{
		// 1.0f�𒴂����ꍇ0.0f�ɂ���
		texPos.y = 0.0f;
	}
	else if (texPos.y < 0.0f)
	{
		// 0.0f����������ꍇ1.0f�ɂ���
		texPos.y = 1.0f;
	}

	// ���X�V
	m_dataTexPos.Set(texPos);		// �e�N�X�`���ʒu
}