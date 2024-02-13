
//-===============================================
//-
//-	システムオブジェクト管理処理のヘッダー[mgr_sys_obj.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _MGR_SYS_OBJ_H_		// このマクロが定義されなかったら
#define _MGR_SYS_OBJ_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

//-======================================
//-	前方宣言
//-======================================

class CTimer;

class CScore;

//-======================================
//-	クラス定義
//-======================================

class CMgrSysObj
{

public:

	CMgrSysObj();
	~CMgrSysObj();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetNumber(void);
	void NullAllNumber(void);

	static CTimer *GetTimer(void);
	static CScore *GetScore(void);

private:

	static CTimer *m_pTimer;	// 時間のポインタ
	static CScore *m_pScore;	// スコアのポインタ

};

#endif	// 二重インクルード防止の終了