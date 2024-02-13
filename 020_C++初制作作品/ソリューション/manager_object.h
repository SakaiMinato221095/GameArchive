
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

#define FIELD_NUM_MAX			(64)	// �n�ʂ̍ő�g�p��
#define WALL_NUM_MAX			(64)	// �ǂ̍ő�g�p��
#define OBJECTX_NONE_NUM_MAX	(512)	// ���ʂȂ��I�u�W�F�N�g�̍ő�g�p��
#define EVENT_OBJECT_NUM_MAX	(512)	// �C�x���g�I�u�W�F�N�g�̍ő�g�p��
#define GARBAGE_NUM_MAX			(512)	// �S�~�̍ő�g�p��
#define GARBAGE_COLLECT_NUM_MAX	(512)	// �S�~���W�̍ő�g�p��
#define ITEM_NUM_MAX			(512)	// �A�C�e���̍ő吔
#define ENEMY_NORMAL_NUM_MAX	(512)	// �ʏ�G�̍ő�i�[��

//-======================================
//-	�O���錾
//-======================================

class CBgManager;

class CObjectXNone;
class CEventObject;
class CGarbage;
class CGarbageCollect;
class CItem;
class CEnemyNormal;
class CEnemyBoss;
class CObj3dField;
class CObj3dWall;
class CGate;
class CSkybox;

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

	static CObjectXNone * GetObjectNone(int nNum);
	static void SetObjectNone(int nNum, CObjectXNone *pObjectXNone);
	static void ReleaseObjectNone(int nNum);

	static CEventObject * GetEventObject(int nNum);
	static void SetEventObject(int nNum, CEventObject *pEventObject);
	static void ReleaseEventObject(int nNum);

	static CGarbage * GetGarbage(int nNum);
	static void SetGarbage(int nNum, CGarbage * pGarbage);
	static void ReleaseGarbage(int nNum);

	static CGarbageCollect * GetGarbageCollect(int nNum);
	static void SetGarbageCollect(int nNum, CGarbageCollect *pGarbageCollect);
	static void ReleaseGarbageCollect(int nNum);

	static CItem * GetItem(int nNum);
	static void SetItem(int nNum, CItem *pItem);
	static void ReleaseItem(int nNum);

	static void SetEnemyNormal(int nNum, CEnemyNormal *pEnemyNormal);
	static CEnemyNormal * GetEnemyNormal(int nNum);
	static void ReleaseEnemyNormal(int nNum);

	static void SetEnemyBoss(CEnemyBoss *pEnemyBoss);
	static CEnemyBoss * GetEnemyBoss(void);
	static void ReleaseEnemyBoss(void);

	static void SetGate(CGate *pGate);
	static CGate * GetGate(void);
	static void ReleaseGate(void);

	static void SetSkybox(CSkybox *pSkybox);
	static CSkybox *GetSkybox(void);
	static void ReleaseSkybox(void);

	static CObj3dWall * GetWall(int nNum);
	static void SetWall(int nNum, CObj3dWall * pWall);

private:

	HRESULT CreateAll(HWND hWnd);

	static CObjectXNone *m_apObjectXNone[OBJECTX_NONE_NUM_MAX];				// ���ʂȂ��I�u�W�F�N�g
	static CEventObject *m_apEventObject[EVENT_OBJECT_NUM_MAX];				// �C�x���g�I�u�W�F�N�g
	static CGarbage *m_apGarbage[GARBAGE_NUM_MAX];							// �S�~
	static CGarbageCollect *m_apGarbageCollect[GARBAGE_COLLECT_NUM_MAX];	// �S�~���W
	static CItem *m_apItem[ITEM_NUM_MAX];									// �A�C�e��
	static CEnemyNormal *m_apEnemyNormal[ENEMY_NORMAL_NUM_MAX];				// �ʏ�G
	static CEnemyBoss *m_pEnemyBoss;										// �{�X�G

	static CObj3dField *m_pField[FIELD_NUM_MAX];							// �t�B�[���h
	static CObj3dWall *m_pWall[WALL_NUM_MAX];								// �E�H�[��

	static CGate *m_pGate;													// �Q�[�g
	static CSkybox *m_pSkybox;												// �X�J�C�{�b�N�X

};

#endif	// ��d�C���N���[�h�h�~�̏I��
