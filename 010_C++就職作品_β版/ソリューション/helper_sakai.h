
//-===============================================
//-
//-	����֗̕��֐��̏����̃w�b�_�[[helper_sakai.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _HELPER_SAKAI_H_		// ���̃}�N������`����Ȃ�������
#define _HELPER_SAKAI_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

//=======================================
//=	�}�N����`
//=======================================

//-======================================
//-	�N���X��`
//-======================================

namespace HelperSakai
{
	void NormalizeAngle(D3DXVECTOR3* rot, D3DXVECTOR3* rotDest, float destSpeed);
	bool IfRangeFloat(float fData, float fMin, float fMax);
	float CalculateLength(D3DXVECTOR3 pos, D3DXVECTOR3 posTgt);

	int AddLimitStop(int nData, int nAdd, int nMin, int nMax);
	int AddLimitReturn(int nData, int nAdd, int nMin, int nMax);
}

#endif	// ��d�C���N���[�h�h�~�̏I��
