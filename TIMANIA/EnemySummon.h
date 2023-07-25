#pragma once
#include "object.h"

#define ENEMYSUMMON_MAX 100
#define ENEMYSUMMON_SPEED 0.1f

class ENEMYSUMMON :public OBJECT
{
public:
	D3DXVECTOR3 knockBack;
	D3DXVECTOR3 SizeBackUp;
	float summonerSpeed;
	int spawnCounter;
	bool spawn;
	int birthCounter;
	bool birth;
	OBJECT* follow;

public:

	void Prepare() override;
	void Update() override;

	void Destroy();

};

HRESULT InitEnemySummon();
void UnInitEnemySummon();
void UpdateEnemySummon();
void DrawEnemySummon();
ENEMYSUMMON* GetEnemySummon();
void SetEnemySummon(D3DXVECTOR3 pos, D3DXVECTOR3 mov, D3DXVECTOR3 rot, float movSpeed, OBJECT* follower);