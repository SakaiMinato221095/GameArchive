
//-===============================================
//-
//-	�I�u�W�F�N�g�G�t�F�N�g�̏���[effect_object.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "effect_object.h"

#include "renderer.h"
#include "manager.h"

#include "manager_model.h"
#include "time_stop.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�R���X�g��`
//=======================================

// �G�t�F�N�g�I�u�W�F�N�g�̃��f���̃R���X�g��`
const char *pModelEffectObject[] =
{
	"data\\MODEL\\Coin000.x",	// �R�C���̃��f��
	"data\\MODEL\\bin.x",		// �r
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

int CEffectObject::m_nModelNldx[MODEL_MAX] = {};		// ���f���̔ԍ�

//-------------------------------------
//-	�I�u�W�F�N�g�G�t�F�N�g�̃R���X�g���N�^
//-------------------------------------
CEffectObject::CEffectObject(int nPriority) : CObjectX(nPriority)
{

}

//-------------------------------------
//-	�I�u�W�F�N�g�G�t�F�N�g�̃f�X�g���N�^
//-------------------------------------
CEffectObject::~CEffectObject()
{

}

//-------------------------------------
//- �I�u�W�F�N�g�G�t�F�N�g�̃��f���ǂݍ���
//-------------------------------------
HRESULT CEffectObject::Load(void)
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
		// ���f���ԍ��̎擾�i���f���̊����j
		m_nModelNldx[nCount] = pManagerModel->Regist(pModelEffectObject[nCount]);

		// ���f���̓ǂݍ��ݐ����̗L�����m�F
		if (m_nModelNldx[nCount] == -1)
		{
			// ���s���ɏ����������𔲂���
			return E_FAIL;
		}
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �I�u�W�F�N�g�G�t�F�N�g�̓ǂݍ��񂾃��f���j��
//-------------------------------------
void CEffectObject::Unload(void)
{

}

//-------------------------------------
//- �I�u�W�F�N�g�G�t�F�N�g�̏���������
//-------------------------------------
HRESULT CEffectObject::Init(MODEL model)
{
	// ���f���Ǘ��̐���
	CManagerModel *pManagerModel = CManager::GetManagerModel();

	// ���f���Ǘ��̗L���𔻒�
	if (pManagerModel == NULL)
	{
		// �����𔲂���
		return E_FAIL;
	}

	// �I�u�W�F�N�g�G�t�F�N�g�̃��f������
	BindModel(m_nModelNldx[model],model);

	//	�I�u�W�F�N�g�G�t�F�N�g�̏����� if(�����������̗L���𔻒�)
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �I�u�W�F�N�g�G�t�F�N�g�̏I������
//-------------------------------------
void CEffectObject::Uninit(void)
{
	// �I�u�W�F�N�g�G�t�F�N�g�̏I��
	CObjectX::Uninit();
}

//-------------------------------------
//- �I�u�W�F�N�g�G�t�F�N�g�̍X�V����
//-------------------------------------
void CEffectObject::Update(void)
{
	// �I�u�W�F�N�g�G�t�F�N�g�̉��Z����
	Add();

	// �I�u�W�F�N�g�G�t�F�N�g�̍X�V����
	CObjectX::Update();
}

//-------------------------------------
//- �I�u�W�F�N�g�G�t�F�N�g�̕`�揈��
//-------------------------------------
void CEffectObject::Draw(void)
{
	// �I�u�W�F�N�g�G�t�F�N�g�̕`�揈��
	CObjectX::Draw();
}

//-------------------------------------
//- �I�u�W�F�N�g�G�t�F�N�g�̐�������
//-------------------------------------
CEffectObject *CEffectObject::Create(MODEL model)
{
	// �I�u�W�F�N�g�G�t�F�N�g�̃|�C���^��錾
	CEffectObject *pCEffectObject = DBG_NEW CEffectObject(3);

	// �����̐����̗L���𔻒�
	if (pCEffectObject != NULL)
	{
		// ����������
		if (FAILED(pCEffectObject->Init(model)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCEffectObject == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �I�u�W�F�N�g�G�t�F�N�g�̃|�C���^��Ԃ�
	return pCEffectObject;
}

//-------------------------------------
//- �I�u�W�F�N�g�G�t�F�N�g�̐ݒ菈��
//-------------------------------------
void CEffectObject::Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXVECTOR3 move,D3DXVECTOR3 moveMax)
{
	// �ʒu���ݒ�
	m_dataPos.Set(pos);
	m_dataPosOld.Set(pos);

	// �傫���̐ݒ�
	m_dataSize.Set(size);
	m_dataSizeHold.Set(size);

	// �����̐ݒ�
	m_dataRot.Set(rot);
	m_dataRotDest.Set(rot);

	// �ړ��ʂ̐ݒ�
	m_dataMove.Set(move);

	// �ړ��ʂ̍ő�l
	m_dataMoveMax.Set(moveMax);
	
	// �ړ��ʂ̒~�ϒl
	m_dataMoveAcu.Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// ��]�ʂ�ݒ�
	m_dataAddRot.Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//-------------------------------------
//- �I�u�W�F�N�g�G�t�F�N�g�̉��Z����
//-------------------------------------
void CEffectObject::Add(void)
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
	D3DXVECTOR3 pos = m_dataPos.Get();		// �ʒu
	D3DXVECTOR3 move = m_dataMove.Get();	// �ړ���

	D3DXVECTOR3 moveAcu = m_dataMoveAcu.Get();	// �ړ��ʂ̒~�ϒl
	D3DXVECTOR3 moveMax = m_dataMoveMax.Get();	// �ړ��ʂ̍ő�l

	D3DXVECTOR3 addRot = m_dataAddRot.Get();	// ��]��

	// �~�ϒl�̔���
	if (moveAcu.x >= moveMax.x &&
		moveAcu.y >= moveMax.y &&
		moveAcu.z >= moveMax.z)
	{		
		// ���Ԕ{���̌v�Z
		D3DXVECTOR3 addRotTime = pManagerTime->CalRate(addRot);

		// ��]����
		AddRot(addRotTime);

		// �I�u�W�F�N�g�G�t�F�N�g�̌�������
		if (Sub() == true)
		{
			return;
		}
	}
	else
	{
		// ���Ԕ{���̌v�Z
		D3DXVECTOR3 addRotTime = pManagerTime->CalRate(addRot);

		// ��]����
		AddRot(addRotTime);

		// ���Ԕ{���̌v�Z
		D3DXVECTOR3 addMoveTime = pManagerTime->CalRate(move);

		// �ʒu�Ɉړ��ʂ����Z
		pos += addMoveTime;

		// �ړ��ʂ̒~�ϒl�Ɉړ��ʂ����Z
		moveAcu += addMoveTime;

		// �~�ϒl�̔���
		if (moveAcu.x >= moveMax.x &&
			moveAcu.y >= moveMax.y &&
			moveAcu.z >= moveMax.z)
		{
			// ��]�ʂ�ݒ�
			addRot = D3DXVECTOR3(0.0f, -0.2f, 0.0f);

			// �̗͂�ݒ�
			m_nDataLife.Set(10);
		}
	}

	// �ʒu�̔��f
	m_dataPos.Set(pos);		// �ʒu
	m_dataMove.Set(move);	// �ړ���

	m_dataMoveAcu.Set(moveAcu);	// �ړ��ʂ̒~�ϒl
	m_dataMoveMax.Set(moveMax);	// �ړ��ʂ̍ő�l

	m_dataAddRot.Set(addRot);	// ��]��
}

//-------------------------------------
//- �I�u�W�F�N�g�G�t�F�N�g�̌�������
//-------------------------------------
bool CEffectObject::Sub(void)
{
	// ���ԊǗ��̏����擾
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// ���ԊǗ��擾�̗L���𔻒�
	if (pManagerTime == NULL)
	{
		// �����𔲂���
		return false;
	}

	// �ϐ���錾�i���擾�j
	D3DXVECTOR3 sizeHold = m_dataSizeHold.Get();	// �ێ�����T�C�Y

	D3DXVECTOR3 moveAcu = m_dataMoveAcu.Get();		// �ړ��ʂ̒~�ϒl
	D3DXVECTOR3 moveMax = m_dataMoveMax.Get();		// �ړ��ʂ̍ő�l

	D3DXVECTOR3 size = m_dataSize.Get();			// �傫��
	int nLife = m_nDataLife.Get();					// �̗�

	// ���Ԕ{���̌v�Z�i�T�C�Y�̌����ʎZ�o�j
	float nTimeEffectSizeX = pManagerTime->CalRate(sizeHold.x / nLife);
	float nTimeEffectSizeY = pManagerTime->CalRate(sizeHold.y / nLife);

	// �傫�������炷
	size.x -= nTimeEffectSizeX;
	size.y -= nTimeEffectSizeY;

	// �����J�E���g�̗L���𔻒�
	if (pManagerTime->m_bDataIntCount.Get() == true)
	{
		// �ێ���������X�V
		sizeHold = size;

		// �̗͂����炷
		nLife--;
	}

	// �̗͂̔���
	if (nLife <= 0)
	{
		// �I������
		Uninit();

		// ������Ԃ�
		return true;
	}

	// ���X�V
	m_dataSize.Set(size);			// �傫��
	m_dataSizeHold.Set(sizeHold);	// �ێ�����傫��
	m_nDataLife.Set(nLife);			// �̗�

	// ���s��Ԃ�
	return false;
}