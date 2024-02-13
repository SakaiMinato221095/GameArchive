
//================================================
//=
//= �e�N�X�`���Ǘ��̏���[manager_texture.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "manager_texture.h"

#include "renderer.h"
#include "manager.h"

#include "bg.h"

#include "number.h"
#include "explosion.h"
#include "block.h"

#include "bullet.h"
#include "effect.h"

#include "obj_3d_field.h"
#include "obj_3d_wall.h"

#include "obj_2d_none.h"
#include "obj_2d_item_info.h"
#include "effect_2d.h"

#include "ui_opr_desc.h"
#include "ui_text_desc.h"

#include "ui_mission.h"
#include "ui_start_text.h"

//-------------------------------------
//-	�e�N�X�`���̃R���X�g���N�^
//-------------------------------------
CManagerTexture::CManagerTexture()
{
	// �l�̃N���A
	ZeroMemory(m_apTexture, sizeof(m_apTexture));
}

//-------------------------------------
//-	�e�N�X�`���̃f�X�g���N�^
//-------------------------------------
CManagerTexture::~CManagerTexture()
{
}


//-------------------------------------
//-	�e�N�X�`���̓ǂݍ��ݏ���
//-------------------------------------
HRESULT CManagerTexture::Load(HWND hWnd)
{
	// �w�i
	if (FAILED(CBg::Load()))
	{// ���s��

		// ���s���b�Z�[�W
		MessageBox(hWnd, "�w�i�̃f�[�^", "�f�[�^�ǂݍ��ݏ������s�I", MB_ICONWARNING);

		// �f�[�^�ǂݍ��݂𔲂���
		return E_FAIL;
	}

	// ����
	if (FAILED(CNumber::Load()))
	{// ���s��

		// ���s���b�Z�[�W
		MessageBox(hWnd, "�����̃f�[�^", "�f�[�^�ǂݍ��ݏ������s�I", MB_ICONWARNING);

		// �f�[�^�ǂݍ��݂𔲂���
		return E_FAIL;
	}

	// �e
	if (FAILED(CBullet::Load()))
	{// ���s��

		// ���s���b�Z�[�W
		MessageBox(hWnd, "�e�̃f�[�^", "�f�[�^�ǂݍ��ݏ������s�I", MB_ICONWARNING);

		// �f�[�^�ǂݍ��݂𔲂���
		return E_FAIL;
	}

	// ����
	if (FAILED(CExplosion::Load()))
	{// ���s��

		// ���s���b�Z�[�W
		MessageBox(hWnd, "�����̃f�[�^", "�f�[�^�ǂݍ��ݏ������s�I", MB_ICONWARNING);

		// �f�[�^�ǂݍ��݂𔲂���
		return E_FAIL;
	}

	// �G�t�F�N�g
	if (FAILED(CEffect::Load()))
	{// ���s��

	 // ���s���b�Z�[�W
		MessageBox(hWnd, "�G�t�F�N�g�̃f�[�^", "�f�[�^�ǂݍ��ݏ������s�I", MB_ICONWARNING);

		// �f�[�^�ǂݍ��݂𔲂���
		return E_FAIL;
	}

	// �u���b�N
	if (FAILED(CBlock::Load()))
	{// ���s��

		// ���s���b�Z�[�W
		MessageBox(hWnd, "�u���b�N�̃f�[�^", "�f�[�^�ǂݍ��ݏ������s�I", MB_ICONWARNING);

		// �f�[�^�ǂݍ��݂𔲂���
		return E_FAIL;
	}

	// �t�B�[���h
	if (FAILED(CObj3dField::Load()))
	{
		// ���s���b�Z�[�W
		MessageBox(hWnd, "�t�B�[���h�̃f�[�^", "�f�[�^�ǂݍ��ݏ������s�I", MB_ICONWARNING);

		// �f�[�^�ǂݍ��݂𔲂���
		return E_FAIL;
	}

	// �E�H�[��
	if (FAILED(CObj3dWall::Load()))
	{
		// ���s���b�Z�[�W
		MessageBox(hWnd, "�E�H�[���̃f�[�^", "�f�[�^�ǂݍ��ݏ������s�I", MB_ICONWARNING);

		// �f�[�^�ǂݍ��݂𔲂���
		return E_FAIL;
	}

	// ���ʂȂ�2D
	if (FAILED(CObj2dNone::Load()))
	{
		// ���s���b�Z�[�W
		MessageBox(hWnd, "���ʂȂ�2D�I�u�W�F�N�g�f�[�^", "�f�[�^�ǂݍ��ݏ������s�I", MB_ICONWARNING);

		// �f�[�^�ǂݍ��݂𔲂���
		return E_FAIL;
	}
	
	// 2D�A�C�e�����
	if (FAILED(CEffect2d::Load()))
	{
		// ���s���b�Z�[�W
		MessageBox(hWnd, "2D�G�t�F�N�g�f�[�^", "�f�[�^�ǂݍ��ݏ������s�I", MB_ICONWARNING);

		// �f�[�^�ǂݍ��݂𔲂���
		return E_FAIL;
	}

	// 2D�A�C�e�����
	if (FAILED(CObj2dItemInfo::Load()))
	{
		// ���s���b�Z�[�W
		MessageBox(hWnd, "2D�A�C�e�����f�[�^", "�f�[�^�ǂݍ��ݏ������s�I", MB_ICONWARNING);

		// �f�[�^�ǂݍ��݂𔲂���
		return E_FAIL;
	}

	// �������UI���
	if (FAILED(CUiOprDesc::Load()))
	{
		// ���s���b�Z�[�W
		MessageBox(hWnd, "�������UI���f�[�^", "�f�[�^�ǂݍ��ݏ������s�I", MB_ICONWARNING);

		// �f�[�^�ǂݍ��݂𔲂���
		return E_FAIL;
	}

	// �������UI���
	if (FAILED(CUiTextDesc::Load()))
	{
		// ���s���b�Z�[�W
		MessageBox(hWnd, "���������UI���f�[�^", "�f�[�^�ǂݍ��ݏ������s�I", MB_ICONWARNING);

		// �f�[�^�ǂݍ��݂𔲂���
		return E_FAIL;
	}

	// ���������UI���
	if (FAILED(CUiTextDesc::Load()))
	{
		// ���s���b�Z�[�W
		MessageBox(hWnd, "���������UI���f�[�^", "�f�[�^�ǂݍ��ݏ������s�I", MB_ICONWARNING);

		// �f�[�^�ǂݍ��݂𔲂���
		return E_FAIL;
	}

	// �ړIUI�̏��
	if (FAILED(CUiMission::Load()))
	{
		// ���s���b�Z�[�W
		MessageBox(hWnd, "�ړIUI�̏��f�[�^", "�f�[�^�ǂݍ��ݏ������s�I", MB_ICONWARNING);

		// �f�[�^�ǂݍ��݂𔲂���
		return E_FAIL;
	}

	// �J�n�������̏��
	if (FAILED(CUiStartText::Load()))
	{
		// ���s���b�Z�[�W
		MessageBox(hWnd, "�J�n�������̃f�[�^", "�f�[�^�ǂݍ��ݏ������s�I", MB_ICONWARNING);

		// �f�[�^�ǂݍ��݂𔲂���
		return E_FAIL;
	}


	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//-	�e�N�X�`���̔j������
//-------------------------------------
void CManagerTexture::Unload(void)
{
	for (int nCount = 0; nCount < MANAGER_TEXTUTE_MAX; nCount++)
	{
		// �e�N�X�`���̗L���𔻒�
		if (m_apTexture[nCount] != NULL)
		{
			// �J������
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//-------------------------------------
//-	�e�N�X�`���̎w��ǂݍ��ݏ���
//-------------------------------------
int CManagerTexture::Regist(const char *pFilename)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

		// �����������𔲂���
		return -1;
	}

	// �t�@�C�����𔻒�i�e�N�X�`���Ȃ��j
	if (pFilename == NULL)
	{
		return 0;
	}
	
	for (int nCount = 1; nCount < MANAGER_TEXTUTE_MAX; nCount++)
	{
		// �e�N�X�`���̗L���𔻒�
		if (m_apTexture[nCount] == NULL)
		{
			// �e�N�X�`���̓ǂݍ��� if(�e�N�X�`���ǂݍ��ݐ����̗L���𔻒�)
			if (FAILED(D3DXCreateTextureFromFile(
				pDevice,
				pFilename,
				&m_apTexture[nCount])))
			{
				// ���s��Ԃ�
				return -1;
			}

			// ���݂̔ԍ���Ԃ�
			return nCount;
		}
	}
	
	// ���s��Ԃ�
	return -1;
}

//-------------------------------------
//-	�e�N�X�`���̎擾����
//-------------------------------------
LPDIRECT3DTEXTURE9 CManagerTexture::GetAddress(int nldx)
{
	// �e�N�X�`����Ԃ�
	return m_apTexture[nldx];
}
