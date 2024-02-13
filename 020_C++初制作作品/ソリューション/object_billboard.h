
//================================================
//=
//= �r���{�[�h�I�u�W�F�N�g�����̃w�b�^�[[object_billboard.h]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	��d�C���N���[�h�h�~
//=======================================

#ifndef _OBJECT_BILLBOARD_H_	// ���̃}�N������`����Ȃ�������
#define _OBJECT_BILLBOARD_H_	// ��d�C���N���[�h�X�q�̃}�N�����`

//=======================================
//=	�C���N���[�h
//=======================================

#include "object.h"

#include "data.h"

//=======================================
//=	�N���X��`
//=======================================

// �r���{�[�h�I�u�W�F�N�g�̃N���X
class CObjectBillboard : public CObject
{
public:
	CObjectBillboard(int nPriority = 3);
	~CObjectBillboard();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjectBillboard *Create(void);

	void BindTexture(int nTextureNldx);

	void SetVtx(void);

	CDataD3DXVECTOR3 m_dataPos;		// �ʒu
	CDataD3DXVECTOR3 m_dataSize;	// �傫��
	CDataD3DXVECTOR3 m_dataMove;	// �ړ���
	CDataD3DXCOLOR m_dataColor;		// �F���

private:

	int m_nTextureNldxUse;				// �e�N�X�`���̔ԍ�

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�̃|�C���^
	
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
};

#endif 