
//-===============================================
//-
//-	�C�x���g�I�u�W�F�N�g�t�@�C�������̃w�b�_�[[file_evt_obj.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _FILE_EVT_OBJ_H_		// ���̃}�N������`����Ȃ�������
#define _FILE_EVT_OBJ_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�O���錾
//-======================================

//-======================================
//-	�N���X��`
//-======================================

class CFileEvtObj
{

public:

	typedef enum
	{
		TXT_NORMAL_000 = 0,	// �ʏ�C�x���g�I�u�W�F�N�g_000�̃e�L�X�g
	}TXT;

	CFileEvtObj();
	~CFileEvtObj();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CFileEvtObj *Create(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);

	static void Save(CFileEvtObj::TXT txtType);
	static void Load(CFileEvtObj::TXT txtType);

private:

};

#endif	// ��d�C���N���[�h�h�~�̏I��
