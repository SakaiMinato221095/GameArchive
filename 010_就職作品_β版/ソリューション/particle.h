
//-===============================================
//-
//-	パーティクル処理のヘッダー[particle.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _PARTICLE_H_		// このマクロが定義されなかったら
#define _PARTICLE_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

//-======================================
//-	クラス定義
//-======================================

void SetParticle(int nMaxEffect, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR color, int nEffectLife);
void SetRange(int nMaxEffect, D3DXVECTOR3 objSize, D3DXVECTOR3 objRot, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR color, int nEffectLife);

#endif	// 二重インクルード防止の終了
