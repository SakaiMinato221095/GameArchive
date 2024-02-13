
//-===============================================
//-
//-	�A�j���[�V�����I�u�W�F�N�g�����̃w�b�_�[[object2d_anima.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _OBJECT_ANIMA_H_		// ���̃}�N������`����Ȃ�������
#define _OBJECT_ANIMA_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object2d.h"

//-======================================
//-	�N���X��`
//-======================================

class CObjectAnima: public CObject2d
{

public:

	CObjectAnima();
	~CObjectAnima();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjectAnima *Create(void);

	void UpdateAnima(void);

	void SetVtx(void);

	void SetAllAnima(int nLine, int nColumn, int nChangeFrame);

	CDataInt m_nDataLine;			// �A�j���[�V�����̍s��
	CDataInt m_nDataColumn;			// �A�j���[�V�����̗�

	CDataInt m_nDataChangeFrame;	// �؂�ւ���܂ł̃t���[����

	CDataInt m_nDataCounter;		// �A�j���[�V�����J�E���^�[
	CDataInt m_nDataPattern;		// �A�j���[�V�����p�^�[��No.

private:
	
};

#endif	// ��d�C���N���[�h�h�~�̏I��

