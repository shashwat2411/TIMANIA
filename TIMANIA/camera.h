//=============================================================================
//
// カメラ処理 [camera.h]
// Author : 
//
//=============================================================================
#pragma once


//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <d3dx9.h>
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	POS_X_CAM		(6.0f)			// カメラの初期位置(X座標)
#define	POS_Y_CAM		(5.5f)		// カメラの初期位置(Y座標)
#define	POS_Z_CAM		(-10.0f)		// カメラの初期位置(Z座標)

#define MOVE_ROTATION 6.0f

#define VIEW_CHANGE 10.0f
#define	VIEW_ANGLE	40.0f							// ビュー平面の視野角

class CAMERA
{
public:

	D3DXVECTOR3			pos;			// カメラの視点(位置)
	D3DXVECTOR3			at;				// カメラの注視点
	D3DXVECTOR3			up;				// カメラの上方向ベクトル
	D3DXVECTOR3			rot;			// カメラの回転

	float				len;			// カメラの視点と注視点の距離
	float				fov;			// 視野角

	D3DXMATRIX			mtxView;		// ビューマトリックス
	D3DXMATRIX			mtxInvView;		// ビューマトリックス
	D3DXMATRIX			mtxProjection;	// プロジェクションマトリックス

	bool shake;
	float shakeValue;
	int shakeCounter;

	float viewChanger;
	bool viewAngle;
	float changeValue;
	bool change;
	bool inGame;

	float ViewFar;

	void CameraShake(float value) 
	{ 
		//at.x += D3DXToRadian(value);
		shake = true;
		shakeValue = D3DXToRadian(value)*2;
		shakeCounter = 0;
	}

	void CameraRotate(float value)
	{
		rot.y = value;
		if (rot.y < -D3DX_PI)
		{
			rot.y += D3DX_PI * 2.0f;
		}

		at.x = pos.x + sinf(rot.y) * len;
		at.z = pos.z + cosf(rot.y) * len;
	}

	void SetZoom(bool value)
	{
		changeValue = VIEW_CHANGE;
		viewAngle = value;
		change = true;
	}
	void SetZoom(bool value, float v)
	{
		changeValue = VIEW_CHANGE * v;
		viewAngle = value;
		change = true;
	}
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
CAMERA *GetCamera(void);
void SetCameraAT(D3DXVECTOR3 pos);
void SetCameraATDelay(D3DXVECTOR3 pos);
