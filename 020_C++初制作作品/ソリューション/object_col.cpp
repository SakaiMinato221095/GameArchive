
//================================================
//=
//=	�����蔻��I�u�W�F�N�g����[object_col.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "object_col.h"

#include "obj_3d_wall.h"
#include "obj_3d_field.h"

//=======================================
//=	�}�N����`
//=======================================

//-------------------------------------
//-	�����蔻��I�u�W�F�N�g�̃R���X�g���N�^
//-------------------------------------
CObjectCol::CObjectCol()
{
	ZeroMemory(m_apObj3dWall,sizeof(m_apObj3dWall));
	ZeroMemory(m_apObj3dField, sizeof(m_apObj3dField));
}

//-------------------------------------
//-	�����蔻��I�u�W�F�N�g�̃f�X�g���N�^
//-------------------------------------
CObjectCol::~CObjectCol()
{
}

//-------------------------------------
//-	�����蔻��I�u�W�F�N�g�̏�����
//-------------------------------------
HRESULT CObjectCol::Init(void)
{
	for (int nCount = 0; nCount < TYPE_WALL_MAX; nCount++)
	{
		// 3D�ǂ̐�������
		m_apObj3dWall[nCount] = CObj3dWall::Create(CObj3dWall::TEX_NULL);

		// 3D�ǂ̐��������̔���
		if (m_apObj3dWall[nCount] == NULL)
		{
			// �����𔲂���
			return E_FAIL;
		}
	}

	for (int nCount = 0; nCount < TYPE_FIELD_MAX; nCount++)
	{
		// 3D�n�ʂ̐�������
		m_apObj3dField[nCount] = CObj3dField::Create(CObj3dField::TEX_NULL);

		//  3D�n�ʂ̐��������̔���
		if (m_apObj3dField[nCount] == NULL)
		{
			// �����𔲂���
			return E_FAIL;
		}
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//-	�����蔻��I�u�W�F�N�g�̏I������
//-------------------------------------
void CObjectCol::Uninit(void)
{
	for (int nCount = 0; nCount < TYPE_WALL_MAX; nCount++)
	{
		// 3D�ǂ̏I������
		m_apObj3dWall[nCount]->Uninit();

		// 3D�ǂ̃|�C���^������
		m_apObj3dWall[nCount] = NULL;
	}

	for (int nCount = 0; nCount < TYPE_FIELD_MAX; nCount++)
	{
		// 3D�n�ʂ̏I������
		m_apObj3dField[nCount]->Uninit();

		// 3D�n�ʂ̃|�C���^������
		m_apObj3dField[nCount] = NULL;
	}
}

//-------------------------------------
//-	�����蔻��I�u�W�F�N�g�̍X�V����
//-------------------------------------
void CObjectCol::Update(void)
{
	// 3D�I�u�W�F�N�g�̐ݒ�
	SetObjectCol();
}

//-------------------------------------
//-	�����蔻��I�u�W�F�N�g�̕`�揈��
//-------------------------------------
void CObjectCol::Draw(void)
{

}

//-------------------------------------
//-	�����蔻��I�u�W�F�N�g�̐�������
//-------------------------------------
CObjectCol * CObjectCol::Create(void)
{
	// 3D�I�u�W�F�N�g�̃|�C���^��錾
	CObjectCol *pObject3d = new CObjectCol;

	// �����̐����̗L���𔻒�
	if (pObject3d != NULL)
	{
		// ����������
		if (FAILED(pObject3d->Init()))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pObject3d == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// 3D�I�u�W�F�N�g�̃|�C���^��Ԃ�
	return pObject3d;
}

//-------------------------------------
//-	�����蔻��I�u�W�F�N�g�̐ݒ菈��
//-------------------------------------
void CObjectCol::Set(D3DXVECTOR3 pos,D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	// �����
	m_dataPos.Set(pos);		// �ʒu
	m_dataSize.Set(size);	// �T�C�Y
	m_dataRot.Set(rot);		// ����

	SetObjectCol();			// 3D�I�u�W�F�N�g�̐ݒ�
}

//-------------------------------------
//-	�����蔻��I�u�W�F�N�g��3D�I�u�W�F�N�g�̐ݒ菈��
//-------------------------------------
void CObjectCol::SetObjectCol(void)
{
	// ���擾
	D3DXVECTOR3 pos = m_dataPos.Get();			// �ʒu
	D3DXVECTOR3 size = m_dataSize.Get();		// �T�C�Y
	D3DXVECTOR3 rot = m_dataRot.Get();			// ����
	D3DXCOLOR color = m_dataColor.Get();		// �F

	//// 3D�I�u�W�F�N�g�i���j�̐ݒ菈��
	//m_apObj3dWall[TYPE_WALL_LEFT]->Set(
	//	D3DXVECTOR3(pos.x + 0.0f, pos.y + 0.0f, pos.z + size.z),
	//	D3DXVECTOR3(size.x, size.y, size.z),
	//	D3DXVECTOR3(0.0f, rot.y, 0.0f),
	//	D3DXCOLOR(color));

	//// 3D�I�u�W�F�N�g�i�E�j�̐ݒ菈��
	//m_apObj3dWall[TYPE_WALL_RIGHT]->Set(
	//	D3DXVECTOR3(pos.x + 0.0f, pos.y + 0.0f, pos.z - size.z),
	//	D3DXVECTOR3(size.x, size.y, size.z),
	//	D3DXVECTOR3(0.0f, rot.y, 0.0f),
	//	D3DXCOLOR(color));

	//// 3D�I�u�W�F�N�g�i��O�j�̐ݒ菈��
	//m_apObj3dWall[TYPE_WALL_NEAR]->Set(
	//	D3DXVECTOR3(pos.x + size.x, pos.y + 0.0f, pos.z + 0.0f),
	//	D3DXVECTOR3(size.z, size.y, size.z),
	//	D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
	//	D3DXCOLOR(color));

	//// 3D�I�u�W�F�N�g�i���j�̐ݒ菈��
	//m_apObj3dWall[TYPE_WALL_BACK]->Set(
	//	D3DXVECTOR3(pos.x - size.x, pos.y + 0.0f, pos.z + 0.0f),
	//	D3DXVECTOR3(size.z, size.y, size.z),
	//	D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
	//	D3DXCOLOR(color));

	// 3D�I�u�W�F�N�g�i���j�̐ݒ菈��
	m_apObj3dField[TYPE_FIELD_BOTTOM]->Set(
		D3DXVECTOR3(pos.x + 0.0f, pos.y + 0.0f, pos.z + 0.0f),
		D3DXVECTOR3(size.x, size.y, size.z),
		D3DXVECTOR3(0.0f, rot.y, 0.0f),
		D3DXCOLOR(color));

	//// 3D�I�u�W�F�N�g�i��j�̐ݒ菈��
	//m_apObj3dField[TYPE_FIELD_TOP]->Set(
	//	D3DXVECTOR3(pos.x + 0.0f, pos.y + size.y, pos.z + 0.0f),
	//	D3DXVECTOR3(size.x, size.y, size.z),
	//	D3DXVECTOR3(0.0f, rot.y, 0.0f),
	//	D3DXCOLOR(color));
}

//-------------------------------------
//-	�����蔻��I�u�W�F�N�g�̓����蔻�菈��
//-------------------------------------
bool CObjectCol::Collision(D3DXVECTOR3 posGet, D3DXVECTOR3 sizeGet)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();		// �ʒu
	D3DXVECTOR3 size = m_dataSize.Get();	// �傫��

	// ��`�̓����蔻��
	if (pos.x + size.x >= posGet.x - sizeGet.x &&
		pos.x - size.x <= posGet.x + sizeGet.x &&
		pos.z + size.z >= posGet.z - sizeGet.z &&
		pos.z - size.z <= posGet.z + sizeGet.z)
	{
		// ������Ԃ�
		return true;
	}

	// �Ȃ���Ԃ�
	return false;
}