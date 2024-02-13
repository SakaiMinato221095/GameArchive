
//-===============================================
//-
//-	操作説明UIの処理のヘッダー[ui_opr_desc.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _UI_OPR_DESC_H_		// このマクロが定義されなかったら
#define _UI_OPR_DESC_H_		// 二重インクルード帽子のマクロを定義

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

class CUiOprDesc : public CObject2d
{

public:

	// 操作説明UIのテクスチャ列挙型
	typedef enum
	{
		TEX_SPACE = 0,
		TEX_MAX
	}TEX;

	CUiOprDesc(int nPriority = 0);
	~CUiOprDesc();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(TEX tex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CUiOprDesc * Create(TEX tex);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 sizeMoveMax, D3DXVECTOR3 sizeMoveSpeed);

	void SetVtx(void);

	void AddSizeMove(void);
	void SubSizeMove(void);

	CDataD3DXVECTOR3 m_dataSizeMoveMax;		// 大きさの移動量の最大値
	CDataD3DXVECTOR3 m_dataSizeMoveAcu;		// 大きさの移動量の蓄積地
	CDataD3DXVECTOR3 m_dataSizeMoveSpeed;	// 大きさの移動量の速度
	CDataBool m_bDataSizeMove;				// 大きさの移動量の変化方向


private:

	static int m_nTextureNldx[TEX_MAX];		// テクスチャ番号
};

#endif	// 二重インクルード防止の終了
