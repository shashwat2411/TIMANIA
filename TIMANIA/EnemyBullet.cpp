#include "EnemyBullet.h"
#include "Explosion.h"
#include "player.h"

ENEMYBULLET g_EnemyBullet[ENEMYBULLET_MAX];

void ENEMYBULLET::Prepare()
{
	Initialize();

	Shadow.SetScaling(0.3f);
	//LoadModel((char*)"data/MODEL/EnemyBullet.obj", &Model);
	pModel = GetReadModel(READ_MODEL::RM_ENEMY_BULLET);
	Size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	CollisionSize = D3DXVECTOR3(0.4f, 0.4f, 0.4f);

	Speed = ENEMYBULLET_SPEED;

}

void ENEMYBULLET::Update()
{
	if (use == true)
	{
		if (GetStop() == false)
		{
			Counter += 1;

			Speed = ENEMYBULLET_SPEED*(1.0f + (float)GetDifficultyIncreaser() / TIME_DIVIDER);

			//if (GetSlow() == false && (fabs(MoveSpeedBackUp.x) > fabs(MoveSpeed.x) || fabs(MoveSpeedBackUp.z) > fabs(MoveSpeed.z))) { MoveSpeed = MoveSpeedBackUp; }
			if (Counter % (8*SECONDS * GetSlowNum()) == 0)
			{
				Counter = 0;
				Destroy();
			}
			if (DistanceFrom(GetPlayer()) >= 40.0f) { Destroy(); }

			Position += (MoveSpeed * (GetSlow() == true ? SLOW : 1.0f));
			//Rotation += D3DXVECTOR3(3.0f, 3.0f, 3.0f);

			Shadow.Update();
			Shadow.SetPosition(D3DXVECTOR3(Position.x, SHADOW_ERROR, Position.z));

			MoveSpeedNotSet();
		}
	}
}

void ENEMYBULLET::Destroy()
{
	use = false;
	SetExplosion(Position, D3DXVECTOR3(1.0f, 0.0f, 0.0f), EXPLOSION_TYPE::NORMAL, 0.8f, /*(DistanceFrom(GetPlayer()) < SOUND_DISTANCE / 4 ? SE_EXPLOSION_SMALL : */READ_SOUND_NONE);
	if (DistanceFrom(GetPlayer()) < SOUND_DISTANCE / 2) { PlayReadSound(SE_EXPLOSION_SMALL, SE, 0.02f*SoundDistance(GetPlayer())); }
}

void SetEnemyBullet(D3DXVECTOR3 pos, D3DXVECTOR3 mov, D3DXVECTOR3 rot)
{
	for (int i = 0; i < ENEMYBULLET_MAX; i++)
	{
		if (g_EnemyBullet[i].GetUse() == false)
		{
			g_EnemyBullet[i].SetSpeed(ENEMYBULLET_SPEED);
			g_EnemyBullet[i].SetPosition(pos);
			g_EnemyBullet[i].SetMoveSpeed(mov * g_EnemyBullet[i].GetSpeed());
			g_EnemyBullet[i].SetRotation(rot);
			g_EnemyBullet[i].SetUse(true);
			if (g_EnemyBullet[i].DistanceFrom(GetPlayer()) < SOUND_DISTANCE) { PlayReadSound(SE_ENEMY_BULLET_LAUNCH, SE, 0.1f*g_EnemyBullet[i].SoundDistance(GetPlayer())); }
			break;
		}
	}
}

HRESULT InitEnemyBullet()
{
	for (int i = 0; i < ENEMYBULLET_MAX; i++)
	{
		g_EnemyBullet[i].Prepare();
	}
	return S_OK;
}

void UnInitEnemyBullet()
{
	for (int i = 0; i < ENEMYBULLET_MAX; i++)
	{
		g_EnemyBullet[i].UnInitialize();
	}
}

void UpdateEnemyBullet()
{
	for (int i = 0; i < ENEMYBULLET_MAX; i++)
	{
		g_EnemyBullet[i].Update();
	}
}

void DrawEnemyBullet()
{
	for (int i = 0; i < ENEMYBULLET_MAX; i++)
	{
		g_EnemyBullet[i].Draw();
	}
}

ENEMYBULLET * GetEnemyBullet()
{
	return &g_EnemyBullet[0];
}
