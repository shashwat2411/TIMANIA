#pragma once
#include "Text.h"

enum LEVELUP
{
	HP_UP,
	EXPERIENCE_UP,
	MOVEMENT_SPEED_UP,
	ATTACK_COOLDOWN_DOWN,
	ATTACK_RANGE_UP,
	ATTACK_KNOCKBACK_UP,
	STOP_COOLDOWN_DOWN,
	SLOW_COOLDOWN_DOWN,
	STOP_TIME_UP,
	SLOW_TIME_UP,

	ABILITIES_MAX
};

class ABILITIES :public TEXT
{
public:

public:

	void Prepare() override
	{
		Initialize();

		use = false;
	}

	void Update() override
	{

	}

};

void InitializeAbilities();
void UnInitializeAbilities();
void UpdateAbilities();
void DrawAbilities();

void SetAbilitiesUse(bool value);
int GetChosen();