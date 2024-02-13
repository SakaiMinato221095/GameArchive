
//================================================
//=
//=	当たり判定の処理[coll.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "coll.h"

#include "manager.h"

#include "box_field.h"
#include "box_wall.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//=	コンスト定義
//=======================================

//=======================================
//=	静的変数宣言
//=======================================

//-------------------------------------
//-	当たり判定のコンストラクタ
//-------------------------------------
CColl::CColl()
{
	ZeroMemory(&m_data, sizeof(m_data));

	// 番号の初期値を代入
	m_data.nNldx = -1;

	// 接触相手番号の初期値を代入
	for (int nCnt = 0; nCnt < COLLSION_NUM_MAX; nCnt++)
	{
		m_data.hitData[nCnt].nNldx = -1;
	}
}

//-------------------------------------
//-	当たり判定のデストラクタ
//-------------------------------------
CColl::~CColl()
{

}

//-------------------------------------
//- 当たり判定の初期化処理
//-------------------------------------
HRESULT CColl::Init(CMgrColl::TAG tag, CObject* pObj, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 当たり判定のポインタ取得
	CMgrColl *pMgrColl = CManager::GetInstance()->GetMgrColl();

	// 当たり判定の有無を判定
	if (pMgrColl == NULL)
	{
		// 処理を抜ける
		return false;
	}

	// 当たり判定の床を生成
	m_data.dataVisual.pField = CBoxField::Create();

	if (m_data.dataVisual.pField != nullptr)
	{
		m_data.dataVisual.pField->InitSet(
			pos + D3DXVECTOR3(0.0f, 3.0f, 0.0f),
			size,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			D3DXVECTOR2(1.0f, 1.0f));

		m_data.dataVisual.pField->SetIsDrawStop(true);
	}

	// 当たり判定の壁を生成
	m_data.dataVisual.pWall = CBoxWall::Create();

	if (m_data.dataVisual.pWall != nullptr)
	{
		m_data.dataVisual.pWall->InitSet(
			pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			size,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			D3DXVECTOR2(1.0f, 1.0f));

		m_data.dataVisual.pWall->SetIsDrawStop(true);
	}

	// 当たり判定管理に設定処理
	m_data.nNldx = pMgrColl->Set(this);

	// 初期設定処理
	InitSet(tag, pObj,pos, size);

	return S_OK;
}

//-------------------------------------
//- 当たり判定の終了処理
//-------------------------------------
void CColl::Uninit(void)
{
	// 当たり判定のポインタ取得
	CMgrColl *pMgrColl = CManager::GetInstance()->GetMgrColl();

	// 当たり判定の有無を判定
	if (pMgrColl == NULL)
	{
		// 処理を抜ける
		return;
	}

	if (m_data.dataVisual.pField != nullptr)
	{
		m_data.dataVisual.pField->Uninit();
		m_data.dataVisual.pField = nullptr;
	}

	if (m_data.dataVisual.pWall != nullptr)
	{
		m_data.dataVisual.pWall->Uninit();
		m_data.dataVisual.pWall = nullptr;
	}

	// 当たり判定管理に設定処理
	pMgrColl->Reset(m_data.nNldx);
}

//-------------------------------------
//- 当たり判定の更新処理
//-------------------------------------
void CColl::Update(void)
{

}

//-------------------------------------
//- 当たり判定の描画処理
//-------------------------------------
void CColl::Draw(void)
{
}


//-------------------------------------
//- 当たり判定の生成処理
//-------------------------------------
CColl* CColl::Create(CMgrColl::TAG tag, CObject* pObj, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 当たり判定の生成
	CColl *pCollision = DBG_NEW CColl;

	// 生成の成功の有無を判定
	if (pCollision != NULL)
	{
		// 初期化処理
		if (FAILED(pCollision->Init(tag, pObj,pos,size)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCollision == NULL)
	{// 失敗時

	 // 「なし」を返す
		return NULL;
	}

	// 当たり判定のポインタを返す
	return pCollision;
}

//-------------------------------------
//- 当たり判定の接触処理（矩形）
//-------------------------------------
bool CColl::Hit(CMgrColl::TAG hitTag,CMgrColl::EVENT_TYPE eventType)
{
	// 当たり判定のポインタ取得
	CMgrColl *pMgrColl = CManager::GetInstance()->GetMgrColl();		

	// 当たり判定の有無を判定
	if (pMgrColl == NULL)
	{
		// 処理を抜ける
		return false;
	}

	// 変数宣言
	bool bHitTgt = false;	// 目的の接触の有無

	// 当たり判定管理の接触処理
	bHitTgt = pMgrColl->Hit(m_data.nNldx, hitTag, eventType);

	return bHitTgt;
}

//-------------------------------------
//- 当たり判定の接触処理（矩形の辺）
//-------------------------------------
bool CColl::HitSide(CMgrColl::TAG hitTag,CMgrColl::EVENT_TYPE eventType, CMgrColl::TYPE_SXIS typeSxis)
{
	// 当たり判定のポインタ取得
	CMgrColl* pMgrColl = CManager::GetInstance()->GetMgrColl();

	// 当たり判定の有無を判定
	if (pMgrColl == NULL)
	{
		// 処理を抜ける
		return false;
	}

	// 変数宣言
	bool bHitTgt = false;	// 目的の接触の有無

	// 当たり判定管理の接触処理
	bHitTgt = pMgrColl->Hit(m_data.nNldx, hitTag, eventType);

	return bHitTgt;
}

//-------------------------------------
//- 当たり判定の接触情報の設定処理
//-------------------------------------
void CColl::SetHitData(HitData data)
{
	// 変数宣言（情報取得）
	int nHitNumMax = m_data.nHitNldxMax;			// 現在の最大接触数
	int nHitNumMaxTemp = m_data.nHitNldxMaxTemp;	// 一時的な最大接触数

	for (int nCount = 0; nCount < nHitNumMax; nCount++)
	{
		if (data.nNldx == m_data.hitData[nCount].nNldx)
		{
			m_data.nHitNldxMax--;

			break;
		}
	}

	// 接触相手の当たり判定情報を代入
	m_data.hitData[nHitNumMax] = data;
	m_data.hitDataTemp[nHitNumMaxTemp] = data;

	// 最大接触数を加算
	m_data.nHitNldxMax++;
	m_data.nHitNldxMaxTemp++;
}

//-------------------------------------
//- 当たり判定の接触情報のリセット処理
//-------------------------------------
void CColl::ResetHitData(void)
{
	// 変数宣言（情報取得）
	int nHitNum = m_data.nHitNldxMax;	// 現在の最大接触数

	for (int nCount = 0; nCount < nHitNum; nCount++)
	{
		// 接触番号の初期化
		m_data.hitData[nHitNum].nNldx = -1;
	}

	// 接触最大数の初期化
	m_data.nHitNldxMax = 0;
}

//-------------------------------------
//- 当たり判定の見た目の描画設定
//-------------------------------------
void CColl::SetIsVisualDrawStop(bool bDrawStop)
{
	if (m_data.dataVisual.pField != nullptr)
	{
		m_data.dataVisual.pField->SetIsDrawStop(bDrawStop);
	}

	if (m_data.dataVisual.pWall != nullptr)
	{
		m_data.dataVisual.pWall->SetIsDrawStop(bDrawStop);
	}
}

//-------------------------------------
//- 当たり判定の見た目設定処理
//-------------------------------------
void CColl::SetDataVisual(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	if (m_data.dataVisual.pField != nullptr)
	{
		CObject3d::VtxData vtxData = m_data.dataVisual.pField->GetVtxData();
		vtxData.pos = pos + D3DXVECTOR3(0.0f, size.y * 0.5f, 0.0f);
		vtxData.size = size;
		m_data.dataVisual.pField->SetVtxData(vtxData);
	}

	if (m_data.dataVisual.pWall != nullptr)
	{
		CObject3d::VtxData vtxData = m_data.dataVisual.pWall->GetVtxData();
		vtxData.pos = pos;
		vtxData.size = size;
		m_data.dataVisual.pWall->SetVtxData(vtxData);
	}
}

//-------------------------------------
//- 当たり判定の初期設定処理
//-------------------------------------
void CColl::InitSet(CMgrColl::TAG tag, CObject* pObj,D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_data.tag = tag;
	m_data.pObj = pObj;
	m_data.pos = pos;
	m_data.size = size;
}

