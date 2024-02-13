
//-===============================================
//-
//-	出現壁処理[spwan_wall.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "spwan_wall.h"

#include "renderer.h"
#include "manager.h"

#include "game.h"

#include "manager_texture.h"

#include "obj_3d_wall.h"
#include "coll.h"

#include "model.h"
#include "motion.h"

#include "enemy_minion.h"
#include "enemy_boss.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	コンスト定義
//=======================================

// 出現壁のテクスチャ
const char* DataTexture[] =
{
	nullptr,											// テクスチャなし
	"data\\TEXTURE\\SpwanWall\\SpawnWall000.png",		// 出現壁のテクスチャ
	"data\\TEXTURE\\SpwanWall\\BlockWall000.jpg",		// 封鎖壁のテクスチャ
};

// フェーズ2の敵の位置
const D3DXVECTOR3 ENEMY_POS_PHASE_TWO[3] =
{
	D3DXVECTOR3(-300.0f,0.0f,300.0f),
	D3DXVECTOR3(0.0f,0.0f,400.0f),
	D3DXVECTOR3(500.0f,0.0f,700.0f),
};

//-======================================
//-	静的変数宣言
//-======================================

int CSpwanWall::m_nTextureNldx[TEX_MAX] = {};

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CSpwanWall::CSpwanWall(int nPriority) : CObject(nPriority)
{
	ZeroMemory(&m_info, sizeof(m_info));
	ZeroMemory(&m_infoVisual, sizeof(m_infoVisual));
	ZeroMemory(&m_infoAttach, sizeof(m_infoAttach));
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CSpwanWall::~CSpwanWall()
{

}

//-------------------------------------
//- 背景のテクスチャの読み込み
//-------------------------------------
HRESULT CSpwanWall::Load(void)
{
	// 情報取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	CManagerTexture* pManagerTexture = CManager::GetInstance()->GetManagerTexture();

	// 情報取得の成功を判定
	if (pDevice == nullptr ||
		pManagerTexture == nullptr)
	{// 失敗時

		// 初期化処理を抜ける
		return E_FAIL;
	}

	// テクスチャ設定
	for (int nCount = 0; nCount < TEX_MAX; nCount++)
	{
		// テクスチャ番号の取得（テクスチャの割当）
		m_nTextureNldx[nCount] = pManagerTexture->Regist(DataTexture[nCount]);

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
//- 背景の読み込んだテクスチャの破棄
//-------------------------------------
void CSpwanWall::Unload(void)
{

}
//-------------------------------------
//- 初期化処理（3Dオブジェクト設定）
//-------------------------------------
HRESULT CSpwanWall::Init(void)
{
	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 終了処理
//-------------------------------------
void CSpwanWall::Uninit(void)
{
	if (m_infoVisual.pObj3dWall != NULL)
	{
		// 当たり判定の終了処理
		m_infoVisual.pObj3dWall->Uninit();
		m_infoVisual.pObj3dWall = NULL;
	}

	if (m_infoAttach.pColl != NULL)
	{
		// 当たり判定の終了処理
		m_infoAttach.pColl->Uninit();

		delete m_infoAttach.pColl;
		m_infoAttach.pColl = NULL;
	}

	// 開放処理
	Release();
}

//-------------------------------------
//- 更新処理
//-------------------------------------
void CSpwanWall::Update(void)
{
	if (m_infoAttach.pColl != nullptr)
	{
		// 当たり判定の情報更新処理
		m_infoAttach.pColl->UpdateData(
			GetPos(),
			GetSize());
	}

	// 種類の更新処理
	UpdateType();
}

//-------------------------------------
//- 描画処理
//-------------------------------------
void CSpwanWall::Draw(void)
{

}

//-------------------------------------
//- 接触処理
//-------------------------------------
void CSpwanWall::Hit(void)
{
	// 敵の生成処理
	SetPhase();

	// ターゲット数の設定処理
	CPhaseManager* pPhaseManager = CGame::GetPhaseManager();

	if (pPhaseManager != nullptr)
	{
		pPhaseManager->SetTargetCompNum(m_info.nNumTarget);
	}
	
	// 終了処理
	Uninit();
}

//-------------------------------------
//-	初期設定処理
//-------------------------------------
void CSpwanWall::InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR color, D3DXVECTOR2 texPos)
{
	SetPos(pos);
	SetSize(size);
	SetRot(rot);
	SetColor(color);
	SetTexPos(texPos);

	if (m_infoVisual.pObj3dWall == nullptr)
	{
		// 壁の生成・設定処理
		m_infoVisual.pObj3dWall = CObj3dWall::Create(CObj3dWall::TEX_NULL);
		m_infoVisual.pObj3dWall->InitSet(m_info.pos, m_info.size, m_info.rot, m_info.color, m_info.texPos);
	}

	if (m_infoAttach.pColl == nullptr)
	{
		// 当たり判定設定
		m_infoAttach.pColl = CColl::Create(
			CMgrColl::TAG_SPAWN_ENEMY_WALL,
			this,
			m_info.pos,
			m_info.size);
	}

	// 種類の更新
	UpdateType();
}

//-------------------------------------
//- 生成処理
//-------------------------------------
CSpwanWall* CSpwanWall::Create(void)
{
	// ポインタを宣言
	CSpwanWall* pCSpwanWall = DBG_NEW CSpwanWall(1);

	// 生成の成功の有無を判定
	if (pCSpwanWall != NULL)
	{
		// 初期化処理
		if (FAILED(pCSpwanWall->Init()))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCSpwanWall == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// ポインタを返す
	return pCSpwanWall;
}

//-------------------------------------
//- 種類設定処理
//-------------------------------------
void CSpwanWall::UpdateType(void)
{
	// フェーズ管理を取得
	CPhaseManager* pPhaseManager = CGame::GetPhaseManager();

	if (pPhaseManager != nullptr)
	{
		if (m_info.typePhase == pPhaseManager->GetTypePhase())
		{
			if (m_infoVisual.pObj3dWall != nullptr)
			{
				m_infoVisual.pObj3dWall->BindTexture(m_nTextureNldx[TEX_SPWAN_000]);

				CColl::Data data = m_infoVisual.pObj3dWall->GetColl()->GetData();
				data.tag = CMgrColl::TAG_NONE;
				m_infoVisual.pObj3dWall->GetColl()->SetData(data);
			}
		}
		else
		{
			if (m_infoVisual.pObj3dWall != nullptr)
			{
				// 封鎖のテクスチャを設定
				m_infoVisual.pObj3dWall->BindTexture(m_nTextureNldx[TEX_BLOCK_000]);
			}
		}

	}
}

//-------------------------------------
//- フェーズ1の敵の生成処理
//-------------------------------------
void CSpwanWall::SetPhase(void)
{
	// フェーズ1の生成処理
	switch (m_info.typePhase)
	{
	case CPhaseManager::TYPE_PHASE_ONE:

		SpwanEnemyPhaseOne();

		break;

	case CPhaseManager::TYPE_PHASE_TWO:

		SpwanEnemyPhaseTwo();

		break;

	case CPhaseManager::TYPE_PHASE_THREE:

		SpwanEnemyPhaseThree();

		break;
	}
}
//-------------------------------------
//- フェーズ1の敵の生成処理
//-------------------------------------
void CSpwanWall::SpwanEnemyPhaseOne(void)
{
	CEnemyMinion* pEnemy = CEnemyMinion::Create(
		CModel::MODEL_TYPE_ALIEN_000,
		CMotion::MOTION_TYPE_ALIEN_000);

	pEnemy->SetInit(
		D3DXVECTOR3(m_info.pos.x, 0.0f, m_info.pos.z) + D3DXVECTOR3(0.0f, 0.0f, 500.0f),
		D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
		(16 * 3),
		(16 * 3));

	pEnemy->SetIsPhaseTarget(true);

	m_info.nNumTarget++;

}

//-------------------------------------
//- フェーズ2の敵の生成処理
//-------------------------------------
void CSpwanWall::SpwanEnemyPhaseTwo(void)
{
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		CEnemyMinion* pEnemy = CEnemyMinion::Create(
			CModel::MODEL_TYPE_ALIEN_000,
			CMotion::MOTION_TYPE_ALIEN_000);

		pEnemy->SetInit(
			D3DXVECTOR3(m_info.pos.x, 0.0f, m_info.pos.z) + ENEMY_POS_PHASE_TWO[nCnt],
			D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
			(9 * 3),
			(9 * 3));

		pEnemy->SetIsPhaseTarget(true);

		m_info.nNumTarget++;
	}
}

//-------------------------------------
//- フェーズ3の敵の生成処理
//-------------------------------------
void CSpwanWall::SpwanEnemyPhaseThree(void)
{
	CEnemyBoss* pEnemyBoss = CEnemyBoss::Create(
		CModel::MODEL_TYPE_ENEMY_BOSS,
		CMotion::MOTION_TYPE_ENEMY_BOSS);

	pEnemyBoss->SetInit(
		D3DXVECTOR3(m_info.pos.x, 0.0f, m_info.pos.z) + D3DXVECTOR3(0.0f, 0.0f, 500.0f),
		D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
		(16 * 7));

	pEnemyBoss->SetIsPhaseTarget(true);

	m_info.nNumTarget++;
}