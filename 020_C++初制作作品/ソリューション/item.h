
//-===============================================
//-
//-	�A�C�e�������̃w�b�_�[[item.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _ITEM_H_		// ���̃}�N������`����Ȃ�������
#define _ITEM_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object_x.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�O���錾
//-======================================

class CObj2dItemInfo;

//-======================================
//-	�N���X��`
//-======================================

// �A�C�e���̃N���X
class CItem : public CObjectX
{

public:

	typedef enum
	{
		MODEL_GUN_000 = 0,	// �X�e�[�^�X�����i���j
		MODEL_GUN_001,		// �X�e�[�^�X�����i��j
		MODEL_GUN_002,		// �X�e�[�^�X�����i���j
		MODEL_BOMB_000,		// �{��
		MODEL_MAX
	}MODEL;

	// ���f�����
	typedef struct
	{
		D3DXVECTOR3 size;	// �傫��
		int nType;			// ���
		int nBuyMax;		// �ő�w����
		int nPrice;			// �l�i
	}ModelData;

	CItem();
	~CItem();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CItem * Create(MODEL model);

	int GetModel(void);
	void SetModel(int nModelNldx);

	static void SetModelData(int nNum, ModelData modelData);
	static ModelData GetModelData(int nNum);

	void InitSet(MODEL model);

	void Execution(void);

	void AvailableDisplay(void);

	bool GetBuyUse(void);

	CObj2dItemInfo *GetItemInfo(void);
	
	static CDataInt m_nDataModelNldx[MODEL_MAX];	// ���f���̔ԍ�

	CDataD3DXVECTOR3 m_dataRotAdd;	// ��]��

	CDataBool m_bDataUse;			// �g�p�̗L��
	CDataInt m_nBuyCount;			// �w����

	CDataInt m_nDataEffectCount;	// �G�t�F�N�g�̃J�E���g

private:

	MODEL m_model;								// �������g�̃��f��
	static ModelData m_modelData[MODEL_MAX];	// ���f���̏��
	CObj2dItemInfo *m_pItemInfo;				// �A�C�e���̏��
};

#endif	// ��d�C���N���[�h�h�~�̏I��
