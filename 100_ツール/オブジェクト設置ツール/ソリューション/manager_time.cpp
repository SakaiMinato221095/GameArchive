
//-===============================================
//-
//-	���ԊǗ�����[manager_time.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "manager_time.h"

#include "renderer.h"
#include "manager.h"

//-======================================
//-	�}�N����`
//-======================================

//-------------------------------------
//-	���ԊǗ��̃R���X�g���N�^
//-------------------------------------
CManagerTime::CManagerTime()
{

}

//-------------------------------------
//-	���ԊǗ��̃f�X�g���N�^
//-------------------------------------
CManagerTime::~CManagerTime()
{

}

//-------------------------------------
//- ���ԊǗ��̏���������
//-------------------------------------
void CManagerTime::Init(void)
{
	m_fDataTimeRate.Set(1.0f);		// ���Ԕ{��
	m_nDataTimeCount.Set(0);		// ���ԃJ�E���g
	m_nDataTimeCountMax.Set(0);		// ���ԃJ�E���g�̍ő�l
	m_bDataIntCount.Set(true);	// �����J�E���g�����̗L��
}

//-------------------------------------
//- ���ԊǗ��̏I������
//-------------------------------------
void CManagerTime::Uninit(void)
{

}

//-------------------------------------
//- ���ԊǗ��̍X�V����
//-------------------------------------
void CManagerTime::Update(void)
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
		float fValueInt;										// ����v�Z�̐���
		float fValueFloat = modff(fCalTime, &fValueInt);		// ����v�Z�̏����i�����Ə����̕��ʁj

		// ���ԃJ�E���g�̔��� if�i�����̃J�E���g�����j
		if (fValueInt == fValueIntOld)
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
		if (nTimeCount == nTimeCountMax)
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
CManagerTime *CManagerTime::Create(void)
{
	// �A�C�e���̃|�C���^��錾
	CManagerTime *pCManagerTime = new CManagerTime;

	// �����̐����̗L���𔻒�
	if (pCManagerTime != NULL)
	{
		// ����������
		pCManagerTime->Init();
	}
	else if (pCManagerTime == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �A�C�e���̃|�C���^��Ԃ�
	return pCManagerTime;
}

//-------------------------------------
//- ���ԊǗ��̌v�Z�����iFloat�j
//-------------------------------------
float CManagerTime::CalRate(float data)
{
	// �ϐ��錾�i���擾�j
	float nTimeRate = m_fDataTimeRate.Get();			// ���Ԕ{��

	data *= nTimeRate;

	return data;
}

//-------------------------------------
//- ���ԊǗ��̌v�Z�����iD3DXVECTOR3�j
//-------------------------------------
D3DXVECTOR3 CManagerTime::CalRate(D3DXVECTOR3 data)
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
void CManagerTime::Set(float fTimeRate, int nTimeMax)
{
	m_fDataTimeRate.Set(fTimeRate);		// ���Ԕ{��
	m_nDataTimeCountMax.Set(nTimeMax);	// ���ԃJ�E���g�̍ő�l
}
