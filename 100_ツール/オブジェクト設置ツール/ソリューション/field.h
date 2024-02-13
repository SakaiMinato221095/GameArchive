
//-===============================================
//-
//-	�n�ʏ����̃w�b�_�[[field.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _FIELD_H_		// ���̃}�N������`����Ȃ�������
#define _FIELD_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object3d.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�N���X��`
//-======================================

// �A�C�e���̃N���X
class CField : public CObject3d
{

public:
	
	// �t�B�[���h�̃e�N�X�`���̗񋓌^
	typedef enum
	{
		TEX_WHITE_TILE_000 = 0,		// ������000�̃e�N�X�`��
		TEX_ROAD_000,				// ���H000�̃e�N�X�`��
		TEX_ASPHALT_000,			// �A�X�t�@���g000�̃e�N�X�`��
		TEX_GLASS_000,				// ����000�̃e�N�X�`��
		TEX_TILE_000,
		TEX_MAX
	}TEX;

	CField();
	~CField();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(TEX tex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CField * Create(TEX tex);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);

private:

	static int m_nTextureNldx[TEX_MAX];		// �e�N�X�`���̔ԍ�

};

//-======================================
//- �v���g�^�C�v�錾
//-======================================

#endif	// ��d�C���N���[�h�h�~�̏I��
