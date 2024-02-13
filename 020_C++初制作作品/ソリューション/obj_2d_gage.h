
//-===============================================
//-
//-	�Q�[�W�����̃w�b�_�[[obj_2d_gage.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _OBJ_2D_GAGE_H_		// ���̃}�N������`����Ȃ�������
#define _OBJ_2D_GAGE_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object2d.h"

#include "data.h"

//-======================================
//-	�N���X��`
//-======================================

class CObj2dGage : public CObject2d
{

public:

	// �����̃e�N�X�`���񋓌^
	typedef enum
	{
		TEX_NULL = 0,		// �Ȃ�
		TEX_MAX
	}TEX;

	// �Q�[�W�̎��
	typedef enum
	{
		TYPE_LEFT = 0,
		TYPE_RIGHT,
		TYPE_CENTER,
		TYPE_MAX
	}TYPE;

	CObj2dGage(int nPriority = 3);
	~CObj2dGage();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(TEX tex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObj2dGage *Create(TEX tex);

	void SetVtx(void);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color , TYPE type);

	CDataD3DXVECTOR3 m_dataGage;

private:

	static int m_nTextureNldx[TEX_MAX];		// �e�N�X�`���ԍ�
	TYPE m_type;							// ���
};

#endif	// ��d�C���N���[�h�h�~�̏I��
