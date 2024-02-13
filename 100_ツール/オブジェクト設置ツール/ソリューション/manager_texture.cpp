
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

#include "field.h"

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
	// フィールド
	if (FAILED(CField::Load()))
	{
		// 失敗メッセージ
		MessageBox(hWnd, "フィールドのデータ", "データ読み込み処理失敗！", MB_ICONWARNING);

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

	for (int nCount = 0; nCount < MANAGER_TEXTUTE_MAX; nCount++)
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
