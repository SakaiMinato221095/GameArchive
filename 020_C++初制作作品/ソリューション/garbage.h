
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
		int nScoreHave;		// 保持するスコア
		int nType;			// 種類
		int nNor;			// 通常属性値
		int nLow;			// 聖属性値
		int nChaos;			// 悪属性値
	}ModelData;

	CGarbage(int nPriority = 3);
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

	void Execution(int nEatTime);

	static CDataInt m_nDataModelNldx[MODEL_MAX];	// モデルの番号

	CDataInt m_nDataEffectCount;					// エフェクト出現のカウント
	CDataInt m_nGetScore;							// 入手スコア
	CDataInt m_nType;								// 種類

	CDataInt m_nDataEatCut;							// 食べるカウント
	CDataInt m_nDataEatTime;						// 食べる時間

private:

	void InitSet(MODEL model);

	void AvailableDisplay(void);
	void UpdateEat(void);

	void EatEnd(void);

	MODEL m_model;								// 自分自身のモデル
	CScore::GET_TYPE m_scoreGetType;			// スコアの取得系統

	static ModelData m_modelData[MODEL_MAX];	// モデルの情報
};

#endif	// 二重インクルード防止の終了
