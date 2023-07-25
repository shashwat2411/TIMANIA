#include "Pointer.h"
#include "player.h"
#include "enemy.h"

POINTER g_Pointer[ENEMY_MAX];
ENEMY* enemy;

void POINTER::Prepare()
{
	Initialize();

	Shadow.SetScaling(0.3f);

	//if (GetChosenPlayer() == 0) { pModel = GetReadModel(READ_MODEL::RM_POINTER_1); }
	//else if (GetChosenPlayer() == 1) { pModel = GetReadModel(READ_MODEL::RM_POINTER_2); }
	//else if (GetChosenPlayer() == 2) { pModel = GetReadModel(READ_MODEL::RM_POINTER_3); }
	pModel = GetReadModel(READ_MODEL::RM_POINTER_YELLOW);
	flicker = 15;

	Size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	use = false;
	PointerMoveSpeed = D3DXVECTOR3(0.08f, 0.0f, 0.0f);
}

void POINTER::Update()
{
	Position = GetPlayer()->GetPosition();

	if (use == true)
	{
		Counter++;
		if (Counter % flicker == 0) { Counter = 0; PointerMoveSpeed.x *= -1.0f; }
		Position += PointerMoveSpeed;

	}
}


void SetPointer(D3DXVECTOR3 pos)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Pointer[i].GetUse() == false)
		{
			g_Pointer[i].SetPosition(pos);
			g_Pointer[i].SetUse(true);
			//if (g_Pointer[i].DistanceFrom(GetPlayer()) < SOUND_DISTANCE) { PlayReadSound(SE_ENEMY_BULLET_LAUNCH, SE, 0.1f*g_Pointer[i].SoundDistance(GetPlayer())); }
			break;
		}
	}
}

HRESULT InitPointer()
{
	enemy = GetEnemy();
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		g_Pointer[i].Prepare();
	}
	return S_OK;
}

void UnInitPointer()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		g_Pointer[i].UnInitialize();
	}
}

void UpdatePointer()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemy[i].GetUse() == true && GetPlayer()->GetUse() == true)
		{
			g_Pointer[i].SetUse(true);
		}
		else if (enemy[i].GetUse() == false || GetPlayer()->GetUse() == false)
		{
			g_Pointer[i].SetUse(false);
		}

		g_Pointer[i].flicker = (enemy[i].DistanceFrom(GetPlayer()) >= 50.0f ? 15 : ((int)enemy[i].DistanceFrom(GetPlayer()) / 5 + 4));
		g_Pointer[i].FaceTowards(&enemy[i]);
		g_Pointer[i].Update();
	}

#ifdef DEBUG	// デバッグ情報を表示する
	char* str = GetDebugStr();
	sprintf(&str[strlen(str)], "    flicker : %d", g_Pointer[0].flicker);
#endif
}

void DrawPointer()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		g_Pointer[i].Draw();
	}
}

POINTER * GetPointer()
{
	return &g_Pointer[0];
}
