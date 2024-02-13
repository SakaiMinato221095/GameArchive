
//-===============================================
//-
//-	�S�~���̃t�@�C������[file_data_garbage.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "file_data_garbage.h"

#include "manager_object.h"

#include "objectx_none.h"
#include "garbage.h"

//-======================================
//-	�}�N����`
//-======================================

#define FILE_DATA_GARBAGE_TEX	("data\\TXT\\DataModel\\DataGarbage.txt")

#define ARRAY_SIZE				(256)		// �z��̃T�C�Y

//=======================================
//= �R���X�g��`
//=======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CFileDataGarbage::CFileDataGarbage()
{
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CFileDataGarbage::~CFileDataGarbage()
{

}

//-------------------------------------
//- �A�C�e�����̃t�@�C���̏����o������
//-------------------------------------
void CFileDataGarbage::Save(int nNumber, D3DXVECTOR3 sizeCol)
{
	//�ϐ��錾
	FILE *pFile;	// �t�@�C���̃|�C���^

	// �t�@�C���̏�����
	pFile = fopen(FILE_DATA_GARBAGE_TEX, "w");

	// �t�@�C���̗L���𔻒�
	if (pFile != NULL)
	{
		// �ϐ��錾�i�A�C�e���̃��f�����j
		int nMaxNum = 0;

		// ���o���̏����o��
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "#=\n");
		fprintf(pFile, "#= [�S�~���] \n");
		fprintf(pFile, "#=\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "\n");

		// ���f�����̏����o��
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "#= [���f����] \n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "%d\n", nMaxNum);
		fprintf(pFile, "\n");

		// �z�u�󋵌��o���̏����o��
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "#= [���f�����] \n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "\n");

		for (int nCount = 0; nCount < CGarbage::MODEL_MAX; nCount++)
		{
			// �A�C�e���̏��
			CGarbage::ModelData modelData;

			if (nCount == nNumber)
			{
				// �����蔻��I�u�W�F�N�g�̃T�C�Y����
				modelData.size = sizeCol;

				// �f�[�^���㏑��
				CGarbage::SetModelData(nCount, modelData);
			}
			else
			{
				// ���f��������
				modelData = CGarbage::GetModelData(nCount);
			}

			// �ϐ��錾
			D3DXVECTOR3 size = modelData.size;			// �T�C�Y���i�[
			int nScoreHave = modelData.nScoreHave;	// �ێ�����X�R�A���i�[

			// �z�u���f���̏��̏����o��
			fprintf(pFile, "MODEL_NUMBER = %d\n", nCount);
			fprintf(pFile, " --- SIZE       = %3.1f %3.1f %3.1f \n", size.x, size.y, size.z);
			fprintf(pFile, " --- SCORE_HAVE = %d", nScoreHave);
			fprintf(pFile, "END_MODEL_DATA_SET \n");
			fprintf(pFile, "\n");
		}

		// �����o���̏I��
		fprintf(pFile, "SET_END");

		// �t�@�C�������
		fclose(pFile);
	}
}

//-------------------------------------
//- �A�C�e�����̃t�@�C���̓ǂݍ��ݏ���
//-------------------------------------
void CFileDataGarbage::Load(void)
{
	//�ϐ��錾
	FILE *pFile;	// �t�@�C���̃|�C���^

	// �t�@�C���̏�����
	pFile = fopen(FILE_DATA_GARBAGE_TEX, "r");

	// �t�@�C���̗L���𔻒�
	if (pFile != NULL)
	{
		// �ϐ��錾
		char aFileData[ARRAY_SIZE] = { 0 };		// �t�@�C���̕��͂��i�[
		int nModelNumber = -1;					// ���f���ԍ�
		CGarbage::ModelData modelData = {};		// ���f�����

		while (true)
		{
			// �������ǂݍ���
			fgets(aFileData, 256, pFile);

			// ���������ǂݍ���
			for (int nCount = 0; nCount < ARRAY_SIZE; nCount++)
			{
				// �R�����g�𔻒�
				if (aFileData[nCount] == '#')
				{
					// �R�����g������
					memset(&aFileData[nCount], NULL, sizeof(ARRAY_SIZE - nCount));
					break;
				}
			}

			if (strstr(aFileData, "MODEL_NUMBER") != NULL)
			{
				if (strstr(aFileData, "=") != NULL)
				{
					for (int nCount = 0; nCount < OBJECTX_NONE_NUM_MAX; nCount++)
					{
						// �A�C�e���̗L���𔻒�
						if (CManagerObject::GetGarbage(nCount) == NULL)
						{
							// �ϐ��錾
							char aTenp[2][ARRAY_SIZE] = {};	// �S�~����	
							int nValue = 0;					// ���l

							// ���l�����o��
							sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nValue);

							// ���o�������l�i���f���ԍ��j����
							nModelNumber = nValue;

							break;
						}
					}

				}
			}

			if (strstr(aFileData, "SIZE") != NULL)
			{
				// ����̕����𔻒�
				if (strstr(aFileData, "=") != NULL)
				{
					// �ϐ��錾
					char aTenp[3][ARRAY_SIZE] = {};	// �S�~����	
					float fSizeX = 0;			// �ʒu�iX�j
					float fSizeY = 0;			// �ʒu�iY�j
					float fSizeZ = 0;			// �ʒu�iZ�j

					// ���l�����o��
					sscanf(aFileData, "%s %s %s %f %f %f", aTenp[0], aTenp[1], aTenp[2], &fSizeX, &fSizeY, &fSizeZ);

					// �T�C�Y����
					modelData.size = D3DXVECTOR3(fSizeX, fSizeY, fSizeZ);
				}
			}

			if (strstr(aFileData, "SCORE_HAVE") != NULL)
			{
				// ����̕����𔻒�
				if (strstr(aFileData, "=") != NULL)
				{
					// �ϐ��錾
					char aTenp[3][ARRAY_SIZE] = {};	// �S�~����	
					int nValue = 0;					// ���l

					// ���l�����o��
					sscanf(aFileData, "%s %s %s %d", aTenp[0], aTenp[1], aTenp[2], &nValue);

					// ���o�������l�i���f���ԍ��j����
					modelData.nScoreHave = nValue;
				}
			}

			if (strstr(aFileData, "TYPE") != NULL)
			{
				// ����̕����𔻒�
				if (strstr(aFileData, "=") != NULL)
				{
					// �ϐ��錾
					char aTenp[3][ARRAY_SIZE] = {};	// �S�~����	
					int nValue = 0;					// ���l

					// ���l�����o��
					sscanf(aFileData, "%s %s %s %d", aTenp[0], aTenp[1], aTenp[2], &nValue);

					// ���o�������l�i���f���ԍ��j����
					modelData.nType = nValue;
				}
			}

			if (strstr(aFileData, "NOR_STATE") != NULL)
			{
				// ����̕����𔻒�
				if (strstr(aFileData, "=") != NULL)
				{
					// �ϐ��錾
					char aTenp[3][ARRAY_SIZE] = {};	// �S�~����	
					int nValue = 0;					// ���l

					// ���l�����o��
					sscanf(aFileData, "%s %s %s %d", aTenp[0], aTenp[1], aTenp[2], &nValue);

					// ���o�������l�i���f���ԍ��j����
					modelData.nNor = nValue;
				}
			}

			if (strstr(aFileData, "LOW_STATE") != NULL)
			{
				// ����̕����𔻒�
				if (strstr(aFileData, "=") != NULL)
				{
					// �ϐ��錾
					char aTenp[3][ARRAY_SIZE] = {};	// �S�~����	
					int nValue = 0;					// ���l

					// ���l�����o��
					sscanf(aFileData, "%s %s %s %d", aTenp[0], aTenp[1], aTenp[2], &nValue);

					// ���o�������l�i���f���ԍ��j����
					modelData.nLow = nValue;
				}
			}

			if (strstr(aFileData, "CHAOS_STATE") != NULL)
			{
				// ����̕����𔻒�
				if (strstr(aFileData, "=") != NULL)
				{
					// �ϐ��錾
					char aTenp[3][ARRAY_SIZE] = {};	// �S�~����	
					int nValue = 0;					// ���l

					// ���l�����o��
					sscanf(aFileData, "%s %s %s %d", aTenp[0], aTenp[1], aTenp[2], &nValue);

					// ���o�������l�i���f���ԍ��j����
					modelData.nChaos = nValue;
				}
			}

			// ���f���ݒ�̏I��
			if (strstr(aFileData, "END_MODEL_DATA_SET") != NULL)
			{
				// �T�C�Y������
				CGarbage::SetModelData(nModelNumber, modelData);

				// ���f���ԍ���������
				nModelNumber = -1;
			}

			if (strstr(aFileData, "SET_END") != NULL)
			{
				break;
			}
		}

		// �t�@�C�������
		fclose(pFile);
	}
}