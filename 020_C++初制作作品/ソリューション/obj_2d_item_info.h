
//-===============================================
//-
//-	2D�̃A�C�e�����̕\���̃w�b�_�[[obj_2d_item_info.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _2D_ITEM_INFO_H_		// ���̃}�N������`����Ȃ�������
#define _2D_ITEM_INFO_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "main.h"

#include "object2d.h"

#include "item.h"

#include "data.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�N���X��`
//-======================================

class CObj2dItemInfo : public CObject2d
{

public:

	CObj2dItemInfo(int nPriority = 3);
	~CObj2dItemInfo();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(CItem::MODEL nModel);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObj2dItemInfo * Create(CItem::MODEL nModel);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	CDataBool m_bDataDraw;

private:

	void InitSet(void);

	static int m_nTextureNldx[CItem::MODEL_MAX];		// �e�N�X�`���ԍ�
};

#endif	// ��d�C���N���[�h�h�~�̏I��
