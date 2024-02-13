
//-===============================================
//-
//-	���ʂȂ��I�u�W�F�N�g���t�@�C������[file_data_obj_none.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "file_data_obj_none.h"

#include "manager_object.h"

#include "objectx_none.h"
#include "event_object.h"

//-======================================
//-	�}�N����`
//-======================================

#define FILE_DATA_OBJ_NONE_TEX	("data\\TXT\\DataModel\\DataObjNone.txt")

#define ARRAY_SIZE	(256)		// �z��̃T�C�Y

//=======================================
//= �R���X�g��`
//=======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CFileDataObjNone::CFileDataObjNone()
{
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CFileDataObjNone::~CFileDataObjNone()
{

}

//-------------------------------------
//- ���ʂȂ��I�u�W�F�N�g���t�@�C���̏����o������
//-------------------------------------
void CFileDataObjNone::Save(int nNumber , D3DXVECTOR3 sizeCol)
{
	//�ϐ��錾
	FILE *pFile;	// �t�@�C���̃|�C���^

	// �t�@�C���̏�����
	pFile = fopen(FILE_DATA_OBJ_NONE_TEX, "w");

	// �t�@�C���̗L���𔻒�
	if (pFile != NULL)
	{
		// �ϐ��錾�i���ʂȂ��I�u�W�F�N�g�̃��f�����j
		int nMaxNum = 0;

		// ���o���̏����o��
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "#=\n");
		fprintf(pFile, "#= [���ʂȂ��I�u�W�F�N�g���] \n");
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

		for (int nCount = 0; nCount < CObjectXNone::MODEL_MAX; nCount++)
		{
			// �G�̏��
			CObjectXNone::ModelData modelData;

			if (nCount == nNumber)
			{
				// �����蔻��I�u�W�F�N�g�̃T�C�Y����
				modelData.size = sizeCol;

				// �f�[�^���㏑��
				CObjectXNone::SetModelData(nCount, modelData);
			
			}
			else
			{
				// ���f��������
				modelData = CObjectXNone::GetModelData(nCount);
			}

			// �ϐ��錾
			D3DXVECTOR3 size = modelData.size;	// �T�C�Y���i�[

			// �z�u���f���̏��̏����o��
			fprintf(pFile, "MODEL_NUMBER = %d\n", nCount);
			fprintf(pFile, " --- SIZE = %3.1f %3.1f %3.1f \n", size.x, size.y, size.z);
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
//- ���ʂȂ��I�u�W�F�N�g���t�@�C���̓ǂݍ��ݏ���
//-------------------------------------
void CFileDataObjNone::Load(void)
{
	//�ϐ��錾
	FILE *pFile;	// �t�@�C���̃|�C���^

	// �t�@�C���̏�����
	pFile = fopen(FILE_DATA_OBJ_NONE_TEX, "r");

	// �t�@�C���̗L���𔻒�
	if (pFile != NULL)
	{
		// �ϐ��錾
		char aFileData[ARRAY_SIZE] = { 0 };			// �t�@�C���̕��͂��i�[
		int nModelNumber = -1;					// ���f���ԍ�
		CObjectXNone::ModelData modelData = {};	// ���f�����

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
						// ���ʂȂ��I�u�W�F�N�g�̗L���𔻒�
						if (CManagerObject::GetObjectNone(nCount) == NULL)
						{
							// �ϐ��錾
							char aTenp[2][ARRAY_SIZE] = {};	// �S�~����	
							int nValue = 0;				// ���l

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

			// ���f���ݒ�̏I��
			if (strstr(aFileData, "END_MODEL_DATA_SET") != NULL)
			{
				// �T�C�Y������
				CObjectXNone::SetModelData(nModelNumber, modelData);

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