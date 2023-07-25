#pragma once
#include "object.h"
#include "Icon.h"
#include "Number.h"
#include "camera.h"

#define ATTACK_COOLDOWN 15

#define ATTACK_KNOCKBACK 5.0f

#define STOP_TIME (3 * SECONDS)
#define SLOW_TIME (5 * SECONDS)

#define STOP_COOLDOWN (9 * SECONDS)
#define SLOW_COOLDOWN (6 * SECONDS)

#define ATTACK_RANGE D3DXVECTOR3(9.0f,6.0f,9.0f)

#define PLAYER_HP 100

#define GAME_UI_ERROR 1.25f

struct ABILITY
{
	bool UseBool;
	bool CoolDownBool;
	int Counter;
	int CounterMax;
	int CoolDownTimer;
	int CoolDownTimerMax;
	ICON meter;
};

class PLAYER :public OBJECT
{
public:
	//Miscellaneous
	D3DXVECTOR3 PlayerMoveSpeed;
	bool move;
	bool moveDiagonal;
	int rotationFix;
	int enemyCloseNum;
	bool called_1;
	bool called_2;

	//TopDown Effect
	bool topDown;
	bool topDownChange;
	float topDownAngle;
	float angleChanger;
	float normalAngle;
	int angleChangeCounter;
	int defeated;

	//Out Of Bounds
	bool OutOfBounds;

	//BASE PARAMETERS
	int PlayerHP;
	float PlayerSpeed;
	D3DXVECTOR3 AttackRange;
	int AttackCoolDown;
	float AttackKnockBack;
	int StopTime;
	int StopCoolDown;
	int SlowTime;
	int SlowCoolDowm;

	//ABILITIES
	ABILITY stop;
	ABILITY slow;
	TEXT TimeShade;

	//HP
	ICON HP;
	ICON HP_Container;
	ICON Blood;
	int hp;
	int hpMax;
	bool lowHP;

	//ATTACK
	bool attack;
	int attackCoolDown;
	int attackCoolDownMax;
	float attackKnockBack;
	D3DXVECTOR3 range;

	//EXPERIENCE
	int experience;
	int experienceMax;
	int experienceMaxBackUp;
	int level;
	int nextLevel;
	ICON Experience;
	ICON Experience_Container;
	NUMBER Level;
	TEXT LVL;

	//VALUES
	int experienceAmount;
	int damageRecieveAmount;

	//DEATH
	bool death;
	bool deathEffect;
	int deathCounter;
	int deathSoundDelay;
	bool control;

public:
	void Prepare() override;
	void Update() override;

	void SetPlayerMoveSpeed(D3DXVECTOR3 mov) { PlayerMoveSpeed = mov; }
	D3DXVECTOR3 GetPlayerMoveSpeed() { return PlayerMoveSpeed; }

	void Damage(int value) 
	{
		if (use == true && control == true)
		{
			value = (value + damageRecieveAmount + (GetDifficultyIncreaser() / 2));
			if (GetStage() == 1) { value = (int)((float)value * 1.2f); }
			else if (GetStage() == 2) { value = (int)((float)value * 1.5f); }
			GetCamera()->CameraShake((value * 2 < 4 ? 4 : value * 2));
			damage = true;
			black = true;
			hp -= value;
			HP.Color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			PlayReadSound(SE_PLAYER_DAMAGE, SE);
		}
	}

	void GainExperience(int value)
	{
		if (use == true && control == true)
		{
			if (level != 10 && experience <= experienceMax*2)
				experience += value + experienceAmount;
		}
	}

	void GainHealth(int value)
	{
		if (use == true && control == true)
		{
			if ((hp + value) < hpMax) { hp += value; }
			else { hp = hpMax; }
		}
	}
	void FaceTowardsRD(OBJECT* object, float correction)
	{
		float X = object->GetPosition().x;
		float Z = object->GetPosition().z;
		float corrector = 180;
		float height = (Z - Position.z);
		float base = (X - Position.x);

		if (object->GetPosition().z < Position.z) { corrector = 180; }
		else { corrector = 0; }

		RotationDirection.y = (D3DXToDegree(atanf(base / height))) + corrector + correction;
	}
};

int GetChosenPlayer();
PLAYER* GetPlayer();
void DrawPlayer();
void UnInitializePlayer();