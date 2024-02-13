
//-===============================================
//-
//-	���Ԓ�~����[time_stop.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "time_stop.h"

#include "renderer.h"
#include "manager.h"

//-======================================
//-	�}�N����`
//-======================================

//-------------------------------------
//-	���ԊǗ��̃R���X�g���N�^
//-------------------------------------
CTimeStop::CTimeStop()
{

}

//-------------------------------------
//-	���ԊǗ��̃f�X�g���N�^
//-------------------------------------
CTimeStop::~CTimeStop()
{

}

//-------------------------------------
//- ���ԊǗ��̏���������
//-------------------------------------
void CTimeStop::Init(void)
{
	m_fDataTimeRate.Set(1.0f);		// ���Ԕ{��
	m_nDataTimeCount.Set(0);		// ���ԃJ�E���g
	m_nDataTimeCountMax.Set(0);		// ���ԃJ�E���g�̍ő�l
	m_bDataIntCount.Set(true);	// �����J�E���g�����̗L��
}

//-------------------------------------
//- ���ԊǗ��̏I������
//-------------------------------------
void CTimeStop::Uninit(void)
{

}

//-------------------------------------
//- ���ԊǗ��̍X�V����
//-------------------------------------
void CTimeStop::Update(void)
{
	// �ϐ��錾�i���擾�j
	float nTimeRate = m_fDataTimeRate.Get();		// ���Ԕ{��
	int nTimeCount = m_nDataTimeCount.Get();		// ���ԃJ�E���g
	int nTimeCountMax = m_nDataTimeCountMax.Get();	// ���ԃJ�E���g�̍ő�l
	bool bIntCount = m_bDataIntCount.Get();			// �����̃J�E���g�̗L��

	// ���ԃJ�E���g�O�̔���v�Z
	float fCalTimeOld = ((1.0f * 0.5f) * nTimeCount);			// ���ԃJ�E���g�O�̔���v�Z
	float fValueIntOld;											// ���ԃJ�E���g�O�̔���v�Z�̐���
	float fValueFloatOld = modff(fCalTimeOld, &fValueIntOld);	// ���ԃJ�E���g�O�̔���v�Z�̏����i�����Ə����̕��ʁj

	// ���ԃJ�E���g�̍ő�l������
	if (nTimeCountMax != 0)
	{
		// ���ԃJ�E���g�����Z
		nTimeCount++;
		
		// ����v�Z
		float fCalTime = ((1.0f * 0.5f) * nTimeCount);		// ����v�Z
		float fValueInt;									// ����v�Z�̐���
		float fValueFloat = modff(fCalTime, &fValueInt);	// ����v�Z�̏����i�����Ə����̕��ʁj

		// ���ԃJ�E���g�̔��� if�i�����̃J�E���g�����j
		if (fValueInt == fValueIntOld && nTimeRate != 0.0f)
		{
			// �����J�E���g��ݒ�
			bIntCount = true;
		}
		else
		{
			// �����J�E���g��ݒ�
			bIntCount = false;
		}

		// ���ԃJ�E���g�̔��� if�i���{�������j
		if (nTimeCount >= nTimeCountMax)
		{
			nTimeRate = 1.0f;
			nTimeCount = 0;
			nTimeCountMax = 0;
			bIntCount = true;
		}
	}

	// ���X�V
	m_fDataTimeRate.Set(nTimeRate);			// ���Ԕ{��
	m_nDataTimeCount.Set(nTimeCount);		// ���ԃJ�E���g
	m_nDataTimeCountMax.Set(nTimeCountMax);	// ���ԃJ�E���g�̍ő�l
	m_bDataIntCount.Set(bIntCount);			// �����J�E���g�����̗L��
}

//-------------------------------------
//- ���ԊǗ��̐�������
//-------------------------------------
CTimeStop *CTimeStop::Create(void)
{
	// ���Ԓ�~�̃|�C���^��錾
	CTimeStop *pCTimeStop = DBG_NEW CTimeStop;

	// �����̐����̗L���𔻒�
	if (pCTimeStop != NULL)
	{
		// ����������
		pCTimeStop->Init();
	}
	else if (pCTimeStop == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �A�C�e���̃|�C���^��Ԃ�
	return pCTimeStop;
}

//-------------------------------------
//- ���ԊǗ��̌v�Z�����iFloat�j
//-------------------------------------
float CTimeStop::CalRate(float data)
{
	// �ϐ��錾�i���擾�j
	float nTimeRate = m_fDataTimeRate.Get();			// ���Ԕ{��

	data *= nTimeRate;

	return data;
}

//-------------------------------------
//- ���ԊǗ��̌v�Z�����iD3DXVECTOR3�j
//-------------------------------------
D3DXVECTOR3 CTimeStop::CalRate(D3DXVECTOR3 data)
{
	// �ϐ��錾�i���擾�j
	float nTimeRate = m_fDataTimeRate.Get();			// ���Ԕ{��

	data.x *= nTimeRate;
	data.y *= nTimeRate;
	data.z *= nTimeRate;

	return data;
}

//-------------------------------------
//- ���ԊǗ��̐ݒ菈��
//-------------------------------------
void CTimeStop::Set(float fTimeRate, int nTimeMax)
{
	m_fDataTimeRate.Set(fTimeRate);		// ���Ԕ{��
	m_nDataTimeCountMax.Set(nTimeMax);	// ���ԃJ�E���g�̍ő�l
}
