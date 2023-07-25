#include "Title.h"
#include "fade.h"
#include "Text.h"
#include "camera.h"
#include "inputx.h"
#include "Dome.h"
#include "SoundReader.h"

#define BACKGROUND_SIZE 2.35f
#define COLORCHANGE_SPEED 0.5f

TEXT BackgroundTitle;
TEXT Press;
TEXT Title;

DOME TitleDome;

TEXT Options[3];

UI* test;
int chosenTitle = 0;
float color[3] = { 0.0f };
bool switcher[3] = { false };
bool changeTitle = false;

void	InitTitle()		//	ステージ選択初期化
{
	chosenTitle = 0;
	color[0] = 0.0f;
	color[1] = 0.0f;
	color[2] = 0.0f;
	switcher[0] = false;
	switcher[1] = false;
	switcher[2] = false;
	changeTitle = false;

	SetCameraATDelay(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	GetCamera()->pos.y = 0.0f;
	GetCamera()->fov = VIEW_ANGLE;

	BackgroundTitle.SetText(LoadTexture((char*)"data/TEXTURE/titleGround.jpg"), D3DXVECTOR3(0.0f, 0.5f, UI_Z), D3DXVECTOR2(BACKGROUND_SIZE, BACKGROUND_SIZE), true, WHITE);		//Background
	Title.SetText(LoadTexture((char*)"data/TEXTURE/Timania.png"), D3DXVECTOR3(0.0f, 1.2f, UI_Z), D3DXVECTOR2(3.11f, 0.6f), true, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));		//Title
	Press.SetText(LoadTexture((char*)"data/TEXTURE/pressEnter.png"), D3DXVECTOR3(0.0f, 0.2f, UI_Z), D3DXVECTOR2(2.37f, 0.2f), true);		//Press button

	Options[0].SetText(LoadTexture((char*)"data/TEXTURE/play.png"), D3DXVECTOR3(0.0f, 0.5f, UI_Z), D3DXVECTOR2(0.9f, 0.3f), false,  D3DXCOLOR(1.0f, 1.0f, 1.0, ALPHA_LOWEST*0.9f));		//Play
	Options[1].SetText(LoadTexture((char*)"data/TEXTURE/characterSelect.png"), D3DXVECTOR3(0.0f, 0.1f, UI_Z), D3DXVECTOR2(2.05f, 0.3f), false,  D3DXCOLOR(1.0f, 1.0f, 1.0, ALPHA_LOWEST*0.9f));		//Tutorial
	Options[2].SetText(LoadTexture((char*)"data/TEXTURE/quit.png"), D3DXVECTOR3(0.0f, -0.3f, UI_Z), D3DXVECTOR2(0.9f, 0.3f), false, D3DXCOLOR(1.0f, 1.0f, 1.0, ALPHA_LOWEST*0.9f));		//Quit
	
	//TitleDome.Prepare();
	TitleDome.SetDome(GetStage()+1, D3DXVECTOR3(0.0f, 450.0f - Y_AXIS, 0.0f));
	TitleDome.GenerateRandomRotation(true, true, true, 3);


	SetFade(FADEIN);

	test = &Title;

	PlayReadSound(BGM_TITLE, BGM);
}

void	UnInitTitle()	//	ステージ選択終了処理
{
	Press.UnInitialize();
	Title.UnInitialize();
	Options[0].UnInitialize();
	Options[1].UnInitialize();
	Options[2].UnInitialize();
	BackgroundTitle.UnInitialize();
	TitleDome.UnInitialize();
}

void	UpdateTitle()	//	ステージ選択更新処理
{
	SetCameraAT(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	TitleDome.Update();

	if (switcher[0] == false) { color[0] -= 0.01f * COLORCHANGE_SPEED; if (color[0] <= 0.0f) { switcher[0] = true; } }
	else if (switcher[0] == true) { color[0] += 0.01f * COLORCHANGE_SPEED; if (color[0] >= 1.0f) { switcher[0] = false; } }

	if (switcher[1] == false) { color[1] -= 0.02f * COLORCHANGE_SPEED; if (color[1] <= 0.0f) { switcher[1] = true; } }
	else if (switcher[1] == true) { color[1] += 0.03f * COLORCHANGE_SPEED; if (color[1] >= 1.0f) { switcher[1] = false; } }

	if (switcher[2] == false) { color[2] -= 0.04f * COLORCHANGE_SPEED; if (color[2] <= 0.0f) { switcher[2] = true; } }
	else if (switcher[2] == true) { color[2] += 0.05f * COLORCHANGE_SPEED; if (color[2] >= 1.0f) { switcher[2] = false; } }

	Title.Color = D3DXCOLOR(color[0], color[1], color[2], 1.0f);

	Options[0].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, Options[0].Color.a);
	Options[1].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, Options[1].Color.a);
	Options[2].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, Options[2].Color.a);

	Options[0].Size = Options[0].SizeBackUp;
	Options[1].Size = Options[1].SizeBackUp;
	Options[2].Size = Options[2].SizeBackUp;

	Options[chosenTitle].Color = D3DXCOLOR(color[2], color[0], color[1], Options[chosenTitle].Color.a);
	Options[chosenTitle].Size = Options[chosenTitle].SizeBackUp*1.2f;

	if (Press.use == false)
	{
		if ((GetKeyBoardBool() == true ? GetKeyboardTrigger(DIK_UP) : GetControllerTrigger("Up")) == true) { chosenTitle--; PlayReadSound(SE_SELECT_CHANGE, SE); }
		if ((GetKeyBoardBool() == true ? GetKeyboardTrigger(DIK_DOWN) : GetControllerTrigger("Down")) == true) { chosenTitle++; PlayReadSound(SE_SELECT_CHANGE, SE); }
	}

	if (chosenTitle < 0) { chosenTitle = 2; }
	if (chosenTitle > 2) { chosenTitle = 0; }

	if ((GetKeyBoardBool() == true ? GetKeyboardPress(DIK_SPACE) : GetControllerPress("A")) == true && Press.use == false) { Options[chosenTitle].Size = Options[chosenTitle].SizeBackUp; changeTitle = true; }
	if (chosenTitle == 0 && Press.use == false) { Fader((GetKeyBoardBool() == true ? GetKeyboardTrigger(DIK_SPACE) : GetControllerTrigger("A")), SELECT); }
	if (chosenTitle == 1 && Press.use == false) { Fader((GetKeyBoardBool() == true ? GetKeyboardTrigger(DIK_SPACE) : GetControllerTrigger("A")), CHARACTER); }
	if (chosenTitle == 2 && Press.use == false) { if ((GetKeyBoardBool() == true ? GetKeyboardTrigger(DIK_SPACE) : GetControllerTrigger("A")) == true) { exit(999); } }

	if ((GetKeyBoardBool() == true ? GetKeyboardTrigger(DIK_SPACE) : GetControllerTrigger("A")) == true && Press.use == false) { PlayReadSound(SE_BUTTON_1, SE); }
	if ((GetKeyBoardBool() == true ? GetKeyboardTrigger(DIK_SPACE) : GetControllerTrigger("A")) == true && Press.use == true) { PlayReadSound(SE_BUTTON_2, SE); }

	if (Press.use == false && changeTitle == true && (GetKeyBoardBool() == true ? GetKeyboardPress(DIK_SPACE) : GetControllerPress("A")) == false)
	{
		StopControlsBool(30);
	}
	//Press Button
	{
		if (Press.use == true) { Press.Blink(0.005f); }
		if ((GetKeyBoardBool() == true ? GetKeyboardTrigger(DIK_SPACE) : GetControllerTrigger("A")) == true) { if (Press.use == true) { StopControlsBool(20); }Press.use = false; for (int i = 0; i < 3; i++) { Options[i].use = true; } }

		for (int i = 0; i < 3; i++) { if (Options[i].use == true) { Options[i].Appear(0.01f); } }
	}

#ifdef DEBUG
	if (GetKeyboardPress(DIK_W)) { test->Offset.y += 0.1f; }
	else if (GetKeyboardPress(DIK_S)) { test->Offset.y -= 0.1f; }
	if (GetKeyboardPress(DIK_D)) { test->Offset.x += 0.1f; }
	else if (GetKeyboardPress(DIK_A)) { test->Offset.x -= 0.1f; }

	char* str = GetDebugStr();
	//sprintf(&str[strlen(str)], "     CamX : %.2f, CamY : %.2f, CamZ : %.2f", GetCamera()->pos.x, GetCamera()->pos.y, GetCamera()->pos.z);
	sprintf(&str[strlen(str)], "     TestX : %.2f, TestY : %.2f", test->Offset.x, test->Offset.y);
	//sprintf(&str[strlen(str)], "     Color Alpha : %.2f", test->Color.a);

	//bool a = (IsButtonPressed(0, BUTTON_A) || GetKeyboardTrigger(DIK_SPACE));
	//sprintf(&str[strlen(str)], "     A : %d", a);
#endif
}

void	DrawTitle()		//	ステージ選択描画処理
{
	DrawDome(&TitleDome);

	Press.Draw();
	Title.Draw();
	Options[0].Draw();
	Options[1].Draw();
	Options[2].Draw();
	//BackgroundTitle.Draw();
}
