
//================================================
//=
//= �Q�[�W�̃r���{�[�h�����̃w�b�^�[[billboard_gage.h]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	��d�C���N���[�h�h�~
//=======================================

#ifndef _BILLBOARD_GAGE_H_	// ���̃}�N������`����Ȃ�������
#define _BILLBOARD_GAGE_H_	// ��d�C���N���[�h�X�q�̃}�N�����`

//=======================================
//=	�C���N���[�h
//=======================================

#include "billboard.h"

//=======================================
//=	�N���X��`
//=======================================

// �Q�[�W�̃r���{�[�h�N���X
class CBillboardGage : public CBillboard
{
public:

	CBillboardGage(int nPriority = 3);
	~CBillboardGage();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBillboardGage* Create(void);

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

	void UpdateInfo(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color,int nData)
	{
		m_info.nData = nData;
		
		if (m_info.nMaxData != 0)
		{
			m_info.fRateData = ((float)m_info.nData / (float)m_info.nMaxData);
		}

		CBillboard::UpdateInfo(pos,size,color);		
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

#endif 