//=============================================================================
//
// 弾処理 [bullet.cpp]
// Author : 
//
//=============================================================================
#include "bullet.h"
#include "camera.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer		*g_VertexBuffer = NULL;	// 頂点バッファ

static BULLET		g_Bullet[BULLET_MAX];	// 弾データ



//=============================================================================
// 初期化処理
//=============================================================================


void BULLET::Prepare()
{
	Initialize();

	Offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Size = D3DXVECTOR2(1.0f, 1.0f);

	animate = true;
	animationTimer = 0.0f;
	animationTimerMax = 8.0f;
	oneFrameTime = 0.2f;

	FrameWidth = 8;
	FrameHeight = 1;

	TextureSize.x = 1.0f / FrameWidth;
	TextureSize.y = 1.0f / FrameHeight;

	TextNo = LoadTexture((char*)"data/TEXTURE/explosion000.png");
}
void BULLET::Update()
{
	if (use)
	{
		if (animationOver == true)
		{
			use = false;
		}
	}
}

void InitBullet(void)
{
	// マテリアル初期化

	// 初期化
	for(int i = 0; i < BULLET_MAX; i++)
	{
		g_Bullet[i].Prepare();
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UnInitBullet(void)
{
	for (int i = 0; i < BULLET_MAX; i++)
		g_Bullet[i].UnInitialize();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBullet(void)
{
	for(int i = 0; i < BULLET_MAX; i++)
	{
		g_Bullet[i].Update();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBullet(void)
{
	for (int i = 0; i < BULLET_MAX; i++)
		g_Bullet[i].Draw();
}


//=============================================================================
// 弾のパラメータをセット
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 direction)
{
	for(int i = 0; i < BULLET_MAX; i++)
	{
		//まだ表示されていない場所を探す
		if(g_Bullet[i].use == false)
		{
			D3DXVec3Normalize(&direction, &direction);
			direction *= BULLET_SPEED;
			g_Bullet[i].Position = pos;
			g_Bullet[i].Move = direction;
			g_Bullet[i].count = 0.0f;
			g_Bullet[i].use = true;
			g_Bullet[i].animationOver = false;
			break;
		}
	}
}

BULLET* GetBullet(void)
{
	return &g_Bullet[0];
}
