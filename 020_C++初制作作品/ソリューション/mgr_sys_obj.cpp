
//-===============================================
//-
//-	�V�X�e���I�u�W�F�N�g�Ǘ�����[mgr_sys_obj.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "mgr_sys_obj.h"

#include "main.h"

#include "timer.h"

#include "score.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

CTimer *CMgrSysObj::m_pTimer = NULL;
CScore *CMgrSysObj::m_pScore = NULL;

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CMgrSysObj::CMgrSysObj()
{
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CMgrSysObj::~CMgrSysObj()
{

}

//-------------------------------------
//- �V�X�e���I�u�W�F�N�g�Ǘ��̏���������
//-------------------------------------
HRESULT CMgrSysObj::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// ���Ԃ̐�������
	{
		// ���Ԃ̐���
		m_pTimer = CTimer::Create();

		// ���Ԃ̐��������̗L���𔻒�
		if (m_pTimer == NULL)
		{// ���s��

			// ���s���b�Z�[�W
			MessageBox(hWnd, "���Ԃ̐���", "�����������s�I", MB_ICONWARNING);

			// �����������𔲂���
			return E_FAIL;
		}

		// ���Ԃ̐ݒ菈��
		{
			m_pTimer->SetPos(
				D3DXVECTOR3(SCREEN_WIDTH * 0.05f, SCREEN_HEIGHT * 0.10f, 0.0f),
				D3DXVECTOR3(60.0f, 0.0f, 0.0f),
				D3DXVECTOR3(60.0f, 0.0f, 0.0f));

			m_pTimer->SetSize(
				D3DXVECTOR3(40.0f, 50.0f, 0.0f));
		}
	}

	// �X�R�A�̐�������
	{
		// �X�R�A�̐���
		m_pScore = CScore::Create();

		// �X�R�A�̐��������̗L���𔻒�
		if (m_pScore == NULL)
		{// ���s��

		 // ���s���b�Z�[�W
			MessageBox(hWnd, "�X�R�A�̐���", "�����������s�I", MB_ICONWARNING);

			// �����������𔲂���
			return E_FAIL;
		}

		// �X�R�A�̐ݒ菈��
		{
			m_pScore->SetPosition(
				D3DXVECTOR3(SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.05f, 0.0f),
				D3DXVECTOR3(40.0f, 0.0f, 0.0f));

			m_pScore->SetSize(
				D3DXVECTOR3(25.0f, 25.0f, 0.0f));
		}
	}



	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �V�X�e���I�u�W�F�N�g�Ǘ��̏I������
//-------------------------------------
void CMgrSysObj::Uninit(void)
{
	// ���Ԃ̔j��
	if (m_pTimer != NULL)
	{
		// ���Ԃ̏I������
		m_pTimer->Uninit();

		// ���Ԃ̊J������
		delete m_pTimer;
		m_pTimer = NULL;
	}

	// �X�R�A�̔j��
	if (m_pScore != NULL)
	{
		// �X�R�A�̏I������
		m_pScore->Uninit();

		// �X�R�A�̊J������
		delete m_pScore;
		m_pScore = NULL;
	}
}

//-------------------------------------
//- �V�X�e���I�u�W�F�N�g�Ǘ��̍X�V����
//-------------------------------------
void CMgrSysObj::Update(void)
{
	// ���Ԃ̗L���𔻒�
	if (m_pTimer != NULL)
	{
		// ���Ԃ̍X�V����
		m_pTimer->Update();
	}

	// �X�R�A�̗L���𔻒�
	if (m_pScore != NULL)
	{
		// �X�R�A�̍X�V����
		m_pScore->Update();
	}
}

//-------------------------------------
//- �V�X�e���I�u�W�F�N�g�Ǘ��̕`�揈��
//-------------------------------------
void CMgrSysObj::Draw(void)
{
	// ���Ԃ̗L���𔻒�
	if (m_pTimer != NULL)
	{
		// ���Ԃ̕`�揈��
		m_pTimer->Draw();
	}

	// �X�R�A�̗L���𔻒�
	if (m_pScore != NULL)
	{
		// �X�R�A�̕`�揈��
		m_pScore->Draw();
	}
}

//-------------------------------------
//- �V�X�e���I�u�W�F�N�g�Ǘ��̐����ݒ菈��
//-------------------------------------
void CMgrSysObj::SetNumber(void)
{
	// ���Ԃ̐ݒ�
	m_pTimer->CreateNumber();		// �����̐���
	m_pTimer->SetNumber();			// �����ݒ菈��

	// �X�R�A�̐ݒ�
	m_pScore->CreateNumber();		// �����̐���
	m_pScore->SetNumber();			// �����ݒ菈��
}

//-------------------------------------
//- �V�X�e���I�u�W�F�N�g�Ǘ��̐����|�C���^����������
//-------------------------------------
void CMgrSysObj::NullAllNumber(void)
{
	// ���Ԃ̐ݒ�
	m_pTimer->NullAllNumber();		// �����̃|�C���^����������
	m_pScore->NullAllNumber();		// �����̃|�C���^����������
}

//-------------------------------------
//-	���Ԃ̏����擾
//-------------------------------------
CTimer *CMgrSysObj::GetTimer(void)
{
	// ���Ԃ̃|�C���^��Ԃ�
	return m_pTimer;
}

//-------------------------------------
//-	�X�R�A�̏����擾
//-------------------------------------
CScore *CMgrSysObj::GetScore(void)
{
	// �X�R�A�̃|�C���^��Ԃ�
	return m_pScore;
}