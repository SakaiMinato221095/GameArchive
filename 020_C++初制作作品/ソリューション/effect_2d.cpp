
//-===============================================
//-
//-	2D�G�t�F�N�g�̏���[effect2d.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "effect_2d.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"
#include "time_stop.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//= �R���X�g��`
//=======================================

// �G�t�F�N�g�e�N�X�`���̃R���X�g��`
const char *pTextureEffect2d[] =
{
	"data\\TEXTURE\\effect000.jpg"	// �ʏ�G�t�F�N�g_000�̃e�N�X�`��
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

int CEffect2d::m_nTextureNldx[TEX_MAX] = {};	// �e�N�X�`��

//-------------------------------------
//-	�G�t�F�N�g�̃R���X�g���N�^
//-------------------------------------
CEffect2d::CEffect2d(int nPriority) : CObject2d(nPriority)
{
}

//-------------------------------------
//-	�G�t�F�N�g�̃f�X�g���N�^
//-------------------------------------
CEffect2d::~CEffect2d()
{

}

//-------------------------------------
//- �G�t�F�N�g�̃e�N�X�`���̓ǂݍ���
//-------------------------------------
HRESULT CEffect2d::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

	 // �����������𔲂���
		return E_FAIL;
	}

	// �e�N�X�`���Ǘ��̐���
	CManagerTexture *pManagerTexture = CManager::GetManagerTexture();

	// �e�N�X�`���Ǘ��̗L���𔻒�
	if (pManagerTexture == NULL)
	{
		// �����������𔲂���
		return E_FAIL;
	}

	// �e�N�X�`���ݒ�
	for (int nCount = 0; nCount < TEX_MAX; nCount++)
	{
		// �e�N�X�`���ԍ��̎擾�i�e�N�X�`���̊����j
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureEffect2d[nCount]);

		// �e�N�X�`���̓ǂݍ��ݐ����̗L�����m�F
		if (m_nTextureNldx[nCount] == -1)
		{
			// ���s���ɏ����������𔲂���
			return E_FAIL;
		}
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �G�t�F�N�g�̓ǂݍ��񂾃e�N�X�`���̔j��
//-------------------------------------
void CEffect2d::Unload(void)
{

}

//-------------------------------------
//- �G�t�F�N�g�̏���������
//-------------------------------------
HRESULT CEffect2d::Init(TEX tex)
{
	// �e�N�X�`������
	BindTexture(m_nTextureNldx[tex]);

	// �r���{�[�h�I�u�W�F�N�g�̏�����
	CObject2d::Init();

	// ����ێ�����
	m_dataSizeHold.Set(m_dataSize.Get());
	m_dataColorHold.Set(m_dataColor.Get());

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �G�t�F�N�g�̏I������
//-------------------------------------
void CEffect2d::Uninit(void)
{
	// �r���{�[�h�I�u�W�F�N�g�̏I��
	CObject2d::Uninit();
}

//-------------------------------------
//- �G�t�F�N�g�̍X�V����
//-------------------------------------
void CEffect2d::Update(void)
{
	// �G�t�F�N�g�̉��Z����
	Add();

	// �G�t�F�N�g�̌�������
	if (Sub() == true)
	{
		return;
	}

	// �r���{�[�h�I�u�W�F�N�g�̍X�V����
	CObject2d::Update();
}

//-------------------------------------
//- �G�t�F�N�g�̕`�揈��
//-------------------------------------
void CEffect2d::Draw(void)
{
	// �f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pRenderer == NULL)
	{// ���s��

	 // �����������𔲂���
		return;
	}

	// �ϐ��錾�i���擾�j
	bool bZTestOff = m_bDataZTestOff.Get();	// Z�e�X�g�̗L��

											// �A���t�@�u���f�B���O�̐ݒ�
	pRenderer->SetAlphaBlend(true);

	// �A���t�@�e�X�g�̐ݒ�
	pRenderer->SetAlphaTest(true);

	if (bZTestOff == false)
	{
		// Z�e�X�g�̐ݒ�
		pRenderer->SetZTest(true);
	}

	// �G�t�F�N�g�̕`�揈��
	CObject2d::Draw();

	if (bZTestOff == false)
	{
		// Z�e�X�g�̉���
		pRenderer->SetZTest(false);
	}

	// �A���t�@�u���f�B���O�̉���
	pRenderer->SetAlphaBlend(false);

	// �A���t�@�e�X�g�̉���
	pRenderer->SetAlphaTest(false);
}

//-------------------------------------
//- �G�t�F�N�g�̌�������
//-------------------------------------
void CEffect2d::Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR color, int nLife, bool bZTest)
{
	// ���ݒ�
	m_dataPos.Set(pos);				// �ʒu
	m_dataSize.Set(size);			// �傫��
	m_dataMove.Set(move);			// �ړ���
	m_dataColor.Set(color);			// �F
	m_nDataLife.Set(nLife);			// ����
	m_bDataZTestOff.Set(bZTest);	// Z�e�X�g�̗L��
}

//-------------------------------------
//- �G�t�F�N�g�̐�������
//-------------------------------------
CEffect2d *CEffect2d::Create(TEX tex)
{
	// �G�t�F�N�g�̃|�C���^��錾
	CEffect2d *pCEffect2d = DBG_NEW CEffect2d(7);

	// �����̐����̗L���𔻒�
	if (pCEffect2d != NULL)
	{
		// ����������
		if (FAILED(pCEffect2d->Init(tex)))
		{// ���s��

		 // �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCEffect2d == NULL)
	{// ���s��

	 // �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// ��ނ�ݒ�
	pCEffect2d->SetType(TYPE_EFFECT);

	// �G�t�F�N�g�̃|�C���^��Ԃ�
	return pCEffect2d;
}

//-------------------------------------
//- �G�t�F�N�g�̉��Z����
//-------------------------------------
void CEffect2d::Add(void)
{
	// ���ԊǗ��̏����擾
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// ���ԊǗ��擾�̗L���𔻒�
	if (pManagerTime == NULL)
	{
		// �����𔲂���
		return;
	}

	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();		// �ʒu
	D3DXVECTOR3 move = m_dataMove.Get();	// �ړ���

	// ���Ԕ{���̌v�Z
	D3DXVECTOR3 moveTime = pManagerTime->CalRate(move);

	// �ʒu���X�V
	pos += moveTime;

	// �ʒu�̔��f
	m_dataPos.Set(pos);
	m_dataMove.Set(move);
}

//-------------------------------------
//- �G�t�F�N�g�̌�������
//-------------------------------------
bool CEffect2d::Sub(void)
{
	// ���ԊǗ��̏����擾
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// ���ԊǗ��擾�̗L���𔻒�
	if (pManagerTime == NULL)
	{
		// �����𔲂���
		return false;
	}

	// �ϐ���錾�i���擾�j
	D3DXVECTOR3 size = m_dataSize.Get();			// �傫��
	D3DXVECTOR3 sizeHold = m_dataSizeHold.Get();	// �ێ�����傫��
	D3DXCOLOR color = m_dataColor.Get();			// �F
	D3DXCOLOR colorHold = m_dataColorHold.Get();	// �ێ�����F
	int nLife = m_nDataLife.Get();					// �̗�

	// ���Ԕ{���̌v�Z�i�T�C�Y�̌����ʎZ�o�j
	float nTimeEffectSizeX = pManagerTime->CalRate(sizeHold.x / nLife);
	float nTimeEffectSizeY = pManagerTime->CalRate(sizeHold.y / nLife);

	// �傫�������炷
	size.x -= nTimeEffectSizeX;
	size.y -= nTimeEffectSizeY;

	// ���Ԕ{���̌v�Z�i�F�̌����ʎZ�o�j
	float nTimeEffectColorA = pManagerTime->CalRate(colorHold.a / nLife);

	// �F�̃��l������
	color.a -= nTimeEffectColorA;

	// �����J�E���g�̗L���𔻒�
	if (pManagerTime->m_bDataIntCount.Get() == true)
	{
		// �ێ���������X�V
		sizeHold = size;
		colorHold = color;

		// �̗͂����炷
		nLife--;
	}

	// �̗͂̔���
	if (nLife <= 0)
	{
		// �I������
		Uninit();

		// ������Ԃ�
		return true;
	}

	// ���X�V
	m_dataSize.Set(size);			// �傫��
	m_dataSizeHold.Set(sizeHold);	// �ێ�����傫��
	m_dataColor.Set(color);			// �F
	m_dataColorHold.Set(colorHold);	// �ێ�����F
	m_nDataLife.Set(nLife);			// �̗�

									// ���s��Ԃ�
	return false;
}
