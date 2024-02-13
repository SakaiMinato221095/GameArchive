
//-===============================================
//-
//-	�I�u�W�F�N�g�C�x���g�̏���[event_object.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "event_object.h"

#include "renderer.h"
#include "manager.h"
#include "game.h"

#include "manager_model.h"
#include "time_stop.h"

#include "mgr_sys_obj.h"
#include "sys_game_phase.h"

#include "effect.h"
#include "particle.h"

#include "effect_object.h"	

#include "file_data_evt_obj.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�R���X�g��`
//=======================================

// �I�u�W�F�N�g�C�x���g�̃��f���̃R���X�g��`
const char *pModelEventObject[] =
{
	"data\\MODEL\\DrinkShop000.x",			// ���̋@_000�̃��f��
	"data\\MODEL\\obaravegetable000.x",		// ���S��_000�̃��f��
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

CDataInt CEventObject::m_nDataModelNldx[MODEL_MAX] = {};
int CEventObject::m_nEventObjectNum = 0;

CEventObject::ModelData CEventObject::m_modelData[MODEL_MAX] = {};		// ���f�����

//-------------------------------------
//-	�I�u�W�F�N�g�C�x���g�̃R���X�g���N�^
//-------------------------------------
CEventObject::CEventObject(int nPriority) : CObjectX(nPriority)
{
	m_model = (MODEL)0;
	m_scoreGetType = CScore::GET_TYPE_NORMAL;
}

//-------------------------------------
//-	�I�u�W�F�N�g�C�x���g�̃f�X�g���N�^
//-------------------------------------
CEventObject::~CEventObject()
{

}

//-------------------------------------
//- �I�u�W�F�N�g�C�x���g�̃��f���ǂݍ���
//-------------------------------------
HRESULT CEventObject::Load(void)
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
		nModelNldx = pManagerModel->Regist(pModelEventObject[nCount]);

		// ���f���̓ǂݍ��ݐ����̗L�����m�F
		if (nModelNldx == -1)
		{
			// ���s���ɏ����������𔲂���
			return E_FAIL;
		}

		// ���f���ԍ���ݒ�
		m_nDataModelNldx[nCount].Set(nModelNldx);
	}

	// �C�x���g�I�u�W�F�N�g
	CFileDataEvtObj::Load();

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �I�u�W�F�N�g�C�x���g�̓ǂݍ��񂾃��f���j��
//-------------------------------------
void CEventObject::Unload(void)
{

}

//-------------------------------------
//- �I�u�W�F�N�g�C�x���g�̏���������
//-------------------------------------
HRESULT CEventObject::Init(MODEL model)
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

	// �G�̃��f������
	BindModel(nModelNldx, model);

	// �f�[�^�ݒ�
	m_dataSize.Set(m_modelData[model].size);

	// �����ݒ菈��
	InitSet(model);

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
//- �I�u�W�F�N�g�C�x���g�̏I������
//-------------------------------------
void CEventObject::Uninit(void)
{
	// X�t�@�C���I�u�W�F�N�g�̏I��
	CObjectX::Uninit();
}

//-------------------------------------
//- �I�u�W�F�N�g�C�x���g�̍X�V����
//-------------------------------------
void CEventObject::Update(void)
{
	// �t�F�[�Y�����擾
	CSysGamePhase::TYPE pPhaseType = CGame::GetSysGamePhase()->GetType();

	if(pPhaseType == CSysGamePhase::TYPE_SEARCH)
	{
		// �ϐ��錾�i���擾�j
		bool bUse = m_bDataUse.Get();	// �g�p�̗L��

		// �g�p�̗L���𔻒�
		if (bUse == true)
		{
			// �Ďg�p�̏���
			UpdateReuse();
		}
		else
		{
			// �g�p�\�\������
			AvailableDisplay();
		}
	}

	// X�t�@�C���I�u�W�F�N�g�̍X�V����
	CObjectX::Update();
}

//-------------------------------------
//- �I�u�W�F�N�g�C�x���g�̕`�揈��
//-------------------------------------
void CEventObject::Draw(void)
{
	// �I�u�W�F�N�g�C�x���g�̕`�揈��
	CObjectX::Draw();
}

//-------------------------------------
//- �I�u�W�F�N�g�C�x���g�̐�������
//-------------------------------------
CEventObject *CEventObject::Create(MODEL model)
{
	// �I�u�W�F�N�g�C�x���g�̐���
	CEventObject *pCEventObject = DBG_NEW CEventObject;

	// �����̐����̗L���𔻒�
	if (pCEventObject != NULL)
	{
		// ����������
		if (FAILED(pCEventObject->Init(model)))
		{// ���s��

		 // �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCEventObject == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// ��ނ�ݒ�
	pCEventObject->SetType(TYPE_ENEMY);

	// �I�u�W�F�N�g�C�x���g�̃|�C���^��Ԃ�
	return pCEventObject;
}

//-------------------------------------
//-	���f���̐ݒ菈��
//-------------------------------------
int CEventObject::GetModel(void)
{
	// ���f���ݒ�
	return(int)m_model;
}

//-------------------------------------
//-	���f���̐ݒ菈��
//-------------------------------------
void CEventObject::SetModel(int nModelNldx)
{
	// ���f���ݒ�
	m_model = (MODEL)nModelNldx;
}

//-------------------------------------
//-	���f���̏��̐ݒ菈��
//-------------------------------------
void CEventObject::SetModelData(int nNum, CEventObject::ModelData modelData)
{
	// ���f�����̑��
	m_modelData[nNum] = modelData;	// �傫��
}

//-------------------------------------
//-	���f���̏��̎擾����
//-------------------------------------
CEventObject::ModelData CEventObject::GetModelData(int nNum)
{
	// ���f������Ԃ�
	return m_modelData[nNum];
}

//-------------------------------------
//- �I�u�W�F�N�g�C�x���g�̎��s����
//-------------------------------------
void CEventObject::Execution(void)
{
	// �X�R�A�̏����擾
	CScore *pScore = CGame::GetMgrSysObj()->GetScore();

	// �X�R�A���̗L���𔻒�
	if (pScore == NULL)
	{
		return;
	}

	// �ϐ��錾�i���擾�j
 	D3DXVECTOR3 pos = m_dataPos.Get();	// �ʒu
	int nGetScore = m_nGetScore.Get();	// �擾�X�R�A

	// �g�p�󋵂��X�V
	m_bDataUse.Set(true);

	// �I�u�W�F�N�g�G�t�F�N�g�̐���
	CEffectObject *pEffectObject = CEffectObject::Create(CEffectObject::MODEL_COIN_000);

	// �I�u�W�F�N�g�G�t�F�N�g�̐��������̗L���𔻒�
	if (pEffectObject != NULL)
	{
		// �I�u�W�F�N�g�G�t�F�N�g�ݒ�
		pEffectObject->Set(
			D3DXVECTOR3(pos.x,pos.y + 30.0f,pos.z),
			D3DXVECTOR3(5.0f, 5.0f, 5.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(0.0f, 10.0f, 0.0f),
			D3DXVECTOR3(0.0f, 200.0f, 0.0f));
	}

	// �X�R�A�̎擾����
	pScore->Add(m_scoreGetType, nGetScore);
}

//-------------------------------------
//- �I�u�W�F�N�g�C�x���g�̏����ݒ菈��
//-------------------------------------
void CEventObject::InitSet(MODEL model)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();	// �ʒu
	D3DXVECTOR3 rot = m_dataRot.Get();	// ����

	// ���X�V
	m_dataPosOld.Set(pos);				// �O��̈ʒu
	m_dataRotDest.Set(rot);				// �ړI�̌���

	m_nDataReuseTime.Set(1200);					// �Ďg�p����

	m_scoreGetType = CScore::GET_TYPE_RANDOM;	// �X�R�A�̎擾�n��

	m_nGetScore.Set(0);							// �X�R�A�̓����
}

//-------------------------------------
//- �I�u�W�F�N�g�C�x���g�̍Ďg�p�̏���
//-------------------------------------
void CEventObject::UpdateReuse(void)
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
	int nReuseTime = m_nDataReuseTime.Get();	// �Ďg�p����
	int nReuseCount = m_nDataReuseCount.Get();	// �Ďg�p�J�E���g
	bool bUse = m_bDataUse.Get();				// �g�p�̗L��

	if (pManagerTime->m_bDataIntCount.Get() == true)
	{
		// �Ďg�p�J�E���g�����Z
		nReuseCount++;

		// �Ďg�p�J�E���g�̔���
		if (nReuseCount >= nReuseTime)
		{
			// �Ďg�p�J�E���g��������
			nReuseCount = 0;

			// �g�p�\
			bUse = false;
		}
	}

	// ���X�V
	m_nDataReuseCount.Set(nReuseTime);	// �Ďg�p����
	m_nDataReuseCount.Set(nReuseCount);	// �Ďg�p�J�E���g
	m_bDataUse.Set(bUse);				// �g�p�̗L��
}

//-------------------------------------
//- �I�u�W�F�N�g�C�x���g�̎g�p�\�\��
//-------------------------------------
void CEventObject::AvailableDisplay(void)
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
	D3DXVECTOR3 pos = m_dataPos.Get();				// �ʒu
	int nEffectCount = m_nDataEffectCount.Get();	// �G�t�F�N�g�o���̃J�E���g

	if (pManagerTime->m_bDataIntCount.Get() == true)
	{
		// �G�t�F�N�g�̃|�C���^��錾
		CEffect *pEffect = NULL;

		// �G�t�F�N�g�J�E���g�����Z
		nEffectCount++;

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
				pEffect->m_dataSize.Set(D3DXVECTOR3(30.0f, 30.0f, 0.0f));

				// �ړ��ʂ�ݒ�
				pEffect->m_dataMove.Set(D3DXVECTOR3(0.0f, 3.0f, 0.0f));

				// �F��ݒ�i��{�F�j
				pEffect->m_dataColor.Set(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

				// �G�t�F�N�g�̐ݒ菈��
				pEffect->m_nDataLife.Set(60);
			}

		}
	}

	// ���X�V
	m_dataPos.Set(pos);						// �ʒu
	m_nDataEffectCount.Set(nEffectCount);	// �G�t�F�N�g�o���̃J�E���g
}
