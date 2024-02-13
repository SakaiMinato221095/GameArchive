
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

#include "data.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�N���X��`
//-======================================

// �A�C�e���̃N���X
class CObjectXNone : public CObjectX
{

public:

	// ���f���̗񋓌^
	typedef enum
	{
		MODEL_OBARAFOOD,			// ���X�X�i�H���j
		MODEL_OBAMART,				// ���X�X�i���z�X�j
		MODEL_OBASTATION,			// ���X�X�i�Q�[���Z���^�[�j
		MODEL_OBARAKURABU,			// ���X�X�i�G�݁j
		MODEL_OBARAMEAT,			// ���X�X�i�����X�j
		MODEL_OBARAVEGETABLE,		// ���X�X�i�ʓX�j
		MODEL_OBARAFLOUR,			// ���X�X�i�ԉ��j
		MODEL_OBARAFUKUYA,			// ���X�X�i�����j

		MODEL_SANDBOX,				// �����i����j
		MODEL_TOILET,				// �����i�g�C���j
		MODEL_WATER,				// �����i�����j
		MODEL_BIN,					// �����i�S�~���j
		MODEL_BENCH,				// �����i�x���`�j
		MODEL_STREETLIGHT,			// �����i�X���j
		MODEL_HORIZONTALBAR,		// �����i�S�_�j
		MODEL_SLIDE,				// �����i�����j

		MODEL_HOUSE001,				// �Ɓi1�j
		MODEL_HOUSE002,				// �Ɓi2�j
		MODEL_HOUSE003,				// �Ɓi3�j

		MODEL_STREET_STALL_DARK,	// �ŘI�X
		MODEL_HOUSE_BLOOD,			// ���t���̉�

		MODEL_ZINJA,				// �_��
		MODEL_OMIKUJI,				// ���݂���

		MODEL_YAKISOBA,				// �₫����
		MODEL_KAKIGOORI,			// �����X
		MDOEL_WANAGE,				// �֓���
		MODEL_TAKOYAKI,				// �����₫
		MODEL_YO_YO_TURI,			// ���[���[�ނ�

		MODEL_TREE,					// ��
		MODEL_TORII,				// ����

		MODEL_NINJA_MANSION000,		// ���~
		MODEL_SCARECROW000,			// ������
		MODEL_SISIODOSI,			// �������ǂ�
		MODEL_SAKURA000,			// ��

		MODEL_PLANT,				// �H��

		MODEL_MAX
	}MODEL;

	// ���f�����
	typedef struct
	{
		D3DXVECTOR3 size;	// �傫��
	}ModelData;

	CObjectXNone(int nPriority = 3);
	~CObjectXNone();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjectXNone * Create(MODEL model);

	int GetModel(void);
	void SetModel(int nModelNldx);

	static void SetModelData(int nNum, ModelData modelData);
	static ModelData GetModelData(int nNum);

	static CDataInt m_nDataModelNldx[MODEL_MAX];	// ���f���̔ԍ�

private:

	void InitSet(MODEL model);

	MODEL m_model;	// ���g�̃��f��
	static ModelData m_modelData[MODEL_MAX];	// ���f���̏��
};

#endif	// ��d�C���N���[�h�h�~�̏I��
