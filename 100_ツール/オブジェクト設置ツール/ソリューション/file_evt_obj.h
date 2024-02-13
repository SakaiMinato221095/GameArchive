
//-===============================================
//-
//-	イベントオブジェクトファイル処理のヘッダー[file_evt_obj.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _FILE_EVT_OBJ_H_		// このマクロが定義されなかったら
#define _FILE_EVT_OBJ_H_		// 二重インクルード帽子のマクロを定義

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

class CFileEvtObj
{

public:

	typedef enum
	{
		TXT_NORMAL_000 = 0,	// 通常イベントオブジェクト_000のテキスト
	}TXT;

	CFileEvtObj();
	~CFileEvtObj();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CFileEvtObj *Create(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);

	static void Save(CFileEvtObj::TXT txtType);
	static void Load(CFileEvtObj::TXT txtType);

private:

};

#endif	// 二重インクルード防止の終了
