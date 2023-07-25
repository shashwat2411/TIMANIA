#include "InputController.h"

#include	<xinput.h>
#include	<Windows.h>
#include	"game.h"
#pragma comment(lib,"xinput.lib")

_XINPUT_STATE state;

bool Controls = true;
int ControlsBoolCounter = 0;
int Counter[14] = { 0 };
bool pressed[14] = { false };
bool trigger[14] = { false };

void InitXinput()
{
	Controls = true;
	ControlsBoolCounter = 0;

	for (int i = 0; i < 14; i++)
	{
		Counter[i] = 0;
		pressed[i] = false;
		trigger[i] = false;
	}
}

void UpdateXinput()
{
	XInputGetState(0, &state);

	if ((state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		state.Gamepad.sThumbLX = 0;
		state.Gamepad.sThumbLY = 0;
	}
	if ((state.Gamepad.sThumbRX <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
		state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
		(state.Gamepad.sThumbRY <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
			state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
	{
		state.Gamepad.sThumbRX = 0;
		state.Gamepad.sThumbRY = 0;
	}

	if (Controls == false)
	{
		ControlsBoolCounter--;
		if (ControlsBoolCounter <= 0)
		{
			ControlsBoolCounter = 0;
			Controls = true;
		}
	}

	if (Controls == true)
	{
		for (int i = 0; i < 14; i++)
		{
			WORD compare;
			bool *reference;
			int num;
			if (i == 0) { compare = XINPUT_GAMEPAD_X;					num = 0; }
			else if (i == 1) { compare = XINPUT_GAMEPAD_Y;				num = 1; }
			else if (i == 2) { compare = XINPUT_GAMEPAD_A;				num = 2; }
			else if (i == 3) { compare = XINPUT_GAMEPAD_B;				num = 3; }
			else if (i == 4) { compare = XINPUT_GAMEPAD_RIGHT_SHOULDER; num = 4; }
			else if (i == 5) { compare = XINPUT_GAMEPAD_LEFT_SHOULDER;	num = 5; }
			else if (i == 6) { compare = XINPUT_GAMEPAD_LEFT_THUMB;		num = 6; }
			else if (i == 7) { compare = XINPUT_GAMEPAD_LEFT_THUMB;		num = 7; }
			else if (i == 8) { compare = XINPUT_GAMEPAD_START;			num = 8; }
			else if (i == 9) { compare = XINPUT_GAMEPAD_BACK;			num = 9; }
			else if (i == 10) { compare = XINPUT_GAMEPAD_DPAD_UP;		num = 10; }
			else if (i == 11) { compare = XINPUT_GAMEPAD_DPAD_DOWN;		num = 11; }
			else if (i == 12) { compare = XINPUT_GAMEPAD_DPAD_RIGHT;	num = 12; }
			else if (i == 13) { compare = XINPUT_GAMEPAD_DPAD_LEFT;		num = 13; }
			else { compare = NULL; break; }

			if (state.Gamepad.wButtons == compare)
			{
				pressed[i] = true;

				Counter[i]++;
				if (Counter[i] >= 0 && Counter[num] < 2) { trigger[i] = true; }
				else { trigger[i] = false; }
			}
			else
			{
				pressed[i] = false;
				trigger[i] = false;
				Counter[num] = 0;
			}
		}
	}

#ifdef DEBUG
	char* str = GetDebugStr();
	sprintf(&str[strlen(str)], "     Controls : %d, Counter : %d", Controls, ControlsBoolCounter);
#endif
}

//=================================================================================================
//	入力取得関数
//=================================================================================================
//STICK
const	D3DXVECTOR2&	GetStickL()	//	左スティックの入力ベクトル取得
{
	/*if (GetKeyboardPress(DIK_RIGHT))	return	D3DXVECTOR2(1, 0);
	else if (GetKeyboardPress(DIK_LEFT))	return	D3DXVECTOR2(-1, 0);
	else return	D3DXVECTOR2(0, 0);*/

	return	D3DXVECTOR2((float)state.Gamepad.sThumbLX / 32768.0f,
		(float)state.Gamepad.sThumbLY / 32768.0f);
}
const	D3DXVECTOR2&	GetStickR()	//	右スティックの入力ベクトル取得
{
	return	D3DXVECTOR2((float)state.Gamepad.sThumbRX / 32768.0f,
		(float)state.Gamepad.sThumbRY / 32768.0f);
}

bool GetControllerPress(const char name[])
{
	int num;

	if      (name == "X")		{ num = 0; }
	else if (name == "Y")		{ num = 1; }
	else if (name == "A")		{ num = 2; }
	else if (name == "B")		{ num = 3; }
	else if (name == "RS")		{ num = 4; }
	else if (name == "LS")		{ num = 5; }
	else if (name == "RT")		{ num = 6; }
	else if (name == "LT")		{ num = 7; }
	else if (name == "Start")	{ num = 8; }
	else if (name == "Options") { num = 9; }
	else if (name == "Up")		{ num = 10; }
	else if (name == "Down")	{ num = 11; }
	else if (name == "Right")	{ num = 12; }
	else if (name == "Left")	{ num = 13; }
	else						{ num = -1; }

	return pressed[num];
}

bool GetControllerTrigger(const char name[])
{
	int num;

	if (name == "X") { num = 0; }
	else if (name == "Y") { num = 1; }
	else if (name == "A") { num = 2; }
	else if (name == "B") { num = 3; }
	else if (name == "RS") { num = 4; }
	else if (name == "LS") { num = 5; }
	else if (name == "RT") { num = 6; }
	else if (name == "LT") { num = 7; }
	else if (name == "Start") { num = 8; }
	else if (name == "Options") { num = 9; }
	else if (name == "Up") { num = 10; }
	else if (name == "Down") { num = 11; }
	else if (name == "Right") { num = 12; }
	else if (name == "Left") { num = 13; }
	else { num = -1; }

	return trigger[num];
}

void StopControlsBool(int frames)
{
	for (int i = 0; i < 14; i++)
	{
		pressed[i] = false;
		trigger[i] = false;
		Counter[i] = 0;
	}

	Controls = false;
	ControlsBoolCounter = frames;
}

bool GetControlsBool()
{
	return Controls;
}
