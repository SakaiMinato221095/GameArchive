
//-===============================================
//-
//-	�I�u�W�F�N�g�t�@�C������[map_object_x.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "map_object_x.h"

#include "objectx_none.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//= �R���X�g��`
//=======================================

// �ʏ�G�̃e�L�X�g�̃R���X�g��`
const char* pTxtObjectX[] =
{
	"data\\TXT\\Object\\ObjectNone_000.txt"		// �I�u�W�F�N�g_000�̃e�L�X�g
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CMapObjectX::CMapObjectX()
{
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CMapObjectX::~CMapObjectX()
{

}

//-------------------------------------
//- �I�u�W�F�N�g�t�@�C���̏����o������
//-------------------------------------
void CMapObjectX::Save(CMapObjectX::TXT txtType)
{

}

//-------------------------------------
//- �I�u�W�F�N�g�t�@�C���̓ǂݍ��ݏ���
//-------------------------------------
void CMapObjectX::Load(CMapObjectX::TXT txtType)
{
	//�ϐ��錾
	FILE* pFile;	// �t�@�C���̃|�C���^

	// �t�@�C���̏�����
	pFile = fopen(pTxtObjectX[txtType], "r");

	// �t�@�C���̗L���𔻒�
	if (pFile != NULL)
	{
		// �ϐ��錾
		char aFileData[256] = { 0 };				// �t�@�C���̕��͂��i�[
		CObjectXNone* pObjectNone = nullptr;		// �I�u�W�F�N�g�̃|�C���^

		while (true)
		{
			// �������ǂݍ���
			fgets(aFileData, 256, pFile);

			// ���������ǂݍ���
			for (int nCount = 0; nCount < 256; nCount++)
			{
				// �R�����g�𔻒�
				if (aFileData[nCount] == '#')
				{
					// �R�����g������
					memset(&aFileData[nCount], NULL, sizeof(256 - nCount));
					break;
				}
			}

			if (strstr(aFileData, "MODEL") != NULL)
			{
				if (strstr(aFileData, "=") != NULL)
				{
					// �G�̐�������
					pObjectNone = CObjectXNone::Create((CObjectXNone::MODEL)0, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					// �ϐ��錾
					char aTenp[2][256] = {};	// �S�~����	
					int nValue = 0;				// ���l

					// ���l�����o��
					sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nValue);

					// ���f���ԍ��̎擾
					int nModelNldx = CObjectXNone::GetModelData(nValue).nModelNldx;

					// ���f������
					pObjectNone->BindModel(nModelNldx, nValue);
				}
			}

			if (strstr(aFileData, "POS") != NULL)
			{
				// ����̕����𔻒�
				if (strstr(aFileData, "=") != NULL)
				{
					// �ϐ��錾
					char aTenp[3][256] = {};	// �S�~����	
					float fPosX = 0.0f;			// �ʒu�iX�j
					float fPosY = 0.0f;			// �ʒu�iY�j
					float fPosZ = 0.0f;			// �ʒu�iZ�j

					// ���l�����o��
					sscanf(aFileData, "%s %s %s %f %f %f", aTenp[0], aTenp[1], aTenp[2], &fPosX, &fPosY, &fPosZ);

					// �ʒu�ݒ�
					CObjectX::VtxData vtxData = pObjectNone->GetVtxData();
					vtxData.pos = D3DXVECTOR3(fPosX, fPosY, fPosZ);
					pObjectNone->SetVtxData(vtxData);
				}
			}

			// �������̔���
			if (strstr(aFileData, "ROT") != NULL)
			{
				// ����̕����𔻒�
				if (strstr(aFileData, "=") != NULL)
				{
					// �ϐ��錾
					char aTenp[3][256] = {};	// �S�~����	
					float fRotX = 0.0f;			// �����iX�j
					float fRotY = 0.0f;			// �����iY�j
					float fRotZ = 0.0f;			// �����iZ�j

					// ���l�����o��
					sscanf(aFileData, "%s %s %s %f %f %f", aTenp[0], aTenp[1], aTenp[2], &fRotX, &fRotY, &fRotZ);

					// �ʒu�ݒ�
					CObjectX::VtxData vtxData = pObjectNone->GetVtxData();
					vtxData.rot = D3DXVECTOR3(fRotX, fRotY, fRotZ);
					pObjectNone->SetVtxData(vtxData);
				}
			}

			// ���f���ݒ�̏I��
			if (strstr(aFileData, "END_MODEL_SET") != NULL)
			{
				// �I�u�W�F�N�g�̃|�C���^���Ȃ���
				pObjectNone = NULL;
			}

			// �ǂݍ��ݏI��
			if (strstr(aFileData, "SET_END") != NULL)
			{
				break;
			}
		}

		// �t�@�C�������
		fclose(pFile);
	}
}