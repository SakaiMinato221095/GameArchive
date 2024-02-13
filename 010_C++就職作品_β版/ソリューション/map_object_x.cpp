
//-===============================================
//-
//-	オブジェクトファイル処理[map_object_x.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "map_object_x.h"

#include "objectx_none.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//= コンスト定義
//=======================================

// 通常敵のテキストのコンスト定義
const char* pTxtObjectX[] =
{
	"data\\TXT\\Object\\ObjectNone_000.txt"		// オブジェクト_000のテキスト
};

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CMapObjectX::CMapObjectX()
{
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CMapObjectX::~CMapObjectX()
{

}

//-------------------------------------
//- オブジェクトファイルの書き出し処理
//-------------------------------------
void CMapObjectX::Save(CMapObjectX::TXT txtType)
{

}

//-------------------------------------
//- オブジェクトファイルの読み込み処理
//-------------------------------------
void CMapObjectX::Load(CMapObjectX::TXT txtType)
{
	//変数宣言
	FILE* pFile;	// ファイルのポインタ

	// ファイルの情報を代入
	pFile = fopen(pTxtObjectX[txtType], "r");

	// ファイルの有無を判定
	if (pFile != NULL)
	{
		// 変数宣言
		char aFileData[256] = { 0 };				// ファイルの文章を格納
		CObjectXNone* pObjectNone = nullptr;		// オブジェクトのポインタ

		while (true)
		{
			// 文字列を読み込み
			fgets(aFileData, 256, pFile);

			// 文字数分読み込み
			for (int nCount = 0; nCount < 256; nCount++)
			{
				// コメントを判定
				if (aFileData[nCount] == '#')
				{
					// コメントを除去
					memset(&aFileData[nCount], NULL, sizeof(256 - nCount));
					break;
				}
			}

			if (strstr(aFileData, "MODEL") != NULL)
			{
				if (strstr(aFileData, "=") != NULL)
				{
					// 敵の生成処理
					pObjectNone = CObjectXNone::Create((CObjectXNone::MODEL)0, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					// 変数宣言
					char aTenp[2][256] = {};	// ゴミ入れ	
					int nValue = 0;				// 数値

					// 数値を取り出す
					sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nValue);

					// モデル番号の取得
					int nModelNldx = CObjectXNone::GetModelData(nValue).nModelNldx;

					// モデル割当
					pObjectNone->BindModel(nModelNldx, nValue);
				}
			}

			if (strstr(aFileData, "POS") != NULL)
			{
				// 特定の文字を判定
				if (strstr(aFileData, "=") != NULL)
				{
					// 変数宣言
					char aTenp[3][256] = {};	// ゴミ入れ	
					float fPosX = 0.0f;			// 位置（X）
					float fPosY = 0.0f;			// 位置（Y）
					float fPosZ = 0.0f;			// 位置（Z）

					// 数値を取り出す
					sscanf(aFileData, "%s %s %s %f %f %f", aTenp[0], aTenp[1], aTenp[2], &fPosX, &fPosY, &fPosZ);

					// 位置設定
					CObjectX::VtxData vtxData = pObjectNone->GetVtxData();
					vtxData.pos = D3DXVECTOR3(fPosX, fPosY, fPosZ);
					pObjectNone->SetVtxData(vtxData);
				}
			}

			// 向き情報の判定
			if (strstr(aFileData, "ROT") != NULL)
			{
				// 特定の文字を判定
				if (strstr(aFileData, "=") != NULL)
				{
					// 変数宣言
					char aTenp[3][256] = {};	// ゴミ入れ	
					float fRotX = 0.0f;			// 向き（X）
					float fRotY = 0.0f;			// 向き（Y）
					float fRotZ = 0.0f;			// 向き（Z）

					// 数値を取り出す
					sscanf(aFileData, "%s %s %s %f %f %f", aTenp[0], aTenp[1], aTenp[2], &fRotX, &fRotY, &fRotZ);

					// 位置設定
					CObjectX::VtxData vtxData = pObjectNone->GetVtxData();
					vtxData.rot = D3DXVECTOR3(fRotX, fRotY, fRotZ);
					pObjectNone->SetVtxData(vtxData);
				}
			}

			// モデル設定の終了
			if (strstr(aFileData, "END_MODEL_SET") != NULL)
			{
				// オブジェクトのポインタをなくす
				pObjectNone = NULL;
			}

			// 読み込み終了
			if (strstr(aFileData, "SET_END") != NULL)
			{
				break;
			}
		}

		// ファイルを閉じる
		fclose(pFile);
	}
}