
//-===============================================
//-
//-	�G���G�̏����̃w�b�_�[[enemy_minion.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _ENEMY_MINION_H_		// ���̃}�N������`����Ȃ�������
#define _ENEMY_MINION_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "enemy.h"

#include "model.h"
#include "motion.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�O���錾
//=======================================

class CCharacter;
class CBillboardGage;

class CAttack;

//-======================================
//-	�N���X��`
//-======================================

// �{�X�G�̃N���X
class CEnemyMinion : public CEnemy
{

public:

	// �e�N�X�`��
	enum TEX
	{
		TEX_NULL = 0,	// �Ȃ�
		TEX_MAX
	};

	// ���[�V�������
	enum MOTION_STATE
	{
		MOTION_STATE_NEUTRAL = 0,	// �ҋ@
		MOTION_STATE_MOVE,			// �ړ�
		MOTION_STATE_KICK_1,		// �L�b�N1
		MOTION_STATE_KICK_2,		// �L�b�N2
		MOTION_STATE_KICK_3,		// �L�b�N3
		MOTION_STATE_CHARGE,		// �ːi
		MOTION_STATE_CHARGE_ATTACK,	// �ːi�U��
		MOTION_STATE_DAMAGE,		// �_���[�W
		MOTION_STATE_BIG_DAMAGE,	// �������
		MOTION_STATE_MAX
	};

	// AI�̏��
	enum AI_STATE
	{
		AI_STATE_WAIT = 0,		// �ҋ@���
		AI_STATE_KICK_1,		// �R��1
		AI_STATE_CHARGE,		// �ːi
		AI_STATE_MAX
	};

	CEnemyMinion();
	~CEnemyMinion();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEnemyMinion* Create(CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType);

	virtual void HitDamage(int nDamage);

	void SetInit(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, int nMaxLife);

private:

	enum STATE
	{
		STATE_NORMAL = 0,	// �ʏ���
		STATE_DAMAGE,		// �_���[�W���
		STATE_ATTACK,		// �U�����
		STATE_BIG_DAMAGE,	// ������я��
		STATE_MAX
	};

	// ���
	struct Info
	{
		STATE state;	// ���
	};

	// �����ڂ̏��
	struct InfoVisual
	{
		CCharacter* pCharacter;			// �L�����N�^�[�̃|�C���^
		MOTION_STATE motionState;		// ���[�V�������

		CBillboardGage* pLifeBillGage;	// �r���{�[�h�̗̑̓Q�[�W
	};

	// �t�����
	struct InfoAttach
	{
		CAttack* pAttack;			// �U���̃|�C���^
		int nPartsIdx;				// �p�[�c�̔ԍ�
	};

	// AI�̏��
	struct InfoAi
	{
		AI_STATE state;			// AI�̏�ԏ��
		int nCnt;				// AI�̏�ԃJ�E���g
		int nCntChange;			// AI�̏�ԃJ�E���g�̐؂�ւ���
	};

	void UpdateVisual(void);
	void UpdateMotion(void);
	void UpdateAi(void);
	void UpdateAttack(void);

	void UpdateDamage(void);
	void UpdateBigDamage(void);

	void AiWait(void);
	void AiKickCombo(void);
	void AiCharge(void);

	void SetAiActiv(void);
	void SetCombo(void);
	void SetAttack(int nPartsNum);

	void SetState(MOTION_STATE motionState);
	void ReSetState(void);

	void Debug(void);

	Info m_info;				// ���
	InfoVisual m_infoVisual;	// �����ڏ��
	InfoAttach m_infoAttach;	// �t�����
	InfoAi m_infoAi;			// AI�̏��

	static int m_nTextureNldx[TEX_MAX];	// �e�N�X�`���ԍ�
};

#endif	// ��d�C���N���[�h�h�~�̏I��
