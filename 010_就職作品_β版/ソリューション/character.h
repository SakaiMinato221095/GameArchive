
//-===============================================
//-
//-	�L�����N�^�[�����̃w�b�_�[[character.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _CHARACTER_H_		// ���̃}�N������`����Ȃ�������
#define _CHARACTER_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object.h"

#include "model.h"
#include "motion.h"

//=======================================
//=	�}�N����`
//=======================================

//-======================================
//-	�O���錾
//-======================================

//-======================================
//-	�N���X��`
//-======================================

class CCharacter : public CObject
{

public:

	struct Data
	{
		D3DXVECTOR3 pos;		// �ʒu

		D3DXVECTOR3 rot;		// ����
	};

	CCharacter();
	~CCharacter();

	HRESULT Init(CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nMotionStateMax);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CCharacter* Create(CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nMotionStateMax);

	void UpdateData(D3DXVECTOR3 pos, D3DXVECTOR3 rot) {

		m_data.pos = pos; 
		m_data.rot = rot;

		for (int nCnt = 0; nCnt < MODEL_PARTS_MAX; nCnt++)
		{
			if (m_apModel[nCnt] != nullptr)
			{
				m_apModel[nCnt]->SetMatrix();
			}
		};
	}

	CMotion* GetMotion(void) { return m_pMotion; }
	CModel* GetModel(int nNumParts) { return m_apModel[nNumParts]; }

	void SetColorAll(D3DXCOLOR color) {
		for (int nCnt = 0; nCnt < MODEL_PARTS_MAX; nCnt++)
		{
			if (m_apModel[nCnt] != nullptr)
			{
				m_apModel[nCnt]->SetColor(color);
			}
		};}

private:

	void SetMatrix(void);

	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X

	CModel* m_apModel[MODEL_PARTS_MAX];		// ���f���i�p�[�c�j�̃|�C���^
	int m_nNumModel;						// ���f���i�p�[�c�j�̑���

	CMotion* m_pMotion;						// ���[�V�����̃|�C���^

	Data m_data;							// ���
};

#endif	// ��d�C���N���[�h�h�~�̏I��
