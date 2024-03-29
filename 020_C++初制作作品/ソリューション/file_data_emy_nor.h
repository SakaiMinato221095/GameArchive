
//-===============================================
//-
//-	通常敵の情報ファイル処理のヘッダー[file_data_emy_nor.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _FILE_DATA_EMY_NOR_H_		// このマクロが定義されなかったら
#define _FILE_DATA_EMY_NOR_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	前方宣言
//-======================================

//-======================================
//-	クラス定義
//-======================================

class CFileDataEmyNor
{

public:

	CFileDataEmyNor();
	~CFileDataEmyNor();

	static void Save(int nNumber, D3DXVECTOR3 sizeCol);
	static void Load(void);

private:
	
};

#endif	// 二重インクルード防止の終了
