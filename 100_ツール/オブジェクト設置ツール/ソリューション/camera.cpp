
//================================================
//=
//= �J�����̏���[camera.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "camera.h"

#include "renderer.h"
#include "manager.h"
#include "manager_object.h"

#include "input.h"

#include "manager_time.h"

#include "debugproc.h"

//=======================================
//=	�}�N����`
//=======================================

#define CAMERA_MOVE_SPEED	(50.0f)	// �J�����̈ړ����x

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	�J�����̃R���X�g���N�^
//-------------------------------------
CCamera::CCamera()
{
	ZeroMemory(m_mtxProjectien, sizeof(D3DXMATRIX));
	ZeroMemory(m_mtxView, sizeof(D3DXMATRIX));

	m_mode = MODE_NORMAL;
}

//-------------------------------------
//-	�J�����̃f�X�g���N�^
//-------------------------------------
CCamera::~CCamera()
{
}

//-------------------------------------
//-	�J�����̏���������
//-------------------------------------
HRESULT CCamera::Init(void)
{	
	// �O���[�o���ϐ��̏�����
	{
		m_dataPosV.Set(D3DXVECTOR3(-750.0f, 2000.0f, -800.0f));	// ���_
		m_dataPosVDest.Set(m_dataPosV.Get());					// �ړI�̎��_

		m_dataPosR.Set(D3DXVECTOR3(-750.0f, 0.0f, -800.0f));	// �����_
		m_dataPosRDest.Set(m_dataPosR.Get());					// �ړI�̒����_

		m_dataVecU.Set(D3DXVECTOR3(0.0f, 1.0f, 0.0f));			// ������̃x�N�g��

		m_fDataLength.Set(2000.0f);								// �J�����Ƃ̒���

		m_dataRot.Set(D3DXVECTOR3(0.0f, 0.72f, 0.0f));			// ����
		m_dataRotDest.Set(m_dataRot.Get());						// �ړI�̌���

		// �ϐ��錾�i���擾�j
		D3DXVECTOR3 posR = m_dataPosR.Get();	// ���_
		D3DXVECTOR3 posV = m_dataPosV.Get();	// �����_
		D3DXVECTOR3 rot = m_dataRot.Get();		// ����
		float fLength = m_fDataLength.Get();	// �J�����Ƃ̒���

		//�����_�̈ʒu���X�V
		posR.x = posV.x + sinf(rot.y) * fLength;
		posR.z = posV.z + cosf(rot.y) * fLength;

		// ���X�V
		m_dataPosR.Set(posR);		// ���_
		m_dataPosV.Set(posV);		// �����_
		m_dataRot.Set(rot);			// ����
		m_fDataLength.Set(fLength);	// �J�����Ƃ̒���
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//-	�J�����̏I������
//-------------------------------------
void CCamera::Uninit(void)
{

}

//-------------------------------------
//-	�J�����̍X�V����
//-------------------------------------
void CCamera::Update(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

		// �X�V�����𔲂���
		return;
	}

	if (pInputKeyboard->GetTrigger(DIK_F2) != NULL)
	{
		// ���[�h�ݒ菈��
		SetMode();
	}

	// �J�����̃��[�h
	switch (m_mode)
	{
	case MODE_NORMAL:

		// �J�����̈ړ�����
		UpdateOperation();

		break;

	case MODE_SHOP:

		// �J�����̈ړ�����
		UpdateOperation();

		break;
	}
}

//-------------------------------------
//-	�J�����̑��쏈��
//-------------------------------------
void CCamera::UpdateOperation(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 posV = m_dataPosV.Get();	// ���_
	D3DXVECTOR3 posR = m_dataPosR.Get();	// �����_
	D3DXVECTOR3 rot = m_dataRot.Get();		// ����
	float fLength = m_fDataLength.Get();	// �J�����Ƃ̋���

	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

		// �X�V�����𔲂���
		return;
	}

	// ���ԊǗ��̏����擾
	CManagerTime *pManagerTime = CManager::GetManagerTime();

	// ���ԊǗ��擾�̗L���𔻒�
	if (pManagerTime == NULL)
	{
		// �����𔲂���
		return;
	}

	//�ړ�
	if (pInputKeyboard->GetPress(DIK_LEFT) == true)
	{//���̈ړ�[A�L�[�������ꂽ�Ƃ�]

		posV.x -= CAMERA_MOVE_SPEED;
		posR.x -= CAMERA_MOVE_SPEED;

	}
	if (pInputKeyboard->GetPress(DIK_RIGHT) == true)
	{//�E�̈ړ�[D�L�[�������ꂽ�Ƃ�]

		posV.x += CAMERA_MOVE_SPEED;
		posR.x += CAMERA_MOVE_SPEED;

	}
	if (pInputKeyboard->GetPress(DIK_UP) == true)
	{//�E�̈ړ�[W�L�[�������ꂽ�Ƃ�]

		posV.z += CAMERA_MOVE_SPEED;
		posR.z += CAMERA_MOVE_SPEED;

	}
	if (pInputKeyboard->GetPress(DIK_DOWN) == true)
	{//�E�̈ړ�[S�L�[�������ꂽ�Ƃ�]

		posV.z -= CAMERA_MOVE_SPEED;
		posR.z -= CAMERA_MOVE_SPEED;

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
	m_dataPosV.Set(posV);		// ���_
	m_dataPosR.Set(posR);		// �����_
	m_dataRot.Set(rot);			// �J�����̌���
	m_fDataLength.Set(fLength);	// �J�����Ƃ̋���

}

//-------------------------------------
//-	�J�����̐ݒ菈��
//-------------------------------------
void CCamera::SetCamera(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 posV = m_dataPosV.Get();	// ���_
	D3DXVECTOR3 posR = m_dataPosR.Get();	// �����_
	D3DXVECTOR3 vecU = m_dataVecU.Get();	// ������̃x�N�g��

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

		// �����������𔲂���
		return;
	}

	// �ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	// �v���W�F�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjectien);

	// �v���W�F�V�����}�g���b�N�X�𐶐��i��{�J�����j
	D3DXMatrixPerspectiveFovLH(
		&m_mtxProjectien,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH /
		(float)SCREEN_HEIGHT,
		10.0f,
		20000.0f);

	//// �v���W�F�V�����}�g���b�N�X�𐶐��i���s���e�j
	//D3DXMatrixOrthoLH(
	//	&m_mtxProjectien,
	//	(float)SCREEN_WIDTH,
	//	(float)SCREEN_HEIGHT,
	//	10.0f,
	//	1000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(
		D3DTS_PROJECTION,
		&m_mtxProjectien);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);
		
	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(
		&m_mtxView,
		&posV,		// ���_
		&posR,		// �����_
		&vecU);		// ������x�N�g��

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(
		D3DTS_VIEW,
		&m_mtxView);

	// ���X�V
	m_dataPosV.Set(posV);	// ���_
	m_dataPosR.Set(posR);	// �����_
	m_dataVecU.Set(vecU);	// ������̃x�N�g��
}

//-------------------------------------
//-	�J�����̊e���[�h�̐ݒ菈��
//-------------------------------------
void CCamera::SetMode(void)
{
	// ��ނ����Z
	m_mode = (MODE)(m_mode + 1);

	if (m_mode == MODE_MAX)
	{
		// ��ނ�������
		m_mode = (MODE)(0);
	}

	switch (m_mode)
	{
	case MODE_NORMAL:

		m_dataPosV.Set(D3DXVECTOR3(-750.0f, 2000.0f, -800.0f));	// ���_
		m_dataPosR.Set(D3DXVECTOR3(-750.0f, 0.0f, -800.0f));	// �����_
		m_fDataLength.Set(2000.0f);								// �J�����Ƃ̒���
		m_dataRot.Set(D3DXVECTOR3(0.0f, 0.72f, 0.0f));			// ����

		break;

	case MODE_SHOP:

		m_dataPosV.Set(D3DXVECTOR3(0.0f, 1250.0f, -500.0f));	// ���_
		m_dataPosR.Set(D3DXVECTOR3(0.0f, 0.0f, 500.0f));		// �����_
		m_fDataLength.Set(1250.0f);								// �J�����Ƃ̒���
		m_dataRot.Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f));			// ����

		break;
	}

	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 posR = m_dataPosR.Get();	// ���_
	D3DXVECTOR3 posV = m_dataPosV.Get();	// �����_
	D3DXVECTOR3 rot = m_dataRot.Get();		// ����
	float fLength = m_fDataLength.Get();	// �J�����Ƃ̒���

	//�����_�̈ʒu���X�V
	posR.x = posV.x + sinf(rot.y) * fLength;
	posR.z = posV.z + cosf(rot.y) * fLength;

	// ���X�V
	m_dataPosR.Set(posR);		// ���_
	m_dataPosV.Set(posV);		// �����_
	m_dataRot.Set(rot);			// ����
	m_fDataLength.Set(fLength);	// �J�����Ƃ̒���

	// �ړI�̏��̍X�V
	m_dataPosVDest.Set(m_dataPosV.Get());	// �ړI�̎��_
	m_dataPosRDest.Set(m_dataPosR.Get());	// �ړI�̒����_
	m_dataRotDest.Set(m_dataRot.Get());		// �ړI�̌���
}