
//================================================
//=
//= �K�w�\���̊K�w�\����X�t�@�C���I�u�W�F�N�g����[object_model.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "object_model.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

//=======================================
//=	�R���X�g��`
//=======================================

// ���f���e�L�X�g�̃R���X�g��`
const char *pModelText[] =
{
	"data\\TXT\\Model\\Murabito.txt",		// ���l�̊K�w�\�����f���t�@�C��
	"data\\TXT\\Model\\Cloud.txt",			// �N���E�h�̊K�w�\�����f���t�@�C��
	"data\\TXT\\Model\\Sample.txt",			// �T���v���̊K�w�\�����f���t�@�C��
};

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

CObjectModel::Model CObjectModel::m_model[MODEL_NUM_MAX] = {};

//-------------------------------------
//-	�K�w�\����X�t�@�C���I�u�W�F�N�g�̃R���X�g���N�^
//-------------------------------------
CObjectModel::CObjectModel()
{
	// �l���N���A
	m_pTexture = NULL;
	m_nldxTexture = NULL;

	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_dwNumMat = 0;

	ZeroMemory(m_mtxWorld, sizeof(D3DXMATRIX));
}

//-------------------------------------
//-	�K�w�\����X�t�@�C���I�u�W�F�N�g�̃f�X�g���N�^
//-------------------------------------
CObjectModel::~CObjectModel()
{
}

//-------------------------------------
//-	�K�w�\����X�t�@�C���I�u�W�F�N�g�̏���������
//-------------------------------------
HRESULT CObjectModel::Init(MODEL_TYPE modelType , int nCount)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

		// �����������𔲂���
		return E_FAIL;
	}

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(
		m_model[modelType].modelParts[nCount].aFileName,		// X�t�@�C���I�u�W�F�N�g��
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,									// �}�e���A���̏��
		NULL,
		&m_dwNumMat,									// �}�e���A���̐�
		&m_pMesh);										// ���b�V���̏��

	// X�t�@�C���̓ǂݍ��ݐ����̗L�����m�F
	if (m_pBuffMat == NULL)
	{
		// ���s���ɏ����������𔲂���
		return E_FAIL;
	}

	// �e�N�X�`���̎g�p�̗L�����m�F
	if (m_pTexture == NULL)
	{
		// �}�e���A���������I�m��
		m_pTexture = new LPDIRECT3DTEXTURE9[m_dwNumMat];
		m_nldxTexture = new int[m_dwNumMat];

		// �e�N�X�`������������
		ZeroMemory(m_pTexture, sizeof(m_pTexture));
		ZeroMemory(m_nldxTexture, sizeof(m_nldxTexture));
	}
	else
	{
		// �����������𔲂���
		return E_FAIL;
	}

	// �}�e���A���̏����擾
	D3DXMATERIAL *pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// �}�e���A���̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s

	 // �������𔲂���
		return E_FAIL;

	}

	// �}�e���A�����Ƃ̓ǂݍ���
	for (int nCutMat = 0; nCutMat < (int)m_dwNumMat; nCutMat++)
	{
		// �e�N�X�`���ݒ�̗L���𔻒�
		if (pMat[nCutMat].pTextureFilename != NULL)
		{// �e�N�X�`���ݒ肪���݂���

			// �e�N�X�`���̓ǂݍ��� if(�e�N�X�`���ǂݍ��ݐ����̗L���𔻒�)
			if (FAILED(D3DXCreateTextureFromFile(
				pDevice,
				pMat[nCutMat].pTextureFilename,
				&m_pTexture[nCutMat])))
			{
				// ���s��Ԃ�
				return E_FAIL;
			}

			// �e�N�X�`���Ǘ��̐���
			CManagerTexture *pManagerTexture = CManager::GetManagerTexture();

			// �e�N�X�`���Ǘ��̗L���𔻒�
			if (pManagerTexture != NULL)
			{
				// �e�N�X�`���ݒ�
				m_nldxTexture[nCutMat] = pManagerTexture->Regist(pMat[nCutMat].pTextureFilename);
			}

		}
		else
		{
			// �u�Ȃ��v����
			m_pTexture[nCutMat] = NULL;
		}
	}

	// ����ݒ�
	m_dataPos.Set(m_model[modelType].modelParts[nCount].pos);	// �ʒu
	m_dataRot.Set(m_model[modelType].modelParts[nCount].rot);	// ����

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//-	�K�w�\����X�t�@�C���I�u�W�F�N�g�̏I������
//-------------------------------------
void CObjectModel::Uninit(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		// ���I�m�ە�
		for (int nCutMat = 0; nCutMat < (int)m_dwNumMat; nCutMat++)
		{
			// �e�N�X�`���̗L���𔻒�
			if (m_pTexture[nCutMat] != NULL)
			{
				// �e�N�X�`���̊J������
				m_pTexture[nCutMat]->Release();
				m_pTexture[nCutMat] = NULL;
			}
		}

		// �e�N�X�`���̊J��
		delete[] m_pTexture;
		m_pTexture = NULL;

		// �e�N�X�`���ԍ��̊J��
		delete[] m_nldxTexture;
		m_nldxTexture = NULL;
	}

	// ���b�V���̔j��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	// �}�e���A���̔j��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}

//-------------------------------------
//-	�K�w�\����X�t�@�C���I�u�W�F�N�g�̍X�V����
//-------------------------------------
void CObjectModel::Update(void)
{

}

//-------------------------------------
//-	�K�w�\����X�t�@�C���I�u�W�F�N�g�̕`�揈��
//-------------------------------------
void CObjectModel::Draw(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get() + m_dataMotionPos.Get();	// �ʒu���
	D3DXVECTOR3 rot = m_dataRot.Get() + m_dataMotionRot.Get();	// �������

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

	 // �����������𔲂���
		return;
	}

	// �ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			// ���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL *pMat;				// �}�e���A���ւ̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu���f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//�e�̌v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxParent;

	//�p�[�c�́u�e�}�g���b�N�X�v��ݒ�
	if (m_pParent != NULL)
	{//�e���f��������ꍇ

		// �e�̃}�g���b�N�X����
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{//�e���f�����Ȃ��ꍇ

		//�v���C���[�̃}�g���b�N�X��ݒ�
		pDevice->GetTransform(D3DTS_WORLD,&mtxParent);
	}

	//�Z�o�����p�[�c�̃}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(
		&m_mtxWorld,
		&m_mtxWorld,
		&mtxParent);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(
		D3DTS_WORLD,
		&m_mtxWorld);

	// ���݂̃}�e���A���̎擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// �}�e���A�����Ƃ̕`��
	for (int nCutMat = 0; nCutMat < (int)m_dwNumMat; nCutMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCutMat].MatD3D);

		// �e�N�X�`���̐ݒ�i���j
		pDevice->SetTexture(0, m_pTexture[nCutMat]);

		// �K�w�\����X�t�@�C���I�u�W�F�N�g�i�p�[�c�j�̕`��
		m_pMesh->DrawSubset(nCutMat);
	}

	// �ۑ����Ă����}�e���A���ɖ߂�
	pDevice->SetMaterial(&matDef);

}

//-------------------------------------
//-	�K�w�\����X�t�@�C���I�u�W�F�N�g�̐�������
//-------------------------------------
CObjectModel *CObjectModel::Create(MODEL_TYPE modelType, int nCount)
{
	// �K�w�\����X�t�@�C���I�u�W�F�N�g�̃|�C���^��錾
	CObjectModel *pObjectX = NULL;

	// ����
	pObjectX = new CObjectModel;

	// �����̐����̗L���𔻒�
	if (pObjectX != NULL)
	{
		// ����������
		if (FAILED(pObjectX->Init(modelType,nCount)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pObjectX == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �K�w�\����X�t�@�C���I�u�W�F�N�g�̃|�C���^��Ԃ�
	return pObjectX;
}

//-------------------------------------
//-	�K�w�\����X�t�@�C���I�u�W�F�N�g�̐e�q�֌W�ݒ菈��
//-------------------------------------
void CObjectModel::SetParent(CObjectModel **pObjectModel, MODEL_TYPE modelType,int nCount)
{
	// �e�̔ԍ����擾
	int nParent = m_model[modelType].modelParts[nCount].nParent;

	if (nParent != -1)
	{
		// �e�̃��f��������
		m_pParent = pObjectModel[nParent];
	}
	else
	{
		m_pParent = NULL;
	}
}

//-------------------------------------
//-	�K�w�\����X�t�@�C���I�u�W�F�N�g�̃��[���h�}�g���b�N�X�擾����
//-------------------------------------
D3DXMATRIX CObjectModel::GetMtxWorld(void)
{
	// ���[���h�}�g���b�N�X��Ԃ�
	return m_mtxWorld;
}

//-------------------------------------
//- �K�w�\����X�t�@�C���I�u�W�F�N�g�̃��f���ݒ菈��
//-------------------------------------
void CObjectModel::SetFile(MODEL_TYPE modelType)
{
	//�ϐ��錾
	FILE *pFile;	// �t�@�C���̃|�C���^

	// �t�@�C���̏�����
	pFile = fopen(pModelText[modelType], "r");

	// �t�@�C���̗L���𔻒�
	if (pFile != NULL)
	{// �t�@�C�����J����Ƃ�

		// �ϐ��錾
		char aFileData[256] = {};		// �t�@�C���̕��͂��i�[

		int nFileNameCount = -1;		// �t�@�C���̖��O�̃J�E���g 
		int nIndex = -1;				// �p�[�c�����i�[

		while (true)
		{
			// �������ǂݍ���
			fgets(aFileData, 256, pFile);

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

			// ���f���̃p�[�c����ݒ�
			if (strstr(aFileData, "NUM_MODEL") != NULL)
			{
				// �ϐ��錾
				char aTenp[2][256] = {};	// �S�~����	
				int nPartsNum = 0;			// �p�[�c��

				// �p�[�c�������o��
				sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nPartsNum);

				// �p�[�c������
				m_model[modelType].nPartsNum = nPartsNum;
			}

			// �p�[�c�̃t�@�C������ݒ�
			if (strstr(aFileData, "MODEL_FILENAME") != NULL)
			{
				// �ϐ��錾
				char aTenp[2][256] = {};	// �S�~����	
				char aFileName[256] = {};	// �t�@�C���̖��O���i�[

				// �p�[�c�J�E���g��i�߂�
				nFileNameCount++;

				// �t�@�C���̖��O�����o��
				sscanf(aFileData, "%s %s %s", aTenp[0], aTenp[1], aFileName);

				// �t�@�C���̖��O����
				strcpy(m_model[modelType].modelParts[nFileNameCount].aFileName, aFileName);
			}

			// �p�[�c�ԍ��̐ݒ�
			if (strstr(aFileData, "INDEX") != NULL)
			{
				// �ϐ��錾
				char aTenp[2][256] = {};	// �S�~����	

				// �p�[�c�̔ԍ������o��
				sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nIndex);

				// �p�[�c�̔ԍ�����
				m_model[modelType].modelParts[nIndex].nIndex = nIndex;
			}

			// �e�̐ݒ�
			if (strstr(aFileData, "PARENT") != NULL)
			{
				// �ϐ��錾
				char aTenp[2][256] = {};	// �S�~����	
				int nParent = -1;

				// �e�̔ԍ������o��
				sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nParent);

				// �e�̔ԍ�����
				m_model[modelType].modelParts[nIndex].nParent = nParent;
			}

			// �ʒu���̐ݒ�
			if (strstr(aFileData, "POS") != NULL)
			{
				// �ϐ��錾
				char aTenp[2][256] = {};	// �S�~����	
				float fPosX = 0;			// �ʒu�iX�j
				float fPosY = 0;			// �ʒu�iY�j
				float fPosZ = 0;			// �ʒu�iZ�j

				// �ʒu�����o��
				sscanf(aFileData, "%s %s %f %f %f", aTenp[0], aTenp[1], &fPosX, &fPosY, &fPosZ);

				// �ʒu����
				m_model[modelType].modelParts[nIndex].pos = D3DXVECTOR3(fPosX, fPosY, fPosZ);
			}

			// �������̐ݒ�
			if (strstr(aFileData, "ROT") != NULL)
			{
				// �ϐ��錾
				char aTenp[2][256] = {};	// �S�~����	
				float fRotX = 0;			// �����iX�j
				float fRotY = 0;			// �����iY�j
				float fRotZ = 0;			// �����iZ�j

				// ���������o��
				sscanf(aFileData, "%s %s %f %f %f", aTenp[0], aTenp[1], &fRotX, &fRotY, &fRotZ);

				// ��������
				m_model[modelType].modelParts[nIndex].rot = D3DXVECTOR3(fRotX, fRotY, fRotZ);
			}

			// �I��
			if (strstr(aFileData, "END_CHARACTERSET") != NULL)
			{
				break;
			}
		}

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{

	}
}

//-------------------------------------
//- �K�w�\����X�t�@�C���I�u�W�F�N�g�̃��f���ݒ菈��
//-------------------------------------
int CObjectModel::GetPartsNum(MODEL_TYPE modelType)
{
	// �p�[�c����Ԃ�
	return m_model[modelType].nPartsNum;
}