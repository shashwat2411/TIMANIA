//=============================================================================
//
// メッシュ地面の処理 [meshfield.h]
// Author : 
//
//=============================================================================
#pragma once

struct FIELD
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scl;
	D3DXMATRIX  mtxWorld;
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitMeshField(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int numBlockX, int numBlockZ, float sizeX, float sizeZ);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);

