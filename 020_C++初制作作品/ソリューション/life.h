
//-===============================================
//-
//-	�̗͂̏����̃w�b�_�[[life.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _LIFE_H_		// ���̃}�N������`����Ȃ�������
#define _LIFE_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "data.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�O���錾
//-======================================

class CObj2dNone;
class CObj2dGage;

//-======================================
//-	�N���X��`
//-======================================

class CLife
{
public:

	CLife();
	~CLife();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CLife *Create(void);

	void InitSet(void);

	CDataD3DXVECTOR3 m_dataPos;			// �ʒu
	CDataD3DXVECTOR3 m_dataSize;		// �傫��

	CDataInt m_nDataLife;				// �̗͂̒l

private:

	CObj2dNone *m_pObj2dNone;	// �ʏ�2D�I�u�W�F�N�g�̃|�C���^
	CObj2dGage *m_pObj2dGage;	// �Q�[�W�̃|�C���^

};

#endif	// ��d�C���N���[�h�h�~�̏I��
