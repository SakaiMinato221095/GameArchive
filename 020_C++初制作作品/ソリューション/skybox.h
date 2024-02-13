
//-===============================================
//-
//-	�X�J�C�{�b�N�X�����̃w�b�_�[[skybox.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _SKYBOX_H_		// ���̃}�N������`����Ȃ�������
#define _SKYBOX_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

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
class CSkybox : public CObjectX
{

public:

	// ���f���̗񋓌^
	typedef enum
	{
		MODEL_SKYBOX_000 = 0,
		MODEL_MAX
	}MODEL;

	CSkybox(int nPriority = 3);
	~CSkybox();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CSkybox * Create(MODEL model);

	int GetModel(void);
	void SetModel(int nModelNldx);

	static CDataInt m_nDataModelNldx[MODEL_MAX];	// ���f���̔ԍ�

private:

	void InitSet(MODEL model);

	MODEL m_model;								// ���g�̃��f��
};

#endif	// ��d�C���N���[�h�h�~�̏I��