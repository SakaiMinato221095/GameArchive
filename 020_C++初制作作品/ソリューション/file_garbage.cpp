
//-===============================================
//-
//-	�S�~�t�@�C������[file_garbage.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "file_garbage.h"

#include "manager_object.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//= �R���X�g��`
//=======================================

// �ʏ�G�̃e�L�X�g�̃R���X�g��`
const char *pTxtGarbage[] =
{
	"data\\TXT\\Object\\Garbage_000.txt"		// �S�~_000�̃e�L�X�g
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

CFileGarbage::FileData CFileGarbage::m_aFileData[FILE_DATA_MAX] = {};
int  CFileGarbage::m_nSetMax = 0;

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CFileGarbage::CFileGarbage()
{
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CFileGarbage::~CFileGarbage()
{

}

//-------------------------------------
//- �I�u�W�F�N�g�t�@�C���̏����o������
//-------------------------------------
void CFileGarbage::Save(CFileGarbage::TXT txtType)
{
	//�ϐ��錾
	FILE *pFile;	// �t�@�C���̃|�C���^

	// �t�@�C���̏�����
	pFile = fopen(pTxtGarbage[txtType], "w");

	// �t�@�C���̗L���𔻒�
	if (pFile != NULL)
	{
		// �ϐ��錾�i�G�̃��f�����j
		int nMaxNum = 0;

		// ���o���̏����o��
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "#=\n");
		fprintf(pFile, "#= [�G] \n");
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
		fprintf(pFile, "#= [�z�u���] \n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "\n");

		for (int nCount = 0; nCount < OBJECTX_NONE_NUM_MAX; nCount++)
		{
			// �ϐ��錾�i�w��̓G�̃|�C���^�擾�j
			CGarbage *pGarbage = CManagerObject::GetGarbage(nCount);

			// �G�̗L���𔻒�
			if (pGarbage != NULL)
			{
				// �ϐ��錾�i�G�̏��擾�j
				int nModelNldx = pGarbage->GetModel();			// �g�p���f���ԍ�
				D3DXVECTOR3 pos = pGarbage->m_dataPos.Get();	// �ʒu
				D3DXVECTOR3 rot = pGarbage->m_dataRot.Get();	// ����

				// �z�u���f���̏��̏����o��
				fprintf(pFile, "MODEL = %d\n", nModelNldx);
				fprintf(pFile, " --- POS = %3.1f %3.1f %3.1f \n", pos.x, pos.y, pos.z);
				fprintf(pFile, " --- ROT = %3.1f %3.1f %3.1f \n", rot.x, rot.y, rot.z);
				fprintf(pFile, "END_MODEL_SET \n");
				fprintf(pFile, "\n");
			}
		}

		// �����o���̏I��
		fprintf(pFile, "SET_END");

		// �t�@�C�������
		fclose(pFile);
	}
}

//-------------------------------------
//- �I�u�W�F�N�g�t�@�C���̓ǂݍ��ݏ���
//-------------------------------------
void CFileGarbage::Load(CFileGarbage::TXT txtType)
{
	//�ϐ��錾
	FILE *pFile;	// �t�@�C���̃|�C���^

	// �t�@�C���̏�����
	pFile = fopen(pTxtGarbage[txtType], "r");

	int nObjCount = 0;

	// �t�@�C���̗L���𔻒�
	if (pFile != NULL)
	{
		// �ϐ��錾
		char aFileData[256] = { 0 };	// �t�@�C���̕��͂��i�[

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
					// �ϐ��錾
					char aTenp[2][256] = {};	// �S�~����	
					int nValue = 0;				// ���l

					// ���l�����o��
					sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nValue);

					// ���f���ԍ���ۑ�
					m_aFileData[nObjCount].modelNldx = nValue;
				}
			}

			if (strstr(aFileData, "POS") != NULL)
			{
				// ����̕����𔻒�
				if (strstr(aFileData, "=") != NULL)
				{
					// �ϐ��錾
					char aTenp[3][256] = {};	// �S�~����	
					float fPosX = 0;			// �ʒu�iX�j
					float fPosY = 0;			// �ʒu�iY�j
					float fPosZ = 0;			// �ʒu�iZ�j

					// ���l�����o��
					sscanf(aFileData, "%s %s %s %f %f %f", aTenp[0], aTenp[1], aTenp[2], &fPosX, &fPosY, &fPosZ);

					// �ʒu����ۑ�
					m_aFileData[nObjCount].pos = D3DXVECTOR3(fPosX,fPosY,fPosZ);
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
					float fRotX = 0;			// �����iX�j
					float fRotY = 0;			// �����iY�j
					float fRotZ = 0;			// �����iZ�j

					// ���l�����o��
					sscanf(aFileData, "%s %s %s %f %f %f", aTenp[0], aTenp[1], aTenp[2], &fRotX, &fRotY, &fRotZ);

					// �ʒu����ۑ�
					m_aFileData[nObjCount].rot = D3DXVECTOR3(fRotX, fRotY, fRotZ);
				}
			}

			// ���f���ݒ�̏I��
			if (strstr(aFileData, "END_MODEL_SET") != NULL)
			{
				nObjCount++;
			}

			// ���f���ݒ�̏I�� �i �I���̕��������� || �i�[�ꏊ���Ȃ� �j 
			if (strstr(aFileData, "SET_END") != NULL)
			{
				m_nSetMax = nObjCount;

				break;
			}
		}

		// �t�@�C�������
		fclose(pFile);
	}
}

//-------------------------------------
//- �I�u�W�F�N�g�t�@�C���̒u������
//-------------------------------------
void CFileGarbage::Locate(void)
{
	for (int nCount = 0; nCount < m_nSetMax; nCount++)
	{
		// �S�~�̗L���𔻒�
		if (m_aFileData[nCount].bNoLoad == false)
		{
			// �S�~�̐�������
			CGarbage *pGarbage = CGarbage::Create((CGarbage::MODEL)m_aFileData[nCount].modelNldx);

			// �ݒ菈��
			pGarbage->Set(
				m_aFileData[nCount].pos,
				m_aFileData[nCount].rot);

			// �ʏ�G�̃|�C���^����
			CManagerObject::SetGarbage(nCount, pGarbage);
		}
	}
}

//-------------------------------------
//- �I�u�W�F�N�g�t�@�C���̊m�F����
//-------------------------------------
void CFileGarbage::ObjCheck(void)
{
	for (int nCount = 0; nCount < m_nSetMax; nCount++)
	{
		// �S�~�̗L���𔻒�
		if (CManagerObject::GetGarbage(nCount) == NULL)
		{
			m_aFileData[nCount].bNoLoad = true;
		}
	}
}

//-------------------------------------
//- �I�u�W�F�N�g�t�@�C���̕�������
//-------------------------------------
void CFileGarbage::ObjRecall(void)
{
	for (int nCount = 0; nCount < m_nSetMax; nCount++)
	{
		m_aFileData[nCount].bNoLoad = false;
	}
}