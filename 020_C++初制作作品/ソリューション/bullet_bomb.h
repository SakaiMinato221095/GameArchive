
//-===============================================
//-
//-	���e�e�̏����̃w�b�_�[[bullet_bomb.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _BULLET_BOMB_H_		// ���̃}�N������`����Ȃ�������
#define _BULLET_BOMB_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "bullet.h"

#include "data.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�N���X��`
//-======================================

class CBulletBomb : public CBullet
{

public:

	CBulletBomb(int nPriority = 3);
	~CBulletBomb();

	HRESULT Init(TEX tex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBulletBomb * Create(TEX tex);

	CDataInt m_nDataBlastDamage;

private:

	void InitSet(void);

	void Move(void);

	void Add(void);
	bool Sub(void);

	bool CollisionEnemy(void);
	void CollisionEnemyBlast(int nRawEmyNum);
	bool CollisionObject(void);

};

#endif	// ��d�C���N���[�h�h�~�̏I��
