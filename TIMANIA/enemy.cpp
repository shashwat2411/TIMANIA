#include "enemy.h"
#include "player.h"
#include "object.h"
#include "Explosion.h"
#include "Number.h"
#include "camera.h"
#include "EnemyBullet.h"
#include "ball.h"
#include "EnemySummon.h"
#include "FloatRing.h"
#include "Pointer.h"
#include "Dome.h"

#define VALUE_MOVE (GetStage()==0?0.055f:GetStage()==1?0.07f:0.08f)
#define VALUE_ROTATE 1.0f

#define OUT_OF_CAMERA_X_LEFT GetSkyDome()->GetSize().x/2 + 5.0f
#define OUT_OF_CAMERA_X_RIGHT 20.0f
#define OUT_OF_CAMERA_Z_FRONT 60.0f
#define OUT_OF_CAMERA_Z_BACK -20.0f


D3DXVECTOR4 OutOfCamera;


static ENEMY g_Enemy[ENEMY_MAX];
int SpawnCounter = 0;
int EnemyNumber = ENEMY_NUM;

void ENEMY::Prepare()
{
	Initialize();
	EnemyNumber = ENEMY_NUM;

	Position = D3DXVECTOR3(0.0f, Y_AXIS, 0.0f);
	Rotation = D3DXVECTOR3(MOVE_ROTATION, 0.0f, 0.0f);
	Size = D3DXVECTOR3(1.5f, 1.5f, 1.5f);
	CollisionSize = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	KnockBack = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	MoveSpeed = D3DXVECTOR3(0.0f, 0.01f, 0.0f);

	hpAmount = (GetStage() == 0 ? 0 : (GetStage() == 1 ? 2 : 4));

	shotsFired = 0;
	coolDown = false;
	cooldownCounter = 0;
	shooterCounter = 0;
	summonCounter = 0;
	summonSoundCounter = 0;
	followerCounter = 0;
	shakeCounter = 0;
	explodeCounter = 0;
	Speed = VALUE_MOVE;
	originalSpeed = Speed;
	HP = 3 + hpAmount;
	collide = false;
	Type = FOLLOWER;

	D3DXVec3Normalize(&Direction, &Direction);

	Material.Emission = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//Model = enemyModel1;
	//Pointer.Prepare();

	use = false;
}


void ENEMY::Update()
{
	//Pointer.Update();
	if (use == true)
	{
		//Pointer.SetRotation(D3DXVECTOR3(Pointer.GetRotation().x, Rotation.y+180.0f, Pointer.GetRotation().z));

		shakeCounter++;
		if (shakeCounter % 30 == 0) { MoveSpeed.y *= -1; }

		Speed = originalSpeed * (1.0f + (float)GetDifficultyIncreaser()/ TIME_DIVIDER);

		if (damage == true) { DamageCounter++; }
		if (damage == true && DamageCounter > DAMAGE_EFFECT_TIME) { damage = false; DamageCounter = 0; }
		if (collide == true) { Counter += 1; }
		if (Counter % GetPlayer()->attackCoolDownMax == 0) { collide = false; Counter = 0; }

		if (GetStop() == false)
		{
			//if (DistanceFrom(GetPlayer()) < SOUND_DISTANCE) { PlayReadSound(SE_HOVER, BGM, 0.5f*SoundDistance(GetPlayer())); }

			Position += (MoveSpeed * (GetSlow() == true ? SLOW : 1.0f));

			KnockBack *= 0.9;

			MoveSpeed = D3DXVECTOR3(MoveTowardsR(GetPlayer()).x - KnockBack.x, MoveSpeed.y, MoveTowardsR(GetPlayer()).z - KnockBack.z);
			FaceTowards(GetPlayer());

			if (Type == FOLLOWER)
			{
				followerCounter++;
				if (followerCounter % (5 * SECONDS) == 0) { if (DistanceFrom(GetPlayer()) < SOUND_DISTANCE) { PlayReadSound(SE_ENEMY_FOLLOW_SOUND, SE, 0.04f*SoundDistance(GetPlayer())); } followerCounter = 0; }
			}
			else if (Type == SHOOTER)
			{
				shooterCounter++;
				if (shooterCounter % (max((1*SECONDS - GetDifficultyIncreaser()*SECONDS/6),1) * GetSlowNum() ) == 0 && DistanceFrom(GetPlayer())<SOUND_DISTANCE*1.5f && coolDown == false)
				{
					if (shooterCounter >= 30) { shotsFired = 0; }
					SetEnemyBullet(Position, MoveInDirection(), Rotation);
					shooterCounter = 0;
					shotsFired++;
					if (shotsFired >= 20) { coolDown = true; }
				}
				if (coolDown == true)
				{
					cooldownCounter++;
					if (cooldownCounter % (3*SECONDS) == 0)
					{
						cooldownCounter = 0;
						coolDown = false;
						shotsFired = 0;
					}
				}
			}
			else if (Type == KAMIKAZE)
			{
				explodeCounter++;
				float distance = DistanceFrom(GetPlayer());
				if (explodeCounter % (max((int)distance, 15)*GetSlowNum()) == 0)
				{
					if (distance < SOUND_DISTANCE) { PlayReadSound(SE_ENEMY_TICK, SE, 0.1f*SoundDistance(GetPlayer())); }
					damage = true;
					black = false;
					explodeCounter = 0;
				}
			}
			else if (Type == SUMMONER)
			{
				summonCounter++;
				summonSoundCounter++;
				if (summonCounter % ((3 * SECONDS - GetDifficultyIncreaser()*SECONDS / 12) * GetSlowNum()) == 0 && DistanceFrom(GetPlayer()) < SOUND_DISTANCE * 2)
				{
					SetEnemySummon(D3DXVECTOR3(Position.x, Position.y, Position.z), MoveInDirection(), Rotation, Speed, this);
					summonCounter = 0;
				}
				//SetVolumeForReadSound(SE_ENEMY_SUMMONER_SOUND, 0.1f*SoundDistance(GetPlayer()));
				if (summonSoundCounter % (5 * SECONDS) == 0)
				{
					if (DistanceFrom(GetPlayer()) < SOUND_DISTANCE)
					{
						PlayReadSound(SE_ENEMY_SUMMON_SOUND, SE, 0.06f*SoundDistance(GetPlayer()));
					}
					summonSoundCounter = 0;
				}

			}

			Shadow.Update();
			Shadow.SetPosition(D3DXVECTOR3(Position.x, SHADOW_ERROR, Position.z));
		}
	}
}

void ENEMY::PrepareType(ENEMY_TYPE type)
{
	collide = false;
	Type = type;
	
	if (Type == FOLLOWER)
	{
		SetFloatRing(this, D3DXVECTOR3(0.5f, 0.5f, 0.5f), 0.0f, READ_MODEL::RM_FLOATRING_PURPLE);
		pModel = GetReadModel(READ_MODEL::RM_ENEMY_FOLLOWER);
		//LoadModel((char*)"data/MODEL/Follower.obj", &Model);
		Speed = VALUE_MOVE*3;
		followerCounter = 0;
		HP = 5 + hpAmount;
	}
	else if (Type == SHOOTER)
	{
		SetFloatRing(this, D3DXVECTOR3(0.5f, 0.5f, 0.5f), 0.0f, READ_MODEL::RM_FLOATRING_CYAN);
		pModel = GetReadModel(READ_MODEL::RM_ENEMY_SHOOTER);
		//LoadModel((char*)"data/MODEL/miku_01.obj", &Model);
		Speed = VALUE_MOVE;
		HP = 3 + hpAmount;
		shooterCounter = 0;
		shotsFired = 0;
		coolDown = false;
		cooldownCounter = 0;
		Rotation.x = 0.0f;
	}
	else if (Type == KAMIKAZE)
	{
		SetFloatRing(this, D3DXVECTOR3(0.5f, 0.5f, 0.5f), 0.0f, READ_MODEL::RM_FLOATRING_YELLOW);
		pModel = GetReadModel(READ_MODEL::RM_ENEMY_KAMIKAZE);
		//LoadModel((char*)"data/MODEL/miku_01.obj", &Model);
		Speed = VALUE_MOVE*5;
		explodeCounter = 0;
		HP = 2 + hpAmount;
	}
	else if (Type == SUMMONER)
	{
		SetFloatRing(this, D3DXVECTOR3(0.5f, 0.5f, 0.5f), 0.0f, READ_MODEL::RM_FLOATRING_BLACK);
		pModel = GetReadModel(READ_MODEL::RM_ENEMY_SUMMONER);
		Speed = VALUE_MOVE;
		summonCounter = 0;
		summonSoundCounter = 0;
		HP = 5 + hpAmount;
	}
	originalSpeed = Speed;
	Pointer.SetUse(true);
}

void ENEMY::Damage(int value)
{
	if (use == true)
	{
		D3DXVECTOR3 temp;
		D3DXVec3Normalize(&temp, &MoveSpeed);
		KnockBack = (temp * (0.06f < Speed ? (Speed < VALUE_MOVE * 8 ? Speed : VALUE_MOVE * 8) : 0.06f) * GetPlayer()->attackKnockBack * GetSlowNum());
		damage = true;
		black = true;
		HP -= value;
		PlayReadSound(SE_ENEMY_DAMAGE, SE);
		if (HP <= 0)
		{
			int chance = rand() % 15;
			int type = rand() % 2;
			use = false;
			HP = 0;
			if (Type == FOLLOWER)
			{
				SetExplosion(Position, MoveInDirection(), EXPLOSION_TYPE::NORMAL, 1.0f, SE_EXPLOSION_MEDIUM);
				GetPlayer()->GainExperience(3);
				AddScore(3);
				PlayReadSound(SE_EXPLOSION_MEDIUM, SE);
				StopReadSound(SE_ENEMY_FOLLOW_SOUND);
			}
			else if (Type == SHOOTER)
			{
				SetExplosion(Position, MoveInDirection(), EXPLOSION_TYPE::NORMAL, 1.0f, SE_EXPLOSION_MEDIUM);
				GetPlayer()->GainExperience(5);
				AddScore(5);
				PlayReadSound(SE_EXPLOSION_MEDIUM, SE);
			}
			else if (Type == KAMIKAZE)
			{
				if (collide == false) { GetPlayer()->Damage(7); }
				GetPlayer()->GainExperience(3);
				AddScore(3);
				SetExplosion(Position, MoveInDirection(), EXPLOSION_TYPE::DAMAGE, 3.0f, SE_EXPLOSION_BIG);
				PlayReadSound(SE_EXPLOSION_BIG, SE);
			}
			else if (Type == SUMMONER)
			{
				SetExplosion(Position, MoveInDirection(), EXPLOSION_TYPE::DAMAGE, 2.0f, SE_EXPLOSION_MEDIUM);
				GetPlayer()->GainExperience(8);
				AddScore(8);
				PlayReadSound(SE_EXPLOSION_MEDIUM, SE);
				StopReadSound(SE_ENEMY_SUMMONER_SOUND);
			}
			PlayReadSound(SE_ENEMY_DEATH, SE);

			
			if (chance == 0) { if (type == 0) { SetBall(Position, BALL_TYPE::HEALTH); } else if (type == 1) { SetBall(Position, BALL_TYPE::EXP); } }
			EnemyNumber--;
			GetPlayer()->defeated++;
		}
	}
}



HRESULT InitEnemy()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		g_Enemy[i].Prepare();
	}
	SpawnCounter = 0;

	return S_OK;
}

void UnInitEnemy()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		g_Enemy[i].UnInitialize();
		//g_Enemy[i].Pointer.UnInitialize();
	}
}

void UpdateEnemy()
{
	OutOfCamera.w = -(GetSkyDome()->GetSize().x / 2 + 5.0f);
	OutOfCamera.x = (GetSkyDome()->GetSize().x / 2 + 5.0f);
	OutOfCamera.y = -(GetSkyDome()->GetSize().z / 2 + 5.0f);
	OutOfCamera.z = (GetSkyDome()->GetSize().z / 2 + 5.0f);
	for (int i = 0; i < ENEMY_MAX; i++) { g_Enemy[i].Update(); }

	SpawnCounter++;
	int spawnSpeed = (3 * SECONDS - GetDifficultyIncreaser()*SECONDS/3) * GetSlowNum();
	//int spawnSpeed = 1;
	if (SpawnCounter % spawnSpeed == 0 && GetStop() == false)
	{
		SpawnCounter = 0;

		int directionX;
		int directionZ;

		int typeNum;
		ENEMY_TYPE type;
		//Direction
		{
			directionX = (int)rand() % 2;
			directionZ = (int)rand() % 2;

			if (directionX % 2 == 0) { directionX = 1; }
			else if (directionX % 2 == 1) { directionX = -1; }

			if (directionZ % 2 == 0) { directionZ = 1; }
			else if (directionZ % 2 == 1) { directionZ = -1; }
		}

		typeNum = rand() % ENEMY_TYPE::ENEMY_TYPE_MAX;
		if (typeNum == ENEMY_TYPE::FOLLOWER) { type = FOLLOWER; }
		else if (typeNum == ENEMY_TYPE::SHOOTER) { type = SHOOTER; }
		else if (typeNum == ENEMY_TYPE::KAMIKAZE) { type = KAMIKAZE; }
		else if (typeNum == ENEMY_TYPE::SUMMONER) { if (GetStage() != 0) { type = SUMMONER; } else { type = ENEMY_TYPE(rand() % (ENEMY_TYPE::ENEMY_TYPE_MAX - 1)); } }

		int rX = 50 + (rand() % 100);
		int rZfront = 130 + (rand() % 50);
		int rZback = 50 + (rand() % 100);
		//X
		float x/* = directionX * r * ((r > (GetPlayer()->GetPosition().x + 100.0f)) ? (1) : (-1))*/;
		if (directionX == 1) { x = GetPlayer()->GetPosition().x + (rX); }
		else if (directionX == -1) { x = GetPlayer()->GetPosition().x - (rX); }

		//Z
		float z;
		if (directionZ == 1) { z = GetPlayer()->GetPosition().z + (rZfront); }
		else if (directionZ == -1) { z = GetPlayer()->GetPosition().z - (rZback); }

		//Set
		SetEnemy(D3DXVECTOR3(x, Y_AXIS, z), type);
		//SetPointer(GetPlayer()->GetPosition());
	}

#ifdef DEBUG	// デバッグ情報を表示する
	char* str = GetDebugStr();
	//sprintf(&str[strlen(str)], "     SpawnSpeed : %d  Distance : %.2f", spawnSpeed, g_Enemy[0].DistanceFrom(GetPlayer()));
#endif
}

void DrawEnemy()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		g_Enemy[i].Draw();
		//g_Enemy[i].Pointer.Draw();
	}
}

ENEMY * GetEnemy()
{
	return &g_Enemy[0];
}

void SetEnemy(D3DXVECTOR3 spawnPoint, ENEMY_TYPE type)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].GetUse() == false)
		{
			g_Enemy[i].SetUse(true);
			g_Enemy[i].SetPosition(spawnPoint);
			g_Enemy[i].PrepareType(type);
			break;
		}
	}
}

int GetEnemyNumber() { return EnemyNumber; }
void SetEnemyNumber(int value) { EnemyNumber = value; }