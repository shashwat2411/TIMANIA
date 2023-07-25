//=============================================================================
//
// ポリゴン表示処理 [polygon.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "inputx.h"
#include "camera.h"
#include "keyboard.h"
#include "mouse.h"
#include "model.h"

#include "object.h"



//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
bool keyboard = true;
bool mute = false;

//=============================================================================
// 初期化処理
//=============================================================================
void OBJECT::Initialize()
{
	Shadow.Init();
	Shadow.SetScaling(1.0f);
	//行列を単位行列で初期化
	D3DXMatrixIdentity(&mtxWorld);
	D3DXMatrixIdentity(&TranslationMatrix);
	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixIdentity(&ScalingMatrix);

	pModel = nullptr;

	Position = D3DXVECTOR3(0.0f, Y_AXIS, 0.0f);
	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scaling = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	CollisionSize = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	RotationDirection = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	MoveSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	MoveSpeedBackUp = MoveSpeed;

	ZeroMemory(&Material, sizeof(Material));
	Material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	D3DXMatrixScaling(&ScalingMatrix, Size.x * Scaling.x, Size.y * Scaling.y, Size.z * Scaling.z);
	D3DXMatrixRotationYawPitchRoll(&RotationMatrix, D3DXToRadian(Rotation.y), D3DXToRadian(Rotation.x), D3DXToRadian(Rotation.z));
	D3DXMatrixTranslation(&TranslationMatrix, Position.x, Position.y, Position.z);

	D3DXMatrixMultiply(&mtxWorld, &ScalingMatrix, &RotationMatrix);	//World = Scaling * Rotation
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &TranslationMatrix);//World = World * Translation

	use = false;
	Gravity = false;
	damage = false;
	black = true;
	Counter = 0;
	DamageCounter = 0;
	Speed = 0.0f;

}

//=============================================================================
// 終了処理
//=============================================================================
void OBJECT::UnInitialize()
{
	Shadow.UnInit();
	//UnloadModel(&Model);
	pModel = nullptr;
}

//=============================================================================
// 描画処理
//=============================================================================
void OBJECT::Draw()
{
	SetCamera();
	if (use == true)
	{
		//Shadow.Draw();
		//Position += (MoveSpeed * (GetSlow() == true ? SLOW : 1.0f));
		//if (GetSlow() == false) { MoveSpeedBackUp = MoveSpeed; }
		//if (Gravity == true && GetStopAnything() == false) { Position.y -= GRAVITY; }

		if (GetSlow() == true) 
		{ 
			D3DXVECTOR3 temp;
			D3DXVec3Normalize(&temp, &MoveSpeed);
			//MoveSpeed = temp * Speed * SLOW;
		}

#ifdef GLOBAL_MOVEMENT
		{//グローバル座標で移動
			D3DXMatrixScaling(&ScalingMatrix, Size.x * Scaling.x, Size.y * Scaling.y, Size.z * Scaling.z);
			D3DXMatrixRotationYawPitchRoll(&RotationMatrix, D3DXToRadian(Rotation.y), D3DXToRadian(Rotation.x), D3DXToRadian(Rotation.z));
			D3DXMatrixTranslation(&TranslationMatrix, Position.x, Position.y, Position.z);

			//World行列作成
			{
				D3DXMatrixMultiply(&mtxWorld, &ScalingMatrix, &RotationMatrix);	//World = Scaling * Rotation
				D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &TranslationMatrix);//World = World * Translation
			}
		}
#else
		{//ローカル座標で移動
			D3DXMatrixScaling(&ScalingMatrix, Scaling.x, Scaling.y, Scaling.z);
			D3DXMatrixRotationYawPitchRoll(&RotationMatrix, D3DXToRadian(Rotation.y), D3DXToRadian(Rotation.x), D3DXToRadian(Rotation.z));
			D3DXMatrixTranslation(&TranslationMatrix, MoveSpeed.x, MoveSpeed.y, MoveSpeed.z);

			//World行列作成
			{
				//D3DXMatrixMultiply(&mtxWorld, &ScalingMatrix, &RotationMatrix);	//World = Scaling * Rotation
				//D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &TranslationMatrix);//World = World * Translation
			}

			//前回のWorld行列作成
			{
				D3DXMATRIX tempM;	//前回から変化した分だけの情報が入っている行列
				D3DXMatrixMultiply(&tempM, &ScalingMatrix, &RotationMatrix);	//World = Scaling * Rotation
				D3DXMatrixMultiply(&tempM, &tempM, &TranslationMatrix);//World = World * Translation
				//今回のWorld行列作成 :前回の動きの行列 (mtxWorld) を乗算する
				D3DXMatrixMultiply(&mtxWorld, &tempM, &mtxWorld);
			}
		}
#endif

		//World行列のセット
		SetWorldMatrix(&mtxWorld);

		//裏面カリングOFF
		//SetCullingMode(CULL_MODE_NONE);
		SetMaterial(&Material);

		if (damage == true)
		{
			if (black == true) { SetBlendState(BLEND_MODE_SUBTRACT); }
			if (black == false) { SetBlendState(BLEND_MODE_ADD); }
		}

		//描画
		DrawModel(pModel);

		//裏面カリングON
		//SetCullingMode(CULL_MODE_BACK);
		if (damage == true)
		{
			SetBlendState(BLEND_MODE_ALPHABLEND);
		}
	}
}

void OBJECT::Follow(OBJECT* object, float OffsetY)
{
	Position.x = object->GetPosition().x;
	Position.y -= object->GetPosition().y - OffsetY;
	Position.z = object->GetPosition().z;
}

void OBJECT::FaceTowards(OBJECT* object)
{
	float X = object->GetPosition().x;
	float Z = object->GetPosition().z;
	float corrector = 180;
	float height = (Z - Position.z);
	float base = (X - Position.x);

	if (object->GetPosition().z < Position.z) { corrector = 180; }
	else { corrector = 0; }

	Rotation.y = (D3DXToDegree(atanf(base / height))) + corrector;
}

void OBJECT::FaceTowards(D3DXVECTOR2 Coordinates)
{
	float X = Coordinates.x;
	float Z = Coordinates.y;
	float corrector = 180;
	float height = (Z - Position.z);
	float base = (X -   Position.x);

	if (Coordinates.y < 0) { corrector = 180; }
	else { corrector = 0; }

	Rotation.y = (D3DXToDegree(atanf(base / height))) + corrector;
}

D3DXVECTOR3 OBJECT::MoveTowardsR(OBJECT* object)
{
	D3DXVECTOR3 Returner = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3	Distance = object->GetPosition() - Position;
	D3DXVec3Normalize(&Distance, &Distance);

	Returner.x = Distance.x * Speed;
	Returner.z = Distance.z * Speed;

	return Returner;
}

void OBJECT::MoveTowards(OBJECT* object)
{
	D3DXVECTOR3	Distance = object->GetPosition() - Position;
	D3DXVec3Normalize(&Distance, &Distance);

	MoveSpeed.x = Distance.x * Speed;
	MoveSpeed.z = Distance.z * Speed;
}

D3DXVECTOR3 OBJECT::MoveInDirection()
{
	D3DXVECTOR3 mov = D3DXVECTOR3(RotationMatrix._31, RotationMatrix._32, RotationMatrix._33);
	D3DXVec3Normalize(&mov, &mov);
	return mov;
}

D3DXVECTOR3 OBJECT::MoveInDirection(float OffsetY)
{
	D3DXVECTOR3 mov = D3DXVECTOR3(RotationMatrix._31, RotationMatrix._32+D3DXToRadian(OffsetY), RotationMatrix._33);
	D3DXVec3Normalize(&mov, &mov);
	return mov;
}

void OBJECT::FaceInDirection()
{
	float X = 0.0f;
	float Z = 1.0f;
	float corrector = 180;
	float height = MoveSpeed.z;//(Z - Position.z);
	float base = MoveSpeed.x;//(X - Position.x);

	if (height < 0.0f) { corrector = 180; }
	else { corrector = 0; }

	Rotation.y = (D3DXToDegree(atanf(base / height))) + corrector;
}

void OBJECT::MoveSpeedNotSet()
{
	if (GetSlow() == true || GetSlowCoolDown() == true)
	{
		MoveSpeed = MoveSpeedBackUp;
	}
}

float OBJECT::DistanceFrom(OBJECT* obj)
{
	D3DXVECTOR3 dist = obj->GetPosition() - Position;		//双法の中心同士をつなぐベクトル
	float length = D3DXVec3Length(&dist);	//ベクトルの長さを計算
	
	return length;
}

float OBJECT::SoundDistance(OBJECT* obj)
{
	float distance = DistanceFrom(obj);
	float offset = (SOUND_DISTANCE - distance + 5.0f) / SOUND_DISTANCE;

	return offset;
}

int GetSlowNum()
{
	float num;
	int returner;

	if (GetSlow()) { num = (SLOW*10.0f); }
	else { num = 1.0f; }

	returner = (int)num;
	return returner;
}

void SetKeyBoardBool(bool value) { keyboard = value; }
void SetMuteBool(bool value) { mute = value; }

bool GetKeyBoardBool() { return keyboard; }
bool GetMuteBool() { return mute; }