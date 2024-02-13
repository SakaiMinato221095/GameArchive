
//-===============================================
//-
//-	スコアの処理のヘッダー[score.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _SCORE_H_		// このマクロが定義されなかったら
#define _SCORE_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "number.h"

#include "data.h"

//-======================================
//-	マクロ定義
//-======================================

#define DIGITS_SCORE	(8)		// スコアの桁数

//-======================================
//-	クラス定義
//-======================================

class CScore
{
public:
	
	typedef enum
	{
		GET_TYPE_NORMAL = 0,	// 一定量のスコア
		GET_TYPE_RANDOM,		// ランダム性があるスコア
		GET_TYPE_MAX
	}GET_TYPE;

	CScore();
	~CScore();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScore *Create(void);
	HRESULT CreateNumber(void);

	void NullAllNumber(void);

	void NumberTex(void);

	void Add(GET_TYPE getType, int nAddScore);

	int CalRandom(int nAddScore);

	void SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 interval);

	void SetSize(D3DXVECTOR3 size);

	void SetColor(void);

	void SetNumber(void);

	CDataD3DXVECTOR3 m_dataPos;			// 位置
	CDataD3DXVECTOR3 m_dataInterval;	// 間隔
	CDataD3DXVECTOR3 m_dataSize;		// 大きさ

	CDataInt m_nDataScore;				// スコアの値

private:

	CNumber *m_apNumber[DIGITS_SCORE];	// 数字のポインタ

};

//-======================================
//- プロトタイプ宣言
//-======================================

#endif	// 二重インクルード防止の終了
