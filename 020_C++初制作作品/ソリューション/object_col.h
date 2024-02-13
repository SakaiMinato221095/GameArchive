
//-===============================================
//=
//= �����蔻��I�u�W�F�N�g�����̃w�b�^�[[object_col.h]
//= Author Sakai Minato
//=
//-===============================================

//=======================================
//=	��d�C���N���[�h�h�~
//=======================================

#ifndef _OBJECT_COL_H_	// ���̃}�N������`����Ȃ�������
#define _OBJECT_COL_H_	// ��d�C���N���[�h�X�q�̃}�N�����`

//=======================================
//=	�C���N���[�h
//=======================================

#include "obj_3d_field.h"
#include "obj_3d_wall.h"

#include "data.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�O���錾
//-======================================

class CObj3dField;
class CObj3dWall;

//=======================================
//=	�N���X��`
//=======================================

// X�t�@�C���I�u�W�F�N�g�̃N���X
class CObjectCol
{
public:

	typedef enum
	{
		TYPE_WALL_LEFT = 0,	// ��
		TYPE_WALL_RIGHT,	// �E
		TYPE_WALL_NEAR,		// ��O
		TYPE_WALL_BACK,		// ��
		TYPE_WALL_MAX
	}TYPE_WALL;

	typedef enum
	{
		TYPE_FIELD_BOTTOM = 0,	// ��
		TYPE_FIELD_TOP,			// ��
		TYPE_FIELD_MAX
	}TYPE_FIELD;

	CObjectCol();
	~CObjectCol();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjectCol *Create(void);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);

	void SetObjectCol(void);

	bool Collision(D3DXVECTOR3 posGet, D3DXVECTOR3 sizeGet);

	CDataD3DXVECTOR3 m_dataPos;		// �ʒu���
	CDataD3DXVECTOR3 m_dataSize;	// �T�C�Y
	CDataD3DXVECTOR3 m_dataRot;		// ����
	CDataD3DXCOLOR m_dataColor;		// �F

private:

	CObj3dWall *m_apObj3dWall[TYPE_WALL_MAX];		// �ǂ̃|�C���^
	CObj3dField *m_apObj3dField[TYPE_FIELD_MAX];	// �n�ʂ̃|�C���^
};

#endif	// ��d�C���N���[�h�h�~�̏I��