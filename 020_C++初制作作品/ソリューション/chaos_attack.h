
//-===============================================
//-
//-	�ł̍U���̏����̃w�b�_�[[chaos_attack.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _CHAOS_ATTACK_H_		// ���̃}�N������`����Ȃ�������
#define _CHAOS_ATTACK_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object.h"

#include "data.h"

#include "manager_object.h"

//-======================================
//-	�}�N����`
//-======================================

#define COLLISION_NUM_MAX	(4)	// �����蔻��̍ő吔

//-======================================
//-	�O���錾
//-======================================

class CObjectCol;

//-======================================
//-	�N���X��`
//-======================================

class CChaosAttack : public CObject
{

public:

	// �ł̍U���̓����蔻��̍\����
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 size;
	}Collision;

	CChaosAttack(int nPriority = 3);
	~CChaosAttack();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nDamage);

	static CChaosAttack * Create(void);

	CDataInt m_nDataDamage;
	CDataInt m_nDamageTime;

	CDataD3DXVECTOR3 m_dataPos;
	CDataD3DXVECTOR3 m_dataRot;

private:

	void Add(void);
	void Sub(void);

	bool CollisionEnemy(void);

	void InitSet(void);

	Collision m_aCol[COLLISION_NUM_MAX];			// �����蔻��

	int m_aEnemyDamageCut[ENEMY_NORMAL_NUM_MAX];	// �G�̃_���[�W�J�E���g 
	int m_nEnemyBossDmageCut;						// �{�X�̃_���[�W�J�E���g
};

#endif	// ��d�C���N���[�h�h�~�̏I��
