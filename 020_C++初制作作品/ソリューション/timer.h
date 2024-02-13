
//-===============================================
//-
//-	�^�C�}�[�̏����̃w�b�_�[[timer.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _TIMER_H_		// ���̃}�N������`����Ȃ�������
#define _TIMER_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "number.h"

#include "data.h"

//=======================================
//=	�}�N����`
//=======================================

#define TIMER_NUM_MAX	(4)		// �^�C�}�[�̎g�p��

#define GAME_TIME		(180)	// �Q�[������

//-======================================
//-	�N���X��`
//-======================================

class CTimer
{

public:

	CTimer();
	~CTimer();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTimer *Create(void);
	HRESULT CreateNumber(void);

	void NullAllNumber(void);

	void NumberTex(void);

	void Elapsed(void);

	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 interval, D3DXVECTOR3 between);
	void SetSize(D3DXVECTOR3 size);

	void SetNumber(void);

	void SetTime(int nTime);
	
	CDataD3DXVECTOR3 m_dataPos;			// �ʒu
	CDataD3DXVECTOR3 m_dataInterval;	// �Ԋu
	CDataD3DXVECTOR3 m_dataBetween;		// ��؂�̊Ԋu

	CDataD3DXVECTOR3 m_dataSize;		// �T�C�Y

	CDataInt m_nDataTime;				// �X�R�A�̒l

	CDataInt m_nTimerCount;				// �^�C�}�[�̃J�E���g

private:

	CNumber *m_apNumber[TIMER_NUM_MAX];	// �^�C�}�[�p�̐���

};

#endif	// ��d�C���N���[�h�h�~�̏I��
