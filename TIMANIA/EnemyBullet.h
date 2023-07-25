#pragma once
#include "object.h"

#define ENEMYBULLET_MAX 300
#define ENEMYBULLET_SPEED 0.2f

class ENEMYBULLET :public OBJECT
{
public:

public:

	void Prepare() override;
	void Update() override;

	void Destroy();

};

HRESULT InitEnemyBullet();
void UnInitEnemyBullet();
void UpdateEnemyBullet();
void DrawEnemyBullet();
ENEMYBULLET* GetEnemyBullet();
void SetEnemyBullet(D3DXVECTOR3 pos, D3DXVECTOR3 mov, D3DXVECTOR3 rot);