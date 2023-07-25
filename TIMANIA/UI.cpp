
#include "UI.h"
#include "camera.h"

static ID3D11Buffer		*g_VertexBuffer = NULL;	// 頂点バッファ

void UI::Initialize()
{
	vertex = nullptr;

	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scaling = D3DXVECTOR2(250.0f, 250.0f);
	Size = D3DXVECTOR2(1.0f, 1.0f);
	Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Offset = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	use = false;

	//frameRate = 60 / 12;
	//frameCount = 0;
	//animate = false;
	//yoko = 1.0f;
	//tate = 1.0f;
	//yokoNum = 1;
	//tateNum = 1;
	//imageNum = 1;
	//animationOffset = D3DXVECTOR2(0.0f, 0.0f);
	//animationOver = false;

	animate = false;
	animationOver = false;
	animationTimer = 0.0f;
	animationTimerMax = 0.0f;
	oneFrameTime = 0.0f;

	FrameWidth = 1;
	FrameHeight = 1;
	animationOffset.x = 0.0f;
	animationOffset.y = 0.0f;
	TextureSize = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);


	//// 頂点バッファに値をセットする
	//{
	//	D3D11_MAPPED_SUBRESOURCE msr;
	//	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	//	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	//	// 頂点座標の設定
	//	vertex[0].Position = D3DXVECTOR3(-(Size.x * Scaling.x) / 2.0f, 0.0f, 0.0f);
	//	vertex[1].Position = D3DXVECTOR3(-(Size.x * Scaling.x) / 2.0f, (Size.y * Scaling.y), 0.0f);
	//	vertex[2].Position = D3DXVECTOR3((Size.x * Scaling.x) / 2.0f, 0.0f, 0.0f);
	//	vertex[3].Position = D3DXVECTOR3((Size.x * Scaling.x) / 2.0f, (Size.y * Scaling.y), 0.0f);

	//	// 頂点カラーの設定
	//	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//	// テクスチャ座標の設定
	//	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
	//	vertex[1].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	//	vertex[2].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
	//	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	//	GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	//}


	TextNo = 0;

	left = 0.0f;
	right = 0.0f;

	ZeroMemory(&Material, sizeof(Material));
	Material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

}

void UI::UnInitialize()
{
	if (g_VertexBuffer != NULL)
	{// 頂点バッファの解放
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

void UI::Draw()
{
	if (use)
	{
		SetWorldViewProjection2D();
		// αテストを有効に
		SetAlphaTestEnable(true);

		// ライティングを無効
		SetLightEnable(false);

		SetDepthEnable(false);

		// 頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

		// プリミティブトポロジ設定
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// 頂点バッファに値をセットする
		{
			D3D11_MAPPED_SUBRESOURCE msr;
			GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

			vertex = (VERTEX_3D*)msr.pData;

			// 頂点座標の設定
			vertex[0].Position = D3DXVECTOR3((-(Size.x * Scaling.x) / 2.0f) + ((right*200.0f)), -(Size.y * Scaling.y) / 2.0f, 0.0f);
			vertex[1].Position = D3DXVECTOR3((+(Size.x * Scaling.x) / 2.0f) + ((left*200.0f)), -(Size.y * Scaling.y) / 2.0f, 0.0f);
			vertex[2].Position = D3DXVECTOR3((-(Size.x * Scaling.x) / 2.0f) + ((right*200.0f)), +(Size.y * Scaling.y) / 2.0f, 0.0f);
			vertex[3].Position = D3DXVECTOR3((+(Size.x * Scaling.x) / 2.0f) + ((left*200.0f)), +(Size.y * Scaling.y) / 2.0f, 0.0f);

			// 頂点カラーの設定
			SetMaterial(Material);
			vertex[0].Diffuse = Color;
			vertex[1].Diffuse = Color;
			vertex[2].Diffuse = Color;
			vertex[3].Diffuse = Color;

			// テクスチャ座標の設定
			vertex[0].TexCoord = D3DXVECTOR2((animationOffset.x) * TextureSize.x + right, (animationOffset.y) * TextureSize.y);
			vertex[1].TexCoord = D3DXVECTOR2((animationOffset.x + 1) * TextureSize.x + left, (animationOffset.y) * TextureSize.y);
			vertex[2].TexCoord = D3DXVECTOR2((animationOffset.x) * TextureSize.x + right, (animationOffset.y + 1) * TextureSize.y);
			vertex[3].TexCoord = D3DXVECTOR2((animationOffset.x + 1) * TextureSize.x + left, (animationOffset.y + 1) * TextureSize.y);

			Animate();

#ifdef _2D

			Position.x = SCREEN_WIDTH / 2 + (Offset.x*250.0f);
			Position.y = SCREEN_HEIGHT / 2 - ((Offset.y - 0.6f)*250.0f);
			Position.z = 0.0f;
			for (int i = 0; i < 4; i++)
			{
				vertex[i].Position.x += Position.x;
				vertex[i].Position.y += Position.y;
				vertex[i].Position.z = 0.0f;
			}

			// テクスチャ設定
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TextNo));
#endif
			GetDeviceContext()->Unmap(g_VertexBuffer, 0);

#ifdef _2D
			// ポリゴンの描画
			GetDeviceContext()->Draw(4, 0);
#endif
		}

#ifdef _3D

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxWorld);

		CAMERA* cam = GetCamera();

		mtxView = cam->mtxInvView;
		mtxView._41 = 0;
		mtxView._42 = 0;
		mtxView._43 = 0;

		Position = cam->pos + Offset + D3DXVECTOR3(0.0f, -0.5f, 3.0f);
		mtxWorld = mtxView;
		// 移動を反映
		D3DXMatrixScaling(&ScalingMatrix, (Size.x * Scaling.x), (Size.y * Scaling.y), 0.0f);
		D3DXMatrixTranslation(&TranslateMatrix, Position.x, Position.y, Position.z);

		//D3DXMatrixMultiply(&mtxWorld, &ScalingWorld, &TranslateMatrix);
		//D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxView);

		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &TranslateMatrix);
		// ワールドマトリックスの設定
		SetWorldMatrix(&mtxWorld);

		// マテリアル設定
		SetMaterial(Material);

		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TextNo));

		// ポリゴンの描画
		GetDeviceContext()->Draw(4, 0);

#endif

		//// ライティングを有効に
		//SetLightEnable(true);

		// αテストを無効に

		SetDepthEnable(true);
		SetAlphaTestEnable(false);
	}
}

void UI::Animate()
{
	if (animate && use)
	{
		animationTimer += oneFrameTime;


		if (animationTimer >= animationTimerMax)
		{
			animationTimer = 0.0f;
			animationOver = true;
		}

		animationOffset.x = (int)animationTimer % FrameWidth;
		animationOffset.y = (int)(animationTimer / FrameWidth);
	}
}