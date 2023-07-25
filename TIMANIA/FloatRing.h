#pragma once
#include "object.h"

#define FLOATRING_MAX 300

class FLOATRING :public OBJECT
{
public:
	D3DXVECTOR3 SizeBackUp;
	D3DXVECTOR3 FloatSpeed;
	OBJECT* follow;
	float PositionY;
	float SetY;
	float LimitY;
	float SizeLimit;
	float OffsetY;
	float followDelay;

public:
	void SetFloatSpeed(const D3DXVECTOR3 value) { FloatSpeed = value; }
	const D3DXVECTOR3 GetFloatSpeed() { return FloatSpeed; }

	void SetSizeW(D3DXVECTOR3 value) { Size = value; SizeBackUp = value; }

	void Prepare() override;
	void Update() override;
};

HRESULT InitFloatRing();
void UnInitFloatRing();
void UpdateFloatRing();
void DrawFloatRing();
FLOATRING* GetFloatRing();

void SetFloatRing(OBJECT* obj, D3DXVECTOR3 size, float OffsetY, READ_MODEL model);