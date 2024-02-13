
//-===============================================
//-
//-	���������̃w�b�_�[[explosion.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _EXPLOSION_H_		// ���̃}�N������`����Ȃ�������
#define _EXPLOSION_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object_anima.h"

#include "data.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�N���X��`
//-======================================

class CExplosion : public CObjectAnima
{

public:

	CExplosion();
	~CExplosion();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CExplosion *Create(void);

	bool Sub(void);

	void SetAnimaLife(void);

	CDataInt m_nDataLife;

private:

	static LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`��
};

#endif	// ��d�C���N���[�h�h�~�̏I��
