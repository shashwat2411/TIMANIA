//=============================================================================
//
// 弾処理 [bullet.h]
// Author : 
//
//=============================================================================
#pragma once

#include "UI.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BULLET_MAX		(300)		// バレットのMax数
#define BULLET_SPEED	(5.0f)		// バレットの移動スピード



// バレット構造体
class BULLET:public UI
{
public:
	int count = 0;
	void Prepare() override;
	void Update() override;

};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBullet(void);
void UnInitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

BULLET *GetBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 direction);

