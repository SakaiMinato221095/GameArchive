
//-===============================================
//-
//-	オブジェクトイベントの処理のヘッダー[event_object.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _EVENT_OBJECT_H_		// このマクロが定義されなかったら
#define _EVENT_OBJECT_H_		// 二重インクルード帽子のマクロを定義

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

// 敵のクラス
class CEventObject : public CObjectX
{

public:

	// イベントオブジェクトのモデル
	typedef enum
	{
		MODEL_DRINK_SHOP_000 = 0,	// 自販機
		MODEL_VEGETABLE_000,		// カジノ
		MODEL_MAX
	}MODEL;

	// モデル情報
	typedef struct
	{
		D3DXVECTOR3 size;	// 大きさ
	}ModelData;

	CEventObject(int nPriority = 3);
	~CEventObject();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEventObject * Create(MODEL model);

	int GetModel(void);
	void SetModel(int nModelNldx);

	static void SetModelData(int nNum, ModelData modelData);
	static ModelData GetModelData(int nNum);

	void Execution(void);

	static CDataInt m_nDataModelNldx[MODEL_MAX];	// モデルの番号

	CDataInt m_nDataReuseTime;		// 再使用時間
	CDataInt m_nDataReuseCount;		// 再使用カウント
	CDataBool m_bDataUse;			// 使用の有無

	CDataInt m_nDataEffectCount;	// エフェクト出現のカウント

	CDataInt m_nGetScore;			// 入手スコア

private:

	void InitSet(MODEL model);

	void UpdateReuse(void);
	void AvailableDisplay(void);

	static int m_nEventObjectNum;			// イベントオブジェクトの総数

	MODEL m_model;							// 自分自身のモデル
	CScore::GET_TYPE m_scoreGetType;		// スコアの取得系統

	static ModelData m_modelData[MODEL_MAX];	// モデルの情報
};

//-======================================
//- プロトタイプ宣言
//-======================================

#endif	// 二重インクルード防止の終了
