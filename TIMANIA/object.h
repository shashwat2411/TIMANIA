//=============================================================================
//
// 地面処理 [polygon.h]
// Author : 
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "model.h"
#include "ModelReader.h"
#include "SoundReader.h"
#include "shadow.h"

#define Y_AXIS 1.7f
#define SHADOW_ERROR -1.6f
#define GRAVITY 0.05f
#define SECONDS 60
#define SLOW 0.3f

#define DAMAGE_EFFECT_TIME 10

#define TIME_DIVIDER 10.0f
#define TIME_LIMIT 120
#define DIFFICULTY_INCREASER 20	

#define GLOBAL_MOVEMENT
//#define LOCAL_MOVEMENT

class OBJECT
{
protected:
	bool use;
	bool Gravity;
	bool damage;
	bool black;
	D3DXVECTOR3	Position;		// ポリゴンの位置
	D3DXVECTOR3	Rotation;		// ポリゴンの向き(回転)
	D3DXVECTOR3	Scaling;		// ポリゴンの大きさ(スケール)
	D3DXVECTOR3 Size;
	D3DXVECTOR3 CollisionSize;
	D3DXVECTOR3	Direction;		//移動方向

	D3DXVECTOR3 MoveSpeed;		//移動量
	D3DXVECTOR3 MoveSpeedBackUp;
	D3DXVECTOR3 RotationDirection;	//回転量

	DX11_MODEL Model;
	DX11_MODEL* pModel;

	D3DXCOLOR Color;

	MATERIAL Material;

	D3DXMATRIX mtxWorld;	// ワールドマトリックス
	D3DXMATRIX TranslationMatrix;
	D3DXMATRIX RotationMatrix;
	D3DXMATRIX ScalingMatrix;

	SHADOW Shadow;

	int ShadowIndex;
	int Counter;
	int DamageCounter;

	float Speed;

public:
	OBJECT() { Shadow.SetPosition(D3DXVECTOR3(Position.x, SHADOW_ERROR, Position.z)); }

	void SetUse(const bool value) { use = value; }
	void SetDamage(const bool value) { damage = value; }
	void SetLight(const bool value) { black = value; }
	void SetGravity(const bool value) { Gravity = value; }
	void SetModel(const DX11_MODEL* model) { Model = *model; }
	void SetModelPointer(DX11_MODEL* model) { pModel = model; }
	void SetMaterial(const MATERIAL* material) { Material = *material; }
	void SetPosition(const D3DXVECTOR3 value) { Position = value; }
	void SetMoveSpeed(const D3DXVECTOR3 value) { MoveSpeed = value; MoveSpeedBackUp = MoveSpeed; }
	void SetMoveSpeedBackUp(const D3DXVECTOR3 value) { MoveSpeedBackUp = value; }
	void SetDirection(const D3DXVECTOR3 value) { Direction = value; }
	void SetRotation(const D3DXVECTOR3 value) { Rotation = value; }
	void SetRotationDirection(const D3DXVECTOR3 value) { RotationDirection = value; }
	void SetSize(const D3DXVECTOR3 value) { Size = value; }
	void SetScaling(const D3DXVECTOR3 value) { Scaling = value; }
	void SetCollisionSize(const D3DXVECTOR3 value) { CollisionSize = value; }
	void SetColor(const D3DXCOLOR value) { Color = value; }
	void SetSpeed(const float value) { Speed = value; }
	void SetCounter(const int value) { Counter = value; }


	bool		GetUse()const { return use; }
	bool		GetDamage()const { return damage; }
	bool		GetGravity()const { return Gravity; }
	D3DXVECTOR3	GetPosition()const { return Position; }
	D3DXVECTOR3	GetMoveSpeed()const { return MoveSpeed; }
	D3DXVECTOR3	GetMoveSpeedBackUp()const { return MoveSpeedBackUp; }
	D3DXVECTOR3	GetDirection()const { return Direction; }
	D3DXVECTOR3	GetRotation()const { return Rotation; }
	D3DXVECTOR3	GetRotationDirection()const { return RotationDirection; }
	MATERIAL	GetMaterial() { return Material; }
	D3DXVECTOR3	GetScaling()const { return Scaling; }
	D3DXVECTOR3	GetSize()const { return Size; }
	D3DXVECTOR3	GetCollisionSize()const { return CollisionSize; }
	D3DXCOLOR	GetColor()const { return Color; }
	DX11_MODEL* GetModelPointer() { return pModel; }
	float		GetSpeed()const { return Speed; }
	int			GetCounter()const { return Counter; }

	void Initialize();
	void UnInitialize();
	void Draw();

	virtual void Update() = 0;
	virtual void Prepare() = 0;

	void Follow(OBJECT* object, float OffsetY);
	void FaceTowards(OBJECT* object);
	void FaceTowards(D3DXVECTOR2 Coordinates);
	D3DXVECTOR3 MoveTowardsR(OBJECT* object);
	void MoveTowards(OBJECT* object);
	D3DXVECTOR3 MoveInDirection();
	D3DXVECTOR3 MoveInDirection(float OffsetY);
	void FaceInDirection();
	float DistanceFrom(OBJECT* obj);
	float SoundDistance(OBJECT* obj);

	void MoveSpeedNotSet();


	virtual ~OBJECT() {}
};

#define ROTATION_SPEED 3
#define MOVE_SPEED 0.2

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

bool GetStop();
bool GetSlow();
bool GetPause();
bool GetSlowCoolDown();
bool GetStopAnything();
int GetSlowNum();
int GetStage();

void SetKeyBoardBool(bool value);
void SetMuteBool(bool value);

bool GetKeyBoardBool();
bool GetMuteBool();