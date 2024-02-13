
//-===============================================
//-
//-	爆発弾の処理[bullet_bomb.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "bullet_bomb.h"

#include "renderer.h"
#include "manager.h"

#include "time_stop.h"

#include "effect.h"

#include "manager_object.h"
#include "objectx_none.h"
#include "event_object.h"

#include "enemy_normal.h"
#include "enemy_boss.h"

#include "hit.h"

//-======================================
//-	マクロ定義
//-======================================

#define ENEMY_BOSS_NUM	(-1)		// ボス用の番号
#define BLAST_DAMAGE	(5)			// 爆風ダメージ
#define BLAST_RANGE		(800.0f)	// 爆風範囲

#define BLT_BOMB_EFCT_SIZE	(10.0f)									// 爆発弾のエフェクトのサイズ
#define BLT_BOMB_EFCT_LIFE	(30)									// 爆発弾のエフェクトの体力
#define BLT_BOMB_EFCT_COLOR	(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f))		// 爆発弾のエフェクトの色

//=======================================
//= コンスト定義
//=======================================

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	爆発弾のコンストラクタ
//-------------------------------------
CBulletBomb::CBulletBomb(int nPriority) : CBullet(nPriority)
{

}

//-------------------------------------
//-	爆発弾のデストラクタ
//-------------------------------------
CBulletBomb::~CBulletBomb()
{

}

//-------------------------------------
//- 爆発弾の初期化処理
//-------------------------------------
HRESULT CBulletBomb::Init(TEX tex)
{
	// 弾の初期化
	CBullet::Init(tex);

	// 初期設定処理
	InitSet();

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 爆発弾の終了処理
//-------------------------------------
void CBulletBomb::Uninit(void)
{
	// 弾の終了
	CBullet::Uninit();
}

//-------------------------------------
//- 爆発弾の更新処理
//-------------------------------------
void CBulletBomb::Update(void)
{
	// 移動処理
	Move();

	// 加算処理
	Add();

	// 敵との当たり判定処理
	if (CollisionEnemy() == true ||
		CollisionObject() == true)
	{
		return;
	}

	// 減算処理
	if (Sub() == true)
	{
		return;
	}

	// ビルボードオブジェクトの更新処理
	CObjectBillboard::Update();
}

//-------------------------------------
//- 爆発弾の描画処理
//-------------------------------------
void CBulletBomb::Draw(void)
{
	// デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();

	// デバイスの情報取得の成功を判定
	if (pRenderer == NULL)
	{// 失敗時

		// 初期化処理を抜ける
		return;
	}

	// Zテストの設定
	pRenderer->SetZTest(true);

	// アルファテストの設定
	pRenderer->SetAlphaTest(true);

	// 爆発弾の描画処理
	CBullet::Draw();

	// Zテストの解除
	pRenderer->SetZTest(false);

	// アルファテストの解除
	pRenderer->SetAlphaTest(false);
}

//-------------------------------------
//- 爆発弾の生成処理
//-------------------------------------
CBulletBomb *CBulletBomb::Create(TEX tex)
{
	// 爆発弾の生成
	CBulletBomb *pCBulletBomb = DBG_NEW CBulletBomb(5);

	// 生成の成功の有無を判定
	if (pCBulletBomb != NULL)
	{
		// 初期化処理
		if (FAILED(pCBulletBomb->Init(tex)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCBulletBomb == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// 種類を設定
	pCBulletBomb->SetType(TYPE_BULLET);

	// 爆発弾のポインタを返す
	return pCBulletBomb;
}

//-------------------------------------
//- 爆発弾の初期設定処理
//-------------------------------------
void CBulletBomb::InitSet(void)
{
	m_nDataBlastDamage.Set(BLAST_DAMAGE);	// 爆風ダメージ
}

//-------------------------------------
//- 爆発弾の移動処理
//-------------------------------------
void CBulletBomb::Move(void)
{
	// 時間管理の情報を取得
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// 時間管理取得の有無を判定
	if (pManagerTime == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 変数を宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();		// 位置情報
	D3DXVECTOR3 move = m_dataMove.Get();	// 移動量

	// 時間倍率の計算
	D3DXVECTOR3 moveTime = pManagerTime->CalRate(move);

	// 位置を更新
	pos += moveTime;

	// 情報更新
	m_dataPos.Set(pos);		// 位置情報
	m_dataMove.Set(move);	// 移動量
}

//-------------------------------------
//- 爆発弾の加算処理
//-------------------------------------
void CBulletBomb::Add(void)
{
	// 時間管理の情報を取得
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// 時間管理取得の有無を判定
	if (pManagerTime == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 整数カウントの有無を判定
	if (pManagerTime->m_bDataIntCount.Get() == true)
	{
		// 変数を宣言（情報取得）
		D3DXVECTOR3 pos = m_dataPos.Get();		// 位置情報

		// エフェクトの生成
		CEffect *pEffect = CEffect::Create(CEffect::TEX_NORMAL_000);

		// エフェクトの有無を判定
		if (pEffect != NULL)
		{
			// 位置情報を設定
			pEffect->m_dataPos.Set(pos);

			// 大きさを設定
			pEffect->m_dataSize.Set(D3DXVECTOR3(BLT_BOMB_EFCT_SIZE, BLT_BOMB_EFCT_SIZE, 0.0f));

			// 移動量を設定
			pEffect->m_dataMove.Set();

			// 色を設定
			pEffect->m_dataColor.Set(BLT_BOMB_EFCT_COLOR);

			// エフェクトの設定処理
			pEffect->m_nDataLife.Set(BLT_BOMB_EFCT_LIFE);
		}
	}
}

//-------------------------------------
//- 爆発弾の減算処理
//-------------------------------------
bool CBulletBomb::Sub(void)
{
	// 時間管理の情報を取得
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// 時間管理取得の有無を判定
	if (pManagerTime == NULL)
	{
		// 処理を抜ける
		return false;
	}

	// 変数宣言（情報取得）
	int nLife = m_nDataLife.Get();	// 体力

	// 整数カウントの有無を判定
	if (pManagerTime->m_bDataIntCount.Get() == true)
	{
		// 体力を減らす
		nLife--;
	}

	// 体力の判定
	if (nLife <= 0)
	{
		// 終了処理
		Uninit();

		// 成功を返す
		return true;
	}

	// 情報を更新
	m_nDataLife.Set(nLife);		// 体力

	// 失敗を返す
	return false;
}

//-------------------------------------
//- 爆発弾の敵との当たり判定処理
//-------------------------------------
bool CBulletBomb::CollisionEnemy(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();		// 位置
	D3DXVECTOR3 size = m_dataSize.Get();	// 大きさ

	int nDamage = m_nDataDamage.Get();		// ダメージ値

	for (int nCutEnemy = 0; nCutEnemy < ENEMY_NORMAL_NUM_MAX; nCutEnemy++)
	{
		// 現在の番号の通常敵の取得処理
		CEnemyNormal *pEnemy = CManagerObject::GetEnemyNormal(nCutEnemy);

		// 通常敵の有無を判定
		if (pEnemy != NULL)
		{
			// 変数宣言（情報取得）
			D3DXVECTOR3 enemyPos = pEnemy->m_dataPos.Get();		// 位置
			D3DXVECTOR3 enemySize = pEnemy->m_dataSize.Get();	// 大きさ

			// 矩形の当たり判定
			if (CHit::hitRectangle(pos, size, enemyPos, enemySize) == true)
			{
				// エネミーのダメージ処理
				pEnemy->Hit(nCutEnemy, nDamage);

				// 爆風ダメージ
				CollisionEnemyBlast(nCutEnemy);

				// 自分の終了処理
				Uninit();

				// 成功を返す
				return true;
			}

		}
	}

	// ボス敵の取得処理
	CEnemyBoss *pEnemyBoss = CManagerObject::GetEnemyBoss();

	if (pEnemyBoss != NULL)
	{
		// 変数宣言（情報取得）
		D3DXVECTOR3 enemyPos = pEnemyBoss->m_dataPos.Get();		// 位置
		D3DXVECTOR3 enemySize = pEnemyBoss->m_dataSize.Get();	// 大きさ

		// 矩形の当たり判定
		if (CHit::hitRectangle(pos, size, enemyPos, enemySize) == true)
		{
			// エネミーのダメージ処理
			pEnemyBoss->Hit(nDamage);

			// 爆風ダメージ
			CollisionEnemyBlast(ENEMY_BOSS_NUM);

			// 自分の終了処理
			Uninit();

			// 成功を返す
			return true;
		}

	}

	// 情報更新
	m_dataPos.Set(pos);				// 位置
	m_dataSize.Set(size);			// 大きさ

	m_nDataDamage.Set(nDamage);		// ダメージ値

	// 「なし」を返す
	return false;
}

//-------------------------------------
//- 爆発弾の爆風と敵の当たり判定処理
//-------------------------------------
void CBulletBomb::CollisionEnemyBlast(int nRawEmyNum)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();		// 位置
	D3DXVECTOR3 size = m_dataSize.Get();	// 大きさ

	int nBlastDamage = m_nDataBlastDamage.Get();		// 爆風ダメージ値

	for (int nCutEnemy = 0; nCutEnemy < ENEMY_NORMAL_NUM_MAX; nCutEnemy++)
	{
		// 弾の当たった敵の番号を判定
		if (nCutEnemy != nRawEmyNum)
		{
			CEnemyNormal *pEnemy = CManagerObject::GetEnemyNormal(nCutEnemy);

			if (pEnemy != NULL)
			{
				// 変数宣言（情報取得）
				D3DXVECTOR3 enemyPos = pEnemy->m_dataPos.Get();		// 位置
				D3DXVECTOR3 enemySize = pEnemy->m_dataSize.Get();	// 大きさ

				D3DXVECTOR3 blastSize = D3DXVECTOR3(BLAST_RANGE, 0.0f, BLAST_RANGE);	// 爆風の範囲

				// 矩形の当たり判定
				if (CHit::hitRectangle(pos, size + blastSize, enemyPos, enemySize) == true)
				{
					// エネミーのダメージ処理
					pEnemy->Hit(nCutEnemy, nBlastDamage);
				}

			}
		}
	}

	// 弾の当たった敵の番号を判定（-1 = boss）
	if (ENEMY_BOSS_NUM != nRawEmyNum)
	{
		CEnemyBoss *pEnemyBoss = CManagerObject::GetEnemyBoss();

		if (pEnemyBoss != NULL)
		{
			// 変数宣言（情報取得）
			D3DXVECTOR3 enemyPos = pEnemyBoss->m_dataPos.Get();		// 位置
			D3DXVECTOR3 enemySize = pEnemyBoss->m_dataSize.Get();	// 大きさ

			D3DXVECTOR3 blastSize = D3DXVECTOR3(BLAST_RANGE, 0.0f, BLAST_RANGE);	// 爆風の範囲

			// 矩形の当たり判定
			if (CHit::hitRectangle(pos, size + blastSize, enemyPos, enemySize) == true)
			{
				// エネミーのダメージ処理
				pEnemyBoss->Hit(nBlastDamage);
			}

		}
	}
}

//-------------------------------------
//- 爆発弾のオブジェクトとの当たり判定
//-------------------------------------
bool CBulletBomb::CollisionObject(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();			// 位置
	D3DXVECTOR3 size = m_dataSize.Get();		// 大きさ
	D3DXVECTOR3 move = m_dataMove.Get();		// 移動量

	for (int nCutObjectNone = 0; nCutObjectNone < OBJECTX_NONE_NUM_MAX; nCutObjectNone++)
	{
		// イベントオブジェクトの情報を取得
		CObjectXNone *pObjectNone = CManagerObject::GetObjectNone(nCutObjectNone);

		// イベントオブジェクトの有無を判定
		if (pObjectNone != NULL)
		{
			// 変数宣言（情報取得）
			D3DXVECTOR3 evtObjPos = pObjectNone->m_dataPos.Get();	// 位置
			D3DXVECTOR3 evtObjSize = pObjectNone->m_dataSize.Get();	// 大きさ

			// 矩形の当たり判定
			if (CHit::hitRectangle(pos, size, evtObjPos, evtObjSize) == true)
			{
				// 自分の終了処理
				Uninit();

				// 成功を返す
				return true;
			}
		}
	}

	for (int nCutEventObject = 0; nCutEventObject < EVENT_OBJECT_NUM_MAX; nCutEventObject++)
	{
		// イベントオブジェクトの情報を取得
		CEventObject *pEventObject = CManagerObject::GetEventObject(nCutEventObject);

		// イベントオブジェクトの有無を判定
		if (pEventObject != NULL)
		{
			// 変数宣言（情報取得）
			D3DXVECTOR3 evtObjPos = pEventObject->m_dataPos.Get();		// 位置
			D3DXVECTOR3 evtObjSize = pEventObject->m_dataSize.Get();	// 大きさ

			// 矩形の当たり判定
			if (CHit::hitRectangle(pos, size, evtObjPos, evtObjSize) == true)
			{
				// 自分の終了処理
				Uninit();

				// 成功を返す
				return true;
			}
		}
	}

	return false;
}