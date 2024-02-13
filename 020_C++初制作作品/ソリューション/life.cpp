
//-===============================================
//-
//-	�̗͏���[life.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "life.h"

#include "renderer.h"
#include "manager.h"

#include "obj_2d_none.h"
#include "obj_2d_gage.h"

#include "main.h"

#include "game.h"
#include "state_game.h"

//-======================================
//-	�}�N����`
//-======================================

#define LIFE_MAX	(50)	// �̗͂̍ő吔

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	�̗͂̃R���X�g���N�^
//-------------------------------------
CLife::CLife()
{
	// �l�̃N���A
	m_pObj2dNone = NULL;
	m_pObj2dGage = NULL;
}

//-------------------------------------
//-	�̗͂̃f�X�g���N�^
//-------------------------------------
CLife::~CLife()
{
	
}

//-------------------------------------
//- �̗͂̏���������
//-------------------------------------
HRESULT CLife::Init(void)
{
	// �����ݒ�
	InitSet();

	// ���擾
	D3DXVECTOR3 pos = m_dataPos.Get();		// �ʒu
	D3DXVECTOR3 size = m_dataSize.Get();	// �T�C�Y

	// �ʏ�2D�I�u�W�F�N�g�̐�������
	if (m_pObj2dNone == NULL)
	{
		if (FAILED(m_pObj2dNone = CObj2dNone::Create(CObj2dNone::TEX_NULL)))
		{
			// ���s��Ԃ�
			return E_FAIL;
		}
	}
	else
	{
		// ���s��Ԃ�
		return E_FAIL;
	}

	// �Q�[�W�̐�������
	if (m_pObj2dGage == NULL)
	{
		if (FAILED(m_pObj2dGage = CObj2dGage::Create(CObj2dGage::TEX_NULL)))
		{
			// ���s��Ԃ�
			return E_FAIL;
		}
	}
	else
	{
		// ���s��Ԃ�
		return E_FAIL;
	}

	// �ݒ菈��
	m_pObj2dNone->Set(pos,size);
	m_pObj2dGage->Set(pos, size,D3DXCOLOR(1.0f,0.0f,0.0f,1.0f),CObj2dGage::TYPE_LEFT);

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �̗͂̏I������
//-------------------------------------
void CLife::Uninit(void)
{
	// �ʏ�2D�I�u�W�F�N�g�̗L���𔻒�
	if (m_pObj2dNone != NULL)
	{
		// �ʏ�2D�I�u�W�F�N�g�̃|�C���^����������
		m_pObj2dNone->Uninit();
		m_pObj2dNone = NULL;
	}

	// �Q�[�W�̗L���𔻒�
	if (m_pObj2dGage != NULL)
	{
		// �Q�[�W�̃|�C���^����������
		m_pObj2dGage->Uninit();
		m_pObj2dGage = NULL;
	}
}

//-------------------------------------
//- �̗͂̍X�V����
//-------------------------------------
void CLife::Update(void)
{
	// �Q�[���X�e�[�^�X�̏����擾
	CStateGame *pStateGame = CGame::GetStateGame();

	// �Q�[���X�e�[�^�X�擾�̗L���𔻒�
	if (pStateGame == NULL)
	{
		// �����𔲂���
		return;
	}

	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 gage = m_pObj2dGage->m_dataGage.Get();	// �Q�[�W�̈ʒu
	D3DXVECTOR3 size = m_dataSize.Get();				// �T�C�Y
	int nLife = m_nDataLife.Get();						// �̗͂̒l

	// �Q�[�W�̏���ʂ��v�Z
	gage.x = ((1.0f / LIFE_MAX) * ((LIFE_MAX - nLife) * 2)) * size.x;

	// �̗͒l�̗L���𔻒�
	if (nLife <= 0)
	{
		// �Q�[���̏I����Ԃ̐ݒ�
		pStateGame->SetEndState(CStateGame::END_STATE_DIED);
	}

	// ���X�V
	m_pObj2dGage->m_dataGage.Set(gage);	// �Q�[�W�̈ʒu
}

//-------------------------------------
//- �̗͂̕`�揈��
//-------------------------------------
void CLife::Draw(void)
{

}

//-------------------------------------
//- �̗͂̐�������
//-------------------------------------
CLife *CLife::Create(void)
{
	// �̗͂̐���
	CLife *pLife = DBG_NEW CLife;

	// �����̐����̗L���𔻒�
	if (pLife != NULL)
	{
		// ����������
		if (FAILED(pLife->Init()))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pLife == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �̗͂̃|�C���^��Ԃ�
	return pLife;
}

//-------------------------------------
//- �̗͂̏����ݒ菈��
//-------------------------------------
void CLife::InitSet(void)
{
	m_nDataLife.Set(LIFE_MAX);

	m_dataPos.Set(D3DXVECTOR3(
		SCREEN_WIDTH * 0.87f, 
		SCREEN_HEIGHT * 0.15f,
		0.0f));

	m_dataSize.Set(D3DXVECTOR3(
		150.0f, 
		25.0f, 
		0.0f));
}