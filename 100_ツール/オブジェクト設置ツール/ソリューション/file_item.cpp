
//-===============================================
//-
//-	�A�C�e���t�@�C������[file_item.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "file_item.h"

#include "manager_object.h"

#include "item.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//= �R���X�g��`
//=======================================

// �A�C�e���e�L�X�g�̃R���X�g��`
const char *pTxtItem[] =
{
	"data\\TXT\\Object\\Item_000.txt"		// �A�C�e��_000�̃e�L�X�g
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CFileItem::CFileItem()
{
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CFileItem::~CFileItem()
{

}

//-------------------------------------
//- �I�u�W�F�N�g�t�@�C���̏���������
//-------------------------------------
HRESULT CFileItem::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �I�u�W�F�N�g�t�@�C���̏I������
//-------------------------------------
void CFileItem::Uninit(void)
{

}

//-------------------------------------
//- �I�u�W�F�N�g�t�@�C���̍X�V����
//-------------------------------------
void CFileItem::Update(void)
{

}

//-------------------------------------
//- �I�u�W�F�N�g�t�@�C���̕`�揈��
//-------------------------------------
void CFileItem::Draw(void)
{

}

//-------------------------------------
//- �I�u�W�F�N�g�t�@�C���̐�������
//-------------------------------------
CFileItem *CFileItem::Create(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �I�u�W�F�N�g�t�@�C���̃|�C���^��錾
	CFileItem *pFileObject = new CFileItem;

	// �����̐����̗L���𔻒�
	if (pFileObject != NULL)
	{
		// ����������
		if (FAILED(pFileObject->Init(hInstance, hWnd, bWindow)))
		{// ���s��

		 // �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pFileObject == NULL)
	{// ���s��

	 // �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �I�u�W�F�N�g�t�@�C���̃|�C���^��Ԃ�
	return pFileObject;
}

//-------------------------------------
//- �I�u�W�F�N�g�t�@�C���̏����o������
//-------------------------------------
void CFileItem::Save(CFileItem::TXT txtType)
{
	//�ϐ��錾
	FILE *pFile;	// �t�@�C���̃|�C���^

	// �t�@�C���̏�����
	pFile = fopen(pTxtItem[txtType], "w");

	// �t�@�C���̗L���𔻒�
	if (pFile != NULL)
	{
		// �ϐ��錾�i�A�C�e���̃��f�����j
		int nMaxNum = 0;

		// ���o���̏����o��
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "#=\n");
		fprintf(pFile, "#= [�A�C�e��] \n");
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
			// �ϐ��錾�i�w��̃A�C�e���̃|�C���^�擾�j
			CItem *pItem = CManagerObject::GetItem(nCount);

			// �A�C�e���̗L���𔻒�
			if (pItem != NULL)
			{
				// �ϐ��錾�i�A�C�e���̏��擾�j
				int nModelNldx = pItem->GetModel();			// �g�p���f���ԍ�
				D3DXVECTOR3 pos = pItem->m_dataPos.Get();	// �ʒu
				D3DXVECTOR3 rot = pItem->m_dataRot.Get();	// ����

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
void CFileItem::Load(CFileItem::TXT txtType)
{
	//�ϐ��錾
	FILE *pFile;	// �t�@�C���̃|�C���^

	// �t�@�C���̏�����
	pFile = fopen(pTxtItem[txtType], "r");

	// �t�@�C���̗L���𔻒�
	if (pFile != NULL)
	{
		// �ϐ��錾
		char aFileData[256] = { 0 };		// �t�@�C���̕��͂��i�[
		CItem *pItem = NULL;	// �A�C�e���̃|�C���^

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
					for (int nCount = 0; nCount < EVENT_OBJECT_NUM_MAX; nCount++)
					{
						// �A�C�e���̗L���𔻒�
						if (CManagerObject::GetEventObject(nCount) == NULL)
						{
							// �A�C�e���̐�������
							pItem = CItem::Create((CItem::MODEL)0);

							CManagerObject::SetItem(nCount, pItem);

							// �ϐ��錾
							char aTenp[2][256] = {};	// �S�~����	
							int nValue = 0;				// ���l

							// ���l�����o��
							sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nValue);

							// ���f���ԍ��̎擾
							int nModelNldx = CItem::m_nDataModelNldx[nValue].Get();

							// ���f������
							pItem->BindModel(nModelNldx, (CItem::MODEL)nValue);

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
					pItem->m_dataPos.Set(D3DXVECTOR3(
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
					pItem->m_dataRot.Set(D3DXVECTOR3(
						fRotX,
						fRotY,
						fRotZ));
				}
			}

			// ���f���ݒ�̏I��
			if (strstr(aFileData, "END_MODEL_SET") != NULL)
			{
				// �I�u�W�F�N�g�̃|�C���^���Ȃ���
				pItem = NULL;
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