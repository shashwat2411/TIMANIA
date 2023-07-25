#pragma once
#include "model.h"

enum READ_MODEL
{
	RM_PLAYER_1,
	RM_PLAYER_2,
	RM_PLAYER_3,
	RM_POINTER_1,
	RM_POINTER_2,
	RM_POINTER_3,
	RM_POINTER_YELLOW,
	RM_ENEMY_FOLLOWER,
	RM_ENEMY_SHOOTER,
	RM_ENEMY_KAMIKAZE,
	RM_ENEMY_SUMMONER,
	RM_EXPLOSION_1,
	RM_EXPLOSION_2,
	RM_FLOATRING_CYAN,
	RM_FLOATRING_PURPLE,
	RM_FLOATRING_YELLOW,
	RM_FLOATRING_BLACK,
	RM_FLOATRING_SUMMON,
	RM_FLOATRING_PLAYER_1,
	RM_FLOATRING_PLAYER_2,
	RM_FLOATRING_PLAYER_3,
	RM_HP_BALL,
	RM_XP_BALL,
	RM_ENEMY_BULLET,
	RM_ENEMY_SUMMON,
	RM_LASER_1,
	RM_LASER_2,
	RM_LASER_3,
	RM_DISPLAY_SQUARE_1,
	RM_DISPLAY_SQUARE_2,
	RM_DISPLAY_SQUARE_3,
	RM_SQUARE_1,
	RM_SQUARE_2,
	RM_SQUARE_3,
	RM_SQUARE_4,
	RM_SQUARE_5,
	RM_SPHERE_1,
	RM_GRID_1,
	RM_GRID_2,
	RM_GRID_3,
	RM_PLANE_1,
	RM_PLANE_2,
	RM_PLANE_3,

	READ_MODEL_MAX
};

void ReadModel();
void UnReadModel();
DX11_MODEL* GetReadModel(READ_MODEL value);