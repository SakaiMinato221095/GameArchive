
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

#include "manager.h"
#include "renderer.h"

#include "manager_texture.h"

#include "camera.h"

#include "fade.h"

#include "Input.h"
#include "xinput.h"
#include "sound.h"

#include "character.h"

#include "skybox.h"
#include "obj_3d_field.h"

#include "object2d.h"

//=======================================
//=	�R���X�g��`
//=======================================

// �e�N�X�`�����
const char* pDataTexture[CTitle::TEX_MAX] =
{
	"data\\TEXTURE\\Title\\Logo000.png",		// �^�C�g�����S�̃e�N�X�`��
	"data\\TEXTURE\\Title\\Button000.png",		// �^�C�g���{�^���̃e�N�X�`��
};

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

CCharacter *CTitle::m_pCharacter = {};
CObject2d *CTitle::m_apObj2d[TYPE_2D_MAX] = {};
int CTitle::m_aTextureNldx[TEX_MAX] = {};

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
//- �ʏ�2D�I�u�W�F�N�g�̓ǂݍ��ݏ���
//-------------------------------------
HRESULT CTitle::Load(void)
{
	// �擾����
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	CManagerTexture* pManagerTexture = CManager::GetInstance()->GetManagerTexture();

	// �擾�̗L���𔻒�
	if (pDevice == nullptr ||
		pManagerTexture == nullptr)
	{// ���s��

		// �����������𔲂���
		return E_FAIL;
	}

	// �e�N�X�`���ݒ�
	for (int nCount = 0; nCount < TEX_MAX; nCount++)
	{
		// �e�N�X�`���ԍ��̎擾�i�e�N�X�`���̊����j
		m_aTextureNldx[nCount] = pManagerTexture->Regist(pDataTexture[nCount]);

		// �e�N�X�`���̓ǂݍ��ݐ����̗L�����m�F
		if (m_aTextureNldx[nCount] == -1)
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
void CTitle::Unload(void)
{

}

//-------------------------------------
//- �^�C�g���̏���������
//-------------------------------------
HRESULT CTitle::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// ���擾
	CCamera *pCamera = CManager::GetInstance()->GetCamera();
	CSound* pSound = CManager::GetInstance()->GetSound();

	// �擾�̗L���𔻒�
	if (pCamera == nullptr ||
		pSound == nullptr)
	{
		return E_FAIL;
	}

	// �J�����̐ݒ菈��
	pCamera->SetMode(CCamera::MODE_TITLE);

	// �^�C�g���̍Đ�
	pSound->Play(CSound::LABEL_BGM_TITLE);

	// �X�J�C�{�b�N�X�̐���
	CSkybox::Create(
		CSkybox::MODEL_SKYBOX_000,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// �t�B�[���h�̐���
	CObj3dField* pField = CObj3dField::Create(CObj3dField::TEX_GLASS_000);

	if (pField != nullptr)
	{
		pField->InitSet(
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(5000.0f, 0.0f, 5000.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			D3DXVECTOR2(10.0f, 10.0f));
	}

	if (m_pCharacter == NULL)
	{
		// �v���C���[�̐���
		m_pCharacter = CCharacter::Create(
			CModel::MODEL_TYPE_PLAYER,			// ���f��
			CMotion::MOTION_TYPE_PLAYER,
			1);			// ���[�V����
	}

	for (int nCnt2d = 0; nCnt2d < TYPE_2D_MAX; nCnt2d++)
	{
		if (m_apObj2d[nCnt2d] == nullptr)
		{
			switch (nCnt2d)
			{
			case TYPE_2D_LOGO:

				// �I�u�W�F�N�g�Ǘ��̐���
				m_apObj2d[nCnt2d] = CObject2d::Create();

				if (m_apObj2d[nCnt2d] != nullptr)
				{
					m_apObj2d[nCnt2d]->SetInit(
						D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.3f, 0.0f),
						D3DXVECTOR3(300.0f, 150.0f, 0.0f),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

					m_apObj2d[nCnt2d]->BindTexture(m_aTextureNldx[nCnt2d]);
				}

				break;

			case TYPE_2D_BUTTON:

				// �I�u�W�F�N�g�Ǘ��̐���
				m_apObj2d[nCnt2d] = CObject2d::Create();

				if (m_apObj2d[nCnt2d] != nullptr)
				{
					m_apObj2d[nCnt2d]->SetInit(
						D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.8f, 0.0f),
						D3DXVECTOR3(200.0f, 100.0f, 0.0f),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

					m_apObj2d[nCnt2d]->BindTexture(m_aTextureNldx[nCnt2d]);
				}

				break;
			}

			if (m_apObj2d[nCnt2d] == nullptr)
			{
				// ���s���b�Z�[�W
				MessageBox(hWnd, "2D�I�u�W�F�N�g�̐���", "�����������s�I", MB_ICONWARNING);

				// �������𔲂���
				return E_FAIL;
			}
		}
		else
		{
			// ���s���b�Z�[�W
			MessageBox(hWnd, "2D�I�u�W�F�N�g�̐���", "�����������s�I", MB_ICONWARNING);

			// �������𔲂���
			return E_FAIL;
		}
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �^�C�g���̏I������
//-------------------------------------
void CTitle::Uninit(void)
{
	if (m_pCharacter != NULL)
	{
		m_pCharacter->Uninit();
		m_pCharacter = NULL;
	}

	for (int nCount = 0; nCount < TYPE_2D_MAX; nCount++)
	{
		m_apObj2d[nCount]->Uninit();
		m_apObj2d[nCount] = nullptr;
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
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

		// �X�V�����𔲂���
		return;
	}

	// X���͂̃|�C���^��錾
	CXInput *pXInput = CManager::GetInstance()->GetXInput();

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
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_GAME);
	}
}

//-------------------------------------
//- �^�C�g���̕`�揈��
//-------------------------------------
void CTitle::Draw(void)
{

}