#include "Number.h"
#include "player.h"
#include "enemy.h"

NUMBER Seconds[3];
NUMBER ScoreNumber[3];
NUMBER RemainingEnemyNum[2];
int TimerCounter;
int Time = TIME_LIMIT + 1;
int Score = 0;
bool play = false;

#define NUMBER_SIZE 0.2f

void InitializeTimer(D3DXVECTOR3 TimerPosition, D3DXVECTOR3 ScorePosition)
{
	play = false;
	TimerCounter = -1;
	Time = TIME_LIMIT + 1;
	Seconds[0].SetText(D3DXVECTOR3(TimerPosition.x + 0.15f, TimerPosition.y, TimerPosition.z), D3DXVECTOR2(0.3f, 0.3f));
	Seconds[1].SetText(D3DXVECTOR3(TimerPosition.x + 0.0f, TimerPosition.y, TimerPosition.z), D3DXVECTOR2(0.3f, 0.3f));
	Seconds[2].SetText(D3DXVECTOR3(TimerPosition.x - 0.15f, TimerPosition.y, TimerPosition.z), D3DXVECTOR2(0.3f, 0.3f));

	ScoreNumber[0].SetText(D3DXVECTOR3(ScorePosition.x + NUMBER_SIZE / 2, ScorePosition.y, ScorePosition.z), D3DXVECTOR2(NUMBER_SIZE, NUMBER_SIZE));
	ScoreNumber[1].SetText(D3DXVECTOR3(ScorePosition.x + NUMBER_SIZE * 0, ScorePosition.y, ScorePosition.z), D3DXVECTOR2(NUMBER_SIZE, NUMBER_SIZE));
	ScoreNumber[2].SetText(D3DXVECTOR3(ScorePosition.x - NUMBER_SIZE / 2, ScorePosition.y, ScorePosition.z), D3DXVECTOR2(NUMBER_SIZE, NUMBER_SIZE));

	RemainingEnemyNum[0].SetText(D3DXVECTOR3(ScorePosition.x + NUMBER_SIZE / 4, ScorePosition.y, ScorePosition.z), D3DXVECTOR2(NUMBER_SIZE, NUMBER_SIZE));
	RemainingEnemyNum[1].SetText(D3DXVECTOR3(ScorePosition.x - NUMBER_SIZE / 4, ScorePosition.y, ScorePosition.z), D3DXVECTOR2(NUMBER_SIZE, NUMBER_SIZE));
}

void UnInitializeTimer()
{
	Seconds[0].UnInitialize();
	Seconds[1].UnInitialize();
	Seconds[2].UnInitialize();

	ScoreNumber[0].UnInitialize();
	ScoreNumber[1].UnInitialize();
	ScoreNumber[2].UnInitialize();

	RemainingEnemyNum[0].UnInitialize();
	RemainingEnemyNum[1].UnInitialize();
}

void UpdateTimer()
{
	if (GetStop() == false)
	{
		TimerCounter++;
		if (TimerCounter % (60 * GetSlowNum()) == 0)
		{
			if (Time > 0) { Time--; }
			if (Time < 11 && Time > 0) { PlayReadSound(SE_COUNTDOWN, SE); }

			Seconds[0].SetNumber(Time % 10);
			Seconds[1].SetNumber(Time % 100 / 10);
			Seconds[2].SetNumber(Time / 100);

			TimerCounter = 0;
		}

		ScoreNumber[0].SetNumber(Score % 10);
		ScoreNumber[1].SetNumber(Score % 100 / 10);
		ScoreNumber[2].SetNumber(Score / 100);

		RemainingEnemyNum[0].SetNumber(GetEnemyNumber() % 10);
		RemainingEnemyNum[1].SetNumber(GetEnemyNumber() % 100 / 10);

		if (GetEnemyNumber() == 0 && play == false) { PlayReadSound(SE_WIN, SE); play = true; }
	}
}

void DrawTimer()
{
	Seconds[0].Draw();
	Seconds[1].Draw();
	Seconds[2].Draw();

	//ScoreNumber[0].Draw();
	//ScoreNumber[1].Draw();
	//ScoreNumber[2].Draw();

	RemainingEnemyNum[0].Draw();
	RemainingEnemyNum[1].Draw();
}

void SetRemainingTime(int time) { Time = time; }
int GetRemainingTime() { return Time; }
int GetScore() { return Score; }
void AddScore(int value) { Score += value; }

int GetDifficultyIncreaser() 
{
	int value = (6 - (GetRemainingTime() / DIFFICULTY_INCREASER));
	if (value == 6) { value--; }
	return value; 
}