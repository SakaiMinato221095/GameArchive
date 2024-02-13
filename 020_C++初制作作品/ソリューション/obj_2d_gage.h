
//-===============================================
//-
//-	ゲージ処理のヘッダー[obj_2d_gage.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _OBJ_2D_GAGE_H_		// このマクロが定義されなかったら
#define _OBJ_2D_GAGE_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object2d.h"

#include "data.h"

//-======================================
//-	クラス定義
//-======================================

class CObj2dGage : public CObject2d
{

public:

	// 文字のテクスチャ列挙型
	typedef enum
	{
		TEX_NULL = 0,		// なし
		TEX_MAX
	}TEX;

	// ゲージの種類
	typedef enum
	{
		TYPE_LEFT = 0,
		TYPE_RIGHT,
		TYPE_CENTER,
		TYPE_MAX
	}TYPE;

	CObj2dGage(int nPriority = 3);
	~CObj2dGage();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(TEX tex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObj2dGage *Create(TEX tex);

	void SetVtx(void);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color , TYPE type);

	CDataD3DXVECTOR3 m_dataGage;

private:

	static int m_nTextureNldx[TEX_MAX];		// テクスチャ番号
	TYPE m_type;							// 種類
};

#endif	// 二重インクルード防止の終了
