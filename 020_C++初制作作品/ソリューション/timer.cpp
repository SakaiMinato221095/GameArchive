
//================================================
//=
//=	�^�C�}�[����[timer.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "timer.h"

#include "renderer.h"
#include "game.h"

#include "manager_texture.h"

#include "time_stop.h"

#include "sys_game_phase.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

//-------------------------------------
//-	�^�C�}�[�̃R���X�g���N�^
//-------------------------------------
CTimer::CTimer()
{
	// �l�̃N���A
	for (int nCount = 0; nCount < TIMER_NUM_MAX; nCount++)
	{
		m_apNumber[nCount] = NULL;
	}
}

//-------------------------------------
//-	�^�C�}�[�̃f�X�g���N�^
//-------------------------------------
CTimer::~CTimer()
{

}

//-------------------------------------
//- �^�C�}�[�̏���������
//-------------------------------------
HRESULT CTimer::Init(void)
{
	// �����̐�������
	if (FAILED(CreateNumber()))
	{
		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �^�C�}�[�̏I������
//-------------------------------------
void CTimer::Uninit(void)
{
	for (int nCount = 0; nCount < TIMER_NUM_MAX; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			// �����̏�����
			m_apNumber[nCount] = NULL;
		}
	}
}

//-------------------------------------
//- �^�C�}�[�̍X�V����
//-------------------------------------
void CTimer::Update(void)
{
	// ���Z����
	Elapsed();

	for (int nCount = 0; nCount < TIMER_NUM_MAX; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			// ��񂵕`��̃I��
			m_apNumber[nCount]->m_bDataAfterDraw.Set(true);
		}
	}

	// �e�N�X�`���̌����Ɛݒ菈��
	NumberTex();
}

//-------------------------------------
//- �^�C�}�[�̕`�揈��
//-------------------------------------
void CTimer::Draw(void)
{

}

//-------------------------------------
//- �^�C�}�[�̐�������
//-------------------------------------
CTimer *CTimer::Create(void)
{
	// �^�C�}�[�̐���
	CTimer *pScore = DBG_NEW CTimer;;

	// �����̐����̗L���𔻒�
	if (pScore != NULL)
	{
		// ����������
		if (FAILED(pScore->Init()))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pScore == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �p�[�e�B�N���̃|�C���^��Ԃ�
	return pScore;
}

//-------------------------------------
//- �^�C�}�[�̐�����������
//-------------------------------------
HRESULT CTimer::CreateNumber(void)
{
	// �^�C�}�[�̐����ݒ�
	for (int nCount = 0; nCount < TIMER_NUM_MAX; nCount++)
	{
		if (m_apNumber[nCount] == NULL)
		{
			// �����̐�������
			m_apNumber[nCount] = CNumber::Create(CNumber::TEX_DARK_GREEN_001);

			// �����̐��������̗L���𔻒�
			if (m_apNumber[nCount] == NULL)
			{
				// �u�Ȃ��v��Ԃ�
				return E_FAIL;
			}
		}
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �^�C�}�[�̐����|�C���^����������
//-------------------------------------
void CTimer::NullAllNumber(void)
{
	for (int nCount = 0; nCount < TIMER_NUM_MAX; nCount++)
	{
		// �����̗L���𔻒�
		if (m_apNumber[nCount] != NULL)
		{
			// �����̃|�C���^����������
			m_apNumber[nCount] = NULL;
		}
	}
}

//-------------------------------------
//-	�^�C�}�[�̌����ƃe�N�X�`���̐ݒ菈��
//-------------------------------------
void CTimer::NumberTex(void)
{
	// �ϐ��錾�i���擾�j
	int nTime = m_nDataTime.Get();	// �X�R�A

	// �ϐ��錾
	int aTexU[4];	// �e���̐������i�[

	int nSeconds = (nTime % 60);
	int nMinutes = (nTime / 60);

	// �����Ƃ̐��l����
	aTexU[0] = ((nMinutes % 100) / 10);
	aTexU[1] = ((nMinutes % 10));
	aTexU[2] = ((nSeconds % 100) / 10);
	aTexU[3] =  (nSeconds % 10);

	for (int nCount = 0; nCount < TIMER_NUM_MAX; nCount++)
	{
		// �^�C�}�[�̍X�V����
		m_apNumber[nCount]->m_nDataDigits.Set(aTexU[nCount]);
	}

	// ���X�V
	m_nDataTime.Set(nTime);	// �X�R�A
}

//-------------------------------------
//-	�^�C�}�[�̎��Ԍo�ߏ���
//-------------------------------------
void CTimer::Elapsed(void)
{
	// ���Ԓ�~�̏��擾
	CTimeStop *pTimeStop = CManager::GetManagerTime();

	// ���Ԓ�~�̏��擾�̐����𔻒�
	if (pTimeStop == NULL)
	{// ���s��

	 // �X�V�����𔲂���
		return;
	}

	// �ϐ��錾�i���擾�j
	int nTimeCount = m_nTimerCount.Get();	// �J�E���^�[
	int nTime = m_nDataTime.Get();			// ����

	// ���Ԃ̗L���𔻒�
	if (nTime > 0)
	{
		if (pTimeStop->m_bDataIntCount.Get() == true)
		{
			// �J�E���^�[�����Z
			nTimeCount++;

			// �J�E���^�[�̔���
			if (nTimeCount % 60 == 0)
			{// 60�t���[���Ɉ��

				// ���Ԃ����Z
				nTime--;
			}
		}
	}

	// ���X�V
	m_nTimerCount.Set(nTimeCount);	// �J�E���^�[
	m_nDataTime.Set(nTime);			// ����
}

//-------------------------------------
//- �^�C�}�[�̈ʒu���̐ݒ�
//-------------------------------------
void CTimer::SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 interval, D3DXVECTOR3 between)
{
	// �����
	m_dataPos.Set(pos);				// �ʒu
	m_dataInterval.Set(interval);	// �Ԋu
	m_dataBetween.Set(between);		// ��؂�̊Ԋu

	for (int nCount = 0; nCount < TIMER_NUM_MAX; nCount++)
	{
		if (nCount <= (TIMER_NUM_MAX / 2) - 1)
		{
			// �����̗L���𔻒�
			if (m_apNumber[nCount] != NULL)
			{
				// �����̈ʒu������
				m_apNumber[nCount]->GetObject2d()->m_dataPos.Set(D3DXVECTOR3(
					pos.x + (interval.x * nCount),
					pos.y + (interval.y * nCount),
					pos.z + (interval.z * nCount)));
			}
		}
		else
		{
			// �����̗L���𔻒�
			if (m_apNumber[nCount] != NULL)
			{
				// �����̈ʒu������
				m_apNumber[nCount]->GetObject2d()->m_dataPos.Set(D3DXVECTOR3(
					(pos.x + between.x) + (interval.x * nCount),
					(pos.y + between.y) + (interval.y * nCount),
					(pos.z + between.z) + (interval.z * nCount)));
			}
		}

	}
}

//-------------------------------------
//- �^�C�}�[�̃T�C�Y�̐ݒ�
//-------------------------------------
void CTimer::SetSize(D3DXVECTOR3 size)
{
	// �����
	m_dataSize.Set(size);	// �T�C�Y

	for (int nCount = 0; nCount < TIMER_NUM_MAX; nCount++)
	{
		// �����̗L���𔻒�
		if (m_apNumber[nCount] != NULL)
		{
			// �����̈ʒu������
			m_apNumber[nCount]->GetObject2d()->m_dataSize.Set(size);
		}
	}
}

//-------------------------------------
//- �^�C�}�[�̐����̐ݒ�
//-------------------------------------
void CTimer::SetNumber(void)
{
	// ���擾
	D3DXVECTOR3 pos = m_dataPos.Get();				// �ʒu
	D3DXVECTOR3 interval = m_dataInterval.Get();	// �Ԋu
	D3DXVECTOR3 between = m_dataBetween.Get();		// ��؂�̊Ԋu
	D3DXVECTOR3 size = m_dataSize.Get();			// �T�C�Y

	for (int nCount = 0; nCount < TIMER_NUM_MAX; nCount++)
	{			
		// �����̗L���𔻒�
		if (m_apNumber[nCount] != NULL)
		{
			if (nCount <= (TIMER_NUM_MAX / 2) - 1)
			{
				// �����̈ʒu������
				m_apNumber[nCount]->GetObject2d()->m_dataPos.Set(D3DXVECTOR3(
					pos.x + (interval.x * nCount),
					pos.y + (interval.y * nCount),
					pos.z + (interval.z * nCount)));
			}
			else
			{
				// �����̈ʒu������
				m_apNumber[nCount]->GetObject2d()->m_dataPos.Set(D3DXVECTOR3(
					(pos.x + between.x) + (interval.x * nCount),
					(pos.y + between.y) + (interval.y * nCount),
					(pos.z + between.z) + (interval.z * nCount)));
			}
		}

		// �����̈ʒu������
		m_apNumber[nCount]->GetObject2d()->m_dataSize.Set(size);
	}
}

//-------------------------------------
//- �^�C�}�[�̎��Ԑݒ�
//-------------------------------------
void CTimer::SetTime(int nTime)
{
	// ���Ԑݒ�
	m_nDataTime.Set(nTime);

	// �e�N�X�`���̌����Ɛݒ菈��
	NumberTex();
}