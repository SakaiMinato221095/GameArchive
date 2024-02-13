
//-===============================================
//-
//-	アイテムファイル処理のヘッダー[file_item.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _FILE_ITEM_H_		// このマクロが定義されなかったら
#define _FILE_ITEM_H_		// 二重インクルード帽子のマクロを定義

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

class CFileItem
{

public:

	typedef enum
	{
		TXT_NORMAL_000 = 0,	// 通常のアイテムショップ_000のテキスト
	}TXT;

	CFileItem();
	~CFileItem();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CFileItem *Create(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);

	static void Save(CFileItem::TXT txtType);
	static void Load(CFileItem::TXT txtType);

private:

};

#endif	// 二重インクルード防止の終了
