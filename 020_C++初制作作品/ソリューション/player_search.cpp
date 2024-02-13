
//-===============================================
//-
//-	探索プレイヤー処理[player_search.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "player_search.h"

#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "time_stop.h"
#include "sys_game_phase.h"
#include "sys_phase_search.h"
#include "manager_object.h"

#include "Input.h"
#include "xinput.h"
#include "sound.h"
#include "debugproc.h"

#include "mgr_sys_obj.h"
#include "score.h"

#include "event_object.h"
#include "garbage.h"
#include "garbage_collect.h"

#include "gate.h"

#include "effect_object.h"

#include "ui_opr_desc.h"
#include "ui_text_desc.h"

#include "hit.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CPlayerSearch::CPlayerSearch()
{
	// 値をクリア
	m_stateType = STATE_TYPE_NEUTRAL;
	m_stateTypeOld = m_stateType;

	m_pUiOprDesc = NULL;
	m_pUiTextDesc = NULL;
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CPlayerSearch::~CPlayerSearch()
{

}

//-------------------------------------
//- 探索プレイヤーの初期化処理
//-------------------------------------
HRESULT CPlayerSearch::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CObjectModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax)
{
	// プレイヤーの設定処理
	Set(pos,rot);

	// プレイヤーの初期化処理
	CPlayer::Init(modelType, motionType,nStateMax);

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 探索プレイヤーの終了処理
//-------------------------------------
void CPlayerSearch::Uninit(void)
{
	if (m_pUiOprDesc != NULL)
	{
		// 説明UIの終了処理
		m_pUiOprDesc->Uninit();
		m_pUiOprDesc = NULL;
	}

	if (m_pUiTextDesc != NULL)
	{
		// 説明文UIの終了処理
		m_pUiTextDesc->Uninit();
		m_pUiTextDesc = NULL;
	}

	// プレイヤーの終了処理
	CPlayer::Uninit();
}

//-------------------------------------
//- 探索プレイヤーの更新処理
//-------------------------------------
void CPlayerSearch::Update(void)
{
	// スコアの情報取得処理
	CScore *pScore = CGame::GetMgrSysObj()->GetScore();

	// スコアの情報取得の成功を判定
	if (pScore == NULL)
	{// 失敗時

	 // 処理を抜ける
		return;
	}

	// 情報設定（前回の情報）
	m_dataPosOld.Set(m_dataPos.Get());	// 位置
	m_stateTypeOld = m_stateType;		// 状態

	// ゲームモードの判定
	if (CGame::GetSysGamePhase()->GetType() == CSysGamePhase::TYPE_SEARCH)
	{
		if (m_stateType != STATE_TYPE_TOUCH &&
			m_stateType != STATE_TYPE_EAT)
		{
			// プレイヤーの更新処理
  			CPlayer::Update();
		}

		// イベントの更新処理
		UpdateEvent();

		// モーションの更新処理
		UpdateMotion();
	}
}

//-------------------------------------
//- 探索プレイヤーの描画処理
//-------------------------------------
void CPlayerSearch::Draw(void)
{
	// プレイヤーの描画処理
	CPlayer::Draw();
}

//-------------------------------------
//- 探索プレイヤーの生成処理
//-------------------------------------
CPlayerSearch * CPlayerSearch::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CObjectModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType)
{
	// 探索プレイヤーのポインタを宣言
	CPlayerSearch *pCPlayerSearch = new CPlayerSearch;

	// 生成の成功の有無を判定
	if (pCPlayerSearch != NULL)
	{
		// 初期化処理
		if (FAILED(pCPlayerSearch->Init(pos, rot, modelType, motionType,STATE_TYPE_MAX)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCPlayerSearch == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// 種類を設定
	pCPlayerSearch->SetType(TYPE_PLAYER);

	// 探索プレイヤーのポインタを返す
	return pCPlayerSearch;
}

//-------------------------------------
//- 探索プレイヤーの設定処理
//-------------------------------------
void CPlayerSearch::Set(D3DXVECTOR3 pos,  D3DXVECTOR3 rot)
{
	// 情報更新
	m_dataPos.Set(pos);		// 位置
	m_dataPosOld.Set(pos);	// 前回の位置

	m_dataSize.Set(D3DXVECTOR3(50.0f,50.0f,50.0f));	// 大きさ

	m_dataRot.Set(rot);		// 移動量
	m_dataRotDest.Set(rot);	// 目的の向き
}

//-------------------------------------
//- 探索プレイヤーのイベントの更新処理
//-------------------------------------
void CPlayerSearch::UpdateEvent(void)
{
	// 時間管理の情報を取得
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// 時間管理取得の有無を判定
	if (pManagerTime == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 変数宣言（情報取得）
	int nStateTime = m_nDataStateTime.Get();	// 状態時間
	int nStateCount = m_nDataStateCount.Get();	// 状態カウント

	// 状態の判定
	if (m_stateType == STATE_TYPE_TOUCH ||
		m_stateType == STATE_TYPE_EAT)
	{
		// 整数カウントの有無を判定
		if (pManagerTime->m_bDataIntCount.Get() == true)
		{
			// 触るカウントを加算
			nStateCount++;
		}

		// 触るカウントを判定
		if (nStateCount >= nStateTime)
		{
			// 触るカウントを初期化
			nStateCount = 0;

			// 状態を通常に変更
			m_stateType = STATE_TYPE_NEUTRAL;
		}

		// 情報更新
		m_nDataStateTime.Set(nStateTime);	// 状態時間
		m_nDataStateCount.Set(nStateCount);	// 状態カウント
	}
	else
	{
		// イベントとの当たり判定
		CollisionEvent();
	}
}

//-------------------------------------
//- 探索プレイヤーのイベントとの当たり判定処理
//-------------------------------------
void CPlayerSearch::CollisionEvent(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();		// 位置
	D3DXVECTOR3 size = m_dataSize.Get();	// 大きさ

	// 変数宣言
	bool bCol = false;	// 当たり判定の有無

	for (int nCutEventObject = 0; nCutEventObject < EVENT_OBJECT_NUM_MAX; nCutEventObject++)
	{
		// イベントオブジェクトの情報を取得
		CEventObject *pEventObject = CManagerObject::GetEventObject(nCutEventObject);

		// イベントオブジェクトの有無を判定
		if (pEventObject != NULL)
		{
			// 変数宣言（情報取得）
			D3DXVECTOR3 eventObjectPos = pEventObject->m_dataPos.Get();		// 位置
			D3DXVECTOR3 eventObjectSize = pEventObject->m_dataSize.Get();	// 大きさ
			D3DXVECTOR3 colSizeAdd = D3DXVECTOR3(10.0f, 0.0f, 10.0f);	// 追加の当たり判定の大きさ
			bool bEventObjectUse = pEventObject->m_bDataUse.Get();			// 使用の有無

			// オブジェクトイベントが使用可能
			if (bEventObjectUse == false)
			{
				if (CHit::hitRectangle(pos, size, eventObjectPos, eventObjectSize + colSizeAdd) == true)
				{
					// イベントアクション処理
					InputEventAction(pEventObject);

					// 操作説明UIの有無を判定
					if (m_pUiOprDesc == NULL)
					{
						// 操作説明UIを生成
						m_pUiOprDesc = CUiOprDesc::Create(CUiOprDesc::TEX_SPACE);

						// 操作説明UIの設定処理
						m_pUiOprDesc->Set(
							D3DXVECTOR3(SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT * 0.9f, 0.0f),
							D3DXVECTOR3(100.0f, 50.0f, 0.0f),
							D3DXVECTOR3(5.0f, 5.0f, 0.0f),
							D3DXVECTOR3(0.5f, 0.5f, 0.0f)
						);
					}

					// 操作説明文UIの有無を判定
					if (m_pUiTextDesc == NULL)
					{
						// 操作説明文UIを生成
						m_pUiTextDesc = CUiTextDesc::Create(CUiTextDesc::TEX_PUSH);

						// 操作説明文UIの設定処理
						m_pUiTextDesc->Set(
							D3DXVECTOR3(SCREEN_WIDTH * 0.12f, SCREEN_HEIGHT * 0.825f, 0.0f),
							D3DXVECTOR3(90.0f, 40.0f, 0.0f),
							D3DXVECTOR3(5.0f, 5.0f, 0.0f),
							D3DXVECTOR3(0.5f, 0.5f, 0.0f)
						);
					}

					// 当たり判定が存在する
					bCol = true;
				}
			}
		}
	}

	for (int nCutGarbage = 0; nCutGarbage < GARBAGE_NUM_MAX; nCutGarbage++)
	{
		// ゴミの情報を取得
		CGarbage *pGarbage = CManagerObject::GetGarbage(nCutGarbage);

		// ゴミの有無を判定
		if (pGarbage != NULL)
		{
			// 変数宣言（情報取得）
			D3DXVECTOR3 grabagePos = pGarbage->m_dataPos.Get();			// 位置
			D3DXVECTOR3 grabageSize = pGarbage->m_dataSize.Get();		// 大きさ
			D3DXVECTOR3 colSizeAdd = D3DXVECTOR3(10.0f, 0.0f, 10.0f);	// 追加の当たり判定の大きさ
			bool bEat = pGarbage->m_bDataEat.Get();

			// 矩形当たり判定 && 食べてない
			if (CHit::hitRectangle(pos, size, grabagePos, grabageSize + colSizeAdd) == true &&
				bEat == false)
			{
				// ゴミアクション処理
				InputGarbageAction(pGarbage, nCutGarbage);

				// 操作説明UIの有無を判定
				if (m_pUiOprDesc == NULL)
				{
					// 操作説明UIを生成
					m_pUiOprDesc = CUiOprDesc::Create(CUiOprDesc::TEX_SPACE);

					// 操作説明UIの設定処理
					m_pUiOprDesc->Set(
						D3DXVECTOR3(SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT * 0.9f, 0.0f),
						D3DXVECTOR3(100.0f, 50.0f, 0.0f),
						D3DXVECTOR3(5.0f, 5.0f, 0.0f),
						D3DXVECTOR3(0.5f, 0.5f, 0.0f)
					);
				}

				// 操作説明文UIの有無を判定
				if (m_pUiTextDesc == NULL)
				{
					// 操作説明文UIを生成
					m_pUiTextDesc = CUiTextDesc::Create(CUiTextDesc::TEX_PUSH);

					// 操作説明文UIの設定処理
					m_pUiTextDesc->Set(
						D3DXVECTOR3(SCREEN_WIDTH * 0.12f, SCREEN_HEIGHT * 0.825f, 0.0f),
						D3DXVECTOR3(90.0f, 40.0f, 0.0f),
						D3DXVECTOR3(5.0f, 5.0f, 0.0f),
						D3DXVECTOR3(0.5f, 0.5f, 0.0f)
					);
				}

				// 当たり判定が存在する
				bCol = true;
			}
		}
	}

	// ゲートの情報を取得
	CGate *pGate = CManagerObject::GetGate();

	// ゲートの有無を判定
	if (pGate != NULL)
	{
		// 変数宣言（情報取得）
		D3DXVECTOR3 pGatePos = pGate->m_dataPos.Get();				// 位置
		D3DXVECTOR3 pGateSize = pGate->m_dataSize.Get();			// 大きさ
		D3DXVECTOR3 colSizeAdd = D3DXVECTOR3(10.0f, 0.0f, 10.0f);	// 追加の当たり判定の大きさ

		if (CHit::hitRectangle(pos, size, pGatePos, pGateSize + colSizeAdd) == true)
		{
			// ゲートアクション処理
 			InputGateAction(pGate);

			// 操作説明UIの有無を判定
			if (m_pUiOprDesc == NULL)
			{
				// 操作説明UIを生成
				m_pUiOprDesc = CUiOprDesc::Create(CUiOprDesc::TEX_SPACE);

				// 操作説明UIの設定処理
				m_pUiOprDesc->Set(
					D3DXVECTOR3(SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT * 0.9f, 0.0f),
					D3DXVECTOR3(100.0f, 50.0f, 0.0f),
					D3DXVECTOR3(5.0f, 5.0f, 0.0f),
					D3DXVECTOR3(0.5f, 0.5f, 0.0f)
				);
			}

			// 操作説明文UIの有無を判定
			if (m_pUiTextDesc == NULL)
			{
				// 操作説明文UIを生成
				m_pUiTextDesc = CUiTextDesc::Create(CUiTextDesc::TEX_PUSH);

				// 操作説明文UIの設定処理
				m_pUiTextDesc->Set(
					D3DXVECTOR3(SCREEN_WIDTH * 0.12f, SCREEN_HEIGHT * 0.825f, 0.0f),
					D3DXVECTOR3(90.0f, 40.0f, 0.0f),
					D3DXVECTOR3(5.0f, 5.0f, 0.0f),
					D3DXVECTOR3(0.5f, 0.5f, 0.0f)
				);
			}

			// 当たり判定が存在する
			bCol = true;
		}
	}

	if (bCol == false)
	{
		if (m_pUiOprDesc != NULL)
		{
			// 説明UIの終了処理
			m_pUiOprDesc->Uninit();
			m_pUiOprDesc = NULL;
		}

		if (m_pUiTextDesc != NULL)
		{
			// 説明文UIの終了処理
			m_pUiTextDesc->Uninit();
			m_pUiTextDesc = NULL;
		}
	}
}

//-------------------------------------
//- 探索プレイヤーのイベントアクション処理
//-------------------------------------
void CPlayerSearch::InputEventAction(CEventObject *pEventObject)
{
	// キーボードの情報取得処理
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

		// 処理を抜ける
		return;
	}

	// X入力のポインタを宣言
	CXInput *pXInput = CManager::GetXInput();

	// X入力の情報取得の成功を判定
	if (pXInput == NULL)
	{
		// 処理を抜ける
		return;
	}

	// スコアの情報取得処理
	CScore *pScore = CGame::GetMgrSysObj()->GetScore();

	// スコアの情報取得の成功を判定
	if (pScore == NULL)
	{// 失敗時

		// 処理を抜ける
		return;
	}

	// 入力の判定
	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true ||
		pXInput->GetTrigger(XINPUT_GAMEPAD_A, CXInput::TYPE_INPUT_BUTTON))
	{// SPACEキー

		// クイックタイムイベントの設定
		CSysPhaseSearch::SetQte(CQte::TYPE_QTE_TIMING);

		// プレイヤーの状態を触るに変更
		m_stateType = STATE_TYPE_TOUCH;

		// 状態時間を代入
		m_nDataStateTime.Set(90);

		// イベントオブジェクトの実行処理
		pEventObject->Execution();
	}
}

//-------------------------------------
//- 探索プレイヤーのゴミのアクション処理
//-------------------------------------
void CPlayerSearch::InputGarbageAction(CGarbage *pGarbage, int nNum)
{
	// キーボードの情報取得処理
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

		// 処理を抜ける
		return;
	}

	// X入力のポインタを宣言
	CXInput *pXInput = CManager::GetXInput();

	// X入力の情報取得の成功を判定
	if (pXInput == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 入力の判定
	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true ||
		pXInput->GetTrigger(XINPUT_GAMEPAD_A, CXInput::TYPE_INPUT_BUTTON))
	{// SPACEキー

		// プレイヤーの状態を食べるに変更
		m_stateType = STATE_TYPE_EAT;

		// 状態時間を代入
		m_nDataStateTime.Set(60);

		// オブジェクト管理のポインタを初期化
		CManagerObject::ReleaseGarbage(nNum);

		// イベントオブジェクトの実行処理
		pGarbage->Execution(60);
	}
}

//-------------------------------------
//- 探索プレイヤーのゲートのアクション処理
//-------------------------------------
void CPlayerSearch::InputGateAction(CGate *pGate)
{
	// キーボードの情報取得処理
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

	 // 処理を抜ける
		return;
	}

	// X入力のポインタを宣言
	CXInput *pXInput = CManager::GetXInput();

	// X入力の情報取得の成功を判定
	if (pXInput == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 入力の判定
	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true ||
		pXInput->GetTrigger(XINPUT_GAMEPAD_A, CXInput::TYPE_INPUT_BUTTON))
	{// SPACEキー

		// プレイヤーの状態を触るに変更
		m_stateType = STATE_TYPE_TOUCH;

		// イベントオブジェクトの実行処理
		pGate->Execution();

		// 次のフェーズの代入（戦闘）
		CSysGamePhase::SetTypeNext(CSysGamePhase::TYPE_BATTLE);

		return;
	}
}

//-------------------------------------
//- 探索プレイヤーのモーション更新処理
//-------------------------------------
void CPlayerSearch::UpdateMotion(void)
{
	// 変数宣言
	CMotion *pMotion = GetMotion();			// モーション情報を取得
	D3DXVECTOR3 move = m_dataMove.Get();	// 移動量を取得

	if (m_stateType != STATE_TYPE_TOUCH &&
		m_stateType != STATE_TYPE_EAT)
	{
		// 移動量で状態を変更
		if (move.x >= 0.3f ||
			move.x <= -0.3f ||
			move.z >= 0.3f ||
			move.z <= -0.3f)
		{
			m_stateType = STATE_TYPE_MOVE;
		}
		else
		{
			m_stateType = STATE_TYPE_NEUTRAL;
		}
	}

	// モーションの終了状況を判定
	if (pMotion->IsFinsih() == true)
	{
		// モーションの更新
		pMotion->Update();
	}

	// モーションの設定処理
	if (m_stateType != m_stateTypeOld)
	{
		// 状態の判定
		switch (m_stateType)
		{
		case STATE_TYPE_NEUTRAL:

			// 待機モーションの設定
			pMotion->Set(STATE_TYPE_NEUTRAL);

			break;

		case STATE_TYPE_MOVE:

			// 移動モーションの設定
			pMotion->Set(STATE_TYPE_MOVE);

			break;

		case STATE_TYPE_TOUCH:

			// 触るモーションの設定
			pMotion->Set(STATE_TYPE_TOUCH);

			break;

		case STATE_TYPE_EAT:

			// 触るモーションの設定
			pMotion->Set(STATE_TYPE_EAT);

			break;
		}
	}
}