
//================================================
//=
//=	�U���̏���[attack.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "attack.h"

#include "manager.h"
#include "debugproc.h"

#include "coll.h"
#include "mgr_coll.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

//-------------------------------------
//-	�^�C�}�[�̃R���X�g���N�^
//-------------------------------------
CAttack::CAttack()
{
	// �l�̃N���A
	ZeroMemory(&m_info, sizeof(m_info));
	m_pColl = nullptr;
}

//-------------------------------------
//-	�^�C�}�[�̃f�X�g���N�^
//-------------------------------------
CAttack::~CAttack()
{

}

//-------------------------------------
//- �^�C�}�[�̏���������
//-------------------------------------
HRESULT CAttack::Init(void)
{
	if (m_pColl == NULL)
	{
		// �����蔻��ݒ�
		m_pColl = CColl::Create(
			CMgrColl::TAG_ATTACK,
			this,
			m_info.pos + m_info.posPlus,
			m_info.size);

		m_pColl->SetIsVisualDrawStop(false);
	}
	else
	{
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �^�C�}�[�̏I������
//-------------------------------------
void CAttack::Uninit(void)
{
	if (m_pColl != nullptr)
	{
		// �����蔻��̏�����
		m_pColl->Uninit();
		delete m_pColl;
		m_pColl = nullptr;
	}

	// �������g�̃|�C���^�̊J��
	Release();
}

//-------------------------------------
//- �^�C�}�[�̍X�V����
//-------------------------------------
void CAttack::Update(void)
{
	// �ڐG�X�V����
	UpdateHit();

	// �f�o�b�N
	Debug();
}

//-------------------------------------
//- �^�C�}�[�̕`�揈��
//-------------------------------------
void CAttack::Draw(void)
{

}

//-------------------------------------
//- �^�C�}�[�̈ʒu���̐ݒ�
//-------------------------------------
void CAttack::InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nDamage, CMgrColl::TAG tagTgt)
{
	m_info.pos = pos;
	m_info.size = size;
	m_info.nDamage = nDamage;
	m_info.tagTgt = tagTgt;
}

//-------------------------------------
//- �^�C�}�[�̈ʒu���̐ݒ�
//-------------------------------------
CAttack* CAttack::Create(void)
{
	// ��������
	CAttack* pAttack = DBG_NEW CAttack;

	// �����̐����̗L���𔻒�
	if (pAttack != NULL)
	{
		// ����������
		if (FAILED(pAttack->Init()))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pAttack == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �|�C���^��Ԃ�
	return pAttack;
}

//-------------------------------------
//- �ڐG�X�V����
//-------------------------------------
void CAttack::UpdateHit(void)
{
	CManager* pManager = CManager::GetInstance();

	if (pManager == nullptr)
	{
		return;
	}

	CMgrColl* pMgrColl = pManager->GetMgrColl();

	if (pMgrColl == nullptr)
	{
		return;
	}

	if (m_pColl != nullptr)
	{
		// �����蔻��̏��X�V����
		m_pColl->UpdateData(
			m_info.pos + m_info.posPlus,
			m_info.size);

		// �^�[�Q�b�g�Ƃ̐ڐG����
		if (m_pColl->Hit(m_info.tagTgt, CMgrColl::EVENT_TYPE_TRIGGER))
		{
			// �ő�ڐG�����擾
			CColl::Data data = m_pColl->GetData();
			int nHitNldxMax = data.nHitNldxMax;

			// �ڐG�����G�̃_���[�W����
			for (int nCount = 0; nCount < nHitNldxMax; nCount++)
			{
				CColl* pColl = pMgrColl->GetColl(data.hitData[nCount].nNldx);

				if (pColl != nullptr)
				{
					CObject* pObj = pColl->GetData().pObj;

					if (pObj != nullptr)
					{
						pObj->HitDamage(m_info.nDamage);
					}
				}
			}
		}

	}
}

//-------------------------------------
//- �v���C���[�̃f�o�b�N�\��
//-------------------------------------
void CAttack::Debug(void)
{
	// �f�o�b�N�v���b�N�̎擾
	CDebugProc* pDebugProc = CManager::GetInstance()->GetDbugProc();

	// �f�o�b�N�v���b�N�擾�̗L���𔻒�
	if (pDebugProc == NULL)
	{
		return;
	}

	pDebugProc->Print("\n");
	pDebugProc->Print("�U���̈ʒu");
	pDebugProc->Print("\n");
	pDebugProc->Print("%f,%f,%f", m_info.pos.x, m_info.pos.y, m_info.pos.z);
	pDebugProc->Print("\n");
}