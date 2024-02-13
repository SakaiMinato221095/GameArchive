
//-===============================================
//-
//-	�S�~�t�@�C�������̃w�b�_�[[file_grabage.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _FILE_GRABAGE_H_		// ���̃}�N������`����Ȃ�������
#define _FILE_GRABAGE_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "garbage.h"

//-======================================
//-	�}�N����`
//-======================================

#define FILE_DATA_MAX	(256)	// �g�p�f�[�^�̍ő吔

//-======================================
//-	�N���X��`
//-======================================

class CFileGarbage
{

public:

	typedef struct
	{
		int modelNldx;
		bool bNoLoad;

		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
	}FileData;

	typedef enum
	{
		TXT_NORMAL_000 = 0,	// �ʏ���ʂȂ��I�u�W�F�N�g_000�̃e�L�X�g
	}TXT;

	CFileGarbage();
	~CFileGarbage();

	static void Save(CFileGarbage::TXT txtType);
	static void Load(CFileGarbage::TXT txtType);

	static void Locate(void);
	static void ObjCheck(void);
	static void ObjRecall(void);

private:

	static int m_nSetMax;
	static FileData m_aFileData[FILE_DATA_MAX];
};

#endif	// ��d�C���N���[�h�h�~�̏I��
