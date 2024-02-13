
//================================================
//=
//=	���U���g��ʏ���[result.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "result.h"

#include "fade.h"

#include "Input.h"
#include "xinput.h"

#include "bg.h"

#include "manager.h"
#include "state_mode.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

CBg *CResult::m_apBg[BG_RESULT_NUM_MAX] = {};

//-------------------------------------
//-	���U���g�̃R���X�g���N�^
//-------------------------------------
CResult::CResult()
{

}

//-------------------------------------
//-	���U���g�̃f�X�g���N�^
//-------------------------------------
CResult::~CResult()
{

}

//-------------------------------------
//- ���U���g�̏���������
//-------------------------------------
HRESULT CResult::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// ���[�h�X�e�[�^�X�̏��擾
	CStateMode *pStateMode = CManager::GetStateMode();;

	// ���[�h�X�e�[�^�X�̏��擾�̐����𔻒�
	if (pStateMode == NULL)
	{// ���s��

		// �X�V�����𔲂���
		return E_FAIL;
	}

	// ���U���g��Ԃ��擾
	CStateMode::RESULT_STATE resultState = pStateMode->GetResultState();

	// �w�i�̗L���𔻒�
	if (m_apBg[0] == NULL)
	{
		switch (resultState)
		{
		case CStateMode::RESULT_STATE_WIN:

			// �w�i�̐�������
			m_apBg[0] = CBg::Create(CBg::TEX_RESULT_WIN);

			break;

		case CStateMode::RESULT_STATE_END:

			// �w�i�̐�������
			m_apBg[0] = CBg::Create(CBg::TEX_RESULT_END);

			break;

		case CStateMode::RESULT_STATE_LOOSE:

			// �w�i�̐�������
			m_apBg[0] = CBg::Create(CBg::TEX_RESULT_LOOSE);

			break;
		}


		// �w�i�̗L���𔻒�
		if (m_apBg[0] == NULL)
		{
			// ���s��Ԃ�
			return E_FAIL;
		}

		// �w�i�̐ݒ�
		m_apBg[0]->Set();
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- ���U���g�̏I������
//-------------------------------------
void CResult::Uninit(void)
{
	for (int nCount = 0; nCount < BG_RESULT_NUM_MAX; nCount++)
	{
		// �w�i�̗L���𔻒�
		if (m_apBg[nCount] != NULL)
		{
			// �w�i�̃|�C���^����������
			m_apBg[nCount] = NULL;
		}
	}

	// �I�u�W�F�N�g�̑S�J������
	CObject::ReleaseAll();
}

//-------------------------------------
//- ���U���g�̍X�V����
//-------------------------------------
void CResult::Update(void)
{
	// �L�[�{�[�h�̏��擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

		// �X�V�����𔲂���
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

	// �J�ڃ{�^���i���񂽁[�j
	if (pInputKeyboard->GetTrigger(DIK_RETURN) != NULL ||
		pXInput->GetTrigger(XINPUT_GAMEPAD_A, CXInput::TYPE_INPUT_BUTTON))
	{
		// �Q�[�����[�h
		CManager::GetFade()->SetFade(CScene::MODE_TITEL);
	}

}

//-------------------------------------
//- ���U���g�̕`�揈��
//-------------------------------------
void CResult::Draw(void)
{

}
