
//================================================
//=
//=	���Ԓ�~�����̃w�b�_�[[time_stop.h]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	��d�C���N���[�h�h�~
//=======================================

#ifndef _TIME_STOP_H_		// ���̃}�N������`����Ȃ�������
#define _TIME_STOP_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//=======================================
//=	�C���N���[�h
//=======================================

#include "data.h"

//=======================================
//=	�N���X��`
//=======================================

class CTimeStop
{
public:

	CTimeStop();
	~CTimeStop();

	void Init(void);
	void Uninit(void);

	void Update(void);

	static CTimeStop *Create();

	float CalRate(float data);
	D3DXVECTOR3 CalRate(D3DXVECTOR3 data);

	void Set(float fTimeRate,int nTimeMax);	// ���Ԕ{���ݒ菈��

	CDataFloat m_fDataTimeRate;				// ���Ԕ{��
	CDataInt m_nDataTimeCountMax;			// ���ԃJ�E���g�̍ő�l
	CDataInt m_nDataTimeCount;				// ���ԃJ�E���g
	
	CDataBool m_bDataIntCount;				// �����̃J�E���g�̗L��

private:

};

#endif	// ��d�C���N���[�h�h�~�̏I��

