
//-===============================================
//-
//-	効果なしオブジェクト情報ファイル処理[file_data_obj_none.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "file_data_obj_none.h"

#include "manager_object.h"

#include "objectx_none.h"
#include "event_object.h"

//-======================================
//-	マクロ定義
//-======================================

#define FILE_DATA_OBJ_NONE_TEX	("data\\TXT\\DataModel\\DataObjNone.txt")

#define ARRAY_SIZE	(256)		// 配列のサイズ

//=======================================
//= コンスト定義
//=======================================

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CFileDataObjNone::CFileDataObjNone()
{
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CFileDataObjNone::~CFileDataObjNone()
{

}

//-------------------------------------
//- 効果なしオブジェクト情報ファイルの書き出し処理
//-------------------------------------
void CFileDataObjNone::Save(int nNumber , D3DXVECTOR3 sizeCol)
{
	//変数宣言
	FILE *pFile;	// ファイルのポインタ

	// ファイルの情報を代入
	pFile = fopen(FILE_DATA_OBJ_NONE_TEX, "w");

	// ファイルの有無を判定
	if (pFile != NULL)
	{
		// 変数宣言（効果なしオブジェクトのモデル数）
		int nMaxNum = 0;

		// 見出しの書き出し
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "#=\n");
		fprintf(pFile, "#= [効果なしオブジェクト情報] \n");
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
		fprintf(pFile, "#= [モデル情報] \n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "\n");

		for (int nCount = 0; nCount < CObjectXNone::MODEL_MAX; nCount++)
		{
			// 敵の情報
			CObjectXNone::ModelData modelData;

			if (nCount == nNumber)
			{
				// 当たり判定オブジェクトのサイズを代入
				modelData.size = sizeCol;

				// データを上書き
				CObjectXNone::SetModelData(nCount, modelData);
			
			}
			else
			{
				// モデル情報を代入
				modelData = CObjectXNone::GetModelData(nCount);
			}

			// 変数宣言
			D3DXVECTOR3 size = modelData.size;	// サイズを格納

			// 配置モデルの情報の書き出し
			fprintf(pFile, "MODEL_NUMBER = %d\n", nCount);
			fprintf(pFile, " --- SIZE = %3.1f %3.1f %3.1f \n", size.x, size.y, size.z);
			fprintf(pFile, "END_MODEL_DATA_SET \n");
			fprintf(pFile, "\n");
		}

		// 書き出しの終了
		fprintf(pFile, "SET_END");

		// ファイルを閉じる
		fclose(pFile);
	}
}

//-------------------------------------
//- 効果なしオブジェクト情報ファイルの読み込み処理
//-------------------------------------
void CFileDataObjNone::Load(void)
{
	//変数宣言
	FILE *pFile;	// ファイルのポインタ

	// ファイルの情報を代入
	pFile = fopen(FILE_DATA_OBJ_NONE_TEX, "r");

	// ファイルの有無を判定
	if (pFile != NULL)
	{
		// 変数宣言
		char aFileData[ARRAY_SIZE] = { 0 };			// ファイルの文章を格納
		int nModelNumber = -1;					// モデル番号
		CObjectXNone::ModelData modelData = {};	// モデル情報

		while (true)
		{
			// 文字列を読み込み
			fgets(aFileData, 256, pFile);

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

			if (strstr(aFileData, "MODEL_NUMBER") != NULL)
			{
				if (strstr(aFileData, "=") != NULL)
				{
					for (int nCount = 0; nCount < OBJECTX_NONE_NUM_MAX; nCount++)
					{
						// 効果なしオブジェクトの有無を判定
						if (CManagerObject::GetObjectNone(nCount) == NULL)
						{
							// 変数宣言
							char aTenp[2][ARRAY_SIZE] = {};	// ゴミ入れ	
							int nValue = 0;				// 数値

							// 数値を取り出す
							sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nValue);

							// 取り出した数値（モデル番号）を代入
							nModelNumber = nValue;

							break;
						}
					}

				}
			}

			if (strstr(aFileData, "SIZE") != NULL)
			{
				// 特定の文字を判定
				if (strstr(aFileData, "=") != NULL)
				{
					// 変数宣言
					char aTenp[3][ARRAY_SIZE] = {};	// ゴミ入れ	
					float fSizeX = 0;			// 位置（X）
					float fSizeY = 0;			// 位置（Y）
					float fSizeZ = 0;			// 位置（Z）

					// 数値を取り出す
					sscanf(aFileData, "%s %s %s %f %f %f", aTenp[0], aTenp[1], aTenp[2], &fSizeX, &fSizeY, &fSizeZ);

					// サイズを代入
					modelData.size = D3DXVECTOR3(fSizeX, fSizeY, fSizeZ);
				}
			}

			// モデル設定の終了
			if (strstr(aFileData, "END_MODEL_DATA_SET") != NULL)
			{
				// サイズ情報を代入
				CObjectXNone::SetModelData(nModelNumber, modelData);

				// モデル番号を初期化
				nModelNumber = -1;
			}

			if (strstr(aFileData, "SET_END") != NULL)
			{
				break;
			}
		}

		// ファイルを閉じる
		fclose(pFile);
	}
}