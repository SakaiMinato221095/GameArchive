
//================================================
//=
//= 階層構造の階層構造のXファイルオブジェクト処理[object_model.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "object_model.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

//=======================================
//=	コンスト定義
//=======================================

// モデルテキストのコンスト定義
const char *pModelText[] =
{
	"data\\TXT\\Model\\Murabito.txt",		// 村人の階層構造モデルファイル
	"data\\TXT\\Model\\Cloud.txt",			// クラウドの階層構造モデルファイル
	"data\\TXT\\Model\\Sample.txt",			// サンプルの階層構造モデルファイル
};

//=======================================
//=	静的変数宣言
//=======================================

CObjectModel::Model CObjectModel::m_model[MODEL_NUM_MAX] = {};

//-------------------------------------
//-	階層構造のXファイルオブジェクトのコンストラクタ
//-------------------------------------
CObjectModel::CObjectModel()
{
	// 値をクリア
	m_pTexture = NULL;
	m_nldxTexture = NULL;

	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_dwNumMat = 0;

	ZeroMemory(m_mtxWorld, sizeof(D3DXMATRIX));
}

//-------------------------------------
//-	階層構造のXファイルオブジェクトのデストラクタ
//-------------------------------------
CObjectModel::~CObjectModel()
{
}

//-------------------------------------
//-	階層構造のXファイルオブジェクトの初期化処理
//-------------------------------------
HRESULT CObjectModel::Init(MODEL_TYPE modelType , int nCount)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// デバイスの情報取得の成功を判定
	if (pDevice == NULL)
	{// 失敗時

		// 初期化処理を抜ける
		return E_FAIL;
	}

	// Xファイルの読み込み
	D3DXLoadMeshFromX(
		m_model[modelType].modelParts[nCount].aFileName,		// Xファイルオブジェクト名
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,									// マテリアルの情報
		NULL,
		&m_dwNumMat,									// マテリアルの数
		&m_pMesh);										// メッシュの情報

	// Xファイルの読み込み成功の有無を確認
	if (m_pBuffMat == NULL)
	{
		// 失敗時に初期化処理を抜ける
		return E_FAIL;
	}

	// テクスチャの使用の有無を確認
	if (m_pTexture == NULL)
	{
		// マテリアル数分動的確保
		m_pTexture = new LPDIRECT3DTEXTURE9[m_dwNumMat];
		m_nldxTexture = new int[m_dwNumMat];

		// テクスチャ情報を初期化
		ZeroMemory(m_pTexture, sizeof(m_pTexture));
		ZeroMemory(m_nldxTexture, sizeof(m_nldxTexture));
	}
	else
	{
		// 初期化処理を抜ける
		return E_FAIL;
	}

	// マテリアルの情報を取得
	D3DXMATERIAL *pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// マテリアルの情報取得の成功を判定
	if (pDevice == NULL)
	{// 失敗

	 // 初期化を抜ける
		return E_FAIL;

	}

	// マテリアルごとの読み込み
	for (int nCutMat = 0; nCutMat < (int)m_dwNumMat; nCutMat++)
	{
		// テクスチャ設定の有無を判定
		if (pMat[nCutMat].pTextureFilename != NULL)
		{// テクスチャ設定が存在する

			// テクスチャの読み込み if(テクスチャ読み込み成功の有無を判定)
			if (FAILED(D3DXCreateTextureFromFile(
				pDevice,
				pMat[nCutMat].pTextureFilename,
				&m_pTexture[nCutMat])))
			{
				// 失敗を返す
				return E_FAIL;
			}

			// テクスチャ管理の生成
			CManagerTexture *pManagerTexture = CManager::GetManagerTexture();

			// テクスチャ管理の有無を判定
			if (pManagerTexture != NULL)
			{
				// テクスチャ設定
				m_nldxTexture[nCutMat] = pManagerTexture->Regist(pMat[nCutMat].pTextureFilename);
			}

		}
		else
		{
			// 「なし」を代入
			m_pTexture[nCutMat] = NULL;
		}
	}

	// 情報を設定
	m_dataPos.Set(m_model[modelType].modelParts[nCount].pos);	// 位置
	m_dataRot.Set(m_model[modelType].modelParts[nCount].rot);	// 向き

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//-	階層構造のXファイルオブジェクトの終了処理
//-------------------------------------
void CObjectModel::Uninit(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		// 動的確保分
		for (int nCutMat = 0; nCutMat < (int)m_dwNumMat; nCutMat++)
		{
			// テクスチャの有無を判定
			if (m_pTexture[nCutMat] != NULL)
			{
				// テクスチャの開放処理
				m_pTexture[nCutMat]->Release();
				m_pTexture[nCutMat] = NULL;
			}
		}

		// テクスチャの開放
		delete[] m_pTexture;
		m_pTexture = NULL;

		// テクスチャ番号の開放
		delete[] m_nldxTexture;
		m_nldxTexture = NULL;
	}

	// メッシュの破棄
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	// マテリアルの破棄
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}

//-------------------------------------
//-	階層構造のXファイルオブジェクトの更新処理
//-------------------------------------
void CObjectModel::Update(void)
{

}

//-------------------------------------
//-	階層構造のXファイルオブジェクトの描画処理
//-------------------------------------
void CObjectModel::Draw(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get() + m_dataMotionPos.Get();	// 位置情報
	D3DXVECTOR3 rot = m_dataRot.Get() + m_dataMotionRot.Get();	// 向き情報

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// デバイスの情報取得の成功を判定
	if (pDevice == NULL)
	{// 失敗時

	 // 初期化処理を抜ける
		return;
	}

	// 変数宣言
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス
	D3DMATERIAL9 matDef;			// 現在のマテリアルの保存用
	D3DXMATERIAL *pMat;				// マテリアルへのポインタ

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//親の計算用マトリックス
	D3DXMATRIX mtxParent;

	//パーツの「親マトリックス」を設定
	if (m_pParent != NULL)
	{//親モデルがある場合

		// 親のマトリックスを代入
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{//親モデルがない場合

		//プレイヤーのマトリックスを設定
		pDevice->GetTransform(D3DTS_WORLD,&mtxParent);
	}

	//算出したパーツのマトリックスと親のマトリックスを掛け合わせる
	D3DXMatrixMultiply(
		&m_mtxWorld,
		&m_mtxWorld,
		&mtxParent);

	// ワールドマトリックスの設定
	pDevice->SetTransform(
		D3DTS_WORLD,
		&m_mtxWorld);

	// 現在のマテリアルの取得
	pDevice->GetMaterial(&matDef);

	// マテリアルのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// マテリアルごとの描画
	for (int nCutMat = 0; nCutMat < (int)m_dwNumMat; nCutMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCutMat].MatD3D);

		// テクスチャの設定（仮）
		pDevice->SetTexture(0, m_pTexture[nCutMat]);

		// 階層構造のXファイルオブジェクト（パーツ）の描画
		m_pMesh->DrawSubset(nCutMat);
	}

	// 保存していたマテリアルに戻す
	pDevice->SetMaterial(&matDef);

}

//-------------------------------------
//-	階層構造のXファイルオブジェクトの生成処理
//-------------------------------------
CObjectModel *CObjectModel::Create(MODEL_TYPE modelType, int nCount)
{
	// 階層構造のXファイルオブジェクトのポインタを宣言
	CObjectModel *pObjectX = NULL;

	// 生成
	pObjectX = new CObjectModel;

	// 生成の成功の有無を判定
	if (pObjectX != NULL)
	{
		// 初期化処理
		if (FAILED(pObjectX->Init(modelType,nCount)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pObjectX == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// 階層構造のXファイルオブジェクトのポインタを返す
	return pObjectX;
}

//-------------------------------------
//-	階層構造のXファイルオブジェクトの親子関係設定処理
//-------------------------------------
void CObjectModel::SetParent(CObjectModel **pObjectModel, MODEL_TYPE modelType,int nCount)
{
	// 親の番号を取得
	int nParent = m_model[modelType].modelParts[nCount].nParent;

	if (nParent != -1)
	{
		// 親のモデル情報を代入
		m_pParent = pObjectModel[nParent];
	}
	else
	{
		m_pParent = NULL;
	}
}

//-------------------------------------
//-	階層構造のXファイルオブジェクトのワールドマトリックス取得処理
//-------------------------------------
D3DXMATRIX CObjectModel::GetMtxWorld(void)
{
	// ワールドマトリックスを返す
	return m_mtxWorld;
}

//-------------------------------------
//- 階層構造のXファイルオブジェクトのモデル設定処理
//-------------------------------------
void CObjectModel::SetFile(MODEL_TYPE modelType)
{
	//変数宣言
	FILE *pFile;	// ファイルのポインタ

	// ファイルの情報を代入
	pFile = fopen(pModelText[modelType], "r");

	// ファイルの有無を判定
	if (pFile != NULL)
	{// ファイルが開けるとき

		// 変数宣言
		char aFileData[256] = {};		// ファイルの文章を格納

		int nFileNameCount = -1;		// ファイルの名前のカウント 
		int nIndex = -1;				// パーツ数を格納

		while (true)
		{
			// 文字列を読み込み
			fgets(aFileData, 256, pFile);

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

			// モデルのパーツ数を設定
			if (strstr(aFileData, "NUM_MODEL") != NULL)
			{
				// 変数宣言
				char aTenp[2][256] = {};	// ゴミ入れ	
				int nPartsNum = 0;			// パーツ数

				// パーツ数を取り出す
				sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nPartsNum);

				// パーツ数を代入
				m_model[modelType].nPartsNum = nPartsNum;
			}

			// パーツのファイル名を設定
			if (strstr(aFileData, "MODEL_FILENAME") != NULL)
			{
				// 変数宣言
				char aTenp[2][256] = {};	// ゴミ入れ	
				char aFileName[256] = {};	// ファイルの名前を格納

				// パーツカウントを進める
				nFileNameCount++;

				// ファイルの名前を取り出す
				sscanf(aFileData, "%s %s %s", aTenp[0], aTenp[1], aFileName);

				// ファイルの名前を代入
				strcpy(m_model[modelType].modelParts[nFileNameCount].aFileName, aFileName);
			}

			// パーツ番号の設定
			if (strstr(aFileData, "INDEX") != NULL)
			{
				// 変数宣言
				char aTenp[2][256] = {};	// ゴミ入れ	

				// パーツの番号を取り出す
				sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nIndex);

				// パーツの番号を代入
				m_model[modelType].modelParts[nIndex].nIndex = nIndex;
			}

			// 親の設定
			if (strstr(aFileData, "PARENT") != NULL)
			{
				// 変数宣言
				char aTenp[2][256] = {};	// ゴミ入れ	
				int nParent = -1;

				// 親の番号を取り出す
				sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nParent);

				// 親の番号を代入
				m_model[modelType].modelParts[nIndex].nParent = nParent;
			}

			// 位置情報の設定
			if (strstr(aFileData, "POS") != NULL)
			{
				// 変数宣言
				char aTenp[2][256] = {};	// ゴミ入れ	
				float fPosX = 0;			// 位置（X）
				float fPosY = 0;			// 位置（Y）
				float fPosZ = 0;			// 位置（Z）

				// 位置を取り出す
				sscanf(aFileData, "%s %s %f %f %f", aTenp[0], aTenp[1], &fPosX, &fPosY, &fPosZ);

				// 位置を代入
				m_model[modelType].modelParts[nIndex].pos = D3DXVECTOR3(fPosX, fPosY, fPosZ);
			}

			// 向き情報の設定
			if (strstr(aFileData, "ROT") != NULL)
			{
				// 変数宣言
				char aTenp[2][256] = {};	// ゴミ入れ	
				float fRotX = 0;			// 向き（X）
				float fRotY = 0;			// 向き（Y）
				float fRotZ = 0;			// 向き（Z）

				// 向きを取り出す
				sscanf(aFileData, "%s %s %f %f %f", aTenp[0], aTenp[1], &fRotX, &fRotY, &fRotZ);

				// 向きを代入
				m_model[modelType].modelParts[nIndex].rot = D3DXVECTOR3(fRotX, fRotY, fRotZ);
			}

			// 終了
			if (strstr(aFileData, "END_CHARACTERSET") != NULL)
			{
				break;
			}
		}

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{

	}
}

//-------------------------------------
//- 階層構造のXファイルオブジェクトのモデル設定処理
//-------------------------------------
int CObjectModel::GetPartsNum(MODEL_TYPE modelType)
{
	// パーツ数を返す
	return m_model[modelType].nPartsNum;
}