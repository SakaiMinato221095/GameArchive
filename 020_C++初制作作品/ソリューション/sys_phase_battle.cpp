
//-===============================================
//-
//-	戦闘フェーズの処理[sys_pase_battle.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "sys_phase_battle.h"

#include "game.h"
#include "manager_object.h"
#include "mgr_sys_obj.h"
#include "timer.h"

#include "Input.h"

#include "camera.h"

#include "player_battle.h"

#include "life.h"

#include "obj_2d_none.h"
#include "effect_2d.h"

#include "file_obj_none.h"
#include "file_evt_obj.h"
#include "file_emy_nor.h"

#include "ui_mission.h"

#include "state_game.h"
#include "state_battle.h"

#include "enemy_boss.h"

#include "gate.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	静的変数宣言
//-======================================

CLife *CSysPhaseBattle::m_pLife = NULL;

CPlayer *CSysPhaseBattle::m_pPlayerBattle = NULL;

CManagerObject *CSysPhaseBattle::m_pManagerObject = NULL;

CUiMission *CSysPhaseBattle::m_pUiMission = NULL;

CObj2dNone *CSysPhaseBattle::m_pObj2dNone = NULL;

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CSysPhaseBattle::CSysPhaseBattle()
{
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CSysPhaseBattle::~CSysPhaseBattle()
{
}

//-------------------------------------
//- 戦闘フェーズの初期化処理
//-------------------------------------
HRESULT CSysPhaseBattle::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// システムオブジェクト管理の取得処理
	CMgrSysObj *pMgrSysObj = CGame::GetMgrSysObj();

	//  システムオブジェクト管理の取得の有無を判定
	if (pMgrSysObj == NULL)
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

	// 数値系の再設定
	pMgrSysObj->SetNumber();

	// カメラを追尾視点に変更
	pCamera->SetMode(CCamera::MODE_FOLLOWING);

	// 体力の初期化
	{
		// 体力の有無を判定
		if (m_pLife != NULL)
		{
			// 処理を抜ける
			return E_FAIL;
		}

		// 体力の生成
		m_pLife = CLife::Create();

		// 体力の初期化処理
		if (m_pLife == NULL)
		{// 失敗時

			// 失敗メッセージ
			MessageBox(hWnd, "体力の生成", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}
	}

	// 戦闘プレイヤーの初期化
	{
		// 戦闘プレイヤーの有無を判定
		if (m_pPlayerBattle != NULL)
		{
			// 処理を抜ける
			return E_FAIL;
		}

		// 戦闘プレイヤーの生成
		m_pPlayerBattle = CPlayerBattle::Create(
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),			// 位置
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),			// 向き
			CObjectModel::MODEL_TYPE_PLAYER_BATTLE,	// モデル
			CMotion::MOTION_TYPE_PLAYER_BATTLE);	// モーション

		// 戦闘プレイヤーの初期化処理
		if (m_pPlayerBattle == NULL)
		{// 失敗時

		 // 失敗メッセージ
			MessageBox(hWnd, "戦闘プレイヤーの生成", "初期処理失敗！", MB_ICONWARNING);

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
			m_pUiMission = CUiMission::Create(CUiMission::TEX_BATTLE_NORMAL);

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
				D3DXVECTOR3(SCREEN_WIDTH * 0.925f, SCREEN_HEIGHT * 0.3f, 0.0f),
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

	// 効果なしオブジェクト読み込み設定処理
	CFileObjNone::Load(CFileObjNone::TXT_NORMAL_000);

	// イベントオブジェクト読み込み設定処理
	CFileEvtObj::Load(CFileEvtObj::TXT_NORMAL_000);

	// 通常敵の読み込み設定処理
	CFileEmyNor::Load(CFileEmyNor::TXT_NORMAL_000);

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
//- 戦闘フェーズの終了処理
//-------------------------------------
void CSysPhaseBattle::Uninit(void)
{
	// システムオブジェクト管理の取得処理
	CMgrSysObj *pMgrSysObj = CGame::GetMgrSysObj();

	//  システムオブジェクト管理の取得の有無を判定
	if (pMgrSysObj != NULL)
	{
		// 数字のポインタ初期化処理
		pMgrSysObj->NullAllNumber();
	}

	// 体力の有無を判定
	if (m_pLife != NULL)
	{
		// 体力の終了処理
		m_pLife->Uninit();

		// 体力のポインタ初期化処理
		delete m_pLife;
		m_pLife = NULL;
	}

	// 戦闘プレイヤーの有無を判定
	if (m_pPlayerBattle != NULL)
	{
		// 戦闘プレイヤーの終了処理
		m_pPlayerBattle->Uninit();

		// 戦闘プレイヤーのポインタ初期化処理
		m_pPlayerBattle = NULL;
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
//- 戦闘フェーズの更新処理
//-------------------------------------
void CSysPhaseBattle::Update(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

		// 処理を抜ける
		return;
	}

	// ゲームステータスのポインタを宣言
	CStateGame *pStateGame = CGame::GetStateGame();

	// ゲームステータスの情報取得の成功を判定
	if (pStateGame == NULL)
	{// 失敗時

		// 処理を抜ける
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

	// ボスのポインタを取得
	CEnemyBoss *pEnemyBoss = m_pManagerObject->GetEnemyBoss();

	// 変数宣言（ゲームステータスの情報取得）
	int nEnemyDeathCut = pStateGame->m_nDataEnemyDeathCut.Get();		// 敵の死亡数カウント
	int nEnemyDeathTarget = pStateGame->m_nDataEnemyDeathTarget.Get();	// 敵の目標死亡数カウント

	// ボスの出現判定
	if (nEnemyDeathCut >= nEnemyDeathTarget && pEnemyBoss == NULL && pStateGame->GetEndState() == CStateGame::END_STATE_NONE)
	{
		// 目標UIの切り替え
		m_pUiMission->BindTexture(m_pUiMission->GetTexNldx(CUiMission::TEX_BATTLE_BOSS));

		// ボスの生成処理
		CEnemyBoss *pEnemyBoss = CEnemyBoss::Create(CEnemy::MODEL_TYPE_ALIEN_001);

		// ボスの生成の有無を判定
		if (pEnemyBoss != NULL)
		{
			m_pManagerObject->SetEnemyBoss(pEnemyBoss);
		}
	}

	// 体力の有無を判定
	if (m_pLife != NULL)
	{
		// 体力の更新処理
		m_pLife->Update();
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
	}

	// 情報更新（エフェクト2D）
	m_dataEffectCut.Set(nEffectCut);

#if _DEBUG
	//　入力の判定 if（Cキーのトリガー）
	if (pInputKeyboard->GetTrigger(DIK_C) != NULL)
	{
		CGame::SetPhase(TYPE::TYPE_SEARCH);
	}
#endif

	// フェーズ状態の判定
	if (CSysGamePhase::GetType() != CSysGamePhase::GetTypeNext())
	{
		// フェーズの切り替え
		CGame::SetPhase(CSysGamePhase::GetTypeNext());

		return;
	}
}

//-------------------------------------
//- 戦闘フェーズの描画処理
//-------------------------------------
void CSysPhaseBattle::Draw(void)
{

}

//-------------------------------------
//-	戦闘プレイヤーの情報を取得
//-------------------------------------
CPlayer *CSysPhaseBattle::GetPlayer(void)
{
	// 探索プレイヤーの情報を返す
	return m_pPlayerBattle;
}

//-------------------------------------
//- 戦闘フェーズのオブジェクト管理の取得処理
//-------------------------------------
CManagerObject * CSysPhaseBattle::GetManagerObject(void)
{
	return m_pManagerObject;
}

//-------------------------------------
//- 戦闘フェーズの体力の取得処理
//-------------------------------------
CLife * CSysPhaseBattle::GetLife(void)
{
	return m_pLife;
}

//-------------------------------------
//-	戦闘フェーズの目的UIの情報を取得
//-------------------------------------
CUiMission *CSysPhaseBattle::GetUiMission(void)
{
	// 目的UIの情報を返す
	return m_pUiMission;
}

//-------------------------------------
//-	効果なし2Dの情報を取得
//-------------------------------------
CObj2dNone * CSysPhaseBattle::GetObj2DNone(void)
{
	return m_pObj2dNone;
}
