
//-===============================================
//-
//-	タイマーの処理のヘッダー[timer.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _TIMER_H_		// このマクロが定義されなかったら
#define _TIMER_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "number.h"

#include "data.h"

//=======================================
//=	マクロ定義
//=======================================

#define TIMER_NUM_MAX	(4)		// タイマーの使用数

#define GAME_TIME		(180)	// ゲーム時間

//-======================================
//-	クラス定義
//-======================================

class CTimer
{

public:

	CTimer();
	~CTimer();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTimer *Create(void);
	HRESULT CreateNumber(void);

	void NullAllNumber(void);

	void NumberTex(void);

	void Elapsed(void);

	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 interval, D3DXVECTOR3 between);
	void SetSize(D3DXVECTOR3 size);

	void SetNumber(void);

	void SetTime(int nTime);
	
	CDataD3DXVECTOR3 m_dataPos;			// 位置
	CDataD3DXVECTOR3 m_dataInterval;	// 間隔
	CDataD3DXVECTOR3 m_dataBetween;		// 区切りの間隔

	CDataD3DXVECTOR3 m_dataSize;		// サイズ

	CDataInt m_nDataTime;				// スコアの値

	CDataInt m_nTimerCount;				// タイマーのカウント

private:

	CNumber *m_apNumber[TIMER_NUM_MAX];	// タイマー用の数字

};

#endif	// 二重インクルード防止の終了
