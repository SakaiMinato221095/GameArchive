
//-===============================================
//-
//-	�ʏ�G�̏���[enemy_normal.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "enemy_normal.h"
#include "object_x.h"

#include "renderer.h"
#include "manager.h"
#include "manager_object.h"

#include "manager_model.h"

#include "score.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	�ʏ�G�̃R���X�g���N�^
//-------------------------------------
CEnemyNormal::CEnemyNormal()
{

}

//-------------------------------------
//-	�ʏ�G�̃f�X�g���N�^
//-------------------------------------
CEnemyNormal::~CEnemyNormal()
{

}

//-------------------------------------
//- �ʏ�G�̏���������
//-------------------------------------
HRESULT CEnemyNormal::Init(MODEL model)
{
	// X�t�@�C���I�u�W�F�N�g�̏����� if(�����������̗L���𔻒�)
	if (FAILED(CEnemy::Init(model)))
	{
		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �ʏ�G�̏I������
//-------------------------------------
void CEnemyNormal::Uninit(void)
{
	// �G�̏I������
	CEnemy::Uninit();
}

//-------------------------------------
//- �ʏ�G�̍X�V����
//-------------------------------------
void CEnemyNormal::Update(void)
{
	// �G�̍X�V����
	CEnemy::Update();
}

//-------------------------------------
//- �ʏ�G�̕`�揈��
//-------------------------------------
void CEnemyNormal::Draw(void)
{
	// �G�̕`�揈��
	CEnemy::Draw();
}

//-------------------------------------
//- �ʏ�G�̐�������
//-------------------------------------
CEnemyNormal *CEnemyNormal::Create(MODEL model)
{
	// �ʏ�G�̐���
	CEnemyNormal *pCEnemyNormal = new CEnemyNormal;

	// �����̐����̗L���𔻒�
	if (pCEnemyNormal != NULL)
	{
		// ����������
		if (FAILED(pCEnemyNormal->Init(model)))
		{// ���s��

		 // �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCEnemyNormal == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �ʏ�G�̃|�C���^��Ԃ�
	return pCEnemyNormal;
}

//-------------------------------------
//- �ʏ�G�̐ݒ菈��
//-------------------------------------
void CEnemyNormal::Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot , int nLife)
{
	// ���X�V
	m_dataPos.Set(pos);		// �ʒu
	m_dataPosOld.Set(pos);	// �O��̈ʒu

	m_dataSize.Set(size);	// �傫��

	m_dataRot.Set(rot);		// �ړ���
	m_dataRotDest.Set(rot);	// �ړI�̌���

	m_nDataLife.Set(nLife);	// �̗�
}