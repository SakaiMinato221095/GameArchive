
//-===============================================
//-
//-	出現壁の処理のヘッダー[spwan_wall.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _SPWAN_WALL_H_		// このマクロが定義されなかったら
#define _SPWAN_WALL_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object.h"

#include "phase_manager.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	コンスト定義
//=======================================

//=======================================
//=	前方宣言
//=======================================

class CColl;
class CObj3dWall;

//-======================================
//-	クラス定義
//-======================================

class CSpwanWall : public CObject
{

public:

	// フィールドのテクスチャの列挙型
	typedef enum
	{
		TEX_NULL = 0,		// なし
		TEX_SPWAN_000,		// 出現壁のテクスチャ
		TEX_BLOCK_000,		// 封鎖壁のテクスチャ
		TEX_MAX
	}TEX;

	CSpwanWall(int nPriority);
	~CSpwanWall();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	virtual void Hit(void);

	void InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR color, D3DXVECTOR2 texPos);

	static CSpwanWall* Create(void);

	void SetPos(D3DXVECTOR3 pos) { m_info.pos = pos; }
	D3DXVECTOR3 GetPos(void) { return m_info.pos; }

	void SetRot(D3DXVECTOR3 rot) { m_info.rot = rot; }
	D3DXVECTOR3 GetRot(void) { return m_info.rot; }

	void SetSize(D3DXVECTOR3 size) { m_info.size = size; }
	D3DXVECTOR3 GetSize(void) { return m_info.size; }

	void SetColor(D3DXCOLOR color) { m_info.color = color; }
	D3DXCOLOR GetColor(void) { return m_info.color; }

	void SetTexPos(D3DXVECTOR2 texPos) { m_info.texPos = texPos; }
	D3DXVECTOR2 GetTexPos(void) { return m_info.texPos; }

	void SetTypePhase(CPhaseManager::TYPE_PHASE typePhase) { m_info.typePhase = typePhase; }
	CPhaseManager::TYPE_PHASE SetTypePhase(void) { return m_info.typePhase; }

private:

	void UpdateType(void);
	void SetPhase(void);
	void SpwanEnemyPhaseOne(void);
	void SpwanEnemyPhaseTwo(void);
	void SpwanEnemyPhaseThree(void);

	struct Info
	{
		D3DXVECTOR3 pos;	// 位置
		D3DXVECTOR3 rot;	// 向き
		D3DXVECTOR3 size;	// 大きさ
		D3DXCOLOR color;	// 色
		D3DXVECTOR2 texPos;	// テクスチャ位置

		int nNumTarget;							// ターゲットの数
		CPhaseManager::TYPE_PHASE typePhase;	// フェーズ番号
	};

	struct InfoVisual
	{
		CObj3dWall* pObj3dWall;	// 壁
	};

	struct InfoAttach
	{
		CColl* pColl;			// 当たり判定
	};

	Info m_info;
	InfoVisual m_infoVisual;
	InfoAttach m_infoAttach;

	static int m_nTextureNldx[TEX_MAX];		// テクスチャの番号
};

#endif	// 二重インクルード防止の終了
