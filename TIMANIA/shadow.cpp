#include "shadow.h"
#include "Texture.h"
#include "renderer.h"

//=========================================
//マクロ定義
//=========================================
#define SHADOW_SIZE_X	1.0f
#define SHADOW_SIZE_Z	1.0f
#define SHADOW_MAX		1

//=========================================
//グローバル変数
//=========================================
static		ID3D11Buffer	*g_VertexBufferShadow = NULL;

//static SHADOW g_Shadow[SHADOW_MAX];
static int g_TexNoShadow;	// テクスチャ番号

//メンバー関数
void SHADOW::Init()
{
	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBufferShadow);

	//頂点バッファの初期化
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBufferShadow, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);	//バッファへの書き込み許可をもらう
	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;	//書き込み先のポインタを取得

	//頂点座標
	vertex[0].Position = D3DXVECTOR3(-SHADOW_SIZE_X / 2.0f, 0.0f, SHADOW_SIZE_Z / 2.0f);
	vertex[1].Position = D3DXVECTOR3(SHADOW_SIZE_X / 2.0f, 0.0f, SHADOW_SIZE_Z / 2.0f);
	vertex[2].Position = D3DXVECTOR3(-SHADOW_SIZE_X / 2.0f, 0.0f, -SHADOW_SIZE_Z / 2.0f);
	vertex[3].Position = D3DXVECTOR3(SHADOW_SIZE_X / 2.0f, 0.0f, -SHADOW_SIZE_Z / 2.0f);
	//頂点法線
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//頂点色
	vertex[0].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.8f);
	vertex[1].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.8f);
	vertex[2].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.8f);
	vertex[3].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.8f);
	//頂点のテクスチャ座標
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	//	頂点バッファへの書き込み終了
	GetDeviceContext()->Unmap(g_VertexBufferShadow, 0);

	g_TexNoShadow = LoadTexture((char*)"data/TEXTURE/shadow000.jpg");

	ZeroMemory(&Material, sizeof(Material));
	Material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scaling = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	use = true;
}

void SHADOW::UnInit()
{
	if (g_VertexBufferShadow)
	{
		g_VertexBufferShadow->Release();
		g_VertexBufferShadow = NULL;
	}
}

void SHADOW::Update()
{
	if (use)
	{

	}
}

void SHADOW::Draw()
{
	if (use)
	{
		SetAlphaTestEnable(true);
		SetLightEnable(false);
		SetDepthEnable(false);	//奥行無視

		// 頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBufferShadow, &stride, &offset);

		// プリミティブトポロジ設定
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		//頂点バッファの初期化
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(g_VertexBufferShadow, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);	//バッファへの書き込み許可をもらう
		VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;	//書き込み先のポインタを取得

		//頂点座標
		vertex[0].Position = D3DXVECTOR3(-SHADOW_SIZE_X / 2.0f, 0.0f, SHADOW_SIZE_Z / 2.0f);
		vertex[1].Position = D3DXVECTOR3(SHADOW_SIZE_X / 2.0f, 0.0f, SHADOW_SIZE_Z / 2.0f);
		vertex[2].Position = D3DXVECTOR3(-SHADOW_SIZE_X / 2.0f, 0.0f, -SHADOW_SIZE_Z / 2.0f);
		vertex[3].Position = D3DXVECTOR3(SHADOW_SIZE_X / 2.0f, 0.0f, -SHADOW_SIZE_Z / 2.0f);
		//頂点法線
		vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//頂点色
		vertex[0].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.8f);
		vertex[1].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.8f);
		vertex[2].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.8f);
		vertex[3].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.8f);
		//頂点のテクスチャ座標
		vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
		vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
		vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

		//	頂点バッファへの書き込み終了
		GetDeviceContext()->Unmap(g_VertexBufferShadow, 0);


		SetBlendState(BLEND_MODE_ADD);



		////頂点バッファセット
		//UINT stride = sizeof(VERTEX_3D);
		//UINT offset = 0;
		//GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);
		////Primitive Topolgy Setting
		//GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		////テクスチャのセット
		//GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TexNoShadow));

		//影の描画
		D3DXMatrixIdentity(&mtxWorld);	//ワールド行列の初期化

		D3DXMatrixScaling(&ScalingMatrix, Scaling.x, Scaling.y, Scaling.z);
		D3DXMatrixRotationYawPitchRoll(&RotationMatrix, Rotation.y, Rotation.x, Rotation.z);
		D3DXMatrixTranslation(&TranslationMatrix, Position.x, Position.y, Position.z);

		D3DXMatrixMultiply(&mtxWorld, &ScalingMatrix, &RotationMatrix);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &TranslationMatrix);

		SetWorldMatrix(&mtxWorld);

		//SetMaterial(Material);
		//テクスチャのセット
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TexNoShadow));

		GetDeviceContext()->Draw(4, 0);

		SetDepthEnable(true);
		SetAlphaTestEnable(false);
		SetBlendState(BLEND_MODE_ALPHABLEND);
	}
}



////グローバル関数
//HRESULT InitShadow()
//{
//	for (int i = 0; i < SHADOW_MAX; i++)
//	{
//		g_Shadow[i].Init();
//	}
//	return S_OK;
//}
//
//void UnInitShadow()
//{
//	for (int i = 0; i < SHADOW_MAX; i++)
//	{
//		g_Shadow[i].UnInit();
//	}
//}
//
//void UpdateShadow()
//{
//	for (int i = 0; i < SHADOW_MAX; i++)
//	{
//		g_Shadow[i].Update();
//	}
//}
//
//void DrawShadow()
//{
//	for (int i = 0; i < SHADOW_MAX; i++)
//	{
//		g_Shadow[i].Draw();
//	}
//}
//
//int SetShadow(D3DXVECTOR3 pos, float size)
//{
//	int index = -1;
//
//	for (int i = 0; i < SHADOW_MAX; i++)
//	{
//		if (g_Shadow[i].GetUse() == false)
//		{
//			g_Shadow[i].SetPosition(pos);
//			g_Shadow[i].SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
//			g_Shadow[i].SetScaling(size);
//			g_Shadow[i].SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
//			g_Shadow[i].SetUse(true);
//
//			index = i;
//			break;
//		}
//	}
//
//	return index;	//作成した影のインデックスを返す、-1は作成失敗
//}
//
//void ReleaseShadow(int index)
//{
//	if (index >= 0 && index < SHADOW_MAX)
//	{
//		g_Shadow[index].SetUse(false);
//	}
//}
//
//void SetPositionShadow(int index, D3DXVECTOR3 pos)
//{
//	if (index >= 0 && index < SHADOW_MAX)
//	{
//		g_Shadow[index].SetPosition(pos);
//	}
//}