
//-===============================================
//-
//-	�G�̏����̃w�b�_�[[enemy.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _ENEMY_H_		// ���̃}�N������`����Ȃ�������
#define _ENEMY_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�O���錾
//=======================================

class CColl;

//-======================================
//-	�N���X��`
//-======================================

// �G�̃N���X
class CEnemy : public CObject
{

public:

	CEnemy();
	~CEnemy();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEnemy* Create(void);
	
	virtual void HitDamage(int nDamage);

	void SetInit(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nLife);

	void Damage(int nDamage);
	bool Dead(void);
	void AddDeadNum(void);

	// �O���Ɉړ�
	void SetMoveForward(float fSpeed) { m_data.move = D3DXVECTOR3(-sinf(m_data.rot.y) * fSpeed, 0.0f, -cosf(m_data.rot.y) * fSpeed); }

	void SetPos(D3DXVECTOR3 pos) { m_data.pos = pos; }
	D3DXVECTOR3 GetPos(void) { return m_data.pos; }

	void SetPosOld(D3DXVECTOR3 posOld) { m_data.posOld = posOld; }
	D3DXVECTOR3 GetPosOld(void) { return m_data.posOld; }

	void SetRot(D3DXVECTOR3 rot) { m_data.rot = rot; }
	D3DXVECTOR3 GetRot(void) { return m_data.rot; }

	void SetSize(D3DXVECTOR3 size) { m_data.size = size; }
	D3DXVECTOR3 GetSize(void) { return m_data.size; }

	void SetMove(D3DXVECTOR3 move) { m_data.move = move; }
	D3DXVECTOR3 GetMove(void) { return m_data.move; }

	void SetLife(int nLife) { m_data.nLife = nLife; }
	int GetLife(void) { return m_data.nLife; }

	void SetHit(bool bHit) { m_data.bHit = bHit; }
	bool GetHit(void) { return m_data.bHit; }

	D3DXVECTOR3 GetTargetRot(void) { return m_infoTarger.rot; }
	float GetTargetLength(void) { return m_infoTarger.fLength; }

	CColl* GetColl(void) { return m_pColl; }

	void SetIsPhaseTarget(bool bIsPhaseTarget) { m_data.bIsPhaseTarget = bIsPhaseTarget; }
	bool GetIsPhaseTarget(void) { return m_data.bIsPhaseTarget; }

protected:

	void UpdatePos(void);
	void UpdateTargetPlayer(void);
	void UpdateCollision(void);
	void UpdateCollisionPlayer(void);

private:

	// ���f�����
	typedef struct
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 posOld;		// �O��̈ʒu
		D3DXVECTOR3 rot;		// ����
		D3DXVECTOR3 size;		// �傫��

		D3DXVECTOR3 move;		// �ړ���

		int nLife;				// �̗�
		bool bHit;				// �q�b�g�̗L��

		bool bIsPhaseTarget;	// �t�F�[�Y�^�[�Q�b�g

	}Data;

	// �^�[�Q�b�g�Ƃ̏��
	struct InfoTarget
	{
		D3DXVECTOR3 rot;	// �^�[�Q�b�g�ւ̌���
		float fLength;		// ����
	};

	Data m_data;				// ���
	InfoTarget m_infoTarger;	// �^�[�Q�b�g�Ƃ̏��

	CColl* m_pColl;		// �����蔻��̏��
};

#endif	// ��d�C���N���[�h�h�~�̏I��
