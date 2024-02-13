
//-===============================================
//-
//-	通常敵の処理[enemy_normal.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "enemy_normal.h"
#include "object_x.h"

#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "manager_object.h"

#include "manager_model.h"
#include "time_stop.h"
#include "sys_game_phase.h"

#include "sound.h"

#include "player_battle.h"
#include "sys_phase_battle.h"

#include "particle.h"
#include "effect_object.h"	

#include "mgr_sys_obj.h"
#include "score.h"

#include "effect_game.h"

#include "object_col.h"

#include "state_game.h"
#include "state_battle.h"

#include "hit.h"

//-======================================
//-	マクロ定義
//-======================================

#define EMY_NOR_LIFE			(100)		// 体力
#define EMY_NOR_SPEED			(6.0f)		// 速度

#define EMY_NOR_ATTACK_DAMAGE	(5)			// 攻撃力

#define EMY_NOR_ATTACK_TIME		(45)		// 攻撃タイミング

#define EMY_NOR_SCORE			(1000)		// 持っているスコア値

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	通常敵のコンストラクタ
//-------------------------------------
CEnemyNormal::CEnemyNormal()
{
	state = STATE_NORMAL;
	m_pObjCol = NULL;
}

//-------------------------------------
//-	通常敵のデストラクタ
//-------------------------------------
CEnemyNormal::~CEnemyNormal()
{

}

//-------------------------------------
//- 通常敵の初期化処理
//-------------------------------------
HRESULT CEnemyNormal::Init(MODEL_TYPE modelType)
{
	// 敵の初期化 if(初期化成功の有無を判定)
	if (FAILED(CEnemy::Init(modelType)))
	{
		// 失敗を返す
		return E_FAIL;
	}

	// 初期設定
	InitSet();

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 通常敵の終了処理
//-------------------------------------
void CEnemyNormal::Uninit(void)
{
	// 当たり判定オブジェクトの有無を判定
	if (m_pObjCol != NULL)
	{
		// 当たり判定オブジェクトの更新
		m_pObjCol->Uninit();

		// 当たり判定オブジェクトの開放処理
		delete m_pObjCol;
		m_pObjCol = NULL;
	}

	// 敵の終了処理
	CEnemy::Uninit();
}

//-------------------------------------
//- 通常敵の更新処理
//-------------------------------------
void CEnemyNormal::Update(void)
{
	// ゲームの状態の判定
	switch (state)
	{
	case STATE_NORMAL:

		// 探知AI
		AiSearch();

		break;
	case STATE_TARGET:

		// 追尾AI
		AiTarget();

		break;
	case STATE_ATTACK:

		// 攻撃AI
		AiAttack();

		break;

	case STATE_COOL_TIME:

		// クールタイムAI
		AiCoolTime();

		break;
	}

	// 当たり判定オブジェクトの有無を判定
	if (m_pObjCol != NULL)
	{
		// 当たり判定オブジェクトの更新
		m_pObjCol->Update();
	}

	// 敵の更新処理
	CEnemy::Update();
}

//-------------------------------------
//- 通常敵の描画処理
//-------------------------------------
void CEnemyNormal::Draw(void)
{
	// 敵の描画処理
	CEnemy::Draw();
}

//-------------------------------------
//- 通常敵の生成処理
//-------------------------------------
CEnemyNormal *CEnemyNormal::Create(MODEL_TYPE modelType)
{
	// 通常敵の生成
	CEnemyNormal *pCEnemyNormal = DBG_NEW CEnemyNormal;

	// 生成の成功の有無を判定
	if (pCEnemyNormal != NULL)
	{
		// 初期化処理
		if (FAILED(pCEnemyNormal->Init(modelType)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCEnemyNormal == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// 種類を設定
	pCEnemyNormal->SetType(TYPE_ENEMY);

	// 通常敵のポインタを返す
	return pCEnemyNormal;
}

//-------------------------------------
//- 通常敵の当たり判定オブジェクト取得処理処理
//-------------------------------------
CObjectCol *CEnemyNormal::GetObjectCol(void)
{
	return m_pObjCol;
}

//-------------------------------------
//- 通常敵の設定処理
//-------------------------------------
void CEnemyNormal::InitSet(void)
{
	// 情報更新
	m_nDataLife.Set(EMY_NOR_LIFE);			// 体力

	m_fDataSpeedNor.Set(EMY_NOR_SPEED);
	m_fDataSpeedStr.Set(10.0f);
	m_fDataSpeed.Set(m_fDataSpeedNor.Get());

	m_dataSearchRangeNor.Set(D3DXVECTOR3(1500.0f, 0.0f, 1500.0f));
	m_dataSearchRangeStr.Set(D3DXVECTOR3(2000.0f, 0.0f, 2000.0f));
	m_dataSearchRange.Set(m_dataSearchRangeNor.Get());

	m_dataAttackRangeNor.Set(D3DXVECTOR3(200.0f, 0.0f, 200.0f));
	m_dataAttackRange.Set(m_dataAttackRangeNor.Get());

	m_nDataStrTime.Set(60);
}

//-------------------------------------
//- 通常敵のダメージ処理
//-------------------------------------
void CEnemyNormal::Hit(int nCutEnemy, int nDamage)
{
	// ゲームエフェクトのポインタを宣言
	CEffectGame *pEffectGame = CManager::GetEffectGame();

	// ゲームエフェクトの有無を判定
	if (pEffectGame == NULL)
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

	// スコアのポインタを宣言
	CScore *pScore = CGame::GetMgrSysObj()->GetScore();

	// スコアの有無を判定
	if (pScore == NULL)
	{
		// 処理を抜ける
		return;
	}

	// ゲームステータスの情報を取得
	CStateGame *pStateGame = CGame::GetStateGame();

	// ゲームステータス取得の有無を判定
	if (pStateGame == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 戦闘ステータスの情報を取得
	CStateBattle *pStateBattle = CGame::GetStateBattle();

	// 戦闘ステータス取得の有無を判定
	if (pStateBattle == NULL)
	{
		// 処理を抜ける
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

	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();		// 位置
	D3DXVECTOR3 move = m_dataMove.Get();	// 移動量

	int nLife = m_nDataLife.Get();			// 体力の取得処理
	
	// ダメージの値を減算
	nLife -= nDamage;

	if (nLife <= 0)
	{
		// オブジェクトエフェクトの生成
		CEffectObject *pEffectObject = CEffectObject::Create(CEffectObject::MODEL_COIN_000);

		// オブジェクトエフェクトの生成成功の有無を判定
		if (pEffectObject != NULL)
		{
			// オブジェクトエフェクト設定
			pEffectObject->Set(
				D3DXVECTOR3(pos.x, pos.y + 30.0f, pos.z),
				D3DXVECTOR3(5.0f, 5.0f, 5.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 3.0f, 0.0f),
				D3DXVECTOR3(0.0f, 75.0f, 0.0f));
		}

		// スコアの加算処理
		pScore->Add(CScore::GET_TYPE_NORMAL, EMY_NOR_SCORE);

		// 敵の死亡数を加算
		pStateGame->AddEnemyDeath();

		// パーティクルの生成
		CParticle::SetParticle(
			32,
			pos,
			D3DXVECTOR3(40.0f, 40.0f, 0.0f),
			D3DXVECTOR3(30.0f, 30.0f, 0.0f),
			D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
			60);

		// 画面揺れ
		pEffectGame->Set(
			D3DXVECTOR3(0.0f,0.5f,0.0f),
			D3DXVECTOR3(4.0f,4.0f,4.0f),
			4,
			8);

		// ヒットストップ
		pManagerTime->Set(0.0f,10);

		// SEの再生（敵の死亡音000）
		pSound->Play(CSound::LABEL_SE_DIED_ENEMY_000);

		// オブジェクト管理のポインタを初期化
		CManagerObject::ReleaseEnemyNormal(nCutEnemy);

		// 自分の終了処理
		Uninit();

		// 処理を抜ける
		return;
	}
	else
	{
		// パーティクルの生成
		CParticle::SetParticle(
			8,
			pos,
			D3DXVECTOR3(40.0f, 40.0f, 0.0f),
			D3DXVECTOR3(70.0f, 70.0f, 0.0f),
			D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
			30);

		// 画面揺れ
		pEffectGame->Set(
			D3DXVECTOR3(0.0f, 0.5f, 0.0f),
			D3DXVECTOR3(2.0f, 2.0f, 2.0f),
			2,
			2);

		// ヒットストップ
		pManagerTime->Set(0.5f, 4);

		// 属性を判定
		switch (pStateBattle->GetElemType())
		{
		case CStateBattle::ELEM_TYPE_NORMAL:

			// SEの再生（敵のダメージ音000）
			pSound->Play(CSound::LABEL_SE_DAMAGE_ENEMY_000);

			break;

		case CStateBattle::ELEM_TYPE_CHAOS:

			// SEの再生（敵のダメージ音001）
			pSound->Play(CSound::LABEL_SE_DAMAGE_ENEMY_001);

			break;
		}

	}

	// 情報更新
	m_nDataLife.Set(nLife);		// 体力
}

//-------------------------------------
//- 通常敵の索敵AI処理
//-------------------------------------
void CEnemyNormal::AiSearch(void)
{
	// プレイヤーの情報を取得
	CPlayer *pPlayer = CSysPhaseBattle::GetPlayer();		

	// 情報取得の有無を判定
	if (pPlayer == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();					// 位置
	D3DXVECTOR3 searchRange = m_dataSearchRange.Get();	// 索敵範囲

	// 変数宣言（プレイヤーの情報取得）
	D3DXVECTOR3 posPlayer = pPlayer->m_dataPos.Get();	// プレイヤーの位置

	// 矩形の当たり判定（索敵範囲とプレイヤーの位置）
	if (CHit::hitRectangle(posPlayer, D3DXVECTOR3(0.0f, 0.0f, 0.0f), pos, searchRange) == true)
	{// プレイヤーが一定範囲にいる場合検知
		
		// 状態を変更
		state = STATE_TARGET;
	}

	// 情報更新
	m_dataPos.Set(pos);		// 位置
}

//-------------------------------------
//- 通常敵の追尾AI処理
//-------------------------------------
void CEnemyNormal::AiTarget(void)
{
	// 時間管理の情報を取得
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// 時間管理取得の有無を判定
	if (pManagerTime == NULL)
	{
		// 処理を抜ける
		return;
	}

	// プレイヤーの情報を取得
	CPlayer *pPlayer = CSysPhaseBattle::GetPlayer();

	// 情報取得の有無を判定
	if (pPlayer == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();						// 位置
	D3DXVECTOR3 rot = m_dataRot.Get();						// 向き
	D3DXVECTOR3 move = m_dataMove.Get();					// 移動量
	float speed = m_fDataSpeed.Get();						// 速度
	D3DXVECTOR3 searchRange = m_dataSearchRange.Get();		// 追尾索敵範囲
	D3DXVECTOR3 attackRange = m_dataAttackRange.Get();		// 攻撃開始範囲

	D3DXVECTOR3 posPlayer = pPlayer->m_dataPos.Get();		// プレイヤーの位置
	D3DXVECTOR3 sizePlayer = pPlayer->m_dataRot.Get();		// プレイヤーの大きさ

	// 時間倍率の計算
	D3DXVECTOR3 moveTime = pManagerTime->CalRate(move);

	// 矩形の当たり判定（追尾索敵範囲とプレイヤーの位置）
	if (CHit::hitRectangle(posPlayer, D3DXVECTOR3(0.0f, 0.0f, 0.0f), pos, searchRange) == true)
	{//プレイヤーが一定範囲にいる場合検知

		if (CHit::hitRectangle(posPlayer, D3DXVECTOR3(0.0f, 0.0f, 0.0f), pos, attackRange) == true)
		{
			// 状態を変更
			state = STATE_ATTACK;

			// 当たり判定オブジェクトの有無を判定
			if (m_pObjCol == NULL)
			{
				//プレイヤーに振り向く
				rot.y = atan2f(pos.x - posPlayer.x, pos.z - posPlayer.z);

				// 当たり判定オブジェクトの生成処理
				m_pObjCol = CObjectCol::Create();

				// 当たり判定オブジェクトの設定処理
				m_pObjCol->Set(
					D3DXVECTOR3(
					pos.x + (-sinf(rot.y)) * 200.0f, 
					pos.y,
					pos.z + (-cosf(rot.y)) * 200.0f),
					D3DXVECTOR3(150.0f,50.0f, 150.0f),
					rot);

				// 当たり判定オブジェクトの色の設定
				m_pObjCol->m_dataColor.Set(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			}
		}
		else
		{
			//プレイヤーに振り向く
			rot.y = atan2f(pos.x - posPlayer.x, pos.z - posPlayer.z);

			// 時間倍率の計算
			float fEnemySpeedTime = pManagerTime->CalRate(speed);

			// 移動量を設定
			move.x = -sinf(rot.y) * fEnemySpeedTime;
			move.z = -cosf(rot.y) * fEnemySpeedTime;
		}

	}
	else
	{
		// 状態を変更
		state = STATE_NORMAL;
	}

	// 位置を更新
	pos += moveTime;

	// 時間倍率の計算
	float moveReduceTimeX = pManagerTime->CalRate((0.0f - move.x) * 0.3f);
	float moveReduceTimeZ = pManagerTime->CalRate((0.0f - move.z) * 0.3f);

	// 移動量を減衰
	move.x += moveReduceTimeX;
	move.z += moveReduceTimeZ;

	// 情報更新
	m_dataPos.Set(pos);		// 位置
	m_dataRot.Set(rot);		// 向き
	m_dataMove.Set(move);	// 移動量
}

//-------------------------------------
//- 通常敵の攻撃Ai処理
//-------------------------------------
void CEnemyNormal::AiAttack(void)
{
	// 変数宣言（プレイヤーの情報取得）
	CPlayer *pPlayer = CSysPhaseBattle::GetPlayer();

	// 情報取得の有無を判定
	if (pPlayer == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 変数宣言（プレイヤーの情報取得）
	D3DXVECTOR3 posPlayer = pPlayer->m_dataPos.Get();	// プレイヤーの位置
	D3DXVECTOR3 sizePlayer = pPlayer->m_dataRot.Get();	// プレイヤーの大きさ

	// 変数宣言（情報取得）
	int nAtkCut = m_nDataAtkCnt.Get();				// 攻撃カウント
	int nCoolTimeCut = m_nDataCoolTimeCnt.Get();	// クールタイムカウント

	// 攻撃カウントを加算
	nAtkCut++;

	// 攻撃カウントの判定
	if (nAtkCut >= EMY_NOR_ATTACK_TIME)
	{
		// クールタイム時間を設定
		nCoolTimeCut = 60;

		// クールタイム状態に変更
		state = STATE_COOL_TIME;

		// 攻撃カウントの初期化
		nAtkCut = 0;

		if (m_pObjCol != NULL)
		{
			// プレイヤーと攻撃の当たり判定
			if (m_pObjCol->Collision(posPlayer, sizePlayer) == true)
			{
				// プレイヤーのダメージ処理
				pPlayer->Hit(5);
			}

			// 当たり判定オブジェクトの終了処理
			m_pObjCol->Uninit();

			// 当たり判定オブジェクトの開放処理
			delete m_pObjCol;
			m_pObjCol = NULL;
		}
	}
	else if (nAtkCut == EMY_NOR_ATTACK_TIME * 0.9f)
	{
		if (m_pObjCol != NULL)
		{
			// 当たり判定オブジェクトの色の変更
			m_pObjCol->m_dataColor.Set(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
	}
	else if (nAtkCut == EMY_NOR_ATTACK_TIME * 0.5f)
	{
		if (m_pObjCol != NULL)
		{
			// 当たり判定オブジェクトの色の変更
			m_pObjCol->m_dataColor.Set(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f));
		}
	}

	// 情報更新
	m_nDataAtkCnt.Set(nAtkCut);
	m_nDataCoolTimeCnt.Set(nCoolTimeCut);
}

//-------------------------------------
//- 通常敵のクールタイムAi処理
//-------------------------------------
void CEnemyNormal::AiCoolTime(void)
{
	// 変数宣言（情報取得）
	int nCoolTimeCut = m_nDataCoolTimeCnt.Get();	// クールタイムカウント

	// クールタイムを減算
	nCoolTimeCut--;

	if (nCoolTimeCut == 0)
	{
		// 状態を通常に変更
		state = STATE_NORMAL;
	}

	// 情報更新
	m_nDataCoolTimeCnt.Set(nCoolTimeCut);
}