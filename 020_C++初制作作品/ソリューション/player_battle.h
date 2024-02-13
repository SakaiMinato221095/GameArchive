
//-===============================================
//-
//-	�퓬�v���C���[�����̃w�b�_�[[player_battle.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _PLAYER_BATTLE_H_		// ���̃}�N������`����Ȃ�������
#define _PLAYER_BATTLE_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "player.h"

#include "data.h"

#include "object_model.h"
#include "motion.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//=	�O���錾
//=======================================

class CGate;

class CChaosAttack;

class CUiOprDesc;
class CUiTextDesc;

//-======================================
//-	�N���X��`
//-======================================

class CPlayerBattle : public CPlayer
{

public:

	typedef enum
	{
		STATE_TYPE_NEUTRAL = 0,		// �ҋ@
		STATE_TYPE_MOVE,			// �ړ�
		STATE_TYPE_ATTACK,			// �U��
		STATE_TYPE_NOR_ATTACK,		// �ʏ�`���[�W�U��
		STATE_TYPE_CHAOS_ATTACK,	// �Ń`���[�W�U�� 
		STATE_TYPE_DAMAGE,			// �_���[�W
		STATE_TYPE_DEAD,			// ���S���
		STATE_TYPE_MAX			
	}STATE_TYPE;

	CPlayerBattle();
	~CPlayerBattle();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CObjectModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayerBattle * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CObjectModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	void ColGate(void);

	void Hit(int nDamage);

	CDataInt nDataShotIntervalCount;	// �e�̊Ԋu�̃J�E���g
	CDataBool bDataShot;				// �ˌ��̗L��
	CDataBool bDataShotAgain;			// �Ďˌ�
	CDataBool m_bDataCharge;			// �`���[�W�̗L��
	CDataInt m_nDataChargeCut;			// �`���[�W�J�E���g
	CDataInt m_nDataChargeMax;			// �`���[�W�̍ő�l

	CDataInt m_nDataCoolTime;			// �N�[���^�C��
private:

	void InputAttack(void);

	void InputGateAction(CGate * pGate);

	void UpdateAttack(void);
	void UpdateMotion(void);

	void ShotNor(void);
	void ShotNorCharge(void);
	void ShotChaosCharge(void);

	STATE_TYPE m_stateType;			// ��Ԃ̎��
	STATE_TYPE m_stateTypeNew;		// �ŐV�̏�Ԃ̎��

	CUiOprDesc *m_pUiOprDesc;		// �������UI�̃|�C���^
	CUiTextDesc *m_pUiTextDesc;		// ���������UI�̃|�C���^

	CChaosAttack *m_pChaosAttack;	// �ł̍U��
};

#endif	// ��d�C���N���[�h�h�~�̏I��
