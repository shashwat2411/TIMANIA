
#include "Result.h"
#include "fade.h"
#include "Text.h"
#include "Number.h"
#include "camera.h"
#include "SoundReader.h"
#include "object.h"
#include "enemy.h"

#define TIMER_X 0.0f

TEXT BackgroundResult;
TEXT Result;
NUMBER timerResult[3];
NUMBER scoreResult[3];
int timeNext = TIME_LIMIT;
int scoreNext = 0;
int wait = 0;

int chosenResult = 0;

void	InitResult()		//	ステージ選択初期化
{
	SetCameraATDelay(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	GetCamera()->pos.y = 0.0f;
	timeNext = GetRemainingTime();
	scoreNext = 0;
	wait = 0;

	BackgroundResult.SetText(LoadTexture((char*)"data/TEXTURE/resultBG.jpg"), D3DXVECTOR3(0.0f, 0.6f, UI_Z), D3DXVECTOR2(4.36f, 2.25f), true, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));		//Background
	if (GetEnemyNumber() > 0) { Result.SetText(LoadTexture((char*)"data/TEXTURE/gameover.png"), D3DXVECTOR3(0.0f, 1.2f, UI_Z), D3DXVECTOR2(2.68f, 0.4f), true, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)); }
	if (GetEnemyNumber() <= 0) { Result.SetText(LoadTexture((char*)"data/TEXTURE/youWin.png"), D3DXVECTOR3(0.0f, 1.2f, UI_Z), D3DXVECTOR2(1.91f, 0.4f), true, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)); }

	timerResult[0].SetText(D3DXVECTOR3(TIMER_X + 0.2f, 0.75f, UI_Z), D3DXVECTOR2(0.4f, 0.4f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	timerResult[1].SetText(D3DXVECTOR3(TIMER_X + 0.0f, 0.75f, UI_Z), D3DXVECTOR2(0.4f, 0.4f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	timerResult[2].SetText(D3DXVECTOR3(TIMER_X - 0.2f, 0.75f, UI_Z), D3DXVECTOR2(0.4f, 0.4f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	scoreResult[0].SetText(D3DXVECTOR3(TIMER_X + 0.2f, 0.3f, UI_Z), D3DXVECTOR2(0.4f, 0.4f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	scoreResult[1].SetText(D3DXVECTOR3(TIMER_X + 0.0f, 0.3f, UI_Z), D3DXVECTOR2(0.4f, 0.4f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	scoreResult[2].SetText(D3DXVECTOR3(TIMER_X - 0.2f, 0.3f, UI_Z), D3DXVECTOR2(0.4f, 0.4f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	SetFade(FADEIN);

	if (GetEnemyNumber() > 0) { PlayReadSound(SE_LOSE, SE); PlayReadSound(BGM_RESULT_LOSE, BGM);}
	if (GetEnemyNumber() <= 0) { /*PlayReadSound(SE_WIN, SE);*/ PlayReadSound(BGM_RESULT_WIN, BGM);}
}

void	UnInitResult()	//	ステージ選択終了処理
{
	Result.UnInitialize();

	timerResult[0].UnInitialize();
	timerResult[1].UnInitialize();
	timerResult[2].UnInitialize();

	scoreResult[0].UnInitialize();
	scoreResult[1].UnInitialize();
	scoreResult[2].UnInitialize();

	BackgroundResult.UnInitialize();
}

void	UpdateResult()	//	ステージ選択更新処理
{
	SetCameraAT(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	if (wait <= 60) { wait++; }
	if (wait >= 60)
	{
		if (timeNext > 0) { timeNext--; /*scoreNext++;*/ 		scoreNext += 5;		PlayReadSound(SE_SELECT_CHANGE, SE); }


		//if (scoreNext  ) { scoreNext++; }
	}

	timerResult[0].SetNumber(timeNext % 10);
	timerResult[1].SetNumber(timeNext % 100 / 10);
	timerResult[2].SetNumber(timeNext / 100);

	scoreResult[0].SetNumber(scoreNext % 10);
	scoreResult[1].SetNumber(scoreNext % 100 / 10);
	scoreResult[2].SetNumber(scoreNext / 100);

	if ((GetKeyBoardBool() == true ? GetKeyboardTrigger(DIK_SPACE) : GetControllerTrigger("A")) == true) { PlayReadSound(SE_BUTTON_1, SE); }
	Fader((GetKeyBoardBool() == true ? GetKeyboardTrigger(DIK_SPACE) : GetControllerTrigger("A")), TITLE);

#ifdef DEBUG	// デバッグ情報を表示する
	char* str = GetDebugStr();
	sprintf(&str[strlen(str)], "     Remaining Time : %d", GetRemainingTime());
#endif
}

void	DrawResult()		//	ステージ選択描画処理
{
	BackgroundResult.Draw();

	Result.Draw();
	
	timerResult[0].Draw();
	timerResult[1].Draw();
	timerResult[2].Draw();

	scoreResult[0].Draw();
	scoreResult[1].Draw();
	scoreResult[2].Draw();

	//enemyLeft[0].Draw();
	//enemyLeft[1].Draw();
}
