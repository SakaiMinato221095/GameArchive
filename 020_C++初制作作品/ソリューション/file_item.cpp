
//-===============================================
//-
//-	アイテムファイル処理[file_item.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "file_item.h"

#include "manager_object.h"

#include "item.h"

//-======================================
//-	マクロ定義
//-======================================

#define ARRAY_SIZE	(256)		// 配列のサイズ

//=======================================
//= コンスト定義
//=======================================

// アイテムテキストのコンスト定義
const char *pTxtItem[] =
{
	"data\\TXT\\Object\\Item_000.txt"		// アイテム_000のテキスト
};

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CFileItem::CFileItem()
{
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CFileItem::~CFileItem()
{

}

//-------------------------------------
//- アイテムファイルの書き出し処理
//-------------------------------------
void CFileItem::Save(CFileItem::TXT txtType)
{
	//変数宣言
	FILE *pFile;	// ファイルのポインタ

	// ファイルの情報を代入
	pFile = fopen(pTxtItem[txtType], "w");

	// ファイルの有無を判定
	if (pFile != NULL)
	{
		// 変数宣言（アイテムのモデル数）
		int nMaxNum = 0;

		// 見出しの書き出し
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "#=\n");
		fprintf(pFile, "#= [アイテム] \n");
		fprintf(pFile, "#=\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "\n");

		// モデル数の書き出し
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "#= [モデル数] \n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "%d\n", nMaxNum);
		fprintf(pFile, "\n");

		// 配置状況見出しの書き出し
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "#= [配置情報] \n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "\n");

		for (int nCount = 0; nCount < OBJECTX_NONE_NUM_MAX; nCount++)
		{
			// 変数宣言（指定のアイテムのポインタ取得）
			CItem *pItem = CManagerObject::GetItem(nCount);

			// アイテムの有無を判定
			if (pItem != NULL)
			{
				// 変数宣言（アイテムの情報取得）
				int nModelNldx = pItem->GetModel();			// 使用モデル番号
				D3DXVECTOR3 pos = pItem->m_dataPos.Get();	// 位置
				D3DXVECTOR3 rot = pItem->m_dataRot.Get();	// 向き

				// 配置モデルの情報の書き出し
				fprintf(pFile, "MODEL = %d\n", nModelNldx);								// モデル番号
				fprintf(pFile, " --- POS = %3.1f %3.1f %3.1f \n", pos.x, pos.y, pos.z);	// 位置
				fprintf(pFile, " --- ROT = %3.1f %3.1f %3.1f \n", rot.x, rot.y, rot.z);	// 向き
				fprintf(pFile, "END_MODEL_SET \n");										// 終了コメント
				fprintf(pFile, "\n");
			}
		}

		// 書き出しの終了
		fprintf(pFile, "SET_END");

		// ファイルを閉じる
		fclose(pFile);
	}
}

//-------------------------------------
//- アイテムファイルの読み込み処理
//-------------------------------------
void CFileItem::Load(CFileItem::TXT txtType)
{
	//変数宣言
	FILE *pFile;	// ファイルのポインタ

	// ファイルの情報を代入
	pFile = fopen(pTxtItem[txtType], "r");

	// ファイルの有無を判定
	if (pFile != NULL)
	{
		// 変数宣言
		char aFileData[ARRAY_SIZE] = { 0 };		// ファイルの文章を格納
		CItem *pItem = NULL;	// アイテムのポインタ

		while (true)
		{
			// 文字列を読み込み
			fgets(aFileData, ARRAY_SIZE, pFile);

			// 文字数分読み込み
			for (int nCount = 0; nCount < ARRAY_SIZE; nCount++)
			{
				// コメントを判定
				if (aFileData[nCount] == '#')
				{
					// コメントを除去
					memset(&aFileData[nCount], NULL, sizeof(ARRAY_SIZE - nCount));
					break;
				}
			}

			if (strstr(aFileData, "MODEL") != NULL)
			{
				if (strstr(aFileData, "=") != NULL)
				{
					for (int nCount = 0; nCount < EVENT_OBJECT_NUM_MAX; nCount++)
					{
						// アイテムの有無を判定
						if (CManagerObject::GetItem(nCount) == NULL)
						{
							// 変数宣言
							char aTenp[2][ARRAY_SIZE] = {};	// ゴミ入れ	
							int nValue = 0;				// 数値

							// 値（モデル番号）を取り出す
							sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nValue);

							// アイテムの生成処理
							pItem = CItem::Create((CItem::MODEL)nValue);

							// アイテムのポインタを代入
							CManagerObject::SetItem(nCount, pItem);

							// モデル番号の取得
							int nModelNldx = CItem::m_nDataModelNldx[nValue].Get();

							// モデル割当
							pItem->BindModel(nModelNldx, (CItem::MODEL)nValue);

							break;
						}
					}
				}
			}

			if (strstr(aFileData, "POS") != NULL)
			{
				// 特定の文字を判定
				if (strstr(aFileData, "=") != NULL)
				{
					// 変数宣言
					char aTenp[3][ARRAY_SIZE] = {};	// ゴミ入れ	
					float fPosX = 0;			// 位置（X）
					float fPosY = 0;			// 位置（Y）
					float fPosZ = 0;			// 位置（Z）

					// 値（位置）を取り出す
					sscanf(aFileData, "%s %s %s %f %f %f", aTenp[0], aTenp[1], aTenp[2], &fPosX, &fPosY, &fPosZ);

					// 位置情報を代入
					pItem->m_dataPos.Set(D3DXVECTOR3(
						fPosX,
						fPosY,
						fPosZ));
				}
			}

			// 向き情報の判定
			if (strstr(aFileData, "ROT") != NULL)
			{
				// 特定の文字を判定
				if (strstr(aFileData, "=") != NULL)
				{
					// 変数宣言
					char aTenp[3][ARRAY_SIZE] = {};	// ゴミ入れ	
					float fRotX = 0;			// 向き（X）
					float fRotY = 0;			// 向き（Y）
					float fRotZ = 0;			// 向き（Z）

					// 値（向き）を取り出す
					sscanf(aFileData, "%s %s %s %f %f %f", aTenp[0], aTenp[1], aTenp[2], &fRotX, &fRotY, &fRotZ);

					// 向きを代入
					pItem->m_dataRot.Set(D3DXVECTOR3(
						fRotX,
						fRotY,
						fRotZ));
				}
			}

			// モデル設定の終了
			if (strstr(aFileData, "END_MODEL_SET") != NULL)
			{
				// オブジェクトのポインタをなくす
				pItem = NULL;
			}

			// モデル設定の終了
			if (strstr(aFileData, "SET_END") != NULL)
			{
				break;
			}
		}

		// ファイルを閉じる
		fclose(pFile);
	}
}