
//================================================
//=
//= �r���{�[�h�����̃w�b�^�[[billboard.h]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	��d�C���N���[�h�h�~
//=======================================

#ifndef _BILLBOARD_H_	// ���̃}�N������`����Ȃ�������
#define _BILLBOARD_H_	// ��d�C���N���[�h�X�q�̃}�N�����`

//=======================================
//=	�C���N���[�h
//=======================================

#include "object.h"

//=======================================
//=	�N���X��`
//=======================================

// �r���{�[�h�I�u�W�F�N�g�̃N���X
class CBillboard : public CObject
{
public:

	// ���
	typedef struct
	{
		D3DXVECTOR3 pos;	// �ʒu
		D3DXVECTOR3 size;	// �傫��
		D3DXCOLOR color;	// �F
	}Info;

	CBillboard(int nPriority = 3);
	~CBillboard();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBillboard *Create(void);

	void SetInit(D3DXVECTOR3 pos,D3DXVECTOR3 size, D3DXCOLOR color);

	virtual void SetVtx(void);

	void UpdateInfo(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
	{
		m_info.pos = pos;
		m_info.size = size;
		m_info.color = color;
		SetVtx();
	}

	void BindTexture(int nTextureNldx) { m_nTextureNldxUse = nTextureNldx; };

	void SetPos(D3DXVECTOR3 pos) { m_info.pos = pos; }
	D3DXVECTOR3 GetPos(void) { return m_info.pos; }

	void SetSize(D3DXVECTOR3 size) { m_info.size = size; }
	D3DXVECTOR3 GetSize(void) { return m_info.size; }

	void SetColor(D3DXCOLOR color) { m_info.color = color; }
	D3DXCOLOR GetColor(void) { return m_info.color; }

	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }

private:

	Info m_info;						// ���_�l���

	int m_nTextureNldxUse;				// �e�N�X�`���̔ԍ�

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�̃|�C���^
	
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
};

#endif 