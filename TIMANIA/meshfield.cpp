//=============================================================================
//
// メッシュ地面の処理 [meshfield.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
//#include "input.h"
#include "texture.h"
#include "meshfield.h"
#include "renderer.h"
#include "player.h"
#include "inputx.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// 頂点バッファ
static ID3D11Buffer					*g_IndexBuffer = NULL;	// インデックスバッファ

static FIELD	g_Field;	// フィールド情報
static int		g_TexNo;	// テクスチャ番号

static int		g_VertexNum = 0;//頂点数
static int		g_IndexNum = 0;	//インデックス数

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitMeshField(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int numBlockX, int numBlockZ, float sizeX, float sizeZ)
{
	// 位置・回転・スケールの初期設定
	g_Field.pos = pos;
	g_Field.rot = rot;
	g_Field.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// テクスチャ生成
	g_TexNo = LoadTexture((char*)"data/TEXTURE/Square1.png");


	int yoko = numBlockX;
	int tate = numBlockZ;

	//必要な頂点数とインデックス数を計算する
	g_VertexNum = (numBlockX + 1) * (numBlockZ + 1);
	g_IndexNum = (((yoko * 2 + 2) * (tate)) + ((tate - 1) * 2));

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * g_VertexNum;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);


	// インデックスバッファ生成
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(unsigned short) * g_IndexNum;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_IndexBuffer);


	{//頂点バッファの中身を埋める　　横一直線に頂点を作っていく

		// 頂点バッファへのポインタを取得
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

		//縦のループ
		for (int y = 0; y < (tate + 1); y++)
		{
			//横のループ
			for (int x = 0; x < (yoko + 1); x++)
			{
				//配列のインデックスを計算する
				int i = y * (yoko + 1) + x;

				// 頂点座標の設定
				pVtx[i].Position = D3DXVECTOR3(x * sizeX, 0.0f, y * sizeZ);

				// UV値の設定
				pVtx[i].TexCoord = D3DXVECTOR2(x * 1.0f, y * 1.0f);
				// 法線の設定
				pVtx[i].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				// 頂点カラーの設定
				pVtx[i].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}
		GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	}

	{//インデックスバッファの中身を埋める  図的に下上下上の順で頂点を考える

		// インデックスバッファのポインタを取得
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(g_IndexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
		unsigned short *pIdx = (unsigned short*)msr.pData;

		int idx = 0;

		for (int y = 0; y < tate; y++)
		{
			for (int x = 0; x < (yoko + 1); x++)
			{
				pIdx[idx] = y *(yoko + 1) + x;//上
				idx++;
				pIdx[idx] = (y+1)*(yoko + 1) + x;//下	
				idx++;
			}

			//縮退ポリゴン分のインデックス　ポリゴン偶数時　終わりとはじめを1つずつ重複させる
			if (y < (tate - 1))
			{
				pIdx[idx] = (y + 2) * (yoko + 1);
				idx++;
				pIdx[idx] = y * (yoko + 1) + yoko;
				idx++;
			}
		}

 		GetDeviceContext()->Unmap(g_IndexBuffer, 0);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMeshField(void)
{
	//インデックスバッファの解放
	if (g_IndexBuffer)
		g_IndexBuffer->Release();

	//頂点バッファの解放
	if (g_VertexBuffer)
		g_VertexBuffer->Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeshField(void)
{
	//g_Field.pos.x = GetPlayer()->GetPosition().x-250.0f;
	//g_Field.pos.z = GetPlayer()->GetPosition().z-250.0f;

	//if (GetStopAnything() == false) { g_Field.rot.y += (0.03f / GetSlowNum()); }

#ifdef DEBUG
	if (GetKeyboardPress(DIK_K)) { g_Field.pos.y += 1.0f; }
	if (GetKeyboardPress(DIK_L)) { g_Field.pos.y -= 1.0f; }
	char* str = GetDebugStr();
	//sprintf(&str[strlen(str)], "    MeshField.Y : %.2f", g_Field.pos.y);
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeshField(void)
{
	SetCullingMode(CULL_MODE_BACK);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// インデックスバッファ設定
	GetDeviceContext()->IASetIndexBuffer(g_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TexNo));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Field.mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, g_Field.scl.x, g_Field.scl.y, g_Field.scl.z);
	D3DXMatrixMultiply(&g_Field.mtxWorld, &g_Field.mtxWorld, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Field.rot.y, g_Field.rot.x, g_Field.rot.z);
	D3DXMatrixMultiply(&g_Field.mtxWorld, &g_Field.mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, g_Field.pos.x, g_Field.pos.y, g_Field.pos.z);
	D3DXMatrixMultiply(&g_Field.mtxWorld, &g_Field.mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(&g_Field.mtxWorld);

	// ポリゴンの描画
	GetDeviceContext()->DrawIndexed(g_IndexNum, 0, 0);
}

