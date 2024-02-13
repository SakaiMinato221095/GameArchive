
//-===============================================
//-
//-	�S�~���W�̏����̃w�b�_�[[garbage_collect.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _GARBAGE_COLLECT_H_		// ���̃}�N������`����Ȃ�������
#define _GARBAGE_COLLECT_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

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

// �S�~�̃N���X
class CGarbageCollect : public CObjectX
{

public:

	// �S�~�̃��f��
	typedef enum
	{
		MODEL_GARBAGE_CAR_000 = 0,	// �S�~�����
		MODEL_GARBAGE_CAR_DARK_000,	// �ł̃S�~�����
		MODEL_MAX
	}MODEL;

	// ���f�����
	typedef struct
	{
		D3DXVECTOR3 size;	// �傫��
		int nType;			// ���
	}ModelData;

	CGarbageCollect(int nPriority = 3);
	~CGarbageCollect();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGarbageCollect * Create(MODEL model);

	int GetModel(void);
	void SetModel(int nModelNldx);

	static void SetModelData(int nNum, ModelData modelData);
	static ModelData GetModelData(int nNum);

	void Execution();

	static CDataInt m_nDataModelNldx[MODEL_MAX];	// ���f���̔ԍ�

	CDataInt m_nDataEffectCount;					// �G�t�F�N�g�o���̃J�E���g

private:

	void InitSet(MODEL model);

	void AvailableDisplay(void);

	MODEL m_model;							// �������g�̃��f��

	static ModelData m_modelData[MODEL_MAX];	// ���f���̏��
};

#endif	// ��d�C���N���[�h�h�~�̏I��