
//-===============================================
//-
//-	�ڕWUI�̏����̃w�b�_�[[ui_mission.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _UI_MISSION_H_		// ���̃}�N������`����Ȃ�������
#define _UI_MISSION_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

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

class CUiMission : public CObject2d
{

public:

	// �ڕWUI�̃e�N�X�`���񋓌^
	typedef enum
	{
		TEX_SEARCH = 0,		// �T��
		TEX_SHOP,			// �w��
		TEX_BATTLE_NORMAL,	// �퓬�i�G����j
		TEX_BATTLE_BOSS,	// �퓬�i�{�X��j
		TEX_MAX
	}TEX;

	CUiMission(int nPriority = 0);
	~CUiMission();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(TEX tex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CUiMission * Create(TEX tex);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	int GetTexNldx(TEX tex);

private:

	void InitSet(void);

	static int m_nTextureNldx[TEX_MAX];		// �e�N�X�`���ԍ�
};

#endif	// ��d�C���N���[�h�h�~�̏I��
