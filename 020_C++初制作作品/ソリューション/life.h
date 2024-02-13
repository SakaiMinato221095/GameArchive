
//-===============================================
//-
//-	体力の処理のヘッダー[life.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _LIFE_H_		// このマクロが定義されなかったら
#define _LIFE_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "data.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	前方宣言
//-======================================

class CObj2dNone;
class CObj2dGage;

//-======================================
//-	クラス定義
//-======================================

class CLife
{
public:

	CLife();
	~CLife();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CLife *Create(void);

	void InitSet(void);

	CDataD3DXVECTOR3 m_dataPos;			// 位置
	CDataD3DXVECTOR3 m_dataSize;		// 大きさ

	CDataInt m_nDataLife;				// 体力の値

private:

	CObj2dNone *m_pObj2dNone;	// 通常2Dオブジェクトのポインタ
	CObj2dGage *m_pObj2dGage;	// ゲージのポインタ

};

#endif	// 二重インクルード防止の終了
