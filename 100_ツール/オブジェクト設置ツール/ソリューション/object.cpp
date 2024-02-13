
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

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

CObject *CObject::m_apObject[OBJECT_PRIORITY_MAX][OBJECT_NUM_MAX] = { NULL };
int CObject::m_nNumAll = 0;

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CObject::CObject(int nPriority)
{
	// �|�C���^��ݒ�
	for (int nCountObj = 0; nCountObj < OBJECT_NUM_MAX; nCountObj++)
	{
		if (m_apObject[nPriority][nCountObj] == NULL)
		{
			// �����̃|�C���^����
			m_apObject[nPriority][nCountObj] = this;

			// �����̃A�h���X�ԍ���ݒ�
			m_nID = nCountObj;

			// �����̗D�揇�ʂ�ݒ�
			m_nPriority = nPriority;

			// �I�u�W�F�N�g�̑��������Z
			m_nNumAll++;

			break;
		}
	}
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
	// �S�I�u�W�F�N�g�|�C���^���J��
	for (int nCountPrio = 0; nCountPrio < OBJECT_PRIORITY_MAX; nCountPrio++)
	{
		for (int nCountObj = 0; nCountObj < OBJECT_NUM_MAX; nCountObj++)
		{
			if (m_apObject[nCountPrio][nCountObj] != NULL)
			{
				// �I������
				m_apObject[nCountPrio][nCountObj]->Uninit();
			}
		}
	}
}

//-------------------------------------
//-	�S�X�V����
//-------------------------------------
void CObject::UpdateAll(void)
{
	// �S�I�u�W�F�N�g�|�C���^�̏����X�V
	for (int nCountPrio = 0; nCountPrio < OBJECT_PRIORITY_MAX; nCountPrio++)
	{
		for (int nCountObj = 0; nCountObj < OBJECT_NUM_MAX; nCountObj++)
		{
			if (m_apObject[nCountPrio][nCountObj] != NULL)
			{
				// �X�V����
				m_apObject[nCountPrio][nCountObj]->Update();
			}
		}
	}
}

//-------------------------------------
//-	�S�`�揈��
//-------------------------------------
void CObject::DrawAll(void)
{
	// �S�I�u�W�F�N�g�|�C���^�̏���`��
	for (int nCountPrio = 0; nCountPrio < OBJECT_PRIORITY_MAX; nCountPrio++)
	{
		for (int nCountObj = 0; nCountObj < OBJECT_NUM_MAX; nCountObj++)
		{
			if (m_apObject[nCountPrio][nCountObj] != NULL)
			{
				// �`�揈��
				m_apObject[nCountPrio][nCountObj]->Draw();
			}
		}
	}
}

//-------------------------------------
//-	�I�u�W�F�N�g�̎擾����
//-------------------------------------
CObject * CObject::GetObject(int nPriority, int nldx)
{
	// ��ނ�Ԃ�
	return m_apObject[nPriority][nldx];
}

//-------------------------------------
//-	2D�I�u�W�F�N�g�̎擾����
//-------------------------------------
CObject2d *CObject::GetObject2d(void)
{
	// �Ȃ���Ԃ�
	return NULL;
}

//-------------------------------------
//-	���d�w�i�̎擾����
//-------------------------------------
CBgMulti *CObject::GetBgMulti(void)
{
	// �Ȃ���Ԃ�
	return NULL;
}

//-------------------------------------
//-	�J������
//-------------------------------------
void CObject::Release(void)
{
	// ID����
	int nID = m_nID;
	int nPrio = m_nPriority;

	// �I�u�W�F�N�g�̔j��
	if (m_apObject[m_nID] != NULL)
	{
		// �I�u�W�F�N�g�̊J��
		delete m_apObject[nPrio][nID];
		m_apObject[nPrio][nID] = NULL;

		// �I�u�W�F�N�g�̑��������Z
		m_nNumAll--;
	}
}