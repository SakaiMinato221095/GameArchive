
//-===============================================
//-
//-	オブジェクトエフェクトの処理[effect_object.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "effect_object.h"

#include "renderer.h"
#include "manager.h"

#include "manager_model.h"
#include "time_stop.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	コンスト定義
//=======================================

// エフェクトオブジェクトのモデルのコンスト定義
const char *pModelEffectObject[] =
{
	"data\\MODEL\\Coin000.x",	// コインのモデル
	"data\\MODEL\\bin.x",		// 瓶
};

//-======================================
//-	静的変数宣言
//-======================================

int CEffectObject::m_nModelNldx[MODEL_MAX] = {};		// モデルの番号

//-------------------------------------
//-	オブジェクトエフェクトのコンストラクタ
//-------------------------------------
CEffectObject::CEffectObject(int nPriority) : CObjectX(nPriority)
{

}

//-------------------------------------
//-	オブジェクトエフェクトのデストラクタ
//-------------------------------------
CEffectObject::~CEffectObject()
{

}

//-------------------------------------
//- オブジェクトエフェクトのモデル読み込み
//-------------------------------------
HRESULT CEffectObject::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// デバイスの情報取得の成功を判定
	if (pDevice == NULL)
	{// 失敗時

	 // 初期化処理を抜ける
		return E_FAIL;
	}

	// モデル管理の生成
	CManagerModel *pManagerModel = CManager::GetManagerModel();

	// モデル管理の有無を判定
	if (pManagerModel == NULL)
	{
		// 初期化処理を抜ける
		return E_FAIL;
	}

	// テクスチャ設定
	for (int nCount = 0; nCount < MODEL_MAX; nCount++)
	{
		// モデル番号の取得（モデルの割当）
		m_nModelNldx[nCount] = pManagerModel->Regist(pModelEffectObject[nCount]);

		// モデルの読み込み成功の有無を確認
		if (m_nModelNldx[nCount] == -1)
		{
			// 失敗時に初期化処理を抜ける
			return E_FAIL;
		}
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- オブジェクトエフェクトの読み込んだモデル破棄
//-------------------------------------
void CEffectObject::Unload(void)
{

}

//-------------------------------------
//- オブジェクトエフェクトの初期化処理
//-------------------------------------
HRESULT CEffectObject::Init(MODEL model)
{
	// モデル管理の生成
	CManagerModel *pManagerModel = CManager::GetManagerModel();

	// モデル管理の有無を判定
	if (pManagerModel == NULL)
	{
		// 処理を抜ける
		return E_FAIL;
	}

	// オブジェクトエフェクトのモデル割当
	BindModel(m_nModelNldx[model],model);

	//	オブジェクトエフェクトの初期化 if(初期化成功の有無を判定)
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- オブジェクトエフェクトの終了処理
//-------------------------------------
void CEffectObject::Uninit(void)
{
	// オブジェクトエフェクトの終了
	CObjectX::Uninit();
}

//-------------------------------------
//- オブジェクトエフェクトの更新処理
//-------------------------------------
void CEffectObject::Update(void)
{
	// オブジェクトエフェクトの加算処理
	Add();

	// オブジェクトエフェクトの更新処理
	CObjectX::Update();
}

//-------------------------------------
//- オブジェクトエフェクトの描画処理
//-------------------------------------
void CEffectObject::Draw(void)
{
	// オブジェクトエフェクトの描画処理
	CObjectX::Draw();
}

//-------------------------------------
//- オブジェクトエフェクトの生成処理
//-------------------------------------
CEffectObject *CEffectObject::Create(MODEL model)
{
	// オブジェクトエフェクトのポインタを宣言
	CEffectObject *pCEffectObject = DBG_NEW CEffectObject(3);

	// 生成の成功の有無を判定
	if (pCEffectObject != NULL)
	{
		// 初期化処理
		if (FAILED(pCEffectObject->Init(model)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCEffectObject == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// オブジェクトエフェクトのポインタを返す
	return pCEffectObject;
}

//-------------------------------------
//- オブジェクトエフェクトの設定処理
//-------------------------------------
void CEffectObject::Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXVECTOR3 move,D3DXVECTOR3 moveMax)
{
	// 位置情報設定
	m_dataPos.Set(pos);
	m_dataPosOld.Set(pos);

	// 大きさの設定
	m_dataSize.Set(size);
	m_dataSizeHold.Set(size);

	// 向きの設定
	m_dataRot.Set(rot);
	m_dataRotDest.Set(rot);

	// 移動量の設定
	m_dataMove.Set(move);

	// 移動量の最大値
	m_dataMoveMax.Set(moveMax);
	
	// 移動量の蓄積値
	m_dataMoveAcu.Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// 回転量を設定
	m_dataAddRot.Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//-------------------------------------
//- オブジェクトエフェクトの加算処理
//-------------------------------------
void CEffectObject::Add(void)
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
	D3DXVECTOR3 pos = m_dataPos.Get();		// 位置
	D3DXVECTOR3 move = m_dataMove.Get();	// 移動量

	D3DXVECTOR3 moveAcu = m_dataMoveAcu.Get();	// 移動量の蓄積値
	D3DXVECTOR3 moveMax = m_dataMoveMax.Get();	// 移動量の最大値

	D3DXVECTOR3 addRot = m_dataAddRot.Get();	// 回転量

	// 蓄積値の判定
	if (moveAcu.x >= moveMax.x &&
		moveAcu.y >= moveMax.y &&
		moveAcu.z >= moveMax.z)
	{		
		// 時間倍率の計算
		D3DXVECTOR3 addRotTime = pManagerTime->CalRate(addRot);

		// 回転処理
		AddRot(addRotTime);

		// オブジェクトエフェクトの減少処理
		if (Sub() == true)
		{
			return;
		}
	}
	else
	{
		// 時間倍率の計算
		D3DXVECTOR3 addRotTime = pManagerTime->CalRate(addRot);

		// 回転処理
		AddRot(addRotTime);

		// 時間倍率の計算
		D3DXVECTOR3 addMoveTime = pManagerTime->CalRate(move);

		// 位置に移動量を加算
		pos += addMoveTime;

		// 移動量の蓄積値に移動量を加算
		moveAcu += addMoveTime;

		// 蓄積値の判定
		if (moveAcu.x >= moveMax.x &&
			moveAcu.y >= moveMax.y &&
			moveAcu.z >= moveMax.z)
		{
			// 回転量を設定
			addRot = D3DXVECTOR3(0.0f, -0.2f, 0.0f);

			// 体力を設定
			m_nDataLife.Set(10);
		}
	}

	// 位置の反映
	m_dataPos.Set(pos);		// 位置
	m_dataMove.Set(move);	// 移動量

	m_dataMoveAcu.Set(moveAcu);	// 移動量の蓄積値
	m_dataMoveMax.Set(moveMax);	// 移動量の最大値

	m_dataAddRot.Set(addRot);	// 回転量
}

//-------------------------------------
//- オブジェクトエフェクトの減少処理
//-------------------------------------
bool CEffectObject::Sub(void)
{
	// 時間管理の情報を取得
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// 時間管理取得の有無を判定
	if (pManagerTime == NULL)
	{
		// 処理を抜ける
		return false;
	}

	// 変数を宣言（情報取得）
	D3DXVECTOR3 sizeHold = m_dataSizeHold.Get();	// 保持するサイズ

	D3DXVECTOR3 moveAcu = m_dataMoveAcu.Get();		// 移動量の蓄積値
	D3DXVECTOR3 moveMax = m_dataMoveMax.Get();		// 移動量の最大値

	D3DXVECTOR3 size = m_dataSize.Get();			// 大きさ
	int nLife = m_nDataLife.Get();					// 体力

	// 時間倍率の計算（サイズの減少量算出）
	float nTimeEffectSizeX = pManagerTime->CalRate(sizeHold.x / nLife);
	float nTimeEffectSizeY = pManagerTime->CalRate(sizeHold.y / nLife);

	// 大きさを減らす
	size.x -= nTimeEffectSizeX;
	size.y -= nTimeEffectSizeY;

	// 整数カウントの有無を判定
	if (pManagerTime->m_bDataIntCount.Get() == true)
	{
		// 保持する情報を更新
		sizeHold = size;

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

	// 情報更新
	m_dataSize.Set(size);			// 大きさ
	m_dataSizeHold.Set(sizeHold);	// 保持する大きさ
	m_nDataLife.Set(nLife);			// 体力

	// 失敗を返す
	return false;
}