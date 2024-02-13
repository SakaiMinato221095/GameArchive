
//-===============================================
//-
//-	�ʏ�G�̏����̃w�b�_�[[enemy_normal.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _ENEMY_NORMAL_H_		// ���̃}�N������`����Ȃ�������
#define _ENEMY_NORMAL_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "enemy.h"

#include "data.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�N���X��`
//-======================================

// �ʏ�G�̃N���X
class CEnemyNormal : public CEnemy
{

public:

	CEnemyNormal();
	~CEnemyNormal();

	HRESULT Init(MODEL model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEnemyNormal *Create(MODEL model);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nLife);

private:

};

//-======================================
//- �v���g�^�C�v�錾
//-======================================

#endif	// ��d�C���N���[�h�h�~�̏I��
