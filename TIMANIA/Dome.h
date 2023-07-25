#pragma once
#include "object.h"
#include <ctime>

class DOME :public OBJECT
{
public:
	bool inGame;
	D3DXVECTOR3 Offset;
	D3DXVECTOR3 SizeBackUp;
	bool SizeReduction;

private:
	bool X;
	bool Y;
	bool Z;
	D3DXVECTOR3 RotationVector;

public:

	void Prepare() override;
	void Update() override;

	void SetSize(D3DXVECTOR3 value) { Size = value; SizeBackUp = value; }

	void SetDome(int number)
	{
		Prepare();

		//if (number > 5) { number = 5; }
		//else if (number < 0) { number = 0; }

		if (number == 0) { pModel = GetReadModel(READ_MODEL::RM_SPHERE_1); }
		else if (number == 1)	{ pModel = GetReadModel(READ_MODEL::RM_SQUARE_1); }
		else if (number == 2)	{ pModel = GetReadModel(READ_MODEL::RM_SQUARE_2); }
		else if (number == 3)	{ pModel = GetReadModel(READ_MODEL::RM_SQUARE_3); }
		else if (number == 4)	{ pModel = GetReadModel(READ_MODEL::RM_SQUARE_4); }
		else if (number == 5)	{ pModel = GetReadModel(READ_MODEL::RM_SQUARE_5); }
		else if (number == 10) { pModel = GetReadModel(READ_MODEL::RM_DISPLAY_SQUARE_1); }
		else if (number == 11) { pModel = GetReadModel(READ_MODEL::RM_DISPLAY_SQUARE_2); }
		else if (number == 12) { pModel = GetReadModel(READ_MODEL::RM_DISPLAY_SQUARE_3); }
		else if (number == 21) { pModel = GetReadModel(READ_MODEL::RM_GRID_1); }
		else if (number == 22) { pModel = GetReadModel(READ_MODEL::RM_GRID_2); }
		else if (number == 23) { pModel = GetReadModel(READ_MODEL::RM_GRID_3); }
	}

	void SetDome(int number, D3DXVECTOR3 pos)
	{
		SetDome(number);

		Position = pos;
	}
	void SetDome(int number, D3DXVECTOR3 pos, D3DXVECTOR3 size)
	{
		SetDome(number);
		
		Position = pos;
		Size = size;
	}

	void GenerateRandomRotation(bool x, bool y, bool z, int limit)
	{
		float Vector[3];
		Vector[0] = ((float)(rand() % limit)) * 0.01f;
		Vector[1] = ((float)(rand() % limit)) * 0.01f;
		Vector[2] = ((float)(rand() % limit)) * 0.01f;
		//if (Vector[0] <= 0.0f) { Vector[0] += 0.01f; }
		if (Vector[1] <= 0.0f) { Vector[1] += 0.01f; }
		//if (Vector[2] <= 0.0f) { Vector[2] += 0.01f; }

		int direction[3];
		direction[0] = rand() % 2;
		direction[1] = rand() % 2;
		direction[2] = rand() % 2;
		if (direction[0] % 2 == 0) { Vector[0] *= -1; }
		if (direction[1] % 2 == 0) { Vector[1] *= -1; }
		if (direction[2] % 2 == 0) { Vector[2] *= -1; }

		if (x == true) { RotationVector.x = Vector[0]; }
		if (y == true) { RotationVector.y = Vector[1]; }
		if (z == true) { RotationVector.z = Vector[2]; }
	}

	void DomePlayerFollow();
};

void DrawDome(DOME* dome);
DOME* GetSkyDome();