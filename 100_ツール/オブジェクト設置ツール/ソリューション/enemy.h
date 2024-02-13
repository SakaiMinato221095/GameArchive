
//-===============================================
//-
//-	敵の処理のヘッダー[enemy.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _ENEMY_H_		// このマクロが定義されなかったら
#define _ENEMY_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object_x.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	クラス定義
//-======================================

// 敵のクラス
class CEnemy : public CObjectX
{

public:

	// モデル
	typedef enum
	{
		MODEL_ALIEN_000 = 0,	// エイリアン_000
		MODEL_MAX
	}MODEL;

	// 種類
	typedef enum
	{
		TYPE_NORMAL = 0,		// 通常敵
		TYPE_MAX
	}TYPE;

	CEnemy();
	~CEnemy();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CDataD3DXVECTOR3 m_dataMove;	// 移動量
	CDataInt m_nDataLife;			// 体力

	int GetModel(void);
	void SetModel(int nModelNldx);

	static CDataInt m_nDataModelNldx[MODEL_MAX];	// モデルの番号

private:

	MODEL m_model;	// 自身のモデル

};

#endif	// 二重インクルード防止の終了
