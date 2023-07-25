#include "characterSelect.h"
#include "fade.h"
#include "Text.h"
#include "camera.h"
#include "Dome.h"
#include "player.h"
#include "SoundReader.h"

#define ROTATE_SPEED 0.06f

DOME BackgroundCharacterSelect;
PLAYER CharacterOptions[3];
TEXT Shade;
TEXT ReturnCharacter;
TEXT AttackText;
TEXT SpeedText;
TEXT AttackValue[3];
TEXT SpeedValue[3];
TEXT* test;
bool changeCharacter;
int changeCharacterTo;
int floatCounter;
float floatSpeed;
int CharacterSelectTimer = 0;

int chosenCharacterSelect = 0;
int finalSelection = chosenCharacterSelect;
D3DXVECTOR3 characterNormal = D3DXVECTOR3(0.1f, 0.1f, 0.1f);
D3DXVECTOR3 characterSelected = D3DXVECTOR3(0.12f, 0.12f, 0.12f);
float selectedZ = -7.5f;

void	InitCharacterSelect()		//	ステージ選択初期化
{
	SetCameraATDelay(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	GetCamera()->pos.y = 0.0f;

	CharacterSelectTimer = 0;

	//BackgroundCharacterSelect.SetText(LoadTexture((char*)"data/TEXTURE/selectBackground.jpg"), D3DXVECTOR3(0.0f, 0.5f, UI_Z * 10), D3DXVECTOR2(6.5f, 3.65f), true, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));		//Background
	BackgroundCharacterSelect.SetDome(5, D3DXVECTOR3(0.0f, 450.0f - Y_AXIS, 0.0f));

	//CharacterOptions[0].SetDome(LoadTexture((char*)"data/MODEL/Square1.jpg"), D3DXVECTOR3(-1.2f, 0.5f, UI_Z), D3DXVECTOR2(1.0f, 1.0f), true, D3DXVECTOR2(7.0f, 7.0f));		//Stage 1
	//CharacterOptions[1].SetDome(LoadTexture((char*)"data/MODEL/Square2.png"), D3DXVECTOR3(0.0f, 0.5f, UI_Z), D3DXVECTOR2(1.0f, 1.0f), true, D3DXVECTOR2(5.0f, 5.0f));		//Stage 2
	//CharacterOptions[2].SetDome(LoadTexture((char*)"data/MODEL/Square3.jpg"), D3DXVECTOR3(1.2f, 0.5f, UI_Z), D3DXVECTOR2(1.0f, 1.0f), true, D3DXVECTOR2(2.0f, 2.0f));		//Stage 3
	Shade.SetText(LoadTexture((char*)"data/TEXTURE/fade.png"), D3DXVECTOR3(0.0f, 0.3f, UI_Z * 4), D3DXVECTOR2(5.27f, 4.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, ALPHA_LOWEST*1.1f));

	CharacterOptions[0].Prepare();
	CharacterOptions[1].Prepare();
	CharacterOptions[2].Prepare();

	CharacterOptions[0].SetModelPointer(GetReadModel(READ_MODEL::RM_PLAYER_1));
	CharacterOptions[1].SetModelPointer(GetReadModel(READ_MODEL::RM_PLAYER_2));
	CharacterOptions[2].SetModelPointer(GetReadModel(READ_MODEL::RM_PLAYER_3));

	CharacterOptions[0].SetRotation(D3DXVECTOR3(0.0f, 190.0f, 0.0f));
	CharacterOptions[1].SetRotation(D3DXVECTOR3(0.0f, 180.0f, 0.0f));
	CharacterOptions[2].SetRotation(D3DXVECTOR3(0.0f, 170.0f, 0.0f));

	CharacterOptions[0].SetPosition(D3DXVECTOR3(-1.4f, 0.0f, -6.0f));
	CharacterOptions[1].SetPosition(D3DXVECTOR3(0.0f, 0.0f, -6.0f));
	CharacterOptions[2].SetPosition(D3DXVECTOR3(1.4f, 0.0f, -6.0f));

	ReturnCharacter.SetText(LoadTexture((char*)"data/TEXTURE/backSpace.png"), D3DXVECTOR3(1.6f, 1.5f, UI_Z), D3DXVECTOR2(0.65f, 0.2f), true, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	AttackText			.SetText(LoadTexture((char*)"data/TEXTURE/attack.png"),		D3DXVECTOR3(-1.4f , -0.35f, UI_Z),	D3DXVECTOR2(0.9f,  0.1f), true);
	SpeedText			.SetText(LoadTexture((char*)"data/TEXTURE/speed.png"),		D3DXVECTOR3(0.6f  , -0.35f, UI_Z),	D3DXVECTOR2(0.77f, 0.1f), true);
	AttackValue[0]		.SetText(LoadTexture((char*)"data/TEXTURE/normal.png"),		D3DXVECTOR3(-0.42f, -0.35f, UI_Z),  D3DXVECTOR2(0.75f, 0.1f), false, D3DXCOLOR(1.0f, 0.67f, 0.1f, 1.0f));
	AttackValue[1]		.SetText(LoadTexture((char*)"data/TEXTURE/strong.png"),		D3DXVECTOR3(-0.42f, -0.35f, UI_Z),  D3DXVECTOR2(0.75f, 0.1f), false, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	AttackValue[2]		.SetText(LoadTexture((char*)"data/TEXTURE/weak.png"),		D3DXVECTOR3(-0.42f, -0.35f, UI_Z),  D3DXVECTOR2(0.49f, 0.1f), false, D3DXCOLOR(0.8f, 0.4f, 1.0f, 1.0f));
	SpeedValue[0]		.SetText(LoadTexture((char*)"data/TEXTURE/normal.png"),		D3DXVECTOR3(1.45f , -0.35f, UI_Z),  D3DXVECTOR2(0.75f, 0.1f), false, D3DXCOLOR(1.0f, 0.67f, 0.1f, 1.0f));
	SpeedValue[1]		.SetText(LoadTexture((char*)"data/TEXTURE/slowText.png"),	D3DXVECTOR3(1.45f , -0.35f, UI_Z),  D3DXVECTOR2(0.49f, 0.1f), false, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	SpeedValue[2]		.SetText(LoadTexture((char*)"data/TEXTURE/fast.png"),		D3DXVECTOR3(1.45f , -0.35f, UI_Z),  D3DXVECTOR2(0.49f, 0.1f), false, D3DXCOLOR(0.8f, 0.4f, 1.0f, 1.0f));

	changeCharacter = false;
	changeCharacterTo = 0;
	floatCounter = 0;
	floatSpeed = 0.01f;
	chosenCharacterSelect = finalSelection;

	SetFade(FADEIN);

	PlayReadSound(BGM_CHARACTER, BGM);

	test = &AttackValue[0];
}

void	UnInitCharacterSelect()	//	ステージ選択終了処理
{
	ReturnCharacter.UnInitialize();

	AttackText.UnInitialize();
	SpeedText.UnInitialize();

	for (int i = 0; i < 3; i++)
	{
		AttackValue[i].UnInitialize();
		SpeedValue[i].UnInitialize();
		CharacterOptions[i].UnInitialize();
	}

	BackgroundCharacterSelect.UnInitialize();
}

void	UpdateCharacterSelect()	//	ステージ選択更新処理
{
	if (CharacterSelectTimer <= 60) { CharacterSelectTimer++; }
	SetCameraAT(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//BackgroundCharacterSelect.Update();

	floatCounter++;
	if (floatCounter % 30 == 0) { floatCounter = 0; floatSpeed *= -1; }

	if (chosenCharacterSelect == 0)
	{
		CharacterOptions[1].SetPosition(D3DXVECTOR3(CharacterOptions[1].GetPosition().x, 0.0f, -6.0f));
		CharacterOptions[2].SetPosition(D3DXVECTOR3(CharacterOptions[2].GetPosition().x, 0.0f, -6.0f));
	}
	else if (chosenCharacterSelect == 1)
	{
		CharacterOptions[0].SetPosition(D3DXVECTOR3(CharacterOptions[0].GetPosition().x, 0.0f, -6.0f));
		CharacterOptions[2].SetPosition(D3DXVECTOR3(CharacterOptions[2].GetPosition().x, 0.0f, -6.0f));
	}
	else if (chosenCharacterSelect == 2)
	{
		CharacterOptions[0].SetPosition(D3DXVECTOR3(CharacterOptions[0].GetPosition().x, 0.0f, -6.0f));
		CharacterOptions[1].SetPosition(D3DXVECTOR3(CharacterOptions[1].GetPosition().x, 0.0f, -6.0f));
	}

	for (int i = 0; i < 3; i++)
	{
		CharacterOptions[i].SetSize(characterNormal);

		AttackValue[i].use = false;
		SpeedValue[i].use = false;
	}

	CharacterOptions[chosenCharacterSelect].SetSize(characterSelected);
	CharacterOptions[chosenCharacterSelect].SetPosition(D3DXVECTOR3(CharacterOptions[chosenCharacterSelect].GetPosition().x, CharacterOptions[chosenCharacterSelect].GetPosition().y+floatSpeed, selectedZ));
	AttackValue[chosenCharacterSelect].use = true;
	SpeedValue[chosenCharacterSelect].use =  true;

	if ((GetKeyBoardBool() == true ? GetKeyboardTrigger(DIK_LEFT) : GetControllerTrigger("Left")) == true) { chosenCharacterSelect--; PlayReadSound(SE_SELECT_CHANGE, SE); floatSpeed = 0.01f; floatCounter = 0; }
	if ((GetKeyBoardBool() == true ? GetKeyboardTrigger(DIK_RIGHT) : GetControllerTrigger("Right")) == true) { chosenCharacterSelect++; PlayReadSound(SE_SELECT_CHANGE, SE); floatSpeed = 0.01f; floatCounter = 0; }

	if (chosenCharacterSelect < 0) { chosenCharacterSelect = 2; }
	if (chosenCharacterSelect > 2) { chosenCharacterSelect = 0; }

	if((GetKeyBoardBool() == true ? GetKeyboardPress(DIK_SPACE) : GetControllerPress("A"))){ CharacterOptions[chosenCharacterSelect].SetSize(characterNormal); }
	if (((GetKeyBoardBool() == true ? GetKeyboardTrigger(DIK_SPACE) : GetControllerTrigger("A")) || (GetKeyBoardBool() == true ? GetKeyboardTrigger(DIK_BACKSPACE) : GetControllerTrigger("B"))) && changeCharacter == false)
	{
		changeCharacter = true;
		if ((GetKeyBoardBool() == true ? GetKeyboardTrigger(DIK_SPACE) : GetControllerTrigger("A"))) { changeCharacterTo = 1; finalSelection = chosenCharacterSelect; }
		else if ((GetKeyBoardBool() == true ? GetKeyboardTrigger(DIK_BACKSPACE) : GetControllerTrigger("B"))) { changeCharacterTo = -1; }
		PlayReadSound(SE_BUTTON_1, SE);
	}
	if (changeCharacter == true && CharacterSelectTimer >= 60)
	{
		if (changeCharacterTo == 1) { Fader(true, TITLE); }
		else if (changeCharacterTo == -1) { Fader(true, TITLE); }
	}
	if (changeCharacter == true && (GetKeyBoardBool() == true ? GetKeyboardPress(DIK_SPACE) : GetControllerPress("A")) == false)
	{
		StopControlsBool(30);
	}

#ifdef DEBUG
	if (GetKeyboardPress(DIK_W)) { test->Offset.y += 0.01f; }
	else if (GetKeyboardPress(DIK_S)) { test->Offset.y -= 0.01f; }
	if (GetKeyboardPress(DIK_D)) { test->Offset.x += 0.01f; }
	else if (GetKeyboardPress(DIK_A)) { test->Offset.x -= 0.01f; }

	if (GetKeyboardPress(DIK_1)) { test = &SpeedValue[0]; }
	if (GetKeyboardPress(DIK_2)) { test = &SpeedValue[1]; }
	if (GetKeyboardPress(DIK_3)) { test = &SpeedValue[2]; }

	char* str = GetDebugStr();
	sprintf(&str[strlen(str)], "     TestX : %.2f, TestY : %.2f", test->Offset.x, test->Offset.y);
	//sprintf(&str[strlen(str)], "     BackPosition X : %.2f  BackPosition Y : %.2f", BackgroundCharacterSelect.Position.x, BackgroundCharacterSelect.Position.y);
#endif
}

void	DrawCharacterSelect()		//	ステージ選択描画処理
{
	DrawDome(&BackgroundCharacterSelect);

	CharacterOptions[0].Draw();
	CharacterOptions[1].Draw();
	CharacterOptions[2].Draw();

	//Shade.Draw();

	ReturnCharacter.Draw();

	AttackText.Draw();
	SpeedText.Draw();
	AttackValue[0].Draw();
	AttackValue[1].Draw();
	AttackValue[2].Draw();

	SpeedValue[0].Draw();
	SpeedValue[1].Draw();
	SpeedValue[2].Draw();
}

int GetChosenPlayer()
{
	return finalSelection;
}