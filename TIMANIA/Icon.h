#pragma once

#include "Text.h"

class ICON :public TEXT
{
private:

public:
	D3DXVECTOR2 SizeBackUp;

	void Prepare() override
	{
		Initialize();

		Offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Size = D3DXVECTOR2(0.27f, 0.27f);
		SizeBackUp = Size;

		TextNo = LoadTexture((char*)"data/TEXTURE/bullet000.png");

		use = true;
	}

	void Update() override
	{
		if (use == true)
		{

		}
	}

	void Appear(float value)
	{
		if (Color.a <= 1.0f) { Color.a += value; }
	}

};


