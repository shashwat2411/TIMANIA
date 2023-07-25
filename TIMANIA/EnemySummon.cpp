#include "EnemySummon.h"
#include "Explosion.h"
#include "player.h"
#include "FloatRing.h"

#define KNOCKBACK_SPEED 1.0f

ENEMYSUMMON g_EnemySummon[ENEMYSUMMON_MAX];

void ENEMYSUMMON::Prepare()
{
	Initialize();

	Shadow.SetScaling(0.3f);
	//LoadModel((char*)"data/MODEL/EnemySummon.obj", &Model);
	pModel = GetReadModel(READ_MODEL::RM_ENEMY_SUMMON);
	Size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	SizeBackUp = Size;
	CollisionSize = D3DXVECTOR3(0.4f, 0.4f, 0.4f);
	MoveSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	knockBack = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	spawnCounter = 0;
	spawn = false;
	birthCounter = 0;
	birth = false;
	summonerSpeed = 0.0f;

	follow = nullptr;

	Speed = 0.4f;
}

void ENEMYSUMMON::Update()
{
	if (use == true)
	{
		if (GetStop() == false)
		{
			if (spawn == false && follow != nullptr)
			{
				spawnCounter++;
				D3DXVECTOR3 diff = SizeBackUp - Size;

				Position.x = follow->GetPosition().x;
				Position.y = follow->GetPosition().y;
				Position.z = follow->GetPosition().z;

				Rotation.y = follow->GetRotation().y;

				if (diff.x < 0.1f) { Size = SizeBackUp; }
				else { Size += diff * 0.1f; }

				if (follow->GetUse() == false) { Destroy(); }

				if (spawnCounter % 30 == 0)
				{
					int random = rand() % 2;
					float direction;
					spawn = true;
					spawnCounter = 0;
					knockBack = follow->GetMoveSpeed();
					D3DXVec3Normalize(&knockBack, &knockBack);

					if (random == 0) { direction = -1.0f; }
					else if (random == 1) { direction = 1.0f; }
					knockBack *= -KNOCKBACK_SPEED * direction;
				}
			}
			else if (spawn == true)
			{
				if (birth == false)
				{
					birthCounter++;

					//MoveSpeed = MoveInDirection() * Speed;
					MoveSpeed = D3DXVECTOR3(knockBack.z, MoveSpeed.y, knockBack.x);
					knockBack *= 0.9f;

					if (birthCounter % 60 == 0)
					{
						birthCounter = 0;
						birth = true;
						MoveSpeed.y = 0.02f;
						SetFloatRing(this, D3DXVECTOR3(0.5f, 0.5f, 0.5f), -0.5f, READ_MODEL::RM_FLOATRING_SUMMON);
						summonerSpeed += ENEMYSUMMON_SPEED;
						Speed = summonerSpeed;
					}
				}

				FaceTowards(GetPlayer());
				Position += (MoveSpeed * (GetSlow() == true ? SLOW : 1.0f));

				if (birth == true)
				{

					//knockBack *= 0.9f;
					MoveSpeed = D3DXVECTOR3(MoveTowardsR(GetPlayer()).x, MoveSpeed.y, MoveTowardsR(GetPlayer()).z);

					Counter++;
					if (Counter % 30 == 0) { MoveSpeed.y *= -1; /*PlayReadSound(SE_ENEMY_SUMMON_SOUND, SE);*/ }

					Speed = summonerSpeed * (1.0f + (float)GetDifficultyIncreaser() / TIME_DIVIDER);

				}
			}
		}
	}
}

void ENEMYSUMMON::Destroy()
{
	use = false;
	SetExplosion(Position, D3DXVECTOR3(1.0f, 0.0f, 0.0f), EXPLOSION_TYPE::NORMAL, 0.8f, /*(DistanceFrom(GetPlayer()) < SOUND_DISTANCE / 4 ? SE_EXPLOSION_SMALL : */READ_SOUND_NONE);
	follow = nullptr;
	PlayReadSound(SE_ENEMY_SUMMON_DEATH, SE, 0.05f);
}

void SetEnemySummon(D3DXVECTOR3 pos, D3DXVECTOR3 mov, D3DXVECTOR3 rot, float movSpeed, OBJECT* follower)
{
	for (int i = 0; i < ENEMYSUMMON_MAX; i++)
	{
		if (g_EnemySummon[i].GetUse() == false && g_EnemySummon[i].follow == nullptr)
		{
			g_EnemySummon[i].SetPosition(pos);
			g_EnemySummon[i].SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			g_EnemySummon[i].SetRotation(D3DXVECTOR3(0.0f, rot.y, 0.0f));

			g_EnemySummon[i].follow = follower;
			g_EnemySummon[i].knockBack = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_EnemySummon[i].spawnCounter = 0;
			g_EnemySummon[i].spawn = false;
			g_EnemySummon[i].birthCounter = 0;
			g_EnemySummon[i].birth = false;
			g_EnemySummon[i].summonerSpeed = movSpeed;

			g_EnemySummon[i].SetUse(true);

			if (g_EnemySummon[i].DistanceFrom(GetPlayer()) < SOUND_DISTANCE) { PlayReadSound(SE_ENEMY_SUMMON_SPAWN, SE, 0.05f*g_EnemySummon[i].SoundDistance(GetPlayer())); }

			break;
		}
	}
}

HRESULT InitEnemySummon()
{
	for (int i = 0; i < ENEMYSUMMON_MAX; i++)
	{
		g_EnemySummon[i].Prepare();
	}
	return S_OK;
}

void UnInitEnemySummon()
{
	for (int i = 0; i < ENEMYSUMMON_MAX; i++)
	{
		g_EnemySummon[i].UnInitialize();
	}
}

void UpdateEnemySummon()
{
	for (int i = 0; i < ENEMYSUMMON_MAX; i++)
	{
		g_EnemySummon[i].Update();
	}
}

void DrawEnemySummon()
{
	for (int i = 0; i < ENEMYSUMMON_MAX; i++)
	{
		g_EnemySummon[i].Draw();
	}
}

ENEMYSUMMON * GetEnemySummon()
{
	return &g_EnemySummon[0];
}
