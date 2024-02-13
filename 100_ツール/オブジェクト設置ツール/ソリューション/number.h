
//-===============================================
//-
//-	���������̃w�b�_�[[object.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _NUMBER_H_		// ���̃}�N������`����Ȃ�������
#define _NUMBER_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object2d.h"

#include "data.h"

//-======================================
//-	�N���X��`
//-======================================

class CNumber : public CObject2d
{

public:

	// �����̃e�N�X�`���񋓌^
	typedef enum
	{
		TEX_GOLD_000 = 0,		// ���F_000
		TEX_MAX
	}TEX;

	CNumber(int nPriority = 3);
	~CNumber();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(TEX tex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CNumber *Create(TEX tex);

	void SetVtx(void);

	CDataInt m_nDataDigits;

private:

	static int m_nTextureNldx[TEX_MAX];		// �e�N�X�`���ԍ�

};

#endif	// ��d�C���N���[�h�h�~�̏I��
