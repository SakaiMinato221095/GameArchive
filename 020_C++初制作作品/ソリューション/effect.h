
//-===============================================
//-
//-	�G�t�F�N�g�̏����̃w�b�_�[[effect.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _EFFECT_H_		// ���̃}�N������`����Ȃ�������
#define _EFFECT_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object_billboard.h"

#include "data.h"

//-======================================
//-	�N���X��`
//-======================================

class CEffect : public CObjectBillboard
{

public:


	// �G�t�F�N�g�̃e�N�X�`���񋓌^
	typedef enum
	{
		TEX_NORMAL_000 = 0,		// �ʏ�G�t�F�N�g000�̃e�N�X�`��
		TEX_MAX
	}TEX;

	CEffect(int nPriority = 3);
	~CEffect();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(TEX tex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR color, int nLife, bool bZTest);

	static CEffect *Create(TEX tex);

	CDataD3DXVECTOR3 m_dataSizeHold;	// �T�C�Y��ێ�
	CDataD3DXCOLOR m_dataColorHold;		// �F��ێ�

	CDataInt m_nDataLife;				// �̗�

	CDataBool m_bDataZTestOff;			// Z�e�X�g�̗L��

private:

	void Add(void);
	bool Sub(void);

	static int m_nTextureNldx[TEX_MAX];		// �e�N�X�`���ԍ�

};

//-======================================
//- �v���g�^�C�v�錾
//-======================================

#endif	// ��d�C���N���[�h�h�~�̏I��
