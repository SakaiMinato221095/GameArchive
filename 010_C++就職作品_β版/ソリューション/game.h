
//-===============================================
//-
//-	�Q�[���̏����̃w�b�_�[[game.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _GAME_H_		// ���̃}�N������`����Ȃ�������
#define _GAME_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "manager.h"

//=======================================
//=	�R���X�g��`
//=======================================

namespace GAME
{
	const int FIELD_NUM = 2;
	const int WALL_NUM = 4;
}

//-======================================
//-	�O���錾
//-======================================

class CTimer;
class CPause;
class CPhaseManager;

class CPlayer;

class CSkybox;
class CObj3dField;
class CObj3dWall;

//-======================================
//-	�N���X��`
//-======================================

class CGame : public CScene
{

public:

	typedef enum
	{
		GAME_STATE_NONE = 0,	// �Q�[���̒ʏ���
		GAME_STATE_PAUSE,		// �|�[�Y���
		GAME_STATE_MAX
	}GAME_STATE;

	CGame();
	~CGame();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPause* GetPause(void) { return m_infoPoint.pPause; }
	static CPhaseManager* GetPhaseManager(void) { return m_infoPoint.pPhaseManager; }
	static CSkybox* GetSkyBox(int nNum) { return m_infoPoint.pSkyBox; }
	static CObj3dField* GetField(int nNum) { return m_infoPoint.apField[nNum]; }
	static CObj3dWall* GetWall(int nNum) { return m_infoPoint.apWall[nNum]; }
	static CPlayer* GetPlayer(void) { return m_infoPoint.pPlayer; }

private:

	// �|�C���^���
	struct InfoPoint
	{
		CPause* pPause;					// �|�[�Y
		CPhaseManager* pPhaseManager;	// �t�F�[�Y�Ǘ�

		CSkybox* pSkyBox;						// �X�J�C�{�b�N�X
		CObj3dField* apField[GAME::FIELD_NUM];	// ��
		CObj3dWall* apWall[GAME::WALL_NUM];		// ��

		CPlayer* pPlayer;					// �v���C���[
	};

	static InfoPoint m_infoPoint;		// �|�C���^�̏��

	GAME_STATE m_gameState;				// �Q�[�����
};

#endif	// ��d�C���N���[�h�h�~�̏I��
