
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

#include "main.h"

#include "renderer.h"
#include "manager.h"
#include "game.h"

#include "helper_sakai.h"

#include "input.h"
#include "xinput.h"

#include "player.h"

//=======================================
//=	�R���X�g��`
//=======================================

const D3DXVECTOR3 FOLL_POS_V = (D3DXVECTOR3(0.0f, 400.0f, 0.0f));		// �ǔ���Ԃ̏������_
const D3DXVECTOR3 FOLL_POS_R = (D3DXVECTOR3(0.0f, 200.0f, 0.0f));		// �ǔ���Ԃ̏��������_
const float FOLL_LENGTH = (600.0f);										// �ǔ���Ԃ̎��_�ƒ����_�̋���
const float FOLL_POS_DEST_SPEED = (0.3f);								// �ǔ���Ԃ̈ʒu�␳���x

//=======================================
//=	�}�N����`
//=======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	�J�����̃R���X�g���N�^
//-------------------------------------
CCamera::CCamera()
{
	ZeroMemory(&m_data, sizeof(m_data));
	ZeroMemory(m_mtxProjectien, sizeof(D3DXMATRIX));
	ZeroMemory(m_mtxView, sizeof(D3DXMATRIX));

	m_mode = MODE(0);
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
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 posV = m_data.posV;		// ���_
	D3DXVECTOR3 posR = m_data.posR;		// �����_
	D3DXVECTOR3 vecU = m_data.vecU;		// ������̃x�N�g��
	D3DXVECTOR3 rot = m_data.rot;		// ����
	float fLength = m_data.fLength;		// �J�����Ƃ̒���
	
	m_bIsUpdateStop = false;

	// �O���[�o���ϐ��̏�����
	{
		// ���ݒ�
		posV = FOLL_POS_V;						// ���_
		posR = FOLL_POS_R;						// �����_
		vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// ������̃x�N�g��
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
		fLength = FOLL_LENGTH;					// �J�����Ƃ̒���

		// ���X�V
		m_data.posV = posV;			// ���_
		m_data.posVDest = posV;		// �ړI�̎��_
		m_data.posR = posR;			// �����_
		m_data.posRDest = posR;		// �ړI�̒����_
		m_data.vecU = vecU;			// ������̃x�N�g��
		m_data.rot = rot;			// ����
		m_data.rotDest = rot;		// �ړI�̌���
		m_data.fLength = fLength;	// �J�����Ƃ̒���
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
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

		// �X�V�����𔲂���
		return;
	}

	if (CManager::GetInstance()->GetMode() == CScene::MODE_GAME)
	{
		// �v���C���[�J��������
		CameraPlayer();

		// �����̍X�V����
		UpdateRot();
	}
	else if (CManager::GetInstance()->GetMode() == CScene::MODE_TITEL)
	{
		// �^�C�g���̍X�V����
		UpdateTitle();
	}
}

//-------------------------------------
//-	�J�����̐ݒ菈��
//-------------------------------------
void CCamera::SetCamera(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 posV = m_data.posV;		// ���_
	D3DXVECTOR3 posR = m_data.posR;		// �����_
	D3DXVECTOR3 vecU = m_data.vecU;		// ������̃x�N�g��

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

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
		40000.0f);

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
	m_data.posV = posV;			// ���_
	m_data.posR = posR;			// �����_
	m_data.vecU = vecU;			// ������̃x�N�g��
}

//-------------------------------------
//-	�J�����̊e���[�h�̐ݒ菈��
//-------------------------------------
void CCamera::SetMode(CCamera::MODE mode)
{
	// ���[�h�̐ݒ�
	m_mode = mode;

	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 posV = m_data.posV;		// ���_
	D3DXVECTOR3 posR = m_data.posR;		// �����_
	D3DXVECTOR3 vecU = m_data.vecU;		// ������̃x�N�g��
	D3DXVECTOR3 rot = m_data.rot;		// ����
	float fLength = m_data.fLength;		// �J�����Ƃ̒���

	switch (m_mode)
	{
	case MODE_NORMAL:

		// ���ݒ�
		posV = D3DXVECTOR3(0.0f, 1250.0f, -500.0f);		// ���_
		posR = D3DXVECTOR3(0.0f, 0.0f, 500.0f);			// �����_
		fLength = 1250.0f;								// �J�����Ƃ̒���
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ����

		break;

	case MODE_FOLLOWING:

		// ���ݒ�
		posV = FOLL_POS_V;						// ���_
		posR = FOLL_POS_R;						// �����_
		vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// ������̃x�N�g��
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
		fLength = FOLL_LENGTH;					// �J�����Ƃ̒���

		break;
		
	case MODE_TITLE:

		// ���ݒ�
		posV = D3DXVECTOR3(0.0f, 100.0f, 0.0f);			// ���_
		posR = D3DXVECTOR3(400.0f, 100.0f, 0.0f);		// �����_
		fLength = 800.0f;								// �J�����Ƃ̒���
		rot = D3DXVECTOR3(0.0f, 0.9f, 0.0f);			// ����

		break;
	}

	// ���X�V
	m_data.posV = posV;			// ���_
	m_data.posVDest = posV;		// �ړI�̎��_
	m_data.posR = posR;			// �����_
	m_data.posRDest = posR;		// �ړI�̒����_
	m_data.vecU = vecU;			// ������̃x�N�g��
	m_data.rot = rot;			// ����
	m_data.rotDest = rot;		// �ړI�̌���
	m_data.fLength = fLength;	// �J�����Ƃ̒���
}

//-------------------------------------
//-	�J�����̌����ǔ�����
//-------------------------------------
void CCamera::UpdateRot(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 rot = m_data.rot;				// ����
	D3DXVECTOR3 rotDest = m_data.rotDest;		// �ړI�̌���

	// �p�x�̐��K��
	HelperSakai::NormalizeAngle(&rot, &rotDest, 0.2f);

	// ���X�V
	m_data.rot = rot;			// ����
	m_data.rotDest = rotDest;	// �ړI�̌���
}

//-------------------------------------
//-	�^�C�g���J�����̍X�V����
//-------------------------------------
void CCamera::UpdateTitle(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 posV = m_data.posV;				// ���_
	D3DXVECTOR3 posVDest = m_data.posVDest;		// �ړI�̎��_
	D3DXVECTOR3 posR = m_data.posR;				// �����_
	D3DXVECTOR3 posRDest = m_data.posRDest;		// �ړI�̒����_
	D3DXVECTOR3 rot = m_data.rot;				// ����
	D3DXVECTOR3 rotDest = m_data.rotDest;		// �ړI�̌���
	float fLength = m_data.fLength;				// �J�����Ƃ̋���

	//���_�̈ʒu���X�V
	posV.x = posR.x + sinf(rot.y) * -fLength;
	posV.z = posR.z + cosf(rot.y) * -fLength;

	//�ړI�̎��_�̈ʒu
	posVDest.x = 0.0f + (sinf(rot.y) * -fLength) + 0.0f;
	posVDest.z = 0.0f + (cosf(rot.y) * -fLength) + 0.0f;

	//�ړI�̒����_�̈ʒu
	posRDest.x = 400.0f + 0.0f;
	posRDest.z = 0.0f + 0.0f;

	//���_�̕␳
	posV.x += (posVDest.x - posV.x) * 0.3f;
	posV.z += (posVDest.z - posV.z) * 0.3f;

	//�����_�̕␳
	posR.x += (posRDest.x - posR.x) * 0.3f;
	posR.z += (posRDest.z - posR.z) * 0.3f;

	//�p�x�̕␳
	rot.y += (rotDest.y - rot.y) * 0.3f;

	// ���X�V
	m_data.posV = posV;			// ���_
	m_data.posVDest = posV;		// �ړI�̎��_
	m_data.posR = posR;			// �����_
	m_data.posRDest = posR;		// �ړI�̒����_
	m_data.rot = rot;			// ����
	m_data.rotDest = rot;		// �ړI�̌���
	m_data.fLength = fLength;	// �J�����Ƃ̒���
}

//-------------------------------------
//-	�v���C���[�̃J��������
//-------------------------------------
void CCamera::CameraPlayer(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

	 // �X�V�����𔲂���
		return;
	}

	// X���͂̃|�C���^��錾
	CXInput* pXInput = CManager::GetInstance()->GetXInput();

	// X���͂̏��擾�̐����𔻒�
	if (pXInput == NULL)
	{
		// �����𔲂���
		return;
	}

	if (pInputKeyboard->GetPress(DIK_A) == true ||
		pXInput->GetPress(CXInput::TYPE_STICK_LEFT, CXInput::TYPE_INPUT_STICK_L) == true ||
		pXInput->GetPress(CXInput::TYPE_STICK_LEFT, CXInput::TYPE_INPUT_STICK_R) == true)
	{//[E�L�[�������ꂽ�Ƃ�]

		m_data.rotDest.y -= 0.02f;
	}
	else if (
		pInputKeyboard->GetPress(DIK_D) == true ||
		pXInput->GetPress(CXInput::TYPE_STICK_RIGHT, CXInput::TYPE_INPUT_STICK_L) == true ||
		pXInput->GetPress(CXInput::TYPE_STICK_RIGHT, CXInput::TYPE_INPUT_STICK_R) == true)
	{
		m_data.rotDest.y += 0.02f;
	}

	if (pInputKeyboard->GetPress(DIK_Q) == true || 
		pXInput->GetPress(CXInput::TYPE_STICK_LEFT, CXInput::TYPE_INPUT_STICK_R) == true)
	{//[E�L�[�������ꂽ�Ƃ�]

		m_data.rotDest.y -= 0.03f;
	}
	else if (pInputKeyboard->GetPress(DIK_E) == true ||
			 pXInput->GetPress(CXInput::TYPE_STICK_RIGHT, CXInput::TYPE_INPUT_STICK_R) == true)
	{
		m_data.rotDest.y += 0.03f;
	}

	// �v���C���[�̏��擾
	CPlayer* pPlayer = CGame::GetPlayer();

	// �v���C���[�̏��擾�̐����𔻒�
	if (pPlayer == NULL)
	{// ���s��

		// �ǔ������𔲂���
		return;
	}

	CPlayer::Data data = pPlayer->GetData();

	//�����_�ƃv���C���[�̋���
	D3DXVECTOR3 cameraPlayer = D3DXVECTOR3(
		sinf(data.rot.y),
		30.0f,
		cosf(data.rot.y));

	//���_�̈ʒu���X�V
	m_data.posV.x = m_data.posR.x + sinf(m_data.rot.y) * -m_data.fLength;
	m_data.posV.z = m_data.posR.z + cosf(m_data.rot.y) * -m_data.fLength;

	//�ړI�̎��_�̈ʒu
	m_data.posVDest.x = data.pos.x + (sinf(m_data.rot.y) * -m_data.fLength) + cameraPlayer.x;
	m_data.posVDest.z = data.pos.z + (cosf(m_data.rot.y) * -m_data.fLength) + cameraPlayer.z;

	//�ړI�̒����_�̈ʒu
	m_data.posRDest.x = data.pos.x + cameraPlayer.x;
	m_data.posRDest.z = data.pos.z + cameraPlayer.z;

	//�����_�̕␳
	m_data.posR.x += (m_data.posRDest.x - m_data.posR.x) * 0.05f;
	m_data.posR.z += (m_data.posRDest.z - m_data.posR.z) * 0.05f;
}