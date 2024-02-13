
//-===============================================
//-
//-	�e�̏����̃w�b�_�[[bullet.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _BULLET_H_		// ���̃}�N������`����Ȃ�������
#define _BULLET_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object_billboard.h"

#include "data.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�N���X��`
//-======================================

class CBullet : public CObjectBillboard
{

public:

	// �e�̃e�N�X�`���񋓌^
	typedef enum
	{
		TEX_RED_000 = 0,		// �Ԃ̒e000�̃e�N�X�`��
		TEX_BLUE_000,			// �̒e000�̃e�N�X�`��
		TEX_MAX
	}TEX;

	CBullet(int nPriority = 3);
	~CBullet();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(TEX tex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBullet * Create(TEX tex);

	CDataInt m_nDataLife;
	CDataInt m_nDataDamage;

private:

	void Move(void);

	void Add(void);
	bool Sub(void);

	bool CollisionEnemy(void);
	bool CollisionObject(void);

	static int m_nTextureNldx[TEX_MAX];		// �e�N�X�`���̔ԍ�

};

#endif	// ��d�C���N���[�h�h�~�̏I��
