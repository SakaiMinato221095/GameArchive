
//-===============================================
//-
//-	アニメーションオブジェクト処理のヘッダー[object2d_anima.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _OBJECT_ANIMA_H_		// このマクロが定義されなかったら
#define _OBJECT_ANIMA_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object2d.h"

//-======================================
//-	クラス定義
//-======================================

class CObjectAnima: public CObject2d
{

public:

	CObjectAnima();
	~CObjectAnima();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjectAnima *Create(void);

	void UpdateAnima(void);

	void SetVtx(void);

	void SetAllAnima(int nLine, int nColumn, int nChangeFrame);

	CDataInt m_nDataLine;			// アニメーションの行数
	CDataInt m_nDataColumn;			// アニメーションの列数

	CDataInt m_nDataChangeFrame;	// 切り替えるまでのフレーム数

	CDataInt m_nDataCounter;		// アニメーションカウンター
	CDataInt m_nDataPattern;		// アニメーションパターンNo.

private:
	
};

#endif	// 二重インクルード防止の終了

