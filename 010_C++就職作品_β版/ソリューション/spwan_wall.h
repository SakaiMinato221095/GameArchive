
//-===============================================
//-
//-	�o���ǂ̏����̃w�b�_�[[spwan_wall.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _SPWAN_WALL_H_		// ���̃}�N������`����Ȃ�������
#define _SPWAN_WALL_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object.h"

#include "phase_manager.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�R���X�g��`
//=======================================

//=======================================
//=	�O���錾
//=======================================

class CColl;
class CObj3dWall;

//-======================================
//-	�N���X��`
//-======================================

class CSpwanWall : public CObject
{

public:

	// �t�B�[���h�̃e�N�X�`���̗񋓌^
	typedef enum
	{
		TEX_NULL = 0,		// �Ȃ�
		TEX_SPWAN_000,		// �o���ǂ̃e�N�X�`��
		TEX_BLOCK_000,		// �����ǂ̃e�N�X�`��
		TEX_MAX
	}TEX;

	CSpwanWall(int nPriority);
	~CSpwanWall();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	virtual void Hit(void);

	void InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR color, D3DXVECTOR2 texPos);

	static CSpwanWall* Create(void);

	void SetPos(D3DXVECTOR3 pos) { m_info.pos = pos; }
	D3DXVECTOR3 GetPos(void) { return m_info.pos; }

	void SetRot(D3DXVECTOR3 rot) { m_info.rot = rot; }
	D3DXVECTOR3 GetRot(void) { return m_info.rot; }

	void SetSize(D3DXVECTOR3 size) { m_info.size = size; }
	D3DXVECTOR3 GetSize(void) { return m_info.size; }

	void SetColor(D3DXCOLOR color) { m_info.color = color; }
	D3DXCOLOR GetColor(void) { return m_info.color; }

	void SetTexPos(D3DXVECTOR2 texPos) { m_info.texPos = texPos; }
	D3DXVECTOR2 GetTexPos(void) { return m_info.texPos; }

	void SetTypePhase(CPhaseManager::TYPE_PHASE typePhase) { m_info.typePhase = typePhase; }
	CPhaseManager::TYPE_PHASE SetTypePhase(void) { return m_info.typePhase; }

private:

	void UpdateType(void);
	void SetPhase(void);
	void SpwanEnemyPhaseOne(void);
	void SpwanEnemyPhaseTwo(void);
	void SpwanEnemyPhaseThree(void);

	struct Info
	{
		D3DXVECTOR3 pos;	// �ʒu
		D3DXVECTOR3 rot;	// ����
		D3DXVECTOR3 size;	// �傫��
		D3DXCOLOR color;	// �F
		D3DXVECTOR2 texPos;	// �e�N�X�`���ʒu

		int nNumTarget;							// �^�[�Q�b�g�̐�
		CPhaseManager::TYPE_PHASE typePhase;	// �t�F�[�Y�ԍ�
	};

	struct InfoVisual
	{
		CObj3dWall* pObj3dWall;	// ��
	};

	struct InfoAttach
	{
		CColl* pColl;			// �����蔻��
	};

	Info m_info;
	InfoVisual m_infoVisual;
	InfoAttach m_infoAttach;

	static int m_nTextureNldx[TEX_MAX];		// �e�N�X�`���̔ԍ�
};

#endif	// ��d�C���N���[�h�h�~�̏I��
