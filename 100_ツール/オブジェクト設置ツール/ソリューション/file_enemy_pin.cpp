
//-===============================================
//-
//-	�G�l�~�[�s���t�@�C������[file_enemy_pin.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "file_enemy_pin.h"

#include "manager_object.h"

#include "enemy.h"
#include "enemy_pin.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//= �R���X�g��`
//=======================================

// �ʏ�G�̃e�L�X�g�̃R���X�g��`
const char *pTxtEnemyPin[] =
{
	"data\\TXT\\Object\\EnemyPin_000.txt"		// �G�l�~�[�s��_000�̃e�L�X�g
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CFileEnemyPin::CFileEnemyPin()
{
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CFileEnemyPin::~CFileEnemyPin()
{

}

//-------------------------------------
//- �I�u�W�F�N�g�t�@�C���̏����o������
//-------------------------------------
void CFileEnemyPin::Save(CFileEnemyPin::TXT txtType)
{
	//�ϐ��錾
	FILE *pFile;	// �t�@�C���̃|�C���^

	// �t�@�C���̏�����
	pFile = fopen(pTxtEnemyPin[txtType], "w");

	// �t�@�C���̗L���𔻒�
	if (pFile != NULL)
	{
		// �ϐ��錾�i�G�̃��f�����j
		int nMaxNum = 0;

		// ���o���̏����o��
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "#=\n");
		fprintf(pFile, "#= [�G�l�~�[�s��] \n");
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

		for (int nCount = 0; nCount < ENEMY_PIN_NUM_MAX; nCount++)
		{
			// �ϐ��錾�i�w��̓G�̃|�C���^�擾�j
			CEnemyPin *pEnemyPin = CManagerObject::GetEnemyPin(nCount);

			// �G�̗L���𔻒�
			if (pEnemyPin != NULL)
			{
				// �ϐ��錾�i�G�̏��擾�j
				int nModelNldx = pEnemyPin->GetModel();			// �g�p���f���ԍ�
				D3DXVECTOR3 pos = pEnemyPin->m_dataPos.Get();	// �ʒu
				D3DXVECTOR3 rot = pEnemyPin->m_dataRot.Get();	// ����

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
void CFileEnemyPin::Load(CFileEnemyPin::TXT txtType)
{
	//�ϐ��錾
	FILE *pFile;	// �t�@�C���̃|�C���^

	// �t�@�C���̏�����
	pFile = fopen(pTxtEnemyPin[txtType], "r");

	// �t�@�C���̗L���𔻒�
	if (pFile != NULL)
	{
		// �ϐ��錾
		char aFileData[256] = { 0 };			// �t�@�C���̕��͂��i�[
		CEnemyPin *pEnemyPin = NULL;			// �G�l�~�[�s���̃|�C���^

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
						if (CManagerObject::GetEnemyPin(nCount) == NULL)
						{
							// �G�̐�������
							pEnemyPin = CEnemyPin::Create((CEnemyPin::MODEL)0);

							CManagerObject::SetEnemyPin(nCount, pEnemyPin);

							// �ϐ��錾
							char aTenp[2][256] = {};	// �S�~����	
							int nValue = 0;				// ���l

							// ���l�����o��
							sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nValue);

							// ���f���ԍ��̎擾
							int nModelNldx = CEnemyPin::m_nDataModelNldx[nValue].Get();

							// ���f������
							pEnemyPin->BindModel(nModelNldx, (CEnemyPin::MODEL)nValue);

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
					pEnemyPin->m_dataPos.Set(D3DXVECTOR3(
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
					pEnemyPin->m_dataRot.Set(D3DXVECTOR3(
						fRotX,
						fRotY,
						fRotZ));
				}
			}

			// ���f���ݒ�̏I��
			if (strstr(aFileData, "END_MODEL_SET") != NULL)
			{
				// �I�u�W�F�N�g�̃|�C���^���Ȃ���
				pEnemyPin = NULL;
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