
//-===============================================
//-
//-	テスト用のXファイルオブジェクト処理のヘッダー[objectx_test.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _OBJECT_X_TEST_H_		// このマクロが定義されなかったら
#define _OBJECT_X_TEST_H_		// 二重インクルード帽子のマクロを定義

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
class CObjectXTest : public CObjectX
{

public:

	// モデルの列挙型
	typedef enum
	{
		MODEL_HUMAN_BOX_000 = 0,		// 人型の基準モデル
		MODEL_MAX
	}MODEL;

	CObjectXTest();
	~CObjectXTest();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjectXTest * Create(MODEL model);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);

	int GetModel(void);
	void SetModel(int nModelNldx);

	static CDataInt m_nDataModelNldx[MODEL_MAX];	// モデルの番号

private:

	MODEL m_model;	// 自身のモデル
};

#endif	// 二重インクルード防止の終了
