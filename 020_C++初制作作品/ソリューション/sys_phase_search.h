
//-===============================================
//-
//-	�T���t�F�[�Y�V�X�e�������̃w�b�_�[[sys_phase_search.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _SYS_PHASE_SEARCH_H_		// ���̃}�N������`����Ȃ�������
#define _SYS_PHASE_SEARCH_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "sys_game_phase.h"

#include "qte.h"
//-======================================
//-	�O���錾
//-======================================

class CPlayer;

class CManagerObject;

class CUiMission;
class CUiStartText;

class CObj2dNone;

//-======================================
//-	�N���X��`
//-======================================

class CSysPhaseSearch : public CSysGamePhase
{

public:

	typedef enum
	{
		STATE_TEXT_000 = 0,
		STATE_TEXT_001,
		STATE_TEXT_MAX,
	}STATE_TEXT;

	CSysPhaseSearch();
	~CSysPhaseSearch();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer *GetPlayer(void);
	static CManagerObject *GetManagerObject(void);
	static CUiMission *GetUiMission(void);

	static CObj2dNone *GetObj2DNone(void);

	static void SetQte(CQte::TYPE_QTE typeQte);
	static void ReleaseQte(void);
		
	CDataInt m_dataEffectCut;

private:

	static CPlayer *m_pPlayerSearch;			// �T���v���C���[
	static CManagerObject *m_pManagerObject;	// �I�u�W�F�N�g�Ǘ��̃|�C���^
	static CUiMission *m_pUiMission;			// �ړIUI�̃|�C���^
	static CUiStartText *m_apUiStartText[2];	// �X�^�[�g�e�L�X�g	

	static CQte *m_pQte;						// �N�C�b�N�^�C���C�x���g

	static CObj2dNone *m_pObj2dNone;			// ���ʂȂ�2D�I�u�W�F�N�g

	bool bState;								// �X�^�[�g�̗L��

};

#endif	// ��d�C���N���[�h�h�~�̏I��
