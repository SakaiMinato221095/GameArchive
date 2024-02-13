
//-===============================================
//-
//-	パーティクル処理[particle.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "particle.h"

#include "renderer.h"
#include "manager.h"

#include "effect.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CParticle::CParticle()
{

}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CParticle::~CParticle()
{

}

//-------------------------------------
//- パーティクルからのエフェクト設定
//-------------------------------------
void CParticle::SetParticle(int nMaxEffect, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR color, int nEffectLife)
{
	for (int nCount = 0; nCount < nMaxEffect; nCount++)
	{
		// エフェクトのポインタ宣言
		CEffect *pEffect = CEffect::Create(CEffect::TEX_NORMAL_000);

		// エフェクト生成の有無を判定
		if (pEffect != NULL)
		{
			// 変数宣言（XとZのランダム情報）
			float fRotData = (float)(rand() % 629 - 314) / 100.0f;		// 向き
			float fRotMove = (float)(rand() % int(move.x)) / 10.0f;		// 移動量

			// 変数宣言（Yのランダム情報）
			float fRotData2 = (float)(rand() % 629 + 314) / 100.0f;		// 向き
			float fRotMove2 = (float)(rand() % int(move.y)) / 10.0f;	// 移動量

			// エフェクトの位置を設定
			pEffect->m_dataPos.Set(D3DXVECTOR3(pos.x, pos.y + 30.0f, pos.z));

			// エフェクトのサイズを設定
			pEffect->m_dataSize.Set(size);

			// エフェクトの移動量を設定
			pEffect->m_dataMove.Set(D3DXVECTOR3((sinf(fRotData) * fRotMove), (cosf(fRotData2) * fRotMove2), (cosf(fRotData) * fRotMove)));

			// エフェクトの色を設定
			pEffect->m_dataColor.Set(color);

			// エフェクトの体力を設定
			pEffect->m_nDataLife.Set(nEffectLife);

			// エフェクトのZテストオフ設定
			pEffect->m_bDataZTestOff.Set(false);
		}
	}
}

//-------------------------------------
//- パーティクルからのエフェクト設定
//-------------------------------------
void CParticle::SetRange(int nMaxEffect, D3DXVECTOR3 objSize, D3DXVECTOR3 objRot,D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move,D3DXCOLOR color, int nEffectLife)
{
	if (objRot.y >= 0.0f &&
		objRot.y >= (D3DX_PI * 0.25f) &&
		objRot.y <= (D3DX_PI * 0.75f))
	{
		float tenpSizeX = objSize.x;
		objSize.x = objSize.z;
		objSize.z = tenpSizeX;
	}
	else if (
		objRot.y <= 0.0f &&
		objRot.y <= (-D3DX_PI * 0.25f) &&
		objRot.y >= (-D3DX_PI * 0.75f))
	{
		float tenpSizeX = objSize.x;
		objSize.x = objSize.z;
		objSize.z = tenpSizeX;
	}

	for (int nCount = 0; nCount < nMaxEffect; nCount++)
	{
		// エフェクトのポインタ宣言
		CEffect *pEffect = CEffect::Create(CEffect::TEX_NORMAL_000);

		// エフェクト生成の有無を判定
		if (pEffect != NULL)
		{
			// 変数宣言（サイズのランダム情報）
			float fSizeX = (float)(rand() % int(objSize.x * 2)) - objSize.x;	// サイズ（X）のランダム
			float fSizeZ = (float)(rand() % int(objSize.z * 2)) - objSize.z;	// サイズ（Z）のランダム

			pEffect->Set(
				D3DXVECTOR3(pos.x + fSizeX, pos.y, pos.z + fSizeZ),
				size,
				move,
				color,
				nEffectLife,
				false);
		}
	}

}