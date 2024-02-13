
//-===============================================
//-
//-	エネミーピンの処理のヘッダー[enemy_pin.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _ENEMY_PIN_H_		// このマクロが定義されなかったら
#define _ENEMY_PIN_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object_x.h"

#include "data.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	クラス定義
//-======================================

// 敵のクラス
class CEnemyPin : public CObjectX
{

public:

	// イベントオブジェクトのモデル
	typedef enum
	{
		MODEL_ENEMY_PIN = 0,	// 自販機
		MODEL_MAX
	}MODEL;

	CEnemyPin();
	~CEnemyPin();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEnemyPin * Create(MODEL model);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	int GetModel(void);
	void SetModel(int nModelNldx);

	static CDataInt m_nDataModelNldx[MODEL_MAX];	// モデルの番号

private:

	MODEL m_model;							// 自分自身のモデル
};

//-======================================
//- プロトタイプ宣言
//-======================================

#endif	// 二重インクルード防止の終了
#pragma once
