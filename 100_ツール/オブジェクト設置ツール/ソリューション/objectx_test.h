
//-===============================================
//-
//-	�e�X�g�p��X�t�@�C���I�u�W�F�N�g�����̃w�b�_�[[objectx_test.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _OBJECT_X_TEST_H_		// ���̃}�N������`����Ȃ�������
#define _OBJECT_X_TEST_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

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

// �A�C�e���̃N���X
class CObjectXTest : public CObjectX
{

public:

	// ���f���̗񋓌^
	typedef enum
	{
		MODEL_HUMAN_BOX_000 = 0,		// �l�^�̊���f��
		MODEL_MAX
	}MODEL;

	CObjectXTest();
	~CObjectXTest();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjectXTest * Create(MODEL model);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);

	int GetModel(void);
	void SetModel(int nModelNldx);

	static CDataInt m_nDataModelNldx[MODEL_MAX];	// ���f���̔ԍ�

private:

	MODEL m_model;	// ���g�̃��f��
};

#endif	// ��d�C���N���[�h�h�~�̏I��
