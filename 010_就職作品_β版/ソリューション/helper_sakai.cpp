
//================================================
//=
//=	酒井の便利関数処理[helper_sakai.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "helper_sakai.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//=	静的変数宣言
//=======================================

//-------------------------------------
//-	角度の正規化
//-------------------------------------
void HelperSakai::NormalizeAngle(D3DXVECTOR3* rot, D3DXVECTOR3* rotDest, float destSpeed)
{
	// 目的の向きの補正
	if (rotDest->y > D3DX_PI)
	{
		rotDest->y += -D3DX_PI * 2;
	}
	else if (rotDest->y < -D3DX_PI)
	{
		rotDest->y += D3DX_PI * 2;
	}

	// 差分の向きを算出
	float rotDiff = rotDest->y - rot->y;

	// 差分の向きを補正
	if (rotDiff > D3DX_PI)
	{
		rotDiff += -D3DX_PI * 2;
	}
	else if (rotDiff < -D3DX_PI)
	{
		rotDiff += D3DX_PI * 2;
	}

	// 角度の移動
	rot->y += rotDiff * destSpeed;

	// 向きの補正
	if (rot->y > D3DX_PI)
	{
		rot->y += -D3DX_PI * 2;
	}
	else if (rot->y < -D3DX_PI)
	{
		rot->y += D3DX_PI * 2;
	}

}

//-------------------------------------
//-	範囲指定のIF文（浮動小数）
//-------------------------------------
bool HelperSakai::IfRangeFloat(float fData,float fMin, float fMax)
{
	if (fData > fMin &&
		fData < fMax)
	{
		return true;
	}

	return false;
}

//-------------------------------------
//-	対象との距離を算出
//-------------------------------------
float HelperSakai::CalculateLength(D3DXVECTOR3 pos, D3DXVECTOR3 posTgt)
{
	// ターゲットとの距離を判定
	float fLengthTgtSquared = ((posTgt.x - pos.x) * (posTgt.x - pos.x) +
							   (posTgt.y - pos.y) * (posTgt.y - pos.y) +
							   (posTgt.z - pos.z) * (posTgt.z - pos.z));

	// 距離を返す
	return std::sqrt(fLengthTgtSquared);
}

//-------------------------------------
//-	最大値指定の加算処理（最大値時に停止）
//-------------------------------------
int HelperSakai::AddLimitStop(int nData, int nAdd, int nMin,int nMax)
{
	// 算出
	int nDataCal = nData + nAdd;

	// 最大値・最小値の判定
	if (nDataCal > nMax)
	{
		nDataCal = nMax;
	}
	else if(nDataCal < nMin)
	{
		nDataCal = nMin;
	}

	return nDataCal;
}

//-------------------------------------
//-	最大値指定の加算処理（最大値時に反転）
//-------------------------------------
int HelperSakai::AddLimitReturn(int nData, int nAdd, int nMin, int nMax)
{
	// 算出
	int nDataCal = nData + nAdd;

	// 最大値・最小値の判定
	if (nDataCal > nMax)
	{
		nDataCal = nDataCal - nMax;
	}
	else if (nDataCal < nMin)
	{
		nDataCal = nDataCal + nMin;
	}

	return nDataCal;
}

