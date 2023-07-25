#include "Abilities.h"
#include "inputx.h"
#include "Number.h"
#include "Icon.h"
#include "SoundReader.h"
#include "player.h"


ABILITIES abilitiesBox[3];
NUMBER abilityNumber[3];
ICON AbilityIcon[LEVELUP::ABILITIES_MAX];
int chosen = 0;
bool Abilitypress[2] = { false };
bool decideAbility = false;

int random[3] = { 0 };
void InitializeAbilities()
{	
	decideAbility = false;
	Abilitypress[0] = false;
	Abilitypress[1] = false;
	chosen = 0;
	random[0] = 0;
	random[1] = 0;
	random[2] = 0;

	abilitiesBox[0].SetText(LoadTexture((char*)"data/TEXTURE/hp.png"), D3DXVECTOR3(-1.0f, -1.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	abilitiesBox[1].SetText(LoadTexture((char*)"data/TEXTURE/hp.png"), D3DXVECTOR3( 0.0f, -1.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	abilitiesBox[2].SetText(LoadTexture((char*)"data/TEXTURE/hp.png"), D3DXVECTOR3( 1.0f, -1.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));

#ifdef DEBUG
	abilityNumber[0].SetText(D3DXVECTOR3(-1.0f, -1.0f, 0.0f),D3DXVECTOR2(1.0f, 1.0f));
	abilityNumber[1].SetText(D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	abilityNumber[2].SetText(D3DXVECTOR3(1.0f, -1.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));

	abilityNumber[0].use = false;
	abilityNumber[1].use = false;
	abilityNumber[2].use = false;
#endif

	for (int i = 0; i < LEVELUP::ABILITIES_MAX; i++)
	{
		AbilityIcon[i].Prepare();
		AbilityIcon[i].Size = D3DXVECTOR2(0.8f, 0.8f);
		AbilityIcon[i].SizeBackUp = D3DXVECTOR2(0.8f, 0.8f);
		AbilityIcon[i].use = false;
	}

	AbilityIcon[LEVELUP::HP_UP].TextNo = LoadTexture((char*)"data/TEXTURE/Health_Up.png");
	AbilityIcon[LEVELUP::EXPERIENCE_UP].TextNo = LoadTexture((char*)"data/TEXTURE/XP_Up.png");
	AbilityIcon[LEVELUP::MOVEMENT_SPEED_UP].TextNo = LoadTexture((char*)"data/TEXTURE/Speed_Up.png");
	AbilityIcon[LEVELUP::ATTACK_COOLDOWN_DOWN].TextNo = LoadTexture((char*)"data/TEXTURE/Attack_CoolDown_Down.png");
	AbilityIcon[LEVELUP::ATTACK_RANGE_UP].TextNo = LoadTexture((char*)"data/TEXTURE/Attack_Range_Up.png");
	AbilityIcon[LEVELUP::ATTACK_KNOCKBACK_UP].TextNo = LoadTexture((char*)"data/TEXTURE/Attack_Knockback_Up.png");
	AbilityIcon[LEVELUP::STOP_COOLDOWN_DOWN].TextNo = LoadTexture((char*)"data/TEXTURE/Stop_CoolDown_Down.png");
	AbilityIcon[LEVELUP::SLOW_COOLDOWN_DOWN].TextNo = LoadTexture((char*)"data/TEXTURE/Slow_CoolDown_Down.png");
	AbilityIcon[LEVELUP::STOP_TIME_UP].TextNo = LoadTexture((char*)"data/TEXTURE/Stop_Time_Up.png");
	AbilityIcon[LEVELUP::SLOW_TIME_UP].TextNo = LoadTexture((char*)"data/TEXTURE/Slow_Time_Up.png");

}

void UnInitializeAbilities()
{
	abilitiesBox[0].UnInitialize();
	abilitiesBox[1].UnInitialize();
	abilitiesBox[2].UnInitialize();

#ifdef DEBUG
	abilityNumber[0].UnInitialize();
	abilityNumber[1].UnInitialize();
	abilityNumber[2].UnInitialize();
#endif

	for (int i = 0; i < LEVELUP::ABILITIES_MAX; i++)
	{
		AbilityIcon[i].UnInitialize();
	}
}

void UpdateAbilities()
{
	if (decideAbility == false)
	{
		while (decideAbility == false)
		{
			random[0] = (int)rand() % LEVELUP::ABILITIES_MAX;
			random[1] = (int)rand() % LEVELUP::ABILITIES_MAX;
			random[2] = (int)rand() % LEVELUP::ABILITIES_MAX;

			if (random[0] != random[1] && random[0] != random[2] && random[1] != random[2]) { decideAbility = true; }

			if (random[0] == random[1]) { random[1] = (int)rand() % LEVELUP::ABILITIES_MAX; }
			if (random[0] == random[2]) { random[1] = (int)rand() % LEVELUP::ABILITIES_MAX; }
			if (random[1] == random[2]) { random[2] = (int)rand() % LEVELUP::ABILITIES_MAX; }

		}

#ifdef DEBUG
		abilityNumber[0].SetNumber(random[0]);
		abilityNumber[1].SetNumber(random[1]);
		abilityNumber[2].SetNumber(random[2]);
#endif
		
		AbilityIcon[random[0]].Offset = D3DXVECTOR3(-0.8f,-0.75f + GAME_UI_ERROR, 0.0f);
		AbilityIcon[random[1]].Offset = D3DXVECTOR3(0.0f, -0.75f + GAME_UI_ERROR, 0.0f);
		AbilityIcon[random[2]].Offset = D3DXVECTOR3(0.8f, -0.75f + GAME_UI_ERROR, 0.0f);

		AbilityIcon[random[0]].use = true;
		AbilityIcon[random[1]].use = true;
		AbilityIcon[random[2]].use = true;

		AbilityIcon[random[0]].Color.a = ALPHA_LOWEST * 0.9f;
		AbilityIcon[random[1]].Color.a = ALPHA_LOWEST * 0.9f;
		AbilityIcon[random[2]].Color.a = ALPHA_LOWEST * 0.9f;
	}

	AbilityIcon[random[0]].Appear(0.03f);
	AbilityIcon[random[1]].Appear(0.03f);
	AbilityIcon[random[2]].Appear(0.03f);

	abilitiesBox[0].Appear(0.03f);
	abilitiesBox[1].Appear(0.03f);
	abilitiesBox[2].Appear(0.03f);

	if ((GetKeyBoardBool() == true? GetKeyboardTrigger(DIK_RIGHT): GetControllerTrigger("Right")) == true) { chosen++; Abilitypress[0] = false; PlayReadSound(SE_SELECT_CHANGE, SE);}
	if ((GetKeyBoardBool() == true ? GetKeyboardTrigger(DIK_LEFT) : GetControllerTrigger("Left")) == true) { chosen--; Abilitypress[1] = false; PlayReadSound(SE_SELECT_CHANGE, SE);}

	if ((GetKeyBoardBool() == true ? GetKeyboardTrigger(DIK_SPACE) : GetControllerTrigger("A")) == true)
	{ 


		decideAbility = false; 
		PlayReadSound(SE_BUTTON_1, SE);
	}

	if (chosen > 2) { chosen = 0; }
	else if (chosen < 0) { chosen = 2; }

	AbilityIcon[random[0]].Color = D3DXCOLOR(0.5f, 0.5f, 0.5f, AbilityIcon[random[0]].Color.a);
	AbilityIcon[random[1]].Color = D3DXCOLOR(0.5f, 0.5f, 0.5f, AbilityIcon[random[1]].Color.a);
	AbilityIcon[random[2]].Color = D3DXCOLOR(0.5f, 0.5f, 0.5f, AbilityIcon[random[2]].Color.a);

	AbilityIcon[random[0]].Size = AbilityIcon[0].SizeBackUp;
	AbilityIcon[random[1]].Size = AbilityIcon[1].SizeBackUp;
	AbilityIcon[random[2]].Size = AbilityIcon[2].SizeBackUp;

	AbilityIcon[random[chosen]].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, AbilityIcon[random[chosen]].Color.a);
	AbilityIcon[random[chosen]].Size = AbilityIcon[random[chosen]].SizeBackUp*1.2f;

	abilitiesBox[0].Update();
	abilitiesBox[1].Update();
	abilitiesBox[2].Update();

#ifdef DEBUG
	abilityNumber[0].Update();
	abilityNumber[1].Update();
	abilityNumber[2].Update();
#endif

	for (int i = 0; i < LEVELUP::ABILITIES_MAX; i++)
	{
		AbilityIcon[i].Update();
	}
}

void DrawAbilities()
{
#ifdef DEBUG
	abilityNumber[0].Draw();
	abilityNumber[1].Draw();
	abilityNumber[2].Draw();
#endif

	for (int i = 0; i < LEVELUP::ABILITIES_MAX; i++)
	{
		AbilityIcon[i].Draw();
	}

	abilitiesBox[0].Draw();
	abilitiesBox[1].Draw();
	abilitiesBox[2].Draw();
}

void SetAbilitiesUse(bool value)
{
	//abilitiesBox[0].use = value;
	//abilitiesBox[1].use = value;
	//abilitiesBox[2].use = value;

	for (int i = 0; i < LEVELUP::ABILITIES_MAX; i++)
	{
		if (value == false)
			AbilityIcon[i].use = value;
	}

#ifdef DEBUG
	//abilityNumber[0].use = value;
	//abilityNumber[1].use = value;
	//abilityNumber[2].use = value;
#endif
}

int GetChosen() { return random[chosen]; }