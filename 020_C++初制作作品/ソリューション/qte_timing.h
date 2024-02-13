
//-===============================================
//-
//-	�N�C�b�N�^�C���C�x���g�i�^�C�~���O�j�̏����̃w�b�_�[[qte_timing.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _QTE_TIMING_H_		// ���̃}�N������`����Ȃ�������
#define _QTE_TIMING_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "qte.h"

#include "data.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�O���錾
//-======================================

class CObj2dNone;
class CObj2dGage;

//-======================================
//-	�N���X��`
//-======================================

class CQteTiming : public CQte
{
public:

	CQteTiming();
	~CQteTiming();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CQteTiming *Create(void);

	void InitSet(void);
	void UpdateGage(void);

	void AddGage(void);
	void SubGage(void);

	void Decision(void);

	CDataD3DXVECTOR3 m_dataPos;			// �ʒu
	CDataD3DXVECTOR3 m_dataSize;		// �傫��

	CDataInt m_nDataGageTarget;			// �ړI�̃Q�[�W�l
	CDataInt m_nDataGagePlayer;			// �v���C���[�̃Q�[�W�l

	CDataD3DXVECTOR3 m_dataGageMove;	// �v���C���[�Q�[�W�̈ړ��ʂ̑��x
	CDataBool m_bDataGageMoveDirect;	// �v���C���[�Q�[�W�̈ړ��ʂ̕ω�����

private:

	CObj2dNone *m_pObj2dNone;		// �ʏ�2D�I�u�W�F�N�g�̃|�C���^
	CObj2dGage *m_pObj2dGageTarget;	// �ړI�Q�[�W�̃|�C���^
	CObj2dGage *m_pObj2dGagePlayer;	// �v���C���[�Q�[�W�̃|�C���^


};

#endif	// ��d�C���N���[�h�h�~�̏I��
