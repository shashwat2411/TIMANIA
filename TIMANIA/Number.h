#pragma once
#include "Text.h"

class NUMBER :public TEXT
{
public:
	int index;

public:

	void Prepare() override
	{
		Initialize();

		index = 0;

		//animate = true;
		animationTimer = 0.0f;
		animationTimerMax = 10.0f;
		oneFrameTime = 0.2f;

		FrameWidth = 10;
		FrameHeight = 1;

		TextureSize.x = 1.0f / FrameWidth;
		TextureSize.y = 1.0f / FrameHeight;

		TextNo = LoadTexture((char*)"data/TEXTURE/number.png");
		use = true;
	}

	void Update() override
	{
		if (use == true)
		{
			//if (index < 0) { index = 0; }
			//if (index > 9) { index = 0; }
			animationOffset.x = (index) % FrameWidth;
		}
	}

	void SetNumber(int num)
	{
		index = num;
		animationOffset.x = (index) % FrameWidth;
	}

	void SetText(D3DXVECTOR3 offset, D3DXVECTOR2 size)
	{
		Prepare();
		Offset = offset;
		Size = size;
	}
	void SetText(D3DXVECTOR3 offset, D3DXVECTOR2 size, D3DXCOLOR color)
	{
		Prepare();
		Offset = offset;
		Size = size;
		Color = color;
	}
};

void InitializeTimer(D3DXVECTOR3 TimerPosition, D3DXVECTOR3 ScorePosition);
void UnInitializeTimer();
void UpdateTimer();
void DrawTimer();

void SetRemainingTime(int time);
int GetRemainingTime();
int GetScore();
void AddScore(int value);
int GetDifficultyIncreaser();