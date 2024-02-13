
//-===============================================
//-
//-	3D�Ǐ���[obj_3d_wall.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "obj_3d_wall.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

#include "coll.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�R���X�g��`
//=======================================

// 3D�ǂ̃e�N�X�`���̃R���X�g��`
const char *pTextureWall[] =
{
	NULL,										// �e�N�X�`���Ȃ�
	"data\\TEXTURE\\blockade_wall000.jpg",		// �����ǂ̃e�N�X�`��
	"data\\TEXTURE\\dark_wall000.png",			// �ŕǂ̃e�N�X�`��
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

int CObj3dWall::m_nTextureNldx[TEX_MAX] = {};

//-------------------------------------
//-	3D�ǂ̃R���X�g���N�^
//-------------------------------------
CObj3dWall::CObj3dWall(int nPriority) : CObject3d(nPriority)
{
	m_pColl = nullptr;
}

//-------------------------------------
//-	3D�ǂ̃f�X�g���N�^
//-------------------------------------
CObj3dWall::~CObj3dWall()
{

}

//-------------------------------------
//- �w�i�̃e�N�X�`���̓ǂݍ���
//-------------------------------------
HRESULT CObj3dWall::Load(void)
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
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureWall[nCount]);

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
void CObj3dWall::Unload(void)
{

}
//-------------------------------------
//- 3D�ǂ̏����������i3D�I�u�W�F�N�g�ݒ�j
//-------------------------------------
HRESULT CObj3dWall::Init(TEX tex)
{
	// �e�N�X�`������
	BindTexture(m_nTextureNldx[tex]);

	// 3D�I�u�W�F�N�g�̏�����
	CObject3d::Init();

	if (m_pColl == NULL)
	{
		// �����蔻��ݒ�
		m_pColl = CColl::Create(
			CMgrColl::TAG_WALL_X,
			this,
			GetVtxData().pos,
			GetVtxData().size);
	}
	else
	{
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- 3D�ǂ̏I������
//-------------------------------------
void CObj3dWall::Uninit(void)
{
	if (m_pColl != NULL)
	{
		// �����蔻��̏I������
		m_pColl->Uninit();
		delete m_pColl;
		m_pColl = NULL;
	}

	// 3D�I�u�W�F�N�g�̏I��
	CObject3d::Uninit();
}

//-------------------------------------
//- 3D�ǂ̍X�V����
//-------------------------------------
void CObj3dWall::Update(void)
{
	if (m_pColl != nullptr)
	{
		// �����蔻��̏��X�V����
		m_pColl->UpdateData(
			GetVtxData().pos,
			GetVtxData().size);
	}

	// 3D�I�u�W�F�N�g�̍X�V����
	CObject3d::Update();
}

//-------------------------------------
//- 3D�ǂ̕`�揈��
//-------------------------------------
void CObj3dWall::Draw(void)
{
	// 3D�I�u�W�F�N�g�̕`�揈��
	CObject3d::Draw();
}


//-------------------------------------
//-	3D�I�u�W�F�N�g�̒��_���ݒ菈��
//-------------------------------------
void CObj3dWall::InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR color, D3DXVECTOR2 texPos)
{
	CObject3d::InitSet(pos,size,rot,color,texPos);

	if (rot.y == 0.0f)
	{
		CColl::Data data = m_pColl->GetData();
		data.tag = CMgrColl::TAG_WALL_Z;

		m_pColl->SetData(data);
	}
	else if (rot.y == (D3DX_PI * 0.5f))
	{
		CColl::Data data = m_pColl->GetData();
		data.tag = CMgrColl::TAG_WALL_X;

		m_pColl->SetData(data);
	}
}

//-------------------------------------
//- 3D�ǂ̐�������
//-------------------------------------
CObj3dWall * CObj3dWall::Create(TEX tex)
{
	// �t�B�[���h�̃|�C���^��錾
	CObj3dWall *pCObj3dWall = DBG_NEW CObj3dWall(1);

	// �����̐����̗L���𔻒�
	if (pCObj3dWall != NULL)
	{
		// ����������
		if (FAILED(pCObj3dWall->Init(tex)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCObj3dWall == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �t�B�[���h�̃|�C���^��Ԃ�
	return pCObj3dWall;
}

//-------------------------------------
//-	3D�I�u�W�F�N�g�̒��_���ݒ菈��
//-------------------------------------
void CObj3dWall::SetVtx(void)
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
			pVtx[0].pos = D3DXVECTOR3(-size.x,	size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3( size.x,	size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-size.x, -size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3( size.x, -size.y, 0.0f);
		}
		else if (rot.y == (D3DX_PI * 0.5f))
		{
			//���_���W
			pVtx[0].pos = D3DXVECTOR3(-size.z,  size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3( size.z,  size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-size.z, -size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3( size.z, -size.y, 0.0f);
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