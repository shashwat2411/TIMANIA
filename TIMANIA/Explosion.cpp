#include "Explosion.h"

#define EXPLOSION_SIZE 1.5f
int random = 0;

void EXPLOSION::Prepare()
{
	Initialize();

	//LoadModel((char*)"data/MODEL/miku_01.obj", &Model);
	pModel = GetReadModel(READ_MODEL::RM_EXPLOSION_1);
	Size = D3DXVECTOR3(EXPLOSION_SIZE, EXPLOSION_SIZE, EXPLOSION_SIZE);
	CollisionSize = Size;

	Shadow.SetUse(false);
	Speed = 0.1f;

	Type = NORMAL;
	//blink = true;
	stopper = false;
	use = false;
	Gravity = true;
	damage = true;
	black = false;
}

void EXPLOSION::Update()
{
	if (use == true && stopper == false)
	{
		Counter += 1;
		if (Counter%GetSlowNum() == 0) { MoveSpeed *= 0.9; }
		Position += (MoveSpeed * (GetSlow() == true ? SLOW : 1.0f));
		if (Gravity == true && GetStopAnything() == false) { Position.y -= (GRAVITY * (GetSlow() == true ? SLOW : 1.0f)); }
		if (Counter % (10 * GetSlowNum()) == 0)
		{
			if (Type != DAMAGE) { Gravity = true; }
			if (GetStop() == true) { stopper = true; Gravity = false; }
		}
		if (Counter % (20 * GetSlowNum()) == 0)
		{
			Counter = 0;
			use = false;
			stopper = false;
			//blink = false;
			//Gravity = false;
		}

		Shadow.Update();
		Shadow.SetPosition(D3DXVECTOR3(Position.x, SHADOW_ERROR, Position.z));

		//MoveSpeedNotSet();
	}
	if (GetStop() == false) { stopper = false; if (Type != DAMAGE) { Gravity = true; } }
	//Blink
	//if (Counter % 10 == 0 && blink) { use = false; Counter++; }
	//else if(blink && Counter % 10 == 5) { use = true; }
}


EXPLOSION g_Explosion[EXPLOSION_MAX];
void InitExplosion()
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		g_Explosion[i].Prepare();
	}
}

void UnInitExplosion()
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		g_Explosion[i].UnInitialize();
	}
}

void UpdateExplosion()
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		g_Explosion[i].Update();
	}
}

void DrawExplosion()
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		g_Explosion[i].Draw();
	}
}

EXPLOSION * GetExplosion()
{
	return &g_Explosion[0];
}

//void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 mov, EXPLOSION_TYPE type, float size, float volume)
//{
//	int n = 0;
//	for (int i = 0; i < EXPLOSION_MAX; i++)
//	{
//		if (g_Explosion[i].GetUse() == false)
//		{
//			n++;
//			g_Explosion[i].Type = type;
//			g_Explosion[i].SetUse(true);
//			g_Explosion[i].SetPosition(pos);
//			g_Explosion[i].SetSize(D3DXVECTOR3(EXPLOSION_SIZE * size, EXPLOSION_SIZE * size, EXPLOSION_SIZE * size));
//			float distance = 1.41f*size;
//
//			//if (g_Explosion[i].Type == NORMAL)
//			//{
//			//	mov.x = -(-mov.x / mov.x) * 1.0f;
//			//	mov.z = -(-mov.x / mov.x) * 1.0f;
//
//			//	if (n > NORMAL_SET_NUMBER) { return; }
//
//			//	if		(n == 1) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	mov.x,					mov.y,			mov.z				)	* g_Explosion[i].GetSpeed()); }
//			//	else if (n == 2) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	-mov.x,					mov.y,			mov.z				)	* g_Explosion[i].GetSpeed()); }
//			//	else if (n == 3) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	mov.x,					mov.y,			-mov.z				)	* g_Explosion[i].GetSpeed()); }
//			//	else if (n == 4) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	-mov.x,					mov.y,			-mov.z				)	* g_Explosion[i].GetSpeed()); }
//			//	else if (n == 5) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	0.0f,					mov.y,			distance * mov.z	)	* g_Explosion[i].GetSpeed()); }
//			//	else if (n == 6) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	distance * -mov.x,		mov.y,			0.0f				)	* g_Explosion[i].GetSpeed()); }
//			//	else if (n == 7) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	0.0f,					mov.y,			distance * -mov.z	)	* g_Explosion[i].GetSpeed()); }
//			//	else if (n == 8) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	distance * mov.x,		mov.y,			 0.0f				)	* g_Explosion[i].GetSpeed()); }
//
//			//	g_Explosion[i].FaceInDirection();
//			//}
//			//else if (g_Explosion[i].Type == DAMAGE)
//			//{
//			mov.x = -(-mov.x / mov.x) * 2.0f;
//			mov.z = -(-mov.x / mov.x) * 2.0f;
//
//			g_Explosion[i].SetGravity(false);
//
//			if (n > NORMAL_SET_NUMBER * 3) { return; }
//
//			if (n == 1) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(mov.x, mov.y, mov.z)	* g_Explosion[i].GetSpeed()); }
//			else if (n == 2) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(-mov.x, mov.y, mov.z)	* g_Explosion[i].GetSpeed()); }
//			else if (n == 3) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(mov.x, mov.y, -mov.z)	* g_Explosion[i].GetSpeed()); }
//			else if (n == 4) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(-mov.x, mov.y, -mov.z)	* g_Explosion[i].GetSpeed()); }
//			else if (n == 5) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(0.0f, mov.y, distance * mov.z)	* g_Explosion[i].GetSpeed()); }
//			else if (n == 6) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(distance * -mov.x, mov.y, 0.0f)	* g_Explosion[i].GetSpeed()); }
//			else if (n == 7) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(0.0f, mov.y, distance * -mov.z)	* g_Explosion[i].GetSpeed()); }
//			else if (n == 8) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(distance * mov.x, mov.y, 0.0f)	* g_Explosion[i].GetSpeed()); }
//
//			//else if (n == 9)  { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	mov.x,					distance,			mov.z				)	* g_Explosion[i].GetSpeed()); }
//			//else if (n == 10) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	-mov.x,					distance,			mov.z				)	* g_Explosion[i].GetSpeed()); }
//			//else if (n == 11) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	mov.x,					distance,			-mov.z				)	* g_Explosion[i].GetSpeed()); }
//			//else if (n == 12) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	-mov.x,					distance,			-mov.z				)	* g_Explosion[i].GetSpeed()); }
//			else if (n == 13) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(0.0f, distance, distance * mov.z)	* g_Explosion[i].GetSpeed()); }
//			else if (n == 14) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(distance * -mov.x, distance, 0.0f)	* g_Explosion[i].GetSpeed()); }
//			else if (n == 15) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(0.0f, distance, distance * -mov.z)	* g_Explosion[i].GetSpeed()); }
//			else if (n == 16) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(distance * mov.x, distance, 0.0f)	* g_Explosion[i].GetSpeed()); }
//
//			//else if (n == 17) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	mov.x,					-distance,			mov.z				)	* g_Explosion[i].GetSpeed()); }
//			//else if (n == 18) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	-mov.x,					-distance,			mov.z				)	* g_Explosion[i].GetSpeed()); }
//			//else if (n == 19) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	mov.x,					-distance,			-mov.z				)	* g_Explosion[i].GetSpeed()); }
//			//else if (n == 20) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	-mov.x,					-distance,			-mov.z				)	* g_Explosion[i].GetSpeed()); }
//			else if (n == 21) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(0.0f, -distance, distance * mov.z)	* g_Explosion[i].GetSpeed()); }
//			else if (n == 22) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(distance * -mov.x, -distance, 0.0f)	* g_Explosion[i].GetSpeed()); }
//			else if (n == 23) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(0.0f, -distance, distance * -mov.z)	* g_Explosion[i].GetSpeed()); }
//			else if (n == 24) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(distance * mov.x, -distance, 0.0f)	* g_Explosion[i].GetSpeed()); }
//
//			if (n > 8) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(g_Explosion[i].GetMoveSpeed().x*0.5f, g_Explosion[i].GetMoveSpeed().y, g_Explosion[i].GetMoveSpeed().z*0.5f)); }
//			g_Explosion[i].FaceInDirection();
//			//}
//			if (volume > 0.0f) { PlayReadSound(SE_EXPLOSION_SMALL, SE); }
//		}
//	}
//}

void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 mov, EXPLOSION_TYPE type, float size, READ_SOUND num)
{
	int n = 0;
	int chooser = random;
	while (chooser == random)
	{
		chooser = rand() % 2;
	}
	random = chooser;
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (g_Explosion[i].GetUse() == false)
		{
			if (random == 0) { g_Explosion[i].SetModelPointer(GetReadModel(RM_EXPLOSION_1)); }
			else if (random == 1) { g_Explosion[i].SetModelPointer(GetReadModel(RM_EXPLOSION_2)); }

			n++;
			g_Explosion[i].Type = type;
			g_Explosion[i].SetUse(true);
			g_Explosion[i].SetPosition(pos);
			g_Explosion[i].SetSize(D3DXVECTOR3(EXPLOSION_SIZE * size, EXPLOSION_SIZE * size, EXPLOSION_SIZE * size));
			float distance = 1.41f*size;

			//if (g_Explosion[i].Type == NORMAL)
			//{
			//	mov.x = -(-mov.x / mov.x) * 1.0f;
			//	mov.z = -(-mov.x / mov.x) * 1.0f;

			//	if (n > NORMAL_SET_NUMBER) { return; }

			//	if		(n == 1) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	mov.x,					mov.y,			mov.z				)	* g_Explosion[i].GetSpeed()); }
			//	else if (n == 2) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	-mov.x,					mov.y,			mov.z				)	* g_Explosion[i].GetSpeed()); }
			//	else if (n == 3) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	mov.x,					mov.y,			-mov.z				)	* g_Explosion[i].GetSpeed()); }
			//	else if (n == 4) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	-mov.x,					mov.y,			-mov.z				)	* g_Explosion[i].GetSpeed()); }
			//	else if (n == 5) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	0.0f,					mov.y,			distance * mov.z	)	* g_Explosion[i].GetSpeed()); }
			//	else if (n == 6) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	distance * -mov.x,		mov.y,			0.0f				)	* g_Explosion[i].GetSpeed()); }
			//	else if (n == 7) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	0.0f,					mov.y,			distance * -mov.z	)	* g_Explosion[i].GetSpeed()); }
			//	else if (n == 8) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	distance * mov.x,		mov.y,			 0.0f				)	* g_Explosion[i].GetSpeed()); }

			//	g_Explosion[i].FaceInDirection();
			//}
			//else if (g_Explosion[i].Type == DAMAGE)
			//{
			mov.x = -(-mov.x / mov.x) * 2.0f;
			mov.z = -(-mov.x / mov.x) * 2.0f;

			g_Explosion[i].SetGravity(false);

			if (n > NORMAL_SET_NUMBER * 2) { return; }

			if (n == 1) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(mov.x, mov.y, mov.z)	* g_Explosion[i].GetSpeed()); }
			else if (n == 2) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(-mov.x, mov.y, mov.z)	* g_Explosion[i].GetSpeed()); }
			else if (n == 3) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(mov.x, mov.y, -mov.z)	* g_Explosion[i].GetSpeed()); }
			else if (n == 4) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(-mov.x, mov.y, -mov.z)	* g_Explosion[i].GetSpeed()); }
			else if (n == 5) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(0.0f, mov.y, distance * mov.z)	* g_Explosion[i].GetSpeed()); }
			else if (n == 6) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(distance * -mov.x, mov.y, 0.0f)	* g_Explosion[i].GetSpeed()); }
			else if (n == 7) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(0.0f, mov.y, distance * -mov.z)	* g_Explosion[i].GetSpeed()); }
			else if (n == 8) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(distance * mov.x, mov.y, 0.0f)	* g_Explosion[i].GetSpeed()); }

			//else if (n == 9)  { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	mov.x,					distance,			mov.z				)	* g_Explosion[i].GetSpeed()); }
			//else if (n == 10) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	-mov.x,					distance,			mov.z				)	* g_Explosion[i].GetSpeed()); }
			//else if (n == 11) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	mov.x,					distance,			-mov.z				)	* g_Explosion[i].GetSpeed()); }
			//else if (n == 12) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	-mov.x,					distance,			-mov.z				)	* g_Explosion[i].GetSpeed()); }
			else if (n == 9) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(0.0f, distance, distance * mov.z)	* g_Explosion[i].GetSpeed()); }
			else if (n == 10) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(distance * -mov.x, distance, 0.0f)	* g_Explosion[i].GetSpeed()); }
			else if (n == 11) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(0.0f, distance, distance * -mov.z)	* g_Explosion[i].GetSpeed()); }
			else if (n == 12) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(distance * mov.x, distance, 0.0f)	* g_Explosion[i].GetSpeed()); }

			//else if (n == 17) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	mov.x,					-distance,			mov.z				)	* g_Explosion[i].GetSpeed()); }
			//else if (n == 18) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	-mov.x,					-distance,			mov.z				)	* g_Explosion[i].GetSpeed()); }
			//else if (n == 19) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	mov.x,					-distance,			-mov.z				)	* g_Explosion[i].GetSpeed()); }
			//else if (n == 20) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(	-mov.x,					-distance,			-mov.z				)	* g_Explosion[i].GetSpeed()); }
			else if (n == 13) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(0.0f, -distance, distance * mov.z)	* g_Explosion[i].GetSpeed()); }
			else if (n == 14) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(distance * -mov.x, -distance, 0.0f)	* g_Explosion[i].GetSpeed()); }
			else if (n == 15) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(0.0f, -distance, distance * -mov.z)	* g_Explosion[i].GetSpeed()); }
			else if (n == 16) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(distance * mov.x, -distance, 0.0f)	* g_Explosion[i].GetSpeed()); }

			if (n > 8) { g_Explosion[i].SetMoveSpeed(D3DXVECTOR3(g_Explosion[i].GetMoveSpeed().x*0.5f, g_Explosion[i].GetMoveSpeed().y, g_Explosion[i].GetMoveSpeed().z*0.5f)); }
			g_Explosion[i].FaceInDirection();
			//}

			//PlayReadSound(num, SE);
		}
	}
}