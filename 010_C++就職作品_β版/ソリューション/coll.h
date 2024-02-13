
//-===============================================
//-
//-	当たり判定の処理のヘッダー[coll.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _COLL_H_		// このマクロが定義されなかったら
#define _COLL_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object.h"

#include "mgr_coll.h"

//-======================================
//-	マクロ定義
//-======================================

#define COLLSION_NUM_MAX		(1024)	// 当たり判定の最大数

//-======================================
//-	前方宣言
//-======================================

class CBoxField;
class CBoxWall;

//-======================================
//-	クラス定義
//-======================================

// 接触のクラス
class CColl
{

public:

	// 接触相手との情報
	typedef struct
	{
		int nNldx;		// 番号
		float fLength;	// 距離
	}HitData;

	// 見た目情報
	struct DataVisual
	{
		CBoxField* pField;
		CBoxWall* pWall;
	};

	// 当たり判定情報
	typedef struct
	{
		CMgrColl::TAG tag;						// タグ
		int nNldx;								// 番号
		CObject* pObj;							// オブジェクトのポインタ

		HitData hitData[COLLSION_NUM_MAX];		// 接触相手の接触情報
		int nHitNldxMax;						// 接触相手の番号の最大数

		HitData hitDataTemp[COLLSION_NUM_MAX];	// 一時的の接触相手の接触情報
		int nHitNldxMaxTemp;					// 一時的の接触相手の番号の最大数

		D3DXVECTOR3 pos;						// 位置
		D3DXVECTOR3 posOld;						// 前回の位置
		D3DXVECTOR3 size;						// 大きさ
		D3DXVECTOR2 collVec;					// 接触方向ベクトル

		DataVisual dataVisual;					// 見た目情報
	}Data;

	CColl();
	~CColl();

	HRESULT Init(CMgrColl::TAG tag, CObject* pObj, D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);

	void Update(void);
	void Draw(void);

	static CColl* Create(CMgrColl::TAG tag, CObject* pObj, D3DXVECTOR3 pos, D3DXVECTOR3 size);

	bool Hit(CMgrColl::TAG hitTag, CMgrColl::EVENT_TYPE eventType);
	bool HitSide(CMgrColl::TAG hitTag, CMgrColl::EVENT_TYPE eventType, CMgrColl::TYPE_SXIS typeSxis);

	void SetHitData(HitData data);
	void ResetHitData(void);

	void SetIsVisualDrawStop(bool bDrawStop);

	void UpdateData(D3DXVECTOR3 pos, D3DXVECTOR3 size) { m_data.pos = pos, m_data.size = size, SetDataVisual(pos, size); }
	void UpdateData(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 size) { m_data.pos = pos, m_data.posOld = posOld, m_data.size = size, SetDataVisual(pos, size); }

	void SetData(Data data) { m_data = data; }
	Data GetData(void) { return m_data; }

	void ResetHitDataTemp(void)
	{
		ZeroMemory(&m_data.hitDataTemp[0], sizeof(m_data.hitDataTemp));
		m_data.nHitNldxMaxTemp = 0;
	}

private:

	void SetDataVisual(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	void InitSet(CMgrColl::TAG tag, CObject* pObj, D3DXVECTOR3 pos, D3DXVECTOR3 size);

	Data m_data;
};

#endif	// 二重インクルード防止の終了
