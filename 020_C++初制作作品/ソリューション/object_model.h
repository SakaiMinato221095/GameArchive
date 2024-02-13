
//-===============================================
//=
//= 階層構造のXファイルオブジェクト処理のヘッター[object_model.h]
//= Author Sakai Minato
//=
//-===============================================

//=======================================
//=	二重インクルード防止
//=======================================

#ifndef _OBJECT_MODEL_H_	// このマクロが定義されなかったら
#define _OBJECT_MODEL_H_	// 二重インクルード帽子のマクロを定義

//=======================================
//=	インクルード
//=======================================

#include "data.h"

//-======================================
//-	マクロ定義
//-======================================

#define MODEL_PARTS_MAX	(32)	// モデルパーツの最大数
#define MODEL_NUM_MAX	(32)	// モデルの最大数

//=======================================
//=	クラス定義
//=======================================

// 階層構造のXファイルオブジェクトのクラス
class CObjectModel
{
public:
	
	// モデルの種類
	typedef enum
	{
		MODEL_TYPE_PLAYER_SEARCH = 0,	// 探索プレイヤー
		MODEL_TYPE_PLAYER_BATTLE,		// 戦闘プレイヤー
		MODEL_TYPE_SAMPLE,				// ランニングマン
		MODEL_TYPE_MAX
	}MODEL_TYPE;

	// モデルパーツの情報
	typedef struct
	{
		int nIndex;				// パーツの番号
		int nParent;			// 親の番号
		char aFileName[256];	// ファイルの名前

		D3DXVECTOR3 pos;		// 位置情報
		D3DXVECTOR3 rot;		// 向き情報

	}ModelParts;

	// モデルの情報
	typedef struct
	{
		ModelParts modelParts[MODEL_PARTS_MAX];		// モデルパーツの情報
		int nPartsNum;								// パーツ数
	}Model;

	CObjectModel();
	~CObjectModel();

	static HRESULT Load(void);

	HRESULT Init(MODEL_TYPE modelType, int nCount);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjectModel * Create(MODEL_TYPE modelType, int nCount);

	void SetParent(CObjectModel ** pObjectModel, MODEL_TYPE modelType, int nCount);

	D3DXMATRIX GetMtxWorld(void);

	static void SetFile(MODEL_TYPE modelType);
	static int GetPartsNum(MODEL_TYPE modelType);

	static CDataInt m_nDataModelNldx[MODEL_TYPE_MAX][MODEL_PARTS_MAX];	// モデルの番号

	CDataD3DXVECTOR3 m_dataPos;
	CDataD3DXVECTOR3 m_dataMotionPos;

	CDataD3DXVECTOR3 m_dataRot;
	CDataD3DXVECTOR3 m_dataMotionRot;

private:

	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス

	CObjectModel *m_pParent;				// 親モデルのポインタ

	MODEL_TYPE m_modelType;					// 自分のモデルの種類
	int m_nPartsNum;						// 自分のパーツ番号

	static Model m_model[MODEL_NUM_MAX];	// モデルの情報
};

#endif	// 二重インクルード防止の終了