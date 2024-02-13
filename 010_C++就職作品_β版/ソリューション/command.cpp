
//-===============================================
//-
//-	コマンド処理[command.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "command.h"

#include "renderer.h"
#include "manager.h"

#include "debugproc.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	静的変数宣言
//-======================================

//-======================================
//-	コンスト定義
//-======================================

// 入力受付時間
const int WINDOW_TIME = 180;

const CCommand::DataCommand DATA_COMMAND[CCommand::COMMAND_TYPE_MAX] =
{
	3,	// フィニッシュまでの回数

	CCommand::INPUT_TYPE_PUNCH,
	CCommand::INPUT_TYPE_PUNCH,
	CCommand::INPUT_TYPE_PUNCH,
	CCommand::INPUT_TYPE_NONE,
	CCommand::INPUT_TYPE_NONE,

	3,	// フィニッシュまでの回数

	CCommand::INPUT_TYPE_KICK,
	CCommand::INPUT_TYPE_KICK,
	CCommand::INPUT_TYPE_KICK,
	CCommand::INPUT_TYPE_NONE,
	CCommand::INPUT_TYPE_NONE,
};

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CCommand::CCommand()
{
	ZeroMemory(&m_dataCommand, sizeof(m_dataCommand));
	ZeroMemory(&m_InfoCombo, sizeof(m_InfoCombo));
	ZeroMemory(&m_InfoFinish,sizeof(m_InfoFinish));
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CCommand::~CCommand()
{

}

//-------------------------------------
//- 戦闘プレイヤーの初期化処理
//-------------------------------------
HRESULT CCommand::Init(void)
{
	// 初期設定データ
	SetInitData();

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 戦闘プレイヤーの終了処理
//-------------------------------------
void CCommand::Uninit(void)
{

}

//-------------------------------------
//- 戦闘プレイヤーの更新処理
//-------------------------------------
void CCommand::Update(void)
{
	if (m_InfoCombo.nNum > 0)
	{
		m_InfoCombo.nWindowTimeCnt++;

		if (m_InfoCombo.nWindowTimeCnt >= WINDOW_TIME)
		{
			// コンボのリセット処理
			ReSetCombo();
		}
	}

	// デバック表示
	Debug();
}

//-------------------------------------
//- 戦闘プレイヤーの描画処理
//-------------------------------------
void CCommand::Draw(void)
{

}

//-------------------------------------
//- 戦闘プレイヤーの描画処理
//-------------------------------------
bool CCommand::SetInput(INPUT_TYPE inputType)
{
	// フィニッシュの有無
	bool bFinish = false;

	// コンボ受付時間を初期化
	m_InfoCombo.nWindowTimeCnt = 0;

	if (m_InfoCombo.nNum >= COMMAND::COMBO_NUM_MAX)
	{
		// コンボのリセット処理
		ReSetCombo();
	}

	for (int nCntCommand = 0; nCntCommand < COMMAND_TYPE_MAX; nCntCommand++)
	{
		// コンボ中
		if (m_InfoCombo.InfoCommand[nCntCommand].bIsCombo)
		{
			// コンボ
			for (int nCntCombo = m_InfoCombo.nNum; nCntCombo < COMMAND::COMBO_NUM_MAX; nCntCombo++)
			{
				// コマンド入力と入力情報を判定
				if (m_dataCommand[nCntCommand].aInputType[m_InfoCombo.InfoCommand[nCntCommand].nNumCombo] == inputType)
				{
					// コンボ回数を加算
					m_InfoCombo.InfoCommand[nCntCommand].nNumCombo++;

					// フィニッシュの有無を判定
					if (m_dataCommand[nCntCommand].nInputNumFinish <= m_InfoCombo.InfoCommand[nCntCommand].nNumCombo)
					{
						// コンボのリセット処理
						ReSetCombo();

						// フィニッシュコマンドを設定
						m_InfoFinish.type = (COMMAND_TYPE)nCntCommand;

						// フィニッシュを返す
						bFinish = true;
						return bFinish;
					}
					else
					{
						// コンボ中に変更
						m_InfoCombo.InfoCommand[nCntCommand].bIsCombo = true;

						break;
					}
				}
				else
				{
					// コマンドのコンボ数を初期化
					m_InfoCombo.InfoCommand[nCntCommand].nNumCombo = 0;

					// コマンドをコンボ中を解除
					m_InfoCombo.InfoCommand[nCntCommand].bIsCombo = false;
				}
			}
		}
		// コンボ始動可能の有無
 		else if (m_dataCommand[nCntCommand].nInputNumFinish > m_InfoCombo.nNum)
		{
			// コンボ始動と入力の比較
			if (m_dataCommand[nCntCommand].aInputType[0] == inputType)
			{
				// コマンドのコンボ数を加算
				m_InfoCombo.InfoCommand[nCntCommand].nNumCombo++;

				// コマンドをコンボ中に
				m_InfoCombo.InfoCommand[nCntCommand].bIsCombo = true;
			}
		}
	}

	// コンボ数を加算
	m_InfoCombo.nNum++;

	return bFinish;
}

//-------------------------------------
//- 戦闘プレイヤーの生成処理
//-------------------------------------
CCommand* CCommand::Create(void)
{
	// 戦闘プレイヤーのポインタを宣言
	CCommand* pCCommand = DBG_NEW CCommand;

	// 生成の成功の有無を判定
	if (pCCommand != NULL)
	{
		// 初期化処理
		if (FAILED(pCCommand->Init()))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCCommand == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// 戦闘プレイヤーのポインタを返す
	return pCCommand;
}

//-------------------------------------
//- 戦闘プレイヤーの初期設定データ
//-------------------------------------
void CCommand::SetInitData(void)
{
	for (int nCntCommand = 0; nCntCommand < COMMAND_TYPE_MAX; nCntCommand++)
	{
		// 情報を代入
		m_dataCommand[nCntCommand] = DATA_COMMAND[nCntCommand];
	}
}

//-------------------------------------
//- 戦闘プレイヤーのコンボリセット処理
//-------------------------------------
void CCommand::ReSetCombo(void)
{
	ZeroMemory(&m_InfoCombo, sizeof(m_InfoCombo));
}

//-------------------------------------
//- 戦闘プレイヤーのデバック表示
//-------------------------------------
void CCommand::Debug(void)
{
	// デバックプロックの取得
	CDebugProc* pDebugProc = CManager::GetInstance()->GetDbugProc();

	// デバックプロック取得の有無を判定
	if (pDebugProc == NULL)
	{
		return;
	}

	pDebugProc->Print("-----コマンド-----");
	pDebugProc->Print("\n");
	pDebugProc->Print("コンボ回数");
	pDebugProc->Print("\n");
	pDebugProc->Print("%d", m_InfoCombo.nNum);
	pDebugProc->Print("\n");
}