
//-===============================================
//-
//-	�퓬�t�F�[�Y�V�X�e�������̃w�b�_�[[sys_phase_battle.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _SYS_PHASE_BATTLE_H_		// ���̃}�N������`����Ȃ�������
#define _SYS_PHASE_BATTLE_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "sys_game_phase.h"

//-======================================
//-	�O���錾
//-======================================

class CPlayer;
class CManagerObject;
class CLife;
class CUiMission;
class CObj2dNone;

class CEnemyBoss;

//-======================================
//-	�N���X��`
//-======================================

class CSysPhaseBattle : public CSysGamePhase
{

public:

	CSysPhaseBattle();
	~CSysPhaseBattle();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CLife *GetLife(void);
	static CPlayer *GetPlayer(void);
	static CManagerObject *GetManagerObject(void);
	static CUiMission *GetUiMission(void);

	static CObj2dNone *GetObj2DNone(void);

	CDataInt m_dataEffectCut;

private:

	static CLife *m_pLife;						// �̗�
	static CPlayer *m_pPlayerBattle;			// �퓬�v���C���[
	static CManagerObject *m_pManagerObject;	// �I�u�W�F�N�g�Ǘ��̃|�C���^
	static CUiMission *m_pUiMission;			// �ړIUI�̃|�C���^

	static CObj2dNone *m_pObj2dNone;			// ���ʂȂ�2D�I�u�W�F�N�g

};

#endif	// ��d�C���N���[�h�h�~�̏I��
