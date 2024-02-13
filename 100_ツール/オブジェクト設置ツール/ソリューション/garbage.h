
//-===============================================
//-
//-	ゴミの処理のヘッダー[garbage.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _GARBAGE_H_		// このマクロが定義されなかったら
#define _GARBAGE_H_		// 二重インクルード帽子のマクロを定義

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
class CGarbage : public CObjectX
{

public:

	// ゴミのモデル
	typedef enum
	{
		MODEL_BIN_000 = 0,			// 瓶

		MODEL_BLOOD_KNIFE,			// 血付きのナイフ
		MODEL_ORGAN_BOTTLE_NONE,	// 中身なし臓器保管瓶
		MODEL_SYRINGE_NONE,			// 中身なし注射器

		MODEL_ICE_CUP,				// かき氷ごみ
		MODEL_OMIKUGI,				// おみくじゴミ
		MODEL_PURAGOMI,				// ぷらごみ

		MODEL_MAX
	}MODEL;

	// モデル情報
	typedef struct
	{
		D3DXVECTOR3 size;	// 大きさ
	}ModelData;

	CGarbage();
	~CGarbage();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGarbage * Create(MODEL model);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	int GetModel(void);
	void SetModel(int nModelNldx);

	static void SetModelData(int nNum, ModelData modelData);
	static ModelData GetModelData(int nNum);

	static CDataInt m_nDataModelNldx[MODEL_MAX];	// モデルの番号

	CDataInt m_nDataEffectCount;	// エフェクト出現のカウント

	CDataInt m_nGetScore;			// 入手スコア

private:

	void InitSet(MODEL model);

	MODEL m_model;							// 自分自身のモデル
	CScore::GET_TYPE m_scoreGetType;		// スコアの取得系統

	static ModelData m_modelData[MODEL_MAX];	// モデルの情報
};

#endif	// 二重インクルード防止の終了
