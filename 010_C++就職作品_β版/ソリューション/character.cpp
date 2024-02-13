
//-===============================================
//-
//-	キャラクター処理[character.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "character.h"

#include "renderer.h"
#include "manager.h"

#include "Input.h"
#include "xinput.h"

#include "sound.h"
#include "debugproc.h"

#include "helper_sakai.h"

#include "camera.h"

#include "coll.h"
#include "enemy.h"

#include "command.h"

#include "attack.h"
#include "punch.h"

#include "finish_punch.h"

//-======================================
//-	マクロ定義
//-======================================

#define PLAYER_SPEED		(3.0f)	// プレイヤーの速度

//-======================================
//-	静的変数宣言
//-======================================

//-======================================
//-	コンスト定義
//-======================================

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CCharacter::CCharacter()
{
	// 値をクリア
	ZeroMemory(&m_mtxWorld, sizeof(m_mtxWorld));

	ZeroMemory(&m_apModel, sizeof(m_apModel));

	m_nNumModel = 0;

	m_pMotion = NULL;

	ZeroMemory(&m_data, sizeof(m_data));


}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CCharacter::~CCharacter()
{

}

//-------------------------------------
//- プレイヤーの初期化処理
//-------------------------------------
HRESULT CCharacter::Init(CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType,int nStateMax)
{
	// モデルのパーツ数を取得
	m_nNumModel = CModel::GetPartsNum(modelType);

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		// 階層構造Xオブジェクトの有無を判定
		if (m_apModel[nCount] == NULL)
		{
			// 階層構造Xオブジェクトの生成
			m_apModel[nCount] = CModel::Create(modelType, nCount);

			if (m_apModel[nCount] == nullptr)
			{
				return E_FAIL;
			}

			// 階層構造Xオブジェクトの設定
			m_apModel[nCount]->SetParent(m_apModel, modelType, nCount);
		}
	}

	if (m_pMotion == NULL)
	{
		// モーションの生成
		m_pMotion = CMotion::Create(m_nNumModel, nStateMax);

		if (m_pMotion == nullptr)
		{
			return E_FAIL;
		}

		// ファイルを読み込み
		m_pMotion->SetFile(motionType);

		// モデルの設定
		m_pMotion->SetModel(m_apModel, 0);

		// 待機モーションを設定
		m_pMotion->Set(0);
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- プレイヤーの終了処理
//-------------------------------------
void CCharacter::Uninit(void)
{
	// モデルの終了処理
	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{
			// モデルの開放処理
			m_apModel[nCount]->Uninit();

			delete m_apModel[nCount];
			m_apModel[nCount] = NULL;
		}
	}

	// モーションの終了処理
	if (m_pMotion != NULL)
	{
		// モーションの開放
		m_pMotion->Uninit();

		delete m_pMotion;
		m_pMotion = NULL;
	}

	// 自分自身のポインタの開放
	Release();
}

//-------------------------------------
//- プレイヤーの更新処理
//-------------------------------------
void CCharacter::Update(void)
{
	// モーションの終了処理
	if (m_pMotion != NULL)
	{
		if (m_pMotion->IsFinsih())
		{
			// モーションの更新処理
			m_pMotion->Update();
		}
	}
}

//-------------------------------------
//- プレイヤーの描画処理
//-------------------------------------
void CCharacter::Draw(void)
{
	// マトリックスの設定
	SetMatrix();

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_apModel[nCount] != nullptr)
		{
			// パーツの描画処理
			m_apModel[nCount]->Draw();
		}
	}
}

//-------------------------------------
//- プレイヤーの生成処理
//-------------------------------------
CCharacter* CCharacter::Create(CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType,int nMotionStateMax)
{
	// プレイヤーのポインタを宣言
	CCharacter* pPlayer = DBG_NEW CCharacter;

	// 生成の成功の有無を判定
	if (pPlayer != NULL)
	{
		// 初期化処理
		if (FAILED(pPlayer->Init(modelType, motionType, nMotionStateMax)))
		{// 失敗時

		 // 「なし」を返す
			return NULL;
		}
	}
	else if (pPlayer == NULL)
	{// 失敗時

	 // 「なし」を返す
		return NULL;
	}

	// プレイヤーのポインタを返す
	return pPlayer;
}

//-------------------------------------
//- プレイヤーの描画処理
//-------------------------------------
void CCharacter::SetMatrix(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// デバイスの情報取得の成功を判定
	if (pDevice == NULL)
	{// 失敗時

	 // 初期化処理を抜ける
		return;
	}

	// 変数宣言
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_data.rot.y, m_data.rot.x, m_data.rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置反映
	D3DXMatrixTranslation(&mtxTrans, m_data.pos.x, m_data.pos.y, m_data.pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(
		D3DTS_WORLD,
		&m_mtxWorld);
}