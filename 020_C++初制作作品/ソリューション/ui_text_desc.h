
//-===============================================
//-
//-	���������UI�̏����̃w�b�_�[[ui_text_desc.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _UI_TEXT_DESC_H_		// ���̃}�N������`����Ȃ�������
#define _UI_TEXT_DESC_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

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

class CUiTextDesc : public CObject2d
{

public:

	// ����������̃e�N�X�`���񋓌^
	typedef enum
	{
		TEX_PUSH = 0,
		TEX_MAX
	}TEX;

	CUiTextDesc(int nPriority = 0);
	~CUiTextDesc();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(TEX tex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CUiTextDesc * Create(TEX tex);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 sizeMoveMax , D3DXVECTOR3 sizeMoveSpeed);

	void SetVtx(void);

	void AddSizeMove(void);
	void SubSizeMove(void);

	CDataD3DXVECTOR3 m_dataSizeMoveMax;		// �傫���̈ړ��ʂ̍ő�l
	CDataD3DXVECTOR3 m_dataSizeMoveAcu;		// �傫���̈ړ��ʂ̒~�ϒn
	CDataD3DXVECTOR3 m_dataSizeMoveSpeed;	// �傫���̈ړ��ʂ̑��x
	CDataBool m_bDataSizeMove;				// �傫���̈ړ��ʂ̕ω�����

private:

	static int m_nTextureNldx[TEX_MAX];		// �e�N�X�`���ԍ�
};

#endif	// ��d�C���N���[�h�h�~�̏I��
