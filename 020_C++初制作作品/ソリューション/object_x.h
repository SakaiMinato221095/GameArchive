
//=======================
//=
//= X�t�@�C���I�u�W�F�N�g�����̃w�b�^�[[object_x.h]
//= Author Sakai Minato
//=
//=======================

//=======================================
//=	��d�C���N���[�h�h�~
//=======================================

#ifndef _OBJECT_X_H_	// ���̃}�N������`����Ȃ�������
#define _OBJECT_X_H_	// ��d�C���N���[�h�X�q�̃}�N�����`

//=======================================
//=	�C���N���[�h
//=======================================

#include "object.h"

#include "data.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�N���X��`
//=======================================

// X�t�@�C���I�u�W�F�N�g�̃N���X
class CObjectX : public CObject
{
public:

	CObjectX(int nPriority = 3);
	~CObjectX();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjectX *Create(void);

	void BindModel(int nModelNldx, int nModelNum);

	virtual void SetModel(int nModelNldx);

	void AddRot(D3DXVECTOR3 addRot);

	void SetDrawRemove(void);

	CDataD3DXVECTOR3 m_dataPos;
	CDataD3DXVECTOR3 m_dataPosOld;

	CDataD3DXVECTOR3 m_dataRot;
	CDataD3DXVECTOR3 m_dataRotDest;

	CDataD3DXVECTOR3 m_dataSize;

	CDataBool m_bDataEat;

private:

	bool m_bDraw;			// �`��̗L��
	int m_nModelNldxUse;	// ���f���ԍ�
	
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
};

#endif	// ��d�C���N���[�h�h�~�̏I��