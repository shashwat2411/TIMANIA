#pragma once
#include "object.h"

#define EXPLOSION_MAX 800
#define NORMAL_SET_NUMBER 8
#define EXPLOSION_SPEED 0.05f;

enum EXPLOSION_TYPE
{
	NORMAL,
	DAMAGE,

	EXPLOSION_TYPE_MAX
};

class EXPLOSION :public OBJECT
{
public:
	//bool blink;
	EXPLOSION_TYPE Type;
	bool stopper;

public:

	void Prepare() override;
	void Update() override;

};

void InitExplosion();
void UnInitExplosion();
void UpdateExplosion();
void DrawExplosion();

EXPLOSION* GetExplosion();
//void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 mov, EXPLOSION_TYPE type, float size, float volume);
void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 mov, EXPLOSION_TYPE type, float size, READ_SOUND num);