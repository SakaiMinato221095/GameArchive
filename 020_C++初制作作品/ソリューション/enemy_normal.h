
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
class CEnemyNormal : public CEnemy
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

	CEnemyNormal();
	~CEnemyNormal();

	HRESULT Init(MODEL_TYPE model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEnemyNormal *Create(MODEL_TYPE modelType);

	void Hit(int nCutEnemy, int nDamage);

	CObjectCol *GetObjectCol(void);

	CDataFloat m_fDataSpeed;	// ���x
	CDataFloat m_fDataSpeedNor;	// �������̑��x
	CDataFloat m_fDataSpeedStr;	// �������̑��x

	CDataD3DXVECTOR3 m_dataSearchRange;		// ���G�͈�
	CDataD3DXVECTOR3 m_dataSearchRangeNor;	// �ʏ�̍��G�͈�
	CDataD3DXVECTOR3 m_dataSearchRangeStr;	// �������̍��G�͈�

	CDataD3DXVECTOR3 m_dataAttackRange;		// �U���͈�
	CDataD3DXVECTOR3 m_dataAttackRangeNor;	// �ʏ�̍U���͈�
	CDataD3DXVECTOR3 m_dataAttackRangeStr;	// �������̍U���͈�

	CDataInt m_nDataAtkCnt;			// �U���J�E���g
	CDataInt m_nDataCoolTimeCnt;	// �N�[���^�C���J�E���g
	CDataInt m_nDataStrTime;		// ��������
	CDataInt m_nDataStrTimeCut;		// �������ԃJ�E���g

private:

	STATE state;
	CObjectCol *m_pObjCol;

	void InitSet(void);

	void AiSearch(void);
	void AiTarget(void);
	void AiAttack(void);
	void AiCoolTime(void);

};

#endif	// ��d�C���N���[�h�h�~�̏I��
