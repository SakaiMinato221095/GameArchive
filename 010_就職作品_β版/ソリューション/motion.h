
//-===============================================
//-
//-	モーション処理のヘッダー[motion.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _MOTION_H_		// このマクロが定義されなかったら
#define _MOTION_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "model.h"

//-======================================
//-	マクロ定義
//-======================================

#define KEY_INFO_NUM_MAX	(32)	// キーの総数の最大数
#define MOTION_TYPE_NUM_MAX	(64)	// モーション種類の総数の最大数

//-======================================
//-	構造体定義
//-======================================

//-======================================
//-	クラス定義
//-======================================

class CMotion
{

public:
	
	// モデルの種類
	typedef enum
	{
		MOTION_TYPE_PLAYER = 0,		// プレイヤー
		MOTION_TYPE_ALIEN_000,		// 敵000
		MOTION_TYPE_ENEMY_BOSS,		// 敵ボス
		MOTION_TYPE_MAX
	}MOTION_TYPE;

	// モーション情報の構造体
	typedef struct
	{
		D3DXVECTOR3 pos;		// 位置
		D3DXVECTOR3 posOld;		// 前回の位置
		D3DXVECTOR3 rot;		// 向き
		D3DXVECTOR3 rotOld;		// 前回の向き
	}MotionData;

	// キー要素の構造体
	typedef struct
	{
		float fPosX;	// X軸の位置
		float fPosY;	// Y軸の位置
		float fPosZ;	// Z軸の位置

		float fRotX;	// X軸の向き
		float fRotY;	// Y軸の向き
		float fRotZ;	// Z軸の向き
	}Key;

	// キー情報の構造体
	typedef struct
	{
		int nFrame;						// 再生フレーム
		Key aKey[MODEL_PARTS_MAX];		// 各モデルのキー要素
	}KeyInfo;
	
	// モーション情報の構造体
	typedef struct
	{
		bool bLoop;							// ループの有無
		int nNumKey;						// キーの総数
		KeyInfo aKeyInfo[KEY_INFO_NUM_MAX];	// キー情報
	}Info;

	CMotion();
	~CMotion();

	HRESULT Init(int nNumModel, int nNumState);
	void Uninit(void);

	static CMotion * Create(int nNumModel,int nNumState);

	void Set(int nType);
	void BlendSet(void);
	void Update(void);

	void SetFile(MOTION_TYPE MotionType);

	int GetType(void) { return m_nType; }
	bool IsFinsih(void) { return m_bFinish; }
	int GetKey(void) { return m_nKey; }

	void SetInfo(Info info) { m_aInfo[m_nType] = info; }
	void SetModel(CModel** ppModel, int nNumModel) { m_ppModel = &ppModel[nNumModel]; }

	bool GetBlend(void) { return m_bBlend; }
	bool GetChangeBlend(void) { return m_bChangeBlend; }

private:

	void UpdateNormal(void);
	void UpdateBlend(void);
	void UpdateChangeBlend(void);

	Info m_aInfo[MOTION_TYPE_NUM_MAX];	// キー情報

	MotionData m_aMotionData[MODEL_PARTS_MAX];

	int m_nNumState;		// モーションの種類の数
	int m_nNumAll;			// 

	bool m_bMotionUse;		// 現在のモーションの有無

	int m_nType;			// モーションの種類
	bool m_bLoop;			// 現在のループの状況
	int m_nNumKey;			// キーの数
	int m_nKey;				// 現在のキー
	int m_nCounter;			// 現在のカウンター
	bool m_bFinish;			// 終了の有無

	bool m_bBlend;			// モーションブレンドの有無
	bool m_bChangeBlend;	// 切り替え時のモーションブレンドの有無

	CModel ** m_ppModel;	// モデルのポインタ
	int m_nNumModel;		// モデルの総数
};

#endif	// 二重インクルード防止の終了
