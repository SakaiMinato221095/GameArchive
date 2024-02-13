
//-===============================================
//-
//-	�G�t�F�N�g�̏����̃w�b�_�[[effect_object.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _EFFECT_OBJECT_H_		// ���̃}�N������`����Ȃ�������
#define _EFFECT_OBJECT_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object_x.h"

#include "data.h"

//-======================================
//-	�N���X��`
//-======================================

class CEffectObject : public CObjectX
{

public:

	// �G�t�F�N�g�I�u�W�F�N�g�̃��f��
	typedef enum
	{
		MODEL_COIN_000 = 0,	// �R�C��
		MODEL_BIN_000,		// �r
		MODEL_MAX
	}MODEL;

	CEffectObject(int nPriority = 3);
	~CEffectObject();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEffectObject *Create(MODEL model);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXVECTOR3 moveMax);

	void Add(void);
	bool Sub(void);

	CDataD3DXVECTOR3 m_dataSizeHold;	// �T�C�Y��ێ�

	CDataD3DXVECTOR3 m_dataMove;		// �ړ���

	CDataD3DXVECTOR3 m_dataMoveAcu;		// �ړ��ʂ̒~�ϒl
	CDataD3DXVECTOR3 m_dataMoveMax;		// �ړ��ʂ̍ő�l

	CDataD3DXVECTOR3 m_dataAddRot;		// ��]��

	CDataInt m_nDataLife;				// �̗�

	CDataBool m_bDataZTestOff;			// Z�e�X�g�̗L��

private:

	static int m_nModelNldx[MODEL_MAX];	// ���f���̔ԍ�

};

//-======================================
//- �v���g�^�C�v�錾
//-======================================

#endif	// ��d�C���N���[�h�h�~�̏I��
