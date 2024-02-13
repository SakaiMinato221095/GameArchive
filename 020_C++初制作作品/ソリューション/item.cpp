
//-===============================================
//-
//-	�A�C�e���̏���[item.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "item.h"
#include "obj_2d_item_info.h"

#include "renderer.h"
#include "manager.h"

#include "manager_model.h"
#include "time_stop.h"

#include "effect.h"
#include "particle.h"
#include "state_battle.h"

#include "file_data_item.h"

#include "game.h"
#include "mgr_sys_obj.h"
#include "score.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�R���X�g��`
//=======================================

// �A�C�e���̃��f���̃R���X�g��`
const char *pModelItem[] =
{
	"data\\MODEL\\gun_copper.x",	// �e�̃��f��
	"data\\MODEL\\gun_silver.x",	// �e�̃��f��
	"data\\MODEL\\gun_gold.x",		// �e�̃��f��

	"data\\MODEL\\Bomb.x",			// �{���̃��f��
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

CDataInt CItem::m_nDataModelNldx[MODEL_MAX] = {};		// ���f���̔ԍ�
CItem::ModelData CItem::m_modelData[MODEL_MAX] = {};	// ���f�����

//-------------------------------------
//-	�A�C�e���̃R���X�g���N�^
//-------------------------------------
CItem::CItem()
{
	m_model = (MODEL)0;
	m_pItemInfo = NULL;
}

//-------------------------------------
//-	�A�C�e���̃f�X�g���N�^
//-------------------------------------
CItem::~CItem()
{

}

//-------------------------------------
//- �G�̃��f���ǂݍ���
//-------------------------------------
HRESULT CItem::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

	 // �����������𔲂���
		return E_FAIL;
	}

	// ���f���Ǘ��̐���
	CManagerModel *pManagerModel = CManager::GetManagerModel();

	// ���f���Ǘ��̗L���𔻒�
	if (pManagerModel == NULL)
	{
		// �����������𔲂���
		return E_FAIL;
	}

	// �e�N�X�`���ݒ�
	for (int nCount = 0; nCount < MODEL_MAX; nCount++)
	{
		// ���f���ԍ����擾
		int nModelNldx = m_nDataModelNldx[nCount].Get();

		// ���f���ԍ��̎擾�i���f���̊����j
		nModelNldx = pManagerModel->Regist(pModelItem[nCount]);

		// ���f���̓ǂݍ��ݐ����̗L�����m�F
		if (nModelNldx == -1)
		{
			// ���s���ɏ����������𔲂���
			return E_FAIL;
		}

		// ���f���ԍ���ݒ�
		m_nDataModelNldx[nCount].Set(nModelNldx);
	}

	// ���f�����
	CFileDataItem::Load();

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �G�̓ǂݍ��񂾃��f���j��
//-------------------------------------
void CItem::Unload(void)
{

}

//-------------------------------------
//- �A�C�e���̏����������iX�t�@�C���I�u�W�F�N�g�ݒ�j
//-------------------------------------
HRESULT CItem::Init(MODEL model)
{
	// ���f���Ǘ��̐���
	CManagerModel *pManagerModel = CManager::GetManagerModel();

	// ���f���Ǘ��̗L���𔻒�
	if (pManagerModel == NULL)
	{
		// �����𔲂���
		return E_FAIL;
	}

	// ���f���ԍ����擾
	int nModelNldx = m_nDataModelNldx[model].Get();

	// ���ʂȂ��I�u�W�F�N�g�̃��f������
	BindModel(nModelNldx, model);

	// �����ݒ�
	InitSet(model);

	// 2D�̃A�C�e�����
	{
		// 2D�̃A�C�e�����̗L���𔻒�
		if (m_pItemInfo == NULL)
		{
			// 2D�̃A�C�e�����̐���
			m_pItemInfo = CObj2dItemInfo::Create(m_model);

			// 2D�̃A�C�e�����̐��������̗L���𔻒�
			if (m_pItemInfo == NULL)
			{
				// ���������𔲂���
				return E_FAIL;
			}
		}
	}

	// X�t�@�C���I�u�W�F�N�g�̏����� if(�����������̗L���𔻒�)
	if (FAILED(CObjectX::Init()))
	{
		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �A�C�e���̏I������
//-------------------------------------
void CItem::Uninit(void)
{
	// 2D�A�C�e�����̃|�C���^��������
	m_pItemInfo = NULL;

	// X�t�@�C���I�u�W�F�N�g�̏I��
	CObjectX::Uninit();
}

//-------------------------------------
//- �A�C�e���̍X�V����
//-------------------------------------
void CItem::Update(void)
{
	// ���ԊǗ��̏����擾
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// ���ԊǗ��擾�̗L���𔻒�
	if (pManagerTime == NULL)
	{
		// �����𔲂���
		return;
	}

	// �ϐ��錾�i���擾�j
	bool bUse = m_bDataUse.Get();				// �g�p�̗L��
	D3DXVECTOR3 rotAdd = m_dataRotAdd.Get();	// ��]��

	// �g�p�̗L���𔻒�
	if (bUse == false)
	{// �g�p�\

		// �g�p�\�\������
		AvailableDisplay();
	}

	// ���Ԕ{���̌v�Z
	D3DXVECTOR3 rotAddTime = pManagerTime->CalRate(rotAdd);

	// ��]����
	AddRot(rotAddTime);

	// X�t�@�C���I�u�W�F�N�g�̍X�V����
	CObjectX::Update();
}

//-------------------------------------
//- �A�C�e���̕`�揈��
//-------------------------------------
void CItem::Draw(void)
{
	// X�t�@�C���I�u�W�F�N�g�̕`�揈��
	CObjectX::Draw();
}

//-------------------------------------
//- �A�C�e���̐��������iX�t�@�C���I�u�W�F�N�g�ݒ�j
//-------------------------------------
CItem * CItem::Create(MODEL model)
{
	// �A�C�e���̃|�C���^��錾
	CItem *pCItem = new CItem;

	// �����̐����̗L���𔻒�
	if (pCItem != NULL)
	{
		// ����������
		if (FAILED(pCItem->Init(model)))
		{// ���s��

		 // �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCItem == NULL)
	{// ���s��

	 // �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �A�C�e���̃|�C���^��Ԃ�
	return pCItem;
}

//-------------------------------------
//-	���f���̐ݒ菈��
//-------------------------------------
int CItem::GetModel(void)
{
	// ���f���ݒ�
	return(int)m_model;
}

//-------------------------------------
//-	���f���̐ݒ菈��
//-------------------------------------
void CItem::SetModel(int nModelNldx)
{
	// ���f���ݒ�
	m_model = (MODEL)nModelNldx;
}

//-------------------------------------
//-	���f���̏��̐ݒ菈��
//-------------------------------------
void CItem::SetModelData(int nNum, CItem::ModelData modelData)
{
	// ���f�����̑��
	m_modelData[nNum] = modelData;	// �傫��
}

//-------------------------------------
//-	���f���̏��̎擾����
//-------------------------------------
CItem::ModelData CItem::GetModelData(int nNum)
{
	// ���f������Ԃ�
	return m_modelData[nNum];
}

//-------------------------------------
//- �A�C�e���̐ݒ菈��
//-------------------------------------
void CItem::InitSet(MODEL model)
{
	// ���X�V
	m_dataRotAdd.Set(D3DXVECTOR3(0.0f, 0.01f, 0.0f));	// ��]��

	// �f�[�^�ݒ�
	m_dataSize.Set(m_modelData[model].size);
}

//-------------------------------------
//- �A�C�e���̎��s����
//-------------------------------------
void CItem::Execution(void)
{
	// �퓬�X�e�[�^�X�̏����擾
	CStateBattle *pStateBattle = CGame::GetStateBattle();

	// �퓬�X�e�[�^�X�擾�����̗L���𔻒�
	if (pStateBattle == NULL)
	{
		// �����𔲂���
		return;
	}

	// �X�R�A�̏����擾
	CScore *pScore = CGame::GetMgrSysObj()->GetScore();

	//  �X�R�A�̎擾�����̗L���𔻒�
	if (pScore == NULL)
	{
		// �����������𔲂���
		return;
	}

	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();	// �ʒu���

	int nBuyCount = m_nBuyCount.Get();	// �w���J�E���g

	// �ϐ��錾�i�X�R�A�̏��j
	int nScore = pScore->m_nDataScore.Get();	// �X�R�A�̒l

	// �X�R�A�ƒl�i�𔻒�
	if (nScore >= m_modelData[m_model].nPrice)
	{
		// �X�R�A�̌��Z
		nScore -= m_modelData[m_model].nPrice;

		// �w���J�E���g�����Z
		nBuyCount++;

		// �w���񐔂̔���
		if (nBuyCount == m_modelData[m_model].nBuyMax)
		{
			// �g�p��ݒ�
			m_bDataUse.Set(true);
		}

		// �p�[�e�B�N���̐���
		CParticle::SetParticle(
			32,
			pos,
			D3DXVECTOR3(20.0f, 20.0f, 0.0f),
			D3DXVECTOR3(30.0f,30.0f,0.0f),
			D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f),
			60);

		switch (m_model)
		{
		case MODEL_GUN_000:

			// �������̐ݒ�
			pStateBattle->SetWeaponCopper(true);

			break;

		case MODEL_GUN_001:

			// �⑕���̐ݒ�
			pStateBattle->SetWeaponSilver(true);

			break;

		case MODEL_GUN_002:

			// �������̐ݒ�
			pStateBattle->SetWeaponGold(true);

			break;

		case MODEL_BOMB_000:

			// �{���i�T�u����j�̐ݒ�
			pStateBattle->SetSubWeaponBomb(true);

			break;
		}
	}

	// ���X�V
	m_nBuyCount.Set(nBuyCount);			// �w���J�E���g

	// ���X�V�i�X�R�A�j
	pScore->m_nDataScore.Set(nScore);	// �X�R�A
}

//-------------------------------------
//- �A�C�e���̎g�p�\�\��
//-------------------------------------
void CItem::AvailableDisplay(void)
{
	// ���ԊǗ��̏����擾
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// ���ԊǗ��擾�̗L���𔻒�
	if (pManagerTime == NULL)
	{
		// �����𔲂���
		return;
	}

	// �X�R�A�̏����擾
	CScore *pScore = CGame::GetMgrSysObj()->GetScore();

	//  �X�R�A�̎擾�����̗L���𔻒�
	if (pScore == NULL)
	{
		// �����������𔲂���
		return;
	}

	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();				// �ʒu
	int nEffectCount = m_nDataEffectCount.Get();	// �G�t�F�N�g�o���̃J�E���g

	// �ϐ��錾�i�X�R�A�̏��j
	int nScore = pScore->m_nDataScore.Get();		// �X�R�A�̒l

	// �����J�E���g�̗L���𔻒�
	if (pManagerTime->m_bDataIntCount.Get() == true)
	{
		// �G�t�F�N�g�̃|�C���^��錾
		CEffect *pEffect = NULL;

		// �G�t�F�N�g�J�E���g�����Z
		nEffectCount++;

		if (nScore >= m_modelData[m_model].nPrice)
		{
			// �G�t�F�N�g�J�E���g�̔���
			if (nEffectCount >= 10)
			{
				// �G�t�F�N�g�̐���
				pEffect = CEffect::Create(CEffect::TEX_NORMAL_000);

				// �G�t�F�N�g�̗L���𔻒�
				if (pEffect != NULL)
				{
					// �G�t�F�N�g�J�E���g�̏�����
					nEffectCount = 0;

					// �ʒu����ݒ�
					pEffect->m_dataPos.Set(D3DXVECTOR3(pos.x, pos.y + 20.0f, pos.z));

					// �傫����ݒ�
					pEffect->m_dataSize.Set(D3DXVECTOR3(15.0f, 15.0f, 0.0f));

					// �ړ��ʂ�ݒ�
					pEffect->m_dataMove.Set(D3DXVECTOR3(0.0f, 1.0f, 0.0f));

					// �F��ݒ�
					pEffect->m_dataColor.Set(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

					// �̗͐ݒ�
					pEffect->m_nDataLife.Set(60);
				}
			}
		}
		else
		{
			// �G�t�F�N�g�J�E���g�̔���
			if (nEffectCount >= 10)
			{
				// �G�t�F�N�g�̐���
				pEffect = CEffect::Create(CEffect::TEX_NORMAL_000);

				// �G�t�F�N�g�̗L���𔻒�
				if (pEffect != NULL)
				{
					// �G�t�F�N�g�J�E���g�̏�����
					nEffectCount = 0;

					// �ʒu����ݒ�
					pEffect->m_dataPos.Set(D3DXVECTOR3(pos.x, pos.y + 20.0f, pos.z));

					// �傫����ݒ�
					pEffect->m_dataSize.Set(D3DXVECTOR3(15.0f, 15.0f, 0.0f));

					// �ړ��ʂ�ݒ�
					pEffect->m_dataMove.Set(D3DXVECTOR3(0.0f, 1.0f, 0.0f));

					// �F��ݒ�
					pEffect->m_dataColor.Set(D3DXCOLOR(0.5f, 0.0f, 0.0f, 0.5f));

					// �̗͐ݒ�
					pEffect->m_nDataLife.Set(60);
				}
			}
		}
	}

	// ���X�V
	m_dataPos.Set(pos);						// �ʒu
	m_nDataEffectCount.Set(nEffectCount);	// �G�t�F�N�g�o���̃J�E���g
}

//-------------------------------------
//- �A�C�e���̍w���\�̗L���𔻒�
//-------------------------------------
bool CItem::GetBuyUse(void)
{
	// �X�R�A�̏����擾
	CScore *pScore = CGame::GetMgrSysObj()->GetScore();

	//  �X�R�A�̎擾�����̗L���𔻒�
	if (pScore == NULL)
	{
		// �����������𔲂���
		return false;
	}

	// �ϐ��錾�i�X�R�A�̏��j
	int nScore = pScore->m_nDataScore.Get();	// �X�R�A�̒l

	// �X�R�A�ƃA�C�e���̉��i�𔻒�
	if (nScore >= m_modelData[m_model].nPrice)
	{
		// �w���\��Ԃ�
		return true;
	}

	// �w���s��Ԃ�
	return false;
}

//-------------------------------------
//- �A�C�e�����̎擾����
//-------------------------------------
CObj2dItemInfo *CItem::GetItemInfo(void)
{
	return m_pItemInfo;
}
