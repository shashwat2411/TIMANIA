#include "SelectStage.h"
#include "fade.h"
#include "Text.h"
#include "camera.h"
#include "Dome.h"
#include "SoundReader.h"

#define ROTATE_SPEED 0.06f

DOME BackgroundSelect;
DOME StageOptions[3];
TEXT DifficultyText[3];
TEXT ReturnSelect;
bool change;
int changeTo;
TEXT* testS;
CAMERA* g_camera;

int SelectTimer = 0;

int chosenSelect = 3;
int finalChosenSelect = chosenSelect;
D3DXVECTOR3 normal = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
D3DXVECTOR3 selected = D3DXVECTOR3(1.2f, 1.2f, 1.2f);

D3DXVECTOR3 selectedPosition = D3DXVECTOR3(0.0f, -0.5f, -1.5f);
D3DXVECTOR3 normalPosition[3];

void	InitSelectStage()		//	ステージ選択初期化
{
	SetCameraATDelay(D3DXVECTOR3(0.0f, 4.0f, 0.0f));
	GetCamera()->pos = D3DXVECTOR3(0.0f, -0.5f, -10.0f);

	g_camera = GetCamera();
	SelectTimer = 0;

	g_camera->fov = 60.0f;
	//BackgroundSelect.SetText(LoadTexture((char*)"data/TEXTURE/selectBackground.jpg"), D3DXVECTOR3(0.0f, 0.5f, UI_Z * 10), D3DXVECTOR2(6.5f, 3.65f), true, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));		//Background
	BackgroundSelect.SetDome(4, D3DXVECTOR3(0.0f, 450.0f - Y_AXIS, 0.0f));
	BackgroundSelect.GenerateRandomRotation(true, true, true, 3);

	//StageOptions[0].SetDome(LoadTexture((char*)"data/MODEL/Square1.jpg"), D3DXVECTOR3(-1.2f, 0.5f, UI_Z), D3DXVECTOR2(1.0f, 1.0f), true, D3DXVECTOR2(7.0f, 7.0f));		//Stage 1
	//StageOptions[1].SetDome(LoadTexture((char*)"data/MODEL/Square2.png"), D3DXVECTOR3(0.0f, 0.5f, UI_Z), D3DXVECTOR2(1.0f, 1.0f), true, D3DXVECTOR2(5.0f, 5.0f));		//Stage 2
	//StageOptions[2].SetDome(LoadTexture((char*)"data/MODEL/Square3.jpg"), D3DXVECTOR3(1.2f, 0.5f, UI_Z), D3DXVECTOR2(1.0f, 1.0f), true, D3DXVECTOR2(2.0f, 2.0f));		//Stage 3

	StageOptions[0].SetDome(10, D3DXVECTOR3(-1.1f, 0.0f, -7.6f), D3DXVECTOR3(0.01f, 0.01f, 0.01f));		//Stage 1
	StageOptions[1].SetDome(11, D3DXVECTOR3( 0.0f, 0.0f, -7.6f), D3DXVECTOR3(0.01f, 0.01f, 0.01f));		//Stage 2
	StageOptions[2].SetDome(12, D3DXVECTOR3( 1.1f, 0.0f, -7.6f), D3DXVECTOR3(0.01f, 0.01f, 0.01f));		//Stage 3

	normalPosition[0] = StageOptions[0].GetPosition();
	normalPosition[1] = StageOptions[1].GetPosition();
	normalPosition[2] = StageOptions[2].GetPosition();

	DifficultyText[0].SetText(LoadTexture((char*)"data/TEXTURE/easy.png"), D3DXVECTOR3(-1.04f, 0.6f, UI_Z),	D3DXVECTOR2(0.8f, 0.16f), true);		//Stage 1
	DifficultyText[1].SetText(LoadTexture((char*)"data/TEXTURE/medium.png"), D3DXVECTOR3(0.0f, 0.6f, UI_Z), D3DXVECTOR2(0.8f, 0.16f), true);		//Stage 2
	DifficultyText[2].SetText(LoadTexture((char*)"data/TEXTURE/hard.png"), D3DXVECTOR3(1.04f, 0.6f, UI_Z),	D3DXVECTOR2(0.8f, 0.16f), true);		//Stage 3

	//ReturnSelect.SetText(LoadTexture((char*)"data/TEXTURE/backSpace.png"), D3DXVECTOR3(1.6f, 1.5f, UI_Z), D3DXVECTOR2(0.65f, 0.2f), true, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	change = false;
	changeTo = 0;
	chosenSelect = finalChosenSelect;

	SetFade(FADEIN);

	PlayReadSound(BGM_SELECT, BGM);

	testS = &DifficultyText[0];
}

void	UnInitSelectStage()	//	ステージ選択終了処理
{
	DifficultyText[0].UnInitialize();
	DifficultyText[1].UnInitialize();
	DifficultyText[2].UnInitialize();

	StageOptions[0].UnInitialize();
	StageOptions[1].UnInitialize();
	StageOptions[2].UnInitialize();

	//ReturnSelect.UnInitialize();

	BackgroundSelect.UnInitialize();
}

void	UpdateSelectStage()	//	ステージ選択更新処理
{
	if (SelectTimer <= 60) { SelectTimer++; }

	SetCameraATDelay(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//BackgroundSelect.Update();

	//if (chosenSelect == 0) { StageOptions[0].SetRotation(D3DXVECTOR3(0.0f, StageOptions[0].GetRotation().y + ROTATE_SPEED, 0.0f)); }
	//if (chosenSelect == 1) { StageOptions[1].SetRotation(D3DXVECTOR3(StageOptions[1].GetRotation().x - ROTATE_SPEED, 0.0f, 0.0f)); }
	//if (chosenSelect == 2) { StageOptions[2].SetRotation(D3DXVECTOR3(0.0f, StageOptions[2].GetRotation().y - ROTATE_SPEED, 0.0f)); }

	StageOptions[0].SetPosition(normalPosition[0]);
	StageOptions[1].SetPosition(normalPosition[1]);
	StageOptions[2].SetPosition(normalPosition[2]);

	StageOptions[0].SetSize(normal);
	StageOptions[1].SetSize(normal);
	StageOptions[2].SetSize(normal);

	DifficultyText[0].Size = DifficultyText[0].SizeBackUp;
	DifficultyText[1].Size = DifficultyText[1].SizeBackUp;
	DifficultyText[2].Size = DifficultyText[2].SizeBackUp;

	DifficultyText[0].Color = D3DXCOLOR(0.4, 0.4f, 0.4f, 1.0f);
	DifficultyText[1].Color = D3DXCOLOR(0.4, 0.4f, 0.4f, 1.0f);
	DifficultyText[2].Color = D3DXCOLOR(0.4, 0.4f, 0.4f, 1.0f);

	//StageOptions[chosenSelect].SetRotation(D3DXVECTOR3(0.0f, StageOptions[chosenSelect].GetRotation().y + ROTATE_SPEED, 0.0f));
	StageOptions[chosenSelect].SetRotation(D3DXVECTOR3(StageOptions[chosenSelect].GetRotation().x - ROTATE_SPEED, 0.0f, 0.0f));
	StageOptions[chosenSelect].SetSize(selected);
	StageOptions[chosenSelect].SetPosition(normalPosition[chosenSelect] + selectedPosition);
	
	DifficultyText[chosenSelect].Size = DifficultyText[chosenSelect].SizeBackUp*1.5f;
	DifficultyText[chosenSelect].Color = WHITE;

	if ((GetKeyBoardBool() == true ? GetKeyboardTrigger(DIK_LEFT) : GetControllerTrigger("Left")) == true) { chosenSelect--; PlayReadSound(SE_SELECT_CHANGE, SE);}
	if ((GetKeyBoardBool() == true ? GetKeyboardTrigger(DIK_RIGHT) : GetControllerTrigger("Right")) == true) { chosenSelect++; PlayReadSound(SE_SELECT_CHANGE, SE);}

	if (chosenSelect < 0) { chosenSelect = 2; }
	if (chosenSelect > 2) { chosenSelect = 0; }

	if ((GetKeyBoardBool() == true ? GetKeyboardPress(DIK_SPACE) : GetControllerPress("A")) == true) { DifficultyText[chosenSelect].Size = DifficultyText[chosenSelect].SizeBackUp; StageOptions[chosenSelect].SetSize(normal);}
	if ((GetKeyBoardBool() == true ? GetKeyboardTrigger(DIK_SPACE) : GetControllerTrigger("A")) || (GetKeyBoardBool() == true ? GetKeyboardTrigger(DIK_BACKSPACE) : GetControllerTrigger("B")) == true && change == false)
	{
		change = true;
		if ((GetKeyBoardBool() == true ? GetKeyboardTrigger(DIK_SPACE) : GetControllerTrigger("A")) == true) { changeTo = 1; finalChosenSelect = chosenSelect; }
		else if ((GetKeyBoardBool() == true ? GetKeyboardTrigger(DIK_BACKSPACE) : GetControllerTrigger("B")) == true) { changeTo = -1; }
		PlayReadSound(SE_BUTTON_1, SE);
	}
	if (change == true && SelectTimer >= 60)
	{
		if (changeTo == 1){Fader(true, GAME);}
		else if (changeTo == -1){Fader(true, TITLE);}
	}

	if (change == true && (GetKeyBoardBool() == true ? GetKeyboardPress(DIK_SPACE) : GetControllerPress("A")) == false)
	{
		StopControlsBool(30);
	}

#ifdef DEBUG
	if (GetKeyboardPress(DIK_W))		{ g_camera->pos.y += 0.1f; }
	else if (GetKeyboardPress(DIK_S))	{ g_camera->pos.y -= 0.1f; }
	if (GetKeyboardPress(DIK_D))		{ g_camera->pos.x += 0.1f; }
	else if (GetKeyboardPress(DIK_A))	{ g_camera->pos.x -= 0.1f; }
	if (GetKeyboardPress(DIK_Q))		{ g_camera->pos.z += 0.1f; }
	else if (GetKeyboardPress(DIK_E))	{ g_camera->pos.z -= 0.1f; }
	//if (GetKeyboardPress(DIK_W))		{ testS->Offset.y -= 1; }
	//else if (GetKeyboardPress(DIK_S))	{ testS->Offset.y += 1; }
	//if (GetKeyboardPress(DIK_D))		{ testS->Offset.x += 1; }
	//else if (GetKeyboardPress(DIK_A))	{ testS->Offset.x -= 1; }

	char* str = GetDebugStr();
	//sprintf(&str[strlen(str)], "     CamX : %.2f, CamY : %.2f, CamZ : %.2f", GetCamera()->pos.x, GetCamera()->pos.y, GetCamera()->pos.z);
	sprintf(&str[strlen(str)], "     TestX : %.2f, TestY : %.2f, TestZ : %.2f", g_camera->pos.x, g_camera->pos.y, g_camera->pos.z);
	//sprintf(&str[strlen(str)], "     TestX : %.2f, TestY : %.2f", testS->Offset.x, testS->Offset.y);
	//sprintf(&str[strlen(str)], "     Color Alpha : %.2f", test->Color.a);
#endif
}

void	DrawSelectStage()		//	ステージ選択描画処理
{
	DrawDome(&BackgroundSelect);

	SetCullingMode(CULL_MODE_NONE);
	StageOptions[0].Draw();
	StageOptions[1].Draw();
	StageOptions[2].Draw();
	SetCullingMode(CULL_MODE_BACK);

	DifficultyText[0].Draw();
	DifficultyText[1].Draw();
	DifficultyText[2].Draw();

	//ReturnSelect.Draw();
}

int GetStage()
{
	return finalChosenSelect;
}