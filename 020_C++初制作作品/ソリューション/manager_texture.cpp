
//================================================
//=
//= テクスチャ管理の処理[manager_texture.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "manager_texture.h"

#include "renderer.h"
#include "manager.h"

#include "bg.h"

#include "number.h"
#include "explosion.h"
#include "block.h"

#include "bullet.h"
#include "effect.h"

#include "obj_3d_field.h"
#include "obj_3d_wall.h"

#include "obj_2d_none.h"
#include "obj_2d_item_info.h"
#include "effect_2d.h"

#include "ui_opr_desc.h"
#include "ui_text_desc.h"

#include "ui_mission.h"
#include "ui_start_text.h"

//-------------------------------------
//-	テクスチャのコンストラクタ
//-------------------------------------
CManagerTexture::CManagerTexture()
{
	// 値のクリア
	ZeroMemory(m_apTexture, sizeof(m_apTexture));
}

//-------------------------------------
//-	テクスチャのデストラクタ
//-------------------------------------
CManagerTexture::~CManagerTexture()
{
}


//-------------------------------------
//-	テクスチャの読み込み処理
//-------------------------------------
HRESULT CManagerTexture::Load(HWND hWnd)
{
	// 背景
	if (FAILED(CBg::Load()))
	{// 失敗時

		// 失敗メッセージ
		MessageBox(hWnd, "背景のデータ", "データ読み込み処理失敗！", MB_ICONWARNING);

		// データ読み込みを抜ける
		return E_FAIL;
	}

	// 数字
	if (FAILED(CNumber::Load()))
	{// 失敗時

		// 失敗メッセージ
		MessageBox(hWnd, "数字のデータ", "データ読み込み処理失敗！", MB_ICONWARNING);

		// データ読み込みを抜ける
		return E_FAIL;
	}

	// 弾
	if (FAILED(CBullet::Load()))
	{// 失敗時

		// 失敗メッセージ
		MessageBox(hWnd, "弾のデータ", "データ読み込み処理失敗！", MB_ICONWARNING);

		// データ読み込みを抜ける
		return E_FAIL;
	}

	// 爆発
	if (FAILED(CExplosion::Load()))
	{// 失敗時

		// 失敗メッセージ
		MessageBox(hWnd, "爆発のデータ", "データ読み込み処理失敗！", MB_ICONWARNING);

		// データ読み込みを抜ける
		return E_FAIL;
	}

	// エフェクト
	if (FAILED(CEffect::Load()))
	{// 失敗時

	 // 失敗メッセージ
		MessageBox(hWnd, "エフェクトのデータ", "データ読み込み処理失敗！", MB_ICONWARNING);

		// データ読み込みを抜ける
		return E_FAIL;
	}

	// ブロック
	if (FAILED(CBlock::Load()))
	{// 失敗時

		// 失敗メッセージ
		MessageBox(hWnd, "ブロックのデータ", "データ読み込み処理失敗！", MB_ICONWARNING);

		// データ読み込みを抜ける
		return E_FAIL;
	}

	// フィールド
	if (FAILED(CObj3dField::Load()))
	{
		// 失敗メッセージ
		MessageBox(hWnd, "フィールドのデータ", "データ読み込み処理失敗！", MB_ICONWARNING);

		// データ読み込みを抜ける
		return E_FAIL;
	}

	// ウォール
	if (FAILED(CObj3dWall::Load()))
	{
		// 失敗メッセージ
		MessageBox(hWnd, "ウォールのデータ", "データ読み込み処理失敗！", MB_ICONWARNING);

		// データ読み込みを抜ける
		return E_FAIL;
	}

	// 効果なし2D
	if (FAILED(CObj2dNone::Load()))
	{
		// 失敗メッセージ
		MessageBox(hWnd, "効果なし2Dオブジェクトデータ", "データ読み込み処理失敗！", MB_ICONWARNING);

		// データ読み込みを抜ける
		return E_FAIL;
	}
	
	// 2Dアイテム情報
	if (FAILED(CEffect2d::Load()))
	{
		// 失敗メッセージ
		MessageBox(hWnd, "2Dエフェクトデータ", "データ読み込み処理失敗！", MB_ICONWARNING);

		// データ読み込みを抜ける
		return E_FAIL;
	}

	// 2Dアイテム情報
	if (FAILED(CObj2dItemInfo::Load()))
	{
		// 失敗メッセージ
		MessageBox(hWnd, "2Dアイテム情報データ", "データ読み込み処理失敗！", MB_ICONWARNING);

		// データ読み込みを抜ける
		return E_FAIL;
	}

	// 操作説明UI情報
	if (FAILED(CUiOprDesc::Load()))
	{
		// 失敗メッセージ
		MessageBox(hWnd, "操作説明UI情報データ", "データ読み込み処理失敗！", MB_ICONWARNING);

		// データ読み込みを抜ける
		return E_FAIL;
	}

	// 操作説明UI情報
	if (FAILED(CUiTextDesc::Load()))
	{
		// 失敗メッセージ
		MessageBox(hWnd, "操作説明文UI情報データ", "データ読み込み処理失敗！", MB_ICONWARNING);

		// データ読み込みを抜ける
		return E_FAIL;
	}

	// 操作説明文UI情報
	if (FAILED(CUiTextDesc::Load()))
	{
		// 失敗メッセージ
		MessageBox(hWnd, "操作説明文UI情報データ", "データ読み込み処理失敗！", MB_ICONWARNING);

		// データ読み込みを抜ける
		return E_FAIL;
	}

	// 目的UIの情報
	if (FAILED(CUiMission::Load()))
	{
		// 失敗メッセージ
		MessageBox(hWnd, "目的UIの情報データ", "データ読み込み処理失敗！", MB_ICONWARNING);

		// データ読み込みを抜ける
		return E_FAIL;
	}

	// 開始説明文の情報
	if (FAILED(CUiStartText::Load()))
	{
		// 失敗メッセージ
		MessageBox(hWnd, "開始説明文のデータ", "データ読み込み処理失敗！", MB_ICONWARNING);

		// データ読み込みを抜ける
		return E_FAIL;
	}


	// 成功を返す
	return S_OK;
}

//-------------------------------------
//-	テクスチャの破棄処理
//-------------------------------------
void CManagerTexture::Unload(void)
{
	for (int nCount = 0; nCount < MANAGER_TEXTUTE_MAX; nCount++)
	{
		// テクスチャの有無を判定
		if (m_apTexture[nCount] != NULL)
		{
			// 開放処理
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//-------------------------------------
//-	テクスチャの指定読み込み処理
//-------------------------------------
int CManagerTexture::Regist(const char *pFilename)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// デバイスの情報取得の成功を判定
	if (pDevice == NULL)
	{// 失敗時

		// 初期化処理を抜ける
		return -1;
	}

	// ファイル名を判定（テクスチャなし）
	if (pFilename == NULL)
	{
		return 0;
	}
	
	for (int nCount = 1; nCount < MANAGER_TEXTUTE_MAX; nCount++)
	{
		// テクスチャの有無を判定
		if (m_apTexture[nCount] == NULL)
		{
			// テクスチャの読み込み if(テクスチャ読み込み成功の有無を判定)
			if (FAILED(D3DXCreateTextureFromFile(
				pDevice,
				pFilename,
				&m_apTexture[nCount])))
			{
				// 失敗を返す
				return -1;
			}

			// 現在の番号を返す
			return nCount;
		}
	}
	
	// 失敗を返す
	return -1;
}

//-------------------------------------
//-	テクスチャの取得処理
//-------------------------------------
LPDIRECT3DTEXTURE9 CManagerTexture::GetAddress(int nldx)
{
	// テクスチャを返す
	return m_apTexture[nldx];
}
