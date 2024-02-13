
//-===============================================
//-
//-	開始説明文UIの処理のヘッダー[ui_start_text.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _UI_START_TEXT_H_		// このマクロが定義されなかったら
#define _UI_START_TEXT_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "main.h"

#include "object2d.h"

#include "data.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	クラス定義
//-======================================

class CUiStartText : public CObject2d
{

public:

	// スタートテキストのテクスチャ列挙型
	typedef enum
	{
		TEX_START_000 = 0,	// スタートテキスト000
		TEX_START_001,		// スタートテキスト001
		TEX_MAX
	}TEX;

	CUiStartText(int nPriority = 0);
	~CUiStartText();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(TEX tex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CUiStartText * Create(TEX tex);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 sizeMoveMax, D3DXVECTOR3 sizeMoveSpeed);

	void AddSizeMove(void);
	void SubSizeMove(void);

	CDataD3DXVECTOR3 m_dataPosTarget;		// 目的の位置
	CDataD3DXVECTOR3 m_dataMoveSpeed;		// 移動量の速度
	CDataBool m_bDataMoveStop;				// 移動停止の有無

private:

	static int m_nTextureNldx[TEX_MAX];		// テクスチャ番号
};

#endif	// 二重インクルード防止の終了
