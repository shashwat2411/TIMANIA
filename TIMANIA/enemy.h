#pragma once
#include "object.h"
#include "Pointer.h"

#define ENEMY_MAX 30

//30 / 30 / 40
#define ENEMY_NUM (GetStage()==0?30:GetStage()==1?30:40)

enum ENEMY_TYPE
{
	FOLLOWER,
	SHOOTER,
	KAMIKAZE,
	SUMMONER,

	ENEMY_TYPE_MAX
};



class ENEMY :public OBJECT
{
public:
	int HP;
	bool collide;
	D3DXVECTOR3 KnockBack;
	ENEMY_TYPE Type;
	POINTER Pointer;
	int shooterCounter;
	int summonCounter;
	int summonSoundCounter;
	int followerCounter;
	int shakeCounter;
	int explodeCounter;
	float originalSpeed;
	int shotsFired;
	int cooldownCounter;
	bool coolDown;
	int hpAmount;

public:

	void SetSpeed(const float& value) { Speed = value; }
	const float GetSpeed() { return Speed; }

	void Prepare() override;
	void Update() override;

	void PrepareType(ENEMY_TYPE type);
	void Damage(int value);

};

HRESULT InitEnemy();
void UnInitEnemy();
void UpdateEnemy();
void DrawEnemy();
ENEMY* GetEnemy();
void SetEnemy(D3DXVECTOR3 spawnPoint, ENEMY_TYPE type);

int GetEnemyNumber();
void SetEnemyNumber(int value);