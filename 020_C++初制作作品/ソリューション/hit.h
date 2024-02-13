
//-===============================================
//-
//-	�ڐG�̏����̃w�b�_�[[hit.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _HIT_H_		// ���̃}�N������`����Ȃ�������
#define _HIT_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�N���X��`
//-======================================

// �ڐG�̃N���X
class CHit
{

public:

	CHit();
	~CHit();

	static bool hitRectangle(D3DXVECTOR3 posMy, D3DXVECTOR3 sizeMy,D3DXVECTOR3 posPair, D3DXVECTOR3 sizePair);
	static bool hitRectangleRot(D3DXVECTOR3 posMy, D3DXVECTOR3 sizeMy, D3DXVECTOR3 rot, D3DXVECTOR3 posPair, D3DXVECTOR3 sizePair, D3DXVECTOR3 rotPair);
	static bool hitRectangleSide(float fPos, float fSize, float fPosPair, float fSizePair);

private:

};

#endif	// ��d�C���N���[�h�h�~�̏I��
