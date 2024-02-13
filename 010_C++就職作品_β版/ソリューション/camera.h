

//================================================
//=
//= カメラのヘッター[camera.h]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	二重インクルード防止
//=======================================

#ifndef _CAMERA_H_	//このマクロが定義されなかったら
#define _CAMERA_H_	//二重インクルード帽子のマクロを定義

//=======================================
//=	インクルード
//=======================================

//=======================================
//=	クラス定義
//=======================================

// カメラのクラス
class CCamera
{

public:

	// カメラの値情報
	typedef struct
	{
		D3DXVECTOR3 posV;			// 視点
		D3DXVECTOR3 posVDest;		// 目的の視点

		D3DXVECTOR3 posR;			// 注視点
		D3DXVECTOR3 posRDest;		// 目的の注視点

		D3DXVECTOR3 vecU;			// 上方向ベクトル

		D3DXVECTOR3 rot;			// 向き
		D3DXVECTOR3 rotDest;		// 目的の向き

		float fLength;				// 長さ
	}Data;

	// カメラモード
	typedef enum
	{
		MODE_NORMAL = 0,	// 通常
		MODE_FOLLOWING,		// 追尾
		MODE_TITLE,			// タイトル
		MODE_MAX
	}MODE;

	CCamera();
	~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void SetCamera(void);

	void SetMode(CCamera::MODE mode);

	Data GetData(void) { return m_data; }

	bool GetIsUpdateStop(void) { return m_bIsUpdateStop;}
	void SetIsUpdateStop(bool bUpdateStop) { m_bIsUpdateStop = bUpdateStop; }
private:
	
	void UpdateRot(void);
	void UpdateTitle(void);

	void CameraPlayer(void);

	D3DXMATRIX m_mtxProjectien;		// プロジェクションマトリックス
	D3DXMATRIX m_mtxView;			// ビューマトリックス

	MODE m_mode;					// カメラのモード

	Data m_data;					// カメラの値情報を格納

	bool m_bIsUpdateStop;			// 更新の停止

};

#endif	// 二重インクルード防止の終了