
//=======================
//=
//= Xファイルオブジェクト処理のヘッター[object_x.h]
//= Author Sakai Minato
//=
//=======================

//=======================================
//=	二重インクルード防止
//=======================================

#ifndef _OBJECT_X_H_	// このマクロが定義されなかったら
#define _OBJECT_X_H_	// 二重インクルード帽子のマクロを定義

//=======================================
//=	インクルード
//=======================================

#include "object.h"

#include "data.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	クラス定義
//=======================================

// Xファイルオブジェクトのクラス
class CObjectX : public CObject
{
public:

	CObjectX(int nPriority = 3);
	~CObjectX();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjectX *Create(void);

	void BindModel(int nModelNldx, int nModelNum);

	virtual void SetModel(int nModelNldx);

	void AddRot(D3DXVECTOR3 addRot);

	void SetDrawRemove(void);

	CDataD3DXVECTOR3 m_dataPos;
	CDataD3DXVECTOR3 m_dataPosOld;

	CDataD3DXVECTOR3 m_dataRot;
	CDataD3DXVECTOR3 m_dataRotDest;

	CDataD3DXVECTOR3 m_dataSize;

	CDataBool m_bDataEat;

private:

	bool m_bDraw;			// 描画の有無
	int m_nModelNldxUse;	// モデル番号
	
	D3DXMATRIX m_mtxWorld;	// ワールドマトリックス
};

#endif	// 二重インクルード防止の終了