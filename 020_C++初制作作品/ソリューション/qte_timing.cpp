
//-===============================================
//-
//-	�N�C�b�N�^�C���C�x���g�i�^�C�~���O�j����[qte_timing.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "qte_timing.h"

#include "renderer.h"
#include "manager.h"

#include "Input.h"
#include "xinput.h"

#include "obj_2d_none.h"
#include "obj_2d_gage.h"

#include "main.h"

#include "particle.h"

#include "sys_phase_search.h"

//-======================================
//-	�}�N����`
//-======================================

#define GAGE_RANGE_MAX	(50)	// �Q�[�W�̒����̍ő�

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	�N�C�b�N�^�C���C�x���g�i�^�C�~���O�j�̃R���X�g���N�^
//-------------------------------------
CQteTiming::CQteTiming()
{
	// �l�̃N���A
	m_pObj2dNone = NULL;
	m_pObj2dGageTarget = NULL;
	m_pObj2dGagePlayer = NULL;
}

//-------------------------------------
//-	�N�C�b�N�^�C���C�x���g�i�^�C�~���O�j�̃f�X�g���N�^
//-------------------------------------
CQteTiming::~CQteTiming()
{

}

//-------------------------------------
//- �N�C�b�N�^�C���C�x���g�i�^�C�~���O�j�̏���������
//-------------------------------------
HRESULT CQteTiming::Init(void)
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
	if (m_pObj2dGageTarget == NULL)
	{
		if (FAILED(m_pObj2dGageTarget = CObj2dGage::Create(CObj2dGage::TEX_NULL)))
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
	if (m_pObj2dGagePlayer == NULL)
	{
		if (FAILED(m_pObj2dGagePlayer = CObj2dGage::Create(CObj2dGage::TEX_NULL)))
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
	
	float fRotData = (float)((rand() % 3000) - 1000) * 0.1f;	// ����

	// �ݒ菈��
	m_pObj2dNone->Set(pos, size);

	// �ړI�Q�[�W�̐ݒ�
	m_pObj2dGageTarget->Set(
		D3DXVECTOR3(pos.x + fRotData, pos.y, pos.z),
		size,
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
		CObj2dGage::TYPE_CENTER);

	// �v���C���[�Q�[�W�̐ݒ�
	m_pObj2dGagePlayer->Set(
		D3DXVECTOR3(pos.x - size.x,pos.y,pos.z),
		 size,
		D3DXCOLOR(1.0f, 0.95f, 0.0f, 1.0f),
		CObj2dGage::TYPE_CENTER);

	// �Q�[�W�̍X�V����
	UpdateGage();

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �N�C�b�N�^�C���C�x���g�i�^�C�~���O�j�̏I������
//-------------------------------------
void CQteTiming::Uninit(void)
{
	// �ʏ�2D�I�u�W�F�N�g�̗L���𔻒�
	if (m_pObj2dNone != NULL)
	{
		// �ʏ�2D�I�u�W�F�N�g�̃|�C���^����������
		m_pObj2dNone->Uninit();
		m_pObj2dNone = NULL;
	}

	// �Q�[�W�̗L���𔻒�
	if (m_pObj2dGageTarget != NULL)
	{
		// �Q�[�W�̃|�C���^����������
		m_pObj2dGageTarget->Uninit();
		m_pObj2dGageTarget = NULL;
	}

	// �Q�[�W�̗L���𔻒�
	if (m_pObj2dGagePlayer != NULL)
	{
		// �Q�[�W�̃|�C���^����������
		m_pObj2dGagePlayer->Uninit();
		m_pObj2dGagePlayer = NULL;
	}
}

//-------------------------------------
//- �N�C�b�N�^�C���C�x���g�i�^�C�~���O�j�̍X�V����
//-------------------------------------
void CQteTiming::Update(void)
{
	// �L�[�{�[�h�̏��擾����
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

	 // �����𔲂���
		return;
	}
	
	// X���͂̃|�C���^��錾
	CXInput *pXInput = CManager::GetXInput();

	// X���͂̏��擾�̐����𔻒�
	if (pXInput == NULL)
	{
		// �����𔲂���
		return;
	}

	// �Q�[�W�̍X�V����
	UpdateGage();

	// �ϐ��錾�i���擾�j
	bool bMove = m_bDataGageMoveDirect.Get();							// �ړ�����

	if (bMove == true)
	{
		// ���Z����
		AddGage();
	}
	else
	{
		// �I������
		CSysPhaseSearch::ReleaseQte();

		return;
	}

	// ���͂̔���
	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true ||
		pXInput->GetTrigger(XINPUT_GAMEPAD_A, CXInput::TYPE_INPUT_BUTTON))
	{// SPACE�L�[

		// ���菈��
		Decision();

		return;
	}

}

//-------------------------------------
//- �N�C�b�N�^�C���C�x���g�i�^�C�~���O�j�̕`�揈��
//-------------------------------------
void CQteTiming::Draw(void)
{

}

//-------------------------------------
//- �N�C�b�N�^�C���C�x���g�i�^�C�~���O�j�̐�������
//-------------------------------------
CQteTiming *CQteTiming::Create(void)
{
	// �N�C�b�N�^�C���C�x���g�i�^�C�~���O�j�̐���
	CQteTiming *pLife = DBG_NEW CQteTiming;

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

	// �N�C�b�N�^�C���C�x���g�i�^�C�~���O�j�̃|�C���^��Ԃ�
	return pLife;
}

//-------------------------------------
//- �N�C�b�N�^�C���C�x���g�i�^�C�~���O�j�̏����ݒ菈��
//-------------------------------------
void CQteTiming::InitSet(void)
{
	m_dataPos.Set(D3DXVECTOR3(
		SCREEN_WIDTH * 0.5f,
		SCREEN_HEIGHT * 0.85f,
		0.0f));

	m_dataSize.Set(D3DXVECTOR3(
		250.0f,
		50.0f,
		0.0f));

	m_nDataGageTarget.Set(10);
	m_nDataGagePlayer.Set(2);

	m_bDataGageMoveDirect.Set(true);
}

//-------------------------------------
//- �N�C�b�N�^�C���C�x���g�i�^�C�~���O�j�̃Q�[�W�\��
//-------------------------------------
void CQteTiming::UpdateGage(void)
{
	// �ϐ��錾�i���X�V�j
	D3DXVECTOR3 size = m_dataSize.Get();
	int nGageTarget = m_nDataGageTarget.Get();
	int nGagePlayer = m_nDataGagePlayer.Get();
	D3DXVECTOR3 gageTarget = m_pObj2dGageTarget->m_dataGage.Get();	// �ړI�̃Q�[�W
	D3DXVECTOR3 gagePlayer = m_pObj2dGagePlayer->m_dataGage.Get();	// �v���C���[�̃Q�[�W

	// �Q�[�W�̏���ʂ��v�Z
	gageTarget.x = ((1.0f / GAGE_RANGE_MAX) * (GAGE_RANGE_MAX - nGageTarget)) * size.x;
	gagePlayer.x = ((1.0f / GAGE_RANGE_MAX) * (GAGE_RANGE_MAX - nGagePlayer)) * size.x;

	// ���X�V
	m_pObj2dGageTarget->m_dataGage.Set(gageTarget);	// �ړI�̃Q�[�W
	m_pObj2dGagePlayer->m_dataGage.Set(gagePlayer);	// �v���C���[�̃Q�[�W
}

//-------------------------------------
//- �N�C�b�N�^�C���C�x���g�i�^�C�~���O�j�̉��Z
//-------------------------------------
void CQteTiming::AddGage(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 posGagePlayer = m_pObj2dGagePlayer->m_dataPos.Get();	// �v���C���[�Q�[�W�̈ʒu
	bool bMove = m_bDataGageMoveDirect.Get();							// �ړ�����
	D3DXVECTOR3 pos = m_dataPos.Get();									// �ʒu
	D3DXVECTOR3 size = m_dataSize.Get();								// �T�C�Y

	// �v���C���[�Q�[�W�̈ʒu�����Z
	posGagePlayer.x += 5.0f;

	if (posGagePlayer.x == pos.x + size.x)
	{
		// �ړ����������Z��
		bMove = false;
	}

	// ���X�V
	m_pObj2dGagePlayer->m_dataPos.Set(posGagePlayer);	// �v���C���[�Q�[�W�̈ʒu
	m_bDataGageMoveDirect.Set(bMove);					// �ړ�����
}

//-------------------------------------
//- �N�C�b�N�^�C���C�x���g�i�^�C�~���O�j�̌��Z
//-------------------------------------
void CQteTiming::SubGage(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 posGagePlayer = m_pObj2dGagePlayer->m_dataPos.Get();	// �v���C���[�Q�[�W�̈ʒu
	bool bMove = m_bDataGageMoveDirect.Get();							// �ړ�����
	D3DXVECTOR3 pos = m_dataPos.Get();									// �ʒu
	D3DXVECTOR3 size = m_dataSize.Get();								// �T�C�Y

	// �v���C���[�Q�[�W�̈ʒu�����Z
	posGagePlayer.x -= 5.0f;

	if (posGagePlayer.x == pos.x - size.x)
	{
		// �ړ����������Z��
		bMove = true;
	}

	// ���X�V
	m_pObj2dGagePlayer->m_dataPos.Set(posGagePlayer);	// �v���C���[�Q�[�W�̈ʒu
	m_bDataGageMoveDirect.Set(bMove);					// �ړ�����

}

//-------------------------------------
//- �N�C�b�N�^�C���C�x���g�i�^�C�~���O�j�̔��菈��
//-------------------------------------
void CQteTiming::Decision(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 posGagePlayer = m_pObj2dGagePlayer->m_dataPos.Get();	// �v���C���[�Q�[�W�̈ʒu
	D3DXVECTOR3 posGageTarget = m_pObj2dGageTarget->m_dataPos.Get();	// �ړI�Q�[�W�̈ʒu
	D3DXVECTOR3 gageTarget = m_pObj2dGageTarget->m_dataGage.Get();		// �ړI�Q�[�W
	D3DXVECTOR3 size = m_dataSize.Get();

	if (posGagePlayer.x <= posGageTarget.x + size.x - gageTarget.x &&
		posGagePlayer.x >= posGageTarget.x - size.x + gageTarget.x)
	{
		// �I������
		CSysPhaseSearch::ReleaseQte();
		
		return;
	}
}