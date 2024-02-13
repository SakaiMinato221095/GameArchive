
//================================================
//=
//=	�|�[�Y��ʏ���[pause.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "pause.h"

#include "object2d.h"

#include "manager.h"
#include "renderer.h"

#include "manager_texture.h"

#include "fade.h"

#include "object.h"
#include "camera.h"

#include "Input.h"
#include "xinput.h"
#include "sound.h"

//=======================================
//=	�}�N����`
//=======================================

#define WINDOW_POS_X		(SCREEN_WIDTH * 0.5f)	//�|�[�Y�̘g�̈ʒu(X)
#define WINDOW_POS_Y		(SCREEN_HEIGHT * 0.5f)	//�|�[�Y�̘g�̈ʒu(Y)
#define WINDOW_SIZE_X		(300.0f)				//�|�[�Y�̘g�̃T�C�Y(X)
#define WINDOW_SIZE_Y		(200.0f)				//�|�[�Y�̘g�̃T�C�Y(Y)
#define MENU_POS_X			(SCREEN_WIDTH * 0.5f)	//�|�[�Y���j���[�̍ŏ��̊J�n�ʒu�iX)
#define MENU_POS_Y			(230.0f)				//�|�[�Y���j���[�̍ŏ��̊J�n�ʒu�iY�j	
#define MENU_SIZE_X			(200.0f)				//�|�[�Y���j���[�̑傫���iX�j
#define MENU_SIZE_Y			(60.0f)					//�|�[�Y���j���[�̑傫���iY�j
#define MENU_INTERVAL_Y		(130.0f)				//�|�[�Y���j���[�̊Ԋu�iY�j

//=======================================
//=	�R���X�g��`
//=======================================

// �|�[�Y�̃e�N�X�`��
const char* Texture[] =
{
	"data\\TEXTURE\\Pause\\Bg.jpg",				// �w�i
	"data\\TEXTURE\\Pause\\BackToGame.png",		// �Q�[�����s�e�N�X�`��
	"data\\TEXTURE\\Pause\\GameRetry.png",		// �Q�[����蒼���e�N�X�`��
	"data\\TEXTURE\\Pause\\QuitTitle.png",		// �^�C�g���ɖ߂�e�N�X�`��
	"data\\TEXTURE\\Pause\\Cursor.png",			// �J�[�\���e�N�X�`��
};

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

int CPause::m_nTextureNldx[TEX_MAX] = {};

//-------------------------------------
//-	�|�[�Y�̃R���X�g���N�^
//-------------------------------------
CPause::CPause()
{
	ZeroMemory(&m_infoVisual,sizeof(m_infoVisual));
	m_typeSelect = (TYPE_SELECT)0;
	m_bOk = false;
}

//-------------------------------------
//-	�|�[�Y�̃f�X�g���N�^
//-------------------------------------
CPause::~CPause()
{

}

//-------------------------------------
//-	�|�[�Y�̃f�[�^�ǂݍ���
//-------------------------------------
HRESULT CPause::Load(void)
{
	// ���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	CManagerTexture* pManagerTexture = CManager::GetInstance()->GetManagerTexture();

	// ���擾�̐����𔻒�
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
		m_nTextureNldx[nCount] = pManagerTexture->Regist(Texture[nCount]);

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
//-	�|�[�Y�̃f�[�^�j��
//-------------------------------------
void CPause::Unload(void)
{
}

//-------------------------------------
//- �|�[�Y�̏���������
//-------------------------------------
HRESULT CPause::Init(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_infoVisual.apObj2d[nCnt] == NULL)
		{
			// �I�u�W�F�N�g�Ǘ��̐���
			m_infoVisual.apObj2d[nCnt] = CObject2d::Create();

			// �I�u�W�F�N�g�Ǘ��̏���������
			if (m_infoVisual.apObj2d[nCnt] == NULL)
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

	for (int nCutPause = 0; nCutPause < TYPE_MAX; nCutPause++)
	{
		if (m_infoVisual.apObj2d[nCutPause] != nullptr)
		{
			if (nCutPause == TYPE_BG)
			{
				m_infoVisual.apObj2d[nCutPause]->SetInit(
					D3DXVECTOR3(WINDOW_POS_X, WINDOW_POS_Y, 0.0f),
					D3DXVECTOR3(WINDOW_SIZE_X, WINDOW_SIZE_Y, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else if (nCutPause == TYPE_CURSOR)
			{
				m_infoVisual.apObj2d[nCutPause]->SetInit(
					D3DXVECTOR3(MENU_POS_X - 250.0f, MENU_POS_Y, 0.0f),
					D3DXVECTOR3(30.0f, 30.0f, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				m_infoVisual.apObj2d[nCutPause]->SetInit(
					D3DXVECTOR3(MENU_POS_X, MENU_POS_Y + (MENU_INTERVAL_Y * (nCutPause - 1)), 0.0f),
					D3DXVECTOR3(MENU_SIZE_X, MENU_SIZE_Y, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}

			m_infoVisual.apObj2d[nCutPause]->BindTexture(m_nTextureNldx[nCutPause]);
		}


	}

	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	if (pCamera != nullptr)
	{
		pCamera->SetIsUpdateStop(true);
	}

	// �S��~����
	CObject::SetIsUpdateAllStop(true);

	// �I�u�W�F�N�g�̍X�V��~���O
	for (int nCutPause = 0; nCutPause < TYPE_MAX; nCutPause++)
	{
		m_infoVisual.apObj2d[nCutPause]->SetIsUpdatePause(true);
	}


	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �|�[�Y�̏I������
//-------------------------------------
void CPause::Uninit(void)
{
	for (int nCutPause = 0; nCutPause < TYPE_MAX; nCutPause++)
	{
		if (m_infoVisual.apObj2d[nCutPause] != NULL)
		{
			// ���ʂȂ�2D�I�u�W�F�N�g�̊J������
			m_infoVisual.apObj2d[nCutPause]->Uninit();
			m_infoVisual.apObj2d[nCutPause] = NULL;
		}
	}

	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	
	if (pCamera != nullptr)
	{
		pCamera->SetIsUpdateStop(false);
	}

	// �S��~����
	CObject::SetIsUpdateAllStop(false);

}

//-------------------------------------
//- �|�[�Y�̍X�V����
//-------------------------------------
void CPause::Update(void)
{
	// ���擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CXInput* pXInput = CManager::GetInstance()->GetXInput();

	// ���擾�̐����𔻒�
	if (pInputKeyboard == NULL ||
		pXInput == NULL)
	{// ���s��

		// �X�V�����𔲂���
		return;
	}

	if (pInputKeyboard->GetTrigger(DIK_W) != NULL)
	{
		// ��ނ����Z
		m_typeSelect = (TYPE_SELECT)(m_typeSelect - 1);

		if (m_typeSelect < 0)
		{
			m_typeSelect = TYPE_SELECT_TITLE;
		}

		m_infoVisual.apObj2d[TYPE_CURSOR]->SetPos(
			D3DXVECTOR3(
				MENU_POS_X - 250.0f, 
				MENU_POS_Y + (MENU_INTERVAL_Y * m_typeSelect),
				0.0f));

	}
	else if (pInputKeyboard->GetTrigger(DIK_S) != NULL)
	{
		// ��ނ����Z
		m_typeSelect = (TYPE_SELECT)(m_typeSelect + 1);

		if (m_typeSelect > TYPE_SELECT_TITLE)
		{
			m_typeSelect = (TYPE_SELECT)0;
		}

		m_infoVisual.apObj2d[TYPE_CURSOR]->SetPos(
			D3DXVECTOR3(
				MENU_POS_X - 250.0f, 
				MENU_POS_Y + (MENU_INTERVAL_Y * m_typeSelect), 
				0.0f));
	}
	
	if (pInputKeyboard->GetTrigger(DIK_RETURN) != NULL)
	{
		m_bOk = true;
	}
}

//-------------------------------------
//- �|�[�Y�̕`�揈��
//-------------------------------------
void CPause::Draw(void)
{

}

//-------------------------------------
//- �|�[�Y�̐�������
//-------------------------------------
CPause *CPause::Create(void)
{
	// �|�[�Y�̐���
	CPause *pCPause = DBG_NEW CPause;

	// �����̐����̗L���𔻒�
	if (pCPause != NULL)
	{
		// ����������
		if (FAILED(pCPause->Init()))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCPause == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �|�[�Y�̃|�C���^��Ԃ�
	return pCPause;
}

