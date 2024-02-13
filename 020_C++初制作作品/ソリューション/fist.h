
//-===============================================
//-
//-	拳の処理のヘッダー[fist.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _FIST_H_		// このマクロが定義されなかったら
#define _FIST_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object_x.h"

#include "data.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	クラス定義
//-======================================

class CFist : public CObjectX
{

public:

	// 拳のモデル列挙型
	typedef enum
	{
		MODEL_FIST_000 = 0,
		MODEL_MAX
	}MODEL;

	CFist(int nPriority = 3);
	~CFist();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL tex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CFist * Create(MODEL tex);

	int GetModel(void);
	void SetModel(int nModelNldx);

	CDataInt m_nDataLife;
	CDataInt m_nDataDamage;

private:

	void Move(void);

	void Add(void);
	bool Sub(void);

	bool CollisionEnemy(void);
	bool CollisionObject(void);

	static int m_nTextureNldx[MODEL_MAX];		// テクスチャの番号

};

#endif	// 二重インクルード防止の終了
