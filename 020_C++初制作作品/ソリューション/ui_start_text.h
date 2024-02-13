
//-===============================================
//-
//-	�J�n������UI�̏����̃w�b�_�[[ui_start_text.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _UI_START_TEXT_H_		// ���̃}�N������`����Ȃ�������
#define _UI_START_TEXT_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "main.h"

#include "object2d.h"

#include "data.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�N���X��`
//-======================================

class CUiStartText : public CObject2d
{

public:

	// �X�^�[�g�e�L�X�g�̃e�N�X�`���񋓌^
	typedef enum
	{
		TEX_START_000 = 0,	// �X�^�[�g�e�L�X�g000
		TEX_START_001,		// �X�^�[�g�e�L�X�g001
		TEX_MAX
	}TEX;

	CUiStartText(int nPriority = 0);
	~CUiStartText();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(TEX tex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CUiStartText * Create(TEX tex);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 sizeMoveMax, D3DXVECTOR3 sizeMoveSpeed);

	void AddSizeMove(void);
	void SubSizeMove(void);

	CDataD3DXVECTOR3 m_dataPosTarget;		// �ړI�̈ʒu
	CDataD3DXVECTOR3 m_dataMoveSpeed;		// �ړ��ʂ̑��x
	CDataBool m_bDataMoveStop;				// �ړ���~�̗L��

private:

	static int m_nTextureNldx[TEX_MAX];		// �e�N�X�`���ԍ�
};

#endif	// ��d�C���N���[�h�h�~�̏I��
