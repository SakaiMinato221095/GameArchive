
//-===============================================
//-
//-	�p�[�e�B�N�������̃w�b�_�[[particle.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _PARTICLE_H_		// ���̃}�N������`����Ȃ�������
#define _PARTICLE_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

//-======================================
//-	�N���X��`
//-======================================

void SetParticle(int nMaxEffect, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR color, int nEffectLife);
void SetRange(int nMaxEffect, D3DXVECTOR3 objSize, D3DXVECTOR3 objRot, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR color, int nEffectLife);

#endif	// ��d�C���N���[�h�h�~�̏I��
