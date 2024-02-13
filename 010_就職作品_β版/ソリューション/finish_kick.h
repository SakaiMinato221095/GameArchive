
//-===============================================
//-
//-	�L�b�N�̃t�B�j�b�V���U�������̃w�b�_�[[finish_kick.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _FINISH_KICK_H_		// ���̃}�N������`����Ȃ�������
#define _FINISH_KICK_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "attack.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//=	�O���錾
//=======================================

class CColl;

//-======================================
//-	�N���X��`
//-======================================

class CFinishKick : public CAttack
{

public:

	CFinishKick();
	~CFinishKick();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nDamage, CMgrColl::TAG tagTgt);

	static CFinishKick* Create(void);

private:

};

#endif	// ��d�C���N���[�h�h�~�̏I��
