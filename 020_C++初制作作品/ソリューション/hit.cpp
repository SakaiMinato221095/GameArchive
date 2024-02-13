
//-===============================================
//-
//-	接触の処理[hit.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "hit.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	コンスト定義
//=======================================

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	接触のコンストラクタ
//-------------------------------------
CHit::CHit()
{

}

//-------------------------------------
//-	接触のデストラクタ
//-------------------------------------
CHit::~CHit()
{

}


//-------------------------------------
//- 接触の矩形の当たり判定
//-------------------------------------
bool CHit::hitRectangle(D3DXVECTOR3 posMy, D3DXVECTOR3 sizeMy, D3DXVECTOR3 posPair, D3DXVECTOR3 sizePair)
{
	if (posMy.x + sizeMy.x >= posPair.x - sizePair.x &&
		posMy.x - sizeMy.x <= posPair.x + sizePair.x &&
		posMy.z + sizeMy.z >= posPair.z - sizePair.z &&
		posMy.z - sizeMy.z <= posPair.z + sizePair.z)
	{
		return true;
	}

	return false;
}

//-------------------------------------
//- 接触の回転矩形の当たり判定
//-------------------------------------
bool CHit::hitRectangleRot(D3DXVECTOR3 posMy, D3DXVECTOR3 sizeMy, D3DXVECTOR3 rot, D3DXVECTOR3 posPair, D3DXVECTOR3 sizePair,D3DXVECTOR3 rotPair)
{
	if (rot.y >= 0.0f &&
		rot.y >= (D3DX_PI * 0.25f) &&
		rot.y <= (D3DX_PI * 0.75f))
	{
		float tenpSizeX = sizeMy.x;
		sizeMy.x = sizeMy.z;
		sizeMy.z = tenpSizeX;
	}
	else if (
		rot.y <= 0.0f &&
		rot.y <= (-D3DX_PI * 0.25f) &&
		rot.y >= (-D3DX_PI * 0.75f))
	{
		float tenpSizeX = sizeMy.x;
		sizeMy.x = sizeMy.z;
		sizeMy.z = tenpSizeX;
	}

	if (posMy.x + sizeMy.x >= posPair.x - sizePair.x &&
		posMy.x - sizeMy.x <= posPair.x + sizePair.x &&
		posMy.z + sizeMy.z >= posPair.z - sizePair.z &&
		posMy.z - sizeMy.z <= posPair.z + sizePair.z)
	{
		return true;
	}

	return false;
}

//-------------------------------------
//- 接触の辺の当たり判定
//-------------------------------------
bool CHit::hitRectangleSide(float fPos, float fSize, float fPosPair, float fSizePair)
{
	if (fPos + fSize >= fPosPair - fSizePair &&
		fPos - fSize <= fPosPair + fSizePair)
	{
		return true;
	}

	return false;
}

