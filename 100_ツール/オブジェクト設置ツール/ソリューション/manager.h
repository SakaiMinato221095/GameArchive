
//-===============================================
//-
//-	管理処理のヘッダー[manager.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _MANAGER_H_		// このマクロが定義されなかったら
#define _MANAGER_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

//-======================================
//-	前方宣言
//-======================================

class CManagerObject;

class CRenderer;
class CInputKeyboard;
class CSound;
class CDebugProc;

class CManagerTexture;
class CManagerModel;
class CManagerTime;

class CCamera;
class CLight;

class CEditMap;

//-======================================
//-	クラス定義
//-======================================

class CManager
{

public:

	CManager();
	virtual ~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CManagerObject *GetManagerObject(void);

	static CRenderer *GetRenderer(void);
	static CInputKeyboard *GetInputKeyboard(void);
	static CSound *GetSound(void);
	static CDebugProc *GetDbugProc(void);

	static CManagerTexture *GetManagerTexture(void);
	static CManagerModel *GetManagerModel(void);
	static CManagerTime *GetManagerTime(void);

	static CCamera *GetCamera(void);
	static CLight *GetLight(void);

	static CEditMap *GetMapEdit(void);

private:

	void DebugCommand(void);					// デバック入力

	static CManagerObject *m_pManagerObject;	// オブジェクト管理のポインタ

	static CRenderer *m_pRenderer;				// レンダラーのポインタ
	static CInputKeyboard *m_pInputKeyboard;	// キーボードのポインタ
	static CSound *m_pSound;					// サウンドのポインタ
	static CDebugProc *m_pDbugProc;				// デバックのポインタ

	static CManagerTexture *m_pManagerTexture;	// テクスチャ管理のポインタ
	static CManagerModel *m_pManagerModel;		// モデル管理のポインタ
	static CManagerTime *m_pManagerTime;		// 時間管理のポインタ

	static CCamera *m_pCamera;					// カメラのポインタ
	static CLight *m_pLight;					// ライトのポインタ

	static CEditMap *m_pMapEdit;				// マップエディタのポインタ
};

#endif	// 二重インクルード防止の終了
