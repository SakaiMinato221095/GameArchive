
//-===============================================
//-
//-	�S�~�̏����̃w�b�_�[[garbage.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _GARBAGE_H_		// ���̃}�N������`����Ȃ�������
#define _GARBAGE_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

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
class CGarbage : public CObjectX
{

public:

	// �S�~�̃��f��
	typedef enum
	{
		MODEL_BIN_000 = 0,			// �r

		MODEL_BLOOD_KNIFE,			// ���t���̃i�C�t
		MODEL_ORGAN_BOTTLE_NONE,	// ���g�Ȃ�����ۊǕr
		MODEL_SYRINGE_NONE,			// ���g�Ȃ����ˊ�

		MODEL_ICE_CUP,				// �����X����
		MODEL_OMIKUGI,				// ���݂����S�~
		MODEL_PURAGOMI,				// �Ղ炲��

		MODEL_MAX
	}MODEL;

	// ���f�����
	typedef struct
	{
		D3DXVECTOR3 size;	// �傫��
	}ModelData;

	CGarbage();
	~CGarbage();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGarbage * Create(MODEL model);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	int GetModel(void);
	void SetModel(int nModelNldx);

	static void SetModelData(int nNum, ModelData modelData);
	static ModelData GetModelData(int nNum);

	static CDataInt m_nDataModelNldx[MODEL_MAX];	// ���f���̔ԍ�

	CDataInt m_nDataEffectCount;	// �G�t�F�N�g�o���̃J�E���g

	CDataInt m_nGetScore;			// ����X�R�A

private:

	void InitSet(MODEL model);

	MODEL m_model;							// �������g�̃��f��
	CScore::GET_TYPE m_scoreGetType;		// �X�R�A�̎擾�n��

	static ModelData m_modelData[MODEL_MAX];	// ���f���̏��
};

#endif	// ��d�C���N���[�h�h�~�̏I��
