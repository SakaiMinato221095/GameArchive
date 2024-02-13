
//-===============================================
//-
//-	ゲージ処理のヘッダー[obj_2d_gage.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _OBJ_2D_GAGE_H_		// このマクロが定義されなかったら
#define _OBJ_2D_GAGE_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object2d.h"

//-======================================
//-	クラス定義
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

	// 情報
	typedef struct
	{
		int nData;			// 現在の値
		int nMaxData;		// 現在の最大値
		float fRateData;	// 割合の値
	}Info;

	Info m_info;	// 情報

};

#endif	// 二重インクルード防止の終了
