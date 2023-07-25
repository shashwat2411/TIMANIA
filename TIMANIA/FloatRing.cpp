#include "FloatRing.h"
#include "player.h"

FLOATRING g_FloatRing[FLOATRING_MAX];

void FLOATRING::Prepare()
{
	Initialize();
	//LoadModel((char*)"data/MODEL/Laser.obj", &Model);
	//pModel = &Model;

	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Size = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
	SizeBackUp = Size;
	FloatSpeed = D3DXVECTOR3(0.0f, -0.02f, 0.0f);
	MoveSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	followDelay = 0.2f;
	OffsetY = 0.05f;
	PositionY = Position.y;
	LimitY = Position.y - OffsetY;
	SizeLimit = 2.32f;

	follow = nullptr;

	use = false;
}
void FLOATRING::Update()
{
	if (follow != nullptr)
	{
		if (follow->GetUse() == false) { use = false; follow = nullptr; return; }
		if (follow->GetUse() == true)
		{
			D3DXVECTOR3 PosVec;

			PosVec = follow->GetPosition();
			PosVec -= Position;
			PosVec *= followDelay;
			Position += D3DXVECTOR3(PosVec.x, 0.0f, PosVec.z);
			//Position.x = follow->GetPosition().x;
			//Position.z = follow->GetPosition().z;
			if (use == true)
			{
				if (GetStop() == false)
				{
					if (Size.x <= SizeLimit) { Size.x += 0.07f / (follow==GetPlayer()?1.0f:GetSlowNum()); }
					if (Size.y <= SizeLimit) { Size.y += 0.07f / (follow==GetPlayer()?1.0f:GetSlowNum()); }
					if (Size.z <= SizeLimit) { Size.z += 0.07f / (follow==GetPlayer()?1.0f:GetSlowNum()); }

					//MoveSpeed.y = MoveSpeed.y / GetSlowNum();
					Position.y += FloatSpeed.y / (follow == GetPlayer()?1.0f:GetSlowNum());
				}
				else if (GetStop() == true && follow == GetPlayer() && GetPlayer()->death == false)
				{
					if (Size.x <= SizeLimit) { Size.x += 0.07f / (follow==GetPlayer()?1.0f:GetSlowNum()); }
					if (Size.y <= SizeLimit) { Size.y += 0.07f / (follow==GetPlayer()?1.0f:GetSlowNum()); }
					if (Size.z <= SizeLimit) { Size.z += 0.07f / (follow==GetPlayer()?1.0f:GetSlowNum()); }

					//MoveSpeed.y = MoveSpeed.y / GetSlowNum();
					Position.y += FloatSpeed.y / (follow == GetPlayer() ? 1.0f : GetSlowNum());
				}
				//if (Position.y > LimitY) { Position.y = LimitY; }
				if (Position.y <= LimitY) { Counter = 0; use = false; }
			}
			else if (use == false)
			{
				Counter++;
				if (Counter % 10 == 0)
				{
					Counter = 0;
					use = true;
					Size = SizeBackUp;
					Position.y = PositionY;
				}
			}
		}
	}
}



void SetFloatRing(OBJECT* obj, D3DXVECTOR3 size, float OffsetY, READ_MODEL model)
{
	int n = 0;
	for (int i = 0; i < FLOATRING_MAX; i++)
	{
		if (g_FloatRing[i].GetUse() == false && g_FloatRing[i].follow == nullptr)
		{
			n++;
			g_FloatRing[i].Prepare();
			g_FloatRing[i].follow = obj;
			g_FloatRing[i].SetSizeW(size);
			g_FloatRing[i].SetY = OffsetY;
			g_FloatRing[i].SetModelPointer(GetReadModel(model));

			g_FloatRing[i].OffsetY = 0.5f;
			g_FloatRing[i].PositionY = obj->GetPosition().y - obj->GetSize().y / 2 - g_FloatRing[i].SetY;
			g_FloatRing[i].LimitY = g_FloatRing[i].PositionY - g_FloatRing[i].OffsetY;

			if (n == 1) 
			{
				g_FloatRing[i].followDelay = 0.2f;
				g_FloatRing[i].SetPosition(D3DXVECTOR3(obj->GetPosition().x, g_FloatRing[i].PositionY, obj->GetPosition().z)); 
			}
			else if (n == 2)
			{ 
				g_FloatRing[i].followDelay = 0.3f;
				g_FloatRing[i].SetPosition(D3DXVECTOR3(obj->GetPosition().x, g_FloatRing[i].LimitY, obj->GetPosition().z)); 
			}

			g_FloatRing[i].SetUse(true);

			if (n >= 2) { break; }
		}
	}
}

HRESULT InitFloatRing()
{
	for (int i = 0; i < FLOATRING_MAX; i++)
	{
		g_FloatRing[i].Prepare();
	}
	return S_OK;
}

void UnInitFloatRing()
{
	for (int i = 0; i < FLOATRING_MAX; i++)
	{
		g_FloatRing[i].UnInitialize();
	}
}

void UpdateFloatRing()
{
	for (int i = 0; i < FLOATRING_MAX; i++)
	{
		g_FloatRing[i].Update();
	}
}

void DrawFloatRing()
{
	for (int i = 0; i < FLOATRING_MAX; i++)
	{
		g_FloatRing[i].Draw();
	}
}

FLOATRING * GetFloatRing()
{
	return &g_FloatRing[0];
}
