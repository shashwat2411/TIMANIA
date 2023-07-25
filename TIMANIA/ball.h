#pragma once
#include "object.h"

#define BALL_MAX 6

enum BALL_TYPE
{
	HEALTH,
	EXP,

	BALL_TYPE_MAX
};

class BALL :public OBJECT
{
public:
	BALL_TYPE Type;
	D3DXVECTOR3 SizeBackUp;

public:

	void Prepare() override;
	void Update() override;

	void PrepareType(BALL_TYPE type);
};

HRESULT InitBall();
void UnInitBall();
void UpdateBall();
void DrawBall();
BALL* GetBall();
void SetBall(D3DXVECTOR3 pos, BALL_TYPE type);