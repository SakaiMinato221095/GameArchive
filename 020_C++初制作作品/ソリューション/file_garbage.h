
//-===============================================
//-
//-	ゴミファイル処理のヘッダー[file_grabage.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _FILE_GRABAGE_H_		// このマクロが定義されなかったら
#define _FILE_GRABAGE_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "garbage.h"

//-======================================
//-	マクロ定義
//-======================================

#define FILE_DATA_MAX	(256)	// 使用データの最大数

//-======================================
//-	クラス定義
//-======================================

class CFileGarbage
{

public:

	typedef struct
	{
		int modelNldx;
		bool bNoLoad;

		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
	}FileData;

	typedef enum
	{
		TXT_NORMAL_000 = 0,	// 通常効果なしオブジェクト_000のテキスト
	}TXT;

	CFileGarbage();
	~CFileGarbage();

	static void Save(CFileGarbage::TXT txtType);
	static void Load(CFileGarbage::TXT txtType);

	static void Locate(void);
	static void ObjCheck(void);
	static void ObjRecall(void);

private:

	static int m_nSetMax;
	static FileData m_aFileData[FILE_DATA_MAX];
};

#endif	// 二重インクルード防止の終了
