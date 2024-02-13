
//-===============================================
//-
//-	�V�X�e���I�u�W�F�N�g�Ǘ������̃w�b�_�[[mgr_sys_obj.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _MGR_SYS_OBJ_H_		// ���̃}�N������`����Ȃ�������
#define _MGR_SYS_OBJ_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

//-======================================
//-	�O���錾
//-======================================

class CTimer;

class CScore;

//-======================================
//-	�N���X��`
//-======================================

class CMgrSysObj
{

public:

	CMgrSysObj();
	~CMgrSysObj();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetNumber(void);
	void NullAllNumber(void);

	static CTimer *GetTimer(void);
	static CScore *GetScore(void);

private:

	static CTimer *m_pTimer;	// ���Ԃ̃|�C���^
	static CScore *m_pScore;	// �X�R�A�̃|�C���^

};

#endif	// ��d�C���N���[�h�h�~�̏I��