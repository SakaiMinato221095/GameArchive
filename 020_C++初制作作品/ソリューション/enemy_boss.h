
//-===============================================
//-
//-	�{�X�G�̏����̃w�b�_�[[enemy_boss.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _ENEMY_BOSS_H_		// ���̃}�N������`����Ȃ�������
#define _ENEMY_BOSS_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "enemy.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�O���錾
//-======================================

class CObjectCol;

//-======================================
//-	�N���X��`
//-======================================

// �ʏ�G�̃N���X
class CEnemyBoss : public CEnemy
{

public:

	typedef enum
	{
		STATE_NORMAL = 0,	// �ʏ���
		STATE_TARGET,		// �ǔ����
		STATE_ATTACK,		// �U�����
		STATE_COOL_TIME,	// �N�[���^�C�����
		STATE_MAX
	}STATE;

	CEnemyBoss();
	~CEnemyBoss();

	HRESULT Init(MODEL_TYPE model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEnemyBoss *Create(MODEL_TYPE modelType);

	void Hit(int nDamage);

	CObjectCol *GetObjectCol(void);

	CDataInt m_nDataAtkCnt;		// �U���J�E���g

	CDataInt m_nDataCoolTimeCnt;	// �N�[���^�C���J�E���g

private:

	STATE state;				// ���
	CObjectCol *m_pObjCol;		// �R���W�����I�u�W�F�N�g�̃|�C���^

	void InitSet(void);

	void AiSearch(void);
	void AiTarget(void);
	void AiAttack(void);

	void AiCoolTime(void);

};

#endif	// ��d�C���N���[�h�h�~�̏I��
