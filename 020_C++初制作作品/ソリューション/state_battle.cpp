
//-===============================================
//-
//-	�퓬�X�e�[�^�X����[state_battle.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "state_battle.h"

#include "renderer.h"
#include "manager.h"

#include "debugproc.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	�퓬�X�e�[�^�X�̃R���X�g���N�^
//-------------------------------------
CStateBattle::CStateBattle()
{
	// �l���N���A
	m_subWeaponType = SUB_WEAPON_TYPE_BOMB;
	m_elemType = ELEM_TYPE_NORMAL;
}

//-------------------------------------
//-	�퓬�X�e�[�^�X�̃f�X�g���N�^
//-------------------------------------
CStateBattle::~CStateBattle()
{

}

//-------------------------------------
//- �퓬�X�e�[�^�X�̏���������
//-------------------------------------
void CStateBattle::Init(void)
{
	// ���̏����l�ݒ�
	m_bDataWeaponEarlyShot.Set(false);	// ���ł������̗L��
	m_nDataShotInterval.Set(60);		// �e�̊Ԋu

	m_elemType = ELEM_TYPE_NORMAL;
}

//-------------------------------------
//- �퓬�X�e�[�^�X�̏I������
//-------------------------------------
void CStateBattle::Uninit(void)
{

}

//-------------------------------------
//- �퓬�X�e�[�^�X�̍X�V����
//-------------------------------------
void CStateBattle::Update(void)
{
	// �f�o�b�N�\��
	Debug();
}

//-------------------------------------
//- �퓬�X�e�[�^�X�̐�������
//-------------------------------------
CStateBattle *CStateBattle::Create(void)
{
	// �A�C�e���̃|�C���^��錾
	CStateBattle *pCStateBattle = DBG_NEW CStateBattle;

	// �����̐����̗L���𔻒�
	if (pCStateBattle != NULL)
	{
		// ����������
		pCStateBattle->Init();
	}
	else if (pCStateBattle == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �A�C�e���̃|�C���^��Ԃ�
	return pCStateBattle;
}

//-------------------------------------
//- �퓬�X�e�[�^�X�̓������̐ݒ�
//-------------------------------------
void CStateBattle::SetWeaponCopper(bool bUse)
{
	// �����̗L��
	if (bUse == true)
	{
		m_bDataWeaponEarlyShot.Set(true);	// ���ł�������ݒ�
		m_nDataShotInterval.Set(50);		// �e�̊Ԋu
	}
	else if (bUse == false)
	{
		m_bDataWeaponEarlyShot.Set(false);	// ���ł������̐ݒ���O��
		m_nDataShotInterval.Set(60);		// �e�̊Ԋu
	}
}

//-------------------------------------
//- �퓬�X�e�[�^�X�̋⑕���̐ݒ�
//-------------------------------------
void CStateBattle::SetWeaponSilver(bool bUse)
{
	// �����̗L��
	if (bUse == true)
	{
		m_bDataWeaponEarlyShot.Set(true);	// ���ł�������ݒ�
		m_nDataShotInterval.Set(40);		// �e�̊Ԋu
	}
	else if (bUse == false)
	{
		m_bDataWeaponEarlyShot.Set(false);	// ���ł������̐ݒ���O��
		m_nDataShotInterval.Set(60);		// �e�̊Ԋu
	}
}

//-------------------------------------
//- �퓬�X�e�[�^�X�̋������̐ݒ�
//-------------------------------------
void CStateBattle::SetWeaponGold(bool bUse)
{
	// �����̗L��
	if (bUse == true)
	{
		m_bDataWeaponEarlyShot.Set(true);	// ���ł�������ݒ�
		m_nDataShotInterval.Set(20);		// �e�̊Ԋu
	}
	else if (bUse == false)
	{
		m_bDataWeaponEarlyShot.Set(false);	// ���ł������̐ݒ���O��
		m_nDataShotInterval.Set(60);		// �e�̊Ԋu
	}
}

//-------------------------------------
//- �퓬�X�e�[�^�X�̃T�u����̐ݒ�
//-------------------------------------
void CStateBattle::SetSubWeaponBomb(bool bUse)
{
	// �ϐ��錾�i���擾�j
	int nSubWeaponNum = m_nSubWeaponNum.Get();	// �T�u����̉�

	// �����̗L��
	if (bUse == true)
	{
		// �T�u����̉񐔂����Z
		nSubWeaponNum++;
	}
	else if (bUse == false)
	{
		// �T�u����̉񐔂����Z
		nSubWeaponNum--;
	}

	// ���X�V
	m_nSubWeaponNum.Set(nSubWeaponNum);	// �T�u����̉�
}

//-------------------------------------
//- �퓬�X�e�[�^�X�̑������Z����
//-------------------------------------
void CStateBattle::AddElem(int nNor, int nLow, int nChaos)
{
	// �ϐ��錾�i���擾�j
	int nElemNor = m_nDataElemNor.Get();		// �ʏ푮��
	int nElemLow = m_nDataElemLow.Get();		// ������
	int nElemChaos = m_nDataElemChaos.Get();	// ������

	nElemNor += nNor;		// �ʏ푮�������Z
	nElemLow += nLow;		// �����������Z
	nElemChaos += nChaos;	// �����������Z

	if (nElemNor < 0)
	{
		// �ʏ푮���̒l��������
		nElemNor = 0;
	}

	if (nElemLow < 0)
	{
		// �������̒l��������
		nElemLow = 0;
	}

	if (nElemChaos < 0)
	{
		// �������̒l��������
		nElemChaos = 0;
	}

	// ������ސݒ菈��
	if (nElemNor > nElemLow &&
		nElemNor > nElemChaos)
	{
		// �ʏ푮���ɐݒ�
		m_elemType = ELEM_TYPE_NORMAL;
	}
	else if(
		nElemLow > nElemNor &&
		nElemLow > nElemChaos)
	{
		// �������ɐݒ�
		m_elemType = ELEM_TYPE_LOW;
	}
	else if (
		nElemChaos > nElemNor &&
		nElemChaos > nElemLow)
	{
		// �������ɐݒ�
		m_elemType = ELEM_TYPE_CHAOS;
	}
	else
	{
		// �ʏ푮���ɐݒ�
		m_elemType = ELEM_TYPE_NORMAL;
	}

	// ���X�V
	m_nDataElemNor.Set(nElemNor);		// �ʏ푮��
	m_nDataElemLow.Set(nElemLow);		// ������
	m_nDataElemChaos.Set(nElemChaos);	// ������

	// �����N�ݒ菈��
	SetElemRank();
}

//-------------------------------------
//- �퓬�X�e�[�^�X�̃T�u����̎�ގ擾����
//-------------------------------------
CStateBattle::SUB_WEAPON_TYPE CStateBattle::GetWeaponType(void)
{
	// �T�u����̎�ނ�Ԃ�
	return m_subWeaponType;
}

//-------------------------------------
//- �퓬�X�e�[�^�X�̑����̎擾����
//-------------------------------------
CStateBattle::ELEM_TYPE CStateBattle::GetElemType(void)
{
	return m_elemType;
}

//-------------------------------------
//- �퓬�X�e�[�^�X�̑��������N�ݒ菈��
//-------------------------------------
void CStateBattle::SetElemRank(void)
{
	int aElem[ELEM_TYPE_MAX] = {};

	aElem[ELEM_TYPE_NORMAL] = m_nDataElemNor.Get();
	aElem[ELEM_TYPE_LOW] = m_nDataElemLow.Get();
	aElem[ELEM_TYPE_CHAOS] = m_nDataElemChaos.Get();

	for (int nCutElem = 0; nCutElem < ELEM_TYPE_MAX; nCutElem++)
	{
		if (aElem[nCutElem] >= 30)
		{
			m_aDataElemRank[nCutElem].Set(3);
		}
		else if (aElem[nCutElem] >= 15)
		{
			m_aDataElemRank[nCutElem].Set(2);
		}
		else if (aElem[nCutElem] >= 5)
		{
			m_aDataElemRank[nCutElem].Set(1);
		}
	}
}

//-------------------------------------
//- �퓬�X�e�[�^�X�̃f�o�b�N�\��
//-------------------------------------
void CStateBattle::Debug(void)
{
	// �f�o�b�N�v���b�N�̎擾
	CDebugProc *pDebugProc = CManager::GetDbugProc();

	// �f�o�b�N�v���b�N�擾�̗L���𔻒�
	if (pDebugProc == NULL)
	{
		return;
	}

	pDebugProc->Print("\n");
	pDebugProc->Print("�����X�e�[�^�X\n");
	pDebugProc->Print("NOR:%d \n", m_nDataElemNor.Get());
	pDebugProc->Print("LOW:%d \n", m_nDataElemLow.Get());
	pDebugProc->Print("CHAOS:%d \n", m_nDataElemChaos.Get());
	pDebugProc->Print("\n");
}