
//-===============================================
//-
//-	通常敵の処理のヘッダー[enemy_normal.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _ENEMY_NORMAL_H_		// このマクロが定義されなかったら
#define _ENEMY_NORMAL_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "enemy.h"

#include "data.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	クラス定義
//-======================================

// 通常敵のクラス
class CEnemyNormal : public CEnemy
{

public:

	CEnemyNormal();
	~CEnemyNormal();

	HRESULT Init(MODEL model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEnemyNormal *Create(MODEL model);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nLife);

private:

};

//-======================================
//- プロトタイプ宣言
//-======================================

#endif	// 二重インクルード防止の終了
