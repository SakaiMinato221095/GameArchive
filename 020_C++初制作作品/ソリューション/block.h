
//-===============================================
//-
//-	�u���b�N�̏����̃w�b�_�[[block.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _BLOCK_H_		// ���̃}�N������`����Ȃ�������
#define _BLOCK_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object2d.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�N���X��`
//-======================================

class CBlock : public CObject2d
{

public:

	CBlock(int nPriority = 3);
	~CBlock();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBlock *Create(void);

private:

	static LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`��

};

#endif	// ��d�C���N���[�h�h�~�̏I��
