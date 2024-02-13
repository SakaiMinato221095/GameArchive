
//================================================
//=
//=	当たり判定管理の処理[mgr_coll.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "mgr_coll.h"

#include "coll.h"

#include "object.h"

#include "helper_sakai.h"

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
//-	当たり判定管理のコンストラクタ
//-------------------------------------
CMgrColl::CMgrColl()
{
	ZeroMemory(&m_apColl, sizeof(m_apColl));
	m_nNldxMax = 0;
}

//-------------------------------------
//-	当たり判定管理のデストラクタ
//-------------------------------------
CMgrColl::~CMgrColl()
{

}

//-------------------------------------
//- 当たり判定管理の初期化処理
//-------------------------------------
HRESULT CMgrColl::Init(void)
{
	return S_OK;
}

//-------------------------------------
//- 当たり判定管理の終了処理
//-------------------------------------
void CMgrColl::Uninit(void)
{

}

//-------------------------------------
//- 当たり判定管理の更新処理
//-------------------------------------
void CMgrColl::Update(void)
{
}

//-------------------------------------
//- 当たり判定管理の描画処理
//-------------------------------------
void CMgrColl::Draw(void)
{
}

//-------------------------------------
//- 当たり判定管理の生成処理
//-------------------------------------
CMgrColl * CMgrColl::Create(void)
{
	// 当たり判定管理の生成
	CMgrColl *pCollision = DBG_NEW CMgrColl;

	// 生成の成功の有無を判定
	if (pCollision != NULL)
	{
		// 初期化処理
		if (FAILED(pCollision->Init()))
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

	// 当たり判定管理のポインタを返す
	return pCollision;
}

//-------------------------------------
//- 接触判定（矩形）
//-------------------------------------
bool CMgrColl::Hit(int nNldxColl, TAG hitTag, EVENT_TYPE eventType)
{
	// 変数宣言
	CColl* pCollMy = m_apColl[nNldxColl];					// 自身の当たり判定情報
	CColl::Data dataMy = m_apColl[nNldxColl]->GetData();	// 自身の情報
	int nHitNldxMax = dataMy.nHitNldxMax;					// 接触相手の最大数

	// 一時的な接触情報の初期化
	pCollMy->ResetHitDataTemp();

	bool bHit = false;									// 接触の有無

	for (int nCount = 0; nCount < COLLSION_NUM_MAX; nCount++)
	{
		if (m_apColl[nCount] != nullptr)
		{
			CColl* pCollPair = m_apColl[nCount];					// 相手の当たり判定情報
			CColl::Data dataPair = m_apColl[nCount]->GetData();		// 相手の情報
			TAG tagPair = dataPair.tag;								// 相手のタグ

			if (tagPair == hitTag)
			{
				if (eventType == EVENT_TYPE_TRIGGER)
				{
					bool bHitTrigger = false;

					for (int nCntHitNldx = 0; nCntHitNldx < nHitNldxMax; nCntHitNldx++)
					{
						if (nCount == dataMy.hitData[nCntHitNldx].nNldx)
						{
							bHitTrigger = true;
							break;
						}
					}

					if (bHitTrigger)
					{
						continue;
					}
				}

				// 変数宣言（情報取得）
				D3DXVECTOR3 posMy = pCollMy->GetData().pos;			// 自身の位置
				D3DXVECTOR3 sizeMy = pCollMy->GetData().size;		// 自身の大きさ

				// 変数宣言 (相手の情報取得)
				D3DXVECTOR3 posPair = pCollPair->GetData().pos;		// 相手の位置
				D3DXVECTOR3 sizePair = pCollPair->GetData().size;	// 相手の大きさ

				// 当たり判定
				if (hitRectangle(posMy, sizeMy, posPair, sizePair) == true)
				{
					// 接触判定を設定
					bHit = true;

					// ターゲットとの距離を算出
					float fLength = HelperSakai::CalculateLength(posMy, posPair);

					// 接触情報設定処理
					SetHit(
						pCollMy,
						nCount,
						pCollPair->GetData().pObj,
						fLength);
				}
			}

		}
	}

	return bHit;

}

//-------------------------------------
//- 接触判定（矩形の辺）
//-------------------------------------
bool CMgrColl::HitSide(int nNldxColl, CMgrColl::TAG hitTag, EVENT_TYPE eventType,CMgrColl::TYPE_SXIS typeSxis)
{
	// 変数宣言
	CColl* pCollMy = m_apColl[nNldxColl];					// 自身の当たり判定情報
	CColl::Data dataMy = m_apColl[nNldxColl]->GetData();	// 自身の情報
	bool bHit = false;										// 接触の有無

	for (int nCount = 0; nCount < COLLSION_NUM_MAX; nCount++)
	{
		if (m_apColl[nCount] != nullptr)
		{
			CColl* pCollPair = m_apColl[nCount];					// 相手の当たり判定情報
			CColl::Data dataPair = m_apColl[nCount]->GetData();		// 相手の情報
			TAG tagPair = dataPair.tag;								// 相手のタグ

			if (tagPair == hitTag)
			{
				// 変数宣言（情報取得）
				D3DXVECTOR3 posMy = pCollMy->GetData().pos;			// 自身の位置
				D3DXVECTOR3 sizeMy = pCollMy->GetData().size;		// 自身の大きさ

				// 変数宣言 (相手の情報取得)
				D3DXVECTOR3 posPair = pCollPair->GetData().pos;		// 相手の位置
				D3DXVECTOR3 sizePair = pCollPair->GetData().size;	// 相手の大きさ

				bool bHitColl = false;

				switch (typeSxis)
				{
				case CMgrColl::TYPE_SXIS_X:

					// X軸の当たり判定
					if (hitRectangleSide(posMy.x, sizeMy.x, posPair.x, sizePair.x) == true)
					{
						bHitColl = true;
					}

					break;

				case CMgrColl::TYPE_SXIS_Y:

					// X軸の当たり判定
					if (hitRectangleSide(posMy.y, sizeMy.y, posPair.y, sizePair.y) == true)
					{
						// 接触判定を設定
						bHitColl = true;
					}

				case CMgrColl::TYPE_SXIS_Z:

					// Z軸の当たり判定
					if (hitRectangleSide(posMy.z, sizeMy.z, posPair.z, sizePair.z) == true)
					{
						// 接触判定を設定
						bHitColl = true;
					}

					break;
				}

				if (bHitColl)
				{
					// 接触判定を設定
					bHit = true;

					// ターゲットとの距離を算出
				 	float fLength = HelperSakai::CalculateLength(posMy, posPair);

					// 接触情報設定処理
					SetHit(
						pCollMy,
						nCount,
						pCollPair->GetData().pObj,
						fLength);
				}
			}
		}
	}

	return bHit;
}

//-------------------------------------
//- 当たり判定管理の設定処理
//-------------------------------------
int CMgrColl::Set(CColl *pColl)
{
	for (int nCount = 0; nCount < COLLSION_NUM_MAX; nCount++)
	{
		if (m_apColl[nCount] == NULL)
		{
			m_apColl[nCount] = pColl;

			m_nNldxMax++;

			return nCount;
		}
	}

	return -1;
}

//-------------------------------------
//- 当たり判定管理の初期化設定処理
//-------------------------------------
void CMgrColl::Reset(int nNldx)
{
	m_apColl[nNldx] = nullptr;

	m_nNldxMax--;
}

//-------------------------------------
//- 接触情報設定処理
//-------------------------------------
void CMgrColl::SetHit(CColl* pCollMy,int nNldx,CObject* pObjPair,float fLength)
{
	// 接触相手の当たり判定情報を設定
	CColl::HitData hitData = {};
	
	hitData.nNldx = nNldx;
	hitData.fLength = fLength;

	// 接触相手の番号を代入
	pCollMy->SetHitData(hitData);
}

//-------------------------------------
//- 当たり判定管理の矩形の当たり判定
//-------------------------------------
bool CMgrColl::hitRectangle(D3DXVECTOR3 posMy, D3DXVECTOR3 sizeMy, D3DXVECTOR3 posPair, D3DXVECTOR3 sizePair)
{
	if (posMy.x + sizeMy.x >= posPair.x - sizePair.x &&
		posMy.x - sizeMy.x <= posPair.x + sizePair.x &&
		posMy.y + sizeMy.y >= posPair.y - sizePair.y &&
		posMy.y - sizeMy.y <= posPair.y + sizePair.y &&
		posMy.z + sizeMy.z >= posPair.z - sizePair.z &&
		posMy.z - sizeMy.z <= posPair.z + sizePair.z)
	{
		return true;
	}

	return false;
}

//-------------------------------------
//- 当たり判定管理の辺の当たり判定
//-------------------------------------
bool CMgrColl::hitRectangleSide(float fPos, float fSize, float fPosPair, float fSizePair)
{
	if (fPos + fSize >= fPosPair - fSizePair &&
		fPos - fSize <= fPosPair + fSizePair)
	{
		return true;
	}

	return false;
}