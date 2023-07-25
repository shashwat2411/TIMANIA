//=============================================================================
//
// ポリゴン表示処理 [polygon.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "polygon.h"
#include "texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VALUE_MOVE		(5.0f)						// 移動量
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// 回転量

#define	SIZE_X			(100.0f)					// 地面のサイズ(X方向)
#define	SIZE_Z			(100.0f)					// 地面のサイズ(Z方向)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexPolygon(void);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// 頂点情報

static POLYGON						g_Polygon;			// ポリゴンデータ
static int							g_TexNo;			// テクスチャ番号


// 頂点配列
static VERTEX_3D g_VertexArray[4] = {
	{D3DXVECTOR3(-SIZE_X, 0.0f,  SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f)},
	{D3DXVECTOR3( SIZE_X, 0.0f,  SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f)},
	{D3DXVECTOR3(-SIZE_X, 0.0f, -SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f)},
	{D3DXVECTOR3( SIZE_X, 0.0f, -SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f)},
};

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPolygon(void)
{
	// 頂点バッファの作成
	MakeVertexPolygon();

	// テクスチャ生成
	g_TexNo = LoadTexture((char*)"data/TEXTURE/field002.jpg");

	// 位置・回転・スケールの初期設定
	g_Polygon.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Polygon.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Polygon.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPolygon(void)
{
	// 頂点バッファの解放
	if (g_VertexBuffer) {
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePolygon(void)
{
	CAMERA *cam = GetCamera();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPolygon(void)
{
	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TexNo));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Polygon.mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, g_Polygon.scl.x, g_Polygon.scl.y, g_Polygon.scl.z);
	D3DXMatrixMultiply(&g_Polygon.mtxWorld, &g_Polygon.mtxWorld, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Polygon.rot.y, g_Polygon.rot.x, g_Polygon.rot.z);
	D3DXMatrixMultiply(&g_Polygon.mtxWorld, &g_Polygon.mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, g_Polygon.pos.x, g_Polygon.pos.y, g_Polygon.pos.z);
	D3DXMatrixMultiply(&g_Polygon.mtxWorld, &g_Polygon.mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(&g_Polygon.mtxWorld);

	// ポリゴン描画
	GetDeviceContext()->Draw(4, 0);
}

HRESULT MakeVertexPolygon(void)
{
	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	// グローバルの頂点配列から頂点バッファをつくる
	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = g_VertexArray;

	GetDevice()->CreateBuffer(&bd, &sd, &g_VertexBuffer);

	return S_OK;
}