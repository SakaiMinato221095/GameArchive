
//-===============================================
//-
//-	戦闘プレイヤー処理[player_battle.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "player_battle.h"

#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "sys_game_phase.h"
#include "sys_phase_battle.h"

#include "Input.h"
#include "xinput.h"
#include "sound.h"
#include "debugproc.h"

#include "state_battle.h"
#include "life.h"

#include "bullet.h"
#include "bullet_bomb.h"
#include "chaos_attack.h"

#include "effect.h"

#include "time_stop.h"

#include "hit.h"

#include "manager_object.h"
#include "gate.h"

#include "ui_opr_desc.h"
#include "ui_text_desc.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CPlayerBattle::CPlayerBattle()
{
	// 値をクリア
	m_stateType = STATE_TYPE_NEUTRAL;
	m_stateTypeNew = m_stateType;

	m_pUiOprDesc = NULL;
	m_pUiTextDesc = NULL;

	m_pChaosAttack = NULL;
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CPlayerBattle::~CPlayerBattle()
{

}

//-------------------------------------
//- 戦闘プレイヤーの初期化処理
//-------------------------------------
HRESULT CPlayerBattle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CObjectModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax)
{
	// 戦闘プレイヤーの設定処理
	Set(pos,rot);

	// プレイヤーの初期化処理
	CPlayer::Init(modelType, motionType,STATE_TYPE_MAX);

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 戦闘プレイヤーの終了処理
//-------------------------------------
void CPlayerBattle::Uninit(void)
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
//- 戦闘プレイヤーの更新処理
//-------------------------------------
void CPlayerBattle::Update(void)
{
	// 情報設定（前回の情報）
	m_dataPosOld.Set(m_dataPos.Get());		// 位置
	int nCollTime = m_nDataCoolTime.Get();	// クールタイム

	if (nCollTime > 0)
	{
		nCollTime--;

		m_nDataCoolTime.Set(nCollTime);
	}
	else
	{
		// プレイヤーの更新処理
		CPlayer::Update();
	}


	// 攻撃の入力処理
	InputAttack();

	// ゲートとの当たり判定
	ColGate();

	// 攻撃の更新処理
	UpdateAttack();

	// モーションの更新処理
	UpdateMotion();
}

//-------------------------------------
//- 戦闘プレイヤーの描画処理
//-------------------------------------
void CPlayerBattle::Draw(void)
{
	// プレイヤーの描画処理
	CPlayer::Draw();
}

//-------------------------------------
//- 戦闘プレイヤーの生成処理
//-------------------------------------
CPlayerBattle *CPlayerBattle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CObjectModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType)
{
	// 戦闘プレイヤーのポインタを宣言
	CPlayerBattle *pCPlayerBattle = new CPlayerBattle;

	// 生成の成功の有無を判定
	if (pCPlayerBattle != NULL)
	{
		// 初期化処理
		if (FAILED(pCPlayerBattle->Init(pos, rot,modelType,motionType,STATE_TYPE_MAX)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCPlayerBattle == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// 種類を設定
	pCPlayerBattle->SetType(TYPE_PLAYER);

	// 戦闘プレイヤーのポインタを返す
	return pCPlayerBattle;
}

//-------------------------------------
//- 戦闘プレイヤーの設定処理
//-------------------------------------
void CPlayerBattle::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 情報更新
	m_dataPos.Set(pos);		// 位置
	m_dataPosOld.Set(pos);	// 前回の位置

	m_dataSize.Set(D3DXVECTOR3(50.0f, 50.0f, 50.0f));	// 大きさ

	m_dataRot.Set(rot);			// 移動量
	m_dataRotDest.Set(rot);		// 目的の向き

	m_nDataChargeMax.Set(60);	// チャージの最大数を設定
}

//-------------------------------------
//- 戦闘プレイヤーのゲートとの当たり判定処理
//-------------------------------------
void CPlayerBattle::ColGate(void)
{
	// 変数宣言
	bool bCol = false;	// 当たり判定の有無

	// ゲートの情報を取得
	CGate *pGate = CManagerObject::GetGate();

	// ゲートの有無を判定
	if (pGate != NULL)
	{
		// 変数宣言（情報取得）
		D3DXVECTOR3 pos = m_dataPos.Get();		// 位置
		D3DXVECTOR3 size = m_dataSize.Get();	// 大きさ

		// 変数宣言（オブジェクトの情報取得）
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
					D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.7f, 0.0f),
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
					D3DXVECTOR3(SCREEN_WIDTH * 0.47f, SCREEN_HEIGHT * 0.625f, 0.0f),
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
//- 戦闘プレイヤーのダメージ処理
//-------------------------------------
void CPlayerBattle::Hit(int nDamage)
{
	// 体力の取得処理
	CLife *pSysPhaseBattle = CSysPhaseBattle::GetLife();

	// 体力取得成功の有無を判定
	if (pSysPhaseBattle == NULL)
	{
		return;
	}

	// サウンドのポインタを宣言
	CSound *pSound = CManager::GetSound();

	// サウンドの情報取得の成功を判定
	if (pSound == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 変数宣言（体力の情報）
	int nLife = pSysPhaseBattle->m_nDataLife.Get();	// 体力値

	// 体力の判定
	if (nLife <= 0)
	{
		// 状態を変更
		m_stateTypeNew = STATE_TYPE_DEAD;
	}
	else
	{
		// 効果音BGMの再生（闇の攻撃000）
		pSound->Play(CSound::LABEL_SE_DAMAGE_PLAYER);

		// 体力の減算
		nLife -= nDamage;

		// 状態を変更
		m_stateTypeNew = STATE_TYPE_DAMAGE;
	}

	// 情報更新（体力の情報）
	pSysPhaseBattle->m_nDataLife.Set(nLife);	// 体力値
}

//-------------------------------------
//- 戦闘プレイヤーの攻撃処理
//-------------------------------------
void CPlayerBattle::InputAttack(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{
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

	// 戦闘ステータスのポインタを宣言
	CStateBattle *pStateBattle = CGame::GetStateBattle();

	// 戦闘ステータスの情報取得の成功を判定
	if (pStateBattle == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 時間管理の情報を取得
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// 時間管理取得の有無を判定
	if (pManagerTime == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 変数宣言（情報の取得）
	D3DXVECTOR3 pos = m_dataPos.Get();								// 位置情報
	D3DXVECTOR3 rot = m_dataRot.Get();								// 向き情報

	bool bShot = bDataShot.Get();									// 射撃の有無
	bool bShotAgain = bDataShotAgain.Get();							// 再射撃状態
	int nShotIntervalCount = nDataShotIntervalCount.Get();			// 弾の間隔カウント
	int nShotInterval = pStateBattle->m_nDataShotInterval.Get();	// 弾の間隔
	int nSubWeponNum = pStateBattle->m_nSubWeaponNum.Get();			// サブ武器の使用回数
	int nChargeCut = m_nDataChargeCut.Get();						// チャージカウント
	bool bCharge = m_bDataCharge.Get();								// チャージの有無

	// 変数宣言（戦闘ステータスの情報取得）
	CStateBattle::ELEM_TYPE elemType = pStateBattle->GetElemType();

	// 弾間隔の判定
	if (nShotIntervalCount >= nShotInterval)
	{
		// 入力の判定
		if (pInputKeyboard->GetTrigger(DIK_SPACE) == true || 
			pXInput->GetTrigger(XINPUT_GAMEPAD_A,CXInput::TYPE_INPUT_BUTTON) == true)
		{// SPACEキー

			// 移動停止
			m_bDataStopMove.Set(true);

			if (elemType == CStateBattle::ELEM_TYPE_CHAOS)
			{
				// 移動停止
				m_bDataStopMoveRot.Set(true);
			}

			// 弾の間隔カウントを初期化
			nShotIntervalCount = 0;

			// チャージを初期化
			nChargeCut = 0;

			// 状態の判定
			if (m_stateTypeNew != STATE_TYPE_ATTACK)
			{
				// 状態を設定
				m_stateTypeNew = STATE_TYPE_ATTACK;

				// 射撃状態に変更
				bShot = true;

				// チャージ状態に変更
				bCharge = true;
			}
			else
			{
				// 再射撃の有無
				bShotAgain = true;

				// チャージ状態に変更
				bCharge = true;
			}

		}
	}
	else
	{
		if (pManagerTime->m_bDataIntCount.Get() == true)
		{
			// 弾の間隔カウントを加算
			nShotIntervalCount++;
		}
	}

	if (elemType == CStateBattle::ELEM_TYPE_CHAOS)
	{
		if (m_pChaosAttack != NULL &&
			bCharge == false)
		{
			// 闇の攻撃の終了処理
			m_pChaosAttack->Uninit();
			m_pChaosAttack = NULL;
		}
	}

	if (nSubWeponNum > 0)
	{
		// 入力の判定
		if (pInputKeyboard->GetTrigger(DIK_J) == true)
		{// Kキー

			// 弾のポインタを宣言
			CBulletBomb *pBullet = pBullet->Create(CBulletBomb::TEX_BLUE_000);

			// サブ武器の使用回数を減算
			nSubWeponNum--;

			// 位置情報を設定
			pBullet->m_dataPos.Set(pos);

			// 大きさを設定
			pBullet->m_dataSize.Set(D3DXVECTOR3(100.0f, 100.0f, 0.0f));

			// 移動量を設定
			pBullet->m_dataMove.Set(D3DXVECTOR3(sinf(rot.y) * -10.0f, 0.0f, cosf(rot.y) * -10.0f));

			// 体力の設定
			pBullet->m_nDataLife.Set(120);

			// ダメージの設定
			pBullet->m_nDataDamage.Set(10);

			// 状態を設定
			m_stateTypeNew = STATE_TYPE_ATTACK;
		}
	}

	// 情報更新
	bDataShot.Set(bShot);								// 射撃の有無
	bDataShotAgain.Set(bShotAgain);						// 再射撃の有無
	nDataShotIntervalCount.Set(nShotIntervalCount);		// 弾の間隔カウント
	pStateBattle->m_nSubWeaponNum.Set(nSubWeponNum);	// サブ武器の使用回数
	m_bDataCharge.Set(bCharge);							// チャージの有無
	m_nDataChargeCut.Set(nChargeCut);					// チャージカウント
}

//-------------------------------------
//- 戦闘プレイヤーのゲートのアクション処理
//-------------------------------------
void CPlayerBattle::InputGateAction(CGate *pGate)
{
	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{
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
		pXInput->GetTrigger(XINPUT_GAMEPAD_A,CXInput::TYPE_INPUT_BUTTON))
	{// SPACEキー

		// イベントオブジェクトの実行処理
		pGate->Execution();

		// 次のフェーズの代入（戦闘）
		CSysGamePhase::SetTypeNext(CSysGamePhase::TYPE_SEARCH);

		return;
	}
}

//-------------------------------------
//- 戦闘プレイヤーの攻撃の更新処理
//-------------------------------------
void CPlayerBattle::UpdateAttack(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{
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

	// 戦闘ステータスのポインタを宣言
	CStateBattle *pStateBattle = CGame::GetStateBattle();

	// 戦闘ステータスの情報取得の成功を判定
	if (pStateBattle == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 変数宣言（情報取得）
	int nChargeCut = m_nDataChargeCut.Get();	// チャージのカウント
	int nChargeMax = m_nDataChargeMax.Get();	// チャージの最大値
	bool bCharge = m_bDataCharge.Get();			// チャージの有無

	// 変数宣言（戦闘ステータスの情報取得）
	CStateBattle::ELEM_TYPE elemType = pStateBattle->GetElemType();

	// 変数宣言
	D3DXVECTOR3 posHead = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 銃の位置を代入（番号ベタ打ち[15]番）
	posHead.x = GetObjectModel(0)->GetMtxWorld()._41;
	posHead.y = GetObjectModel(0)->GetMtxWorld()._42;
	posHead.z = GetObjectModel(0)->GetMtxWorld()._43;

	// 入力の判定
	if (pInputKeyboard->GetPress(DIK_SPACE) == true ||
		pXInput->GetPress(XINPUT_GAMEPAD_A, CXInput::TYPE_INPUT_BUTTON) == true)
	{// SPACEキー

		if (nChargeCut <= nChargeMax)
		{
			// チャージカウントの加算
			nChargeCut++;

			// エフェクトの生成
			CEffect *pEffect = CEffect::Create(CEffect::TEX_NORMAL_000);

			// エフェクトの有無を判定
			if (pEffect != NULL)
			{
				// 位置情報を設定
				pEffect->m_dataPos.Set(posHead);

				// 大きさを設定
				pEffect->m_dataSize.Set(D3DXVECTOR3(10.0f, 10.0f, 0.0f));

				// 移動量を設定
				pEffect->m_dataMove.Set(D3DXVECTOR3(0.0f, 5.0f, 0.0f));

				// 色を設定
				pEffect->m_dataColor.Set(D3DXCOLOR(0.5f, 0.0f, 0.5f, 1.0f));

				// エフェクトの設定処理
				pEffect->m_nDataLife.Set(2);
			}
		}
		else
		{
			// エフェクトの生成
			CEffect *pEffect = CEffect::Create(CEffect::TEX_NORMAL_000);

			// エフェクトの有無を判定
			if (pEffect != NULL)
			{
				// 位置情報を設定
				pEffect->m_dataPos.Set(posHead);

				// 大きさを設定
				pEffect->m_dataSize.Set(D3DXVECTOR3(30.0f, 30.0f, 0.0f));

				// 移動量を設定
				pEffect->m_dataMove.Set(D3DXVECTOR3(0.0f, 5.0f, 0.0f));

				// 色を設定
				pEffect->m_dataColor.Set(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

				// エフェクトの設定処理
				pEffect->m_nDataLife.Set(2);
			}
		}
	}
	else
	{
		// チャージの有無を変更
		bCharge = false;

		// 移動停止を終了
		m_bDataStopMove.Set(false);

		if (elemType == CStateBattle::ELEM_TYPE_CHAOS)
		{
			// 移動停止
			m_bDataStopMoveRot.Set(false);
		}
	}

	// 情報更新
	m_nDataChargeCut.Set(nChargeCut);	// チャージのカウント
	m_nDataChargeMax.Set(nChargeMax);	// チャージの最大値
	m_bDataCharge.Set(bCharge);			// チャージの有無
}

//-------------------------------------
//- 戦闘プレイヤーのモーション更新処理
//-------------------------------------
void CPlayerBattle::UpdateMotion(void)
{
	// 時間管理の情報を取得
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// 時間管理取得の有無を判定
	if (pManagerTime == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 戦闘ステータスのポインタを宣言
	CStateBattle *pStateBattle = CGame::GetStateBattle();

	// 戦闘ステータスの情報取得の成功を判定
	if (pStateBattle == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 変数宣言（情報取得）
	bool bShot = bDataShot.Get();				// 射撃の有無
	bool bShotAgain = bDataShotAgain.Get();		// 再射撃状態
	int nChargeCut = m_nDataChargeCut.Get();	// チャージのカウント
	int nChargeMax = m_nDataChargeMax.Get();	// チャージの最大値
	bool bCharge = m_bDataCharge.Get();			// チャージの有無

	// 変数宣言（戦闘ステータスの情報取得）
	CStateBattle::ELEM_TYPE elemType = pStateBattle->GetElemType();

	// 変数宣言（情報取得）
	CMotion *pMotion = GetMotion();			// モーション
	D3DXVECTOR3 move = m_dataMove.Get();	// 移動量

	// 時間倍率を判定
	if (pManagerTime->m_fDataTimeRate.Get() >= 0.5f)
	{
		// 状態を判定
		if (m_stateTypeNew == STATE_TYPE_NEUTRAL ||
			m_stateTypeNew == STATE_TYPE_MOVE)
		{
			// 移動量で状態を変更
			if (move.x >= 0.3f ||
				move.x <= -0.3f ||
				move.z >= 0.3f ||
				move.z <= -0.3f)
			{
				// 移動状態に変更
				m_stateTypeNew = STATE_TYPE_MOVE;
			}
			else
			{
				// 待機状態の変更
				m_stateTypeNew = STATE_TYPE_NEUTRAL;
			}
		}
	}

	// モーションの終了状況を判定
	if (pMotion->IsFinsih() == true)
	{
		// モーションの更新
		pMotion->Update();
	}
	else
	{
		// 待機状態を設定
		m_stateTypeNew = STATE_TYPE_NEUTRAL;
	}

	// 状態を判定
	if (m_stateType == STATE_TYPE_ATTACK)
	{
		// 射撃の有無とキーの判定（べたうち[銃を前に出したとき]）
		if (bShot == true &&
			GetMotion()->GetKey() == 1)
		{
			if (bCharge == false)
			{
				// 通常射撃
				ShotNor();
				
				// 射撃状態を解除
				bShot = false;
			}
			else
			{
				switch (elemType)
				{
				case CStateBattle::ELEM_TYPE_NORMAL:

					// 状態をチャージに変更
					m_stateTypeNew = STATE_TYPE_NOR_ATTACK;

					break;

				case CStateBattle::ELEM_TYPE_CHAOS:

					// 状態をチャージに変更
					m_stateTypeNew = STATE_TYPE_CHAOS_ATTACK;

					break;
				}

			}
		}

		// 再射撃の有無を判定
		if (bShotAgain == true &&
			GetMotion()->GetKey() >= 2)
		{
			// 攻撃モーションの設定
			pMotion->BlendSet();

			// 射撃状態を設定
			bShot = true;

			// 再射撃をなくす
			bShotAgain = false;
		}
	}

	// 状態を判定
	if (m_stateType == STATE_TYPE_NOR_ATTACK || 
		m_stateType == STATE_TYPE_CHAOS_ATTACK)
	{
		if (bCharge == false)
		{
			if (nChargeCut >= nChargeMax)
			{
				if (m_stateType == STATE_TYPE_NOR_ATTACK)
				{
					// 通常チャージ射撃
					ShotNorCharge();
				}
			}
			else
			{
				// 通常射撃
				ShotNor();
			}

			// チャージカウントの初期化
			nChargeCut = 0;

			// 射撃状態を解除
			bShot = false;

			// 待機状態を設定
			m_stateTypeNew = STATE_TYPE_NEUTRAL;
		}
		else if (bCharge == true)
		{
			if (nChargeCut >= nChargeMax)
			{
				// 闇の攻撃
				ShotChaosCharge();
			}
		}
	}

	// モーションの設定処理
	if (m_stateType != m_stateTypeNew)
	{
		// 状態の更新
		m_stateType = m_stateTypeNew;

		// 状態の判定
		if (m_stateType == STATE_TYPE_NEUTRAL)
		{
			// 待機モーションの設定
			pMotion->Set(STATE_TYPE_NEUTRAL);

			// 再射撃をなくす
			bShotAgain = false;
		}
		else if (m_stateType == STATE_TYPE_MOVE)
		{
			// 移動モーションの設定
			pMotion->Set(STATE_TYPE_MOVE);

			// 再射撃をなくす
			bShotAgain = false;
		}
		else if (m_stateType == STATE_TYPE_ATTACK)
		{
			// 攻撃モーションの設定
			pMotion->Set(STATE_TYPE_ATTACK);
		}
		else if (m_stateType == STATE_TYPE_NOR_ATTACK)
		{
			// 通常攻撃モーションの設定
			pMotion->Set(STATE_TYPE_NOR_ATTACK);
		}
		else if (m_stateType == STATE_TYPE_CHAOS_ATTACK)
		{
			// 闇の攻撃モーションの設定
   			pMotion->Set(STATE_TYPE_CHAOS_ATTACK);
		}
		else if (m_stateType == STATE_TYPE_DAMAGE)
		{
			// ダメージモーションの設定
			pMotion->Set(STATE_TYPE_DAMAGE);
		}
		else if (m_stateType == STATE_TYPE_DEAD)
		{
			// 死亡モーションの設定
			pMotion->Set(STATE_TYPE_DEAD);
		}
	}

	// 情報更新
	bDataShot.Set(bShot);				// 射撃の有無
	bDataShotAgain.Set(bShotAgain);		// 再射撃の有無
	m_nDataChargeCut.Set(nChargeCut);	// チャージカウント
}

//-------------------------------------
//- 戦闘プレイヤーの通常属性の銃の発射処理
//-------------------------------------
void CPlayerBattle::ShotNor(void)
{
	// サウンドのポインタを宣言
	CSound *pSound = CManager::GetSound();

	// サウンドの情報取得の成功を判定
	if (pSound == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 戦闘ステータスのポインタを宣言
	CStateBattle *pStateBattle = CGame::GetStateBattle();

	// 戦闘ステータスの情報取得の成功を判定
	if (pStateBattle == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 時間管理の情報を取得
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// 時間管理取得の有無を判定
	if (pManagerTime == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 変数宣言（情報の取得）
	D3DXVECTOR3 pos = m_dataPos.Get();		// 位置情報
	D3DXVECTOR3 rot = m_dataRot.Get();		// 向き情報

	// モーションのキー数を取得
	int nKey = GetMotion()->GetKey();

	// 変数宣言
	D3DXVECTOR3 posGun = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 銃の位置を代入（番号ベタ打ち[15]番）
	posGun.x = GetObjectModel(15)->GetMtxWorld()._41;
	posGun.y = GetObjectModel(15)->GetMtxWorld()._42;
	posGun.z = GetObjectModel(15)->GetMtxWorld()._43;

	// 弾の生成
	CBullet *pBullet = pBullet->Create(CBullet::TEX_RED_000);

	// 弾の生成成功の有無を取得
	if (pBullet != NULL)
	{
		// 位置情報を設定
		pBullet->m_dataPos.Set(posGun);

		// 大きさを設定
		pBullet->m_dataSize.Set(D3DXVECTOR3(10.0f, 10.0f, 0.0f));

		// 移動量を設定
		pBullet->m_dataMove.Set(D3DXVECTOR3(sinf(rot.y) * -25.0f, 0.0f, cosf(rot.y) * -25.0f));

		// 体力の設定
		pBullet->m_nDataLife.Set(60);

		// ダメージの設定
		pBullet->m_nDataDamage.Set(10);

		// 発射音SEの再生
		pSound->Play(CSound::LABEL_SE_SHOT_000);
	}
}

//-------------------------------------
//- 戦闘プレイヤーの通常属性の銃のチャージ発射処理
//-------------------------------------
void CPlayerBattle::ShotNorCharge(void)
{
	// サウンドのポインタを宣言
	CSound *pSound = CManager::GetSound();

	// サウンドの情報取得の成功を判定
	if (pSound == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 戦闘ステータスのポインタを宣言
	CStateBattle *pStateBattle = CGame::GetStateBattle();

	// 戦闘ステータスの情報取得の成功を判定
	if (pStateBattle == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 時間管理の情報を取得
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// 時間管理取得の有無を判定
	if (pManagerTime == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 変数宣言（情報の取得）
	D3DXVECTOR3 pos = m_dataPos.Get();		// 位置情報
	D3DXVECTOR3 rot = m_dataRot.Get();		// 向き情報

	// 変数宣言
	D3DXVECTOR3 posGun = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 銃の位置を代入（番号ベタ打ち[15]番）
	posGun.x = GetObjectModel(15)->GetMtxWorld()._41;
	posGun.y = GetObjectModel(15)->GetMtxWorld()._42;
	posGun.z = GetObjectModel(15)->GetMtxWorld()._43;

	// 弾の生成
	CBullet *pBullet = pBullet->Create(CBullet::TEX_RED_000);

	// 弾の生成成功の有無を取得
	if (pBullet != NULL)
	{
		// 位置情報を設定
		pBullet->m_dataPos.Set(posGun);

		// 大きさを設定
		pBullet->m_dataSize.Set(D3DXVECTOR3(30.0f, 30.0f, 0.0f));

		// 移動量を設定
		pBullet->m_dataMove.Set(D3DXVECTOR3(sinf(rot.y) * -50.0f, 0.0f, cosf(rot.y) * -50.0f));

		// 体力の設定
		pBullet->m_nDataLife.Set(30);

		// クールタイムの設定
		m_nDataCoolTime.Set(30);

		// 情報取得（戦闘ステータス）
		CStateBattle::ELEM_TYPE elemType = pStateBattle->GetElemType();		// 属性種類
		int nElemRank = pStateBattle->m_aDataElemRank[elemType].Get();		// 属性ランク

		if (nElemRank == 0)
		{
			// ダメージの設定
			pBullet->m_nDataDamage.Set(25);
		}
		else if (nElemRank == 1)
		{
			// ダメージの設定
			pBullet->m_nDataDamage.Set(30);
		}
		else if (nElemRank == 2)
		{
			// ダメージの設定
			pBullet->m_nDataDamage.Set(50);
		}
		else if (nElemRank == 3)
		{
			// ダメージの設定
			pBullet->m_nDataDamage.Set(100);
		}

		// 発射音SEの再生
		pSound->Play(CSound::LABEL_SE_NOR_CHARGE_SHOT);
	}
}

//-------------------------------------
//- 戦闘プレイヤーの闇属性の銃のチャージ発射処理
//-------------------------------------
void CPlayerBattle::ShotChaosCharge(void)
{
	// サウンドのポインタを宣言
	CSound *pSound = CManager::GetSound();

	// サウンドの情報取得の成功を判定
	if (pSound == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 戦闘ステータスのポインタを宣言
	CStateBattle *pStateBattle = CGame::GetStateBattle();

	// 戦闘ステータスの情報取得の成功を判定
	if (pStateBattle == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 時間管理の情報を取得
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// 時間管理取得の有無を判定
	if (pManagerTime == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 変数宣言（情報の取得）
	D3DXVECTOR3 pos = m_dataPos.Get();		// 位置情報
	D3DXVECTOR3 rot = m_dataRot.Get();		// 向き情報

	CMotion *pMotion = GetMotion();			// モーション

	// モーションのキー数を取得
	int nKey = GetMotion()->GetKey();

	// 変数宣言
	D3DXVECTOR3 posGun = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 銃の位置を代入（番号ベタ打ち[15]番）
	posGun.x = GetObjectModel(15)->GetMtxWorld()._41;
	posGun.y = GetObjectModel(15)->GetMtxWorld()._42;
	posGun.z = GetObjectModel(15)->GetMtxWorld()._43;

	// 情報取得（戦闘ステータス）
   	CStateBattle::ELEM_TYPE elemType = pStateBattle->GetElemType();		// 属性種類
	int nElemRank = pStateBattle->m_aDataElemRank[elemType].Get();		// 属性ランク

	if (m_pChaosAttack == NULL &&
		m_stateType == STATE_TYPE_CHAOS_ATTACK)
	{
		// 闇の攻撃の生成
		m_pChaosAttack = CChaosAttack::Create();

		// 闇の攻撃の生成成功の有無を取得
		if (m_pChaosAttack != NULL)
		{
			if (nElemRank == 0)
			{
				// 設定処理
				m_pChaosAttack->Set(
					D3DXVECTOR3(pos.x + (sinf(rot.y) * -75.0f), 125.0f, pos.z + (cosf(rot.y) * -75.0f)),
					rot,
					5);
			}
			else if (nElemRank == 1)
			{
				// 設定処理
				m_pChaosAttack->Set(
					D3DXVECTOR3(pos.x + (sinf(rot.y) * -75.0f), 125.0f, pos.z + (cosf(rot.y) * -75.0f)),
					rot,
					7);
			}
			else if (nElemRank == 2)
			{
				// 設定処理
				m_pChaosAttack->Set(
					D3DXVECTOR3(pos.x + (sinf(rot.y) * -75.0f), 125.0f, pos.z + (cosf(rot.y) * -75.0f)),
					rot,
					10);
			}
			else if (nElemRank == 3)
			{
				// 設定処理
				m_pChaosAttack->Set(
					D3DXVECTOR3(pos.x + (sinf(rot.y) * -75.0f), 125.0f, pos.z + (cosf(rot.y) * -75.0f)),
					rot,
					15);
			}


		}
	}

}