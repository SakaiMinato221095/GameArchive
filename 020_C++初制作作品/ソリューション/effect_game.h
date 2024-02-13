
//-===============================================
//-
//-	�Q�[���G�t�F�N�g�̏����̃w�b�_�[[screen_game.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _EFFECT_GAME_H_		// ���̃}�N������`����Ȃ�������
#define _EFFECT_GAME_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "data.h"

//-======================================
//-	�O���錾
//-======================================

class CCamera;

//-======================================
//-	�N���X��`
//-======================================

class CEffectGame
{

public:

	CEffectGame();
	~CEffectGame();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	static CEffectGame *Create(void);

	void Set(D3DXVECTOR3 rot, D3DXVECTOR3 speed, int nTime, int nLoopCount);

	void AddQuake(D3DXVECTOR3 quakeRot, D3DXVECTOR3 quakeSpeed);
	void SubQuake(D3DXVECTOR3 QuakeRot, D3DXVECTOR3 quakeSpeed);

	CDataD3DXVECTOR3 m_dataRotQuake;		// ��ʗh��̌���
	CDataD3DXVECTOR3 m_dataSpeed;			// ��ʗh��̑��x

	CDataInt m_nDataLife;					// �̗�
	CDataInt m_nDataLoopCount;				// ���[�v�����
	CDataInt m_nDataLifeCount;				// �̗̓J�E���g 

	CDataBool m_bDataUse;					// �g�p�̗L��

	CDataD3DXVECTOR3 m_dataPosVQuake;		// ��ʗh��̎��_
	CDataD3DXVECTOR3 m_dataPosVQuakeDest;	// ��ʗh��̖ړI�̎��_

	CDataD3DXVECTOR3 m_dataPosRQuake;		// ��ʗh��̒����_
	CDataD3DXVECTOR3 m_dataPosRQuakeDest;	// ��ʗh��̖ړI�̒����_

private:

};

//-======================================
//- �v���g�^�C�v�錾
//-======================================

#endif	// ��d�C���N���[�h�h�~�̏I��
