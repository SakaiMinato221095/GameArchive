
//-===============================================
//-
//-	効果なしのXファイルオブジェクト処理のヘッダー[objectx_none.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _OBJECT_X_NONE_H_		// このマクロが定義されなかったら
#define _OBJECT_X_NONE_H_		// 二重インクルード帽子のマクロを定義

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

// アイテムのクラス
class CObjectXNone : public CObjectX
{

public:

	// モデルの列挙型
	typedef enum
	{
		MODEL_OBARAFOOD,			// 商店街（食堂）
		MODEL_OBAMART,				// 商店街（半額店）
		MODEL_OBASTATION,			// 商店街（ゲームセンター）
		MODEL_OBARAKURABU,			// 商店街（雑貨）
		MODEL_OBARAMEAT,			// 商店街（精肉店）
		MODEL_OBARAVEGETABLE,		// 商店街（青果店）
		MODEL_OBARAFLOUR,			// 商店街（花屋）
		MODEL_OBARAFUKUYA,			// 商店街（服屋）

		MODEL_SANDBOX,				// 公園（砂場）
		MODEL_TOILET,				// 公園（トイレ）
		MODEL_WATER,				// 公園（水道）
		MODEL_BIN,					// 公園（ゴミ箱）
		MODEL_BENCH,				// 公園（ベンチ）
		MODEL_STREETLIGHT,			// 公園（街灯）
		MODEL_HORIZONTALBAR,		// 公園（鉄棒）
		MODEL_SLIDE,				// 公園（滑り台）

		MODEL_HOUSE001,				// 家（1）
		MODEL_HOUSE002,				// 家（2）
		MODEL_HOUSE003,				// 家（3）

		MODEL_STREET_STALL_DARK,	// 闇露店
		MODEL_HOUSE_BLOOD,			// 血付きの家

		MODEL_ZINJA,				// 神社
		MODEL_OMIKUJI,				// おみくじ

		MODEL_YAKISOBA,				// やきそば
		MODEL_KAKIGOORI,			// かき氷
		MDOEL_WANAGE,				// 輪投げ
		MODEL_TAKOYAKI,				// たこやき
		MODEL_YO_YO_TURI,			// ヨーヨー釣り

		MODEL_TREE,					// 木
		MODEL_TORII,				// 鳥居

		MODEL_NINJA_MANSION000,		// 屋敷
		MODEL_SCARECROW000,			// かかし
		MODEL_SISIODOSI,			// ししおどし
		MODEL_SAKURA000,			// 桜

		MODEL_PLANT,				// 工場

		MODEL_MAX
	}MODEL;

	// モデル情報
	typedef struct
	{
		D3DXVECTOR3 size;	// 大きさ
	}ModelData;

	CObjectXNone(int nPriority = 3);
	~CObjectXNone();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjectXNone * Create(MODEL model);

	int GetModel(void);
	void SetModel(int nModelNldx);

	static void SetModelData(int nNum, ModelData modelData);
	static ModelData GetModelData(int nNum);

	static CDataInt m_nDataModelNldx[MODEL_MAX];	// モデルの番号

private:

	void InitSet(MODEL model);

	MODEL m_model;	// 自身のモデル
	static ModelData m_modelData[MODEL_MAX];	// モデルの情報
};

#endif	// 二重インクルード防止の終了
