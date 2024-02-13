
//-===============================================
//-
//-	�G�t�F�N�g�̏���[effect.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "effect.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//= �R���X�g��`
//=======================================

// �G�t�F�N�g�e�N�X�`���̃R���X�g��`
const char *pTextureEffect[] =
{
	"data\\TEXTURE\\effect000.jpg"	// �ʏ�G�t�F�N�g_000�̃e�N�X�`��
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

int CEffect::m_nTextureNldx[TEX_MAX] = {};	// �e�N�X�`��

//-------------------------------------
//-	�G�t�F�N�g�̃R���X�g���N�^
//-------------------------------------
 CEffect::CEffect(int nPriority) : CBillboard(nPriority)
{
	 ZeroMemory(&m_data,sizeof(m_data));
}

//-------------------------------------
//-	�G�t�F�N�g�̃f�X�g���N�^
//-------------------------------------
CEffect::~CEffect()
{

}

//-------------------------------------
//- �G�t�F�N�g�̃e�N�X�`���̓ǂݍ���
//-------------------------------------
HRESULT CEffect::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

	 // �����������𔲂���
		return E_FAIL;
	}

	// �e�N�X�`���Ǘ��̐���
	CManagerTexture *pManagerTexture = CManager::GetInstance()->GetManagerTexture();

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
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureEffect[nCount]);

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
void CEffect::Unload(void)
{

}

//-------------------------------------
//- �G�t�F�N�g�̏���������
//-------------------------------------
HRESULT CEffect::Init(TEX tex)
{
	// �e�N�X�`������
	BindTexture(m_nTextureNldx[tex]);

	// �r���{�[�h�I�u�W�F�N�g�̏�����
	CBillboard::Init();

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �G�t�F�N�g�̏I������
//-------------------------------------
void CEffect::Uninit(void)
{
	// �r���{�[�h�I�u�W�F�N�g�̏I��
	CBillboard::Uninit();
}

//-------------------------------------
//- �G�t�F�N�g�̍X�V����
//-------------------------------------
void CEffect::Update(void)
{
	// �G�t�F�N�g�̉��Z����
	Add();

	// �G�t�F�N�g�̌�������
	if (Sub() == true)
	{
		return;
	}

	// �r���{�[�h�I�u�W�F�N�g�̍X�V����
	CBillboard::Update();
}

//-------------------------------------
//- �G�t�F�N�g�̕`�揈��
//-------------------------------------
void CEffect::Draw(void)
{
	// �f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pRenderer == NULL)
	{// ���s��

		// �����������𔲂���
		return;
	}

	// �A���t�@�u���f�B���O�̐ݒ�
	pRenderer->SetAlphaBlend(true);

	// �A���t�@�e�X�g�̐ݒ�
	pRenderer->SetAlphaTest(true);

	if (m_data.bIsZTestStop == false)
	{
		// Z�e�X�g�̐ݒ�
		pRenderer->SetZTest(true);
	}

	// �G�t�F�N�g�̕`�揈��
	CBillboard::Draw();

	if (m_data.bIsZTestStop == false)
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
void CEffect::Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR color, int nLife, bool bZTest)
{
	SetPos(pos);
	SetSize(size);
	SetColor(color);
	
	m_data.move = move;
	m_data.nLife = nLife;
	m_data.bIsZTestStop = bZTest;
}

//-------------------------------------
//- �G�t�F�N�g�̐�������
//-------------------------------------
CEffect *CEffect::Create(TEX tex)
{
	// �G�t�F�N�g�̃|�C���^��錾
	CEffect *pCEffect = DBG_NEW CEffect(3);

	// �����̐����̗L���𔻒�
	if (pCEffect != NULL)
	{
		// ����������
		if (FAILED(pCEffect->Init(tex)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCEffect == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �G�t�F�N�g�̃|�C���^��Ԃ�
	return pCEffect;
}

//-------------------------------------
//- �G�t�F�N�g�̉��Z����
//-------------------------------------
void CEffect::Add(void)
{
	// �ʒu�̍X�V
	SetPos(GetPos() + m_data.move);
}

//-------------------------------------
//- �G�t�F�N�g�̌�������
//-------------------------------------
bool CEffect::Sub(void)
{	
	D3DXVECTOR3 size = GetSize();
	D3DXCOLOR color = GetColor();

	// �傫�������炷
	size.x -= (m_data.sizeHold.x / m_data.nLife);
	size.z -= (m_data.sizeHold.z / m_data.nLife);
	SetSize(size);

	// ���l�����炷
	color.a -= (m_data.colorHold.a / m_data.nLife);
	SetColor(color);

	// �̗͂����炷
	m_data.nLife--;

	// �̗͂̔���
	if (m_data.nLife <= 0)
	{
		// �I������
		Uninit();

		// ������Ԃ�
		return true;
	}

	// ���s��Ԃ�
	return false;
}
