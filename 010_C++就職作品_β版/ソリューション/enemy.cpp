
//-===============================================
//-
//-	敵の処理[enemy.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "enemy.h"

#include "renderer.h"
#include "manager.h"

#include "helper_sakai.h"

#include "fade.h"

#include "coll.h"

#include "particle.h"

#include "player.h"
#include "game.h"

#include "helper_sakai.h"

#include "spwan_wall.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	コンスト定義
//=======================================

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	敵のコンストラクタ
//-------------------------------------
CEnemy::CEnemy()
{
	m_pColl = NULL;

	ZeroMemory(&m_data, sizeof(m_data));
	ZeroMemory(&m_infoTarger, sizeof(m_infoTarger));
}

//-------------------------------------
//-	敵のデストラクタ
//-------------------------------------
CEnemy::~CEnemy()
{

}

//-------------------------------------
//- 敵の初期化処理
//-------------------------------------
HRESULT CEnemy::Init(void)
{
	if (m_pColl == NULL)
	{
		// 当たり判定設定
		m_pColl = CColl::Create(
			CMgrColl::TAG_ENEMY,
			this,
			m_data.pos,
			m_data.size);
	}
	else
	{
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 敵の終了処理
//-------------------------------------
void CEnemy::Uninit(void)
{
	if (m_pColl != NULL)
	{
		// 当たり判定の終了処理
		m_pColl->Uninit();
		delete m_pColl;
		m_pColl = NULL;
	}

	// 自分自身のポインタの開放
	Release();
}

//-------------------------------------
//- 敵の更新処理
//-------------------------------------
void CEnemy::Update(void)
{
	// 位置更新処理
	UpdatePos();

	// ターゲットとの情報更新処理
	UpdateTargetPlayer();

	// 当たり判定更新処理
	UpdateCollision();
}

//-------------------------------------
//- 敵の描画処理
//-------------------------------------
void CEnemy::Draw(void)
{

}

//-------------------------------------
//- 通常敵の生成処理
//-------------------------------------
CEnemy * CEnemy::Create(void)
{
	// 通常敵の生成
	CEnemy *pEnemy = DBG_NEW CEnemy;

	// 生成の成功の有無を判定
	if (pEnemy != NULL)
	{
		// 初期化処理
		if (FAILED(pEnemy->Init()))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pEnemy == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// 通常敵のポインタを返す
	return pEnemy;
}

//-------------------------------------
//- 通常敵の接触ダメージ処理
//-------------------------------------
void CEnemy::HitDamage(int nDamage)
{
	// ダメージ処理
	Damage(nDamage);
}

//-------------------------------------
//-	敵のモデルの初期設定
//-------------------------------------
void CEnemy::SetInit(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	// データの代入
	m_data.pos = pos;										// 位置
	m_data.rot = rot;										// 向き
	m_data.size = D3DXVECTOR3(40.0f, 200.0f, 40.0f);		// サイズ

	m_data.nLife = nLife;
}

//-------------------------------------
//- 通常敵のダメージ処理
//-------------------------------------
void CEnemy::Damage(int nDamage)
{
	m_data.nLife -= nDamage;
	m_data.bHit = true;
}

//-------------------------------------
//- 通常敵の死亡処理
//-------------------------------------
bool CEnemy::Dead(void)
{
	if (GetLife() <= 0)
	{
		if (GetIsPhaseTarget())
		{
			// ターゲットの撃破数加算処理
			AddDeadNum();

			return true;
		}
	}

	return false;
}

//-------------------------------------
//- 通常敵の撃破数加算処理
//-------------------------------------
void CEnemy::AddDeadNum(void)
{
	CPhaseManager* pPhaseManager = CGame::GetPhaseManager();

	if (pPhaseManager != nullptr)
	{
		pPhaseManager->AddDeadEnemy();
	}
}

//-------------------------------------
//- プレイヤーの移動処理
//-------------------------------------
void CEnemy::UpdatePos(void)
{
	// 位置情報に移動量を加算
	m_data.pos += m_data.move;

	// 移動量を減衰
	m_data.move.x += (0.0f - m_data.move.x) * 0.3f;
	m_data.move.z += (0.0f - m_data.move.z) * 0.3f;
}


//-------------------------------------
//-	プレイヤーターゲット処理
//-------------------------------------
void CEnemy::UpdateTargetPlayer(void)
{
	// プレイヤーの情報取得
	CPlayer* pPlayer = CGame::GetPlayer();

	// プレイヤーの情報取得の成功を判定
	if (pPlayer == NULL)
	{// 失敗時

		// 追尾処理を抜ける
		return;
	}

	// ターゲットの位置
	D3DXVECTOR3 posTgt = pPlayer->GetData().pos;

	// ターゲットへの向きを算出
	m_infoTarger.rot.y = atan2f(GetPos().x - posTgt.x, GetPos().z - posTgt.z);

	// ターゲットとの距離を算出
	m_infoTarger.fLength = HelperSakai::CalculateLength(GetPos(), posTgt);
}

//-------------------------------------
//- 壁との当たり判定更新処理
//-------------------------------------
void CEnemy::UpdateCollision(void)
{
	if (m_pColl != nullptr)
	{
		// 当たり判定の情報更新処理
		m_pColl->UpdateData(
			m_data.pos,
			m_data.size);

		// 壁との当たり判定
		if (m_pColl->HitSide(CMgrColl::TAG_WALL_X, CMgrColl::EVENT_TYPE_PRESS, CMgrColl::TYPE_SXIS_X) == true)
		{
			// 移動量をなくす
			m_data.move.x = 0.0f;

			// プレイヤーのY座標移動を停止
			m_data.pos.x = m_data.posOld.x;
		}

		// 壁との当たり判定
		if (m_pColl->HitSide(CMgrColl::TAG_WALL_Z, CMgrColl::EVENT_TYPE_PRESS, CMgrColl::TYPE_SXIS_Z) == true)
		{
			// 移動量をなくす
			m_data.move.z = 0.0f;

			// プレイヤーのY座標移動を停止
			m_data.pos.z = m_data.posOld.z;
		}
	}
}

//-------------------------------------
//- プレイヤーとの当たり判定更新処理
//-------------------------------------
void CEnemy::UpdateCollisionPlayer(void)
{
	if (m_pColl != nullptr)
	{
		// 当たり判定の情報更新処理
		m_pColl->UpdateData(
			m_data.pos,
			m_data.size);

		if (m_pColl->Hit(CMgrColl::TAG_PLAYER, CMgrColl::EVENT_TYPE_PRESS) == true)
		{
			float fSpeed = -5.0f;

			if (HelperSakai::IfRangeFloat(GetTargetLength(),0.0f,10.0f))
			{
				fSpeed *= 5.0f;
			}
			else if (HelperSakai::IfRangeFloat(GetTargetLength(), 10.0f, 50.0f))
			{
				fSpeed *= 3.0f;
			}
			else if (HelperSakai::IfRangeFloat(GetTargetLength(), 50.0f, 100.0f))
			{
				fSpeed *= 2.0f;
			}

			// ターゲットから離れる
			SetRot(GetTargetRot());
			SetMoveForward(fSpeed);

		}
	}
}