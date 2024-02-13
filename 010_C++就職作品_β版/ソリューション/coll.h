
//-===============================================
//-
//-	�����蔻��̏����̃w�b�_�[[coll.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _COLL_H_		// ���̃}�N������`����Ȃ�������
#define _COLL_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object.h"

#include "mgr_coll.h"

//-======================================
//-	�}�N����`
//-======================================

#define COLLSION_NUM_MAX		(1024)	// �����蔻��̍ő吔

//-======================================
//-	�O���錾
//-======================================

class CBoxField;
class CBoxWall;

//-======================================
//-	�N���X��`
//-======================================

// �ڐG�̃N���X
class CColl
{

public:

	// �ڐG����Ƃ̏��
	typedef struct
	{
		int nNldx;		// �ԍ�
		float fLength;	// ����
	}HitData;

	// �����ڏ��
	struct DataVisual
	{
		CBoxField* pField;
		CBoxWall* pWall;
	};

	// �����蔻����
	typedef struct
	{
		CMgrColl::TAG tag;						// �^�O
		int nNldx;								// �ԍ�
		CObject* pObj;							// �I�u�W�F�N�g�̃|�C���^

		HitData hitData[COLLSION_NUM_MAX];		// �ڐG����̐ڐG���
		int nHitNldxMax;						// �ڐG����̔ԍ��̍ő吔

		HitData hitDataTemp[COLLSION_NUM_MAX];	// �ꎞ�I�̐ڐG����̐ڐG���
		int nHitNldxMaxTemp;					// �ꎞ�I�̐ڐG����̔ԍ��̍ő吔

		D3DXVECTOR3 pos;						// �ʒu
		D3DXVECTOR3 posOld;						// �O��̈ʒu
		D3DXVECTOR3 size;						// �傫��
		D3DXVECTOR2 collVec;					// �ڐG�����x�N�g��

		DataVisual dataVisual;					// �����ڏ��
	}Data;

	CColl();
	~CColl();

	HRESULT Init(CMgrColl::TAG tag, CObject* pObj, D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);

	void Update(void);
	void Draw(void);

	static CColl* Create(CMgrColl::TAG tag, CObject* pObj, D3DXVECTOR3 pos, D3DXVECTOR3 size);

	bool Hit(CMgrColl::TAG hitTag, CMgrColl::EVENT_TYPE eventType);
	bool HitSide(CMgrColl::TAG hitTag, CMgrColl::EVENT_TYPE eventType, CMgrColl::TYPE_SXIS typeSxis);

	void SetHitData(HitData data);
	void ResetHitData(void);

	void SetIsVisualDrawStop(bool bDrawStop);

	void UpdateData(D3DXVECTOR3 pos, D3DXVECTOR3 size) { m_data.pos = pos, m_data.size = size, SetDataVisual(pos, size); }
	void UpdateData(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 size) { m_data.pos = pos, m_data.posOld = posOld, m_data.size = size, SetDataVisual(pos, size); }

	void SetData(Data data) { m_data = data; }
	Data GetData(void) { return m_data; }

	void ResetHitDataTemp(void)
	{
		ZeroMemory(&m_data.hitDataTemp[0], sizeof(m_data.hitDataTemp));
		m_data.nHitNldxMaxTemp = 0;
	}

private:

	void SetDataVisual(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	void InitSet(CMgrColl::TAG tag, CObject* pObj, D3DXVECTOR3 pos, D3DXVECTOR3 size);

	Data m_data;
};

#endif	// ��d�C���N���[�h�h�~�̏I��
