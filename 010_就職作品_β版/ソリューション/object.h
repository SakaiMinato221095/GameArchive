
//-===============================================
//-
//-	�I�u�W�F�N�g�����̃w�b�_�[[object.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _OBJECT_H_		// ���̃}�N������`����Ȃ�������
#define _OBJECT_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

//-======================================
//-	�}�N����`
//-======================================

#define OBJECT_PRIORITY_MAX	(8)		// �D�揇�ʂ̐�
#define OBJECT_NUM_MAX		(8192)	// �I�u�W�F�N�g�̍ő吔

#define FVF_VERTEX_2D		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)					// ���_�t�H�[�}�b�g[2D]
#define FVF_VERTEX_3D		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)		// ���_�t�H�[�}�b�g[3D](���_���W�E�@���E���_�t�H�[�}�b�g[3D]�E�e�N�X�`��)

//-======================================
//-	�\���̒�`
//-======================================

// ���_���̍\����
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// ���W�ϊ��p�W���i1,0f�ŌŒ�j
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
}VERTEX_2D;

// ���_���[3D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
}VERTEX_3D;

//-======================================
//-	�O���錾
//-======================================

class CObject2d;
class CMapManagerMulti;

//-======================================
//-	�N���X��`
//-======================================

class CObject
{

public:

	CObject(int nPriority = 3);
	virtual ~CObject();

	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

	static CObject* GetTop(int nPriority);
	CObject* GetNext(void);

	virtual void Hit(void) {};
	virtual void HitDamage(int nDamage) { ; }

	void SetIsUpdateStop(bool bIsUpdateStop) { m_bIsUpdateStop = bIsUpdateStop; }
	void SetIsUpdatePause(bool bIsUpdatePause) { m_bIsUpdatePause = bIsUpdatePause; }
	void SetIsDrawStop(bool bIsDrawStop) { m_bIsDrawStop = bIsDrawStop; }

	static bool GetIsUpdateAllStop(void) { return m_bIsUpdateAllStop; }
	static void SetIsUpdateAllStop(bool bIsUpdateAllStop) { m_bIsUpdateAllStop = bIsUpdateAllStop; }

protected:

	void Release(void);

private:

	bool CheckFlagUpdate(void);

	void ReleaseObj(void);
	static void DeathAllCheckRelease(void);

	static void Debug(void);

	CObject* m_pPrev;		// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CObject* m_pNext;		// ���̃I�u�W�F�N�g�ւ̃|�C���^

	static CObject* m_apTop[OBJECT_PRIORITY_MAX];	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CObject* m_apCur[OBJECT_PRIORITY_MAX];	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^

	int m_nPriority;		// ���g�̗D�揇��

	bool m_bIsUpdateStop;		// �X�V�̗L��
	bool m_bIsUpdatePause;		// �|�[�Y���̍X�V�̗L��
	bool m_bIsDrawStop;			// �`��̗L��
	bool m_bIsDeath;			// ���S�̗L��

	static int m_nNumAll;				// �I�u�W�F�N�g�̑���
	static bool m_bIsUpdateAllStop;		// �S�X�V�̗L��
};

#endif	// ��d�C���N���[�h�h�~�̏I��
