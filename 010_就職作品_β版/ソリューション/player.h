
//-===============================================
//-
//-	�v���C���[�����̃w�b�_�[[player.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _PLAYER_H_		// ���̃}�N������`����Ȃ�������
#define _PLAYER_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object.h"

#include "model.h"
#include "motion.h"

#include "command.h"

//=======================================
//=	�}�N����`
//=======================================

#define INSTANCE_MAX	(8)		// ���g�̃|�C���^�̍ő吔

//-======================================
//-	�O���錾
//-======================================

class CObjectX;
class CObject3d;
class CColl;
class CAttack;

class CObj2dGage;

//-======================================
//-	�N���X��`
//-======================================

class CPlayer : public CObject
{

public:

	// ���[�V�������
	typedef enum
	{
		MOTION_STATE_NEUTRAL = 0,	// �ҋ@
		MOTION_STATE_MOVE,			// �ړ�
		MOTION_STATE_PUNCH,			// �p���`
		MOTION_STATE_KICK,			// �L�b�N
		MOTION_STATE_PUNCH_FINISH,	// �p���`��{�t�B�j�b�V��
		MOTION_STATE_KICK_FINISH,	// �L�b�N��{�t�B�j�b�V��
		MOTION_STATE_MAX
	}MOTION_STATE;

	// ���[�V�������
	typedef enum
	{
		STATE_NEUTRAL = 0,	// �ҋ@
		STATE_BATTLE,		// �퓬��
		STATE_FINISH,		// �t�B�j�b�V��
		STATE_MAX
	}STATE;

	// �ǉ��l�̏��
	typedef struct
	{
		float speedRate;	// ���x�ǉ��̔{��
		int sppedPlusTime;	// ���x�ǉ��̎���

	}DataPlus;

	// ���l
	typedef struct
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 posOld;		// �O��̈ʒu
		D3DXVECTOR3 posTgt;		// �^�[�Q�b�g�̈ʒu

		D3DXVECTOR3 rot;		// ����
		D3DXVECTOR3 rotDest;	// �ړI�̌���

		D3DXVECTOR3 move;		// �ړ���
		D3DXVECTOR3 moveHold;	// �ێ������ړ���

		D3DXVECTOR3 size;		// �傫��

		int nLife;				// �̗�

		DataPlus plus;			// �ǉ��l

		STATE state;				// ���̎��
		MOTION_STATE motionState;	// ���[�V������Ԃ̎��

		bool bIsTarget;				// �^�[�Q�b�g�̗L��

		int nAttackPartsNldx;		// �U���̕���
	}Data;

	CPlayer();
	~CPlayer();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax);

	void Uninit(void);
	void Update(void);
	void Draw(void);

	virtual void HitDamage(int nDamage);

	static CPlayer * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType);

	CMotion* GetMotion(void) { return m_pMotion; }

	CModel* GetModel(int nNumParts) { return m_apModel[nNumParts]; }

	void SetData(Data data) { m_data = data; }
	Data GetData(void) { return m_data; }

	MOTION_STATE GetMotionState(void) { return m_data.motionState; }

	void SetPlus(float fRate, int nTime) { m_data.plus.speedRate = fRate, m_data.plus.sppedPlusTime = nTime; }

private:

	// �����蔻��̎��
	typedef enum
	{
		COLL_TYPE_NEUTRAL = 0,	// �ʏ�
		COLL_TYPE_SEARCH,		// ���G
		COLL_TYPE_MAX
	}COLL_TYPE;

	void InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	void UpdatePos(void);
	void UpdateBattle(void);
	void UpdateRot(void);
	void UpdatePlusData(void);
	void UpdateAttack(void);
	void UpdateCommand(void);
	void UpdateCollision(void);
	void UpdateMotionNone(void);

	void InputMove(void);
	void InputCombo(void);

	void SetAttack(CCommand::INPUT_TYPE inputType);

	void SetAttackFinish(void);
	void SetAttackFinishKick(void);

	void DebugPlayer(void);

	Data m_data;							// �l���i�[
	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X

	CModel *m_apModel[MODEL_PARTS_MAX];		// ���f���i�p�[�c�j�̃|�C���^
	int m_nNumModel;						// ���f���i�p�[�c�j�̑���

	CColl* m_apColl[COLL_TYPE_MAX];			// �����蔻����
	CMotion *m_pMotion;						// ���[�V�����̃|�C���^
	CAttack* m_pAttack;						// �U���̃|�C���^
	CCommand* m_pCommand;					// �R�}���h�̃|�C���^
	CObj2dGage* m_pLife2dGage;				// �̗͕\���̃|�C���^
};

#endif	// ��d�C���N���[�h�h�~�̏I��
