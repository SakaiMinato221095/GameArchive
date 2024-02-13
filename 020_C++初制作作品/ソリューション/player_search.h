
//-===============================================
//-
//-	�T���v���C���[�����̃w�b�_�[[player_search.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _PLAYER_SEARCH_H_		// ���̃}�N������`����Ȃ�������
#define _PLAYER_SEARCH_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

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

#define GARBAGE_SCORE_STOCK_MAX	(10)	// �S�~�X�R�A�̃X�g�b�N�ő吔

//-======================================
//-	�O���錾
//-======================================

class CEventObject;
class CGarbage;
class CGarbageCollect;
class CGate;

class CUiOprDesc;
class CUiTextDesc;

//-======================================
//-	�N���X��`
//-======================================

class CPlayerSearch : public CPlayer
{

public:

	typedef enum
	{
		STATE_TYPE_NEUTRAL = 0,	// �ҋ@
		STATE_TYPE_MOVE,		// �ړ�
		STATE_TYPE_TOUCH,		// �G��
		STATE_TYPE_EAT,			// �H�ׂ�
		STATE_TYPE_MAX
	}STATE_TYPE;

	CPlayerSearch();
	~CPlayerSearch();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CObjectModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayerSearch * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CObjectModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	CDataInt m_nDataStateTime;		// ��Ԏ���
	CDataInt m_nDataStateCount;		// ��Ԏ��Ԃ̃J�E���g

private:

	void UpdateEvent(void);
	void CollisionEvent(void);
	void InputEventAction(CEventObject *pEventObject);
	void InputGarbageAction(CGarbage * pGarbage, int nNum);
	void InputGateAction(CGate * pGate);

	void UpdateMotion(void);

	STATE_TYPE m_stateType;		// ��Ԃ̎��
	STATE_TYPE m_stateTypeOld;	// �O��̏�Ԃ̎��

	CUiOprDesc *m_pUiOprDesc;	// �������UI�̃|�C���^
	CUiTextDesc *m_pUiTextDesc;	// ���������UI�̃|�C���^
};


#endif	// ��d�C���N���[�h�h�~�̏I��
