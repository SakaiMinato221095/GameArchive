
//-===============================================
//-
//-	���̏����̃w�b�_�[[fist.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _FIST_H_		// ���̃}�N������`����Ȃ�������
#define _FIST_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

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

class CFist : public CObjectX
{

public:

	// ���̃��f���񋓌^
	typedef enum
	{
		MODEL_FIST_000 = 0,
		MODEL_MAX
	}MODEL;

	CFist(int nPriority = 3);
	~CFist();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL tex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CFist * Create(MODEL tex);

	int GetModel(void);
	void SetModel(int nModelNldx);

	CDataInt m_nDataLife;
	CDataInt m_nDataDamage;

private:

	void Move(void);

	void Add(void);
	bool Sub(void);

	bool CollisionEnemy(void);
	bool CollisionObject(void);

	static int m_nTextureNldx[MODEL_MAX];		// �e�N�X�`���̔ԍ�

};

#endif	// ��d�C���N���[�h�h�~�̏I��
