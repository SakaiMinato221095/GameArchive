
//-===============================================
//-
//-	エフェクトの処理のヘッダー[effect_object.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _EFFECT_OBJECT_H_		// このマクロが定義されなかったら
#define _EFFECT_OBJECT_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object_x.h"

#include "data.h"

//-======================================
//-	クラス定義
//-======================================

class CEffectObject : public CObjectX
{

public:

	// エフェクトオブジェクトのモデル
	typedef enum
	{
		MODEL_COIN_000 = 0,	// コイン
		MODEL_BIN_000,		// 瓶
		MODEL_MAX
	}MODEL;

	CEffectObject(int nPriority = 3);
	~CEffectObject();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEffectObject *Create(MODEL model);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXVECTOR3 moveMax);

	void Add(void);
	bool Sub(void);

	CDataD3DXVECTOR3 m_dataSizeHold;	// サイズを保持

	CDataD3DXVECTOR3 m_dataMove;		// 移動量

	CDataD3DXVECTOR3 m_dataMoveAcu;		// 移動量の蓄積値
	CDataD3DXVECTOR3 m_dataMoveMax;		// 移動量の最大値

	CDataD3DXVECTOR3 m_dataAddRot;		// 回転量

	CDataInt m_nDataLife;				// 体力

	CDataBool m_bDataZTestOff;			// Zテストの有無

private:

	static int m_nModelNldx[MODEL_MAX];	// モデルの番号

};

//-======================================
//- プロトタイプ宣言
//-======================================

#endif	// 二重インクルード防止の終了
