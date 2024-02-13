
//-===============================================
//-
//-	�I�u�W�F�N�g����[object.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "object.h"

#include "manager.h"
#include "debugproc.h"

#include "Input.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

int CObject::m_nNumAll = 0;
bool CObject::m_bIsUpdateAllStop = false;

CObject* CObject::m_apTop[OBJECT_PRIORITY_MAX] = {};
CObject* CObject::m_apCur[OBJECT_PRIORITY_MAX] = {};

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CObject::CObject(int nPriority)
{
	CObject* pObject = m_apTop[nPriority];

	if (pObject != nullptr)
	{
		while (pObject != nullptr)
		{
			CObject* pObjectNext = pObject->m_pNext;

			if (pObjectNext == nullptr)
			{
				// �Ō���|�C���^���X�V
				pObject->m_pNext = this;
				pObject->m_pNext->m_pNext = nullptr;
				pObject->m_pNext->m_pPrev = pObject;
				m_apCur[nPriority] = this;

				m_nNumAll++;

				break;
			}
			else
			{
				pObject = pObjectNext;
			}
		}
	}
	else
	{
		m_apTop[nPriority] = this;

		m_pPrev = nullptr;		// �O�̃I�u�W�F�N�g�ւ̃|�C���^
		m_pNext = nullptr;		// ���̃I�u�W�F�N�g�ւ̃|�C���^

		m_nNumAll++;
	}

	m_nPriority = nPriority;	// ���g�̗D�揇�ʂ�ۑ�
	m_bIsUpdateStop = false;	// �X�V�̗L��
	m_bIsUpdatePause = false;	// �|�[�Y�̍X�V�̗L��
	m_bIsDrawStop = false;		// �`��̗L��
	m_bIsDeath = false;			// ���S�̗L��
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CObject::~CObject()
{
}

//-------------------------------------
//-	�S�J������
//-------------------------------------
void CObject::ReleaseAll(void)
{
	for (int nCount = 0; nCount < OBJECT_PRIORITY_MAX; nCount++)
	{
		// �擪�̃I�u�W�F�N�g�|�C���^����
		CObject* pObject = m_apTop[nCount];

		while (pObject != nullptr)
		{
			CObject* pObjectNext = pObject->m_pNext;

			// �I�u�W�F�N�g�̍X�V����
			pObject->Uninit();

			// ���̃I�u�W�F�N�g����
			pObject = pObjectNext;
		}
	}

	// �S���S�t���O�m�F�J������
	DeathAllCheckRelease();
}

//-------------------------------------
//-	�S�X�V����
//-------------------------------------
void CObject::UpdateAll(void)
{
	for (int nCount = 0; nCount < OBJECT_PRIORITY_MAX; nCount++)
	{
		// �擪�̃I�u�W�F�N�g�|�C���^����
		CObject* pObject = m_apTop[nCount];

		while (pObject != nullptr)
		{
			CObject* pObjectNext = pObject->m_pNext;

			if (pObject->CheckFlagUpdate())
			{
				// �I�u�W�F�N�g�̍X�V����
				pObject->Update();
			}

			// ���̃I�u�W�F�N�g����
			pObject = pObjectNext;
		}
	}

	// �S���S�t���O�m�F�J������
	DeathAllCheckRelease();

	// �f�o�b�N�\��
	Debug();
}

//-------------------------------------
//-	�S�`�揈��
//-------------------------------------
void CObject::DrawAll(void)
{
	for (int nCount = 0; nCount < OBJECT_PRIORITY_MAX; nCount++)
	{
		// �擪�̃I�u�W�F�N�g�|�C���^����
		CObject* pObject = m_apTop[nCount];

		while (pObject != nullptr)
		{
			CObject* pObjectNext = pObject->m_pNext;

			if (pObject->m_bIsDrawStop == false)
			{
				// �I�u�W�F�N�g�̍X�V����
				pObject->Draw();
			}

			// ���̃I�u�W�F�N�g����
			pObject = pObjectNext;
		}
	}
}

CObject* CObject::GetTop(int nPriority)
{
	return nullptr;
}

CObject* CObject::GetNext(void)
{
	return nullptr;
}

//-------------------------------------
//-	�J���ݒ菈��
//-------------------------------------
void CObject::Release(void)
{
	m_bIsDeath = true;
}

//-------------------------------------
//- �X�V�t���O�m�F����
//-------------------------------------
bool CObject::CheckFlagUpdate(void)
{
	if (m_bIsUpdateStop ||
		m_bIsUpdateAllStop && m_bIsUpdatePause == false)
	{
		return false;
	}

	return true;
}

//-------------------------------------
//-	�I�u�W�F�N�g�̊J������
//-------------------------------------
void CObject::ReleaseObj(void)
{
	// ���g���擪�̃I�u�W�F�N�g
	if (m_apTop[m_nPriority] == this)
	{
		// ���̃I�u�W�F�N�g�|�C���^��擪�ɐݒ�
		m_apTop[m_nPriority] = m_pNext;

		if (m_pNext != nullptr)
		{
			m_pNext->m_pPrev = nullptr;
		}
	}
	// ���g���Ō���̃I�u�W�F�N�g
	else if (m_apCur[m_nPriority] == this)
	{
		// �O�̃I�u�W�F�N�g�|�C���^���Ō���ɐݒ�
		m_apCur[m_nPriority] = m_pPrev;

		if (m_pPrev != nullptr)
		{
			m_pPrev->m_pNext = nullptr;
		}
	}
	else
	{
		m_pPrev->m_pNext = m_pNext;
		m_pNext->m_pPrev = m_pPrev;
	}

	m_nNumAll--;

	delete this;

}

//-------------------------------------
//-	�I�u�W�F�N�g�̑S���S�t���O�m�F�J������
//-------------------------------------
void CObject::DeathAllCheckRelease(void)
{
	for (int nCount = 0; nCount < OBJECT_PRIORITY_MAX; nCount++)
	{
		// �擪�̃I�u�W�F�N�g�|�C���^����
		CObject* pObject = m_apTop[nCount];

		while (pObject != nullptr)
		{
			CObject* pObjectNext = pObject->m_pNext;

			// ���S�̗L��
			if (pObject->m_bIsDeath)
			{
				pObject->ReleaseObj();
			}

			// ���̃I�u�W�F�N�g����
			pObject = pObjectNext;
		}
	}
}

//-------------------------------------
//- �v���C���[�̃f�o�b�N�\��
//-------------------------------------
void CObject::Debug(void)
{
	// �f�o�b�N�v���b�N�̎擾
	CDebugProc *pDebugProc = CManager::GetInstance()->GetDbugProc();

	// �f�o�b�N�v���b�N�擾�̗L���𔻒�
	if (pDebugProc == NULL)
	{
		return;
	}

	pDebugProc->Print("\n");
	pDebugProc->Print("�I�u�W�F�N�g����\n");
	pDebugProc->Print("%d", m_nNumAll);
	pDebugProc->Print("\n");
}