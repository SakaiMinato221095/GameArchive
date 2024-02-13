
//-===============================================
//-
//-	ゴミの処理[garbage.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "garbage.h"

#include "renderer.h"
#include "manager.h"
#include "game.h"

#include "sound.h"

#include "manager_model.h"
#include "manager_object.h"
#include "time_stop.h"

#include "mgr_sys_obj.h"
#include "sys_game_phase.h"

#include "player.h"

#include "effect.h"
#include "particle.h"

#include "file_data_garbage.h"

#include "state_battle.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	コンスト定義
//=======================================

// ゴミのモデルのコンスト定義
const char *pModelGarbage[] =
{
	"data\\MODEL\\garbage\\bin.x",					// 瓶のモデル

	"data\\MODEL\\garbage\\blood_knife.x",			// 血付きのナイフ
	"data\\MODEL\\garbage\\organ_bottle_none.x",	// 中身なし臓器保管瓶
	"data\\MODEL\\garbage\\syringe_none.x",			// 中身なし注射器

	"data\\MODEL\\garbage\\ice_cup.x",				// かき氷かっぷ
	"data\\MODEL\\garbage\\omikuji.x",				// おみくじ
	"data\\MODEL\\garbage\\puragomi.x",				// ぷらごみ
};

//-======================================
//-	静的変数宣言
//-======================================

CDataInt CGarbage::m_nDataModelNldx[MODEL_MAX] = {};

CGarbage::ModelData CGarbage::m_modelData[MODEL_MAX] = {};		// モデル情報

//-------------------------------------
//-	ゴミのコンストラクタ
//-------------------------------------
CGarbage::CGarbage(int nPriority) : CObjectX(nPriority)
{
	m_model = (MODEL)0;
	m_scoreGetType = CScore::GET_TYPE_NORMAL;
}

//-------------------------------------
//-	ゴミのデストラクタ
//-------------------------------------
CGarbage::~CGarbage()
{

}

//-------------------------------------
//- ゴミのモデル読み込み
//-------------------------------------
HRESULT CGarbage::Load(void)
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
		nModelNldx = pManagerModel->Regist(pModelGarbage[nCount]);

		// モデルの読み込み成功の有無を確認
		if (nModelNldx == -1)
		{
			// 失敗時に初期化処理を抜ける
			return E_FAIL;
		}

		// モデル番号を設定
		m_nDataModelNldx[nCount].Set(nModelNldx);
	}

	// ゴミ
	CFileDataGarbage::Load();

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- ゴミの読み込んだモデル破棄
//-------------------------------------
void CGarbage::Unload(void)
{

}

//-------------------------------------
//- ゴミの初期化処理
//-------------------------------------
HRESULT CGarbage::Init(MODEL model)
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
//- ゴミの終了処理
//-------------------------------------
void CGarbage::Uninit(void)
{
	// Xファイルオブジェクトの終了
	CObjectX::Uninit();
}

//-------------------------------------
//- ゴミの更新処理
//-------------------------------------
void CGarbage::Update(void)
{
	// フェーズ情報を取得
	CSysGamePhase::TYPE pPhaseType = CGame::GetSysGamePhase()->GetType();

	if (pPhaseType == CSysGamePhase::TYPE_SEARCH)
	{
		// 変数宣言（情報取得）
		bool bEat = m_bDataEat.Get();

		if (bEat == true)
		{
			// 食べる状態時の処理
			UpdateEat();
		}
		else
		{
			// 使用可能表示処理
			AvailableDisplay();
		}

	}

	// Xファイルオブジェクトの更新処理
	CObjectX::Update();
}

//-------------------------------------
//- ゴミの描画処理
//-------------------------------------
void CGarbage::Draw(void)
{
	// ゴミの描画処理
	CObjectX::Draw();
}

//-------------------------------------
//- ゴミの生成処理
//-------------------------------------
CGarbage *CGarbage::Create(MODEL model)
{
	// ゴミの生成
	CGarbage *pCGarbage = DBG_NEW CGarbage;

	// 生成の成功の有無を判定
	if (pCGarbage != NULL)
	{
		// 初期化処理
		if (FAILED(pCGarbage->Init(model)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCGarbage == NULL)
	{// 失敗時

	 // 「なし」を返す
		return NULL;
	}

	// 種類を設定
	pCGarbage->SetType(TYPE_ENEMY);

	// ゴミのポインタを返す
	return pCGarbage;
}

//-------------------------------------
//-	ゴミの設定処理
//-------------------------------------
void CGarbage::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 情報更新
	m_dataPos.Set(pos);							// 位置
	m_dataPosOld.Set(pos);						// 前回の位置

	m_dataRot.Set(rot);							// 向き
	m_dataRotDest.Set(rot);						// 目的の向き
}

//-------------------------------------
//-	モデルの設定処理
//-------------------------------------
int CGarbage::GetModel(void)
{
	// モデル設定
	return(int)m_model;
}

//-------------------------------------
//-	モデルの設定処理
//-------------------------------------
void CGarbage::SetModel(int nModelNldx)
{
	// モデル設定
	m_model = (MODEL)nModelNldx;
}

//-------------------------------------
//-	モデルの情報の設定処理
//-------------------------------------
void CGarbage::SetModelData(int nNum, CGarbage::ModelData modelData)
{
	// モデル情報の代入
	m_modelData[nNum] = modelData;	// 大きさ
}

//-------------------------------------
//-	モデルの情報の取得処理
//-------------------------------------
CGarbage::ModelData CGarbage::GetModelData(int nNum)
{
	// モデル情報を返す
	return m_modelData[nNum];
}

//-------------------------------------
//- ゴミの実行処理
//-------------------------------------
void CGarbage::Execution(int nEatTime)
{
	// サウンドの取得処理
	CSound *pSound = CManager::GetSound();

	// サウンドの有無を判定
	if (pSound == NULL)
	{
		return;
	}

	// SEの再生（テレポ）
	pSound->Play(CSound::LABEL_SE_EAT_000);

	// 情報更新
	m_bDataEat.Set(true);			// 食べるの有無
	m_nDataEatTime.Set(nEatTime);	// 食べる時間
	m_nDataEatCut.Set(0);			// 食べるカウントを初期化
}

//-------------------------------------
//- ゴミの初期設定処理
//-------------------------------------
void CGarbage::InitSet(MODEL model)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();	// 位置
	D3DXVECTOR3 rot = m_dataRot.Get();	// 向き

	// 情報更新
	m_dataPosOld.Set(pos);				// 前回の位置
	m_dataRotDest.Set(rot);				// 目的の向き

	// データ設定
	m_dataSize.Set(m_modelData[model].size);
	m_nGetScore.Set(m_modelData[model].nScoreHave);
	m_nType.Set(m_modelData[model].nType);
}

//-------------------------------------
//- ゴミの使用可能表示
//-------------------------------------
void CGarbage::AvailableDisplay(void)
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

				if (m_modelData[m_model].nType == 0)
				{
					// 色を設定（基本色）
					pEffect->m_dataColor.Set(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
				else if (m_modelData[m_model].nType == 1)
				{
					// 色を設定（基本色）
					pEffect->m_dataColor.Set(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
				}

				// エフェクトの設定処理
				pEffect->m_nDataLife.Set(60);
			}

		}
	}

	// 情報更新
	m_dataPos.Set(pos);						// 位置
	m_nDataEffectCount.Set(nEffectCount);	// エフェクト出現のカウント
}

//-------------------------------------
//- ゴミの食べられているときの処理
//-------------------------------------
void CGarbage::UpdateEat(void)
{
	// プレイヤーのポインタを取得
	CPlayer *pPlayer = CSysGamePhase::GetPlayer();

	// プレイヤーのポインタの有無を判定
	if (pPlayer == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();		// 位置
	int nEatTime = m_nDataEatTime.Get();	// 食べる時間
	int nEatCut = m_nDataEatCut.Get();		// 食べるカウント

	// 手の位置を代入（番号ベタ打ち[4]番）
	pos.x = pPlayer->GetObjectModel(4)->GetMtxWorld()._41;
	pos.y = pPlayer->GetObjectModel(4)->GetMtxWorld()._42;
	pos.z = pPlayer->GetObjectModel(4)->GetMtxWorld()._43;

	// 食べるカウントを加算
	nEatCut++;

	if (nEatCut >= nEatTime)
	{
		// 食べる終了処理
		EatEnd();
	}

	// 情報更新
	m_dataPos.Set(pos);					// 位置
	m_nDataEatCut.Set(nEatCut);			// 食べるカウント
}

//-------------------------------------
//- ゴミの食べる終了処理
//-------------------------------------
void CGarbage::EatEnd(void)
{
	// 戦闘ステータスの取得処理
	CStateBattle *pStateBattle = CGame::GetStateBattle();

	// 戦闘ステータスのポインタの有無を判定
	if (pStateBattle == NULL)
	{
		return;
	}

	// 属性加算処理
	pStateBattle->AddElem(
		m_modelData[m_model].nNor,
		m_modelData[m_model].nLow,
		m_modelData[m_model].nChaos);

	// 終了処理
	Uninit();
}