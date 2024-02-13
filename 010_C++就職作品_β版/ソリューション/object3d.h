
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

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//=	�N���X��`
//=======================================

class CObject3d : public CObject
{
public:

	typedef struct
	{
		D3DXVECTOR3 pos;	// �ʒu
		D3DXVECTOR3 rot;	// ����
		D3DXVECTOR3 size;	// �傫��
		D3DXCOLOR color;	// �F
		D3DXVECTOR2 texPos;	// �e�N�X�`���ʒu
	}VtxData;

	CObject3d(int nPriority = 3);
	~CObject3d();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR color, D3DXVECTOR2 texPos);

	static CObject3d *Create(void);

	virtual void SetVtx(void);

	void SetVtxTex(D3DXVECTOR2 texPos) { m_vtxData.texPos = texPos; }

	void BindTexture(int nTextureNldx) {m_nTextureNldxUse = nTextureNldx;}

	void SetVtxData(VtxData vtxData) { m_vtxData = vtxData; }
	VtxData GetVtxData(void) { return m_vtxData; }

	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }

private:

	VtxData m_vtxData;					// ���_�l���

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�̃|�C���^
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X

	int m_nTextureNldxUse;				// �e�N�X�`���̔ԍ�
};

#endif	// ��d�C���N���[�h�h�~�̏I��