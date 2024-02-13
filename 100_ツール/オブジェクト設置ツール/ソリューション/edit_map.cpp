
//-===============================================
//-
//-	�}�b�v�G�f�B�^�̏���[item.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "edit_map.h"

#include "renderer.h"
#include "manager.h"

#include "Input.h"
#include "debugproc.h"

#include "objectx_none.h"
#include "event_object.h"
#include "garbage.h"
#include "garbage_collect.h"
#include "item.h"
#include "enemy_normal.h"
#include "enemy_pin.h"

#include "file_obj_none.h"
#include "file_evt_obj.h"
#include "file_garbage.h"
#include "file_garbage_collect.h"
#include "file_item.h"
#include "file_emy_nor.h"
#include "file_enemy_pin.h"

#include "manager_object.h"
#include "camera.h"

//-======================================
//-	�}�N����`
//-======================================

#define MAP_EDIT_MOVE_SPEED	(10.0f);

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	�}�b�v�G�f�B�^�̃R���X�g���N�^
//-------------------------------------
CEditMap::CEditMap()
{
	// �l�N���A
	m_pObject = NULL;
	m_nModelNum = 0;
	m_nModelMax = 0;

	m_typeSelect = TYPE(0);
}

//-------------------------------------
//-	�}�b�v�G�f�B�^�̃f�X�g���N�^
//-------------------------------------
CEditMap::~CEditMap()
{

}

//-------------------------------------
//- �}�b�v�G�f�B�^�̏����������iX�t�@�C���I�u�W�F�N�g�ݒ�j
//-------------------------------------
HRESULT CEditMap::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �����ݒ�
	m_typeSelect = TYPE_OBJECTX_NONE;	// �I����ނ����ʂȂ��I�u�W�F�N�g�ɕύX

	// ��������
	m_pObject = CObjectXNone::Create(CObjectXNone::MODEL(0));

	// ���f���̍ő吔��ݒ�
	m_nModelMax = CObjectXNone::MODEL_MAX;

	// ���������̗L���𔻒�
	if (m_pObject == NULL)
	{// ���s��

		// �����𔲂���
		return E_FAIL;
	}

	// ���f���ݒ菈��
	SetModel();

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̏���������
//-------------------------------------
bool CEditMap::Init(void)
{
	// ���f���ԍ���������
	m_nModelNum = 0;

	switch (m_typeSelect)
	{
		// ���ʂȂ��I�u�W�F�N�g
	case TYPE_OBJECTX_NONE:

		// ��������
		m_pObject = CObjectXNone::Create(CObjectXNone::MODEL(0));

		m_pObject->m_bDataColor.Set(true);

		// ���f���̍ő吔��ݒ�
		m_nModelMax = CObjectXNone::MODEL_MAX;

		break;

		// �C�x���g�I�u�W�F�N�g
	case TYPE_EVENT_OBJECT:

		// ��������
		m_pObject = CEventObject::Create(CEventObject::MODEL(0));

		// ���f���̍ő吔��ݒ�
		m_nModelMax = CEventObject::MODEL_MAX;

		break;

		// �S�~
	case TYPE_GARBAGE:

		// ��������
		m_pObject = CGarbage::Create(CGarbage::MODEL(0));

		// ���f���̍ő吔��ݒ�
		m_nModelMax = CGarbage::MODEL_MAX;

		break;

		// �S�~���
	case TYPE_GARBAGE_COLLECT:

		// ��������
		m_pObject = CGarbageCollect::Create(CGarbageCollect::MODEL(0));

		// ���f���̍ő吔��ݒ�
		m_nModelMax = CGarbageCollect::MODEL_MAX;

		break;

		// �C�x���g�I�u�W�F�N�g
	case TYPE_ITEM:

		// ��������
		m_pObject = CItem::Create(CItem::MODEL(0));

		// ���f���̍ő吔��ݒ�
		m_nModelMax = CItem::MODEL_MAX;

		break;

		// �ʏ�G�̃I�u�W�F�N�g
	case TYPE_ENEMY_NORMAL:

		// ��������
		m_pObject = CEnemyNormal::Create(CEnemyNormal::MODEL(0));

		// ���f���̍ő吔��ݒ�
		m_nModelMax = CEnemyNormal::MODEL_MAX;

		break;

		// �G�l�~�[�s���̃I�u�W�F�N�g
	case TYPE_ENEMY_PIN:

		// ��������
		m_pObject = CEnemyPin::Create(CEnemyPin::MODEL(0));

		// ���f���̍ő吔��ݒ�
		m_nModelMax = CEnemyPin::MODEL_MAX;

		break;
	}

	// ���������̗L���𔻒�
	if (m_pObject == NULL)
	{// ���s��

		// �����𔲂���
		return true;
	}

	// ���f���ݒ菈��
	SetModel();

	// ������Ԃ�
	return false;
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̏I������
//-------------------------------------
void CEditMap::Uninit(void)
{

}

//-------------------------------------
//- �}�b�v�G�f�B�^�̍X�V����
//-------------------------------------
void CEditMap::Update(void)
{
	// �ړ�����
	Move();

	// �����ύX����
	Rot();

	// �I�u�W�F�N�g�̏��ݒ菈��
	SetObjectData();

	// ���f���̎�ސ؂�ւ�����
	ChangeModel();

	// ��ނ�؂�ւ�
	ChangeType();

	// �I�u�W�F�N�g����
	SetObject();

	// �t�@�C�������o������
	SaveFile();

	// �}�b�v�G�f�B�^���̕\��
	DrawDebug();
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̕`�揈��
//-------------------------------------
void CEditMap::Draw(void)
{

}

//-------------------------------------
//- �}�b�v�G�f�B�^�̐��������iX�t�@�C���I�u�W�F�N�g�ݒ�j
//-------------------------------------
CEditMap * CEditMap::Create(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �A�C�e���̃|�C���^��錾
	CEditMap *pCEditMap = new CEditMap;

	// �����̐����̗L���𔻒�
	if (pCEditMap != NULL)
	{
		// ����������
		if (FAILED(pCEditMap->Init(hInstance, hWnd, bWindow)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCEditMap == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �A�C�e���̃|�C���^��Ԃ�
	return pCEditMap;
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̈ړ�����
//-------------------------------------
void CEditMap::Move(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

		// �ړ������𔲂���
		return;
	}

	// �J�����̏����擾
	CCamera *pCamera = CManager::GetCamera();

	// �J�����擾�̗L���𔻒�
	if (pCamera == NULL)
	{
		// �����𔲂���
		return;
	}

	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();		// �ʒu
	D3DXVECTOR3 move = m_dataMove.Get();	// �ړ���

	// �ϐ��錾�i�J�����̏��擾�j
	D3DXVECTOR3 rotCamera = pCamera->m_dataRot.Get();	// �J�����̌���

	// �L�[�{�[�h�̓��͔��� if�iW�L�[�̓��́j
	if (pInputKeyboard->GetPress(DIK_W) == true)
	{
		// �L�[�{�[�h�̓��͔��� if�iA�L�[�̓��́j
		if (pInputKeyboard->GetPress(DIK_A) == true)
		{
			// ����ړ�
			move.x -= sinf((D3DX_PI * 0.75f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
			move.z -= cosf((D3DX_PI * 0.75f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
		}
		// �L�[�{�[�h�̓��͔��� if�iA�L�[�̓��́j
		else if (pInputKeyboard->GetPress(DIK_D) == true)
		{
			// �E��ړ�
			move.x += sinf((D3DX_PI * 0.25f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
			move.z += cosf((D3DX_PI * 0.25f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
		}
		// W�L�[�ȊO�̓��͂Ȃ�
		else
		{
			// ��ړ�
			move.x += sinf((D3DX_PI * 0.0f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
			move.z += cosf((D3DX_PI * 0.0f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
		}
	}
	// �L�[�{�[�h�̓��͔��� if�iS�L�[�̓��́j
	else if (pInputKeyboard->GetPress(DIK_S) == true)
	{
		// �L�[�{�[�h�̓��͔��� if�iA�L�[�̓��́j
		if (pInputKeyboard->GetPress(DIK_A) == true)
		{
			// �����ړ�
			move.x -= sinf((D3DX_PI * 0.25f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
			move.z -= cosf((D3DX_PI * 0.25f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
		}
		// �L�[�{�[�h�̓��͔��� if�iD�L�[�̓��́j
		else if (pInputKeyboard->GetPress(DIK_D) == true)
		{
			// �E���ړ�
			move.x += sinf((D3DX_PI * 0.75f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
			move.z += cosf((D3DX_PI * 0.75f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
		}
		// S�L�[�ȊO�̓��͂Ȃ�
		else
		{
			// ���ړ�
			move.x += sinf((D3DX_PI * 1.0f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
			move.z += cosf((D3DX_PI * 1.0f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
		}
	}
	// �L�[�{�[�h�̓��͔��� if�iA�L�[�̓��́j
	else if (pInputKeyboard->GetPress(DIK_A) == true)
	{
		// ���ړ�
		move.x -= sinf((D3DX_PI * 0.5f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
		move.z -= cosf((D3DX_PI * 0.5f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
	}
	// �L�[�{�[�h�̓��͔��� if�iD�L�[�̓��́j
	else if (pInputKeyboard->GetPress(DIK_D) == true)
	{
		// �E�ړ�
		move.x += sinf((D3DX_PI * 0.5f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
		move.z += cosf((D3DX_PI * 0.5f) + rotCamera.y) * MAP_EDIT_MOVE_SPEED;
	}

	if (pInputKeyboard->GetPress(DIK_LSHIFT) == true)
	{
		// �L�[�{�[�h�̓��͔��� if�iA�L�[�̓��́j
		if (pInputKeyboard->GetTrigger(DIK_R) == true)
		{
			// ���ړ�
			move.y += 100.0f;
		}
		// �L�[�{�[�h�̓��͔��� if�iD�L�[�̓��́j
		else if (pInputKeyboard->GetTrigger(DIK_F) == true)
		{
			// �E�ړ�
			move.y -= 100.0f;
		}
	}

	// �ړ��ʂ̌���
	if (pInputKeyboard->GetPress(DIK_LSHIFT) == true)
	{
		move *= 0.1f;
	}

	// �ʒu���Ɉړ��ʂ����Z
	pos += move;

	// �ړ��ʂ�����
	move.x += (0.0f - move.x) * 0.7f;
	move.y += (0.0f - move.y) * 0.7f;
	move.z += (0.0f - move.z) * 0.7f;

	// ���X�V
	m_dataPos.Set(pos);		// �ʒu
	m_dataMove.Set(move);	// �ړ���
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̌����ύX����
//-------------------------------------
void CEditMap::Rot(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

		// �ړ������𔲂���
		return;
	}

	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 rot = m_dataRot.Get();		// ����

	// �L�[�{�[�h�̓��͔��� if�iR�L�[�̓��́j
	if (pInputKeyboard->GetTrigger(DIK_T) == true)
	{
		// 36�x���������Z
		rot.y += D3DX_PI * 0.1f;
	}
	// �L�[�{�[�h�̓��͔��� if�iF�L�[�̓��́j
	else if (pInputKeyboard->GetTrigger(DIK_G) == true)
	{
		// 36�x���������Z
		rot.y -= D3DX_PI * 0.1f;
	}

	//�p�x�̏C��
	if (rot.y > D3DX_PI)
	{
		rot.y = (-D3DX_PI);
	}
	else if (rot.y < -D3DX_PI)
	{
		rot.y = (D3DX_PI);
	}

	// ���X�V
	m_dataRot.Set(rot);		// ����
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̈ʒu��������
//-------------------------------------
void CEditMap::SetObjectData(void)
{
	// ���ʂȂ��I�u�W�F�N�g�̈ʒu����
	m_pObject->m_dataPos.Set(m_dataPos.Get());
	m_pObject->m_dataRot.Set(m_dataRot.Get());
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̃��f���؂�ւ�����
//-------------------------------------
void CEditMap::ChangeModel(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

		// �ړ������𔲂���
		return;
	}

	if (pInputKeyboard->GetTrigger(DIK_TAB) == true &&
		pInputKeyboard->GetPress(DIK_LSHIFT) == true)
	{
		// ���f���ԍ������Z
		m_nModelNum--;

		// ���f���ԍ����ő吔�Ɠ����Ƃ�
		if (m_nModelNum < 0)
		{
			// ���f���ԍ���������
			m_nModelNum = m_nModelMax - 1;
		}

		// ���f���ݒ�
		SetModel();
	}
	// ���͂̔��� if(TAB�L�[)
	else if (pInputKeyboard->GetTrigger(DIK_TAB) == true)
	{
		// ���f���ԍ������Z
		m_nModelNum++;

		// ���f���ԍ����ő吔�Ɠ����Ƃ�
		if (m_nModelNum == m_nModelMax)
		{
			// ���f���ԍ���������
			m_nModelNum = 0;
		}

		// ���f���ݒ�
		SetModel();
	}


}

//-------------------------------------
//- �}�b�v�G�f�B�^�̎�ސ؂�ւ�����
//-------------------------------------
void CEditMap::ChangeType(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

		// �ړ������𔲂���
		return;
	}

	// ���͂̔��� if(LCONTROL�L�[)
	if (pInputKeyboard->GetTrigger(DIK_LCONTROL) == true)
	{
		// ��ނ����Z
		m_typeSelect = (TYPE)(m_typeSelect + 1);

		if (m_typeSelect == TYPE_MAX)
		{
			// ��ނ�������
			m_typeSelect = (TYPE)(0);
		}

		// �I������
		m_pObject->Uninit();
		m_pObject = NULL;

		// �؂�ւ�����ނ̏��������� if(�����̗L���𔻒�)
		if (Init() == true)
		{
			return;
		}

		// �ʒu������
		SetObjectData();
	}
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̐ݒ菈��
//-------------------------------------
void CEditMap::SetObject(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

		// �ړ������𔲂���
		return;
	}

	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();		// �ʒu
	D3DXVECTOR3 rot = m_dataRot.Get();		// ����

	// ���͂̔��� if(�X�y�[�X�L�[)
	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true)
	{
		switch (m_typeSelect)
		{
			// ���ʂȂ��I�u�W�F�N�g
		case TYPE_OBJECTX_NONE:

			for (int nCount = 0; nCount < OBJECTX_NONE_NUM_MAX; nCount++)
			{
				// ���ʂȂ��I�u�W�F�N�g�̗L���𔻒�
				if (CManagerObject::GetObjectNone(nCount) == NULL)
				{
					// ���ʂȂ��I�u�W�F�N�g�𐶐�
					CObjectXNone *pObjectXNone = CObjectXNone::Create((CObjectXNone::MODEL)m_nModelNum);

					// ���ʂȂ��I�u�W�F�N�g�̐ݒ�
					pObjectXNone->Set(
						pos,
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						rot);

					// �I�u�W�F�N�g�̃|�C���^����
					CManagerObject::SetObjectNone(nCount, pObjectXNone);

					break;
				}
			}

			break;

			// �C�x���g�I�u�W�F�N�g
		case TYPE_EVENT_OBJECT:

			for (int nCount = 0; nCount < EVENT_OBJECT_NUM_MAX; nCount++)
			{
				// �C�x���g�I�u�W�F�N�g�̗L���𔻒�
				if (CManagerObject::GetEventObject(nCount) == NULL)
				{
					// �C�x���g�I�u�W�F�N�g�𐶐�
					CEventObject *pEventObject = CEventObject::Create((CEventObject::MODEL)m_nModelNum);

					// �C�x���g�I�u�W�F�N�g�̐ݒ�
					pEventObject->Set(
						pos,
						rot);

					// �I�u�W�F�N�g�̃|�C���^����
					CManagerObject::SetEventObject(nCount, pEventObject);

					break;
				}
			}

			break;

			// �S�~
		case TYPE_GARBAGE:

			for (int nCount = 0; nCount < GARBAGE_NUM_MAX; nCount++)
			{
				// �C�x���g�I�u�W�F�N�g�̗L���𔻒�
				if (CManagerObject::GetGarbage(nCount) == NULL)
				{
					// �C�x���g�I�u�W�F�N�g�𐶐�
					CGarbage *pGarbage = CGarbage::Create((CGarbage::MODEL)m_nModelNum);

					// �C�x���g�I�u�W�F�N�g�̐ݒ�
					pGarbage->Set(
						pos,
						rot);

					// �I�u�W�F�N�g�̃|�C���^����
					CManagerObject::SetGarbage(nCount, pGarbage);

					break;
				}
			}

			break;

			// �S�~
		case TYPE_GARBAGE_COLLECT:

			for (int nCount = 0; nCount < GARBAGE_COLLECT_NUM_MAX; nCount++)
			{
				// �C�x���g�I�u�W�F�N�g�̗L���𔻒�
				if (CManagerObject::GetGarbageCollect(nCount) == NULL)
				{
					// �C�x���g�I�u�W�F�N�g�𐶐�
					CGarbageCollect *pGarbageCollect = CGarbageCollect::Create((CGarbageCollect::MODEL)m_nModelNum);

					// �C�x���g�I�u�W�F�N�g�̐ݒ�
					pGarbageCollect->Set(
						pos,
						rot);

					// �I�u�W�F�N�g�̃|�C���^����
					CManagerObject::SetGarbageCollect(nCount, pGarbageCollect);

					break;
				}
			}

			break;

			// �A�C�e��
		case TYPE_ITEM:

			for (int nCount = 0; nCount < EVENT_OBJECT_NUM_MAX; nCount++)
			{
				// �C�x���g�I�u�W�F�N�g�̗L���𔻒�
				if (CManagerObject::GetItem(nCount) == NULL)
				{
					// �C�x���g�I�u�W�F�N�g�𐶐�
					CItem *pItem = CItem::Create((CItem::MODEL)m_nModelNum);

					// �C�x���g�I�u�W�F�N�g�̐ݒ�
					pItem->Set(
						pos,
						rot);

					// �I�u�W�F�N�g�̃|�C���^����
					CManagerObject::SetItem(nCount, pItem);

					break;
				}
			}

			break;

			// �ʏ�G
		case TYPE_ENEMY_NORMAL:

			for (int nCount = 0; nCount < EVENT_OBJECT_NUM_MAX; nCount++)
			{
				// �ʏ�G�̗L���𔻒�
				if (CManagerObject::GetEnemyNormal(nCount) == NULL)
				{
					// �ʏ�G�𐶐�
					CEnemyNormal *pEnemyNormal = CEnemyNormal::Create((CEnemyNormal::MODEL)m_nModelNum);

					// �ʏ�G�̐ݒ�
					pEnemyNormal->Set(
						pos,
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						rot,
						0);

					// �ʏ�G�̃|�C���^����
					CManagerObject::SetEnemyNormal(nCount, pEnemyNormal);

					break;
				}
			}

			break;

			// �G�l�~�[�s��
		case TYPE_ENEMY_PIN:

			for (int nCount = 0; nCount < EVENT_OBJECT_NUM_MAX; nCount++)
			{
				// �ʏ�G�̗L���𔻒�
				if (CManagerObject::GetEnemyPin(nCount) == NULL)
				{
					// �ʏ�G�𐶐�
					CEnemyPin *pEnemyPin = CEnemyPin::Create((CEnemyPin::MODEL)m_nModelNum);

					// �ʏ�G�̐ݒ�
					pEnemyPin->Set(
						pos,
						rot);

					// �ʏ�G�̃|�C���^����
					CManagerObject::SetEnemyPin(nCount, pEnemyPin);

					break;
				}
			}

			break;
		}
	}

}

//-------------------------------------
//- �}�b�v�G�f�B�^�̃��f���ݒ菈��
//-------------------------------------
void CEditMap::SetModel(void)
{
	// �ϐ��錾
	int nModelNldx = 0;	// ���f���ԍ�

	switch (m_typeSelect)
	{
		// ���ʂȂ��I�u�W�F�N�g
	case TYPE_OBJECTX_NONE:

		// ���f���ԍ����擾
		nModelNldx = CObjectXNone::m_nDataModelNldx[m_nModelNum].Get();

		break;

		// �C�x���g�I�u�W�F�N�g
	case TYPE_EVENT_OBJECT:

		// ���f���ԍ����擾
		nModelNldx = CEventObject::m_nDataModelNldx[m_nModelNum].Get();

		break;

		// �S�~�I�u�W�F�N�g
	case TYPE_GARBAGE:

		// ���f���ԍ����擾
		nModelNldx = CGarbage::m_nDataModelNldx[m_nModelNum].Get();

		break;

		// �S�~����I�u�W�F�N�g
	case TYPE_GARBAGE_COLLECT:

		// ���f���ԍ����擾
		nModelNldx = CGarbageCollect::m_nDataModelNldx[m_nModelNum].Get();


		break;
		// �A�C�e���I�u�W�F�N�g
	case TYPE_ITEM:

		// ���f���ԍ����擾
		nModelNldx = CItem::m_nDataModelNldx[m_nModelNum].Get();

		break;

		// �ʏ�G
	case TYPE_ENEMY_NORMAL:

		// ���f���ԍ����擾
		nModelNldx = CEnemyNormal::m_nDataModelNldx[m_nModelNum].Get();

		break;

		// �G�l�~�[�s��
	case TYPE_ENEMY_PIN:

		// ���f���ԍ����擾
		nModelNldx = CEnemyPin::m_nDataModelNldx[m_nModelNum].Get();

		break;
	}

	// ���f������
	m_pObject->BindModel(nModelNldx, m_nModelNum);
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̃t�@�C�������o������
//-------------------------------------
void CEditMap::SaveFile(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

		// �ړ������𔲂���
		return;
	}

	// ���͂̔��� if(F5�L�[)
	if (pInputKeyboard->GetTrigger(DIK_F5) == true)
	{
		switch (m_typeSelect)
		{
		case TYPE_OBJECTX_NONE:

			// ���ʂȂ��I�u�W�F�N�g�����o������
			CFileObjNone::Save(CFileObjNone::TXT_NORMAL_000);

			break;

		case TYPE_EVENT_OBJECT:

			// �C�x���g�I�u�W�F�N�g�����o������
			CFileEvtObj::Save(CFileEvtObj::TXT_NORMAL_000);

			break;

		case TYPE_GARBAGE:

			// �S�~�����o������
			CFileGarbage::Save(CFileGarbage::TXT_NORMAL_000);

			break;

		case TYPE_GARBAGE_COLLECT:

			// �S�~�����o������
			CFileGarbageCollect::Save(CFileGarbageCollect::TXT_NORMAL_000);

			break;

		case TYPE_ITEM:

			// �A�C�e�������o������
			CFileItem::Save(CFileItem::TXT_NORMAL_000);

			break;

		case TYPE_ENEMY_NORMAL:

			// �ʏ�G�����o������
			CFileEmyNor::Save(CFileEmyNor::TXT_NORMAL_000);

			break;

		case TYPE_ENEMY_PIN:

			// �ʏ�G�����o������
			CFileEnemyPin::Save(CFileEnemyPin::TXT_ENEMY_PIN_000);

			break;
		}

	}
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̃f�o�b�N�\��
//-------------------------------------
void CEditMap::DrawDebug(void)
{
	// �f�o�b�N�v���b�N�̎擾
	CDebugProc *pDebugProc = CManager::GetDbugProc();

	// �f�o�b�N�v���b�N�擾�̗L���𔻒�
	if (pDebugProc == NULL)
	{
		return;
	}

	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();	// �ʒu
	D3DXVECTOR3 rot = m_dataRot.Get();	// ����

	//���o��
	pDebugProc->Print(" ----- �}�b�v�G�f�B�^�̏�� -----");
	pDebugProc->Print("\n");

	// ���\��
	pDebugProc->Print(" �ʒu��� : %f %f %f", pos.x, pos.y, pos.z);
	pDebugProc->Print("\n");

	pDebugProc->Print(" ������� : %f %f %f", rot.x, rot.y, rot.z);
	pDebugProc->Print("\n");

	switch (m_typeSelect)
	{
	case TYPE_OBJECTX_NONE:

		pDebugProc->Print(" ��ޏ�� [���ʂȂ��I�u�W�F�N�g]");
		pDebugProc->Print("\n");

		break;

	case TYPE_EVENT_OBJECT:

		pDebugProc->Print(" ��ޏ�� [�C�x���g�I�u�W�F�N�g]");
		pDebugProc->Print("\n");

		break;

	case TYPE_GARBAGE:

		pDebugProc->Print(" ��ޏ�� [�S�~]");
		pDebugProc->Print("\n");

		break;

	case TYPE_GARBAGE_COLLECT:

		pDebugProc->Print(" ��ޏ�� [�S�~���]");
		pDebugProc->Print("\n");

		break;

	case TYPE_ITEM:

		pDebugProc->Print(" ��ޏ�� [�A�C�e��]");
		pDebugProc->Print("\n");

		break;

	case TYPE_ENEMY_NORMAL:

		pDebugProc->Print(" ��ޏ�� [�ʏ�G]");
		pDebugProc->Print("\n");

		break;

	case TYPE_ENEMY_PIN:

		pDebugProc->Print(" ��ޏ�� [�G�l�~�[�s��]");
		pDebugProc->Print("\n");

		break;
	}

	pDebugProc->Print(" ���f���ԍ� : %d", m_nModelNum);
	pDebugProc->Print("\n");

	//���o��
	pDebugProc->Print("\n");
	pDebugProc->Print(" ----- ������ -----");
	pDebugProc->Print("\n");

	pDebugProc->Print(" �ړ� : WASD�L�[");
	pDebugProc->Print("\n");
	pDebugProc->Print("  + �����ړ� : LSHIFT�L�[");
	pDebugProc->Print("\n");
	pDebugProc->Print(" �㉺�ړ� : LSHIFT + RF�L�[");
	pDebugProc->Print("\n");
	pDebugProc->Print(" �����ύX�i15�x�j : TG�L�[");
	pDebugProc->Print("\n");
	pDebugProc->Print(" ���f���̎�ޕύX : TAB�L�[");
	pDebugProc->Print("\n");
	pDebugProc->Print(" �I�u�W�F�N�g�J�e�S����ޕύX : LCONTROL�L�[");
	pDebugProc->Print("\n");
	pDebugProc->Print(" �ݒu : SPACE�L�[");
	pDebugProc->Print("\n");
	pDebugProc->Print(" �ۑ� : F5�L�[");
	pDebugProc->Print("\n");
}