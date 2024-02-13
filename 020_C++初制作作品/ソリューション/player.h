
//-===============================================
//-
//-	プレイヤー処理のヘッダー[player.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _PLAYER_H_		// このマクロが定義されなかったら
#define _PLAYER_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object.h"

#include "data.h"

#include "object_model.h"
#include "motion.h"

//=======================================
//=	マクロ定義
//=======================================

//-======================================
//-	前方宣言
//-======================================

class CObjectX;
class CObject3d;

//-======================================
//-	クラス定義
//-======================================

class CPlayer : public CObject
{

public:

	CPlayer();
	~CPlayer();

	HRESULT Init(CObjectModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax);

	void Uninit(void);
	void Update(void);
	void Draw(void);

	virtual void Hit(int nDamage);

	void CollisionObject(void);
	void CollisionMove(CObjectX *pObjX);
	void CollisionMove(CObject3d * pObj3d);

	void DebugPlayer(void);

	CMotion *GetMotion(void);

	CDataD3DXVECTOR3 m_dataPos;			// 位置
	CDataD3DXVECTOR3 m_dataPosOld;		// 前回の位置

	CDataD3DXVECTOR3 m_dataRot;			// 向き
	CDataD3DXVECTOR3 m_dataRotDest;		// 目的の向き

	CDataD3DXVECTOR3 m_dataSize;		// 大きさ

	CDataD3DXVECTOR3 m_dataMove;		// 移動量
	CDataD3DXVECTOR3 m_dataMoveHold;	// 保持した移動量

	CDataBool m_bDataStopMove;			// 移動を停止
	CDataBool m_bDataStopMoveRot;		// 向き移動の停止

	CObjectModel *GetObjectModel(int nNumParts);

private:

	void UpdatePos(void);
	void UpdateRot(void);
	void InputMove(void);

	D3DXMATRIX m_mtxWorld;			// ワールドマトリックス

	CObjectModel *m_apObjectModel[MODEL_PARTS_MAX];	// モデル（パーツ）のポインタ
	int m_nNumModel;								// モデル（パーツ）の総数

	CMotion *m_pMotion;				// モーションのポインタ
};

#endif	// 二重インクルード防止の終了
