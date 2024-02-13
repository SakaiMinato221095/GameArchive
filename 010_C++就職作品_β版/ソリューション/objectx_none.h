
//-===============================================
//-
//-	���ʂȂ���X�t�@�C���I�u�W�F�N�g�����̃w�b�_�[[objectx_none.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _OBJECT_X_NONE_H_		// ���̃}�N������`����Ȃ�������
#define _OBJECT_X_NONE_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

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

// ���ʂȂ��I�u�W�F�N�g�̃N���X
class CObjectXNone : public CObjectX
{

public:

	// ���f���̗񋓌^
	typedef enum
	{
		MODEL_BLOCK_000 = 0,
		MODEL_MAX
	}MODEL;

	// ���f�����
	typedef struct
	{
		int nModelNldx;		// ���f���̔ԍ�
		D3DXVECTOR3 size;	// �傫��
	}ModelData;

	CObjectXNone(int nPriority = 3);
	~CObjectXNone();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjectXNone * Create(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	int GetModel(void) { return m_model; }

	static void SetModelData(int nNum, ModelData modelData) { m_modelData[nNum] = modelData; }
	static ModelData GetModelData(int nNum) { return m_modelData[nNum]; }

private:

	void InitSet(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	MODEL m_model;								// ���g�̃��f��
	static ModelData m_modelData[MODEL_MAX];	// ���f���̏��
};

#endif	// ��d�C���N���[�h�h�~�̏I��
