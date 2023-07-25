#include "ModelReader.h"

DX11_MODEL Models[READ_MODEL::READ_MODEL_MAX];

void ReadModel()
{
	LoadModel((char*)"data/MODEL/Player1.obj", &Models[RM_PLAYER_1]);
	LoadModel((char*)"data/MODEL/Player2.obj", &Models[RM_PLAYER_2]);
	LoadModel((char*)"data/MODEL/Player3.obj", &Models[RM_PLAYER_3]);
	LoadModel((char*)"data/MODEL/Pointer1.obj", &Models[RM_POINTER_1]);
	LoadModel((char*)"data/MODEL/Pointer2.obj", &Models[RM_POINTER_2]);
	LoadModel((char*)"data/MODEL/Pointer3.obj", &Models[RM_POINTER_3]);
	LoadModel((char*)"data/MODEL/PointerYellow.obj", &Models[RM_POINTER_YELLOW]);
	LoadModel((char*)"data/MODEL/Follower.obj", &Models[RM_ENEMY_FOLLOWER]);
	LoadModel((char*)"data/MODEL/Shooter.obj", &Models[RM_ENEMY_SHOOTER]);
	LoadModel((char*)"data/MODEL/Explode.obj", &Models[RM_ENEMY_KAMIKAZE]);
	LoadModel((char*)"data/MODEL/Summoner.obj", &Models[RM_ENEMY_SUMMONER]);
	LoadModel((char*)"data/MODEL/Explosion1.obj", &Models[RM_EXPLOSION_1]);
	LoadModel((char*)"data/MODEL/Explosion2.obj", &Models[RM_EXPLOSION_2]);
	LoadModel((char*)"data/MODEL/RingCyan.obj", &Models[RM_FLOATRING_CYAN]);
	LoadModel((char*)"data/MODEL/RingPurple.obj", &Models[RM_FLOATRING_PURPLE]);
	LoadModel((char*)"data/MODEL/RingYellow.obj", &Models[RM_FLOATRING_YELLOW]);
	LoadModel((char*)"data/MODEL/RingBlack.obj", &Models[RM_FLOATRING_BLACK]);
	LoadModel((char*)"data/MODEL/RingSummon.obj", &Models[RM_FLOATRING_SUMMON]);
	LoadModel((char*)"data/MODEL/RingPlayer1.obj", &Models[RM_FLOATRING_PLAYER_1]);
	LoadModel((char*)"data/MODEL/RingPlayer2.obj", &Models[RM_FLOATRING_PLAYER_2]);
	LoadModel((char*)"data/MODEL/RingPurple.obj", &Models[RM_FLOATRING_PLAYER_3]);
	LoadModel((char*)"data/MODEL/Ball1.obj", &Models[RM_HP_BALL]);
	LoadModel((char*)"data/MODEL/Ball2.obj", &Models[RM_XP_BALL]);
	LoadModel((char*)"data/MODEL/EnemyBullet.obj", &Models[RM_ENEMY_BULLET]);
	LoadModel((char*)"data/MODEL/EnemySummon.obj", &Models[RM_ENEMY_SUMMON]);
	LoadModel((char*)"data/MODEL/Laser1.obj", &Models[RM_LASER_1]);
	LoadModel((char*)"data/MODEL/Laser2.obj", &Models[RM_LASER_2]);
	LoadModel((char*)"data/MODEL/Laser3.obj", &Models[RM_LASER_3]);
	LoadModel((char*)"data/MODEL/SquareDisplay1.obj", &Models[RM_DISPLAY_SQUARE_1]);
	LoadModel((char*)"data/MODEL/SquareDisplay2.obj", &Models[RM_DISPLAY_SQUARE_2]);
	LoadModel((char*)"data/MODEL/SquareDisplay3.obj", &Models[RM_DISPLAY_SQUARE_3]);
	LoadModel((char*)"data/MODEL/Square1.obj", &Models[RM_SQUARE_1]);
	LoadModel((char*)"data/MODEL/Square2.obj", &Models[RM_SQUARE_2]);
	LoadModel((char*)"data/MODEL/Square3.obj", &Models[RM_SQUARE_3]);
	LoadModel((char*)"data/MODEL/Square4.obj", &Models[RM_SQUARE_4]);
	LoadModel((char*)"data/MODEL/Square5.obj", &Models[RM_SQUARE_5]);
	LoadModel((char*)"data/MODEL/Sphere1.obj", &Models[RM_SPHERE_1]);
	LoadModel((char*)"data/MODEL/SphereGrid1.obj", &Models[RM_GRID_1]);
	LoadModel((char*)"data/MODEL/SphereGrid2.obj", &Models[RM_GRID_2]);
	LoadModel((char*)"data/MODEL/SphereGrid3.obj", &Models[RM_GRID_3]);
	LoadModel((char*)"data/MODEL/Plane1.obj", &Models[RM_PLANE_1]);
	LoadModel((char*)"data/MODEL/Plane2.obj", &Models[RM_PLANE_2]);
	LoadModel((char*)"data/MODEL/Plane3.obj", &Models[RM_PLANE_3]);
}

void UnReadModel()
{
	for (int i = 0; i < READ_MODEL::READ_MODEL_MAX; i++)
	{
		UnloadModel(&Models[i]);
	}
}

DX11_MODEL * GetReadModel(READ_MODEL value)
{
	return &Models[value];
}
