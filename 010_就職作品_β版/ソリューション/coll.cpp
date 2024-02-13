
//================================================
//=
//=	�����蔻��̏���[coll.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "coll.h"

#include "manager.h"

#include "box_field.h"
#include "box_wall.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//=	�R���X�g��`
//=======================================

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

//-------------------------------------
//-	�����蔻��̃R���X�g���N�^
//-------------------------------------
CColl::CColl()
{
	ZeroMemory(&m_data, sizeof(m_data));

	// �ԍ��̏����l����
	m_data.nNldx = -1;

	// �ڐG����ԍ��̏����l����
	for (int nCnt = 0; nCnt < COLLSION_NUM_MAX; nCnt++)
	{
		m_data.hitData[nCnt].nNldx = -1;
	}
}

//-------------------------------------
//-	�����蔻��̃f�X�g���N�^
//-------------------------------------
CColl::~CColl()
{

}

//-------------------------------------
//- �����蔻��̏���������
//-------------------------------------
HRESULT CColl::Init(CMgrColl::TAG tag, CObject* pObj, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �����蔻��̃|�C���^�擾
	CMgrColl *pMgrColl = CManager::GetInstance()->GetMgrColl();

	// �����蔻��̗L���𔻒�
	if (pMgrColl == NULL)
	{
		// �����𔲂���
		return false;
	}

	// �����蔻��̏��𐶐�
	m_data.dataVisual.pField = CBoxField::Create();

	if (m_data.dataVisual.pField != nullptr)
	{
		m_data.dataVisual.pField->InitSet(
			pos + D3DXVECTOR3(0.0f, 3.0f, 0.0f),
			size,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			D3DXVECTOR2(1.0f, 1.0f));

		m_data.dataVisual.pField->SetIsDrawStop(true);
	}

	// �����蔻��̕ǂ𐶐�
	m_data.dataVisual.pWall = CBoxWall::Create();

	if (m_data.dataVisual.pWall != nullptr)
	{
		m_data.dataVisual.pWall->InitSet(
			pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			size,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			D3DXVECTOR2(1.0f, 1.0f));

		m_data.dataVisual.pWall->SetIsDrawStop(true);
	}

	// �����蔻��Ǘ��ɐݒ菈��
	m_data.nNldx = pMgrColl->Set(this);

	// �����ݒ菈��
	InitSet(tag, pObj,pos, size);

	return S_OK;
}

//-------------------------------------
//- �����蔻��̏I������
//-------------------------------------
void CColl::Uninit(void)
{
	// �����蔻��̃|�C���^�擾
	CMgrColl *pMgrColl = CManager::GetInstance()->GetMgrColl();

	// �����蔻��̗L���𔻒�
	if (pMgrColl == NULL)
	{
		// �����𔲂���
		return;
	}

	if (m_data.dataVisual.pField != nullptr)
	{
		m_data.dataVisual.pField->Uninit();
		m_data.dataVisual.pField = nullptr;
	}

	if (m_data.dataVisual.pWall != nullptr)
	{
		m_data.dataVisual.pWall->Uninit();
		m_data.dataVisual.pWall = nullptr;
	}

	// �����蔻��Ǘ��ɐݒ菈��
	pMgrColl->Reset(m_data.nNldx);
}

//-------------------------------------
//- �����蔻��̍X�V����
//-------------------------------------
void CColl::Update(void)
{

}

//-------------------------------------
//- �����蔻��̕`�揈��
//-------------------------------------
void CColl::Draw(void)
{
}


//-------------------------------------
//- �����蔻��̐�������
//-------------------------------------
CColl* CColl::Create(CMgrColl::TAG tag, CObject* pObj, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �����蔻��̐���
	CColl *pCollision = DBG_NEW CColl;

	// �����̐����̗L���𔻒�
	if (pCollision != NULL)
	{
		// ����������
		if (FAILED(pCollision->Init(tag, pObj,pos,size)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCollision == NULL)
	{// ���s��

	 // �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �����蔻��̃|�C���^��Ԃ�
	return pCollision;
}

//-------------------------------------
//- �����蔻��̐ڐG�����i��`�j
//-------------------------------------
bool CColl::Hit(CMgrColl::TAG hitTag,CMgrColl::EVENT_TYPE eventType)
{
	// �����蔻��̃|�C���^�擾
	CMgrColl *pMgrColl = CManager::GetInstance()->GetMgrColl();		

	// �����蔻��̗L���𔻒�
	if (pMgrColl == NULL)
	{
		// �����𔲂���
		return false;
	}

	// �ϐ��錾
	bool bHitTgt = false;	// �ړI�̐ڐG�̗L��

	// �����蔻��Ǘ��̐ڐG����
	bHitTgt = pMgrColl->Hit(m_data.nNldx, hitTag, eventType);

	return bHitTgt;
}

//-------------------------------------
//- �����蔻��̐ڐG�����i��`�̕Ӂj
//-------------------------------------
bool CColl::HitSide(CMgrColl::TAG hitTag,CMgrColl::EVENT_TYPE eventType, CMgrColl::TYPE_SXIS typeSxis)
{
	// �����蔻��̃|�C���^�擾
	CMgrColl* pMgrColl = CManager::GetInstance()->GetMgrColl();

	// �����蔻��̗L���𔻒�
	if (pMgrColl == NULL)
	{
		// �����𔲂���
		return false;
	}

	// �ϐ��錾
	bool bHitTgt = false;	// �ړI�̐ڐG�̗L��

	// �����蔻��Ǘ��̐ڐG����
	bHitTgt = pMgrColl->Hit(m_data.nNldx, hitTag, eventType);

	return bHitTgt;
}

//-------------------------------------
//- �����蔻��̐ڐG���̐ݒ菈��
//-------------------------------------
void CColl::SetHitData(HitData data)
{
	// �ϐ��錾�i���擾�j
	int nHitNumMax = m_data.nHitNldxMax;			// ���݂̍ő�ڐG��
	int nHitNumMaxTemp = m_data.nHitNldxMaxTemp;	// �ꎞ�I�ȍő�ڐG��

	for (int nCount = 0; nCount < nHitNumMax; nCount++)
	{
		if (data.nNldx == m_data.hitData[nCount].nNldx)
		{
			m_data.nHitNldxMax--;

			break;
		}
	}

	// �ڐG����̓����蔻�������
	m_data.hitData[nHitNumMax] = data;
	m_data.hitDataTemp[nHitNumMaxTemp] = data;

	// �ő�ڐG�������Z
	m_data.nHitNldxMax++;
	m_data.nHitNldxMaxTemp++;
}

//-------------------------------------
//- �����蔻��̐ڐG���̃��Z�b�g����
//-------------------------------------
void CColl::ResetHitData(void)
{
	// �ϐ��錾�i���擾�j
	int nHitNum = m_data.nHitNldxMax;	// ���݂̍ő�ڐG��

	for (int nCount = 0; nCount < nHitNum; nCount++)
	{
		// �ڐG�ԍ��̏�����
		m_data.hitData[nHitNum].nNldx = -1;
	}

	// �ڐG�ő吔�̏�����
	m_data.nHitNldxMax = 0;
}

//-------------------------------------
//- �����蔻��̌����ڂ̕`��ݒ�
//-------------------------------------
void CColl::SetIsVisualDrawStop(bool bDrawStop)
{
	if (m_data.dataVisual.pField != nullptr)
	{
		m_data.dataVisual.pField->SetIsDrawStop(bDrawStop);
	}

	if (m_data.dataVisual.pWall != nullptr)
	{
		m_data.dataVisual.pWall->SetIsDrawStop(bDrawStop);
	}
}

//-------------------------------------
//- �����蔻��̌����ڐݒ菈��
//-------------------------------------
void CColl::SetDataVisual(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	if (m_data.dataVisual.pField != nullptr)
	{
		CObject3d::VtxData vtxData = m_data.dataVisual.pField->GetVtxData();
		vtxData.pos = pos + D3DXVECTOR3(0.0f, size.y * 0.5f, 0.0f);
		vtxData.size = size;
		m_data.dataVisual.pField->SetVtxData(vtxData);
	}

	if (m_data.dataVisual.pWall != nullptr)
	{
		CObject3d::VtxData vtxData = m_data.dataVisual.pWall->GetVtxData();
		vtxData.pos = pos;
		vtxData.size = size;
		m_data.dataVisual.pWall->SetVtxData(vtxData);
	}
}

//-------------------------------------
//- �����蔻��̏����ݒ菈��
//-------------------------------------
void CColl::InitSet(CMgrColl::TAG tag, CObject* pObj,D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_data.tag = tag;
	m_data.pObj = pObj;
	m_data.pos = pos;
	m_data.size = size;
}

