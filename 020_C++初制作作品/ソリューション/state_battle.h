
//-===============================================
//-
//-	�퓬�X�e�[�^�X�����̃w�b�_�[[state_battle.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _STATE_BATTLE_H_		// ���̃}�N������`����Ȃ�������
#define _STATE_BATTLE_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "data.h"

//-======================================
//-	�N���X��`
//-======================================

class CStateBattle
{
public:

	typedef enum
	{
		SUB_WEAPON_TYPE_BOMB  = 0,	// �{��
		SUB_WEAPON_TYPE_MAX
	}SUB_WEAPON_TYPE;

	typedef enum
	{
		ELEM_TYPE_NORMAL = 0,	// �ʏ푮��
		ELEM_TYPE_LOW,			// ������
		ELEM_TYPE_CHAOS,		// ������
		ELEM_TYPE_MAX
	}ELEM_TYPE;

	CStateBattle();
	~CStateBattle();
	
	void Init(void);
	void Uninit(void);
	void Update(void);

	static CStateBattle *Create();

	void SetWeaponCopper(bool bUse);
	void SetWeaponSilver(bool bUse);
	void SetWeaponGold(bool bUse);

	void SetSubWeaponBomb(bool bUse);

	void AddElem(int nNor,int nLow,int nChaos);

	SUB_WEAPON_TYPE GetWeaponType(void);
	ELEM_TYPE GetElemType(void);

	CDataInt m_nSubWeaponNum;					// �T�u����̉�

	CDataInt m_nDataShotInterval;				// �e�̔��ˊԊu
	CDataBool m_bDataWeaponEarlyShot;			// ���ł������̗L�� 
	
	CDataInt m_nDataElemNor;					// �ʏ푮���l
	CDataInt m_nDataElemLow;					// �������l
	CDataInt m_nDataElemChaos;					// �������l

	CDataInt m_aDataElemRank[ELEM_TYPE_MAX];	// ���������N

private:

	void SetElemRank(void);
	void Debug(void);

	SUB_WEAPON_TYPE m_subWeaponType;
	ELEM_TYPE m_elemType;
};

#endif	// ��d�C���N���[�h�h�~�̏I��

