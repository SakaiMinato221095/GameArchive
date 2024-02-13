
//-===============================================
//-
//-	�w���t�F�[�Y�V�X�e�������̃w�b�_�[[sys_phase_shop.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _SYS_PHASE_SHOP_H_		// ���̃}�N������`����Ȃ�������
#define _SYS_PHASE_SHOP_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "sys_game_phase.h"

//-======================================
//-	�O���錾
//-======================================

class CPlayer;

class CManagerObject;

class CUiMission;

//-======================================
//-	�N���X��`
//-======================================

class CSysPhaseShop : public CSysGamePhase
{

public:

	CSysPhaseShop();
	~CSysPhaseShop();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer *GetPlayer(void);

	static CManagerObject *GetManagerObject(void);

	static CUiMission *GetUiMission(void);

private:

	static CPlayer *m_pPlayerShop;				// �T���v���C���[

	static CManagerObject *m_pManagerObject;	// �I�u�W�F�N�g�Ǘ��̃|�C���^

	static CUiMission *m_pUiMission;			// �ړIUI�̃|�C���^

};

#endif	// ��d�C���N���[�h�h�~�̏I��
