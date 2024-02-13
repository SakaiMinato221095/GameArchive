
//-===============================================
//-
//-	攻撃の処理[attack.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "bullet.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"
#include "manager_object.h"
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

#define BULLET_EFFECT_SIZE	(10.0f)									// 弾のエフェクトの大きさ
#define BULLET_EFFECT_LIFE	(30)									// 弾のエフェクトの体力
#define BULLET_EFFECT_COLOR	(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f))		// 弾のエフェクトの色

//=======================================
//= コンスト定義
//=======================================

// 弾テクスチャのコンスト定義
const char *pTextureBullet[] =
{
	"data\\TEXTURE\\BulletRed.png",		// 赤弾_000のテクスチャ
	"data\\TEXTURE\\BulletBlue.png",	// 青弾_000のテクスチャ
};

//-======================================
//-	静的変数宣言
//-======================================

int CBullet::m_nTextureNldx[TEX_MAX] = {};	// テクスチャ
										
//-------------------------------------
//-	弾のコンストラクタ
//-------------------------------------
CBullet::CBullet(int nPriority) : CObjectBillboard(nPriority)
{

}

//-------------------------------------
//-	弾のデストラクタ
//-------------------------------------
CBullet::~CBullet()
{

}

//-------------------------------------
//- 弾のテクスチャの読み込み
//-------------------------------------
HRESULT CBullet::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// デバイスの情報取得の成功を判定
	if (pDevice == NULL)
	{// 失敗時

	 // 初期化処理を抜ける
		return E_FAIL;
	}

	// テクスチャ管理の生成
	CManagerTexture *pManagerTexture = CManager::GetManagerTexture();

	// テクスチャ管理の有無を判定
	if (pManagerTexture == NULL)
	{
		// 初期化処理を抜ける
		return E_FAIL;
	}

	// テクスチャ設定
	for (int nCount = 0; nCount < TEX_MAX; nCount++)
	{
		// テクスチャ番号の取得（テクスチャの割当）
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureBullet[nCount]);

		// テクスチャの読み込み成功の有無を確認
		if (m_nTextureNldx[nCount] == -1)
		{
			// 失敗時に初期化処理を抜ける
			return E_FAIL;
		}
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 弾の読み込んだテクスチャの破棄
//-------------------------------------
void CBullet::Unload(void)
{

}

//-------------------------------------
//- 弾の初期化処理
//-------------------------------------
HRESULT CBullet::Init(TEX tex)
{
	// 時間管理の情報を取得
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// 時間管理取得の有無を判定
	if (pManagerTime == NULL)
	{
		// 処理を抜ける
		return E_FAIL;
	}

	// テクスチャ割当
	BindTexture(m_nTextureNldx[tex]);

	// ビルボードオブジェクトの初期化
	CObjectBillboard::Init();

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 弾の終了処理
//-------------------------------------
void CBullet::Uninit(void)
{
	// ビルボードオブジェクトの終了
	CObjectBillboard::Uninit();
}

//-------------------------------------
//- 弾の更新処理
//-------------------------------------
void CBullet::Update(void)
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
//- 弾の描画処理
//-------------------------------------
void CBullet::Draw(void)
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

	// 弾の描画処理
	CObjectBillboard::Draw();

	// Zテストの解除
	pRenderer->SetZTest(false);

	// アルファテストの解除
	pRenderer->SetAlphaTest(false);
}

//-------------------------------------
//- 弾の生成処理
//-------------------------------------
CBullet *CBullet::Create(TEX tex)
{
	// 弾の生成
	CBullet *pCBullet = DBG_NEW CBullet(5);

	// 生成の成功の有無を判定
	if (pCBullet != NULL)
	{
		// 初期化処理
		if (FAILED(pCBullet->Init(tex)))
		{// 失敗時

		 // 「なし」を返す
			return NULL;
		}
	}
	else if (pCBullet == NULL)
	{// 失敗時

	 // 「なし」を返す
		return NULL;
	}

	// 種類を設定
	pCBullet->SetType(TYPE_BULLET);

	// 弾のポインタを返す
	return pCBullet;
}

//-------------------------------------
//- 弾の移動処理
//-------------------------------------
void CBullet::Move(void)
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
//- 弾の加算処理
//-------------------------------------
void CBullet::Add(void)
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
			pEffect->m_dataSize.Set(D3DXVECTOR3(BULLET_EFFECT_SIZE, BULLET_EFFECT_SIZE, 0.0f));

			// 移動量を設定
			pEffect->m_dataMove.Set();

			// 色を設定
			pEffect->m_dataColor.Set(BULLET_EFFECT_COLOR);

			// エフェクトの設定処理
			pEffect->m_nDataLife.Set(BULLET_EFFECT_LIFE);
		}
	}
}

//-------------------------------------
//- 弾の減算処理
//-------------------------------------
bool CBullet::Sub(void)
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
//- 敵との当たり判定処理
//-------------------------------------
bool CBullet::CollisionEnemy(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();		// 位置
	D3DXVECTOR3 size = m_dataSize.Get();	// 大きさ

	int nDamage = m_nDataDamage.Get();		// ダメージ値

	for (int nCutEnemy = 0; nCutEnemy < ENEMY_NORMAL_NUM_MAX; nCutEnemy++)
	{
		CEnemyNormal *pEnemy = CManagerObject::GetEnemyNormal(nCutEnemy);

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

				// 自分の終了処理
				Uninit();

				// 成功を返す
				return true;
			}

		}
	}

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
//- 弾のオブジェクトとの当たり判定
//-------------------------------------
bool CBullet::CollisionObject(void)
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