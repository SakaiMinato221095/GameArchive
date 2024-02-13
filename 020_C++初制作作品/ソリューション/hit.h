
//-===============================================
//-
//-	接触の処理のヘッダー[hit.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _HIT_H_		// このマクロが定義されなかったら
#define _HIT_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	クラス定義
//-======================================

// 接触のクラス
class CHit
{

public:

	CHit();
	~CHit();

	static bool hitRectangle(D3DXVECTOR3 posMy, D3DXVECTOR3 sizeMy,D3DXVECTOR3 posPair, D3DXVECTOR3 sizePair);
	static bool hitRectangleRot(D3DXVECTOR3 posMy, D3DXVECTOR3 sizeMy, D3DXVECTOR3 rot, D3DXVECTOR3 posPair, D3DXVECTOR3 sizePair, D3DXVECTOR3 rotPair);
	static bool hitRectangleSide(float fPos, float fSize, float fPosPair, float fSizePair);

private:

};

#endif	// 二重インクルード防止の終了
