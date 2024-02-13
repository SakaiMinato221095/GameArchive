
//-===============================================
//-
//-	�t�F�[�Y�Ǘ��̏����̃w�b�_�[[phase_manager.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _PHASE_MANAGER_H_		// ���̃}�N������`����Ȃ�������
#define _PHASE_MANAGER_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�R���X�g��`
//=======================================

//=======================================
//=	�O���錾
//=======================================

class CColl;
class CObj3dWall;

//-======================================
//-	�N���X��`
//-======================================

class CPhaseManager
{

public:

	enum TYPE_PHASE
	{
		TYPE_PHASE_ONE = 0,		// �t�F�[�Y1
		TYPE_PHASE_TWO,			// �t�F�[�Y2
		TYPE_PHASE_THREE,		// �t�F�[�Y3
		TYPE_PHASE_COMP,		// �R���v���[�g
		TYPE_PHASE_MAX
	};

	CPhaseManager(int nPriority);
	~CPhaseManager();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void AddDeadEnemy(void);

	static CPhaseManager* Create(void);
	
	void SetTargetCompNum(int nTargetCompNum) { m_info.nTargetCompNum = nTargetCompNum; }

	TYPE_PHASE GetTypePhase(void) { return m_info.typePhaseNew; }
	

private:

	void SetComp(void);

	struct Info
	{
		int nTargetCompNum;			// �^�[�Q�b�g�̍ő吔
		int nTargetCompCnt;			// �^�[�Q�b�g�̌��j��
		TYPE_PHASE typePhaseNew;	// ���݂̃t�F�[�Y
	};

	Info m_info;

};

#endif	// ��d�C���N���[�h�h�~�̏I��
