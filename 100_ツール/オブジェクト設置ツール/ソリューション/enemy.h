
//-===============================================
//-
//-	�G�̏����̃w�b�_�[[enemy.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _ENEMY_H_		// ���̃}�N������`����Ȃ�������
#define _ENEMY_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object_x.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�N���X��`
//-======================================

// �G�̃N���X
class CEnemy : public CObjectX
{

public:

	// ���f��
	typedef enum
	{
		MODEL_ALIEN_000 = 0,	// �G�C���A��_000
		MODEL_MAX
	}MODEL;

	// ���
	typedef enum
	{
		TYPE_NORMAL = 0,		// �ʏ�G
		TYPE_MAX
	}TYPE;

	CEnemy();
	~CEnemy();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CDataD3DXVECTOR3 m_dataMove;	// �ړ���
	CDataInt m_nDataLife;			// �̗�

	int GetModel(void);
	void SetModel(int nModelNldx);

	static CDataInt m_nDataModelNldx[MODEL_MAX];	// ���f���̔ԍ�

private:

	MODEL m_model;	// ���g�̃��f��

};

#endif	// ��d�C���N���[�h�h�~�̏I��
