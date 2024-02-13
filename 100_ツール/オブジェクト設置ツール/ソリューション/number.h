
//-===============================================
//-
//-	数字処理のヘッダー[object.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _NUMBER_H_		// このマクロが定義されなかったら
#define _NUMBER_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object2d.h"

#include "data.h"

//-======================================
//-	クラス定義
//-======================================

class CNumber : public CObject2d
{

public:

	// 文字のテクスチャ列挙型
	typedef enum
	{
		TEX_GOLD_000 = 0,		// 金色_000
		TEX_MAX
	}TEX;

	CNumber(int nPriority = 3);
	~CNumber();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(TEX tex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CNumber *Create(TEX tex);

	void SetVtx(void);

	CDataInt m_nDataDigits;

private:

	static int m_nTextureNldx[TEX_MAX];		// テクスチャ番号

};

#endif	// 二重インクルード防止の終了
