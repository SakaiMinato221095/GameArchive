
//-===============================================
//-
//-	�Ǘ�����[manager.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "manager.h"

#include "manager_object.h"

#include "Input.h"
#include "sound.h"
#include "debugproc.h"

#include "manager_texture.h"
#include "manager_model.h"
#include "manager_time.h"

#include "camera.h"
#include "light.h"

#include "renderer.h"

#include "object2d.h"

#include "object3d.h"

#include "object_x.h"

#include "object_billboard.h"

#include "object_model.h"

#include "edit_map.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

CManagerObject *CManager::m_pManagerObject = NULL;

CRenderer *CManager::m_pRenderer = NULL;

CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CSound *CManager::m_pSound = NULL;
CDebugProc *CManager::m_pDbugProc = NULL;

CManagerTexture *CManager::m_pManagerTexture = NULL;
CManagerModel *CManager::m_pManagerModel = NULL;
CManagerTime *CManager::m_pManagerTime = NULL;

CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;

CEditMap *CManager::m_pMapEdit = NULL;

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CManager::CManager()
{
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CManager::~CManager()
{

}

//-------------------------------------
//- �Ǘ��̏���������
//-------------------------------------
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �L�[�{�[�h
	{
		// �L�[�{�[�h�̗L���𔻒�
		if (m_pInputKeyboard == NULL)
		{
			// �L�[�{�[�h�̐���
			m_pInputKeyboard = new CInputKeyboard;

			// �L�[�{�[�h�̏���������
			if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
			{// ���s��

				// ���s���b�Z�[�W
				MessageBox(hWnd, "�L�[�{�[�h�̐���", "�����������s�I", MB_ICONWARNING);

				// �������𔲂���
				return E_FAIL;
			}
		}
		else
		{// �S�~�������Ă���Ƃ�

			// ���s���b�Z�[�W
			MessageBox(hWnd, "�L�[�{�[�h�̏�����", "�����������s�I", MB_ICONWARNING);

			// �������𔲂���
			return E_FAIL;
		}
	}

	// �T�E���h
	{
		// �T�E���h�L���𔻒�
		if (m_pSound == NULL)
		{
			// �T�E���h����
			m_pSound = new CSound;

			// �T�E���h����������
			if (FAILED(m_pSound->Init(hWnd)))
			{// ���s��

				// ���s���b�Z�[�W
				MessageBox(hWnd, "�T�E���h�̐���", "�����������s�I", MB_ICONWARNING);

				// �������𔲂���
				return E_FAIL;
			}
		}
		else
		{// �S�~�������Ă���Ƃ�

			// ���s���b�Z�[�W
			MessageBox(hWnd, "�T�E���h�̏�����", "�����������s�I", MB_ICONWARNING);

			// �������𔲂���
			return E_FAIL;
		}
	}

	// �����_���[
	{
		// �����_���[�̗L���𔻒�
		if (m_pRenderer == NULL)
		{
			// �����_���[�̐���
			m_pRenderer = new CRenderer;

			// �����_���[�̏���������
			if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
			{// ���s��

				// ���s���b�Z�[�W
				MessageBox(hWnd, "�����_���[�̐���", "�����������s�I", MB_ICONWARNING);

				// �������𔲂���
				return E_FAIL;
			}
		}
		else
		{// �S�~�������Ă���Ƃ�

			// ���s���b�Z�[�W
			MessageBox(hWnd, "�����_���[�̏�����", "�����������s�I", MB_ICONWARNING);

			// �������𔲂���
			return E_FAIL;
		}
	}

	// �f�o�b�N�v���b�N
	{
		// �f�o�b�N�v���b�N�L���𔻒�
		if (m_pDbugProc == NULL)
		{
			// �f�o�b�N�v���b�N����
			m_pDbugProc = new CDebugProc;

			// �f�o�b�N�v���b�N����������
			m_pDbugProc->Init();
		}
	}

	// �e�N�X�`���Ǘ�
	{
		// �e�N�X�`���Ǘ��̗L���𔻒�
		if (m_pManagerTexture == NULL)
		{
			// �e�N�X�`���Ǘ��̐���
			m_pManagerTexture = new CManagerTexture;

			// �e�N�X�`���Ǘ��̏���������
			if (FAILED(m_pManagerTexture->Load(hWnd)))
			{// ���s��

				// ���s���b�Z�[�W
				MessageBox(hWnd, "�e�N�X�`���Ǘ��̓ǂݍ���", "�����������s�I", MB_ICONWARNING);

				// �������𔲂���
				return E_FAIL;
			}
		}
		else
		{// �S�~�������Ă���Ƃ�

			// ���s���b�Z�[�W
			MessageBox(hWnd, "�e�N�X�`���Ǘ��̓ǂݍ���", "�����������s�I", MB_ICONWARNING);

			// �������𔲂���
			return E_FAIL;
		}
	}

	// ���f���Ǘ�
	{
		// ���f���Ǘ��̗L���𔻒�
		if (m_pManagerModel == NULL)
		{
			// ���f���Ǘ��̐���
			m_pManagerModel = new CManagerModel;

			// ���f���Ǘ��̏���������
			if (FAILED(m_pManagerModel->Load(hWnd)))
			{// ���s��

				// ���s���b�Z�[�W
				MessageBox(hWnd, "���f���Ǘ��̓ǂݍ���", "�����������s�I", MB_ICONWARNING);

				// �������𔲂���
				return E_FAIL;
			}
		}
		else
		{// �S�~�������Ă���Ƃ�

			// ���s���b�Z�[�W
			MessageBox(hWnd, "���f���Ǘ��̓ǂݍ���", "�����������s�I", MB_ICONWARNING);

			// �������𔲂���
			return E_FAIL;
		}
	}

	// ���ԊǗ�
	{
		// ���ԊǗ��̗L���𔻒�
		if (m_pManagerTime == NULL)
		{
			// ���ԊǗ��̐���
			m_pManagerTime = CManagerTime::Create();

			// ���ԊǗ��̐��������̗L���𔻒�
			if (m_pManagerTime == NULL)
			{
				// ���s���b�Z�[�W
				MessageBox(hWnd, "���ԊǗ��̐���", "�����������s�I", MB_ICONWARNING);

				// ���������𔲂���
				return E_FAIL;
			}
		}
	}

	// �J����
	{
		// �J�����̗L���𔻒�
		if (m_pCamera == NULL)
		{
			// �J�����̐���
			m_pCamera = new CCamera;

			// �J�����̏���������
			if (FAILED(m_pCamera->Init()))
			{// ���s��

				// ���s���b�Z�[�W
				MessageBox(hWnd, "�J�����̐���", "�����������s�I", MB_ICONWARNING);

				// �������𔲂���
				return E_FAIL;
			}
		}
		else
		{// �S�~�������Ă���Ƃ�

			// ���s���b�Z�[�W
			MessageBox(hWnd, "�J�����̏�����", "�����������s�I", MB_ICONWARNING);

			// �������𔲂���
			return E_FAIL;
		}
	}

	// ���C�g
	{
		// ���C�g�̗L���𔻒�
		if (m_pLight == NULL)
		{
			// ���C�g�̐���
			m_pLight = new CLight;

			// ���C�g�̏���������
			if (FAILED(m_pLight->Init()))
			{// ���s��

				// ���s���b�Z�[�W
				MessageBox(hWnd, "���C�g�̐���", "�����������s�I", MB_ICONWARNING);

				// �������𔲂���
				return E_FAIL;
			}
		}
		else
		{// �S�~�������Ă���Ƃ�

		 // ���s���b�Z�[�W
			MessageBox(hWnd, "���C�g�̏�����", "�����������s�I", MB_ICONWARNING);

			// �������𔲂���
			return E_FAIL;
		}
	}

	// �I�u�W�F�N�g�Ǘ��̏�����
	{
		// �I�u�W�F�N�g�Ǘ��̗L���𔻒�
		if (m_pManagerObject == NULL)
		{
			// �I�u�W�F�N�g�Ǘ��̐���
			m_pManagerObject = new CManagerObject;

			// �I�u�W�F�N�g�Ǘ��̏���������
			if (FAILED(m_pManagerObject->Init(hInstance,hWnd,bWindow)))
			{// ���s��

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

	// �}�b�v�G�f�B�^�̏�����
	{
		// �}�b�v�G�f�B�^�̗L���𔻒�
		if (m_pMapEdit == NULL)
		{
			// �}�b�v�G�f�B�^�̏���������
			if (FAILED(m_pMapEdit = CEditMap::Create(hInstance, hWnd, bWindow)))
			{// ���s��

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

	// ���̐ݒ�
	if (m_pSound != NULL)
	{
		// BGM�𗬂�
		//m_pSound->Play(CSound::LABEL_BGM_GAME_000);
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �Ǘ��̏I������
//-------------------------------------
void CManager::Uninit(void)
{
	// �L�[�{�[�h�̔j��
	if (m_pInputKeyboard != NULL)
	{
		// �L�[�{�[�h�̏I������
		m_pInputKeyboard->Uninit();

		// �L�[�{�[�h�̊J��
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	// �T�E���h�̔j��
	if (m_pSound != NULL)
	{
		// �T�E���h�̏I������
		m_pSound->Uninit();

		// �T�E���h�̊J��
		delete m_pSound;
		m_pSound = NULL;
	}

	// �f�o�b�N�v���b�N�̔j��
	if (m_pDbugProc != NULL)
	{
		// �f�o�b�N�v���b�N�̏I������
		m_pDbugProc->Uninit();

		// �f�o�b�N�v���b�N�̊J��
		delete m_pDbugProc;
		m_pDbugProc = NULL;
	}

	// �e�N�X�`���Ǘ��̔j��
	if (m_pManagerTexture != NULL)
	{
		// �e�N�X�`���Ǘ��̏I������
		m_pManagerTexture->Unload();

		// �e�N�X�`���Ǘ��̊J��
		delete m_pManagerTexture;
		m_pManagerTexture = NULL;
	}

	// ���f���Ǘ��̔j��
	if (m_pManagerModel != NULL)
	{
		// ���f���Ǘ��̏I������
		m_pManagerModel->Unload();

		// ���f���Ǘ��̊J��
		delete m_pManagerModel;
		m_pManagerModel = NULL;
	}

	// ���ԊǗ��̔j��
	if (m_pManagerTime != NULL)
	{
		// ���ԊǗ��̏I������
		m_pManagerTime->Uninit();

		// ���ԊǗ��̊J��
		delete m_pManagerTime;
		m_pManagerTime = NULL;
	}

	// �J�����̗L���𔻒�
	if (m_pCamera != NULL)
	{
		// �J�����̏I������
		m_pCamera->Uninit();

		// �J�����̊J������
		delete m_pCamera;
		m_pCamera = NULL;
	}

	// ���C�g�̗L���𔻒�
	if (m_pLight != NULL)
	{
		// ���C�g�̏I������
		m_pLight->Uninit();

		// ���C�g�̊J������
		delete m_pLight;
		m_pLight = NULL;
	}

	// �I�u�W�F�N�g�̑S�J������
	CObject::ReleaseAll();

	// �I�u�W�F�N�g�Ǘ��̗L���𔻒�
	if (m_pManagerObject != NULL)
	{
		// �I�u�W�F�N�g�̏I��
		m_pManagerObject->Uninit();

		// �I�u�W�F�N�g�Ǘ��̊J������
		delete m_pManagerObject;
		m_pManagerObject = NULL;
	}

	// �}�b�v�G�f�B�^�̊J��
	if (m_pMapEdit != NULL)
	{
		// �}�b�v�G�f�B�^�̏I��
		m_pMapEdit->Uninit();

		// �}�b�v�G�f�B�^�Ǘ��̊J������
		delete m_pMapEdit;
		m_pMapEdit = NULL;
	}

	// �����_���[�̔j��
	if (m_pRenderer != NULL)
	{
		// �����_���[�̏I������
		m_pRenderer->Uninit();

		// �����_���[�̊J������
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//-------------------------------------
//- �Ǘ��̍X�V����
//-------------------------------------
void CManager::Update(void)
{
	// �L�[�{�[�h�̗L���𔻒�
	if (m_pInputKeyboard != NULL)
	{
		// �L�[�{�[�h�̍X�V����
		m_pInputKeyboard->Update();
	}

	// ���ԊǗ��̗L���𔻒�
	if (m_pManagerTime != NULL)
	{
		// �J�����̍X�V����
		m_pManagerTime->Update();
	}

	// �J�����̗L���𔻒�
	if (m_pCamera != NULL)
	{
		// �J�����̍X�V����
		m_pCamera->Update();
	}

	// �f�o�b�N�v���b�N�̗L���𔻒�
	if (m_pDbugProc != NULL)
	{
		// �f�o�b�N�v���b�N�̍X�V����
		m_pDbugProc->Update();
	}

	// ���C�g�̗L���𔻒�
	if (m_pLight != NULL)
	{
		// ���C�g�̍X�V����
		m_pLight->Update();
	}

	// �}�b�v�G�f�B�^�̗L���𔻒�
	if (m_pMapEdit != NULL)
	{
		// �}�b�v�G�f�B�^�̍X�V����
		m_pMapEdit->Update();
	}

	// �����_���[�̗L���𔻒�
	if (m_pRenderer != NULL)
	{
		// �����_���[�̍X�V����
		m_pRenderer->Update();
	}

	// �f�o�b�N����
	DebugCommand();
}

//-------------------------------------
//- �Ǘ��̕`�揈��
//-------------------------------------
void CManager::Draw(void)
{
	// �J�����̏����擾
	CCamera *pCamera = CManager::GetCamera();

	// �J�����̗L���𔻒�
	if (pCamera != NULL)
	{
		// �J�����̐ݒ�
		pCamera->SetCamera();
	}

	// �����_���[�̗L���𔻒�
	if (m_pRenderer != NULL)
	{
		// �����_���[�̕`�揈��
		m_pRenderer->Draw();
	}
}

//-------------------------------------
//- �I�u�W�F�N�g�Ǘ��̏����擾
//-------------------------------------
CManagerObject * CManager::GetManagerObject(void)
{
	return m_pManagerObject;
}

//-------------------------------------
//- �����_���[�̏����擾
//-------------------------------------
CRenderer *CManager::GetRenderer(void)
{
	// �����_���[�̃|�C���^��Ԃ�
	return m_pRenderer;
}

//-====================================
//-	�L�[�{�[�h�̏����擾
//-====================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	// �L�[�{�[�h�̃|�C���^��Ԃ�
	return m_pInputKeyboard;
}

//-====================================
//-	�T�E���h�̏����擾
//-====================================
CSound *CManager::GetSound(void)
{
	// �L�[�{�[�h�̃|�C���^��Ԃ�
	return m_pSound;
}

//-====================================
//-	�f�o�b�N�v���b�N�̏����擾
//-====================================
CDebugProc * CManager::GetDbugProc(void)
{
	// �f�o�b�N�v���b�N��Ԃ�
	return m_pDbugProc;
}

//-====================================
//-	�e�N�X�`���Ǘ��̏����擾
//-====================================
CManagerTexture *CManager::GetManagerTexture(void)
{
	// �e�N�X�`���Ǘ���Ԃ�
	return m_pManagerTexture;
}

//-====================================
//-	���f���Ǘ��̏����擾
//-====================================
CManagerModel *CManager::GetManagerModel(void)
{
	return m_pManagerModel;
}

//-====================================
//-	�e�N�X�`���Ǘ��̏����擾
//-====================================
CManagerTime * CManager::GetManagerTime(void)
{
	return m_pManagerTime;
}

//-====================================
//-	�J�����̏����擾
//-====================================
CCamera *CManager::GetCamera(void)
{
	// �L�[�{�[�h�̃|�C���^��Ԃ�
	return m_pCamera;
}

//-====================================
//-	���C�g�̏����擾
//-====================================
CLight * CManager::GetLight(void)
{
	return m_pLight;
}

//-====================================
//-	�}�b�v�G�f�B�^�̏����擾
//-====================================
CEditMap * CManager::GetMapEdit(void)
{
	return nullptr;
}

//-====================================
//-	�f�o�b�N����
//-====================================
void CManager::DebugCommand(void)
{
	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (m_pInputKeyboard == NULL)
	{// ���s��

		// �ړ������𔲂���
		return;
	}
}
