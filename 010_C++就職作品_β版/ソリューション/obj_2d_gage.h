
//-===============================================
//-
//-	�Q�[�W�����̃w�b�_�[[obj_2d_gage.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _OBJ_2D_GAGE_H_		// ���̃}�N������`����Ȃ�������
#define _OBJ_2D_GAGE_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object2d.h"

//-======================================
//-	�N���X��`
//-======================================

class CObj2dGage : public CObject2d
{

public:

	CObj2dGage(int nPriority = 3);
	~CObj2dGage();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObj2dGage *Create(void);

	virtual void SetVtx(void);

	void SetInit(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color, int nData, int nMaxData)
	{
		SetPos(pos);
		SetSize(size);
		SetColor(color);

		m_info.nData = nData;
		m_info.nMaxData = nMaxData;

		if (m_info.nMaxData != 0)
		{
			m_info.fRateData = ((float)m_info.nData / (float)m_info.nMaxData);
		}
	}

	void UpdateInfo(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color, int nData)
	{
		m_info.nData = nData;

		if (m_info.nMaxData != 0)
		{
			m_info.fRateData = ((float)m_info.nData / (float)m_info.nMaxData);
		}

		CObject2d::UpdateInfo(pos, size, color);
	}

private:

	// ���
	typedef struct
	{
		int nData;			// ���݂̒l
		int nMaxData;		// ���݂̍ő�l
		float fRateData;	// �����̒l
	}Info;

	Info m_info;	// ���

};

#endif	// ��d�C���N���[�h�h�~�̏I��
