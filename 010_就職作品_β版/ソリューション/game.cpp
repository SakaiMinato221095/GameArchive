
//================================================
//=
//=	�Q�[����ʏ���[game.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "game.h"

#include "manager.h"

#include "fade.h"

#include "input.h"
#include "xinput.h"
#include "sound.h"

#include "pause.h"

#include "camera.h"

#include "player.h"

#include "spwan_wall.h"
#include "enemy_boss.h"

#include "obj_3d_field.h"
#include "obj_3d_wall.h"
#include "objectx_none.h"

#include "skybox.h"

#include "timer.h"

#include "map_manager.h"

//=======================================
//=	�}�N����`
//=======================================

const D3DXVECTOR3 SPWAN_WALL_POS[CPhaseManager::TYPE_PHASE_COMP] =
{
	D3DXVECTOR3(0.0f, 100.0f, 500.0f),
	D3DXVECTOR3(0.0f, 100.0f, 3000.0f),
	D3DXVECTOR3(0.0f, 100.0f, 5500.0f),
};

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

CGame::InfoPoint CGame::m_infoPoint = {};

//-------------------------------------
//-	�Q�[����ʂ̃R���X�g���N�^
//-------------------------------------
CGame::CGame()
{
	m_gameState = (GAME_STATE)0;
}

//-------------------------------------
//-	�Q�[����ʂ̃f�X�g���N�^
//-------------------------------------
CGame::~CGame()
{

}

//-------------------------------------
//- �Q�[����ʂ̏���������
//-------------------------------------
HRESULT CGame::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{		
	// ���擾�̐ݒ菈��
	CCamera *pCamera = CManager::GetInstance()->GetCamera();
	CSound* pSound = CManager::GetInstance()->GetSound();

	// �擾�̗L������
	if (pCamera == NULL ||
		pSound == NULL)
	{
		return E_FAIL;
	}

	// �J�����̐ݒ菈��
	pCamera->SetMode(CCamera::MODE_FOLLOWING);

	if (m_infoPoint.pPhaseManager == nullptr)
	{
		// �t�F�[�Y�Ǘ��̐���
		m_infoPoint.pPhaseManager = CPhaseManager::Create();

		if (m_infoPoint.pPhaseManager == nullptr)
		{// ���s��

			return E_FAIL;
		}
	}

	if (m_infoPoint.pSkyBox == nullptr)
	{
		// �X�J�C�{�b�N�X�̐���
		m_infoPoint.pSkyBox = CSkybox::Create(
			CSkybox::MODEL_SKYBOX_000,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	{
		// �t�B�[���h�̐���
		CObj3dField* pField = CObj3dField::Create(CObj3dField::TEX_ASPHALT_000);

		if (pField != nullptr)
		{
			pField->InitSet(
				D3DXVECTOR3(0.0f, 0.0f, 3000.0f),
				D3DXVECTOR3(4000.0f, 0.0f, 5000.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				D3DXVECTOR2(10.0f, 10.0f));
		}
	}

	{
		// �t�B�[���h�̐���
		CObj3dField* pField = CObj3dField::Create(CObj3dField::TEX_ROAD_000);

		if (pField != nullptr)
		{
			pField->InitSet(
				D3DXVECTOR3(0.0f, 1.0f, 3000.0f),
				D3DXVECTOR3(1250.0f, 0.0f, 5000.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				D3DXVECTOR2(1.0f, 1.0f));
		}
	}

	// �O�̕�
	{
		// �t�B�[���h�̐���
		CObj3dWall* pWall = CObj3dWall::Create(CObj3dWall::TEX_BLOCKADE_WALL_000);

		if (pWall != nullptr)
		{
			pWall->InitSet(
				D3DXVECTOR3(0.0f, 0.0f, 8000.0f),
				D3DXVECTOR3(1300.0f, 100.0f, 0.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
				D3DXVECTOR2(1.0f, 1.0f));
		}
	}

	// ���̕�
	{
		// �t�B�[���h�̐���
		CObj3dWall* pWall = CObj3dWall::Create(CObj3dWall::TEX_BLOCKADE_WALL_000);

		if (pWall != nullptr)
		{
			pWall->InitSet(
				D3DXVECTOR3(0.0f, 0.0f, -1000.0f),
				D3DXVECTOR3(1300.0f, 100.0f, 0.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
				D3DXVECTOR2(1.0f, 1.0f));
		}
	}

	// �E�̕�
	{
		// �t�B�[���h�̐���
		CObj3dWall* pWall = CObj3dWall::Create(CObj3dWall::TEX_BLOCKADE_WALL_000);

		if (pWall != nullptr)
		{
			pWall->InitSet(
				D3DXVECTOR3(1300.0f, 0.0f, 3000.0f),
				D3DXVECTOR3(0.0f, 100.0f, 6000.0f),
				D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
				D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f),
				D3DXVECTOR2(1.0f, 1.0f));
		}
	}

	// ���̕�
	{
		// �t�B�[���h�̐���
		CObj3dWall* pWall = CObj3dWall::Create(CObj3dWall::TEX_BLOCKADE_WALL_000);

		if (pWall != nullptr)
		{
			pWall->InitSet(
				D3DXVECTOR3(-1300.0f, 0.0f, 3000.0f),
				D3DXVECTOR3(0.0f, 100.0f, 6000.0f),
				D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
				D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f),
				D3DXVECTOR2(1.0f, 1.0f));
		}
	}

	CMapManager::GameLoad();

	for (int nCntSpnWall = 0; nCntSpnWall < CPhaseManager::TYPE_PHASE_COMP; nCntSpnWall++)
	{
		// �o���ǂ̐���
		CSpwanWall* pSpwanWall = CSpwanWall::Create();

		if (pSpwanWall != nullptr)
		{
			// �t�F�[�Y�ݒ菈��
			pSpwanWall->SetTypePhase((CPhaseManager::TYPE_PHASE)nCntSpnWall);

			// �ݒ菈��
			pSpwanWall->InitSet(
				SPWAN_WALL_POS[nCntSpnWall],
				D3DXVECTOR3(1300.0f, 25.0f, 0.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				D3DXVECTOR2(5.0f, 1.0f));
		}
	}

	if (m_infoPoint.pPlayer == NULL)
	{
		// �v���C���[�̐���
		m_infoPoint.pPlayer = CPlayer::Create(
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// �ʒu
			D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),	// ����
			CModel::MODEL_TYPE_PLAYER,			// ���f��
			CMotion::MOTION_TYPE_PLAYER);		// ���[�V����
	}

	// �Q�[���̍Đ�
	pSound->Play(CSound::LABEL_BGM_GAME);

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �Q�[����ʂ̏I������
//-------------------------------------
void CGame::Uninit(void)
{
	if (m_infoPoint.pPause != NULL)
	{
		m_infoPoint.pPause->Uninit();

		delete m_infoPoint.pPause;
		m_infoPoint.pPause = NULL;
	}

	if (m_infoPoint.pPhaseManager != NULL)
	{
		m_infoPoint.pPhaseManager->Uninit();

		delete m_infoPoint.pPhaseManager;
		m_infoPoint.pPhaseManager = NULL;
	}

	if (m_infoPoint.pSkyBox != NULL)
	{
		m_infoPoint.pSkyBox->Uninit();
		m_infoPoint.pSkyBox = NULL;
	}

	for (int nCnt = 0; nCnt < GAME::FIELD_NUM; nCnt++)
	{
		if (m_infoPoint.apField[nCnt] != NULL)
		{
			m_infoPoint.apField[nCnt]->Uninit();
			m_infoPoint.apField[nCnt] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < GAME::WALL_NUM; nCnt++)
	{
		if (m_infoPoint.apWall[nCnt] != NULL)
		{
			m_infoPoint.apWall[nCnt]->Uninit();
			m_infoPoint.apWall[nCnt] = NULL;
		}
	}

	if (m_infoPoint.pPlayer != NULL)
	{
		m_infoPoint.pPlayer->Uninit();
		m_infoPoint.pPlayer = NULL;
	}

	// �I�u�W�F�N�g�̑S�J������
	CObject::ReleaseAll();
}

//-------------------------------------
//- �Q�[����ʂ̍X�V����
//-------------------------------------
void CGame::Update(void)
{
	// �L�[�{�[�h�̏��擾
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

	// ���̑J�ڃ{�^���i���񂽁[�j
	if (pInputKeyboard->GetTrigger(DIK_P) != NULL)
	{
		if (m_gameState == GAME_STATE_NONE)
		{
			m_infoPoint.pPause = CPause::Create();

			// �|�[�Y���
			m_gameState = GAME_STATE_PAUSE;
		}
		else if (m_gameState == GAME_STATE_PAUSE)
		{
			if (m_infoPoint.pPause != NULL)
			{
				m_infoPoint.pPause->Uninit();
				delete m_infoPoint.pPause;

				m_infoPoint.pPause = NULL;
			}

			// �Q�[�����
			m_gameState = GAME_STATE_NONE;
		}
	}

	if (m_gameState == GAME_STATE_NONE)
	{

	}
	else if (m_gameState == GAME_STATE_PAUSE)
	{
		if (m_infoPoint.pPause != NULL)
		{
			// �|�[�Y�̍X�V����
			m_infoPoint.pPause->Update();

			if (m_infoPoint.pPause->GetOk() == true)
			{
				switch (m_infoPoint.pPause->GetTypeSelect())
				{
				case CPause::TYPE_SELECT_GAME:

					break;

				case CPause::TYPE_SELECT_RETRY:

					// �Q�[�����[�h
					CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_GAME);

					break;

				case CPause::TYPE_SELECT_TITLE:

					// �Q�[�����[�h
					CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_TITEL);

					break;
				}

				// �|�[�Y�̊J������
				m_infoPoint.pPause->Uninit();
				delete m_infoPoint.pPause;
				m_infoPoint.pPause = NULL;

				// �Q�[�����
				m_gameState = GAME_STATE_NONE;
			}
		}
	}
}

//-------------------------------------
//- �Q�[����ʂ̕`�揈��
//-------------------------------------
void CGame::Draw(void)
{

}