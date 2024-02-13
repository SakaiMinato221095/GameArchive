
//-===============================================
//-
//-	ゲートの処理のヘッダー[gate.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _GATE_H_		// このマクロが定義されなかったら
#define _GATE_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object_x.h"

#include "data.h"

#include "score.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	クラス定義
//-======================================

// ゲートのクラス
class CGate : public CObjectX
{

public:

	// ゴミのモデル
	typedef enum
	{
		MODEL_GATE_000 = 0,	// ゲートのモデル000
		MODEL_MAX
	}MODEL;

	CGate(int nPriority = 3);
	~CGate();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGate * Create(MODEL model);

	int GetModel(void);
	void SetModel(int nModelNldx);

	void Execution();

	static CDataInt m_nDataModelNldx[MODEL_MAX];	// モデルの番号

	CDataInt m_nDataEffectCount;					// エフェクト出現のカウント
private:

	void InitSet(MODEL model);

	void AvailableDisplay(void);

	MODEL m_model;								// 自分自身のモデル
};

#endif	// 二重インクルード防止の終了
