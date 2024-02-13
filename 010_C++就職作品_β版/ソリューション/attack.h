
//-===============================================
//-
//-	�U���̏����̃w�b�_�[[attack.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _ATTACK_H_		// ���̃}�N������`����Ȃ�������
#define _ATTACK_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object.h"

#include "mgr_coll.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//=	�O���錾
//=======================================

class CColl;

//-======================================
//-	�N���X��`
//-======================================

class CAttack : public CObject
{

public:

	// ���l
	typedef struct
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 size;		// �傫��

		D3DXVECTOR3 posPlus;	// �ǉ��ʒu

		int nDamage;			// �_���[�W

		CMgrColl::TAG tagTgt;	// �^�[�Q�b�g�̃^�O
	}Info;

	CAttack();
	virtual ~CAttack();

	HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nDamage, CMgrColl::TAG tagTgt);

	static CAttack* Create(void);

	void UpdateHit(void);

	void Debug(void);

	void UpdateData(D3DXVECTOR3 pos, D3DXVECTOR3 size) { m_info.pos = pos, m_info.size = size; }

	CColl* GetColl(void) { return m_pColl; }

	D3DXVECTOR3 GetPos(void) { return m_info.pos; }
	D3DXVECTOR3 GetSize(void) { return m_info.size; }

	void SetPosPlus(D3DXVECTOR3 posPlus) { m_info.posPlus = posPlus; }
	D3DXVECTOR3 GetPosPlus(void) { return m_info.posPlus; }

	void SetDamage(int nDamage) { m_info.nDamage = nDamage; }
	int GetDamage(void) { return m_info.nDamage; }

	void SetTagTgt(CMgrColl::TAG tagTgt) { m_info.tagTgt = tagTgt; }
	CMgrColl::TAG GetTagTgt(void) { return m_info.tagTgt; }

private:

	Info m_info;			// �l���

	CColl* m_pColl;			// �����蔻��̏��
};

#endif	// ��d�C���N���[�h�h�~�̏I��
