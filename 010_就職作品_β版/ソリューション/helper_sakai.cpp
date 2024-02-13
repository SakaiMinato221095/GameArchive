
//================================================
//=
//=	����֗̕��֐�����[helper_sakai.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "helper_sakai.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

//-------------------------------------
//-	�p�x�̐��K��
//-------------------------------------
void HelperSakai::NormalizeAngle(D3DXVECTOR3* rot, D3DXVECTOR3* rotDest, float destSpeed)
{
	// �ړI�̌����̕␳
	if (rotDest->y > D3DX_PI)
	{
		rotDest->y += -D3DX_PI * 2;
	}
	else if (rotDest->y < -D3DX_PI)
	{
		rotDest->y += D3DX_PI * 2;
	}

	// �����̌������Z�o
	float rotDiff = rotDest->y - rot->y;

	// �����̌�����␳
	if (rotDiff > D3DX_PI)
	{
		rotDiff += -D3DX_PI * 2;
	}
	else if (rotDiff < -D3DX_PI)
	{
		rotDiff += D3DX_PI * 2;
	}

	// �p�x�̈ړ�
	rot->y += rotDiff * destSpeed;

	// �����̕␳
	if (rot->y > D3DX_PI)
	{
		rot->y += -D3DX_PI * 2;
	}
	else if (rot->y < -D3DX_PI)
	{
		rot->y += D3DX_PI * 2;
	}

}

//-------------------------------------
//-	�͈͎w���IF���i���������j
//-------------------------------------
bool HelperSakai::IfRangeFloat(float fData,float fMin, float fMax)
{
	if (fData > fMin &&
		fData < fMax)
	{
		return true;
	}

	return false;
}

//-------------------------------------
//-	�ΏۂƂ̋������Z�o
//-------------------------------------
float HelperSakai::CalculateLength(D3DXVECTOR3 pos, D3DXVECTOR3 posTgt)
{
	// �^�[�Q�b�g�Ƃ̋����𔻒�
	float fLengthTgtSquared = ((posTgt.x - pos.x) * (posTgt.x - pos.x) +
							   (posTgt.y - pos.y) * (posTgt.y - pos.y) +
							   (posTgt.z - pos.z) * (posTgt.z - pos.z));

	// ������Ԃ�
	return std::sqrt(fLengthTgtSquared);
}

//-------------------------------------
//-	�ő�l�w��̉��Z�����i�ő�l���ɒ�~�j
//-------------------------------------
int HelperSakai::AddLimitStop(int nData, int nAdd, int nMin,int nMax)
{
	// �Z�o
	int nDataCal = nData + nAdd;

	// �ő�l�E�ŏ��l�̔���
	if (nDataCal > nMax)
	{
		nDataCal = nMax;
	}
	else if(nDataCal < nMin)
	{
		nDataCal = nMin;
	}

	return nDataCal;
}

//-------------------------------------
//-	�ő�l�w��̉��Z�����i�ő�l���ɔ��]�j
//-------------------------------------
int HelperSakai::AddLimitReturn(int nData, int nAdd, int nMin, int nMax)
{
	// �Z�o
	int nDataCal = nData + nAdd;

	// �ő�l�E�ŏ��l�̔���
	if (nDataCal > nMax)
	{
		nDataCal = nDataCal - nMax;
	}
	else if (nDataCal < nMin)
	{
		nDataCal = nDataCal + nMin;
	}

	return nDataCal;
}

