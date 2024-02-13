
//-===============================================
//-
//-	�X�R�A�̏����̃w�b�_�[[score.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _SCORE_H_		// ���̃}�N������`����Ȃ�������
#define _SCORE_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "number.h"

#include "data.h"

//-======================================
//-	�}�N����`
//-======================================

#define DIGITS_SCORE	(8)		// �X�R�A�̌���

//-======================================
//-	�N���X��`
//-======================================

class CScore
{
public:
	
	typedef enum
	{
		GET_TYPE_NORMAL = 0,	// ���ʂ̃X�R�A
		GET_TYPE_RANDOM,		// �����_����������X�R�A
		GET_TYPE_MAX
	}GET_TYPE;

	CScore();
	~CScore();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScore *Create(void);
	HRESULT CreateNumber(void);

	void NullAllNumber(void);

	void NumberTex(void);

	void Add(GET_TYPE getType, int nAddScore);

	int CalRandom(int nAddScore);

	void SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 interval);

	void SetSize(D3DXVECTOR3 size);

	void SetColor(void);

	void SetNumber(void);

	CDataD3DXVECTOR3 m_dataPos;			// �ʒu
	CDataD3DXVECTOR3 m_dataInterval;	// �Ԋu
	CDataD3DXVECTOR3 m_dataSize;		// �傫��

	CDataInt m_nDataScore;				// �X�R�A�̒l

private:

	CNumber *m_apNumber[DIGITS_SCORE];	// �����̃|�C���^

};

//-======================================
//- �v���g�^�C�v�錾
//-======================================

#endif	// ��d�C���N���[�h�h�~�̏I��
