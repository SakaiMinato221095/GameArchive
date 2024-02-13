
//-===============================================
//-
//-	酒井の便利関数の処理のヘッダー[helper_sakai.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _HELPER_SAKAI_H_		// このマクロが定義されなかったら
#define _HELPER_SAKAI_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

//=======================================
//=	マクロ定義
//=======================================

//-======================================
//-	クラス定義
//-======================================

namespace HelperSakai
{
	void NormalizeAngle(D3DXVECTOR3* rot, D3DXVECTOR3* rotDest, float destSpeed);
	bool IfRangeFloat(float fData, float fMin, float fMax);
	float CalculateLength(D3DXVECTOR3 pos, D3DXVECTOR3 posTgt);

	int AddLimitStop(int nData, int nAdd, int nMin, int nMax);
	int AddLimitReturn(int nData, int nAdd, int nMin, int nMax);
}

#endif	// 二重インクルード防止の終了
