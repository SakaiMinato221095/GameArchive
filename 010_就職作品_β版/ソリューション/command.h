
//-===============================================
//-
//-	コマンド処理のヘッダー[command.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _COMMAND_H_		// このマクロが定義されなかったら
#define _COMMAND_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

//=======================================
//=	コンスト定義
//=======================================

namespace COMMAND
{
	const int COMBO_NUM_MAX = 5;	// コンボの最大数
}

//-======================================
//-	クラス定義
//-======================================

class CCommand
{

public:

	// 入力の種類
	enum INPUT_TYPE
	{
		INPUT_TYPE_NONE = 0,	// なし
		INPUT_TYPE_PUNCH,		// パンチ
		INPUT_TYPE_KICK,		// キック
		INPUT_TYPE_MAX
	};

	// コマンドの種類
	enum COMMAND_TYPE
	{
		COMMAND_TYPE_PUNCH_NOR = 0,	// パンチ基本コマンド
		COMMAND_TYPE_KICK_NOR,		// キック基本コマンド
		COMMAND_TYPE_MAX
	};

	// コマンドの資料情報
	struct DataCommand
	{
		int nInputNumFinish;							// フィニッシュまでの回数
		INPUT_TYPE aInputType[COMMAND::COMBO_NUM_MAX];	// 入力の種類
	};

	// コマンドの情報
	struct InfoCommand
	{
		bool bIsCombo;				// コンボの有無
		int nNumCombo;				// 現在のコンボ数
	};

	// コンボの情報
	struct InfoCombo
	{
		int nNum;										// 現在のコマンド回数
		int nWindowTimeCnt;								// 受付時間

		InfoCommand InfoCommand[COMMAND_TYPE_MAX];		// コマンド情報
	};

	// フィニッシュの情報
	struct InfoFinish
	{
		COMMAND_TYPE type;			// 種類を格納
	};

	CCommand();
	~CCommand();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	bool SetInput(INPUT_TYPE inputType);

	static CCommand* Create();

	void SetInfoCommand(int nNum, InfoCommand infoCommand) { m_InfoCombo.InfoCommand[nNum] = infoCommand; }
	InfoCommand GetInfoCommand(int nNum) { return m_InfoCombo.InfoCommand[nNum]; }

	void SetInfoCombo(InfoCombo infoCombo) { m_InfoCombo = infoCombo; }
	InfoCombo GetInfoCombo(void) { return m_InfoCombo; }

	InfoFinish GetInfoFinish(void) { return m_InfoFinish; }

private:

	void SetInitData(void);

	void ReSetCombo(void);

	void Debug(void);

	DataCommand m_dataCommand[COMMAND_TYPE_MAX];	// 資料情報
	InfoCombo m_InfoCombo;							// コンボ情報
	InfoFinish m_InfoFinish;						// フィニッシュの情報

};

#endif	// 二重インクルード防止の終了
