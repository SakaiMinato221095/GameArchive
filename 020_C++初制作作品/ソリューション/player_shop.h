
//-===============================================
//-
//-	�w���v���C���[�����̃w�b�_�[[player_shop.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _PLAYER_SHOP_H_		// ���̃}�N������`����Ȃ�������
#define _PLAYER_SHOP_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

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

//-======================================
//-	�O���錾
//-======================================

class CItem;

class CUiOprDesc;
class CUiTextDesc;

//-======================================
//-	�N���X��`
//-======================================

class CPlayerShop : public CPlayer
{

public:

	typedef enum
	{
		STATE_TYPE_NEUTRAL = 0,	// �ҋ@
		STATE_TYPE_MOVE,		// �ړ�
		STATE_TYPE_BUY,			// �w��
		STATE_TYPE_MAX			// �ő吔
	}STATE_TYPE;

	CPlayerShop();
	~CPlayerShop();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CObjectModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayerShop * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CObjectModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:

	void UpdateItem(void);
	void CollisionItem(void);
	void InputItemAction(CItem *pItem);

	void UpdateMotion(void);

	STATE_TYPE m_stateType;		// ��Ԃ̎��
	STATE_TYPE m_stateTypeOld;	// �O��̏�Ԃ̎��

	CUiOprDesc *m_pUiOprDesc;	// �������UI�̃|�C���^
	CUiTextDesc *m_pUiTextDesc;	// ���������UI�̃|�C���^
};

#endif	// ��d�C���N���[�h�h�~�̏I��
