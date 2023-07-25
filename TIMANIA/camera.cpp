//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "inputx.h"
#include "keyboard.h"
#include "camera.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比	
#define	VIEW_NEAR_Z		(0.5f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z		(400.0f)										// ビュー平面のFarZ値

#define	VALUE_MOVE_CAMERA	(20.0f)										// カメラの移動量
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)							// カメラの回転量

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static CAMERA			g_Camera;		// カメラデータ
//=============================================================================
// 初期化処理
//=============================================================================
void InitCamera(void)
{
	g_Camera.pos = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);
	g_Camera.at = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	//カメラの注視点
	g_Camera.up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	//カメラの上方向正規化ベクトル
	g_Camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_Camera.fov = VIEW_ANGLE;	//視野角40°

	g_Camera.shake = false;
	g_Camera.shakeValue = 0.0f;
	g_Camera.shakeCounter = 0;

	g_Camera.viewChanger = 20.0f;
	g_Camera.viewAngle = false;
	g_Camera.changeValue = VIEW_CHANGE;
	g_Camera.change = false;

	g_Camera.ViewFar = 1000.0f;

	// 視点と注視点の距離を計算
	float vx, vz;
	vx = g_Camera.pos.x - g_Camera.at.x;
	vz = g_Camera.pos.z - g_Camera.at.z;
	g_Camera.len = sqrtf(vx * vx + vz * vz);

}


//=============================================================================
// カメラの終了処理
//=============================================================================
void UninitCamera(void)
{

}


//=============================================================================
// カメラの更新処理
//=============================================================================
void UpdateCamera(void)
{
	if (g_Camera.inGame == true) { g_Camera.ViewFar = VIEW_FAR_Z; }
	else { g_Camera.ViewFar = 1000.0f; }

	if (g_Camera.shake == true)
	{
		g_Camera.shakeCounter++;
		if (g_Camera.shakeCounter % 3 == 0) { g_Camera.shakeValue *= -1; }
		g_Camera.at.x += g_Camera.shakeValue;

		if (g_Camera.shakeCounter % 15 == 0) { g_Camera.shake = false; }
	}

	if (g_Camera.viewAngle == true/* && g_Camera.fov < VIEW_ANGLE+20.0f*/)
	{
		/*if (g_Camera.fov <= (VIEW_ANGLE + g_Camera.viewChanger)) { */g_Camera.fov += g_Camera.changeValue*0.5f; g_Camera.changeValue *= 0.8f;
	}
	else if (g_Camera.viewAngle == false && g_Camera.change == true/*&& g_Camera.fov> VIEW_ANGLE*/)
	{
		/*if (g_Camera.fov >= (VIEW_ANGLE - g_Camera.viewChanger)) { */g_Camera.fov -= g_Camera.changeValue*0.5f; g_Camera.changeValue *= 0.8f;
	}

#ifdef DEBUG

	if (Keyboard_IsKeyDown(KK_D1))
	{// 視点移動「上」
		g_Camera.pos.y += VALUE_MOVE_CAMERA;
	}

	if (Keyboard_IsKeyDown(KK_D2))
	{// 視点移動「下」
		g_Camera.pos.y -= VALUE_MOVE_CAMERA;
	}

	if (Keyboard_IsKeyDown(KK_D3))
	{// 注視点旋回「左」
		g_Camera.rot.y -= VALUE_ROTATE_CAMERA;
		if (g_Camera.rot.y < -D3DX_PI)
		{
			g_Camera.rot.y += D3DX_PI * 2.0f;
		}

		g_Camera.at.x = g_Camera.pos.x + sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.at.z = g_Camera.pos.z + cosf(g_Camera.rot.y) * g_Camera.len;
	}

	if (Keyboard_IsKeyDown(KK_D4))
	{// 注視点旋回「右」
		g_Camera.rot.y += VALUE_ROTATE_CAMERA;
		if (g_Camera.rot.y > D3DX_PI)
		{
			g_Camera.rot.y -= D3DX_PI * 2.0f;
		}

		g_Camera.at.x = g_Camera.pos.x + sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.at.z = g_Camera.pos.z + cosf(g_Camera.rot.y) * g_Camera.len;
	}

	if (Keyboard_IsKeyDown(KK_D5))
	{// 注視点移動「上」
		g_Camera.at.y += VALUE_MOVE_CAMERA;
	}

	if (Keyboard_IsKeyDown(KK_D6))
	{// 注視点移動「下」
		g_Camera.at.y -= VALUE_MOVE_CAMERA;
	}

	if (Keyboard_IsKeyDown(KK_D7))
	{// 近づく
		g_Camera.len -= VALUE_MOVE_CAMERA;
		g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
	}

	if (Keyboard_IsKeyDown(KK_D8))
	{// 離れる
		g_Camera.len += VALUE_MOVE_CAMERA;
		g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
	}

	if (Keyboard_IsKeyDown(KK_N))
	{
		//g_Camera.fov -= 1.0f;
	}
	if (Keyboard_IsKeyDown(KK_M))
	{
		//g_Camera.fov += 1.0f;
	}
	// カメラを初期に戻す
	if (Keyboard_IsKeyDown(KK_D0))
	{
		UninitCamera();
		InitCamera();
	}
#endif
}


//=============================================================================
// カメラの更新
//=============================================================================
void SetCamera(void)
{

	// ビューマトリックス設定
	D3DXMatrixLookAtLH(&g_Camera.mtxView, &g_Camera.pos, &g_Camera.at, &g_Camera.up);
	SetViewMatrix(&g_Camera.mtxView);

	float det;
	D3DXMatrixInverse(&g_Camera.mtxInvView, &det, &g_Camera.mtxView);

	// プロジェクションマトリックス設定
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection, D3DXToRadian(g_Camera.fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, VIEW_NEAR_Z, g_Camera.ViewFar);
	SetProjectionMatrix(&g_Camera.mtxProjection);


}


//=============================================================================
// カメラの取得
//=============================================================================
CAMERA *GetCamera(void) 
{
	return &g_Camera;
}


// カメラの視点と注視点をセット
void SetCameraAT(D3DXVECTOR3 pos)
{
	// カメラの注視点をプレイヤーの座標にしてみる
	g_Camera.at = pos;

	// カメラの視点をカメラのY軸回転に対応させている	
	g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
	g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;

}

// カメラの視点と注視点をセット
void SetCameraATDelay(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 AtVec;
	D3DXVECTOR3 PosVec;
	
	//今回のカメラの座標
	PosVec.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
	PosVec.y = g_Camera.pos.y;
	PosVec.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
	
	AtVec = pos - g_Camera.at;	//注視点の変化ベクトル
	PosVec = PosVec - g_Camera.pos;	//一座標の変化

	PosVec *= 0.2f;	//ベクトルスケーリング
	AtVec *= 0.3f;	//ベクトルスケーリング

	// カメラの注視点をプレイヤーの座標にしてみる
	g_Camera.at += AtVec;
	g_Camera.pos += PosVec;
}
