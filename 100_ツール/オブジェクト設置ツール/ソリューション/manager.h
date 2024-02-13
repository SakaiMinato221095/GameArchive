
//-===============================================
//-
//-	�Ǘ������̃w�b�_�[[manager.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _MANAGER_H_		// ���̃}�N������`����Ȃ�������
#define _MANAGER_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

//-======================================
//-	�O���錾
//-======================================

class CManagerObject;

class CRenderer;
class CInputKeyboard;
class CSound;
class CDebugProc;

class CManagerTexture;
class CManagerModel;
class CManagerTime;

class CCamera;
class CLight;

class CEditMap;

//-======================================
//-	�N���X��`
//-======================================

class CManager
{

public:

	CManager();
	virtual ~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CManagerObject *GetManagerObject(void);

	static CRenderer *GetRenderer(void);
	static CInputKeyboard *GetInputKeyboard(void);
	static CSound *GetSound(void);
	static CDebugProc *GetDbugProc(void);

	static CManagerTexture *GetManagerTexture(void);
	static CManagerModel *GetManagerModel(void);
	static CManagerTime *GetManagerTime(void);

	static CCamera *GetCamera(void);
	static CLight *GetLight(void);

	static CEditMap *GetMapEdit(void);

private:

	void DebugCommand(void);					// �f�o�b�N����

	static CManagerObject *m_pManagerObject;	// �I�u�W�F�N�g�Ǘ��̃|�C���^

	static CRenderer *m_pRenderer;				// �����_���[�̃|�C���^
	static CInputKeyboard *m_pInputKeyboard;	// �L�[�{�[�h�̃|�C���^
	static CSound *m_pSound;					// �T�E���h�̃|�C���^
	static CDebugProc *m_pDbugProc;				// �f�o�b�N�̃|�C���^

	static CManagerTexture *m_pManagerTexture;	// �e�N�X�`���Ǘ��̃|�C���^
	static CManagerModel *m_pManagerModel;		// ���f���Ǘ��̃|�C���^
	static CManagerTime *m_pManagerTime;		// ���ԊǗ��̃|�C���^

	static CCamera *m_pCamera;					// �J�����̃|�C���^
	static CLight *m_pLight;					// ���C�g�̃|�C���^

	static CEditMap *m_pMapEdit;				// �}�b�v�G�f�B�^�̃|�C���^
};

#endif	// ��d�C���N���[�h�h�~�̏I��
