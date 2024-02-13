
//================================================
//=
//=	�����蔻��Ǘ��̏���[mgr_coll.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "mgr_coll.h"

#include "coll.h"

#include "object.h"

#include "helper_sakai.h"

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
//-	�����蔻��Ǘ��̃R���X�g���N�^
//-------------------------------------
CMgrColl::CMgrColl()
{
	ZeroMemory(&m_apColl, sizeof(m_apColl));
	m_nNldxMax = 0;
}

//-------------------------------------
//-	�����蔻��Ǘ��̃f�X�g���N�^
//-------------------------------------
CMgrColl::~CMgrColl()
{

}

//-------------------------------------
//- �����蔻��Ǘ��̏���������
//-------------------------------------
HRESULT CMgrColl::Init(void)
{
	return S_OK;
}

//-------------------------------------
//- �����蔻��Ǘ��̏I������
//-------------------------------------
void CMgrColl::Uninit(void)
{

}

//-------------------------------------
//- �����蔻��Ǘ��̍X�V����
//-------------------------------------
void CMgrColl::Update(void)
{
}

//-------------------------------------
//- �����蔻��Ǘ��̕`�揈��
//-------------------------------------
void CMgrColl::Draw(void)
{
}

//-------------------------------------
//- �����蔻��Ǘ��̐�������
//-------------------------------------
CMgrColl * CMgrColl::Create(void)
{
	// �����蔻��Ǘ��̐���
	CMgrColl *pCollision = DBG_NEW CMgrColl;

	// �����̐����̗L���𔻒�
	if (pCollision != NULL)
	{
		// ����������
		if (FAILED(pCollision->Init()))
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

	// �����蔻��Ǘ��̃|�C���^��Ԃ�
	return pCollision;
}

//-------------------------------------
//- �ڐG����i��`�j
//-------------------------------------
bool CMgrColl::Hit(int nNldxColl, TAG hitTag, EVENT_TYPE eventType)
{
	// �ϐ��錾
	CColl* pCollMy = m_apColl[nNldxColl];					// ���g�̓����蔻����
	CColl::Data dataMy = m_apColl[nNldxColl]->GetData();	// ���g�̏��
	int nHitNldxMax = dataMy.nHitNldxMax;					// �ڐG����̍ő吔

	// �ꎞ�I�ȐڐG���̏�����
	pCollMy->ResetHitDataTemp();

	bool bHit = false;									// �ڐG�̗L��

	for (int nCount = 0; nCount < COLLSION_NUM_MAX; nCount++)
	{
		if (m_apColl[nCount] != nullptr)
		{
			CColl* pCollPair = m_apColl[nCount];					// ����̓����蔻����
			CColl::Data dataPair = m_apColl[nCount]->GetData();		// ����̏��
			TAG tagPair = dataPair.tag;								// ����̃^�O

			if (tagPair == hitTag)
			{
				if (eventType == EVENT_TYPE_TRIGGER)
				{
					bool bHitTrigger = false;

					for (int nCntHitNldx = 0; nCntHitNldx < nHitNldxMax; nCntHitNldx++)
					{
						if (nCount == dataMy.hitData[nCntHitNldx].nNldx)
						{
							bHitTrigger = true;
							break;
						}
					}

					if (bHitTrigger)
					{
						continue;
					}
				}

				// �ϐ��錾�i���擾�j
				D3DXVECTOR3 posMy = pCollMy->GetData().pos;			// ���g�̈ʒu
				D3DXVECTOR3 sizeMy = pCollMy->GetData().size;		// ���g�̑傫��

				// �ϐ��錾 (����̏��擾)
				D3DXVECTOR3 posPair = pCollPair->GetData().pos;		// ����̈ʒu
				D3DXVECTOR3 sizePair = pCollPair->GetData().size;	// ����̑傫��

				// �����蔻��
				if (hitRectangle(posMy, sizeMy, posPair, sizePair) == true)
				{
					// �ڐG�����ݒ�
					bHit = true;

					// �^�[�Q�b�g�Ƃ̋������Z�o
					float fLength = HelperSakai::CalculateLength(posMy, posPair);

					// �ڐG���ݒ菈��
					SetHit(
						pCollMy,
						nCount,
						pCollPair->GetData().pObj,
						fLength);
				}
			}

		}
	}

	return bHit;

}

//-------------------------------------
//- �ڐG����i��`�̕Ӂj
//-------------------------------------
bool CMgrColl::HitSide(int nNldxColl, CMgrColl::TAG hitTag, EVENT_TYPE eventType,CMgrColl::TYPE_SXIS typeSxis)
{
	// �ϐ��錾
	CColl* pCollMy = m_apColl[nNldxColl];					// ���g�̓����蔻����
	CColl::Data dataMy = m_apColl[nNldxColl]->GetData();	// ���g�̏��
	bool bHit = false;										// �ڐG�̗L��

	for (int nCount = 0; nCount < COLLSION_NUM_MAX; nCount++)
	{
		if (m_apColl[nCount] != nullptr)
		{
			CColl* pCollPair = m_apColl[nCount];					// ����̓����蔻����
			CColl::Data dataPair = m_apColl[nCount]->GetData();		// ����̏��
			TAG tagPair = dataPair.tag;								// ����̃^�O

			if (tagPair == hitTag)
			{
				// �ϐ��錾�i���擾�j
				D3DXVECTOR3 posMy = pCollMy->GetData().pos;			// ���g�̈ʒu
				D3DXVECTOR3 sizeMy = pCollMy->GetData().size;		// ���g�̑傫��

				// �ϐ��錾 (����̏��擾)
				D3DXVECTOR3 posPair = pCollPair->GetData().pos;		// ����̈ʒu
				D3DXVECTOR3 sizePair = pCollPair->GetData().size;	// ����̑傫��

				bool bHitColl = false;

				switch (typeSxis)
				{
				case CMgrColl::TYPE_SXIS_X:

					// X���̓����蔻��
					if (hitRectangleSide(posMy.x, sizeMy.x, posPair.x, sizePair.x) == true)
					{
						bHitColl = true;
					}

					break;

				case CMgrColl::TYPE_SXIS_Y:

					// X���̓����蔻��
					if (hitRectangleSide(posMy.y, sizeMy.y, posPair.y, sizePair.y) == true)
					{
						// �ڐG�����ݒ�
						bHitColl = true;
					}

				case CMgrColl::TYPE_SXIS_Z:

					// Z���̓����蔻��
					if (hitRectangleSide(posMy.z, sizeMy.z, posPair.z, sizePair.z) == true)
					{
						// �ڐG�����ݒ�
						bHitColl = true;
					}

					break;
				}

				if (bHitColl)
				{
					// �ڐG�����ݒ�
					bHit = true;

					// �^�[�Q�b�g�Ƃ̋������Z�o
				 	float fLength = HelperSakai::CalculateLength(posMy, posPair);

					// �ڐG���ݒ菈��
					SetHit(
						pCollMy,
						nCount,
						pCollPair->GetData().pObj,
						fLength);
				}
			}
		}
	}

	return bHit;
}

//-------------------------------------
//- �����蔻��Ǘ��̐ݒ菈��
//-------------------------------------
int CMgrColl::Set(CColl *pColl)
{
	for (int nCount = 0; nCount < COLLSION_NUM_MAX; nCount++)
	{
		if (m_apColl[nCount] == NULL)
		{
			m_apColl[nCount] = pColl;

			m_nNldxMax++;

			return nCount;
		}
	}

	return -1;
}

//-------------------------------------
//- �����蔻��Ǘ��̏������ݒ菈��
//-------------------------------------
void CMgrColl::Reset(int nNldx)
{
	m_apColl[nNldx] = nullptr;

	m_nNldxMax--;
}

//-------------------------------------
//- �ڐG���ݒ菈��
//-------------------------------------
void CMgrColl::SetHit(CColl* pCollMy,int nNldx,CObject* pObjPair,float fLength)
{
	// �ڐG����̓����蔻�����ݒ�
	CColl::HitData hitData = {};
	
	hitData.nNldx = nNldx;
	hitData.fLength = fLength;

	// �ڐG����̔ԍ�����
	pCollMy->SetHitData(hitData);
}

//-------------------------------------
//- �����蔻��Ǘ��̋�`�̓����蔻��
//-------------------------------------
bool CMgrColl::hitRectangle(D3DXVECTOR3 posMy, D3DXVECTOR3 sizeMy, D3DXVECTOR3 posPair, D3DXVECTOR3 sizePair)
{
	if (posMy.x + sizeMy.x >= posPair.x - sizePair.x &&
		posMy.x - sizeMy.x <= posPair.x + sizePair.x &&
		posMy.y + sizeMy.y >= posPair.y - sizePair.y &&
		posMy.y - sizeMy.y <= posPair.y + sizePair.y &&
		posMy.z + sizeMy.z >= posPair.z - sizePair.z &&
		posMy.z - sizeMy.z <= posPair.z + sizePair.z)
	{
		return true;
	}

	return false;
}

//-------------------------------------
//- �����蔻��Ǘ��̕ӂ̓����蔻��
//-------------------------------------
bool CMgrColl::hitRectangleSide(float fPos, float fSize, float fPosPair, float fSizePair)
{
	if (fPos + fSize >= fPosPair - fSizePair &&
		fPos - fSize <= fPosPair + fSizePair)
	{
		return true;
	}

	return false;
}