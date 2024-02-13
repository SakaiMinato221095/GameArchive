
//-===============================================
//-
//-	クイックタイムイベント（タイミング）の処理のヘッダー[qte_timing.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _QTE_TIMING_H_		// このマクロが定義されなかったら
#define _QTE_TIMING_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "qte.h"

#include "data.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	前方宣言
//-======================================

class CObj2dNone;
class CObj2dGage;

//-======================================
//-	クラス定義
//-======================================

class CQteTiming : public CQte
{
public:

	CQteTiming();
	~CQteTiming();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CQteTiming *Create(void);

	void InitSet(void);
	void UpdateGage(void);

	void AddGage(void);
	void SubGage(void);

	void Decision(void);

	CDataD3DXVECTOR3 m_dataPos;			// 位置
	CDataD3DXVECTOR3 m_dataSize;		// 大きさ

	CDataInt m_nDataGageTarget;			// 目的のゲージ値
	CDataInt m_nDataGagePlayer;			// プレイヤーのゲージ値

	CDataD3DXVECTOR3 m_dataGageMove;	// プレイヤーゲージの移動量の速度
	CDataBool m_bDataGageMoveDirect;	// プレイヤーゲージの移動量の変化方向

private:

	CObj2dNone *m_pObj2dNone;		// 通常2Dオブジェクトのポインタ
	CObj2dGage *m_pObj2dGageTarget;	// 目的ゲージのポインタ
	CObj2dGage *m_pObj2dGagePlayer;	// プレイヤーゲージのポインタ


};

#endif	// 二重インクルード防止の終了
