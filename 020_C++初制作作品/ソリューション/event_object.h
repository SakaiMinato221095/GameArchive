
//-===============================================
//-
//-	�I�u�W�F�N�g�C�x���g�̏����̃w�b�_�[[event_object.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _EVENT_OBJECT_H_		// ���̃}�N������`����Ȃ�������
#define _EVENT_OBJECT_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

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

// �G�̃N���X
class CEventObject : public CObjectX
{

public:

	// �C�x���g�I�u�W�F�N�g�̃��f��
	typedef enum
	{
		MODEL_DRINK_SHOP_000 = 0,	// ���̋@
		MODEL_VEGETABLE_000,		// �J�W�m
		MODEL_MAX
	}MODEL;

	// ���f�����
	typedef struct
	{
		D3DXVECTOR3 size;	// �傫��
	}ModelData;

	CEventObject(int nPriority = 3);
	~CEventObject();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEventObject * Create(MODEL model);

	int GetModel(void);
	void SetModel(int nModelNldx);

	static void SetModelData(int nNum, ModelData modelData);
	static ModelData GetModelData(int nNum);

	void Execution(void);

	static CDataInt m_nDataModelNldx[MODEL_MAX];	// ���f���̔ԍ�

	CDataInt m_nDataReuseTime;		// �Ďg�p����
	CDataInt m_nDataReuseCount;		// �Ďg�p�J�E���g
	CDataBool m_bDataUse;			// �g�p�̗L��

	CDataInt m_nDataEffectCount;	// �G�t�F�N�g�o���̃J�E���g

	CDataInt m_nGetScore;			// ����X�R�A

private:

	void InitSet(MODEL model);

	void UpdateReuse(void);
	void AvailableDisplay(void);

	static int m_nEventObjectNum;			// �C�x���g�I�u�W�F�N�g�̑���

	MODEL m_model;							// �������g�̃��f��
	CScore::GET_TYPE m_scoreGetType;		// �X�R�A�̎擾�n��

	static ModelData m_modelData[MODEL_MAX];	// ���f���̏��
};

//-======================================
//- �v���g�^�C�v�錾
//-======================================

#endif	// ��d�C���N���[�h�h�~�̏I��
