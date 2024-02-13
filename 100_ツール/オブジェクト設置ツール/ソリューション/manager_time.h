
//================================================
//=
//=	時間管理処理のヘッダー[manager_time.h]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	二重インクルード防止
//=======================================

#ifndef _MANAGER_TIME_H_		// このマクロが定義されなかったら
#define _MANAGER_TIME_H_		// 二重インクルード帽子のマクロを定義

//=======================================
//=	インクルード
//=======================================

#include "data.h"

//=======================================
//=	クラス定義
//=======================================

class CManagerTime
{
public:

	CManagerTime();
	~CManagerTime();

	void Init(void);
	void Uninit(void);

	void Update(void);

	static CManagerTime *Create();

	float CalRate(float data);
	D3DXVECTOR3 CalRate(D3DXVECTOR3 data);

	void Set(float fTimeRate,int nTimeMax);	// 時間倍率設定処理

	CDataFloat m_fDataTimeRate;				// 時間倍率
	CDataInt m_nDataTimeCountMax;			// 時間カウントの最大値
	CDataInt m_nDataTimeCount;				// 時間カウント
	
	CDataBool m_bDataIntCount;				// 整数のカウントの有無

private:

};

#endif	// 二重インクルード防止の終了

