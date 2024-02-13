
//================================================
//=
//=	�^�C�g����ʏ���[title.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "title.h"

#include "camera.h"

#include "fade.h"

#include "Input.h"
#include "xinput.h"
#include "sound.h"

#include "manager_object.h"
#include "obj_2d_none.h"

#include "file_obj_none.h"
#include "file_evt_obj.h"
#include "file_garbage.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

CManagerObject *CTitle::m_pManagerObject = {};
CObj2dNone *CTitle::m_apObj2dNone[CTitle::TYPE_NONE_2D_MAX] = {};

//-------------------------------------
//-	�^�C�g���̃R���X�g���N�^
//-------------------------------------
CTitle::CTitle()
{

}

//-------------------------------------
//-	�^�C�g���̃f�X�g���N�^
//-------------------------------------
CTitle::~CTitle()
{

}

//-------------------------------------
//- �^�C�g���̏���������
//-------------------------------------
HRESULT CTitle::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �I�u�W�F�N�g�Ǘ��̏�����
	{
		// �I�u�W�F�N�g�Ǘ��̗L���𔻒�
		if (m_pManagerObject == NULL)
		{
			// �I�u�W�F�N�g�Ǘ��̐���
			m_pManagerObject = DBG_NEW CManagerObject;

			// �I�u�W�F�N�g�Ǘ��̏���������
			if (FAILED(m_pManagerObject->Init(hInstance, hWnd, bWindow)))
			{// ���s��

			 // ���s���b�Z�[�W
				MessageBox(hWnd, "�I�u�W�F�N�g�Ǘ��̐���", "�����������s�I", MB_ICONWARNING);

				// �������𔲂���
				return E_FAIL;
			}
		}
		else
		{// �S�~�������Ă���Ƃ�

		 // �������𔲂���
			return E_FAIL;
		}
	}

	// �I�u�W�F�N�g�Ǘ��̗L���𔻒�
	if (m_apObj2dNone[TYPE_NONE_2D_LOGO] == NULL)
	{
		// �I�u�W�F�N�g�Ǘ��̐���
		m_apObj2dNone[TYPE_NONE_2D_LOGO] = CObj2dNone::Create(CObj2dNone::TEX_TITLE_LOGO);

		// �I�u�W�F�N�g�Ǘ��̏���������
		if (m_apObj2dNone[TYPE_NONE_2D_LOGO] == NULL)
		{// ���s��

			// ���s���b�Z�[�W
			MessageBox(hWnd, "���ʂȂ�2D�I�u�W�F�N�g�̐���", "�����������s�I", MB_ICONWARNING);

			// �������𔲂���
			return E_FAIL;
		}

		m_apObj2dNone[TYPE_NONE_2D_LOGO]->Set(
			D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.4f,0.0f),
			D3DXVECTOR3(400.0f,200.0f,0.0f));
	}
	else
	{// �S�~�������Ă���Ƃ�

		// �������𔲂���
		return E_FAIL;
	}

	// �I�u�W�F�N�g�Ǘ��̗L���𔻒�
	if (m_apObj2dNone[TYPE_NONE_2D_BUTTON] == NULL)
	{
		// �I�u�W�F�N�g�Ǘ��̐���
		m_apObj2dNone[TYPE_NONE_2D_BUTTON] = CObj2dNone::Create(CObj2dNone::TEX_TITLE_BUTTON);

		// �I�u�W�F�N�g�Ǘ��̏���������
		if (m_apObj2dNone[TYPE_NONE_2D_BUTTON] == NULL)
		{// ���s��

			// ���s���b�Z�[�W
			MessageBox(hWnd, "���ʂȂ�2D�I�u�W�F�N�g�̐���", "�����������s�I", MB_ICONWARNING);

			// �������𔲂���
			return E_FAIL;
		}

		m_apObj2dNone[TYPE_NONE_2D_BUTTON]->Set(
			D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.8f, 0.0f),
			D3DXVECTOR3(200.0f, 100.0f, 0.0f));
	}
	else
	{// �S�~�������Ă���Ƃ�

		// �������𔲂���
		return E_FAIL;
	}

	// ���ʂȂ��I�u�W�F�N�g�ǂݍ��ݐݒ菈��
	CFileObjNone::Load(CFileObjNone::TXT_NORMAL_000);

	// �C�x���g�I�u�W�F�N�g�ǂݍ��ݐݒ菈��
	CFileEvtObj::Load(CFileEvtObj::TXT_NORMAL_000);

	// �J�����̐ݒ菈��
	CManager::GetCamera()->SetMode(CCamera::MODE_TITLE);

	// �T�E���h�̃|�C���^��錾
	CSound *pSound = CManager::GetSound();

	// �T�E���h�̏��擾�̐����𔻒�
	if (pSound == NULL)
	{
		// �����𔲂���
		return E_FAIL;
	}

	// ���ˉ�SE�̍Đ�
	pSound->Play(CSound::LABEL_BGM_TITLE);

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �^�C�g���̏I������
//-------------------------------------
void CTitle::Uninit(void)
{
	// �I�u�W�F�N�g�Ǘ��̗L���𔻒�
	if (m_pManagerObject != NULL)
	{
		// �I�u�W�F�N�g�̏I��
		m_pManagerObject->Uninit();

		// �I�u�W�F�N�g�Ǘ��̊J������
		delete m_pManagerObject;
		m_pManagerObject = NULL;
	}

	for (int nCount = 0; nCount < TYPE_NONE_2D_MAX; nCount++)
	{
		if (m_apObj2dNone[nCount] != NULL)
		{
			// ���ʂȂ�2D�I�u�W�F�N�g�̊J������
			m_apObj2dNone[nCount]->Uninit();
			m_apObj2dNone[nCount] = NULL;
		}
	}

	// �I�u�W�F�N�g�̑S�J������
	CObject::ReleaseAll();
}

//-------------------------------------
//- �^�C�g���̍X�V����
//-------------------------------------
void CTitle::Update(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
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
		pXInput->GetTrigger(XINPUT_GAMEPAD_A,CXInput::TYPE_INPUT_BUTTON))
	{
		// �Q�[�����[�h
		CManager::GetFade()->SetFade(CScene::MODE_GAME);
	}
}

//-------------------------------------
//- �^�C�g���̕`�揈��
//-------------------------------------
void CTitle::Draw(void)
{

}

//-------------------------------------
//-	�I�u�W�F�N�g�Ǘ��̏����擾
//-------------------------------------
CManagerObject * CTitle::GetManagerObject(void)
{
	return m_pManagerObject;
}

//-------------------------------------
//-	���ʂȂ�2d�I�u�W�F�N�g�̏����擾
//-------------------------------------
CObj2dNone * CTitle::GetObj2dNone(int nNum)
{
	return m_apObj2dNone[nNum];
}
