
//================================================
//=
//=	ポーズ画面処理[pause.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "pause.h"

#include "object2d.h"

#include "manager.h"
#include "renderer.h"

#include "manager_texture.h"

#include "fade.h"

#include "object.h"
#include "camera.h"

#include "Input.h"
#include "xinput.h"
#include "sound.h"

//=======================================
//=	マクロ定義
//=======================================

#define WINDOW_POS_X		(SCREEN_WIDTH * 0.5f)	//ポーズの枠の位置(X)
#define WINDOW_POS_Y		(SCREEN_HEIGHT * 0.5f)	//ポーズの枠の位置(Y)
#define WINDOW_SIZE_X		(300.0f)				//ポーズの枠のサイズ(X)
#define WINDOW_SIZE_Y		(200.0f)				//ポーズの枠のサイズ(Y)
#define MENU_POS_X			(SCREEN_WIDTH * 0.5f)	//ポーズメニューの最初の開始位置（X)
#define MENU_POS_Y			(230.0f)				//ポーズメニューの最初の開始位置（Y）	
#define MENU_SIZE_X			(200.0f)				//ポーズメニューの大きさ（X）
#define MENU_SIZE_Y			(60.0f)					//ポーズメニューの大きさ（Y）
#define MENU_INTERVAL_Y		(130.0f)				//ポーズメニューの間隔（Y）

//=======================================
//=	コンスト定義
//=======================================

// ポーズのテクスチャ
const char* Texture[] =
{
	"data\\TEXTURE\\Pause\\Bg.jpg",				// 背景
	"data\\TEXTURE\\Pause\\BackToGame.png",		// ゲーム続行テクスチャ
	"data\\TEXTURE\\Pause\\GameRetry.png",		// ゲームやり直しテクスチャ
	"data\\TEXTURE\\Pause\\QuitTitle.png",		// タイトルに戻るテクスチャ
	"data\\TEXTURE\\Pause\\Cursor.png",			// カーソルテクスチャ
};

//=======================================
//=	静的変数宣言
//=======================================

int CPause::m_nTextureNldx[TEX_MAX] = {};

//-------------------------------------
//-	ポーズのコンストラクタ
//-------------------------------------
CPause::CPause()
{
	ZeroMemory(&m_infoVisual,sizeof(m_infoVisual));
	m_typeSelect = (TYPE_SELECT)0;
	m_bOk = false;
}

//-------------------------------------
//-	ポーズのデストラクタ
//-------------------------------------
CPause::~CPause()
{

}

//-------------------------------------
//-	ポーズのデータ読み込み
//-------------------------------------
HRESULT CPause::Load(void)
{
	// 情報取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	CManagerTexture* pManagerTexture = CManager::GetInstance()->GetManagerTexture();

	// 情報取得の成功を判定
	if (pDevice == nullptr ||
		pManagerTexture == nullptr)
	{// 失敗時

		// 初期化処理を抜ける
		return E_FAIL;
	}

	// テクスチャ設定
	for (int nCount = 0; nCount < TEX_MAX; nCount++)
	{
		// テクスチャ番号の取得（テクスチャの割当）
		m_nTextureNldx[nCount] = pManagerTexture->Regist(Texture[nCount]);

		// テクスチャの読み込み成功の有無を確認
		if (m_nTextureNldx[nCount] == -1)
		{
			// 失敗時に初期化処理を抜ける
			return E_FAIL;
		}
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//-	ポーズのデータ破棄
//-------------------------------------
void CPause::Unload(void)
{
}

//-------------------------------------
//- ポーズの初期化処理
//-------------------------------------
HRESULT CPause::Init(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_infoVisual.apObj2d[nCnt] == NULL)
		{
			// オブジェクト管理の生成
			m_infoVisual.apObj2d[nCnt] = CObject2d::Create();

			// オブジェクト管理の初期化処理
			if (m_infoVisual.apObj2d[nCnt] == NULL)
			{// 失敗時

				// 初期化を抜ける
				return E_FAIL;
			}
		}
		else
		{// ゴミが入っているとき

			// 初期化を抜ける
			return E_FAIL;
		}
	}

	for (int nCutPause = 0; nCutPause < TYPE_MAX; nCutPause++)
	{
		if (m_infoVisual.apObj2d[nCutPause] != nullptr)
		{
			if (nCutPause == TYPE_BG)
			{
				m_infoVisual.apObj2d[nCutPause]->SetInit(
					D3DXVECTOR3(WINDOW_POS_X, WINDOW_POS_Y, 0.0f),
					D3DXVECTOR3(WINDOW_SIZE_X, WINDOW_SIZE_Y, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else if (nCutPause == TYPE_CURSOR)
			{
				m_infoVisual.apObj2d[nCutPause]->SetInit(
					D3DXVECTOR3(MENU_POS_X - 250.0f, MENU_POS_Y, 0.0f),
					D3DXVECTOR3(30.0f, 30.0f, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				m_infoVisual.apObj2d[nCutPause]->SetInit(
					D3DXVECTOR3(MENU_POS_X, MENU_POS_Y + (MENU_INTERVAL_Y * (nCutPause - 1)), 0.0f),
					D3DXVECTOR3(MENU_SIZE_X, MENU_SIZE_Y, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}

			m_infoVisual.apObj2d[nCutPause]->BindTexture(m_nTextureNldx[nCutPause]);
		}


	}

	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	if (pCamera != nullptr)
	{
		pCamera->SetIsUpdateStop(true);
	}

	// 全停止処理
	CObject::SetIsUpdateAllStop(true);

	// オブジェクトの更新停止除外
	for (int nCutPause = 0; nCutPause < TYPE_MAX; nCutPause++)
	{
		m_infoVisual.apObj2d[nCutPause]->SetIsUpdatePause(true);
	}


	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- ポーズの終了処理
//-------------------------------------
void CPause::Uninit(void)
{
	for (int nCutPause = 0; nCutPause < TYPE_MAX; nCutPause++)
	{
		if (m_infoVisual.apObj2d[nCutPause] != NULL)
		{
			// 効果なし2Dオブジェクトの開放処理
			m_infoVisual.apObj2d[nCutPause]->Uninit();
			m_infoVisual.apObj2d[nCutPause] = NULL;
		}
	}

	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	
	if (pCamera != nullptr)
	{
		pCamera->SetIsUpdateStop(false);
	}

	// 全停止処理
	CObject::SetIsUpdateAllStop(false);

}

//-------------------------------------
//- ポーズの更新処理
//-------------------------------------
void CPause::Update(void)
{
	// 情報取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CXInput* pXInput = CManager::GetInstance()->GetXInput();

	// 情報取得の成功を判定
	if (pInputKeyboard == NULL ||
		pXInput == NULL)
	{// 失敗時

		// 更新処理を抜ける
		return;
	}

	if (pInputKeyboard->GetTrigger(DIK_W) != NULL)
	{
		// 種類を加算
		m_typeSelect = (TYPE_SELECT)(m_typeSelect - 1);

		if (m_typeSelect < 0)
		{
			m_typeSelect = TYPE_SELECT_TITLE;
		}

		m_infoVisual.apObj2d[TYPE_CURSOR]->SetPos(
			D3DXVECTOR3(
				MENU_POS_X - 250.0f, 
				MENU_POS_Y + (MENU_INTERVAL_Y * m_typeSelect),
				0.0f));

	}
	else if (pInputKeyboard->GetTrigger(DIK_S) != NULL)
	{
		// 種類を加算
		m_typeSelect = (TYPE_SELECT)(m_typeSelect + 1);

		if (m_typeSelect > TYPE_SELECT_TITLE)
		{
			m_typeSelect = (TYPE_SELECT)0;
		}

		m_infoVisual.apObj2d[TYPE_CURSOR]->SetPos(
			D3DXVECTOR3(
				MENU_POS_X - 250.0f, 
				MENU_POS_Y + (MENU_INTERVAL_Y * m_typeSelect), 
				0.0f));
	}
	
	if (pInputKeyboard->GetTrigger(DIK_RETURN) != NULL)
	{
		m_bOk = true;
	}
}

//-------------------------------------
//- ポーズの描画処理
//-------------------------------------
void CPause::Draw(void)
{

}

//-------------------------------------
//- ポーズの生成処理
//-------------------------------------
CPause *CPause::Create(void)
{
	// ポーズの生成
	CPause *pCPause = DBG_NEW CPause;

	// 生成の成功の有無を判定
	if (pCPause != NULL)
	{
		// 初期化処理
		if (FAILED(pCPause->Init()))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCPause == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// ポーズのポインタを返す
	return pCPause;
}

