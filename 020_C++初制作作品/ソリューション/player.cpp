
//-===============================================
//-
//-	�v���C���[����[player_battle.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "player.h"

#include "renderer.h"
#include "manager.h"

#include "Input.h"
#include "xinput.h"

#include "sound.h"
#include "debugproc.h"

#include "manager_object.h"
#include "time_stop.h"

#include "camera.h"

#include "event_object.h"
#include "objectx_none.h"
#include "garbage_collect.h"
#include "gate.h"

#include "object3d.h"
#include "obj_3d_wall.h"

#include "sys_game_phase.h"
#include "effect.h"

#include "hit.h"

//-======================================
//-	�}�N����`
//-======================================

#define PLAYER_SPEED	(4.0f)	//�v���C���[�̑��x

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CPlayer::CPlayer()
{
	//// �l���N���A
	ZeroMemory(m_mtxWorld, sizeof(D3DXMATRIX));

	ZeroMemory(m_apObjectModel, sizeof(m_apObjectModel));

	m_nNumModel = 0;

	m_pMotion = NULL;
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CPlayer::~CPlayer()
{

}

//-------------------------------------
//- �v���C���[�̏���������
//-------------------------------------
HRESULT CPlayer::Init(CObjectModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax)
{
	// ���f���̃p�[�c�����擾
	m_nNumModel = CObjectModel::GetPartsNum(modelType);

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_nNumModel - 1 == nCount)
		{
			int nData = 0;
		}

		// �K�w�\��X�I�u�W�F�N�g�̗L���𔻒�
		if (m_apObjectModel[nCount] == NULL)
		{
			// �K�w�\��X�I�u�W�F�N�g�̐���
			m_apObjectModel[nCount] = CObjectModel::Create(modelType, nCount);

			// �K�w�\��X�I�u�W�F�N�g�̐ݒ�
			m_apObjectModel[nCount]->SetParent(m_apObjectModel, modelType, nCount);
		}
	}

	if (m_pMotion == NULL)
	{
		// ���[�V�����̐���
		m_pMotion = CMotion::Create(m_nNumModel, nStateMax);

		// �t�@�C����ǂݍ���
		m_pMotion->SetFile(motionType);

		// ���f���̐ݒ�
		m_pMotion->SetModel(m_apObjectModel, 0);

		// �ҋ@���[�V������ݒ�
		m_pMotion->Set(0);
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �v���C���[�̏I������
//-------------------------------------
void CPlayer::Uninit(void)
{
	// ���f���̏I������
	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_nNumModel - 1 == nCount)
		{
			int nData = 0;
		}

		if (m_apObjectModel[nCount] != NULL)
		{
			// ���f���̊J������
			m_apObjectModel[nCount]->Uninit();

			delete m_apObjectModel[nCount];
			m_apObjectModel[nCount] = NULL;
		}
	}

	// ���[�V�����̏I������
	if (m_pMotion != NULL)
	{
		// ���[�V�����̊J��
		m_pMotion->Uninit();

		delete m_pMotion;
		m_pMotion = NULL;
	}

	// �������g�̃|�C���^�̊J��
	Release();
}

//-------------------------------------
//- �v���C���[�̍X�V����
//-------------------------------------
void CPlayer::Update(void)
{
	// ���ݒ�i�O��̏��j
	m_dataPosOld.Set(m_dataPos.Get());	// �ʒu
	
	// �ړ��̓��͏���
	InputMove();

	// �����̍X�V����
	UpdateRot();

	// �ʒu���̍X�V����
	UpdatePos();

	// �I�u�W�F�N�g�Ƃ̓����蔻��
	CollisionObject();

	// �f�o�b�N�\��
	DebugPlayer();
}

//-------------------------------------
//- �v���C���[�̕`�揈��
//-------------------------------------
void CPlayer::Draw(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();	// �ʒu���
	D3DXVECTOR3 rot = m_dataRot.Get();	// �������

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

	 // �����������𔲂���
		return;
	}

	// �ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu���f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(
		D3DTS_WORLD,
		&m_mtxWorld);

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		m_apObjectModel[nCount]->Draw();
	}
}

//-------------------------------------
//- �v���C���[�̃��[�V�������擾����
//-------------------------------------
void CPlayer::Hit(int nDamage)
{

}

//-------------------------------------
//- �v���C���[�̃��[�V�������擾����
//-------------------------------------
CMotion *CPlayer::GetMotion(void)
{
	// ���[�V������Ԃ�
	return m_pMotion;
}

//-------------------------------------
//- �v���C���[�̃��f���̏��擾
//-------------------------------------
CObjectModel *CPlayer::GetObjectModel(int nNumParts)
{
	return m_apObjectModel[nNumParts];
}

//-------------------------------------
//- �v���C���[�̈ړ�����
//-------------------------------------
void CPlayer::UpdatePos(void)
{
	// ���ԊǗ��̏����擾
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// ���ԊǗ��擾�̗L���𔻒�
	if (pManagerTime == NULL)
	{
		// �����𔲂���
		return;
	}

	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();				// �ʒu
	D3DXVECTOR3 move = m_dataMove.Get();			// �ړ���

	// ���Ԕ{���̌v�Z
	D3DXVECTOR3 moveTime = pManagerTime->CalRate(move);

	// �ʒu���Ɉړ��ʂ����Z
	pos += moveTime;

	// �ړ��ʂ�����
	move.x += (0.0f - move.x) * 0.3f;
	move.y += (0.0f - move.y) * 0.3f;
	move.z += (0.0f - move.z) * 0.3f;

	// ���X�V
	m_dataPos.Set(pos);		// �ʒu
	m_dataMove.Set(move);	// �ړ���
}

//-------------------------------------
//- �v���C���[�̌�������
//-------------------------------------
void CPlayer::UpdateRot(void)
{
	// ���ԊǗ��̏����擾
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// ���ԊǗ��擾�̗L���𔻒�
	if (pManagerTime == NULL)
	{
		// �����𔲂���
		return;
	}

	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 rot = m_dataRot.Get();			// ����
	D3DXVECTOR3 rotDest = m_dataRotDest.Get();	// �ړI�̌���

	// �ړI�̌����̕␳
	if (rotDest.y > D3DX_PI)
	{
		rotDest.y += -D3DX_PI * 2;
	}
	else if (rotDest.y < -D3DX_PI)
	{
		rotDest.y += D3DX_PI * 2;
	}

	// �����̌������Z�o
	float rotDiff = rotDest.y - rot.y;

	// �����̌�����␳
	if (rotDiff > D3DX_PI)
	{
		rotDiff += -D3DX_PI * 2;
	}
	else if (rotDiff < -D3DX_PI)
	{
		rotDiff += D3DX_PI * 2;
	}

	// ���Ԕ{���̌v�Z
	float fRotCorreTime = pManagerTime->CalRate(0.15f);

	//�ړ������i�p�x�j�̕␳
	rot.y += rotDiff * fRotCorreTime;

	// �����̕␳
	if (rot.y > D3DX_PI)
	{
		rot.y += -D3DX_PI * 2;
	}
	else if (rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2;
	}

	// ���X�V
	m_dataRot.Set(rot);				// ����
	m_dataRotDest.Set(rotDest);		// �ړI�̌���
}

//-------------------------------------
//- �v���C���[�̈ړ�����
//-------------------------------------
void CPlayer::InputMove(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

	 // �ړ������𔲂���
		return;
	}

	// X���͂̃|�C���^��錾
	CXInput *pXInput = CManager::GetXInput();

	// X���͂̏��擾�̐����𔻒�
	if (pXInput == NULL)
	{
		// �����𔲂���
		return;
	}

	// ���ԊǗ��̏����擾
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// ���ԊǗ��擾�̗L���𔻒�
	if (pManagerTime == NULL)
	{
		// �����𔲂���
		return;
	}

	// �ϐ��錾
	D3DXVECTOR3 move = m_dataMove.Get();		// �ړ��ʂ��擾
	D3DXVECTOR3 rotDest = m_dataRotDest.Get();	// �ړI�̉�]�ʂ��擾

	bool bMoveStop = m_bDataStopMove.Get();				// �ړ���~�̗L��
	bool bMoveRotStop = m_bDataStopMoveRot.Get();		// �����ړ���~�̗L��

	// �J�����̏����擾
	CCamera *pCamera = CManager::GetCamera();

	// �J�����̌������擾
	D3DXVECTOR3 rotCamera = pCamera->m_dataRot.Get();

	// ���Ԕ{���̌v�Z
	float fPlayerSpeedTime = pManagerTime->CalRate(PLAYER_SPEED);

	// �ړ�
	if (pInputKeyboard->GetPress(DIK_W) == true ||
		pXInput->GetPress(CXInput::TYPE_STICK_UP, CXInput::TYPE_INPUT_STICK_L) == true)
	{//W�L�[�������ꂽ�Ƃ�
		if (pInputKeyboard->GetPress(DIK_A) == true ||
			pXInput->GetPress(CXInput::TYPE_STICK_LEFT, CXInput::TYPE_INPUT_STICK_L) == true)
		{//����ړ�

			move.x -= sinf((D3DX_PI * 0.75f) + rotCamera.y) * fPlayerSpeedTime;
			move.z -= cosf((D3DX_PI * 0.75f) + rotCamera.y) * fPlayerSpeedTime;

			rotDest.y = (D3DX_PI * 0.75f) + rotCamera.y;
		}
		else if (
			pInputKeyboard->GetPress(DIK_D) == true ||
			pXInput->GetPress(CXInput::TYPE_STICK_RIGHT, CXInput::TYPE_INPUT_STICK_L) == true)
		{//�E��ړ�

			move.x += sinf((D3DX_PI * 0.25f) + rotCamera.y) * fPlayerSpeedTime;
			move.z += cosf((D3DX_PI * 0.25f) + rotCamera.y) * fPlayerSpeedTime;

			rotDest.y = -(D3DX_PI * 0.75f) + rotCamera.y;
		}
		else
		{

			move.x += sinf((D3DX_PI * 0.0f) + rotCamera.y) * fPlayerSpeedTime;
			move.z += cosf((D3DX_PI * 0.0f) + rotCamera.y) * fPlayerSpeedTime;

			rotDest.y = D3DX_PI + rotCamera.y;

		}
	}

	else if (
		pInputKeyboard->GetPress(DIK_S) == true ||
		pXInput->GetPress(CXInput::TYPE_STICK_DOWN, CXInput::TYPE_INPUT_STICK_L) == true)
	{//S�L�[�������ꂽ�Ƃ�
		if (
			pInputKeyboard->GetPress(DIK_A) == true ||
			pXInput->GetPress(CXInput::TYPE_STICK_LEFT, CXInput::TYPE_INPUT_STICK_L) == true)
		{//�����ړ�

			move.x -= sinf((D3DX_PI * 0.25f) + rotCamera.y) * fPlayerSpeedTime;
			move.z -= cosf((D3DX_PI * 0.25f) + rotCamera.y) * fPlayerSpeedTime;

			rotDest.y = (D3DX_PI * 0.25f) + rotCamera.y;
		}
		else  if (
			pInputKeyboard->GetPress(DIK_D) == true ||
			pXInput->GetPress(CXInput::TYPE_STICK_RIGHT, CXInput::TYPE_INPUT_STICK_L) == true)
		{//�E���ړ�

			move.x += sinf((D3DX_PI * 0.75f) + rotCamera.y) * fPlayerSpeedTime;
			move.z += cosf((D3DX_PI * 0.75f) + rotCamera.y) * fPlayerSpeedTime;

			rotDest.y = -(D3DX_PI * 0.25f) + rotCamera.y;
		}
		else
		{
			//�ړ���
			move.x += sinf((D3DX_PI * 1.0f) + rotCamera.y) * fPlayerSpeedTime;
			move.z += cosf((D3DX_PI * 1.0f) + rotCamera.y) * fPlayerSpeedTime;

			rotDest.y = (D3DX_PI * 0.0f) + rotCamera.y;
		}
	}

	else  if (
		pInputKeyboard->GetPress(DIK_A) == true ||
		pXInput->GetPress(CXInput::TYPE_STICK_LEFT, CXInput::TYPE_INPUT_STICK_L) == true)
	{//A�L�[�������ꂽ�Ƃ�

		move.x -= sinf((D3DX_PI * 0.5f) + rotCamera.y) * fPlayerSpeedTime;
		move.z -= cosf((D3DX_PI * 0.5f) + rotCamera.y) * fPlayerSpeedTime;

		rotDest.y = (D3DX_PI * 0.5f) + rotCamera.y;
	}
	else if (
		pInputKeyboard->GetPress(DIK_D) == true ||
		pXInput->GetPress(CXInput::TYPE_STICK_RIGHT, CXInput::TYPE_INPUT_STICK_L) == true)
	{//D�L�[�������ꂽ�Ƃ�

		move.x += sinf((D3DX_PI * 0.5f) + rotCamera.y) * fPlayerSpeedTime;
		move.z += cosf((D3DX_PI * 0.5f) + rotCamera.y) * fPlayerSpeedTime;

		rotDest.y = -(D3DX_PI * 0.5f) + rotCamera.y;
	}

	if (bMoveRotStop != true)
	{
		// �ړI�̌������X�V
		m_dataRotDest.Set(rotDest);
	}

	if (bMoveStop != true)
	{
		// �ړ��ʂ̍X�V
		m_dataMove.Set(move);
	}
}

//-------------------------------------
//- �v���C���[�̃I�u�W�F�N�g�Ƃ̓����蔻��
//-------------------------------------
void CPlayer::CollisionObject(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();			// �ʒu
	D3DXVECTOR3 posOld = m_dataPosOld.Get();	// �O��̈ʒu
	D3DXVECTOR3 size = m_dataSize.Get();		// �傫��
	D3DXVECTOR3 move = m_dataMove.Get();		// �ړ���

	for (int nCutObjectNone = 0; nCutObjectNone < OBJECTX_NONE_NUM_MAX; nCutObjectNone++)
	{
		// �C�x���g�I�u�W�F�N�g�̏����擾
		CObjectX *pObjectNone = CManagerObject::GetObjectNone(nCutObjectNone);

		// �C�x���g�I�u�W�F�N�g�̗L���𔻒�
		if (pObjectNone != NULL)
		{
			CollisionMove(pObjectNone);
		}
	}

	for (int nCutEventObject = 0; nCutEventObject < EVENT_OBJECT_NUM_MAX; nCutEventObject++)
	{
		// �C�x���g�I�u�W�F�N�g�̏����擾
		CObjectX *pEventObject = CManagerObject::GetEventObject(nCutEventObject);

		// �C�x���g�I�u�W�F�N�g�̗L���𔻒�
		if (pEventObject != NULL)
		{
			CollisionMove(pEventObject);
		}
	}

	for (int nCount = 0; nCount < GARBAGE_COLLECT_NUM_MAX; nCount++)
	{
		// �C�x���g�I�u�W�F�N�g�̏����擾
		CObjectX *pGarbageCollect = CManagerObject::GetGarbageCollect(nCount);

		// �C�x���g�I�u�W�F�N�g�̗L���𔻒�
		if (pGarbageCollect != NULL)
		{
			CollisionMove(pGarbageCollect);
		}
	}

	// �C�x���g�I�u�W�F�N�g�̏����擾
	CObjectX *pGate = CManagerObject::GetGate();

	// �C�x���g�I�u�W�F�N�g�̗L���𔻒�
	if (pGate != NULL)
	{
		CollisionMove(pGate);
	}

	for (int nCount = 0; nCount < WALL_NUM_MAX; nCount++)
	{
		// �ǂ̏����擾
		CObject3d *pWall = CManagerObject::GetWall(nCount);

		// �C�x���g�I�u�W�F�N�g�̗L���𔻒�
		if (pWall != NULL)
		{
			CollisionMove(pWall);
		}
	}
}

//-------------------------------------
//- �v���C���[�̓����蔻��̈ړ�����
//-------------------------------------
void CPlayer::CollisionMove(CObjectX *pObjX)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();			// �ʒu
	D3DXVECTOR3 posOld = m_dataPosOld.Get();	// �O��̈ʒu
	D3DXVECTOR3 size = m_dataSize.Get();		// �傫��
	D3DXVECTOR3 move = m_dataMove.Get();		// �ړ���

	// �ϐ��錾�i�I�u�W�F�N�g���擾�j
	D3DXVECTOR3 objPos = pObjX->m_dataPos.Get();	// �ʒu
	D3DXVECTOR3 objSize = pObjX->m_dataSize.Get();	// �傫��

	// �ϐ��錾
	bool bX = false;
	bool bZ = false;

	//�����蔻��
	if (CHit::hitRectangle(pos, size, objPos, objSize) == true)
	{
		//���̓����蔻��
		if (CHit::hitRectangleSide(pos.x, size.x, objPos.x, objSize.x) == true)
		{
			//�O��̈ʒu���c�͈͓̔��ɂ���ꍇ
			if (CHit::hitRectangleSide(posOld.z, size.z, objPos.z, objSize.z) == true)
			{
				bX = true;
			}
		}

		//�c�̓����蔻��
		if (CHit::hitRectangleSide(pos.z, size.z, objPos.z, objSize.z) == true)
		{
			//�O��̈ʒu�����͈͓̔��ɂ���ꍇ
			if (CHit::hitRectangleSide(posOld.x, size.x, objPos.x, objSize.x) == true)
			{
				bZ = true;
			}
		}

		if (bX == true &&
			bZ == true)
		{
			pos.x = posOld.x;
			pos.z = posOld.z;

			m_dataPos.Set(pos);			// �ʒu
			m_dataMove.Set(move);		// �ړ���
		}
		else if (bX == true)
		{
			// �v���C���[��Y���W�ړ����~
			move.x = 0.0f;

			pos.x = posOld.x;

			m_dataPos.Set(pos);			// �ʒu
			m_dataMove.Set(move);		// �ړ���
		}
		else if (bZ == true)
		{
			// �v���C���[��Y���W�ړ����~
			move.z = 0.0f;

			pos.z = posOld.z;

			m_dataPos.Set(pos);			// �ʒu
			m_dataMove.Set(move);		// �ړ���
		}
	}
}

//-------------------------------------
//- �v���C���[�̓����蔻��̈ړ�����i�ǁj
//-------------------------------------
void CPlayer::CollisionMove(CObject3d *pObj3d)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();			// �ʒu
	D3DXVECTOR3 posOld = m_dataPosOld.Get();	// �O��̈ʒu
	D3DXVECTOR3 size = m_dataSize.Get();		// �傫��
	D3DXVECTOR3 move = m_dataMove.Get();		// �ړ���

	// �ϐ��錾�i�I�u�W�F�N�g���擾�j
	D3DXVECTOR3 objPos = pObj3d->m_dataPos.Get();	// �ʒu
	D3DXVECTOR3 objSize = pObj3d->m_dataSize.Get();	// �傫��
	D3DXVECTOR3 objRot = pObj3d->m_dataRot.Get();	// ����

	// �ϐ��錾
	bool bX = false;
	bool bZ = false;

	//�����蔻��
	if (objRot.y == D3DX_PI * 0.5f ||
		objRot.y == -D3DX_PI * 0.5f)
	{
		//���̓����蔻��
		if (CHit::hitRectangleSide(pos.x, size.x, objPos.x, objSize.z) == true)
		{
			//�O��̈ʒu���c�͈͓̔��ɂ���ꍇ
			if (CHit::hitRectangleSide(posOld.z, size.z, objPos.z, objSize.x) == true)
			{
				bX = true;
			}
		}
	}

	if (objRot.y == 0.0f ||
		objRot.y == D3DX_PI)
	{
		//�c�̓����蔻��
		if (CHit::hitRectangleSide(pos.z, size.z, objPos.z, objSize.z) == true)
		{
			//�O��̈ʒu�����͈͓̔��ɂ���ꍇ
			if (CHit::hitRectangleSide(posOld.x, size.x, objPos.x, objSize.x) == true)
			{
				bZ = true;
			}
		}
	}

	if (bX == true &&
		bZ == true)
	{
		pos.x = posOld.x;
		pos.z = posOld.z;

		m_dataPos.Set(pos);			// �ʒu
		m_dataMove.Set(move);		// �ړ���
	}
	else if (bX == true)
	{
		// �v���C���[��Y���W�ړ����~
		move.x = 0.0f;

		pos.x = posOld.x;

		m_dataPos.Set(pos);			// �ʒu
		m_dataMove.Set(move);		// �ړ���
	}
	else if (bZ == true)
	{
		// �v���C���[��Y���W�ړ����~
		move.z = 0.0f;

		pos.z = posOld.z;

		m_dataPos.Set(pos);			// �ʒu
		m_dataMove.Set(move);		// �ړ���
	}
}

//-------------------------------------
//- �v���C���[�̃f�o�b�N�\��
//-------------------------------------
void CPlayer::DebugPlayer(void)
{
	// �f�o�b�N�v���b�N�̎擾
	CDebugProc *pDebugProc = CManager::GetDbugProc();

	// �f�o�b�N�v���b�N�擾�̗L���𔻒�
	if (pDebugProc == NULL)
	{
		return;
	}

	pDebugProc->Print("\n");
	pDebugProc->Print("�v���C���[�̈ʒu\n");
	pDebugProc->Print("%f,%f,%f",m_dataPos.Get().x,m_dataPos.Get().y,m_dataPos.Get().z);
	pDebugProc->Print("\n");
}