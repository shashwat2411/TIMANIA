#include "SoundReader.h"
#include "object.h"

int Sounds[READ_SOUND_MAX];

void ReadSound()
{
	//BGM
	{
		Sounds[BGM_TITLE] = LoadSound((char*)"data\\SOUND\\BGM\\BGM01.wav");
		Sounds[BGM_CHARACTER] = LoadSound((char*)"data\\SOUND\\BGM\\suits-you-69233.wav");
		Sounds[BGM_SELECT] = LoadSound((char*)"data\\SOUND\\BGM\\8bit-music-for-game-68698.wav");
		Sounds[BGM_GAME] = LoadSound((char*)"data\\SOUND\\BGM\\BGM03.wav");
		Sounds[BGM_RESULT_LOSE] = LoadSound((char*)"data\\SOUND\\BGM\\CutSceneDark.wav");
		Sounds[BGM_RESULT_WIN] = LoadSound((char*)"data\\SOUND\\BGM\\short-chiptune-loop-63966.wav");

		SetVolumeForReadSound(BGM_TITLE, 0.2f);
		SetVolumeForReadSound(BGM_CHARACTER, 0.4f);
		SetVolumeForReadSound(BGM_SELECT, 0.2f);
		SetVolumeForReadSound(BGM_GAME, 0.1f);
		SetVolumeForReadSound(BGM_RESULT_LOSE, 0.1f);
		SetVolumeForReadSound(BGM_RESULT_WIN, 0.2f);
	}

	//SE
	{
		//Fade
		{
			Sounds[SE_SCENE_SHIFT] = LoadSound((char*)"data\\SOUND\\SE\\sfx_movement_portal5.wav");

			SetVolumeForReadSound(SE_SCENE_SHIFT, 0.05f);
		}
		//Title & Select
		{
			Sounds[SE_BUTTON_1] = LoadSound((char*)"data\\SOUND\\SE\\sfx_menu_select2.wav");
			Sounds[SE_BUTTON_2] = LoadSound((char*)"data\\SOUND\\SE\\button.wav");
			Sounds[SE_SELECT_CHANGE] = LoadSound((char*)"data\\SOUND\\SE\\selectChange.wav");

			SetVolumeForReadSound(SE_BUTTON_1, 0.1f);
			SetVolumeForReadSound(SE_BUTTON_2, 0.1f);
			SetVolumeForReadSound(SE_SELECT_CHANGE, 0.1f);
		}
		//Game
		{
			//Sounds[SE_HOVER] = LoadSound((char*)"data\\SOUND\\SE\\hover.wav");

			Sounds[SE_PLAYER_ATTACK] = LoadSound((char*)"data\\SOUND\\SE\\laser.wav");
			Sounds[SE_PLAYER_ATTACK_BLOCK] = LoadSound((char*)"data\\SOUND\\SE\\sfx_wpn_noammo2.wav");
			Sounds[SE_PLAYER_DAMAGE] = LoadSound((char*)"data\\SOUND\\SE\\damage.wav");
			Sounds[SE_PLAYER_LOW_HP] = LoadSound((char*)"data\\SOUND\\SE\\lowHP.wav");
			Sounds[SE_PLAYER_SCREAM] = LoadSound((char*)"data\\SOUND\\SE\\sfx_deathscream_android7.wav");
			Sounds[SE_PLAYER_DEATH] = LoadSound((char*)"data\\SOUND\\SE\\playerExplosion.wav");
			Sounds[SE_PLAYER_WALL_COLLISION] = LoadSound((char*)"data\\SOUND\\SE\\lockon000.wav");

			Sounds[SE_STOP] = LoadSound((char*)"data\\SOUND\\SE\\stop.wav");
			Sounds[SE_STOP_REVERSE] = LoadSound((char*)"data\\SOUND\\SE\\stopReverse.wav");
			Sounds[SE_SLOW] = LoadSound((char*)"data\\SOUND\\SE\\slow.wav");
			Sounds[SE_SLOW_REVERSE] = LoadSound((char*)"data\\SOUND\\SE\\slowReverse.wav");
			Sounds[SE_COOLDOWN_FINISH] = LoadSound((char*)"data\\SOUND\\SE\\sfx_sound_neutral10.wav");

			Sounds[SE_EXPLOSION_SMALL] = LoadSound((char*)"data\\SOUND\\SE\\explosionS.wav");
			Sounds[SE_EXPLOSION_MEDIUM] = LoadSound((char*)"data\\SOUND\\SE\\explosionM.wav");
			Sounds[SE_EXPLOSION_BIG] = LoadSound((char*)"data\\SOUND\\SE\\explosionB.wav");

			Sounds[SE_ENEMY_DAMAGE] = LoadSound((char*)"data\\SOUND\\SE\\sfx_sounds_damage3.wav");
			Sounds[SE_ENEMY_FOLLOW_SOUND] = LoadSound((char*)"data\\SOUND\\SE\\followerSound.wav");
			Sounds[SE_ENEMY_BULLET_LAUNCH] = LoadSound((char*)"data\\SOUND\\SE\\enemyShoot.wav");
			Sounds[SE_ENEMY_SUMMON_SPAWN] = LoadSound((char*)"data\\SOUND\\SE\\summonSpawn.wav");
			Sounds[SE_ENEMY_SUMMON_SOUND] = LoadSound((char*)"data\\SOUND\\SE\\summon.wav");
			Sounds[SE_ENEMY_SUMMON_DEATH] = LoadSound((char*)"data\\SOUND\\SE\\summonDeath.wav");
			Sounds[SE_ENEMY_SUMMONER_SOUND] = LoadSound((char*)"data\\SOUND\\SE\\summonerSound.wav");
			Sounds[SE_ENEMY_TICK] = LoadSound((char*)"data\\SOUND\\SE\\enemyTick.wav");
			Sounds[SE_ENEMY_DEATH] = LoadSound((char*)"data\\SOUND\\SE\\sfx_deathscream_robot4.wav");

			Sounds[SE_ITEM_SPAWN] = LoadSound((char*)"data\\SOUND\\SE\\sfx_sounds_powerup1.wav");
			Sounds[SE_ITEM_COLLECT_HP] = LoadSound((char*)"data\\SOUND\\SE\\PowerUp.wav");
			Sounds[SE_ITEM_COLLECT_XP] = LoadSound((char*)"data\\SOUND\\SE\\PowerUp.wav");

			Sounds[SE_LEVEL_UP] = LoadSound((char*)"data\\SOUND\\SE\\sfx_sounds_fanfare3.wav");
			Sounds[SE_PAUSE_IN] = LoadSound((char*)"data\\SOUND\\SE\\pause_in.wav");
			Sounds[SE_PAUSE_OUT] = LoadSound((char*)"data\\SOUND\\SE\\pause_out.wav");
			Sounds[SE_COUNTDOWN] = LoadSound((char*)"data\\SOUND\\SE\\countdown.wav");


			//SetVolumeForReadSound(SE_HOVER, 0.5f);

			SetVolumeForReadSound(SE_PLAYER_ATTACK, 0.1f);
			SetVolumeForReadSound(SE_PLAYER_ATTACK_BLOCK, 0.1f);
			SetVolumeForReadSound(SE_PLAYER_DAMAGE, 0.1f);
			SetVolumeForReadSound(SE_PLAYER_LOW_HP, 0.5f);
			SetVolumeForReadSound(SE_PLAYER_SCREAM, 0.1f);
			SetVolumeForReadSound(SE_PLAYER_DEATH, 0.1f);
			SetVolumeForReadSound(SE_PLAYER_WALL_COLLISION, 0.1f);

			SetVolumeForReadSound(SE_STOP, 0.3f);
			SetVolumeForReadSound(SE_STOP_REVERSE, 0.3f);
			SetVolumeForReadSound(SE_SLOW, 0.5f);
			SetVolumeForReadSound(SE_SLOW_REVERSE, 0.5f);
			SetVolumeForReadSound(SE_COOLDOWN_FINISH, 0.2f);

			SetVolumeForReadSound(SE_EXPLOSION_SMALL, 0.02f);
			SetVolumeForReadSound(SE_EXPLOSION_MEDIUM, 0.05f);
			SetVolumeForReadSound(SE_EXPLOSION_BIG, 0.3f);

			SetVolumeForReadSound(SE_ENEMY_DAMAGE, 0.2f);
			SetVolumeForReadSound(SE_ENEMY_FOLLOW_SOUND, 0.1f);
			SetVolumeForReadSound(SE_ENEMY_BULLET_LAUNCH, 0.1f);
			SetVolumeForReadSound(SE_ENEMY_SUMMON_SPAWN, 0.1f);
			SetVolumeForReadSound(SE_ENEMY_SUMMON_SOUND, 0.1f);
			SetVolumeForReadSound(SE_ENEMY_SUMMON_DEATH, 0.1f);
			SetVolumeForReadSound(SE_ENEMY_SUMMONER_SOUND, 0.1f);
			SetVolumeForReadSound(SE_ENEMY_TICK, 0.1f);
			SetVolumeForReadSound(SE_ENEMY_DEATH, 0.1f);

			SetVolumeForReadSound(SE_ITEM_SPAWN, 0.1f);
			SetVolumeForReadSound(SE_ITEM_COLLECT_HP, 0.1f);
			SetVolumeForReadSound(SE_ITEM_COLLECT_XP, 0.1f);

			SetVolumeForReadSound(SE_LEVEL_UP, 0.1f);
			SetVolumeForReadSound(SE_PAUSE_IN, 0.1f);
			SetVolumeForReadSound(SE_PAUSE_OUT, 0.1f);
			SetVolumeForReadSound(SE_COUNTDOWN, 0.1f);
		}
		//Result
		{
			Sounds[SE_WIN] = LoadSound((char*)"data\\SOUND\\SE\\winSE.wav");
			Sounds[SE_LOSE] = LoadSound((char*)"data\\SOUND\\SE\\gameOver01.wav");


			SetVolumeForReadSound(SE_WIN, 0.2f);
			SetVolumeForReadSound(SE_LOSE, 0.1f);
		}
	}
}

void SetVolumeForReadSound(READ_SOUND num, float volume)
{
	SetVolume(Sounds[num], volume);
}

void StopReadSound(READ_SOUND num)
{
	StopSound(Sounds[num]);
}

void PlayReadSound(READ_SOUND num, SOUND_TYPE type)
{
	if (GetMuteBool() == false)
	{
		if (num != READ_SOUND_NONE)
		{
			if (type == SE) { PlaySound(Sounds[num], 0); }
			else if (type == BGM) { PlaySound(Sounds[num], -1); }
		}
	}
}
void PlayReadSound(READ_SOUND num, SOUND_TYPE type, float volume)
{
	SetVolumeForReadSound(num, volume);

	PlayReadSound(num, type);
}
