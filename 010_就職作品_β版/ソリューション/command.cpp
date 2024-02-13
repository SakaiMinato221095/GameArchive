
//-===============================================
//-
//-	�R�}���h����[command.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "command.h"

#include "renderer.h"
#include "manager.h"

#include "debugproc.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-======================================
//-	�R���X�g��`
//-======================================

// ���͎�t����
const int WINDOW_TIME = 180;

const CCommand::DataCommand DATA_COMMAND[CCommand::COMMAND_TYPE_MAX] =
{
	3,	// �t�B�j�b�V���܂ł̉�

	CCommand::INPUT_TYPE_PUNCH,
	CCommand::INPUT_TYPE_PUNCH,
	CCommand::INPUT_TYPE_PUNCH,
	CCommand::INPUT_TYPE_NONE,
	CCommand::INPUT_TYPE_NONE,

	3,	// �t�B�j�b�V���܂ł̉�

	CCommand::INPUT_TYPE_KICK,
	CCommand::INPUT_TYPE_KICK,
	CCommand::INPUT_TYPE_KICK,
	CCommand::INPUT_TYPE_NONE,
	CCommand::INPUT_TYPE_NONE,
};

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CCommand::CCommand()
{
	ZeroMemory(&m_dataCommand, sizeof(m_dataCommand));
	ZeroMemory(&m_InfoCombo, sizeof(m_InfoCombo));
	ZeroMemory(&m_InfoFinish,sizeof(m_InfoFinish));
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CCommand::~CCommand()
{

}

//-------------------------------------
//- �퓬�v���C���[�̏���������
//-------------------------------------
HRESULT CCommand::Init(void)
{
	// �����ݒ�f�[�^
	SetInitData();

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �퓬�v���C���[�̏I������
//-------------------------------------
void CCommand::Uninit(void)
{

}

//-------------------------------------
//- �퓬�v���C���[�̍X�V����
//-------------------------------------
void CCommand::Update(void)
{
	if (m_InfoCombo.nNum > 0)
	{
		m_InfoCombo.nWindowTimeCnt++;

		if (m_InfoCombo.nWindowTimeCnt >= WINDOW_TIME)
		{
			// �R���{�̃��Z�b�g����
			ReSetCombo();
		}
	}

	// �f�o�b�N�\��
	Debug();
}

//-------------------------------------
//- �퓬�v���C���[�̕`�揈��
//-------------------------------------
void CCommand::Draw(void)
{

}

//-------------------------------------
//- �퓬�v���C���[�̕`�揈��
//-------------------------------------
bool CCommand::SetInput(INPUT_TYPE inputType)
{
	// �t�B�j�b�V���̗L��
	bool bFinish = false;

	// �R���{��t���Ԃ�������
	m_InfoCombo.nWindowTimeCnt = 0;

	if (m_InfoCombo.nNum >= COMMAND::COMBO_NUM_MAX)
	{
		// �R���{�̃��Z�b�g����
		ReSetCombo();
	}

	for (int nCntCommand = 0; nCntCommand < COMMAND_TYPE_MAX; nCntCommand++)
	{
		// �R���{��
		if (m_InfoCombo.InfoCommand[nCntCommand].bIsCombo)
		{
			// �R���{
			for (int nCntCombo = m_InfoCombo.nNum; nCntCombo < COMMAND::COMBO_NUM_MAX; nCntCombo++)
			{
				// �R�}���h���͂Ɠ��͏��𔻒�
				if (m_dataCommand[nCntCommand].aInputType[m_InfoCombo.InfoCommand[nCntCommand].nNumCombo] == inputType)
				{
					// �R���{�񐔂����Z
					m_InfoCombo.InfoCommand[nCntCommand].nNumCombo++;

					// �t�B�j�b�V���̗L���𔻒�
					if (m_dataCommand[nCntCommand].nInputNumFinish <= m_InfoCombo.InfoCommand[nCntCommand].nNumCombo)
					{
						// �R���{�̃��Z�b�g����
						ReSetCombo();

						// �t�B�j�b�V���R�}���h��ݒ�
						m_InfoFinish.type = (COMMAND_TYPE)nCntCommand;

						// �t�B�j�b�V����Ԃ�
						bFinish = true;
						return bFinish;
					}
					else
					{
						// �R���{���ɕύX
						m_InfoCombo.InfoCommand[nCntCommand].bIsCombo = true;

						break;
					}
				}
				else
				{
					// �R�}���h�̃R���{����������
					m_InfoCombo.InfoCommand[nCntCommand].nNumCombo = 0;

					// �R�}���h���R���{��������
					m_InfoCombo.InfoCommand[nCntCommand].bIsCombo = false;
				}
			}
		}
		// �R���{�n���\�̗L��
 		else if (m_dataCommand[nCntCommand].nInputNumFinish > m_InfoCombo.nNum)
		{
			// �R���{�n���Ɠ��͂̔�r
			if (m_dataCommand[nCntCommand].aInputType[0] == inputType)
			{
				// �R�}���h�̃R���{�������Z
				m_InfoCombo.InfoCommand[nCntCommand].nNumCombo++;

				// �R�}���h���R���{����
				m_InfoCombo.InfoCommand[nCntCommand].bIsCombo = true;
			}
		}
	}

	// �R���{�������Z
	m_InfoCombo.nNum++;

	return bFinish;
}

//-------------------------------------
//- �퓬�v���C���[�̐�������
//-------------------------------------
CCommand* CCommand::Create(void)
{
	// �퓬�v���C���[�̃|�C���^��錾
	CCommand* pCCommand = DBG_NEW CCommand;

	// �����̐����̗L���𔻒�
	if (pCCommand != NULL)
	{
		// ����������
		if (FAILED(pCCommand->Init()))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCCommand == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �퓬�v���C���[�̃|�C���^��Ԃ�
	return pCCommand;
}

//-------------------------------------
//- �퓬�v���C���[�̏����ݒ�f�[�^
//-------------------------------------
void CCommand::SetInitData(void)
{
	for (int nCntCommand = 0; nCntCommand < COMMAND_TYPE_MAX; nCntCommand++)
	{
		// ������
		m_dataCommand[nCntCommand] = DATA_COMMAND[nCntCommand];
	}
}

//-------------------------------------
//- �퓬�v���C���[�̃R���{���Z�b�g����
//-------------------------------------
void CCommand::ReSetCombo(void)
{
	ZeroMemory(&m_InfoCombo, sizeof(m_InfoCombo));
}

//-------------------------------------
//- �퓬�v���C���[�̃f�o�b�N�\��
//-------------------------------------
void CCommand::Debug(void)
{
	// �f�o�b�N�v���b�N�̎擾
	CDebugProc* pDebugProc = CManager::GetInstance()->GetDbugProc();

	// �f�o�b�N�v���b�N�擾�̗L���𔻒�
	if (pDebugProc == NULL)
	{
		return;
	}

	pDebugProc->Print("-----�R�}���h-----");
	pDebugProc->Print("\n");
	pDebugProc->Print("�R���{��");
	pDebugProc->Print("\n");
	pDebugProc->Print("%d", m_InfoCombo.nNum);
	pDebugProc->Print("\n");
}