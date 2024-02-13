
//-===============================================
//-
//-	�G�l�~�[�s���̏����̃w�b�_�[[enemy_pin.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _ENEMY_PIN_H_		// ���̃}�N������`����Ȃ�������
#define _ENEMY_PIN_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object_x.h"

#include "data.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�N���X��`
//-======================================

// �G�̃N���X
class CEnemyPin : public CObjectX
{

public:

	// �C�x���g�I�u�W�F�N�g�̃��f��
	typedef enum
	{
		MODEL_ENEMY_PIN = 0,	// ���̋@
		MODEL_MAX
	}MODEL;

	CEnemyPin();
	~CEnemyPin();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEnemyPin * Create(MODEL model);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	int GetModel(void);
	void SetModel(int nModelNldx);

	static CDataInt m_nDataModelNldx[MODEL_MAX];	// ���f���̔ԍ�

private:

	MODEL m_model;							// �������g�̃��f��
};

//-======================================
//- �v���g�^�C�v�錾
//-======================================

#endif	// ��d�C���N���[�h�h�~�̏I��
#pragma once
