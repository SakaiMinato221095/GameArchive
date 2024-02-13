
//-===============================================
//-
//-	2D�I�u�W�F�N�g�����̃w�b�_�[[object2d.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _OBJECT_2D_H_		// ���̃}�N������`����Ȃ�������
#define _OBJECT_2D_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object.h"

#include "data.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�N���X��`
//-======================================

class CObject2d : public CObject
{

public:

	CObject2d(int nPriority = 3);
	~CObject2d();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void BindTexture(int nTextureNldx);

	static CObject2d *CObject2d::Create(int nPriority = 3);

	virtual void SetVtx(void);

	CDataD3DXVECTOR3 m_dataPos;		// �ʒu
	CDataD3DXVECTOR3 m_dataPosOld;	// �O��̈ʒu
	CDataD3DXVECTOR3 m_dataSize;	// �傫��
	CDataD3DXCOLOR m_dataColor;		// �F

	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void);

	CObject2d *GetObject2d(void);

private:

	int m_nTextureNldxUse;						// �e�N�X�`���̔ԍ�

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@���i�[
};

//-======================================
//- �v���g�^�C�v�錾
//-======================================

#endif	// ��d�C���N���[�h�h�~�̏I��
