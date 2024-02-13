
//-===============================================
//-
//-	キャラクター処理のヘッダー[character.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _CHARACTER_H_		// このマクロが定義されなかったら
#define _CHARACTER_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object.h"

#include "model.h"
#include "motion.h"

//=======================================
//=	マクロ定義
//=======================================

//-======================================
//-	前方宣言
//-======================================

//-======================================
//-	クラス定義
//-======================================

class CCharacter : public CObject
{

public:

	struct Data
	{
		D3DXVECTOR3 pos;		// 位置

		D3DXVECTOR3 rot;		// 向き
	};

	CCharacter();
	~CCharacter();

	HRESULT Init(CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nMotionStateMax);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CCharacter* Create(CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nMotionStateMax);

	void UpdateData(D3DXVECTOR3 pos, D3DXVECTOR3 rot) {

		m_data.pos = pos; 
		m_data.rot = rot;

		for (int nCnt = 0; nCnt < MODEL_PARTS_MAX; nCnt++)
		{
			if (m_apModel[nCnt] != nullptr)
			{
				m_apModel[nCnt]->SetMatrix();
			}
		};
	}

	CMotion* GetMotion(void) { return m_pMotion; }
	CModel* GetModel(int nNumParts) { return m_apModel[nNumParts]; }

	void SetColorAll(D3DXCOLOR color) {
		for (int nCnt = 0; nCnt < MODEL_PARTS_MAX; nCnt++)
		{
			if (m_apModel[nCnt] != nullptr)
			{
				m_apModel[nCnt]->SetColor(color);
			}
		};}

private:

	void SetMatrix(void);

	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス

	CModel* m_apModel[MODEL_PARTS_MAX];		// モデル（パーツ）のポインタ
	int m_nNumModel;						// モデル（パーツ）の総数

	CMotion* m_pMotion;						// モーションのポインタ

	Data m_data;							// 情報
};

#endif	// 二重インクルード防止の終了
