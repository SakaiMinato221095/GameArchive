
//================================================
//=
//=	タイトル画面処理[title.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "title.h"

#include "manager.h"
#include "renderer.h"

#include "manager_texture.h"

#include "camera.h"

#include "fade.h"

#include "Input.h"
#include "xinput.h"
#include "sound.h"

#include "character.h"

#include "skybox.h"
#include "obj_3d_field.h"

#include "object2d.h"

//=======================================
//=	コンスト定義
//=======================================

// テクスチャ情報
const char* pDataTexture[CTitle::TEX_MAX] =
{
	"data\\TEXTURE\\Title\\Logo000.png",		// タイトルロゴのテクスチャ
	"data\\TEXTURE\\Title\\Button000.png",		// タイトルボタンのテクスチャ
};

//=======================================
//=	静的変数宣言
//=======================================

CCharacter *CTitle::m_pCharacter = {};
CObject2d *CTitle::m_apObj2d[TYPE_2D_MAX] = {};
int CTitle::m_aTextureNldx[TEX_MAX] = {};

//-------------------------------------
//-	タイトルのコンストラクタ
//-------------------------------------
CTitle::CTitle()
{

}

//-------------------------------------
//-	タイトルのデストラクタ
//-------------------------------------
CTitle::~CTitle()
{

}

//-------------------------------------
//- 通常2Dオブジェクトの読み込み処理
//-------------------------------------
HRESULT CTitle::Load(void)
{
	// 取得処理
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	CManagerTexture* pManagerTexture = CManager::GetInstance()->GetManagerTexture();

	// 取得の有無を判定
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
		m_aTextureNldx[nCount] = pManagerTexture->Regist(pDataTexture[nCount]);

		// テクスチャの読み込み成功の有無を確認
		if (m_aTextureNldx[nCount] == -1)
		{
			// 失敗時に初期化処理を抜ける
			return E_FAIL;
		}
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 背景の読み込んだテクスチャの破棄
//-------------------------------------
void CTitle::Unload(void)
{

}

//-------------------------------------
//- タイトルの初期化処理
//-------------------------------------
HRESULT CTitle::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// 情報取得
	CCamera *pCamera = CManager::GetInstance()->GetCamera();
	CSound* pSound = CManager::GetInstance()->GetSound();

	// 取得の有無を判定
	if (pCamera == nullptr ||
		pSound == nullptr)
	{
		return E_FAIL;
	}

	// カメラの設定処理
	pCamera->SetMode(CCamera::MODE_TITLE);

	// タイトルの再生
	pSound->Play(CSound::LABEL_BGM_TITLE);

	// スカイボックスの生成
	CSkybox::Create(
		CSkybox::MODEL_SKYBOX_000,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// フィールドの生成
	CObj3dField* pField = CObj3dField::Create(CObj3dField::TEX_GLASS_000);

	if (pField != nullptr)
	{
		pField->InitSet(
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(5000.0f, 0.0f, 5000.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			D3DXVECTOR2(10.0f, 10.0f));
	}

	if (m_pCharacter == NULL)
	{
		// プレイヤーの生成
		m_pCharacter = CCharacter::Create(
			CModel::MODEL_TYPE_PLAYER,			// モデル
			CMotion::MOTION_TYPE_PLAYER,
			1);			// モーション
	}

	for (int nCnt2d = 0; nCnt2d < TYPE_2D_MAX; nCnt2d++)
	{
		if (m_apObj2d[nCnt2d] == nullptr)
		{
			switch (nCnt2d)
			{
			case TYPE_2D_LOGO:

				// オブジェクト管理の生成
				m_apObj2d[nCnt2d] = CObject2d::Create();

				if (m_apObj2d[nCnt2d] != nullptr)
				{
					m_apObj2d[nCnt2d]->SetInit(
						D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.3f, 0.0f),
						D3DXVECTOR3(300.0f, 150.0f, 0.0f),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

					m_apObj2d[nCnt2d]->BindTexture(m_aTextureNldx[nCnt2d]);
				}

				break;

			case TYPE_2D_BUTTON:

				// オブジェクト管理の生成
				m_apObj2d[nCnt2d] = CObject2d::Create();

				if (m_apObj2d[nCnt2d] != nullptr)
				{
					m_apObj2d[nCnt2d]->SetInit(
						D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.8f, 0.0f),
						D3DXVECTOR3(200.0f, 100.0f, 0.0f),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

					m_apObj2d[nCnt2d]->BindTexture(m_aTextureNldx[nCnt2d]);
				}

				break;
			}

			if (m_apObj2d[nCnt2d] == nullptr)
			{
				// 失敗メッセージ
				MessageBox(hWnd, "2Dオブジェクトの生成", "初期処理失敗！", MB_ICONWARNING);

				// 初期化を抜ける
				return E_FAIL;
			}
		}
		else
		{
			// 失敗メッセージ
			MessageBox(hWnd, "2Dオブジェクトの生成", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- タイトルの終了処理
//-------------------------------------
void CTitle::Uninit(void)
{
	if (m_pCharacter != NULL)
	{
		m_pCharacter->Uninit();
		m_pCharacter = NULL;
	}

	for (int nCount = 0; nCount < TYPE_2D_MAX; nCount++)
	{
		m_apObj2d[nCount]->Uninit();
		m_apObj2d[nCount] = nullptr;
	}

	// オブジェクトの全開放処理
	CObject::ReleaseAll();
}

//-------------------------------------
//- タイトルの更新処理
//-------------------------------------
void CTitle::Update(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

		// 更新処理を抜ける
		return;
	}

	// X入力のポインタを宣言
	CXInput *pXInput = CManager::GetInstance()->GetXInput();

	// X入力の情報取得の成功を判定
	if (pXInput == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 遷移ボタン（えんたー）
	if (pInputKeyboard->GetTrigger(DIK_RETURN) != NULL || 
		pXInput->GetTrigger(XINPUT_GAMEPAD_A,CXInput::TYPE_INPUT_BUTTON))
	{
		// ゲームモード
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_GAME);
	}
}

//-------------------------------------
//- タイトルの描画処理
//-------------------------------------
void CTitle::Draw(void)
{

}