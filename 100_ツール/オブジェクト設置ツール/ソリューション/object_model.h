
//=======================
//=
//= 階層構造のXファイルオブジェクト処理のヘッター[object_model.h]
//= Author Sakai Minato
//=
//=======================

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

#define MODEL_PARTS_MAX	(16)	// モデルパーツの最大数
#define MODEL_NUM_MAX	(8)		// モデルの最大数

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
		MODEL_TYPE_MURABITO = 0,	// 村人
		MODEL_TYPE_CLOUD,			// クラウド
		MODEL_TYPE_SAMPLE,			// ランニングマン
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

	HRESULT Init(MODEL_TYPE modelType, int nCount);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjectModel * Create(MODEL_TYPE modelType, int nCount);

	void SetParent(CObjectModel ** pObjectModel, MODEL_TYPE modelType, int nCount);

	D3DXMATRIX GetMtxWorld(void);

	static void SetFile(MODEL_TYPE modelType);
	static int GetPartsNum(MODEL_TYPE modelType);

	CDataD3DXVECTOR3 m_dataPos;
	CDataD3DXVECTOR3 m_dataMotionPos;

	CDataD3DXVECTOR3 m_dataRot;
	CDataD3DXVECTOR3 m_dataMotionRot;

private:

	int *m_nldxTexture;						// テクスチャの番号

	LPDIRECT3DTEXTURE9 *m_pTexture;			// テクスチャのポインタ（動的確保）
	LPD3DXMESH m_pMesh;						// メッシュの情報のポインタ
	LPD3DXBUFFER m_pBuffMat;				// マテリアルのポインタ
	DWORD m_dwNumMat;						// マテリアルの数

	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス

	CObjectModel *m_pParent;				// 親モデルのポインタ

	static Model m_model[MODEL_NUM_MAX];	// モデルの情報
};

#endif	// 二重インクルード防止の終了