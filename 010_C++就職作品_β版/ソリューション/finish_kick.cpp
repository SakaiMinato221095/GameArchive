
//================================================
//=
//=	�L�b�N�̃t�B�j�b�V���U������[finish_kick.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "finish_kick.h"

#include "coll.h"
#include "mgr_coll.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CFinishKick::CFinishKick()
{

}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CFinishKick::~CFinishKick()
{

}

//-------------------------------------
//- ����������
//-------------------------------------
HRESULT CFinishKick::Init(void)
{
	// �e�N���X�̏���������
	if (CAttack::Init() == E_FAIL)
	{
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �I������
//-------------------------------------
void CFinishKick::Uninit(void)
{
	// �e�N���X�̏I������
	CAttack::Uninit();
}

//-------------------------------------
//- �X�V����
//-------------------------------------
void CFinishKick::Update(void)
{
	// �ڐG�X�V����
	UpdateHit();

	// �f�o�b�N
	Debug();
}

//-------------------------------------
//- �`�揈��
//-------------------------------------
void CFinishKick::Draw(void)
{
	// �e�N���X�̕`�揈��
	CAttack::Draw();
}

//-------------------------------------
//- �����ݒ菈��
//-------------------------------------
void CFinishKick::InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nDamage,CMgrColl::TAG tagTgt)
{
	// �e�N���X�̏����ݒ菈��
	CAttack::InitSet(pos, size, nDamage, tagTgt);

	// �^�[�Q�b�g��G�ɐݒ�
	SetTagTgt(CMgrColl::TAG_ENEMY);
}

//-------------------------------------
//- ��������
//-------------------------------------
CFinishKick* CFinishKick::Create(void)
{
	// ��������
	CFinishKick* pFinishKick = DBG_NEW CFinishKick;

	// �����̐����̗L���𔻒�
	if (pFinishKick != NULL)
	{
		// ����������
		if (FAILED(pFinishKick->Init()))
		{// ���s��

			return NULL;
		}
	}
	else if (pFinishKick == NULL)
	{// ���s��

		return NULL;
	}

	// �|�C���^��Ԃ�
	return pFinishKick;
}

