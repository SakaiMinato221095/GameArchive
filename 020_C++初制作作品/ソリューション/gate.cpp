
//-===============================================
//-
//-	ゲートの処理[gate.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "gate.h"

#include "renderer.h"
#include "manager.h"
#include "game.h"

#include "sound.h"

#include "manager_model.h"
#include "manager_object.h"
#include "time_stop.h"

#include "mgr_sys_obj.h"
#include "sys_game_phase.h"

#include "effect.h"
#include "particle.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	コンスト定義
//=======================================

// ゲートのモデルのコンスト定義
const char *pModelGate[] =
{
	"data\\MODEL\\gate.x",			// ゲートのモデル
};

//-======================================
//-	静的変数宣言
//-======================================

CDataInt CGate::m_nDataModelNldx[MODEL_MAX] = {};

//-------------------------------------
//-	ゲートのコンストラクタ
//-------------------------------------
CGate::CGate(int nPriority) : CObjectX(nPriority)
{
	m_model = (MODEL)0;
}

//-------------------------------------
//-	ゲートのデストラクタ
//-------------------------------------
CGate::~CGate()
{

}

//-------------------------------------
//- ゲートのモデル読み込み
//-------------------------------------
HRESULT CGate::Load(void)
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
		// モデル番号を取得
		int nModelNldx = m_nDataModelNldx[nCount].Get();

		// モデル番号の取得（モデルの割当）
		nModelNldx = pManagerModel->Regist(pModelGate[nCount]);

		// モデルの読み込み成功の有無を確認
		if (nModelNldx == -1)
		{
			// 失敗時に初期化処理を抜ける
			return E_FAIL;
		}

		// モデル番号を設定
		m_nDataModelNldx[nCount].Set(nModelNldx);
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- ゲートの読み込んだモデル破棄
//-------------------------------------
void CGate::Unload(void)
{

}

//-------------------------------------
//- ゲートの初期化処理
//-------------------------------------
HRESULT CGate::Init(MODEL model)
{
	// モデル管理の生成
	CManagerModel *pManagerModel = CManager::GetManagerModel();

	// モデル管理の有無を判定
	if (pManagerModel == NULL)
	{
		// 処理を抜ける
		return E_FAIL;
	}

	// モデル番号を取得
	int nModelNldx = m_nDataModelNldx[model].Get();

	// 敵のモデル割当
	BindModel(nModelNldx, model);

	// 初期設定処理
	InitSet(model);

	// Xファイルオブジェクトの初期化 if(初期化成功の有無を判定)
	if (FAILED(CObjectX::Init()))
	{
		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- ゲートの終了処理
//-------------------------------------
void CGate::Uninit(void)
{
	// Xファイルオブジェクトの終了
	CObjectX::Uninit();
}

//-------------------------------------
//- ゲートの更新処理
//-------------------------------------
void CGate::Update(void)
{
	// フェーズ情報を取得
	CSysGamePhase::TYPE pPhaseType = CGame::GetSysGamePhase()->GetType();

	if (pPhaseType == CSysGamePhase::TYPE_SEARCH || 
		pPhaseType == CSysGamePhase::TYPE_BATTLE)
	{
		// 使用可能表示処理
		AvailableDisplay();
	}

	// Xファイルオブジェクトの更新処理
	CObjectX::Update();
}

//-------------------------------------
//- ゲートの描画処理
//-------------------------------------
void CGate::Draw(void)
{
	// ゲートの描画処理
	CObjectX::Draw();
}

//-------------------------------------
//- ゲートの生成処理
//-------------------------------------
CGate *CGate::Create(MODEL model)
{
	// ゲートの生成
	CGate *pCGate = DBG_NEW CGate;

	// 生成の成功の有無を判定
	if (pCGate != NULL)
	{
		// 初期化処理
		if (FAILED(pCGate->Init(model)))
		{// 失敗時

		 // 「なし」を返す
			return NULL;
		}
	}
	else if (pCGate == NULL)
	{// 失敗時

	 // 「なし」を返す
		return NULL;
	}

	// 種類を設定
	pCGate->SetType(TYPE_ENEMY);

	// ゲートのポインタを返す
	return pCGate;
}

//-------------------------------------
//-	モデルの設定処理
//-------------------------------------
int CGate::GetModel(void)
{
	// モデル設定
	return(int)m_model;
}

//-------------------------------------
//-	モデルの設定処理
//-------------------------------------
void CGate::SetModel(int nModelNldx)
{
	// モデル設定
	m_model = (MODEL)nModelNldx;
}

//-------------------------------------
//- ゲートの実行処理
//-------------------------------------
void CGate::Execution()
{
	// サウンドの取得処理
	CSound *pSound = CManager::GetSound();

	// サウンドの有無を判定
	if (pSound == NULL)
	{
		return;
	}

	// SEの再生（テレポ）
	pSound->Play(CSound::LABEL_SE_TLEPORT_000);

	return;
}

//-------------------------------------
//- ゲートの初期設定処理
//-------------------------------------
void CGate::InitSet(MODEL model)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();	// 位置
	D3DXVECTOR3 rot = m_dataRot.Get();	// 向き

	// 情報更新
	m_dataPosOld.Set(pos);				// 前回の位置
	m_dataRotDest.Set(rot);				// 目的の向き

	m_dataSize.Set(D3DXVECTOR3(100.0f,100.0f,100.0f));
}

//-------------------------------------
//- ゲートの使用可能表示
//-------------------------------------
void CGate::AvailableDisplay(void)
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
	D3DXVECTOR3 pos = m_dataPos.Get();				// 位置
	int nEffectCount = m_nDataEffectCount.Get();	// エフェクト出現のカウント

	if (pManagerTime->m_bDataIntCount.Get() == true)
	{
		// エフェクトのポインタを宣言
		CEffect *pEffect = NULL;

		// エフェクトカウントを加算
		nEffectCount++;

		// エフェクトカウントの判定
		if (nEffectCount >= 10)
		{
			// エフェクトの生成
			pEffect = CEffect::Create(CEffect::TEX_NORMAL_000);

			// エフェクトの有無を判定
			if (pEffect != NULL)
			{
				// エフェクトカウントの初期化
				nEffectCount = 0;

				// 位置情報を設定
				pEffect->m_dataPos.Set(D3DXVECTOR3(pos.x, pos.y + 20.0f, pos.z));

				// 大きさを設定
				pEffect->m_dataSize.Set(D3DXVECTOR3(10.0f, 10.0f, 0.0f));

				// 移動量を設定
				pEffect->m_dataMove.Set(D3DXVECTOR3(0.0f, 1.0f, 0.0f));

				// 色を設定（基本色）
				pEffect->m_dataColor.Set(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

				// エフェクトの設定処理
				pEffect->m_nDataLife.Set(60);
			}

		}
	}

	// 情報更新
	m_dataPos.Set(pos);						// 位置
	m_nDataEffectCount.Set(nEffectCount);	// エフェクト出現のカウント
}
