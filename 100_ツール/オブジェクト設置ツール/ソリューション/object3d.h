
//================================================
//=
//= 3D�I�u�W�F�N�g�����̃w�b�^�[[object3d.h]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	��d�C���N���[�h�h�~
//=======================================

#ifndef _OBJECT_3D_H_	//���̃}�N������`����Ȃ�������
#define _OBJECT_3D_H_	//��d�C���N���[�h�X�q�̃}�N�����`

//=======================================
//=	�C���N���[�h
//=======================================

#include "object.h"

#include "data.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//=	�N���X��`
//=======================================

class CObject3d : public CObject
{
public:

	typedef enum
	{
		TYPE_BLOCK_001 = 0,		// �t�B�[���h
		TYPE_MAX
	}TYPE;

	CObject3d();
	~CObject3d();

	HRESULT Init(void);
	HRESULT Init(TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObject3d *Create(void);
	static CObject3d *Create(TYPE type);

	void BindTexture(int nTextureNldx);

	virtual void SetVtx(void);

	CDataD3DXVECTOR3 m_dataPos;		// �ʒu
	CDataD3DXVECTOR3 m_dataRot;		// ����
	CDataD3DXVECTOR3 m_dataSize;	// �傫��

private:

	int m_nTextureNldxUse;				// �e�N�X�`���̔ԍ�

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�̃|�C���^

	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
};

#endif	// ��d�C���N���[�h�h�~�̏I��