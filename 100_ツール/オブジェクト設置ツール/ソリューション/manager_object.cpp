
//-===============================================
//-
//-	�I�u�W�F�N�g�Ǘ�����[manager.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "manager_object.h"

#include "object2d.h"

#include "object3d.h"
#include "field.h"

#include "object_billboard.h"

#include "object_x.h"

#include "objectx_none.h"
#include "event_object.h"
#include "garbage.h"
#include "garbage_collect.h"
#include "item.h"
#include "enemy_normal.h"

#include "objectx_test.h"

#include "file_obj_none.h"
#include "file_evt_obj.h"
#include "file_garbage.h"
#include "file_garbage_collect.h"
#include "file_emy_nor.h"
#include "file_enemy_pin.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

CField *CManagerObject::m_pField[FIELD_NUM_MAX] = {};
CObjectXNone *CManagerObject::m_apObjectXNone[OBJECTX_NONE_NUM_MAX] = {};
CEventObject *CManagerObject::m_apEventObject[EVENT_OBJECT_NUM_MAX] = {};
CGarbage *CManagerObject::m_apGarbage[GARBAGE_NUM_MAX] = {};
CGarbageCollect *CManagerObject::m_apGarbageCollect[GARBAGE_COLLECT_NUM_MAX] = {};
CItem *CManagerObject::m_apItem[ITEM_NUM_MAX] = {};
CEnemyNormal *CManagerObject::m_apEnemyNormal[ENEMY_NORMAL_NUM_MAX] = {};
CEnemyPin *CManagerObject::m_apEnemyPin[ENEMY_PIN_NUM_MAX] = {};

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CManagerObject::CManagerObject()
{
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CManagerObject::~CManagerObject()
{

}

//-------------------------------------
//- �I�u�W�F�N�g�Ǘ��̏���������
//-------------------------------------
HRESULT CManagerObject::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �S��������
	if (FAILED(CreateAll(hWnd)))
	{
		// �����������𔲂���
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �I�u�W�F�N�g�Ǘ��̏I������
//-------------------------------------
void CManagerObject::Uninit(void)
{

}

//-------------------------------------
//- �I�u�W�F�N�g�Ǘ��̍X�V����
//-------------------------------------
void CManagerObject::Update(void)
{

}

//-------------------------------------
//- �I�u�W�F�N�g�Ǘ��̕`�揈��
//-------------------------------------
void CManagerObject::Draw(void)
{

}


//-------------------------------------
//-	�t�B�[���h�̏����擾
//-------------------------------------
CField *CManagerObject::GetField(void)
{
	// �t�B�[���h�̃|�C���^��Ԃ�
	return NULL;
}

//-------------------------------------
//-	���ʂȂ��I�u�W�F�N�g�̏����擾
//-------------------------------------
CObjectXNone * CManagerObject::GetObjectNone(int nNum)
{
	// �w��̌��ʂȂ��I�u�W�F�N�g�̃|�C���^��Ԃ�
	return m_apObjectXNone[nNum];
}

//-------------------------------------
//-	���ʂȂ��I�u�W�F�N�g�̐ݒ菈��
//-------------------------------------
void CManagerObject::SetObjectNone(int nNum, CObjectXNone * pObjectXNone)
{
	// ���ʂȂ��I�u�W�F�N�g�̃|�C���^����
	m_apObjectXNone[nNum] = pObjectXNone;
}

//-------------------------------------
//-	�C�x���g�I�u�W�F�N�g�̏����擾
//-------------------------------------
CEventObject * CManagerObject::GetEventObject(int nNum)
{
	// �C�x���g�I�u�W�F�N�g��Ԃ�
	return m_apEventObject[nNum];
}

//-------------------------------------
//-	�C�x���g�I�u�W�F�N�g�̐ݒ菈��
//-------------------------------------
void CManagerObject::SetEventObject(int nNum, CEventObject * pEventObject)
{
	// ���ʂȂ��I�u�W�F�N�g�̃|�C���^����
	m_apEventObject[nNum] = pEventObject;
}

//-------------------------------------
//-	�C�x���g�I�u�W�F�N�g�̐ݒ菈��
//-------------------------------------
void CManagerObject::SetGarbage(int nNum, CGarbage * pGarbage)
{
	// ���ʂȂ��I�u�W�F�N�g�̃|�C���^����
	m_apGarbage[nNum] = pGarbage;
}

//-------------------------------------
//-	�C�x���g�I�u�W�F�N�g�̏����擾
//-------------------------------------
CGarbage *CManagerObject::GetGarbage(int nNum)
{
	// �C�x���g�I�u�W�F�N�g��Ԃ�
	return m_apGarbage[nNum];
}

//-------------------------------------
//-	�S�~���W�̏����擾
//-------------------------------------
CGarbageCollect *CManagerObject::GetGarbageCollect(int nNum)
{
	//�S�~���W��Ԃ�
	return m_apGarbageCollect[nNum];
}

//-------------------------------------
//-	�S�~���W�̐ݒ菈��
//-------------------------------------
void CManagerObject::SetGarbageCollect(int nNum, CGarbageCollect *pGarbageCollect)
{
	// �S�~���W�̃|�C���^����
	m_apGarbageCollect[nNum] = pGarbageCollect;
}

//-------------------------------------
//-	�S�~���W�̏����J������
//-------------------------------------
void CManagerObject::ReleaseGarbageCollect(int nNum)
{
	// �S�~���W�̃|�C���^��������
	m_apGarbageCollect[nNum] = NULL;
}

//-------------------------------------
//-	�A�C�e���̏����擾
//-------------------------------------
CItem * CManagerObject::GetItem(int nNum)
{
	// �A�C�e���̏���Ԃ�
	return m_apItem[nNum];
}

//-------------------------------------
//-	�A�C�e���̐ݒ菈��
//-------------------------------------
void CManagerObject::SetItem(int nNum, CItem * pItem)
{
	// �A�C�e���̏����|�C���^����
	m_apItem[nNum] = pItem;
}

//-------------------------------------
//-	�ʏ�G�̏����擾
//-------------------------------------
CEnemyNormal * CManagerObject::GetEnemyNormal(int nNum)
{
	// �ʏ�G�̏���Ԃ�
	return m_apEnemyNormal[nNum];
}

//-------------------------------------
//-	�ʏ�G�̐ݒ菈��
//-------------------------------------
void CManagerObject::SetEnemyNormal(int nNum, CEnemyNormal * pEnemyNormal)
{
	// �ʏ�G�̏����|�C���^����
	m_apEnemyNormal[nNum] = pEnemyNormal;
}

//-------------------------------------
//-	�G�l�~�[�s���̏����擾
//-------------------------------------
CEnemyPin *CManagerObject::GetEnemyPin(int nNum)
{
	// �ʏ�G�̏���Ԃ�
	return m_apEnemyPin[nNum];
}

//-------------------------------------
//-	�G�l�~�[�s���̐ݒ菈��
//-------------------------------------
void CManagerObject::SetEnemyPin(int nNum, CEnemyPin * pEnemyPin)
{
	// �ʏ�G�̏����|�C���^����
	m_apEnemyPin[nNum] = pEnemyPin;
}

//-------------------------------------
//- �I�u�W�F�N�g�Ǘ��̑S��������
//-------------------------------------
HRESULT CManagerObject::CreateAll(HWND hWnd)
{
	////�t�B�[���h
	//for (int nColumn = 0; nColumn < 4; nColumn++)
	//{
	//	for (int nRow = 0; nRow < 4; nRow++)
	//	{
	//		if (m_pField[nColumn + (nRow * 4)] == NULL)
	//		{
	//			// �t�B�[���h�̐���
	//			m_pField[nColumn + (nRow * 4)] = CField::Create(CField::TEX_WHITE_TILE_000);

	//			if (m_pField[nColumn + (nRow * 4)] == NULL)
	//			{
	//				// ���s���b�Z�[�W
	//				MessageBox(hWnd, "�t�B�[���h�̐���", "�����������s�I", MB_ICONWARNING);

	//				// ���������𔲂���
	//				return E_FAIL;
	//			}

	//			m_pField[nColumn + (nRow * 4)]->Set(
	//				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	//				D3DXVECTOR3(-2000.0f + (2000.0f * nColumn), 0.0f, -2000.0f + (2000.0f * nRow)),
	//				D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//		}
	//	}
	//}

	int nCount = 0;

	for (int nCut = 0; nCut < 4; nCut++)
	{
		nCount++;

		// �t�B�[���h�̐���
		m_pField[nCount] = CField::Create(CField::TEX_ROAD_000);

		if (m_pField[nCount] == NULL)
		{
			// ���s���b�Z�[�W
			MessageBox(hWnd, "�t�B�[���h�̐���", "�����������s�I", MB_ICONWARNING);

			// ���������𔲂���
			return E_FAIL;
		}

		m_pField[nCount]->Set(
			D3DXVECTOR3(-6000.0f + (nCut * 4000.0f), 0.0f, 0.0f),
			D3DXVECTOR3(250.0f, 0.0f, 6250.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	for (int nCut = 0; nCut < 4; nCut++)
	{
		nCount++;

		// �t�B�[���h�̐���
		m_pField[nCount] = CField::Create(CField::TEX_ROAD_000);

		if (m_pField[nCount] == NULL)
		{
			// ���s���b�Z�[�W
			MessageBox(hWnd, "�t�B�[���h�̐���", "�����������s�I", MB_ICONWARNING);

			// ���������𔲂���
			return E_FAIL;
		}

		m_pField[nCount]->Set(
			D3DXVECTOR3(0.0f, 0.0f, -6000.0f + ((nCut) * 4000.0f)),
			D3DXVECTOR3(250.0f, 0.0f, 6250.0f),
			D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	}

	for (int nCut1 = 0; nCut1 < 3; nCut1++)
	{
		for (int nCut2 = 0; nCut2 < 3; nCut2++)
		{
			nCount++;

			// �t�B�[���h�̐���
			m_pField[nCount] = CField::Create(CField::TEX_ASPHALT_000);

			if (m_pField[nCount] == NULL)
			{
				// ���s���b�Z�[�W
				MessageBox(hWnd, "�t�B�[���h�̐���", "�����������s�I", MB_ICONWARNING);

				// ���������𔲂���
				return E_FAIL;
			}

			m_pField[nCount]->Set(
				D3DXVECTOR3(4000.0f - (4000.0f * nCut1), 0.0f, 4000.0f - (4000.0f * nCut2)),
				D3DXVECTOR3(1750.0f, 0.0f, 1750.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}


	// �e�X�g�̐���
	CObjectXTest *m_pObjectTest = CObjectXTest::Create(CObjectXTest::MODEL_HUMAN_BOX_000);

	// ���ʂȂ��I�u�W�F�N�g�ǂݍ��ݐݒ菈��
	CFileObjNone::Load(CFileObjNone::TXT_NORMAL_000);

	// �C�x���g�I�u�W�F�N�g�ǂݍ��ݐݒ菈��
	CFileEvtObj::Load(CFileEvtObj::TXT_NORMAL_000);

	// �S�~�I�u�W�F�N�g�ǂݍ��ݐݒ菈��
	CFileGarbage::Load(CFileGarbage::TXT_NORMAL_000);

	// �S�~����I�u�W�F�N�g�ǂݍ��ݐݒ菈��
	CFileGarbageCollect::Load(CFileGarbageCollect::TXT_NORMAL_000);

	// �G�̓ǂݍ��ݐݒ菈��
	CFileEmyNor::Load(CFileEmyNor::TXT_NORMAL_000);

	// �G�l�~�[�s���̓ǂݍ��ݐݒ菈��
	CFileEnemyPin::Load(CFileEnemyPin::TXT_ENEMY_PIN_000);

	// ������Ԃ�
	return S_OK;
}