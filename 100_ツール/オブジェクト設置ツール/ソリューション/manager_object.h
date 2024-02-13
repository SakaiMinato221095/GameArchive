
//-===============================================
//-
//-	�I�u�W�F�N�g�Ǘ������̃w�b�_�[[manager_object.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _MANAGER_OBJECT_H_		// ���̃}�N������`����Ȃ�������
#define _MANAGER_OBJECT_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "data.h"

//-======================================
//-	�}�N����`
//-======================================

#define OBJECTX_NONE_NUM_MAX	(256)	// ���ʂȂ��I�u�W�F�N�g�̍ő�i�[��
#define EVENT_OBJECT_NUM_MAX	(256)	// �C�x���g�I�u�W�F�N�g�̍ő�i�[��
#define GARBAGE_NUM_MAX			(256)	// �S�~�̍ő�i�[��
#define GARBAGE_COLLECT_NUM_MAX	(256)	// �S�~���W�̍ő�g�p��
#define ITEM_NUM_MAX			(256)	// �A�C�e���̍ő�i�[��
#define ENEMY_NORMAL_NUM_MAX	(256)	// �ʏ�G�̍ő�i�[��
#define ENEMY_PIN_NUM_MAX		(256)	// �G�l�~�[�s���̍ő�i�[��
#define FIELD_NUM_MAX			(64)	// �n�ʂ̍ő�g�p��

//-======================================
//-	�O���錾
//-======================================

class CField;

class CObjectXNone;
class CEventObject;
class CGarbage;
class CGarbageCollect;
class CItem;
class CEnemyNormal;
class CEnemyPin;

//-======================================
//-	�N���X��`
//-======================================

class CManagerObject
{

public:

	CManagerObject();
	virtual ~CManagerObject();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CField *GetField(void);

	static CObjectXNone * GetObjectNone(int nNum);
	static void SetObjectNone(int nNum, CObjectXNone *pObjectXNone);
	static CEventObject * GetEventObject(int nNum);
	static void SetEventObject(int nNum, CEventObject *pEventObject);
	static CItem * GetItem(int nNum);
	static void SetGarbage(int nNum, CGarbage *pGarbage);
	static CGarbage * GetGarbage(int nNum);

	static CGarbageCollect * GetGarbageCollect(int nNum);
	static void SetGarbageCollect(int nNum, CGarbageCollect *pGarbageCollect);
	static void ReleaseGarbageCollect(int nNum);

	static void SetItem(int nNum, CItem *pItem);
	static CEnemyNormal * GetEnemyNormal(int nNum);
	static void SetEnemyNormal(int nNum, CEnemyNormal *pEnemyNormal);
	static CEnemyPin * GetEnemyPin(int nNum);
	static void SetEnemyPin(int nNum, CEnemyPin *pEnemyPin);
private:

	HRESULT CreateAll(HWND hWnd);

	static CField *m_pField[FIELD_NUM_MAX];									// �t�B�[���h
	static CObjectXNone *m_apObjectXNone[OBJECTX_NONE_NUM_MAX];				// ���ʂȂ��I�u�W�F�N�g
	static CEventObject *m_apEventObject[EVENT_OBJECT_NUM_MAX];				// �C�x���g�I�u�W�F�N�g
	static CGarbage *m_apGarbage[GARBAGE_NUM_MAX];							// �S�~
	static CGarbageCollect *m_apGarbageCollect[GARBAGE_COLLECT_NUM_MAX];	// �S�~���W
	static CItem *m_apItem[ITEM_NUM_MAX];									// �A�C�e��
	static CEnemyNormal *m_apEnemyNormal[ENEMY_NORMAL_NUM_MAX];				// �ʏ�G
	static CEnemyPin *m_apEnemyPin[ENEMY_PIN_NUM_MAX];						// �G�l�~�[�s��
};

#endif	// ��d�C���N���[�h�h�~�̏I��
