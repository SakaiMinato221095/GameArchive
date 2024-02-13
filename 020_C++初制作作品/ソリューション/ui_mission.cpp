
//-===============================================
//-
//-	�ڕWUI�̏���[ui_mission.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "ui_mission.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//= �R���X�g��`
//=======================================

// �ڕWUI�e�N�X�`���̃R���X�g��`
const char *pTextureUiMission[] =
{
	"data\\TEXTURE\\mission_search.png",			// �T���̃e�N�X�`��
	"data\\TEXTURE\\mission_shop.png",				// �w���̃e�N�X�`��
	"data\\TEXTURE\\mission_battle_normal.png",		// �퓬�i�G���j�̃e�N�X�`��
	"data\\TEXTURE\\mission_battle_boss.png",		// �퓬�i�{�X�j�̃e�N�X�`��
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

int CUiMission::m_nTextureNldx[TEX_MAX] = {};	// �e�N�X�`��

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CUiMission::CUiMission(int nPriority) : CObject2d(nPriority)
{

}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CUiMission::~CUiMission()
{

}

//-------------------------------------
//- �ڕWUI�̃e�N�X�`���̓ǂݍ���
//-------------------------------------
HRESULT CUiMission::Load(void)
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
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureUiMission[nCount]);

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
//- �ڕWUI�̓ǂݍ��񂾃e�N�X�`���̔j��
//-------------------------------------
void CUiMission::Unload(void)
{

}

//-------------------------------------
//- �ڕWUI�̏���������
//-------------------------------------
HRESULT CUiMission::Init(TEX tex)
{
	// �e�N�X�`������
	BindTexture(m_nTextureNldx[tex]);

	// 2D�I�u�W�F�N�g�̏�����
	CObject2d::Init();

	// �����ݒ菈��
	InitSet();

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �ڕWUI�̏I������
//-------------------------------------
void CUiMission::Uninit(void)
{
	// 2D�I�u�W�F�N�g�̏I��
	CObject2d::Uninit();
}

//-------------------------------------
//- �ڕWUI�̍X�V����
//-------------------------------------
void CUiMission::Update(void)
{
	// ��񂵕`��̃I��
	m_bDataAfterDraw.Set(true);

	// ���_���̐ݒ菈��
	CObject2d::Update();
}

//-------------------------------------
//- �ڕWUI�̕`�揈��
//-------------------------------------
void CUiMission::Draw(void)
{
	// 2D�I�u�W�F�N�g�̕`�揈��
	CObject2d::Draw();
}

//-------------------------------------
//- �ڕWUI�̐�������
//-------------------------------------
CUiMission *CUiMission::Create(TEX tex)
{
	// �ڕWUI�̃|�C���^��錾
	CUiMission *pCUiMission = DBG_NEW CUiMission(7);

	// �����̐����̗L���𔻒�
	if (pCUiMission != NULL)
	{
		// ���������� if(�ڕWUI�̏����������̗L���𔻒�)
		if (FAILED(pCUiMission->Init(tex)))
		{// ���s��

		 // �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCUiMission == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �ڕWUI�̃|�C���^��Ԃ�
	return pCUiMission;
}

//-------------------------------------
//- �ڕWUI�̐ݒ菈��
//-------------------------------------
void CUiMission::Set(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �����
	m_dataPos.Set(pos);
	m_dataSize.Set(size);
}

//-------------------------------------
//- �ڕWUI�̃e�N�X�`���ԍ���Ԃ�
//-------------------------------------
int CUiMission::GetTexNldx(TEX tex)
{
	return m_nTextureNldx[tex];
}

//-------------------------------------
//- �ڕWUI�̏����ݒ菈��
//-------------------------------------
void CUiMission::InitSet(void)
{
	m_dataPos.Set(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.1f, 0.0f));
	m_dataSize.Set(D3DXVECTOR3(200.0f, 50.0f, 0.0f));
}