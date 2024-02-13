
//-===============================================
//-
//-	�I�u�W�F�N�g�Ǘ�����[manager_object.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "manager_object.h"

#include "object3d.h"
#include "obj_3d_field.h"
#include "obj_3d_wall.h"

#include "object_billboard.h"
#include "bullet.h"
#include "effect.h"

#include "object_x.h"
#include "objectx_none.h"
#include "item.h"
#include "enemy_normal.h"
#include "enemy_boss.h"
#include "event_object.h"
#include "garbage.h"
#include "garbage_collect.h"
#include "gate.h"

#include "skybox.h"

#include "obj_3d_wall.h"

#include "player_search.h"
#include "player_battle.h"
#include "player_shop.h"

#include "score.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

CObjectXNone *CManagerObject::m_apObjectXNone[OBJECTX_NONE_NUM_MAX] = {};
CEventObject *CManagerObject::m_apEventObject[EVENT_OBJECT_NUM_MAX] = {};
CGarbage *CManagerObject::m_apGarbage[GARBAGE_NUM_MAX] = {};
CGarbageCollect *CManagerObject::m_apGarbageCollect[GARBAGE_COLLECT_NUM_MAX] = {};

CItem *CManagerObject::m_apItem[ITEM_NUM_MAX] = {};
CEnemyNormal *CManagerObject::m_apEnemyNormal[ENEMY_NORMAL_NUM_MAX] = {};
CEnemyBoss *CManagerObject::m_pEnemyBoss = NULL;

CObj3dField *CManagerObject::m_pField[FIELD_NUM_MAX] = {};
CObj3dWall *CManagerObject::m_pWall[WALL_NUM_MAX] = {};

CGate *CManagerObject::m_pGate = NULL;
CSkybox *CManagerObject::m_pSkybox = NULL;

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
	for (int nCount = 0; nCount < OBJECTX_NONE_NUM_MAX; nCount++)
	{
		if (m_apObjectXNone[nCount] != NULL)
		{
			// ���ʂȂ��I�u�W�F�N�g�̊J������
			m_apObjectXNone[nCount]->Uninit();
			m_apObjectXNone[nCount] = NULL;
		}
	}

	for (int nCount = 0; nCount < EVENT_OBJECT_NUM_MAX; nCount++)
	{
		if (m_apEventObject[nCount] != NULL)
		{
			// �C�x���g�I�u�W�F�N�g�̊J������
			m_apEventObject[nCount]->Uninit();
			m_apEventObject[nCount] = NULL;
		}
	}

	for (int nCount = 0; nCount < EVENT_OBJECT_NUM_MAX; nCount++)
	{
		if (m_apGarbage[nCount] != NULL)
		{
			// �S�~�̊J������
			m_apGarbage[nCount]->Uninit();
			m_apGarbage[nCount] = NULL;
		}
	}

	for (int nCount = 0; nCount < EVENT_OBJECT_NUM_MAX; nCount++)
	{
		if (m_apGarbageCollect[nCount] != NULL)
		{
			// �S�~���W�̊J������
			m_apGarbageCollect[nCount]->Uninit();
			m_apGarbageCollect[nCount] = NULL;
		}

	}
	for (int nCount = 0; nCount < ITEM_NUM_MAX; nCount++)
	{
		if (m_apItem[nCount] != NULL)
		{
			// �A�C�e���̊J������
			m_apItem[nCount]->Uninit();
			m_apItem[nCount] = NULL;
		}
	}

	for (int nCount = 0; nCount < ENEMY_NORMAL_NUM_MAX; nCount++)
	{
		if (m_apEnemyNormal[nCount] != NULL)
		{
			// �ʏ�G�̊J������
			m_apEnemyNormal[nCount]->Uninit();
			m_apEnemyNormal[nCount] = NULL;
		}
	}

	// �{�X�̗L���𔻒�
	if (m_pEnemyBoss != NULL)
	{
		// �{�X�G�̊J������
		m_pEnemyBoss->Uninit();
		m_pEnemyBoss = NULL;
	}

	for (int nCount = 0; nCount < FIELD_NUM_MAX; nCount++)
	{
		if (m_pField[nCount] != NULL)
		{
			// �t�B�[���h�̊J������
			m_pField[nCount]->Uninit();
			m_pField[nCount] = NULL;
		}
	}

	for (int nCount = 0; nCount < WALL_NUM_MAX; nCount++)
	{
		if (m_pWall[nCount] != NULL)
		{
			// �ǂ̊J������
			m_pWall[nCount]->Uninit();
			m_pWall[nCount] = NULL;
		}
	}

	// �Q�[�g�̗L���𔻒�
	if (m_pGate != NULL)
	{
		// �Q�[�g�̊J������
		m_pGate->Uninit();
		m_pGate = NULL;
	}

	// �X�J�C�{�b�N�X�̗L���𔻒�
	if (m_pSkybox != NULL)
	{
		// �X�J�C�{�b�N�X�̊J������
		m_pSkybox->Uninit();
		m_pSkybox = NULL;
	}
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
//-	���ʂȂ��I�u�W�F�N�g�̏����J������
//-------------------------------------
void CManagerObject::ReleaseObjectNone(int nNum)
{
	// ���ʂȂ��I�u�W�F�N�g�̃|�C���^��������
	m_apObjectXNone[nNum] = NULL;
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
	// �C�x���g�I�u�W�F�N�g�̃|�C���^����
	m_apEventObject[nNum] = pEventObject;
}

//-------------------------------------
//-	�C�x���g�I�u�W�F�N�g�̏����J������
//-------------------------------------
void CManagerObject::ReleaseEventObject(int nNum)
{
	// �C�x���g�I�u�W�F�N�g�̃|�C���^��������
	m_apEnemyNormal[nNum] = NULL;
}

//-------------------------------------
//-	�S�~�̏����擾
//-------------------------------------
CGarbage *CManagerObject::GetGarbage(int nNum)
{
	//�S�~��Ԃ�
	return m_apGarbage[nNum];
}

//-------------------------------------
//-	�S�~�̐ݒ菈��
//-------------------------------------
void CManagerObject::SetGarbage(int nNum, CGarbage *pGarbage)
{
	// �S�~�̃|�C���^����
	m_apGarbage[nNum] = pGarbage;
}

//-------------------------------------
//-	�S�~�̏����J������
//-------------------------------------
void CManagerObject::ReleaseGarbage(int nNum)
{
	// �S�~�̃|�C���^��������
	m_apGarbage[nNum] = NULL;
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
//-	�A�C�e���̏����J������
//-------------------------------------
void CManagerObject::ReleaseItem(int nNum)
{
	// �A�C�e���̃|�C���^��������
	m_apItem[nNum] = NULL;
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
//-	�ʏ�G�̏����J������
//-------------------------------------
void CManagerObject::ReleaseEnemyNormal(int nNum)
{
	// �ʏ�G�̃|�C���^��������
	m_apEnemyNormal[nNum] = NULL;
}

//-------------------------------------
//-	�{�X�G�̏����擾
//-------------------------------------
CEnemyBoss *CManagerObject::GetEnemyBoss(void)
{
	// �{�X�G�̏���Ԃ�
	return m_pEnemyBoss;
}

//-------------------------------------
//-	�{�X�G�̐ݒ菈��
//-------------------------------------
void CManagerObject::SetEnemyBoss(CEnemyBoss *pEnemyBoss)
{
	// �{�X�G�̏����|�C���^����
	m_pEnemyBoss = pEnemyBoss;
}

//-------------------------------------
//-	�{�X�G�̏����J������
//-------------------------------------
void CManagerObject::ReleaseEnemyBoss(void)
{
	// �{�X�G�̃|�C���^��������
	m_pEnemyBoss = NULL;
}

//-------------------------------------
//-	�Q�[�g�̏����擾
//-------------------------------------
CGate *CManagerObject::GetGate(void)
{
	// �Q�[�g�̏���Ԃ�
	return m_pGate;
}

//-------------------------------------
//-	�Q�[�g�̐ݒ菈��
//-------------------------------------
void CManagerObject::SetGate(CGate *pGate)
{
	// �Q�[�g�̏����|�C���^����
	m_pGate = pGate;
}

//-------------------------------------
//-	�Q�[�g�̏����J������
//-------------------------------------
void CManagerObject::ReleaseGate(void)
{
	// �Q�[�g�̃|�C���^��������
	m_pGate = NULL;
}

//-------------------------------------
//-	�X�J�C�{�b�N�X�̐ݒ菈��
//-------------------------------------
void CManagerObject::SetSkybox(CSkybox *pSkybox)
{
	// �X�J�C�{�b�N�X�̏����|�C���^����
	m_pSkybox = pSkybox;
}

//-------------------------------------
//-	�X�J�C�{�b�N�X�̏����擾
//-------------------------------------
CSkybox *CManagerObject::GetSkybox(void)
{
	// �X�J�C�{�b�N�X�̏���Ԃ�
	return m_pSkybox;
}

//-------------------------------------
//-	�X�J�C�{�b�N�X�̏����J������
//-------------------------------------
void CManagerObject::ReleaseSkybox(void)
{
	// �X�J�C�{�b�N�X�̃|�C���^��������
	m_pSkybox = NULL;
}

//-------------------------------------
//-	�ǂ̏����擾
//-------------------------------------
CObj3dWall *CManagerObject::GetWall(int nNum)
{
	// �ʏ�G�̏���Ԃ�
	return m_pWall[nNum];
}

//-------------------------------------
//-	�ǂ̐ݒ菈��
//-------------------------------------
void CManagerObject::SetWall(int nNum, CObj3dWall * pWall)
{
	// �ʏ�G�̏����|�C���^����
	m_pWall[nNum] = pWall;
}

//-------------------------------------
//- �I�u�W�F�N�g�Ǘ��̑S��������
//-------------------------------------
HRESULT CManagerObject::CreateAll(HWND hWnd)
{
	int nCount = 0;

	for (int nCut = 0; nCut < 4; nCut++)
	{
		nCount++;

		// �t�B�[���h�̐���
		m_pField[nCount] = CObj3dField::Create(CObj3dField::TEX_ROAD_000);

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
		m_pField[nCount] = CObj3dField::Create(CObj3dField::TEX_ROAD_000);

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
			m_pField[nCount] = CObj3dField::Create(CObj3dField::TEX_ASPHALT_000);

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

	int nCountWall = 0;

	for (int nCut = 0; nCut < 8; nCut++)
	{
		nCountWall++;

		// �E�H�[���̐���
		m_pWall[nCountWall] = CObj3dWall::Create(CObj3dWall::TEX_BLOCKADE_WALL_000);

		if (m_pWall[nCountWall] == NULL)
		{
			// ���s���b�Z�[�W
			MessageBox(hWnd, "�E�H�[���̐���", "�����������s�I", MB_ICONWARNING);

			// ���������𔲂���
			return E_FAIL;
		}

		m_pWall[nCountWall]->Set(
			D3DXVECTOR3(6250.0f - (6250.0f / 8) - ((6250.0f / 4) * nCut), 150.0f, 6250.0f),
			D3DXVECTOR3(6250.0f / 8, 100.0f, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	for (int nCut = 0; nCut < 8; nCut++)
	{
		nCountWall++;

		// �E�H�[���̐���
		m_pWall[nCountWall] = CObj3dWall::Create(CObj3dWall::TEX_BLOCKADE_WALL_000);

		if (m_pWall[nCountWall] == NULL)
		{
			// ���s���b�Z�[�W
			MessageBox(hWnd, "�E�H�[���̐���", "�����������s�I", MB_ICONWARNING);

			// ���������𔲂���
			return E_FAIL;
		}

		m_pWall[nCountWall]->Set(
			D3DXVECTOR3(6250.0f - (6250.0f / 8) - ((6250.0f / 4) * nCut), 150.0f, -6250.0f),
			D3DXVECTOR3(6250.0f / 8, 100.0f, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		// �F�̓�����
		m_pWall[nCountWall]->m_dataColor.Set(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	}

	for (int nCut = 0; nCut < 8; nCut++)
	{
		nCountWall++;

		// �E�H�[���̐���
		m_pWall[nCountWall] = CObj3dWall::Create(CObj3dWall::TEX_BLOCKADE_WALL_000);

		if (m_pWall[nCountWall] == NULL)
		{
			// ���s���b�Z�[�W
			MessageBox(hWnd, "�E�H�[���̐���", "�����������s�I", MB_ICONWARNING);

			// ���������𔲂���
			return E_FAIL;
		}

		m_pWall[nCountWall]->Set(
			D3DXVECTOR3(-6250.0f, 150.0f, 6250.0f - (6250.0f / 8) - ((6250.0f / 4) * nCut)),
			D3DXVECTOR3(6250.0f / 8, 100.0f, 0.0f),
			D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));

	}

	for (int nCut = 0; nCut < 8; nCut++)
	{
		nCountWall++;

		// �E�H�[���̐���
		m_pWall[nCountWall] = CObj3dWall::Create(CObj3dWall::TEX_BLOCKADE_WALL_000);

		if (m_pWall[nCountWall] == NULL)
		{
			// ���s���b�Z�[�W
			MessageBox(hWnd, "�E�H�[���̐���", "�����������s�I", MB_ICONWARNING);

			// ���������𔲂���
			return E_FAIL;
		}

		m_pWall[nCountWall]->Set(
			D3DXVECTOR3(6250.0f, 150.0f, 6250.0f - (6250.0f / 8) - ((6250.0f / 4) * nCut)),
			D3DXVECTOR3(6250.0f / 8, 100.0f, 0.0f),
			D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	}

	// �X�J�C�u���b�N�̐���
	m_pSkybox = CSkybox::Create(CSkybox::MODEL_SKYBOX_000);

	if (m_pSkybox == NULL)
	{
		// ���s���b�Z�[�W
		MessageBox(hWnd, "�X�J�C�{�b�N�X�̐���", "�����������s�I", MB_ICONWARNING);

		// ���������𔲂���
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}