
//-===============================================
//-
//-	�ʏ�G�t�@�C������[file_emy_nor.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "file_emy_nor.h"

#include "manager_object.h"

#include "enemy.h"
#include "enemy_normal.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//= �R���X�g��`
//=======================================

// �ʏ�G�̃e�L�X�g�̃R���X�g��`
const char *pTxtEnemyNormal[] =
{
	"data\\TXT\\Object\\EnemyNormal_000.txt"		// �ʏ�G_000�̃e�L�X�g
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CFileEmyNor::CFileEmyNor()
{
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CFileEmyNor::~CFileEmyNor()
{

}

//-------------------------------------
//- �I�u�W�F�N�g�t�@�C���̏����o������
//-------------------------------------
void CFileEmyNor::Save(CFileEmyNor::TXT txtType)
{
	//�ϐ��錾
	FILE *pFile;	// �t�@�C���̃|�C���^

	// �t�@�C���̏�����
	pFile = fopen(pTxtEnemyNormal[txtType], "w");

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
			CEnemyNormal *pEnemyNormal = CManagerObject::GetEnemyNormal(nCount);

			// �G�̗L���𔻒�
			if (pEnemyNormal != NULL)
			{
				// �ϐ��錾�i�G�̏��擾�j
				int nModelNldx = pEnemyNormal->GetModel();			// �g�p���f���ԍ�
				D3DXVECTOR3 pos = pEnemyNormal->m_dataPos.Get();	// �ʒu
				D3DXVECTOR3 rot = pEnemyNormal->m_dataRot.Get();	// ����

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
void CFileEmyNor::Load(CFileEmyNor::TXT txtType)
{
	//�ϐ��錾
	FILE *pFile;	// �t�@�C���̃|�C���^

	// �t�@�C���̏�����
	pFile = fopen(pTxtEnemyNormal[txtType], "r");

	// �t�@�C���̗L���𔻒�
	if (pFile != NULL)
	{
		// �ϐ��錾
		char aFileData[256] = { 0 };			// �t�@�C���̕��͂��i�[
		CEnemyNormal *pEnemyNormal = NULL;		// �ʏ�G�̃|�C���^

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
					for (int nCount = 0; nCount < ENEMY_NORMAL_NUM_MAX; nCount++)
					{
						// �G�̗L���𔻒�
						if (CManagerObject::GetEnemyNormal(nCount) == NULL)
						{
							// �G�̐�������
							pEnemyNormal = CEnemyNormal::Create((CEnemyNormal::MODEL)0);

							CManagerObject::SetEnemyNormal(nCount, pEnemyNormal);

							// �ϐ��錾
							char aTenp[2][256] = {};	// �S�~����	
							int nValue = 0;				// ���l

							// ���l�����o��
							sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nValue);

							// ���f���ԍ��̎擾
							int nModelNldx = CEnemyNormal::m_nDataModelNldx[nValue].Get();

							// ���f������
							pEnemyNormal->BindModel(nModelNldx, (CEnemyNormal::MODEL)nValue);

							break;
						}
					}
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

					// �ʒu������
					pEnemyNormal->m_dataPos.Set(D3DXVECTOR3(
						fPosX,
						fPosY,
						fPosZ));
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

					// ��������
					pEnemyNormal->m_dataRot.Set(D3DXVECTOR3(
						fRotX,
						fRotY,
						fRotZ));
				}
			}

			// ���f���ݒ�̏I��
			if (strstr(aFileData, "END_MODEL_SET") != NULL)
			{
				// �I�u�W�F�N�g�̃|�C���^���Ȃ���
				pEnemyNormal = NULL;
			}

			// ���f���ݒ�̏I�� �i �I���̕��������� || �i�[�ꏊ���Ȃ� �j 
			if (strstr(aFileData, "SET_END") != NULL)
			{
				break;
			}
		}

		// �t�@�C�������
		fclose(pFile);
	}
}