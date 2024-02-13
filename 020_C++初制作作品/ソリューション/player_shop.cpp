
//-===============================================
//-
//-	購入プレイヤー処理[player_shop.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "player_shop.h"

#include "renderer.h"
#include "manager.h"
#include "game.h"

#include "manager_object.h"
#include "sys_game_phase.h"

#include "Input.h"
#include "sound.h"
#include "debugproc.h"

#include "item.h"
#include "obj_2d_item_info.h"

#include "mgr_sys_obj.h"

#include "ui_opr_desc.h"
#include "ui_text_desc.h"

#include "hit.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CPlayerShop::CPlayerShop()
{
	// 値をクリア
	m_stateType = STATE_TYPE_NEUTRAL;
	m_stateTypeOld = m_stateType;

	m_pUiOprDesc = NULL;
	m_pUiTextDesc = NULL;
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CPlayerShop::~CPlayerShop()
{

}

//-------------------------------------
//- 購入プレイヤーの初期化処理
//-------------------------------------
HRESULT CPlayerShop::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CObjectModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax)
{
	// プレイヤーの設定処理
	Set(pos, rot);
	
	// プレイヤーの初期化処理
	CPlayer::Init(modelType, motionType, nStateMax);

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 購入プレイヤーの終了処理
//-------------------------------------
void CPlayerShop::Uninit(void)
{
	// プレイヤーの終了処理
	CPlayer::Uninit();
}

//-------------------------------------
//- 購入プレイヤーの更新処理
//-------------------------------------
void CPlayerShop::Update(void)
{
	// 情報設定（前回の情報）
	m_dataPosOld.Set(m_dataPos.Get());	// 位置
	m_stateTypeOld = m_stateType;		// 状態

	// ゲームモードの判定
	if (CGame::GetSysGamePhase()->GetType() == CSysGamePhase::TYPE_SHOP)
	{
		// プレイヤーの更新処理
		CPlayer::Update();
		
		// イベントの更新処理
		UpdateItem();

		// モーションの更新処理
		UpdateMotion();
	}
}

//-------------------------------------
//- 購入プレイヤーの描画処理
//-------------------------------------
void CPlayerShop::Draw(void)
{
	// プレイヤーの描画処理
	CPlayer::Draw();
}

//-------------------------------------
//- 購入プレイヤーの生成処理
//-------------------------------------
CPlayerShop * CPlayerShop::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CObjectModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType)
{
	// 購入プレイヤーのポインタを宣言
	CPlayerShop *pCPlayerShop = new CPlayerShop;

	// 生成の成功の有無を判定
	if (pCPlayerShop != NULL)
	{
		// 初期化処理
		if (FAILED(pCPlayerShop->Init(pos, rot, modelType, motionType, STATE_TYPE_MAX)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCPlayerShop == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// 種類を設定
	pCPlayerShop->SetType(TYPE_PLAYER);

	// 購入プレイヤーのポインタを返す
	return pCPlayerShop;
}

//-------------------------------------
//- 購入プレイヤーの設定処理
//-------------------------------------
void CPlayerShop::Set(D3DXVECTOR3 pos,  D3DXVECTOR3 rot)
{
	// 情報更新
	m_dataPos.Set(pos);		// 位置
	m_dataPosOld.Set(pos);	// 前回の位置

	m_dataSize.Set(D3DXVECTOR3(50.0f, 50.0f, 50.0f));	// 大きさ

	m_dataRot.Set(rot);		// 移動量
	m_dataRotDest.Set(rot);	// 目的の向き
}

//-------------------------------------
//- 購入プレイヤーのイベントの更新処理
//-------------------------------------
void CPlayerShop::UpdateItem(void)
{
	// イベントとの当たり判定
	CollisionItem();
}

//-------------------------------------
//- 購入プレイヤーのイベントとの当たり判定処理
//-------------------------------------
void CPlayerShop::CollisionItem(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();		// 位置
	D3DXVECTOR3 size = m_dataSize.Get();	// 大きさ

	// 変数宣言
	bool bCol = false;	// 当たり判定の有無

	// 変数宣言
	for (int nCutItemObject = 0; nCutItemObject < ITEM_NUM_MAX; nCutItemObject++)
	{
		CItem *pItem = CManagerObject::GetItem(nCutItemObject);

		if (pItem != NULL)
		{
			// 変数宣言（情報取得）
			D3DXVECTOR3 eventObjectPos = pItem->m_dataPos.Get();	// 位置
			D3DXVECTOR3 eventObjectSize = pItem->m_dataSize.Get();	// 大きさ
			bool bUse = pItem->m_bDataUse.Get();					// 使用の有無

			// 使用の有無を判定
			if (bUse == false)
			{
				if (CHit::hitRectangle(pos, size, eventObjectPos, eventObjectSize) == true)
				{
					// イベントアクション処理
					InputItemAction(pItem);

					if (pItem->GetBuyUse() == true)
					{
						// 操作説明UIの有無を判定
						if (m_pUiOprDesc == NULL)
						{
							// 操作説明UIを生成
							m_pUiOprDesc = CUiOprDesc::Create(CUiOprDesc::TEX_SPACE);

							// 操作説明UIの設定処理
							m_pUiOprDesc->Set(
								D3DXVECTOR3(
									SCREEN_WIDTH * 0.8f,
									SCREEN_HEIGHT * 0.7f,
									0.0f),
								D3DXVECTOR3(
									100.0f,
									50.0f,
									0.0f),
								D3DXVECTOR3(
									5.0f,
									5.0f,
									0.0f),
								D3DXVECTOR3(
									0.5f,
									0.5f,
									0.0f)
							);
						}

						// 操作説明文UIの有無を判定
						if (m_pUiTextDesc == NULL)
						{
							// 操作説明文UIを生成
							m_pUiTextDesc = CUiTextDesc::Create(CUiTextDesc::TEX_PUSH);

							// 操作説明文UIの設定処理
							m_pUiTextDesc->Set(
								D3DXVECTOR3(
									SCREEN_WIDTH * 0.77f,
									SCREEN_HEIGHT * 0.64f,
									0.0f),
								D3DXVECTOR3(
									90.0f,
									40.0f,
									0.0f),
								D3DXVECTOR3(
									5.0f,
									5.0f,
									0.0f),
								D3DXVECTOR3(
									0.5f,
									0.5f,
									0.0f)
							);
						}
					}

					// 当たり判定が存在する
					bCol = true;
				}
			}

		}

	}

	if (bCol == false)
	{
		if (m_pUiOprDesc != NULL)
		{
			// 終了処理
			m_pUiOprDesc->Uninit();
			m_pUiOprDesc = NULL;
		}

		if (m_pUiTextDesc != NULL)
		{
			// 説明文UIの終了処理
			m_pUiTextDesc->Uninit();
			m_pUiTextDesc = NULL;
		}
	}

}

//-------------------------------------
//- 購入プレイヤーのイベントアクション処理
//-------------------------------------
void CPlayerShop::InputItemAction(CItem *pItem)
{
	// キーボードの情報取得処理
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

		// 処理を抜ける
		return;
	}

	// スコアの情報取得処理
	CScore *pScore = CGame::GetMgrSysObj()->GetScore();

	// スコアの情報取得の成功を判定
	if (pScore == NULL)
	{// 失敗時

		// 処理を抜ける
		return;
	}

	// アイテムの描画を付ける
	pItem->GetItemInfo()->m_bDataDraw.Set(true);

	// 入力の判定
	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true)
	{// SPACEキー

		// プレイヤーの状態を触るに変更
		m_stateType = STATE_TYPE_BUY;

		// アイテム購入処理
		pItem->Execution();
	}
}

//-------------------------------------
//- 購入プレイヤーのモーション更新処理
//-------------------------------------
void CPlayerShop::UpdateMotion(void)
{
	// 変数宣言
	CMotion *pMotion = GetMotion();			// モーション情報を取得
	D3DXVECTOR3 move = m_dataMove.Get();	// 移動量を取得

	// 移動量で状態を変更
	if (move.x >= 0.3f ||
		move.x <= -0.3f ||
		move.z >= 0.3f ||
		move.z <= -0.3f)
	{
		m_stateType = STATE_TYPE_MOVE;
	}
	else
	{
		m_stateType = STATE_TYPE_NEUTRAL;
	}

	// モーションの終了状況を判定
	if (pMotion->IsFinsih() == true)
	{
		// モーションの更新
		pMotion->Update();
	}

	// モーションの設定処理
	if (m_stateType != m_stateTypeOld)
	{
		// 状態の判定
		switch (m_stateType)
		{
		case STATE_TYPE_NEUTRAL:

			// 待機モーションの設定
			pMotion->Set(STATE_TYPE_NEUTRAL);

			break;

		case STATE_TYPE_MOVE:

			// 移動モーションの設定
			pMotion->Set(STATE_TYPE_MOVE);

			break;

		case STATE_TYPE_BUY:

			// 購入モーションの設定
			pMotion->Set(STATE_TYPE_BUY);

			break;
		}
	}

}