
//-===============================================
//-
//-	�Q�[�g�̏����̃w�b�_�[[gate.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _GATE_H_		// ���̃}�N������`����Ȃ�������
#define _GATE_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object_x.h"

#include "data.h"

#include "score.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�N���X��`
//-======================================

// �Q�[�g�̃N���X
class CGate : public CObjectX
{

public:

	// �S�~�̃��f��
	typedef enum
	{
		MODEL_GATE_000 = 0,	// �Q�[�g�̃��f��000
		MODEL_MAX
	}MODEL;

	CGate(int nPriority = 3);
	~CGate();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGate * Create(MODEL model);

	int GetModel(void);
	void SetModel(int nModelNldx);

	void Execution();

	static CDataInt m_nDataModelNldx[MODEL_MAX];	// ���f���̔ԍ�

	CDataInt m_nDataEffectCount;					// �G�t�F�N�g�o���̃J�E���g
private:

	void InitSet(MODEL model);

	void AvailableDisplay(void);

	MODEL m_model;								// �������g�̃��f��
};

#endif	// ��d�C���N���[�h�h�~�̏I��
