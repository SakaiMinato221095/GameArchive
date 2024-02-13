
//-===============================================
//-
//-	ゴミファイル処理[file_garbage.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "file_garbage.h"

#include "manager_object.h"

#include "garbage.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//= コンスト定義
//=======================================

// 通常敵のテキストのコンスト定義
const char *pTxtGarbage[] =
{
	"data\\TXT\\Object\\Garbage_000.txt"		// ゴミ_000のテキスト
};

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CFileGarbage::CFileGarbage()
{
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CFileGarbage::~CFileGarbage()
{

}

//-------------------------------------
//- ゴミファイルの書き出し処理
//-------------------------------------
void CFileGarbage::Save(CFileGarbage::TXT txtType)
{
	//変数宣言
	FILE *pFile;	// ファイルのポインタ

	// ファイルの情報を代入
	pFile = fopen(pTxtGarbage[txtType], "w");

	// ファイルの有無を判定
	if (pFile != NULL)
	{
		// 変数宣言（敵のモデル数）
		int nMaxNum = 0;

		// 見出しの書き出し
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "#=\n");
		fprintf(pFile, "#= [ゴミ] \n");
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
			// 変数宣言（指定の敵のポインタ取得）
			CGarbage *pGarbage = CManagerObject::GetGarbage(nCount);

			// 敵の有無を判定
			if (pGarbage != NULL)
			{
				// 変数宣言（敵の情報取得）
				int nModelNldx = pGarbage->GetModel();			// 使用モデル番号
				D3DXVECTOR3 pos = pGarbage->m_dataPos.Get();	// 位置
				D3DXVECTOR3 rot = pGarbage->m_dataRot.Get();	// 向き

				// 配置モデルの情報の書き出し
				fprintf(pFile, "MODEL = %d\n", nModelNldx);
				fprintf(pFile, " --- POS = %3.1f %3.1f %3.1f \n", pos.x, pos.y, pos.z);
				fprintf(pFile, " --- ROT = %3.1f %3.1f %3.1f \n", rot.x, rot.y, rot.z);
				fprintf(pFile, "END_MODEL_SET \n");
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
//- ゴミファイルの読み込み処理
//-------------------------------------
void CFileGarbage::Load(CFileGarbage::TXT txtType)
{
	//変数宣言
	FILE *pFile;	// ファイルのポインタ

	// ファイルの情報を代入
	pFile = fopen(pTxtGarbage[txtType], "r");

	// ファイルの有無を判定
	if (pFile != NULL)
	{
		// 変数宣言
		char aFileData[256] = { 0 };			// ファイルの文章を格納
		CGarbage *pGarbage = NULL;		// 通常敵のポインタ

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
					for (int nCount = 0; nCount < ENEMY_NORMAL_NUM_MAX; nCount++)
					{
						// 敵の有無を判定
						if (CManagerObject::GetGarbage(nCount) == NULL)
						{
							// 敵の生成処理
							pGarbage = CGarbage::Create((CGarbage::MODEL)0);

							CManagerObject::SetGarbage(nCount, pGarbage);

							// 変数宣言
							char aTenp[2][256] = {};	// ゴミ入れ	
							int nValue = 0;				// 数値

							// 数値を取り出す
							sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nValue);

							// モデル番号の取得
							int nModelNldx = CGarbage::m_nDataModelNldx[nValue].Get();

							// モデル割当
							pGarbage->BindModel(nModelNldx, (CGarbage::MODEL)nValue);

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
					char aTenp[3][256] = {};	// ゴミ入れ	
					float fPosX = 0;			// 位置（X）
					float fPosY = 0;			// 位置（Y）
					float fPosZ = 0;			// 位置（Z）

												// 数値を取り出す
					sscanf(aFileData, "%s %s %s %f %f %f", aTenp[0], aTenp[1], aTenp[2], &fPosX, &fPosY, &fPosZ);

					// 位置情報を代入
					pGarbage->m_dataPos.Set(D3DXVECTOR3(
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
					char aTenp[3][256] = {};	// ゴミ入れ	
					float fRotX = 0;			// 向き（X）
					float fRotY = 0;			// 向き（Y）
					float fRotZ = 0;			// 向き（Z）

												// 数値を取り出す
					sscanf(aFileData, "%s %s %s %f %f %f", aTenp[0], aTenp[1], aTenp[2], &fRotX, &fRotY, &fRotZ);

					// 向きを代入
					pGarbage->m_dataRot.Set(D3DXVECTOR3(
						fRotX,
						fRotY,
						fRotZ));
				}
			}

			// モデル設定の終了
			if (strstr(aFileData, "END_MODEL_SET") != NULL)
			{
				// オブジェクトのポインタをなくす
				pGarbage = NULL;
			}

			// モデル設定の終了 （ 終わりの文を見つけた || 格納場所がない ） 
			if (strstr(aFileData, "SET_END") != NULL)
			{
				break;
			}
		}

		// ファイルを閉じる
		fclose(pFile);
	}
}