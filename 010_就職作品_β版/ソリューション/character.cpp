
//-===============================================
//-
//-	�L�����N�^�[����[character.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "character.h"

#include "renderer.h"
#include "manager.h"

#include "Input.h"
#include "xinput.h"

#include "sound.h"
#include "debugproc.h"

#include "helper_sakai.h"

#include "camera.h"

#include "coll.h"
#include "enemy.h"

#include "command.h"

#include "attack.h"
#include "punch.h"

#include "finish_punch.h"

//-======================================
//-	�}�N����`
//-======================================

#define PLAYER_SPEED		(3.0f)	// �v���C���[�̑��x

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-======================================
//-	�R���X�g��`
//-======================================

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CCharacter::CCharacter()
{
	// �l���N���A
	ZeroMemory(&m_mtxWorld, sizeof(m_mtxWorld));

	ZeroMemory(&m_apModel, sizeof(m_apModel));

	m_nNumModel = 0;

	m_pMotion = NULL;

	ZeroMemory(&m_data, sizeof(m_data));


}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CCharacter::~CCharacter()
{

}

//-------------------------------------
//- �v���C���[�̏���������
//-------------------------------------
HRESULT CCharacter::Init(CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType,int nStateMax)
{
	// ���f���̃p�[�c�����擾
	m_nNumModel = CModel::GetPartsNum(modelType);

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		// �K�w�\��X�I�u�W�F�N�g�̗L���𔻒�
		if (m_apModel[nCount] == NULL)
		{
			// �K�w�\��X�I�u�W�F�N�g�̐���
			m_apModel[nCount] = CModel::Create(modelType, nCount);

			if (m_apModel[nCount] == nullptr)
			{
				return E_FAIL;
			}

			// �K�w�\��X�I�u�W�F�N�g�̐ݒ�
			m_apModel[nCount]->SetParent(m_apModel, modelType, nCount);
		}
	}

	if (m_pMotion == NULL)
	{
		// ���[�V�����̐���
		m_pMotion = CMotion::Create(m_nNumModel, nStateMax);

		if (m_pMotion == nullptr)
		{
			return E_FAIL;
		}

		// �t�@�C����ǂݍ���
		m_pMotion->SetFile(motionType);

		// ���f���̐ݒ�
		m_pMotion->SetModel(m_apModel, 0);

		// �ҋ@���[�V������ݒ�
		m_pMotion->Set(0);
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �v���C���[�̏I������
//-------------------------------------
void CCharacter::Uninit(void)
{
	// ���f���̏I������
	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{
			// ���f���̊J������
			m_apModel[nCount]->Uninit();

			delete m_apModel[nCount];
			m_apModel[nCount] = NULL;
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
void CCharacter::Update(void)
{
	// ���[�V�����̏I������
	if (m_pMotion != NULL)
	{
		if (m_pMotion->IsFinsih())
		{
			// ���[�V�����̍X�V����
			m_pMotion->Update();
		}
	}
}

//-------------------------------------
//- �v���C���[�̕`�揈��
//-------------------------------------
void CCharacter::Draw(void)
{
	// �}�g���b�N�X�̐ݒ�
	SetMatrix();

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_apModel[nCount] != nullptr)
		{
			// �p�[�c�̕`�揈��
			m_apModel[nCount]->Draw();
		}
	}
}

//-------------------------------------
//- �v���C���[�̐�������
//-------------------------------------
CCharacter* CCharacter::Create(CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType,int nMotionStateMax)
{
	// �v���C���[�̃|�C���^��錾
	CCharacter* pPlayer = DBG_NEW CCharacter;

	// �����̐����̗L���𔻒�
	if (pPlayer != NULL)
	{
		// ����������
		if (FAILED(pPlayer->Init(modelType, motionType, nMotionStateMax)))
		{// ���s��

		 // �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pPlayer == NULL)
	{// ���s��

	 // �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �v���C���[�̃|�C���^��Ԃ�
	return pPlayer;
}

//-------------------------------------
//- �v���C���[�̕`�揈��
//-------------------------------------
void CCharacter::SetMatrix(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

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
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_data.rot.y, m_data.rot.x, m_data.rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu���f
	D3DXMatrixTranslation(&mtxTrans, m_data.pos.x, m_data.pos.y, m_data.pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(
		D3DTS_WORLD,
		&m_mtxWorld);
}