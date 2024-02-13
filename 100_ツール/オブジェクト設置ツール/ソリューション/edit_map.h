
//-===============================================
//-
//-	マップエディタ処理のヘッダー[edit_map.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _EDIT_MAP_H_		// このマクロが定義されなかったら
#define _EDIT_MAP_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object_x.h"

#include "data.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	クラス定義
//-======================================

// アイテムのクラス
class CEditMap
{

public:

	typedef enum
	{
		TYPE_OBJECTX_NONE = 0,	// 効果なしオブジェクト
		TYPE_EVENT_OBJECT,		// イベントオブジェクト
		TYPE_GARBAGE,			// ゴミ
		TYPE_GARBAGE_COLLECT,	// ゴミ回収
		TYPE_ITEM,				// アイテム
		TYPE_ENEMY_NORMAL,		// 通常敵
		TYPE_ENEMY_PIN,			// エネミーピン
		TYPE_MAX
	}TYPE;

	CEditMap();
	~CEditMap();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	bool Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEditMap * Create(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);

	CDataD3DXVECTOR3 m_dataPos;
	CDataD3DXVECTOR3 m_dataMove;
	CDataD3DXVECTOR3 m_dataRot;

private:

	void Move(void);
	void Rot(void);
	void SetObjectData(void);
	void ChangeModel(void);
	void ChangeType(void);
	void SetObject(void);

	void SetModel(void);

	void SaveFile(void);
	void DrawDebug(void);

	CObjectX *m_pObject;		// Xファイルオブジェクトのポインタ
	int m_nModelNum;			// モデル番号
	int m_nModelMax;			// モデルの最大数

	TYPE m_typeSelect;			// 選択種類
};

#endif	// 二重インクルード防止の終了
