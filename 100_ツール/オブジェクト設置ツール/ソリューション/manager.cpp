
//-===============================================
//-
//-	管理処理[manager.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "manager.h"

#include "manager_object.h"

#include "Input.h"
#include "sound.h"
#include "debugproc.h"

#include "manager_texture.h"
#include "manager_model.h"
#include "manager_time.h"

#include "camera.h"
#include "light.h"

#include "renderer.h"

#include "object2d.h"

#include "object3d.h"

#include "object_x.h"

#include "object_billboard.h"

#include "object_model.h"

#include "edit_map.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	静的変数宣言
//-======================================

CManagerObject *CManager::m_pManagerObject = NULL;

CRenderer *CManager::m_pRenderer = NULL;

CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CSound *CManager::m_pSound = NULL;
CDebugProc *CManager::m_pDbugProc = NULL;

CManagerTexture *CManager::m_pManagerTexture = NULL;
CManagerModel *CManager::m_pManagerModel = NULL;
CManagerTime *CManager::m_pManagerTime = NULL;

CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;

CEditMap *CManager::m_pMapEdit = NULL;

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CManager::CManager()
{
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CManager::~CManager()
{

}

//-------------------------------------
//- 管理の初期化処理
//-------------------------------------
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// キーボード
	{
		// キーボードの有無を判定
		if (m_pInputKeyboard == NULL)
		{
			// キーボードの生成
			m_pInputKeyboard = new CInputKeyboard;

			// キーボードの初期化処理
			if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
			{// 失敗時

				// 失敗メッセージ
				MessageBox(hWnd, "キーボードの生成", "初期処理失敗！", MB_ICONWARNING);

				// 初期化を抜ける
				return E_FAIL;
			}
		}
		else
		{// ゴミが入っているとき

			// 失敗メッセージ
			MessageBox(hWnd, "キーボードの初期化", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}
	}

	// サウンド
	{
		// サウンド有無を判定
		if (m_pSound == NULL)
		{
			// サウンド生成
			m_pSound = new CSound;

			// サウンド初期化処理
			if (FAILED(m_pSound->Init(hWnd)))
			{// 失敗時

				// 失敗メッセージ
				MessageBox(hWnd, "サウンドの生成", "初期処理失敗！", MB_ICONWARNING);

				// 初期化を抜ける
				return E_FAIL;
			}
		}
		else
		{// ゴミが入っているとき

			// 失敗メッセージ
			MessageBox(hWnd, "サウンドの初期化", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}
	}

	// レンダラー
	{
		// レンダラーの有無を判定
		if (m_pRenderer == NULL)
		{
			// レンダラーの生成
			m_pRenderer = new CRenderer;

			// レンダラーの初期化処理
			if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
			{// 失敗時

				// 失敗メッセージ
				MessageBox(hWnd, "レンダラーの生成", "初期処理失敗！", MB_ICONWARNING);

				// 初期化を抜ける
				return E_FAIL;
			}
		}
		else
		{// ゴミが入っているとき

			// 失敗メッセージ
			MessageBox(hWnd, "レンダラーの初期化", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}
	}

	// デバックプロック
	{
		// デバックプロック有無を判定
		if (m_pDbugProc == NULL)
		{
			// デバックプロック生成
			m_pDbugProc = new CDebugProc;

			// デバックプロック初期化処理
			m_pDbugProc->Init();
		}
	}

	// テクスチャ管理
	{
		// テクスチャ管理の有無を判定
		if (m_pManagerTexture == NULL)
		{
			// テクスチャ管理の生成
			m_pManagerTexture = new CManagerTexture;

			// テクスチャ管理の初期化処理
			if (FAILED(m_pManagerTexture->Load(hWnd)))
			{// 失敗時

				// 失敗メッセージ
				MessageBox(hWnd, "テクスチャ管理の読み込み", "初期処理失敗！", MB_ICONWARNING);

				// 初期化を抜ける
				return E_FAIL;
			}
		}
		else
		{// ゴミが入っているとき

			// 失敗メッセージ
			MessageBox(hWnd, "テクスチャ管理の読み込み", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}
	}

	// モデル管理
	{
		// モデル管理の有無を判定
		if (m_pManagerModel == NULL)
		{
			// モデル管理の生成
			m_pManagerModel = new CManagerModel;

			// モデル管理の初期化処理
			if (FAILED(m_pManagerModel->Load(hWnd)))
			{// 失敗時

				// 失敗メッセージ
				MessageBox(hWnd, "モデル管理の読み込み", "初期処理失敗！", MB_ICONWARNING);

				// 初期化を抜ける
				return E_FAIL;
			}
		}
		else
		{// ゴミが入っているとき

			// 失敗メッセージ
			MessageBox(hWnd, "モデル管理の読み込み", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}
	}

	// 時間管理
	{
		// 時間管理の有無を判定
		if (m_pManagerTime == NULL)
		{
			// 時間管理の生成
			m_pManagerTime = CManagerTime::Create();

			// 時間管理の生成成功の有無を判定
			if (m_pManagerTime == NULL)
			{
				// 失敗メッセージ
				MessageBox(hWnd, "時間管理の生成", "初期処理失敗！", MB_ICONWARNING);

				// 生成処理を抜ける
				return E_FAIL;
			}
		}
	}

	// カメラ
	{
		// カメラの有無を判定
		if (m_pCamera == NULL)
		{
			// カメラの生成
			m_pCamera = new CCamera;

			// カメラの初期化処理
			if (FAILED(m_pCamera->Init()))
			{// 失敗時

				// 失敗メッセージ
				MessageBox(hWnd, "カメラの生成", "初期処理失敗！", MB_ICONWARNING);

				// 初期化を抜ける
				return E_FAIL;
			}
		}
		else
		{// ゴミが入っているとき

			// 失敗メッセージ
			MessageBox(hWnd, "カメラの初期化", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}
	}

	// ライト
	{
		// ライトの有無を判定
		if (m_pLight == NULL)
		{
			// ライトの生成
			m_pLight = new CLight;

			// ライトの初期化処理
			if (FAILED(m_pLight->Init()))
			{// 失敗時

				// 失敗メッセージ
				MessageBox(hWnd, "ライトの生成", "初期処理失敗！", MB_ICONWARNING);

				// 初期化を抜ける
				return E_FAIL;
			}
		}
		else
		{// ゴミが入っているとき

		 // 失敗メッセージ
			MessageBox(hWnd, "ライトの初期化", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}
	}

	// オブジェクト管理の初期化
	{
		// オブジェクト管理の有無を判定
		if (m_pManagerObject == NULL)
		{
			// オブジェクト管理の生成
			m_pManagerObject = new CManagerObject;

			// オブジェクト管理の初期化処理
			if (FAILED(m_pManagerObject->Init(hInstance,hWnd,bWindow)))
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

	// マップエディタの初期化
	{
		// マップエディタの有無を判定
		if (m_pMapEdit == NULL)
		{
			// マップエディタの初期化処理
			if (FAILED(m_pMapEdit = CEditMap::Create(hInstance, hWnd, bWindow)))
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

	// 音の設定
	if (m_pSound != NULL)
	{
		// BGMを流す
		//m_pSound->Play(CSound::LABEL_BGM_GAME_000);
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 管理の終了処理
//-------------------------------------
void CManager::Uninit(void)
{
	// キーボードの破棄
	if (m_pInputKeyboard != NULL)
	{
		// キーボードの終了処理
		m_pInputKeyboard->Uninit();

		// キーボードの開放
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	// サウンドの破棄
	if (m_pSound != NULL)
	{
		// サウンドの終了処理
		m_pSound->Uninit();

		// サウンドの開放
		delete m_pSound;
		m_pSound = NULL;
	}

	// デバックプロックの破棄
	if (m_pDbugProc != NULL)
	{
		// デバックプロックの終了処理
		m_pDbugProc->Uninit();

		// デバックプロックの開放
		delete m_pDbugProc;
		m_pDbugProc = NULL;
	}

	// テクスチャ管理の破棄
	if (m_pManagerTexture != NULL)
	{
		// テクスチャ管理の終了処理
		m_pManagerTexture->Unload();

		// テクスチャ管理の開放
		delete m_pManagerTexture;
		m_pManagerTexture = NULL;
	}

	// モデル管理の破棄
	if (m_pManagerModel != NULL)
	{
		// モデル管理の終了処理
		m_pManagerModel->Unload();

		// モデル管理の開放
		delete m_pManagerModel;
		m_pManagerModel = NULL;
	}

	// 時間管理の破棄
	if (m_pManagerTime != NULL)
	{
		// 時間管理の終了処理
		m_pManagerTime->Uninit();

		// 時間管理の開放
		delete m_pManagerTime;
		m_pManagerTime = NULL;
	}

	// カメラの有無を判定
	if (m_pCamera != NULL)
	{
		// カメラの終了処理
		m_pCamera->Uninit();

		// カメラの開放処理
		delete m_pCamera;
		m_pCamera = NULL;
	}

	// ライトの有無を判定
	if (m_pLight != NULL)
	{
		// ライトの終了処理
		m_pLight->Uninit();

		// ライトの開放処理
		delete m_pLight;
		m_pLight = NULL;
	}

	// オブジェクトの全開放処理
	CObject::ReleaseAll();

	// オブジェクト管理の有無を判定
	if (m_pManagerObject != NULL)
	{
		// オブジェクトの終了
		m_pManagerObject->Uninit();

		// オブジェクト管理の開放処理
		delete m_pManagerObject;
		m_pManagerObject = NULL;
	}

	// マップエディタの開放
	if (m_pMapEdit != NULL)
	{
		// マップエディタの終了
		m_pMapEdit->Uninit();

		// マップエディタ管理の開放処理
		delete m_pMapEdit;
		m_pMapEdit = NULL;
	}

	// レンダラーの破棄
	if (m_pRenderer != NULL)
	{
		// レンダラーの終了処理
		m_pRenderer->Uninit();

		// レンダラーの開放処理
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//-------------------------------------
//- 管理の更新処理
//-------------------------------------
void CManager::Update(void)
{
	// キーボードの有無を判定
	if (m_pInputKeyboard != NULL)
	{
		// キーボードの更新処理
		m_pInputKeyboard->Update();
	}

	// 時間管理の有無を判定
	if (m_pManagerTime != NULL)
	{
		// カメラの更新処理
		m_pManagerTime->Update();
	}

	// カメラの有無を判定
	if (m_pCamera != NULL)
	{
		// カメラの更新処理
		m_pCamera->Update();
	}

	// デバックプロックの有無を判定
	if (m_pDbugProc != NULL)
	{
		// デバックプロックの更新処理
		m_pDbugProc->Update();
	}

	// ライトの有無を判定
	if (m_pLight != NULL)
	{
		// ライトの更新処理
		m_pLight->Update();
	}

	// マップエディタの有無を判定
	if (m_pMapEdit != NULL)
	{
		// マップエディタの更新処理
		m_pMapEdit->Update();
	}

	// レンダラーの有無を判定
	if (m_pRenderer != NULL)
	{
		// レンダラーの更新処理
		m_pRenderer->Update();
	}

	// デバック入力
	DebugCommand();
}

//-------------------------------------
//- 管理の描画処理
//-------------------------------------
void CManager::Draw(void)
{
	// カメラの情報を取得
	CCamera *pCamera = CManager::GetCamera();

	// カメラの有無を判定
	if (pCamera != NULL)
	{
		// カメラの設定
		pCamera->SetCamera();
	}

	// レンダラーの有無を判定
	if (m_pRenderer != NULL)
	{
		// レンダラーの描画処理
		m_pRenderer->Draw();
	}
}

//-------------------------------------
//- オブジェクト管理の情報を取得
//-------------------------------------
CManagerObject * CManager::GetManagerObject(void)
{
	return m_pManagerObject;
}

//-------------------------------------
//- レンダラーの情報を取得
//-------------------------------------
CRenderer *CManager::GetRenderer(void)
{
	// レンダラーのポインタを返す
	return m_pRenderer;
}

//-====================================
//-	キーボードの情報を取得
//-====================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	// キーボードのポインタを返す
	return m_pInputKeyboard;
}

//-====================================
//-	サウンドの情報を取得
//-====================================
CSound *CManager::GetSound(void)
{
	// キーボードのポインタを返す
	return m_pSound;
}

//-====================================
//-	デバックプロックの情報を取得
//-====================================
CDebugProc * CManager::GetDbugProc(void)
{
	// デバックプロックを返す
	return m_pDbugProc;
}

//-====================================
//-	テクスチャ管理の情報を取得
//-====================================
CManagerTexture *CManager::GetManagerTexture(void)
{
	// テクスチャ管理を返す
	return m_pManagerTexture;
}

//-====================================
//-	モデル管理の情報を取得
//-====================================
CManagerModel *CManager::GetManagerModel(void)
{
	return m_pManagerModel;
}

//-====================================
//-	テクスチャ管理の情報を取得
//-====================================
CManagerTime * CManager::GetManagerTime(void)
{
	return m_pManagerTime;
}

//-====================================
//-	カメラの情報を取得
//-====================================
CCamera *CManager::GetCamera(void)
{
	// キーボードのポインタを返す
	return m_pCamera;
}

//-====================================
//-	ライトの情報を取得
//-====================================
CLight * CManager::GetLight(void)
{
	return m_pLight;
}

//-====================================
//-	マップエディタの情報を取得
//-====================================
CEditMap * CManager::GetMapEdit(void)
{
	return nullptr;
}

//-====================================
//-	デバック入力
//-====================================
void CManager::DebugCommand(void)
{
	// キーボードの情報取得の成功を判定
	if (m_pInputKeyboard == NULL)
	{// 失敗時

		// 移動処理を抜ける
		return;
	}
}
