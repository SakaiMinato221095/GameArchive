
//-===============================================
//-
//-	探索フェーズ処理[sys_game_search.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "sys_phase_search.h"

#include "game.h"
#include "manager_object.h"
#include "mgr_sys_obj.h"
#include "timer.h"
#include "time_stop.h"

#include "ui_mission.h"
#include "ui_start_text.h"

#include "Input.h"

#include "camera.h"

#include "player_search.h"

#include "qte_timing.h"

#include "garbage_collect.h"

#include "gate.h"

#include "obj_2d_none.h"
#include "effect_2d.h"

#include "state_game.h"
#include "state_battle.h"

#include "file_obj_none.h"
#include "file_evt_obj.h"
#include "file_garbage.h"
#include "file_garbage_collect.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	静的変数宣言
//-======================================

CPlayer *CSysPhaseSearch::m_pPlayerSearch = NULL;
CManagerObject *CSysPhaseSearch::m_pManagerObject = NULL;
CUiMission *CSysPhaseSearch::m_pUiMission = NULL;
CUiStartText *CSysPhaseSearch::m_apUiStartText[STATE_TEXT_MAX] = {};
CQte *CSysPhaseSearch::m_pQte = NULL;

CObj2dNone *CSysPhaseSearch::m_pObj2dNone = NULL;

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CSysPhaseSearch::CSysPhaseSearch()
{
	bState = false;
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CSysPhaseSearch::~CSysPhaseSearch()
{

}

//-------------------------------------
//- 探索フェーズの初期化処理
//-------------------------------------
HRESULT CSysPhaseSearch::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// システムオブジェクト管理の取得処理
	CMgrSysObj *pMgrSysObj = CGame::GetMgrSysObj();

	//  システムオブジェクト管理の取得の有無を判定
	if (pMgrSysObj == NULL)
	{
		// 生成処理を抜ける
		return E_FAIL;
	}

	// 時間取得処理
	CTimer *pTimer = CGame::GetMgrSysObj()->GetTimer();

	// 時間の取得の有無を判定
	if (pTimer == NULL)
	{
		// 生成処理を抜ける
		return E_FAIL;
	}

	// カメラの取得処理
	CCamera *pCamera = CManager::GetCamera();

	// カメラの取得成功の有無を判定
	if (pCamera == NULL)
	{
		// 生成処理を抜ける
		return E_FAIL;
	}

	// カメラを追尾視点に変更
	pCamera->SetMode(CCamera::MODE_FOLLOWING);

	// 探索プレイヤーの生成成功の有無を判定
	if (m_pPlayerSearch != NULL)
	{
		return E_FAIL;
	}


	// 数値系の設定
	pMgrSysObj->SetNumber();

	// 探索プレイヤーの初期化
	{
		// 探索プレイヤーの有無を判定
		if (m_pPlayerSearch != NULL)
		{
			// 処理を抜ける
			return E_FAIL;
		}

		// 探索プレイヤーの生成
		m_pPlayerSearch = CPlayerSearch::Create(
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),			// 位置
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),			// 向き
			CObjectModel::MODEL_TYPE_PLAYER_SEARCH,	// モデル
			CMotion::MOTION_TYPE_PLAYER_SEARCH);	// モーション

		// 探索プレイヤーの初期化処理
		if (m_pPlayerSearch == NULL)
		{// 失敗時

			// 失敗メッセージ
			MessageBox(hWnd, "探索プレイヤーの生成", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}
	}

	// オブジェクト管理の初期化
	{
		// オブジェクト管理の有無を判定
		if (m_pManagerObject == NULL)
		{
			// オブジェクト管理の生成
			m_pManagerObject = DBG_NEW CManagerObject;

			// オブジェクト管理の初期化処理
			if (FAILED(m_pManagerObject->Init(hInstance, hWnd, bWindow)))
			{// 失敗時

				// 失敗メッセージ
				MessageBox(hWnd, "オブジェクト管理の生成", "初期処理失敗！", MB_ICONWARNING);

				// 初期化を抜ける
				return E_FAIL;
			}
		}
		else
		{// ゴミが入っているとき

			// 初期化を抜ける
			return E_FAIL;
		}
	}

	// 目的UIの設定処理
	{
		// 目的UIの有無を判定
		if (m_pUiMission == NULL)
		{
			// 目的UIの生成
			m_pUiMission = CUiMission::Create(CUiMission::TEX_SEARCH);

			// 目的UIの初期化処理
			if (m_pUiMission == NULL)
			{// 失敗時

				// 失敗メッセージ
				MessageBox(hWnd, "目的UIの初期化", "初期処理失敗！", MB_ICONWARNING);

				// 初期化を抜ける
				return E_FAIL;
			}
		}
		else
		{// ゴミが入っているとき

			// 失敗メッセージ
			MessageBox(hWnd, "目的UIの初期化", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}
	}

	// 効果なしオブジェクトの設定処理
	{
		// 効果なしオブジェクトの有無を判定
		if (m_pObj2dNone == NULL)
		{
			// 初期効果なしオブジェクトの生成
			m_pObj2dNone = CObj2dNone::Create(CObj2dNone::TEX_ELEM_WINDOW);

			// 初期効果なしオブジェクトの初期化処理
			if (m_pObj2dNone == NULL)
			{// 失敗時

			 // 失敗メッセージ
				MessageBox(hWnd, "効果なしオブジェクトの初期化", "初期処理失敗！", MB_ICONWARNING);

				// 初期化を抜ける
				return E_FAIL;
			}

			m_pObj2dNone->Set(
				D3DXVECTOR3(SCREEN_WIDTH * 0.925f, SCREEN_HEIGHT * 0.2f, 0.0f),
				D3DXVECTOR3(50.0f, 50.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{// ゴミが入っているとき

		 // 失敗メッセージ
			MessageBox(hWnd, "効果なしオブジェクトの初期化", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}
	}

	// 時間停止の情報取得
	CTimeStop *pTimeStop = CManager::GetManagerTime();

	// 時間停止の情報取得の成功を判定
	if (pTimeStop == NULL)
	{// 失敗時

	 // 更新処理を抜ける
		return E_FAIL;
	}

	// ゲームステータスのポインタを宣言
	CStateGame *pStateGame = CGame::GetStateGame();

	// ゲームステータスの情報取得の成功を判定
	if (pStateGame == NULL)
	{// 失敗時

		// 処理を抜ける
		return E_FAIL;
	}

	if (pStateGame->m_bDataStart.Get() == false)
	{
		// 開始の時間停止
		pTimeStop->Set(0.0f, 180);

		// 開始の設定
		bState = true;
	}

	// 効果なしオブジェクト読み込み設定処理
	CFileObjNone::Load(CFileObjNone::TXT_NORMAL_000);

	// イベントオブジェクト読み込み設定処理
	CFileEvtObj::Load(CFileEvtObj::TXT_NORMAL_000);

	// ゴミの設置
	CFileGarbage::Locate();

	// ゲートの生成処理	
	CGate *pGate = CGate::Create(CGate::MODEL_GATE_000);

	if (pGate != NULL)
	{
		// 位置を設定
		pGate->m_dataPos.Set(D3DXVECTOR3(0.0f, 0.0f, 500.0f));

		// ゲートの設定処理
		CManagerObject::SetGate(pGate);
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 探索フェーズの終了処理
//-------------------------------------
void CSysPhaseSearch::Uninit(void)
{
	// システムオブジェクト管理の取得処理
	CMgrSysObj *pMgrSysObj = CGame::GetMgrSysObj();

	// なくなったゴミを確認
	CFileGarbage::ObjCheck();

	//  システムオブジェクト管理の取得の有無を判定
	if (pMgrSysObj != NULL)
	{
		// 数字のポインタ初期化処理
		pMgrSysObj->NullAllNumber();
	}

	// 探索プレイヤーの有無を判定
	if (m_pPlayerSearch != NULL)
	{
		// 探索プレイヤーの終了処理
		m_pPlayerSearch->Uninit();

		// 探索プレイヤーのポインタ初期化処理
		m_pPlayerSearch = NULL;
	}

	// オブジェクト管理の有無を判定
	if (m_pManagerObject != NULL)
	{
		// オブジェクトの終了
		m_pManagerObject->Uninit();

		// オブジェクト管理の開放処理
		delete m_pManagerObject;
		m_pManagerObject = NULL;
	}

	// 目的UIの有無を判定
	if (m_pUiMission != NULL)
	{
		// 目的UIの終了処理
		m_pUiMission->Uninit();

		// 目的UIのポインタの初期
		m_pUiMission = NULL;
	}

	for (int nCount = 0; nCount < STATE_TEXT_MAX; nCount++)
	{
		// スタートテキストの破棄
		if (m_apUiStartText[nCount] != NULL)
		{
			// スタートテキストの終了処理
			m_apUiStartText[nCount] = NULL;
		}
	}

	// クイックタイムイベントの有無を判定
	if (m_pQte != NULL)
	{
		// クイックタイムイベントの終了処理
		m_pQte->Uninit();

		// クイックタイムイベントのポインタの初期
		m_pQte = NULL;
	}

	// ゲームステータスの破棄
	if (m_pObj2dNone != NULL)
	{
		// ゲームステータスの終了処理
		m_pObj2dNone = NULL;
	}

	// オブジェクトの全開放処理
	CObject::ReleaseAll();
}

//-------------------------------------
//- 探索フェーズの更新処理
//-------------------------------------
void CSysPhaseSearch::Update(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

		// 処理を抜ける
		return;
	}

	// 時間停止の情報取得
	CTimeStop *pTimeStop = CManager::GetManagerTime();

	// 時間停止の情報取得の成功を判定
	if (pTimeStop == NULL)
	{// 失敗時

	 // 更新処理を抜ける
		return;
	}

	// フェーズ状態の判定
	if (CSysGamePhase::GetType() != CSysGamePhase::GetTypeNext())
	{
		// フェーズの切り替え
		CGame::SetPhase(CSysGamePhase::GetTypeNext());

		return;
	}

	// ゲームステータスのポインタを宣言
	CStateBattle *pStateBattle = CGame::GetStateBattle();

	// ゲームステータスの情報取得の成功を判定
	if (pStateBattle == NULL)
	{// 失敗時

	 // 処理を抜ける
		return;
	}

	// スタートテキストの設定処理
	if (bState == true)
	{
		// スタートテキストの有無を判定
		if (m_apUiStartText[STATE_TEXT_000] == NULL)
		{
			// スタートテキストの生成
			m_apUiStartText[STATE_TEXT_000] = CUiStartText::Create(CUiStartText::TEX_START_000);

			// スタートテキストの有無の判定
			if (m_apUiStartText[STATE_TEXT_000] == NULL)
			{// 失敗時

			 // 初期化を抜ける
				return;
			}

			// スタートテキストの設定処理
			m_apUiStartText[STATE_TEXT_000]->Set(
				D3DXVECTOR3(SCREEN_WIDTH * -0.1f,SCREEN_HEIGHT * 0.4f,0.0f),
				D3DXVECTOR3(SCREEN_WIDTH *  0.35f,SCREEN_HEIGHT * 0.4f,0.0f),
				D3DXVECTOR3(250.0f,50.0f,0.0f),
				D3DXVECTOR3(15.0f,0.0f,0.0f));
		}
	}

	if (pTimeStop->m_nDataTimeCount.Get() >= 60)
	{
		// スタートテキストの設定処理
		{
			// スタートテキストの有無を判定
			if (m_apUiStartText[STATE_TEXT_001] == NULL)
			{
				// スタートテキストの生成
				m_apUiStartText[STATE_TEXT_001] = CUiStartText::Create(CUiStartText::TEX_START_001);

				// スタートテキストの有無の判定
				if (m_apUiStartText[STATE_TEXT_001] == NULL)
				{// 失敗時

				 // 初期化を抜ける
					return;
				}

				// スタートテキストの設定処理
				m_apUiStartText[STATE_TEXT_001]->Set(
					D3DXVECTOR3(SCREEN_WIDTH *  1.1f, SCREEN_HEIGHT * 0.6f, 0.0f),
					D3DXVECTOR3(SCREEN_WIDTH *  0.6f, SCREEN_HEIGHT * 0.6f, 0.0f),
					D3DXVECTOR3(350.0f, 50.0f, 0.0f),
					D3DXVECTOR3(-15.0f, 0.0f, 0.0f));
			}
		}
	}

	if (pTimeStop->m_nDataTimeCount.Get() == pTimeStop->m_nDataTimeCountMax.Get() &&
		bState == true)
	{
		// スタートを終了状態
		bState = false;

		// ゲームステータスのポインタを宣言
		CStateGame *pStateGame = CGame::GetStateGame();

		// ゲームステータスの情報取得の成功を判定
		if (pStateGame == NULL)
		{// 失敗時

		 // 処理を抜ける
			return;
		}
		
		pStateGame->m_bDataStart.Set(true);

		for (int nCount = 0; nCount < STATE_TEXT_MAX; nCount++)
		{
			// スタートテキストの破棄
			if (m_apUiStartText[nCount] != NULL)
			{
				// スタートテキストの終了処理
				m_apUiStartText[nCount]->Uninit();
				m_apUiStartText[nCount] = NULL;
			}
		}
	}

	if (m_pQte != NULL)
	{
		// クイックタイムイベントの更新処理
		m_pQte->Update();
	}

	// 情報取得
	int nEffectCut = m_dataEffectCut.Get();				// エフェクトカウント

	// 情報取得（効果なし2D）
	D3DXVECTOR3 pos = m_pObj2dNone->m_dataPos.Get();	// 位置

	// 情報取得（戦闘ステータス）
	CStateBattle::ELEM_TYPE elemType = pStateBattle->GetElemType();	// 属性種類
	int nElemRank = pStateBattle->m_aDataElemRank[elemType].Get();	// 属性ランク

	// エフェクトカウントの判定
	if (nEffectCut > 0)
	{
		// エフェクトカウントの減算
		nEffectCut--;
	}
	else
	{
		// 変数宣言
		D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// サイズ
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量
		D3DXCOLOR color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// 色
		int nLife = 0;

		if (nElemRank == 0)
		{
			size = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
			move = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
			nLife = 30;
		}
		else if (nElemRank == 1)
		{
			size = D3DXVECTOR3(20.0f, 20.0f, 0.0f);
			move = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
			nLife = 45;
		}
		else if (nElemRank == 2)
		{
			size = D3DXVECTOR3(30.0f, 30.0f, 0.0f);
			move = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
			nLife = 60;
		}
		else if (nElemRank == 3)
		{
			size = D3DXVECTOR3(45.0f, 45.0f, 0.0f);
			move = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
			nLife = 60;
		}

		switch (elemType)
		{
		case CStateBattle::ELEM_TYPE_NORMAL:

			color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			break;

		case CStateBattle::ELEM_TYPE_CHAOS:

			color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

			break;
		}

		// 2Dエフェクトの生成
		CEffect2d *pEffect2d = CEffect2d::Create(CEffect2d::TEX_NORMAL_000);

		// 2Dエフェクトの設定
		pEffect2d->Set(
			D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z),
			size,
			D3DXVECTOR3(0.0f, -1.0f, 0.0f),
			color,
			nLife,
			false);

		nEffectCut = 1;
	}

	// 情報更新（エフェクト2D）
	m_dataEffectCut.Set(nEffectCut);

#if _DEBUG
	//　入力の判定 if（Cキーのトリガー）
	if (pInputKeyboard->GetTrigger(DIK_C) != NULL)
	{
		CGame::SetPhase(TYPE::TYPE_SHOP);
	}
#endif
}

//-------------------------------------
//- 探索フェーズの描画処理
//-------------------------------------
void CSysPhaseSearch::Draw(void)
{

}

//-------------------------------------
//- クイックタイムイベントの設定処理
//-------------------------------------
void CSysPhaseSearch::SetQte(CQte::TYPE_QTE typeQte)
{
	// クイックタイムイベントの有無を判定
	if (m_pQte == NULL)
	{
		switch (typeQte)
		{
		case CQte::TYPE_QTE_TIMING:

			// クイックタイムイベントの生成
			m_pQte = CQteTiming::Create();

			break;
		}

		// クイックタイムイベントの有無っを判定
		if (m_pQte == NULL)
		{// 失敗時

			// 初期化を抜ける
			return;
		}
	}
}

//-------------------------------------
//-	クイックタイムイベントの初期化処理を取得
//-------------------------------------
void CSysPhaseSearch::ReleaseQte(void)
{
	// クイックタイムイベントの終了処理
	m_pQte->Uninit();

	// クイックタイムイベントの開放処理
	delete m_pQte;
	m_pQte = NULL;
}

//-------------------------------------
//-	探索プレイヤーの情報を取得
//-------------------------------------
CPlayer *CSysPhaseSearch::GetPlayer(void)
{
	// 探索プレイヤーの情報を返す
	return m_pPlayerSearch;
}

//-------------------------------------
//- 探索フェーズのオブジェクト管理の取得処理
//-------------------------------------
CManagerObject *CSysPhaseSearch::GetManagerObject(void)
{
	// オブジェクト管理の情報を返す
	return m_pManagerObject;
}

//-------------------------------------
//-	探索フェーズの目的UIの情報を取得
//-------------------------------------
CUiMission *CSysPhaseSearch::GetUiMission(void)
{
	// 目的UIの情報を返す
	return m_pUiMission;
}

//-------------------------------------
//-	効果なし2Dの情報を取得
//-------------------------------------
CObj2dNone * CSysPhaseSearch::GetObj2DNone(void)
{
	return m_pObj2dNone;
}
