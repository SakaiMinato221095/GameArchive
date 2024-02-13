
//-===============================================
//-
//-	ゴミ収集の処理のヘッダー[garbage_collect.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _GARBAGE_COLLECT_H_		// このマクロが定義されなかったら
#define _GARBAGE_COLLECT_H_		// 二重インクルード帽子のマクロを定義

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

// ゴミのクラス
class CGarbageCollect : public CObjectX
{

public:

	// ゴミのモデル
	typedef enum
	{
		MODEL_GARBAGE_CAR_000 = 0,	// ゴミ回収車
		MODEL_GARBAGE_CAR_DARK_000,	// 闇のゴミ回収車
		MODEL_MAX
	}MODEL;

	// モデル情報
	typedef struct
	{
		D3DXVECTOR3 size;	// 大きさ
	}ModelData;

	CGarbageCollect();
	~CGarbageCollect();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGarbageCollect * Create(MODEL model);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	int GetModel(void);
	void SetModel(int nModelNldx);

	static void SetModelData(int nNum, ModelData modelData);
	static ModelData GetModelData(int nNum);

	void Execution(int nNum);

	static CDataInt m_nDataModelNldx[MODEL_MAX];	// モデルの番号

	CDataInt m_nDataEffectCount;					// エフェクト出現のカウント

private:

	void InitSet(MODEL model);

	MODEL m_model;							// 自分自身のモデル

	static ModelData m_modelData[MODEL_MAX];	// モデルの情報
};

#endif	// 二重インクルード防止の終了