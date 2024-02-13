
//-===============================================
//-
//-	�Q�[���G�t�F�N�g�̏���[effect_game.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "effect_game.h"

#include "renderer.h"
#include "manager.h"

#include "time_stop.h"

#include "camera.h"

#include "time_stop.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	�Q�[���G�t�F�N�g�̃R���X�g���N�^
//-------------------------------------
CEffectGame::CEffectGame()
{

}

//-------------------------------------
//-	�Q�[���G�t�F�N�g�̃f�X�g���N�^
//-------------------------------------
CEffectGame::~CEffectGame()
{

}

//-------------------------------------
//- �Q�[���G�t�F�N�g�̏���������
//-------------------------------------
HRESULT CEffectGame::Init(void)
{
	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �Q�[���G�t�F�N�g�̏I������
//-------------------------------------
void CEffectGame::Uninit(void)
{

}

//-------------------------------------
//- �Q�[���G�t�F�N�g�̍X�V����
//-------------------------------------
void CEffectGame::Update(void)
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
	D3DXVECTOR3 rotQuake = m_dataRotQuake.Get();	// ����
	D3DXVECTOR3 speed = m_dataSpeed.Get();			// ���x
	int nLife = m_nDataLife.Get();					// �̗�
	int nLoopCount = m_nDataLoopCount.Get();		// ���[�v��
	int nLifeCount = m_nDataLifeCount.Get();		// �̗̓J�E���g
	bool bUse = m_bDataUse.Get();					// �g�p�̗L��

	D3DXVECTOR3 posVQuake = m_dataPosVQuake.Get();	// ��ʗh�ꎋ�_�ʒu
	D3DXVECTOR3 posRQuake = m_dataPosRQuake.Get();	// ��ʗh�꒍���_

	// �g�p�̗L���𔻒�
	if (bUse == true)
	{
		// �����J�E���g�̗L���𔻒�
		if (pManagerTime->m_bDataIntCount.Get() == true)
		{
			// �̗̓J�E���g��
			nLifeCount++;
		}

		// ���݂̗̑̓J�E���g�𔻒� if�i�̗͍ő�l�̔����ȉ��j
		if (nLife / 2 >= nLifeCount)
		{
			// �Q�[���G�t�F�N�g�̉��Z����
			AddQuake(rotQuake, speed);
		}
		// if�i�̗͍ő�l�̔����ȏ�j
		else
		{
			// �Q�[���G�t�F�N�g�̌��Z����
			SubQuake(rotQuake, speed);
		}
		
		// ���݂̗̑̓J�E���g�̔���i�ő�̗͒l�������j
		if (nLife == nLifeCount)
		{
			// �̗̓J�E���g��������
			nLifeCount = 0;

			// ���[�v�񐔂𔻒� if(���[�v�񐔂��c���Ă���Ƃ�)
			if (nLoopCount != 0)
			{
				// ���[�v�񐔂����炷
				nLoopCount--;

				// �X�s�[�h�����Z
				speed *= 0.50f;
			}
			else
			{
				// �g�p�󋵂�ݒ�
				bUse = false;

				posVQuake = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				posRQuake = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
	}

	// ���X�V
	m_dataRotQuake.Set(rotQuake);			// ����
	m_dataSpeed.Set(speed);					// ���x
	m_nDataLife.Set(nLife);					// �̗�
	m_nDataLoopCount.Set(nLoopCount);		// ���[�v��
	m_nDataLifeCount.Set(nLifeCount);		// �̗̓J�E���g
	m_bDataUse.Set(bUse);					// �g�p�̗L��
	m_dataPosVQuake.Set(posVQuake);			// ��ʗh�ꎋ�_�ʒu
	m_dataPosRQuake.Set(posRQuake);			// ��ʗh�꒍���_
}

//-------------------------------------
//- �Q�[���G�t�F�N�g�̐�������
//-------------------------------------
CEffectGame *CEffectGame::Create(void)
{
	// �Q�[���G�t�F�N�g�̃|�C���^��錾
	CEffectGame *pCEffectGame = DBG_NEW CEffectGame;

	// �����̐����̗L���𔻒�
	if (pCEffectGame != NULL)
	{
		// ����������
		if (FAILED(pCEffectGame->Init()))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCEffectGame == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �Q�[���G�t�F�N�g�̃|�C���^��Ԃ�
	return pCEffectGame;
}

//-------------------------------------
//- �Q�[���G�t�F�N�g�̐ݒ菈��
//-------------------------------------
void CEffectGame::Set(D3DXVECTOR3 rot , D3DXVECTOR3 speed,int nTime,int nLoopCount)
{
	// �ϐ��錾�i���擾�j
	bool bUse = m_bDataUse.Get();	// �g�p�̗L��

	// �g�p�̗L���𔻒�
	if (bUse == false)
	{
		m_dataRotQuake.Set(rot);
		m_dataSpeed.Set(speed);
		m_nDataLife.Set(nTime);
		m_nDataLoopCount.Set(nLoopCount);
		m_bDataUse.Set(true);
	}
}

//-------------------------------------
//-	�J�����̉�ʗh����Z����
//-------------------------------------
void CEffectGame::AddQuake(D3DXVECTOR3 quakeRot, D3DXVECTOR3 quakeSpeed)
{
	// �J�����̏����擾
	CCamera *pCamera = CManager::GetCamera();
	
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 posVQuake = m_dataPosVQuake.Get();	// ��ʗh�ꎋ�_�ʒu
	D3DXVECTOR3 posRQuake = m_dataPosRQuake.Get();	// ��ʗh�꒍���_

	// �ϐ��錾�i�J�����̏��擾�j
	D3DXVECTOR3 posV = pCamera->m_dataPosV.Get();	// ���_
	D3DXVECTOR3 posR = pCamera->m_dataPosR.Get();	// �����_
	D3DXVECTOR3 rot = pCamera->m_dataRot.Get();		// ����

	// ��ʗh��̏����Z�o
	posVQuake.x += sinf((D3DX_PI * quakeRot.y) + rot.y) * quakeSpeed.x;
	posVQuake.z += cosf((D3DX_PI * quakeRot.y) + rot.y) * quakeSpeed.z;
	posRQuake.x += sinf((D3DX_PI * quakeRot.y) + rot.y) * quakeSpeed.x * 1.5f;
	posRQuake.z += cosf((D3DX_PI * quakeRot.y) + rot.y) * quakeSpeed.z * 1.5f;

	// ���Ԕ{���̌v�Z
	D3DXVECTOR3 posVQuakeTime = posVQuake;
	D3DXVECTOR3 posRQuakeTime = posRQuake;

	// ���_�����X�V
	posV = posV + posVQuakeTime;
	posR = posR + posRQuakeTime;

	// ���X�V
	m_dataPosVQuake.Set(posVQuake);
	m_dataPosRQuake.Set(posRQuake);

	// ���X�V�i�J�����j
	pCamera->m_dataPosV.Set(posV);
	pCamera->m_dataPosR.Set(posR);
}

//-------------------------------------
//-	�J�����̉�ʗh�ꌸ�Z����
//-------------------------------------
void CEffectGame::SubQuake(D3DXVECTOR3 quakeRot, D3DXVECTOR3 quakeSpeed)
{
	// �J�����̏����擾
	CCamera *pCamera = CManager::GetCamera();

	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 posVQuake = m_dataPosVQuake.Get();	// ��ʗh�ꎋ�_�ʒu
	D3DXVECTOR3 posRQuake = m_dataPosRQuake.Get();	// ��ʗh�꒍���_

	D3DXVECTOR3 posV = pCamera->m_dataPosV.Get();	// ���_
	D3DXVECTOR3 posR = pCamera->m_dataPosR.Get();	// �����_
	D3DXVECTOR3 rot = pCamera->m_dataRot.Get();		// ����

	posVQuake.x -= sinf((D3DX_PI * quakeRot.y) + rot.y) * quakeSpeed.x;
	posVQuake.z -= cosf((D3DX_PI * quakeRot.y) + rot.y) * quakeSpeed.z;
	posRQuake.x -= sinf((D3DX_PI * quakeRot.y) + rot.y) * quakeSpeed.x * 1.5f;
	posRQuake.z -= cosf((D3DX_PI * quakeRot.y) + rot.y) * quakeSpeed.z * 1.5f;

	// ���Ԕ{���̌v�Z
	D3DXVECTOR3 posVQuakeTime = posVQuake;
	D3DXVECTOR3 posRQuakeTime = posRQuake;

	// ���_�����X�V
	posV = posV + posVQuakeTime;
	posR = posR + posRQuakeTime;

	// ���X�V
	m_dataPosVQuake.Set(posVQuake);
	m_dataPosRQuake.Set(posRQuake);

	// ���X�V�i�J�����j
	pCamera->m_dataPosV.Set(posV);
	pCamera->m_dataPosR.Set(posR);
}