
//================================================
//=
//=	当たり判定管理の処理のヘッダー[mgr_coll.h]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	二重インクルード防止
//=======================================

#ifndef _MGR_COLL_H_		// このマクロが定義されなかったら
#define _MGR_COLL_H_		// 二重インクルード帽子のマクロを定義

//=======================================
//=	インクルード
//=======================================

#include "object.h"

//=======================================
//=	マクロ定義
//=======================================

#define COLLSION_NUM_MAX		(1024)	// 当たり判定の最大数

//=======================================
//=	前方宣言
//=======================================

class CColl;

//-======================================
//-	クラス定義
//-======================================

// 接触のクラス
class CMgrColl
{

public:

	// 当たり判定タグ
	typedef enum
	{
		TAG_NONE = 0,			// 効果なし
		TAG_PLAYER,				// プレイヤー
		TAG_ENEMY,				// 敵
		TAG_ATTACK,				// 攻撃
		TAG_WALL_X,				// X軸の壁
		TAG_WALL_Z,				// Z軸の壁
		TAG_SPAWN_ENEMY_WALL,	// 敵出現壁
		TAG_MAX
	}TAG;

	// 当たり方の種類
	enum EVENT_TYPE
	{
		EVENT_TYPE_TRIGGER = 0,		// トリガー
		EVENT_TYPE_PRESS,			// プレス
		EVENT_TYPE_MAX
	};

	// 軸
	typedef enum
	{
		TYPE_SXIS_X = 0,	// X軸
		TYPE_SXIS_Y,		// Y軸
		TYPE_SXIS_Z,		// Z軸
		TYPE_SXIS_MAX,
	}TYPE_SXIS;

	CMgrColl();
	~CMgrColl();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CMgrColl *Create(void);

	bool Hit(int nNldxColl, TAG hitTag, EVENT_TYPE eventType);
	bool HitSide(int nNldxColl, CMgrColl::TAG hitTag, EVENT_TYPE eventType,  CMgrColl::TYPE_SXIS typeSxis);

	int Set(CColl *pColl);
	void Reset(int nNldx);

	CColl* GetColl(int nNldx) { return m_apColl[nNldx]; }

private:

	void SetHit(CColl* pCollMy, int nNldx, CObject* pObjPair,float fLength);

	bool hitRectangle(D3DXVECTOR3 posMy, D3DXVECTOR3 sizeMy, D3DXVECTOR3 posPair, D3DXVECTOR3 sizePair);
	bool hitRectangleSide(float fPos, float fSize, float fPosPair, float fSizePair);

	CColl *m_apColl[COLLSION_NUM_MAX];	// 当たり判定の情報
	int m_nNldxMax;						// 現在の番号の最大数
};

#endif	// 二重インクルード防止の終了
