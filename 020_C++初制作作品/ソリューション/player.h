
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

#include "data.h"

#include "object_model.h"
#include "motion.h"

//=======================================
//=	�}�N����`
//=======================================

//-======================================
//-	�O���錾
//-======================================

class CObjectX;
class CObject3d;

//-======================================
//-	�N���X��`
//-======================================

class CPlayer : public CObject
{

public:

	CPlayer();
	~CPlayer();

	HRESULT Init(CObjectModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax);

	void Uninit(void);
	void Update(void);
	void Draw(void);

	virtual void Hit(int nDamage);

	void CollisionObject(void);
	void CollisionMove(CObjectX *pObjX);
	void CollisionMove(CObject3d * pObj3d);

	void DebugPlayer(void);

	CMotion *GetMotion(void);

	CDataD3DXVECTOR3 m_dataPos;			// �ʒu
	CDataD3DXVECTOR3 m_dataPosOld;		// �O��̈ʒu

	CDataD3DXVECTOR3 m_dataRot;			// ����
	CDataD3DXVECTOR3 m_dataRotDest;		// �ړI�̌���

	CDataD3DXVECTOR3 m_dataSize;		// �傫��

	CDataD3DXVECTOR3 m_dataMove;		// �ړ���
	CDataD3DXVECTOR3 m_dataMoveHold;	// �ێ������ړ���

	CDataBool m_bDataStopMove;			// �ړ����~
	CDataBool m_bDataStopMoveRot;		// �����ړ��̒�~

	CObjectModel *GetObjectModel(int nNumParts);

private:

	void UpdatePos(void);
	void UpdateRot(void);
	void InputMove(void);

	D3DXMATRIX m_mtxWorld;			// ���[���h�}�g���b�N�X

	CObjectModel *m_apObjectModel[MODEL_PARTS_MAX];	// ���f���i�p�[�c�j�̃|�C���^
	int m_nNumModel;								// ���f���i�p�[�c�j�̑���

	CMotion *m_pMotion;				// ���[�V�����̃|�C���^
};

#endif	// ��d�C���N���[�h�h�~�̏I��
