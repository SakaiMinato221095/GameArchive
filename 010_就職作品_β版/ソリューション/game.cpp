
//================================================
//=
//=	ゲーム画面処理[game.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
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
//=	マクロ定義
//=======================================

const D3DXVECTOR3 SPWAN_WALL_POS[CPhaseManager::TYPE_PHASE_COMP] =
{
	D3DXVECTOR3(0.0f, 100.0f, 500.0f),
	D3DXVECTOR3(0.0f, 100.0f, 3000.0f),
	D3DXVECTOR3(0.0f, 100.0f, 5500.0f),
};

//=======================================
//=	静的変数宣言
//=======================================

CGame::InfoPoint CGame::m_infoPoint = {};

//-------------------------------------
//-	ゲーム画面のコンストラクタ
//-------------------------------------
CGame::CGame()
{
	m_gameState = (GAME_STATE)0;
}

//-------------------------------------
//-	ゲーム画面のデストラクタ
//-------------------------------------
CGame::~CGame()
{

}

//-------------------------------------
//- ゲーム画面の初期化処理
//-------------------------------------
HRESULT CGame::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{		
	// 情報取得の設定処理
	CCamera *pCamera = CManager::GetInstance()->GetCamera();
	CSound* pSound = CManager::GetInstance()->GetSound();

	// 取得の有無判定
	if (pCamera == NULL ||
		pSound == NULL)
	{
		return E_FAIL;
	}

	// カメラの設定処理
	pCamera->SetMode(CCamera::MODE_FOLLOWING);

	if (m_infoPoint.pPhaseManager == nullptr)
	{
		// フェーズ管理の生成
		m_infoPoint.pPhaseManager = CPhaseManager::Create();

		if (m_infoPoint.pPhaseManager == nullptr)
		{// 失敗時

			return E_FAIL;
		}
	}

	if (m_infoPoint.pSkyBox == nullptr)
	{
		// スカイボックスの生成
		m_infoPoint.pSkyBox = CSkybox::Create(
			CSkybox::MODEL_SKYBOX_000,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	{
		// フィールドの生成
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
		// フィールドの生成
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

	// 前の壁
	{
		// フィールドの生成
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

	// 後ろの壁
	{
		// フィールドの生成
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

	// 右の壁
	{
		// フィールドの生成
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

	// 左の壁
	{
		// フィールドの生成
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
		// 出現壁の生成
		CSpwanWall* pSpwanWall = CSpwanWall::Create();

		if (pSpwanWall != nullptr)
		{
			// フェーズ設定処理
			pSpwanWall->SetTypePhase((CPhaseManager::TYPE_PHASE)nCntSpnWall);

			// 設定処理
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
		// プレイヤーの生成
		m_infoPoint.pPlayer = CPlayer::Create(
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 位置
			D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),	// 向き
			CModel::MODEL_TYPE_PLAYER,			// モデル
			CMotion::MOTION_TYPE_PLAYER);		// モーション
	}

	// ゲームの再生
	pSound->Play(CSound::LABEL_BGM_GAME);

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- ゲーム画面の終了処理
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

	// オブジェクトの全開放処理
	CObject::ReleaseAll();
}

//-------------------------------------
//- ゲーム画面の更新処理
//-------------------------------------
void CGame::Update(void)
{
	// キーボードの情報取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

		// 更新処理を抜ける
		return;
	}

	// X入力のポインタを宣言
	CXInput *pXInput = CManager::GetInstance()->GetXInput();

	// X入力の情報取得の成功を判定
	if (pXInput == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 仮の遷移ボタン（えんたー）
	if (pInputKeyboard->GetTrigger(DIK_P) != NULL)
	{
		if (m_gameState == GAME_STATE_NONE)
		{
			m_infoPoint.pPause = CPause::Create();

			// ポーズ状態
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

			// ゲーム状態
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
			// ポーズの更新処理
			m_infoPoint.pPause->Update();

			if (m_infoPoint.pPause->GetOk() == true)
			{
				switch (m_infoPoint.pPause->GetTypeSelect())
				{
				case CPause::TYPE_SELECT_GAME:

					break;

				case CPause::TYPE_SELECT_RETRY:

					// ゲームモード
					CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_GAME);

					break;

				case CPause::TYPE_SELECT_TITLE:

					// ゲームモード
					CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_TITEL);

					break;
				}

				// ポーズの開放処理
				m_infoPoint.pPause->Uninit();
				delete m_infoPoint.pPause;
				m_infoPoint.pPause = NULL;

				// ゲーム状態
				m_gameState = GAME_STATE_NONE;
			}
		}
	}
}

//-------------------------------------
//- ゲーム画面の描画処理
//-------------------------------------
void CGame::Draw(void)
{

}