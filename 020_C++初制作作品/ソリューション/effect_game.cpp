
//-===============================================
//-
//-	ゲームエフェクトの処理[effect_game.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "effect_game.h"

#include "renderer.h"
#include "manager.h"

#include "time_stop.h"

#include "camera.h"

#include "time_stop.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	ゲームエフェクトのコンストラクタ
//-------------------------------------
CEffectGame::CEffectGame()
{

}

//-------------------------------------
//-	ゲームエフェクトのデストラクタ
//-------------------------------------
CEffectGame::~CEffectGame()
{

}

//-------------------------------------
//- ゲームエフェクトの初期化処理
//-------------------------------------
HRESULT CEffectGame::Init(void)
{
	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- ゲームエフェクトの終了処理
//-------------------------------------
void CEffectGame::Uninit(void)
{

}

//-------------------------------------
//- ゲームエフェクトの更新処理
//-------------------------------------
void CEffectGame::Update(void)
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
	D3DXVECTOR3 rotQuake = m_dataRotQuake.Get();	// 向き
	D3DXVECTOR3 speed = m_dataSpeed.Get();			// 速度
	int nLife = m_nDataLife.Get();					// 体力
	int nLoopCount = m_nDataLoopCount.Get();		// ループ回数
	int nLifeCount = m_nDataLifeCount.Get();		// 体力カウント
	bool bUse = m_bDataUse.Get();					// 使用の有無

	D3DXVECTOR3 posVQuake = m_dataPosVQuake.Get();	// 画面揺れ視点位置
	D3DXVECTOR3 posRQuake = m_dataPosRQuake.Get();	// 画面揺れ注視点

	// 使用の有無を判定
	if (bUse == true)
	{
		// 整数カウントの有無を判定
		if (pManagerTime->m_bDataIntCount.Get() == true)
		{
			// 体力カウントを
			nLifeCount++;
		}

		// 現在の体力カウントを判定 if（体力最大値の半分以下）
		if (nLife / 2 >= nLifeCount)
		{
			// ゲームエフェクトの加算処理
			AddQuake(rotQuake, speed);
		}
		// if（体力最大値の半分以上）
		else
		{
			// ゲームエフェクトの減算処理
			SubQuake(rotQuake, speed);
		}
		
		// 現在の体力カウントの判定（最大体力値が同じ）
		if (nLife == nLifeCount)
		{
			// 体力カウントを初期化
			nLifeCount = 0;

			// ループ回数を判定 if(ループ回数が残っているとこ)
			if (nLoopCount != 0)
			{
				// ループ回数を減らす
				nLoopCount--;

				// スピードを減算
				speed *= 0.50f;
			}
			else
			{
				// 使用状況を設定
				bUse = false;

				posVQuake = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				posRQuake = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
	}

	// 情報更新
	m_dataRotQuake.Set(rotQuake);			// 向き
	m_dataSpeed.Set(speed);					// 速度
	m_nDataLife.Set(nLife);					// 体力
	m_nDataLoopCount.Set(nLoopCount);		// ループ回数
	m_nDataLifeCount.Set(nLifeCount);		// 体力カウント
	m_bDataUse.Set(bUse);					// 使用の有無
	m_dataPosVQuake.Set(posVQuake);			// 画面揺れ視点位置
	m_dataPosRQuake.Set(posRQuake);			// 画面揺れ注視点
}

//-------------------------------------
//- ゲームエフェクトの生成処理
//-------------------------------------
CEffectGame *CEffectGame::Create(void)
{
	// ゲームエフェクトのポインタを宣言
	CEffectGame *pCEffectGame = DBG_NEW CEffectGame;

	// 生成の成功の有無を判定
	if (pCEffectGame != NULL)
	{
		// 初期化処理
		if (FAILED(pCEffectGame->Init()))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCEffectGame == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// ゲームエフェクトのポインタを返す
	return pCEffectGame;
}

//-------------------------------------
//- ゲームエフェクトの設定処理
//-------------------------------------
void CEffectGame::Set(D3DXVECTOR3 rot , D3DXVECTOR3 speed,int nTime,int nLoopCount)
{
	// 変数宣言（情報取得）
	bool bUse = m_bDataUse.Get();	// 使用の有無

	// 使用の有無を判定
	if (bUse == false)
	{
		m_dataRotQuake.Set(rot);
		m_dataSpeed.Set(speed);
		m_nDataLife.Set(nTime);
		m_nDataLoopCount.Set(nLoopCount);
		m_bDataUse.Set(true);
	}
}

//-------------------------------------
//-	カメラの画面揺れ加算処理
//-------------------------------------
void CEffectGame::AddQuake(D3DXVECTOR3 quakeRot, D3DXVECTOR3 quakeSpeed)
{
	// カメラの情報を取得
	CCamera *pCamera = CManager::GetCamera();
	
	// 変数宣言（情報取得）
	D3DXVECTOR3 posVQuake = m_dataPosVQuake.Get();	// 画面揺れ視点位置
	D3DXVECTOR3 posRQuake = m_dataPosRQuake.Get();	// 画面揺れ注視点

	// 変数宣言（カメラの情報取得）
	D3DXVECTOR3 posV = pCamera->m_dataPosV.Get();	// 視点
	D3DXVECTOR3 posR = pCamera->m_dataPosR.Get();	// 注視点
	D3DXVECTOR3 rot = pCamera->m_dataRot.Get();		// 向き

	// 画面揺れの情報を算出
	posVQuake.x += sinf((D3DX_PI * quakeRot.y) + rot.y) * quakeSpeed.x;
	posVQuake.z += cosf((D3DX_PI * quakeRot.y) + rot.y) * quakeSpeed.z;
	posRQuake.x += sinf((D3DX_PI * quakeRot.y) + rot.y) * quakeSpeed.x * 1.5f;
	posRQuake.z += cosf((D3DX_PI * quakeRot.y) + rot.y) * quakeSpeed.z * 1.5f;

	// 時間倍率の計算
	D3DXVECTOR3 posVQuakeTime = posVQuake;
	D3DXVECTOR3 posRQuakeTime = posRQuake;

	// 視点情報を更新
	posV = posV + posVQuakeTime;
	posR = posR + posRQuakeTime;

	// 情報更新
	m_dataPosVQuake.Set(posVQuake);
	m_dataPosRQuake.Set(posRQuake);

	// 情報更新（カメラ）
	pCamera->m_dataPosV.Set(posV);
	pCamera->m_dataPosR.Set(posR);
}

//-------------------------------------
//-	カメラの画面揺れ減算処理
//-------------------------------------
void CEffectGame::SubQuake(D3DXVECTOR3 quakeRot, D3DXVECTOR3 quakeSpeed)
{
	// カメラの情報を取得
	CCamera *pCamera = CManager::GetCamera();

	// 変数宣言（情報取得）
	D3DXVECTOR3 posVQuake = m_dataPosVQuake.Get();	// 画面揺れ視点位置
	D3DXVECTOR3 posRQuake = m_dataPosRQuake.Get();	// 画面揺れ注視点

	D3DXVECTOR3 posV = pCamera->m_dataPosV.Get();	// 視点
	D3DXVECTOR3 posR = pCamera->m_dataPosR.Get();	// 注視点
	D3DXVECTOR3 rot = pCamera->m_dataRot.Get();		// 向き

	posVQuake.x -= sinf((D3DX_PI * quakeRot.y) + rot.y) * quakeSpeed.x;
	posVQuake.z -= cosf((D3DX_PI * quakeRot.y) + rot.y) * quakeSpeed.z;
	posRQuake.x -= sinf((D3DX_PI * quakeRot.y) + rot.y) * quakeSpeed.x * 1.5f;
	posRQuake.z -= cosf((D3DX_PI * quakeRot.y) + rot.y) * quakeSpeed.z * 1.5f;

	// 時間倍率の計算
	D3DXVECTOR3 posVQuakeTime = posVQuake;
	D3DXVECTOR3 posRQuakeTime = posRQuake;

	// 視点情報を更新
	posV = posV + posVQuakeTime;
	posR = posR + posRQuakeTime;

	// 情報更新
	m_dataPosVQuake.Set(posVQuake);
	m_dataPosRQuake.Set(posRQuake);

	// 情報更新（カメラ）
	pCamera->m_dataPosV.Set(posV);
	pCamera->m_dataPosR.Set(posR);
}