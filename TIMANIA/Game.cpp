#include "Game.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "meshfield.h"
#include "collision.h"
#include "Dome.h"
#include "EnemyBullet.h"
#include "fade.h"
#include "Texture.h"
#include "Explosion.h"
#include "Sword.h"
#include "sound.h"
#include "Text.h"
#include "Number.h"
#include "Abilities.h"
#include "AbilityUpdate.h"
#include "ball.h"
#include "inputx.h"
#include "camera.h"
#include "FloatRing.h"
#include "SoundReader.h"
#include "EnemySummon.h"
#include "Pointer.h"
#include "Ground.h"

int BackGroundSound;

GROUND Ground;
PLAYER Player;
SWORD Sword;
D3DXVECTOR3 PlayerBackUp;
DOME CageDome;
DOME SkyDome;
//DOME SkyDome2;
TEXT Pause;
TEXT GameReturner;
TEXT Enemies;
bool pause = false;
bool pressed = false;
bool levelup = false;

int timeEndCounter = 0;
bool timeEnd = false;

void InitGame()
{
	GetCamera()->pos.y = POS_Y_CAM;
	GetCamera()->fov = VIEW_ANGLE;
	pause = false;
	pressed = false;
	levelup = false;
	timeEndCounter = 0;
	timeEnd = false;
	Pause.SetText(LoadTexture((char*)"data/TEXTURE/paused.png"), D3DXVECTOR3(0.0f, -0.3f + GAME_UI_ERROR, UI_Z), D3DXVECTOR2(0.6f, 0.08f));
	GameReturner.SetText(LoadTexture((char*)"data/TEXTURE/backSpace.png"), D3DXVECTOR3(1.6f, -1.6f + GAME_UI_ERROR, UI_Z), D3DXVECTOR2(0.65f, 0.2f), false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	Enemies.SetText(LoadTexture((char*)"data/TEXTURE/enemies.png"), D3DXVECTOR3(1.3f, 0.25f + GAME_UI_ERROR, UI_Z), D3DXVECTOR2(0.6f, 0.08f), true);
	InitializeTimer(D3DXVECTOR3(0.0f, 0.2f + GAME_UI_ERROR, UI_Z), D3DXVECTOR3(1.3f, 0.10f + GAME_UI_ERROR, UI_Z));
	InitializeAbilities();
	InitFloatRing();
	Player.Prepare();
	Sword.Prepare();
	CageDome.SetDome((GetStage() == 0 ? 21 : GetStage() == 1 ? 22 : 23));
	SkyDome.SetDome(0);
	//SkyDome2.Prepare();
	InitEnemy();
	InitBullet();
	InitEnemyBullet();
	InitPointer();
	InitEnemySummon();
	InitBall();
	InitExplosion();
	//InitMeshField(D3DXVECTOR3(0.0f, -100.0f+Y_AXIS, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1, 1, 1500, 1500);
	Ground.Prepare();
	InitCollision();

	SetFade(FADEIN);

	PlayReadSound(READ_SOUND::BGM_GAME, SOUND_TYPE::BGM);
	CageDome.GenerateRandomRotation(false, true, false, 5);
	CageDome.inGame = true;
	CageDome.SetSize(D3DXVECTOR3(100.0f, 100.0f, 100.0f));

	SkyDome.SetSize(D3DXVECTOR3(200.0f, 200.0f, 200.0f));
	SkyDome.GenerateRandomRotation(false, true, false, 5);

	GetCamera()->inGame = true;
	//SkyDome2.GenerateRandomRotation(false, true, false, 5);
	//SkyDome2.inGame = true;
	//SkyDome2.SetSize(D3DXVECTOR3(1500.0f, 1500.0f, 1500.0f));
}

void UnInitGame()
{
	pause = false;
	UnInitializePlayer();
	UnInitializeAbilities();
	CageDome.UnInitialize();
	SkyDome.UnInitialize();
	//SkyDome2.UnInitialize();
	Ground.UnInitialize();
	Pause.UnInitialize();
	GameReturner.UnInitialize();
	Enemies.UnInitialize();
	UnInitEnemy();
	UnInitBullet();
	UnInitExplosion();
	UnInitEnemyBullet();
	UnInitPointer();
	UnInitEnemySummon();
	UnInitFloatRing();
	UnInitBall();

	GetCamera()->inGame = false;
}

void UpdateGame()
{
	//PAUSE
	{
		if ((GetKeyBoardBool() == true ? GetKeyboardTrigger(DIK_P) : GetControllerTrigger("Start")) == true)
		{
			pressed = false;
			if (pause == false) { pause = true; PlayerBackUp = Player.GetPosition(); Pause.use = true; GameReturner.use = true; PlayReadSound(SE_PAUSE_IN, SE); SetVolumeForReadSound(BGM_GAME, 0.05f); }
			else if (pause == true) { pause = false; Player.SetPosition(D3DXVECTOR3(PlayerBackUp.x, Player.GetPosition().y, PlayerBackUp.z)); Pause.use = false; GameReturner.use = false; PlayReadSound(SE_PAUSE_OUT, SE); SetVolumeForReadSound(BGM_GAME, 0.1f); }
		}
	}
	if (pause == true) { if ((GetKeyBoardBool() == true? GetKeyboardTrigger(DIK_BACKSPACE): GetControllerTrigger("B")) == true) { PlayReadSound(SE_BUTTON_1, SE); } }

	//Ability Choose
	{
		if (levelup == true && GetEnemyNumber() > 0)
		{
			SetAbilitiesUse(true);
			UpdateAbilities();
			if ((GetKeyBoardBool() == true ? GetKeyboardTrigger(DIK_SPACE) : GetControllerTrigger("A")) == true)
			{
				levelup = false;
				SetAbilitiesUse(false);
				SetAbility(GetChosen());
				StopControlsBool(10);
			}
		}
	}

	if (levelup == false)
	{
		//Level Up
		{
			if (Player.level != Player.nextLevel && Player.death == false && Player.deathEffect == false && Player.GetUse() == true)
			{
				Player.level = Player.nextLevel;
				levelup = true;
				PlayReadSound(SE_LEVEL_UP, SE);
				StopControlsBool(30);
			}
		}

		Player.Update();
		UpdatePointer();
		UpdateCollision();
		Sword.Update();
		CageDome.Update();
		SkyDome.Update();
		//CageDome.DomePlayerFollow();
		//SkyDome2.Update();
		//SkyDome2.DomePlayerFollow();
		UpdateFloatRing();
		UpdateMeshField();
		if (pause == false)
		{
			UpdateExplosion();
			UpdateTimer();
			UpdateBullet();
			UpdateEnemyBullet();
			UpdateEnemySummon();
			UpdateBall();
			UpdateEnemy();

			if (Player.death == false && Player.deathEffect == false)
			{
				//Stop Ability
				if (Player.stop.UseBool == true)
				{
					Player.TimeShade.use = true;
					Player.stop.Counter += 1;
					if (Player.stop.Counter % Player.stop.CounterMax == 0)
					{
						Player.stop.Counter = 0;
						Player.stop.UseBool = false;
						Player.slow.UseBool = false;
						Player.TimeShade.use = false;
						PlayReadSound(SE_STOP_REVERSE, SE);
					}
				}
				//Slow Ability
				if (Player.slow.UseBool == true)
				{
					Player.TimeShade.use = true;
					Player.slow.Counter += 1;
					if (Player.slow.Counter % Player.slow.CounterMax == 0)
					{
						Player.slow.Counter = 0;
						Player.slow.UseBool = false;
						Player.TimeShade.use = false;
						PlayReadSound(SE_SLOW_REVERSE, SE);
					}
				}
			}
		}
	}

#ifdef DEBUG
	if (GetKeyboardTrigger(DIK_T)) { SetRemainingTime(GetRemainingTime() - DIFFICULTY_INCREASER); }
	if (GetKeyboardTrigger(DIK_Y)) { SetRemainingTime(GetRemainingTime() - DIFFICULTY_INCREASER/5); }
	if (GetKeyboardTrigger(DIK_U)) { SetRemainingTime(2); }

	//if (GetKeyboardPress(DIK_G)) { CageDome.Offset.x += 1.0f; }
	//if (GetKeyboardPress(DIK_H)) { CageDome.Offset.x -= 1.0f; }
	//if (GetKeyboardPress(DIK_J)) { SkyDome2.Offset.x += 1.0f; }
	//if (GetKeyboardPress(DIK_K)) { SkyDome2.Offset.x -= 1.0f; }
	char* str = GetDebugStr();
	//sprintf(&str[strlen(str)], "    CageDome.x : %.2f", CageDome.GetPosition().x);
	//sprintf(&str[strlen(str)], "    SkyDome2.x : %.2f", SkyDome2.GetPosition().x);
#endif

	if (GetRemainingTime() <= 0 || GetEnemyNumber() <= 0)
	{
		if(timeEndCounter == 0)
		{
			Player.topDownChange = true;
			Player.angleChanger = 1.0f;
		}
		Player.topDown = false;
		Player.stop.UseBool = true;
		Player.TimeShade.use = false;
		timeEndCounter++;
		if (timeEndCounter % 80 == 0) 
		{ 
			if (timeEnd == false)
			{
				timeEnd = true;
			}
		}
	}
	Fader((timeEnd == true || Player.death == true || (GetKeyBoardBool() == true ? GetKeyboardTrigger(DIK_BACKSPACE) : GetControllerTrigger("B")) && pause == true), RESULT);
}

void DrawGame()
{
	Ground.Draw();
	DrawEnemy();
	DrawBullet();
	DrawEnemyBullet();
	DrawPointer();
	DrawEnemySummon();
	DrawFloatRing();
	DrawBall();
	DrawExplosion();
	Player.Draw();
	Sword.Draw();

	DrawDome(&SkyDome);
	DrawDome(&CageDome);
	//DrawDome(&SkyDome2);
	//DrawMeshField();

	DrawPlayer();
	Enemies.Draw();
	DrawTimer();

	Player.TimeShade.Draw();
	DrawAbilities();

	Pause.Draw();
	GameReturner.Draw();
}

PLAYER* GetPlayer() { return &Player; }
SWORD* GetSword() { return &Sword; }
DOME* GetSkyDome() { return &CageDome; }
bool GetStop() { return Player.stop.UseBool; }
bool GetSlow() { return Player.slow.UseBool; }
bool GetPause() { return pause; }
bool GetSlowCoolDown() { return Player.slow.CoolDownBool; }
bool GetStopAnything() { if (Player.stop.UseBool == true || pause == true || levelup == true) { return true; } return false; }

void DrawPlayer()
{
	Player.stop.meter.Draw();
	Player.slow.meter.Draw();
	Player.HP_Container.Draw();
	Player.HP.Draw();
	Player.Experience_Container.Draw();
	Player.Experience.Draw();
	Player.Level.Draw();
	Player.LVL.Draw();
	Player.Blood.Draw();
}
void UnInitializePlayer()
{
	UnInitializeTimer();
	Pause.UnInitialize();
	Player.TimeShade.UnInitialize();
	Player.HP.UnInitialize();
	Player.HP_Container.UnInitialize();
	Player.stop.meter.UnInitialize();
	Player.slow.meter.UnInitialize();
	Player.Experience.UnInitialize();
	Player.Experience_Container.UnInitialize();
	Player.Level.UnInitialize();
	Player.LVL.UnInitialize();
	Player.Blood.UnInitialize();

	Sword.UnInitialize();
	Player.UnInitialize();
}