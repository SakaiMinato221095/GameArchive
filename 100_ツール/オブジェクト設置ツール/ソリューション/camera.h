

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

#include "data.h"

//=======================================
//=	クラス定義
//=======================================

// カメラのクラス
class CCamera
{

public:

	// カメラモード
	typedef enum
	{
		MODE_NORMAL = 0,	// 通常
		MODE_SHOP,			// 店用の視点
		MODE_MAX
	}MODE;

	CCamera();
	~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void UpdateOperation(void);

	void SetCamera(void);

	CDataD3DXVECTOR3 m_dataPosV;			// 視点
	CDataD3DXVECTOR3 m_dataPosVDest;		// 目的の視点

	CDataD3DXVECTOR3 m_dataPosR;			// 注視点
	CDataD3DXVECTOR3 m_dataPosRDest;		// 目的の注視点

	CDataD3DXVECTOR3 m_dataVecU;			// 上方向ベクトル

	CDataD3DXVECTOR3 m_dataRot;				// 向き
	CDataD3DXVECTOR3 m_dataRotDest;			// 目的の向き

	CDataFloat m_fDataLength;				// 長さ

private:

	void SetMode(void);

	D3DXMATRIX m_mtxProjectien;		// プロジェクションマトリックス
	D3DXMATRIX m_mtxView;			// ビューマトリックス

	MODE m_mode;					// カメラのモード

};

#endif	// 二重インクルード防止の終了