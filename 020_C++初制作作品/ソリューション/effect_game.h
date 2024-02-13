
//-===============================================
//-
//-	ゲームエフェクトの処理のヘッダー[screen_game.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _EFFECT_GAME_H_		// このマクロが定義されなかったら
#define _EFFECT_GAME_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "data.h"

//-======================================
//-	前方宣言
//-======================================

class CCamera;

//-======================================
//-	クラス定義
//-======================================

class CEffectGame
{

public:

	CEffectGame();
	~CEffectGame();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	static CEffectGame *Create(void);

	void Set(D3DXVECTOR3 rot, D3DXVECTOR3 speed, int nTime, int nLoopCount);

	void AddQuake(D3DXVECTOR3 quakeRot, D3DXVECTOR3 quakeSpeed);
	void SubQuake(D3DXVECTOR3 QuakeRot, D3DXVECTOR3 quakeSpeed);

	CDataD3DXVECTOR3 m_dataRotQuake;		// 画面揺れの向き
	CDataD3DXVECTOR3 m_dataSpeed;			// 画面揺れの速度

	CDataInt m_nDataLife;					// 体力
	CDataInt m_nDataLoopCount;				// ループする回数
	CDataInt m_nDataLifeCount;				// 体力カウント 

	CDataBool m_bDataUse;					// 使用の有無

	CDataD3DXVECTOR3 m_dataPosVQuake;		// 画面揺れの視点
	CDataD3DXVECTOR3 m_dataPosVQuakeDest;	// 画面揺れの目的の視点

	CDataD3DXVECTOR3 m_dataPosRQuake;		// 画面揺れの注視点
	CDataD3DXVECTOR3 m_dataPosRQuakeDest;	// 画面揺れの目的の注視点

private:

};

//-======================================
//- プロトタイプ宣言
//-======================================

#endif	// 二重インクルード防止の終了
