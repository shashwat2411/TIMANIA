#include "Dome.h"
#include "Player.h"


void DOME::Prepare()
{
	Initialize();

	if (GetStage() == 0)		{ pModel = GetReadModel(READ_MODEL::RM_SPHERE_1); }
	else if (GetStage() == 1)	{ pModel = GetReadModel(READ_MODEL::RM_SQUARE_2); }
	else if (GetStage() == 2)	{ pModel = GetReadModel(READ_MODEL::RM_SQUARE_3); }
	else if (GetStage() == 3)	{ pModel = GetReadModel(READ_MODEL::RM_SQUARE_4); }

	Shadow.SetUse(false);

	Offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Position = D3DXVECTOR3(GetPlayer()->GetPosition().x, /*400.0f-Y_AXIS*/GetPlayer()->GetPosition().y, GetPlayer()->GetPosition().z);
	Size = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	SizeBackUp = Size;
	//Size = D3DXVECTOR3(50.0f, 500.0f, 50.0f);
	CollisionSize = Size;
	Rotation.x = 180;

	X = false;
	Y = true;
	Z = false;

	SizeReduction = false;

	inGame = false;

	//Material.Diffuse.a = 0.2f;
	RotationVector = D3DXVECTOR3(0.0f, 0.03f, 0.0f);

	use = true;
}

void DOME::Update()
{
	if (use)
	{
		D3DXVECTOR3 ChangeSize;
		if (inGame == true && GetPlayer()->GetUse() == true)
		{
			float changer = (float)GetDifficultyIncreaser() * 0.15f;
			ChangeSize = SizeBackUp - SizeBackUp*changer;
			
			if (ChangeSize.x < Size.x) { SizeReduction = true; }
			if (SizeReduction == true)
			{
				Size -= D3DXVECTOR3(0.3f, 0.3f, 0.3f);
				if (Size.x < ChangeSize.x) { SizeReduction = false; }
			}
			CollisionSize = Size;

#ifdef DEBUG	// デバッグ情報を表示する
			char* str = GetDebugStr();
			//sprintf(&str[strlen(str)], "   Changer:%.2f   ChangeSize.x : %.2f    Size.x : %.2f", changer,ChangeSize.x, Size.x);
#endif

		}
		if (GetStopAnything() == false && inGame == false) { Rotation += (RotationVector / GetSlowNum()); }

	}
}

void DOME::DomePlayerFollow()
{
	Rotation.x += GetPlayer()->PlayerMoveSpeed.z;
	Rotation.z += GetPlayer()->PlayerMoveSpeed.x;

	Position.x = GetPlayer()->GetPosition().x + Offset.x;
	Position.z = GetPlayer()->GetPosition().z + Offset.x;
}

void DrawDome(DOME* dome)
{
	SetLightEnable(false);
	SetCullingMode(CULL_MODE_NONE);
	dome->Draw();
	SetCullingMode(CULL_MODE_BACK);
}