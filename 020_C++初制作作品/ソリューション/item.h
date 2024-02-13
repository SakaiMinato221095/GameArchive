
//-===============================================
//-
//-	アイテム処理のヘッダー[item.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _ITEM_H_		// このマクロが定義されなかったら
#define _ITEM_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object_x.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	前方宣言
//-======================================

class CObj2dItemInfo;

//-======================================
//-	クラス定義
//-======================================

// アイテムのクラス
class CItem : public CObjectX
{

public:

	typedef enum
	{
		MODEL_GUN_000 = 0,	// ステータス装備（銅）
		MODEL_GUN_001,		// ステータス装備（銀）
		MODEL_GUN_002,		// ステータス装備（金）
		MODEL_BOMB_000,		// ボム
		MODEL_MAX
	}MODEL;

	// モデル情報
	typedef struct
	{
		D3DXVECTOR3 size;	// 大きさ
		int nType;			// 種類
		int nBuyMax;		// 最大購入回数
		int nPrice;			// 値段
	}ModelData;

	CItem();
	~CItem();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CItem * Create(MODEL model);

	int GetModel(void);
	void SetModel(int nModelNldx);

	static void SetModelData(int nNum, ModelData modelData);
	static ModelData GetModelData(int nNum);

	void InitSet(MODEL model);

	void Execution(void);

	void AvailableDisplay(void);

	bool GetBuyUse(void);

	CObj2dItemInfo *GetItemInfo(void);
	
	static CDataInt m_nDataModelNldx[MODEL_MAX];	// モデルの番号

	CDataD3DXVECTOR3 m_dataRotAdd;	// 回転量

	CDataBool m_bDataUse;			// 使用の有無
	CDataInt m_nBuyCount;			// 購入回数

	CDataInt m_nDataEffectCount;	// エフェクトのカウント

private:

	MODEL m_model;								// 自分自身のモデル
	static ModelData m_modelData[MODEL_MAX];	// モデルの情報
	CObj2dItemInfo *m_pItemInfo;				// アイテムの情報
};

#endif	// 二重インクルード防止の終了
