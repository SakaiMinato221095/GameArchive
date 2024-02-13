
//-===============================================
//=
//= �K�w�\����X�t�@�C���I�u�W�F�N�g�����̃w�b�^�[[object_model.h]
//= Author Sakai Minato
//=
//-===============================================

//=======================================
//=	��d�C���N���[�h�h�~
//=======================================

#ifndef _OBJECT_MODEL_H_	// ���̃}�N������`����Ȃ�������
#define _OBJECT_MODEL_H_	// ��d�C���N���[�h�X�q�̃}�N�����`

//=======================================
//=	�C���N���[�h
//=======================================

#include "data.h"

//-======================================
//-	�}�N����`
//-======================================

#define MODEL_PARTS_MAX	(32)	// ���f���p�[�c�̍ő吔
#define MODEL_NUM_MAX	(32)	// ���f���̍ő吔

//=======================================
//=	�N���X��`
//=======================================

// �K�w�\����X�t�@�C���I�u�W�F�N�g�̃N���X
class CObjectModel
{
public:
	
	// ���f���̎��
	typedef enum
	{
		MODEL_TYPE_PLAYER_SEARCH = 0,	// �T���v���C���[
		MODEL_TYPE_PLAYER_BATTLE,		// �퓬�v���C���[
		MODEL_TYPE_SAMPLE,				// �����j���O�}��
		MODEL_TYPE_MAX
	}MODEL_TYPE;

	// ���f���p�[�c�̏��
	typedef struct
	{
		int nIndex;				// �p�[�c�̔ԍ�
		int nParent;			// �e�̔ԍ�
		char aFileName[256];	// �t�@�C���̖��O

		D3DXVECTOR3 pos;		// �ʒu���
		D3DXVECTOR3 rot;		// �������

	}ModelParts;

	// ���f���̏��
	typedef struct
	{
		ModelParts modelParts[MODEL_PARTS_MAX];		// ���f���p�[�c�̏��
		int nPartsNum;								// �p�[�c��
	}Model;

	CObjectModel();
	~CObjectModel();

	static HRESULT Load(void);

	HRESULT Init(MODEL_TYPE modelType, int nCount);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjectModel * Create(MODEL_TYPE modelType, int nCount);

	void SetParent(CObjectModel ** pObjectModel, MODEL_TYPE modelType, int nCount);

	D3DXMATRIX GetMtxWorld(void);

	static void SetFile(MODEL_TYPE modelType);
	static int GetPartsNum(MODEL_TYPE modelType);

	static CDataInt m_nDataModelNldx[MODEL_TYPE_MAX][MODEL_PARTS_MAX];	// ���f���̔ԍ�

	CDataD3DXVECTOR3 m_dataPos;
	CDataD3DXVECTOR3 m_dataMotionPos;

	CDataD3DXVECTOR3 m_dataRot;
	CDataD3DXVECTOR3 m_dataMotionRot;

private:

	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X

	CObjectModel *m_pParent;				// �e���f���̃|�C���^

	MODEL_TYPE m_modelType;					// �����̃��f���̎��
	int m_nPartsNum;						// �����̃p�[�c�ԍ�

	static Model m_model[MODEL_NUM_MAX];	// ���f���̏��
};

#endif	// ��d�C���N���[�h�h�~�̏I��