
//-===============================================
//-
//-	闇の攻撃の処理[chaos_attack.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "chaos_attack.h"

#include "renderer.h"
#include "manager.h"
#include "game.h"

#include "sound.h"

#include "time_stop.h"

#include "enemy_normal.h"
#include "enemy_boss.h"

#include "hit.h"

#include "object_col.h"

#include "effect.h"
#include "particle.h"

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
//-	闇の攻撃のコンストラクタ
//-------------------------------------
CChaosAttack::CChaosAttack(int nPriority) : CObject(nPriority)
{
	ZeroMemory(&m_aCol, sizeof(m_aCol[COLLISION_NUM_MAX]));

	for (int nCount = 0; nCount < ENEMY_NORMAL_NUM_MAX; nCount++)
	{
		m_aEnemyDamageCut[nCount] = 0;
	}

	m_nEnemyBossDmageCut = 0;

	m_nDamageTime.Set(10);
}

//-------------------------------------
//-	闇の攻撃のデストラクタ
//-------------------------------------
CChaosAttack::~CChaosAttack()
{

}

//-------------------------------------
//- 闇の攻撃の初期化処理
//-------------------------------------
HRESULT CChaosAttack::Init(void)
{
	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 闇の攻撃の終了処理
//-------------------------------------
void CChaosAttack::Uninit(void)
{
	// サウンドのポインタを宣言
	CSound *pSound = CManager::GetSound();

	// サウンドの情報取得の成功を判定
	if (pSound == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 効果音BGMの再生（闇の攻撃000）
	pSound->Stop(CSound::LABEL_BGM_CHAOS_CHARGE_SHOT);

	// 自分自身のポインタの開放
	Release();
}

//-------------------------------------
//- 闇の攻撃の更新処理
//-------------------------------------
void CChaosAttack::Update(void)
{
	// 敵の当たり判定
	CollisionEnemy();

	Add();

	Sub();
}

//-------------------------------------
//- 闇の攻撃の描画処理
//-------------------------------------
void CChaosAttack::Draw(void)
{

}

//-------------------------------------
//- 闇の攻撃の設定処理
//-------------------------------------
void CChaosAttack::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nDamage)
{
	// 情報設定
	m_dataPos.Set(pos);			// 位置
	m_dataRot.Set(rot);			// 向き
	m_nDataDamage.Set(nDamage);	// ダメージ

	// 初期設定処理
	InitSet();
}

//-------------------------------------
//- 闇の攻撃の生成処理
//-------------------------------------
CChaosAttack *CChaosAttack::Create()
{
	// 闇の攻撃の生成
	CChaosAttack *pCChaosAttack = DBG_NEW CChaosAttack;

	// 生成の成功の有無を判定
	if (pCChaosAttack != NULL)
	{
		// 初期化処理
		if (FAILED(pCChaosAttack->Init()))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCChaosAttack == NULL)
	{// 失敗時

	 // 「なし」を返す
		return NULL;
	}

	// 種類を設定
	pCChaosAttack->SetType(TYPE_ENEMY);

	// 闇の攻撃のポインタを返す
	return pCChaosAttack;
}

///-------------------------------------
//- 闇の攻撃の加算処理
//-------------------------------------
void CChaosAttack::Add(void)
{
	for (int nCount = 0; nCount < COLLISION_NUM_MAX; nCount++)
	{
		// 変数宣言（情報取得）
		D3DXVECTOR3 pos = m_aCol[nCount].pos;		// 位置
		D3DXVECTOR3 size = m_aCol[nCount].size;		// 大きさ
		D3DXVECTOR3 rot = m_dataRot.Get();			// 向き

		CParticle::SetRange(
			12,
			size,
			rot,
			pos,
			D3DXVECTOR3(10.0f,10.0f,10.0f),
			D3DXVECTOR3(0.0f, 5.0f, 0.0f),
			D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
			10);
	}
}

//-------------------------------------
//- 闇の攻撃の減算処理
//-------------------------------------
void CChaosAttack::Sub(void)
{
	for (int nCutEnemy = 0; nCutEnemy < ENEMY_NORMAL_NUM_MAX; nCutEnemy++)
	{
		// 現在の番号の通常敵の取得処理
		CEnemyNormal *pEnemy = CManagerObject::GetEnemyNormal(nCutEnemy);

		// 通常敵の有無を判定
		if (pEnemy != NULL)
		{
			// 敵のダメージカウントを判定
			if (m_aEnemyDamageCut[nCutEnemy] != 0)
			{
				m_aEnemyDamageCut[nCutEnemy]--;
			}
		}
	}

	CEnemyBoss *pEnemyBoss = CManagerObject::GetEnemyBoss();

	// 通常敵の有無を判定
	if (pEnemyBoss != NULL)
	{
		// 敵のダメージカウントを判定
		if (m_nEnemyBossDmageCut != 0)
		{
			m_nEnemyBossDmageCut--;
		}
	}
}

//-------------------------------------
//- 闇の攻撃の敵との当たり判定処理
//-------------------------------------
bool CChaosAttack::CollisionEnemy(void)
{
	// 変数宣言（情報取得）
	int nDamage = m_nDataDamage.Get();		// ダメージ値

	for (int nCutEnemy = 0; nCutEnemy < ENEMY_NORMAL_NUM_MAX; nCutEnemy++)
	{
		// 現在の番号の通常敵の取得処理
		CEnemyNormal *pEnemy = CManagerObject::GetEnemyNormal(nCutEnemy);

		// 通常敵の有無を判定
		if (pEnemy != NULL)
		{
			for (int nCutCol = 0; nCutCol < COLLISION_NUM_MAX; nCutCol++)
			{
				// 変数宣言（情報取得）
				D3DXVECTOR3 pos = m_aCol[nCutCol].pos;		// 位置
				D3DXVECTOR3 size = m_aCol[nCutCol].size;	// 大きさ
				D3DXVECTOR3 rot = m_dataRot.Get();			// 向き

				// 変数宣言（情報取得）
				D3DXVECTOR3 enemyPos = pEnemy->m_dataPos.Get();		// 位置
				D3DXVECTOR3 enemySize = pEnemy->m_dataSize.Get();	// 大きさ
				D3DXVECTOR3 enemyRot = pEnemy->m_dataRot.Get();		// 向き

				// 矩形の当たり判定
				if (CHit::hitRectangleRot(pos, size,rot,enemyPos, enemySize,enemyRot) == true)
				{
					// 敵のダメージカウントを判定
					if (m_aEnemyDamageCut[nCutEnemy] == 0)
					{
						// 敵にダメージカウントを設定
						m_aEnemyDamageCut[nCutEnemy] = m_nDamageTime.Get();

						// エネミーのダメージ処理
						pEnemy->Hit(nCutEnemy, nDamage);
					}
				}
			}

		}
	}

	// ボス敵の取得処理
	CEnemyBoss *pEnemyBoss = CManagerObject::GetEnemyBoss();

	if (pEnemyBoss != NULL)
	{
		for (int nCutCol = 0; nCutCol < COLLISION_NUM_MAX; nCutCol++)
		{
			// 変数宣言（情報取得）
			D3DXVECTOR3 pos = m_aCol[nCutCol].pos;		// 位置
			D3DXVECTOR3 size = m_aCol[nCutCol].size;	// 大きさ
			D3DXVECTOR3 rot = m_dataRot.Get();			// 向き

			// 変数宣言（ボス敵の情報取得）
			D3DXVECTOR3 enemyPos = pEnemyBoss->m_dataPos.Get();		// 位置
			D3DXVECTOR3 enemySize = pEnemyBoss->m_dataSize.Get();	// 大きさ
			D3DXVECTOR3 enemyRot = pEnemyBoss->m_dataRot.Get();		// 向き

			// 矩形の当たり判定
			if (CHit::hitRectangleRot(pos, size, rot,enemyPos, enemySize, enemyRot) == true)
			{
				// 敵のダメージカウントを判定
				if (m_nEnemyBossDmageCut == 0)
				{
					// 敵にダメージカウントを設定
					m_nEnemyBossDmageCut = m_nDamageTime.Get();

					// エネミーのダメージ処理
					pEnemyBoss->Hit(nDamage);
				}
			}
		}
	}

	// 「なし」を返す
	return false;
}

//-------------------------------------
//- 闇の攻撃の初期設定処理
//-------------------------------------
void CChaosAttack::InitSet(void)
{
	// サウンドのポインタを宣言
	CSound *pSound = CManager::GetSound();

	// サウンドの情報取得の成功を判定
	if (pSound == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 効果音BGMの再生（闇の攻撃000）
	pSound->Play(CSound::LABEL_BGM_CHAOS_CHARGE_SHOT);

	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();	// 位置
	D3DXVECTOR3 rot = m_dataRot.Get();	// 向き

	float fdata0 = sinf(rot.y) * 1.0f;
	float fdata1 = cosf(rot.y) * 1.0f;

	m_aCol[0].pos = D3DXVECTOR3(pos.x + (sinf(rot.y) * -50.0f), 125.0f, pos.z + (cosf(rot.y) * -10.0f));
	m_aCol[0].size = D3DXVECTOR3(50.0f, 0.0f, 50.0f);

	m_aCol[1].pos = D3DXVECTOR3(pos.x + (sinf(rot.y) * -100.0f), 125.0f, pos.z + (cosf(rot.y) * -100.0f));
	m_aCol[1].size = D3DXVECTOR3(100.0f, 0.0f, 50.0f);

	m_aCol[2].pos = D3DXVECTOR3(pos.x + (sinf(rot.y) * -200.0f), 125.0f, pos.z + (cosf(rot.y) * -200.0f));
	m_aCol[2].size = D3DXVECTOR3(150.0f, 0.0f, 50.0f);

	m_aCol[3].pos = D3DXVECTOR3(pos.x + (sinf(rot.y) * -300.0f), 125.0f, pos.z + (cosf(rot.y) * -300.0f));
	m_aCol[3].size = D3DXVECTOR3(200.0f, 0.0f, 50.0f);
}