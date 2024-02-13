
//-===============================================
//-
//-	�X�R�A����[score.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "score.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	�X�R�A�̃R���X�g���N�^
//-------------------------------------
CScore::CScore()
{
	// �l�̃N���A
	for (int nCount = 0; nCount < DIGITS_SCORE; nCount++)
	{
		m_apNumber[nCount] = NULL;
	}
}

//-------------------------------------
//-	�X�R�A�̃f�X�g���N�^
//-------------------------------------
CScore::~CScore()
{

}

//-------------------------------------
//- �X�R�A�̏���������
//-------------------------------------
HRESULT CScore::Init(void)
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
//- �X�R�A�̏I������
//-------------------------------------
void CScore::Uninit(void)
{
	for (int nCount = 0; nCount < DIGITS_SCORE; nCount++)
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
//- �X�R�A�̍X�V����
//-------------------------------------
void CScore::Update(void)
{
	for (int nCount = 0; nCount < DIGITS_SCORE; nCount++)
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
//- �X�R�A�̕`�揈��
//-------------------------------------
void CScore::Draw(void)
{

}

//-------------------------------------
//- �X�R�A�̐�������
//-------------------------------------
CScore *CScore::Create(void)
{
	// �X�R�A�̐���
	CScore *pScore = DBG_NEW CScore;;

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
//- �X�R�A�̐�����������
//-------------------------------------
HRESULT CScore::CreateNumber(void)
{
	// �^�C�}�[�̐����ݒ�
	for (int nCount = 0; nCount < DIGITS_SCORE; nCount++)
	{
		if (m_apNumber[nCount] == NULL)
		{
			// �����̐�����������
			m_apNumber[nCount] = CNumber::Create(CNumber::TEX_GOLD_000);

			// �����̐������������̗L���𔻒�
			if (m_apNumber[nCount] == NULL)
			{
				// �����𔲂���
				return E_FAIL;
			}
		}
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �X�R�A�̐����|�C���^����������
//-------------------------------------
void CScore::NullAllNumber(void)
{
	for (int nCount = 0; nCount < DIGITS_SCORE; nCount++)
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
//-	�X�R�A�̌����ƃe�N�X�`���̐ݒ菈��
//-------------------------------------
void CScore::NumberTex(void)
{
	// �ϐ��錾�i���擾�j
	int nScore = m_nDataScore.Get();	// �X�R�A

	// �ϐ��錾
	int aTexU[DIGITS_SCORE];	//�e���̐������i�[

	//�����Ƃ̐��l����
	aTexU[0] = ( nScore / 10000000);
	aTexU[1] = ((nScore % 10000000) / 1000000);
	aTexU[2] = ((nScore % 1000000) / 100000);
	aTexU[3] = ((nScore % 100000) / 10000);
	aTexU[4] = ((nScore % 10000) / 1000);
	aTexU[5] = ((nScore % 1000) / 100);
	aTexU[6] = ((nScore % 100) / 10);
	aTexU[7] = ( nScore % 10);

	for (int nCount = 0; nCount < DIGITS_SCORE; nCount++)
	{
		m_apNumber[nCount]->m_nDataDigits.Set(aTexU[nCount]);
	}

	// ���X�V
	m_nDataScore.Set(nScore);	// �X�R�A
}

//-------------------------------------
//-	�X�R�A�̉��Z����
//-------------------------------------
void CScore::Add(GET_TYPE getType, int nAddScore)
{
	// �ϐ��錾�i���擾�j
	int nScore = m_nDataScore.Get();	// �X�R�A

	// �X�R�A�̎擾�n��
	switch (getType)
	{
	case GET_TYPE_NORMAL:

		// �X�R�A�����Z
		nScore += nAddScore;

		break;

	case GET_TYPE_RANDOM:

		nScore += CalRandom(nAddScore);

		break;
	}

	// ���X�V
	m_nDataScore.Set(nScore);	// �X�R�A
}

//-------------------------------------
//-	�X�R�A�̃����_���̌v�Z
//-------------------------------------
int CScore::CalRandom(int nAddScore)
{
	int nBaseValue = 30 + nAddScore;		// ��b�l�̒l
	int nRandMulti = (rand() % (5)) + 1;	// �{��
	int nRandLuck = (rand() % (20));		// ���^�̗������i�[

	// ���^���������^�i0�j�̂Ƃ�
	if (nRandLuck == 0)
	{
		// ��b�l�ɔ{
		nBaseValue *= 2;
	}

	// �ŏI�X�R�A���Z�o
	nAddScore = nBaseValue * nRandMulti;

	return nAddScore;
}

//-------------------------------------
//- �X�R�A�̈ʒu���̐ݒ�
//-------------------------------------
void CScore::SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 interval)
{
	// �����
	m_dataPos.Set(pos);				// �ʒu
	m_dataInterval.Set(interval);	// �Ԋu

	for (int nCount = 0; nCount < DIGITS_SCORE; nCount++)
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
}

//-------------------------------------
//- �X�R�A�̃T�C�Y�̐ݒ�
//-------------------------------------
void CScore::SetSize(D3DXVECTOR3 size)
{
	// �����
	m_dataSize.Set(size);	// �傫��

	for (int nCount = 0; nCount < DIGITS_SCORE; nCount++)
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
//- �X�R�A�̐F���̐ݒ�i��{�F�j
//-------------------------------------
void CScore::SetColor(void)
{
	for (int nCount = 0; nCount < DIGITS_SCORE; nCount++)
	{
		// �����̗L���𔻒�
		if (m_apNumber[nCount] != NULL)
		{
			// �����̐F������
			m_apNumber[nCount]->GetObject2d()->m_dataColor.Set();
		}
	}
}

//-------------------------------------
//- �X�R�A�̐����̐ݒ�
//-------------------------------------
void CScore::SetNumber(void)
{
	// ���擾
	D3DXVECTOR3 pos = m_dataPos.Get();				// �ʒu
	D3DXVECTOR3 interval = m_dataInterval.Get();	// �Ԋu
	D3DXVECTOR3 size = m_dataSize.Get();			// �T�C�Y

	for (int nCount = 0; nCount < DIGITS_SCORE; nCount++)
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

		// �����̈ʒu������
		m_apNumber[nCount]->GetObject2d()->m_dataSize.Set(size);
	}
}