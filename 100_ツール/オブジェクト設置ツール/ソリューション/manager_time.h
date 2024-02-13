
//================================================
//=
//=	���ԊǗ������̃w�b�_�[[manager_time.h]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	��d�C���N���[�h�h�~
//=======================================

#ifndef _MANAGER_TIME_H_		// ���̃}�N������`����Ȃ�������
#define _MANAGER_TIME_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//=======================================
//=	�C���N���[�h
//=======================================

#include "data.h"

//=======================================
//=	�N���X��`
//=======================================

class CManagerTime
{
public:

	CManagerTime();
	~CManagerTime();

	void Init(void);
	void Uninit(void);

	void Update(void);

	static CManagerTime *Create();

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

