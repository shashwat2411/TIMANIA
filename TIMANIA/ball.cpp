#include "ball.h"
#include "player.h"

void BALL::Prepare()
{
	Initialize();

	Shadow.SetScaling(0.3f);
	
	Size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	SizeBackUp = Size;
	CollisionSize = Size * 1.2f;

	use = false;
}

void BALL::Update()
{
	if (use == true)
	{
		D3DXVECTOR3 diff = SizeBackUp - Size;

		if (diff.x < 0.07f) { Size = SizeBackUp; }
		else { Size += diff * 0.07f; }

		if (GetStop() == false)
		{

		}
	}
}

void BALL::PrepareType(BALL_TYPE type)
{
	Type = type;

	if (Type == HEALTH)
	{
		pModel = GetReadModel(READ_MODEL::RM_HP_BALL);
		//LoadModel((char*)"data/MODEL/EnemyBullet.obj", &Model);
	}
	else if (Type == EXP)
	{
		pModel = GetReadModel(READ_MODEL::RM_XP_BALL);
		//LoadModel((char*)"data/MODEL/EnemyBullet.obj", &Model);
	}
}

BALL g_Ball[BALL_MAX];
int BallCounter = 0;
HRESULT InitBall()
{
	for (int i = 0; i < BALL_MAX; i++)
	{
		g_Ball[i].Prepare();
	}
	BallCounter = 0;

	return S_OK;
}

void UnInitBall()
{
	for (int i = 0; i < BALL_MAX; i++)
	{
		g_Ball[i].UnInitialize();
	}
}

void UpdateBall()
{
	for (int i = 0; i < BALL_MAX; i++)
	{
		g_Ball[i].Update();
	}

	BallCounter++;

	//if (BallCounter % (30*SECONDS*GetSlowNum()) == 0 && GetStop() == false)
	//{
	//	BallCounter = 0;

	//	int directionX;
	//	int directionZ;

	//	int typeNum;
	//	BALL_TYPE type;
	//	//Direction
	//	{
	//		directionX = (int)rand() % 2;
	//		directionZ = (int)rand() % 2;

	//		if (directionX % 2 == 0) { directionX = 1; }
	//		else if (directionX % 2 == 1) { directionX = -1; }

	//		if (directionZ % 2 == 0) { directionZ = 1; }
	//		else if (directionZ % 2 == 1) { directionZ = -1; }
	//	}

	//	typeNum = rand() % BALL_TYPE::BALL_TYPE_MAX;
	//	if (typeNum == BALL_TYPE::HEALTH) { type = HEALTH; }
	//	else if (typeNum == BALL_TYPE::EXP) { type = EXP; }

	//	int rX = 20 + (rand() % 50);
	//	int rZfront = 160 + (rand() % 220);
	//	int rZback = 20 + (rand() % 50);
	//	//X
	//	float x/* = directionX * r * ((r > (GetPlayer()->GetPosition().x + 100.0f)) ? (1) : (-1))*/;
	//	if (directionX == 1) { x = GetPlayer()->GetPosition().x + (rX); }
	//	else if (directionX == -1) { x = GetPlayer()->GetPosition().x - (rX); }

	//	//Z
	//	float z;
	//	if (directionZ == 1) { z = GetPlayer()->GetPosition().z + (rZfront); }
	//	else if (directionZ == -1) { z = GetPlayer()->GetPosition().z - (rZback); }

	//	//Set
	//	SetBall(D3DXVECTOR3(x, Y_AXIS, z), type);
	//}
}

void DrawBall()
{
	for (int i = 0; i < BALL_MAX; i++)
	{
		g_Ball[i].Draw();
	}
}

BALL * GetBall() { return &g_Ball[0]; }

void SetBall(D3DXVECTOR3 pos, BALL_TYPE type)
{
	for (int i = 0; i < BALL_MAX; i++)
	{
		if (g_Ball[i].GetUse() == false)
		{
			g_Ball[i].SetUse(true);
			g_Ball[i].PrepareType(type);
			g_Ball[i].SetPosition(pos);
			g_Ball[i].SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			if (g_Ball[i].DistanceFrom(GetPlayer()) < SOUND_DISTANCE) { PlayReadSound(SE_ITEM_SPAWN, SE, 0.1f*g_Ball[i].SoundDistance(GetPlayer())); }
			return;
		}
	}
}
