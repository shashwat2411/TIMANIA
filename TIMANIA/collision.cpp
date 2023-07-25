#include "collision.h"
#include "player.h"
#include "camera.h"
#include "enemy.h"
#include "EnemyBullet.h"
#include "EnemySummon.h"
#include "Explosion.h"
#include "Sword.h"
#include "ball.h"
#include "Dome.h"

//===================================
//プロトタイプ宣言
//===================================
bool CollisionBB(D3DXVECTOR3 Pos1, D3DXVECTOR3 Size1, D3DXVECTOR3 Pos2, D3DXVECTOR3 Size2);
bool CollisionBB(OBJECT* obj1, OBJECT* obj2);
bool CollisionBS(D3DXVECTOR3 Pos1, float Radius1, D3DXVECTOR3 Pos2, float Radius2);
bool CollisionBS(D3DXVECTOR3 Pos1, D3DXVECTOR3 Radius1, D3DXVECTOR3 Pos2, D3DXVECTOR3 Radius2);

//===================================
//グローバル変数
//===================================
PLAYER* c_Player;
ENEMY* c_Enemy;
ENEMYBULLET* c_EnemyBullet;
ENEMYSUMMON* c_EnemySummon;
SWORD* c_Sword;
BALL* c_Ball;
EXPLOSION* c_Explosion;
DOME* c_SkyDome;

bool enemyCollide = false;
int CollisionCounter = 0;

HRESULT InitCollision()
{
	c_Player = GetPlayer();
	c_Enemy = GetEnemy();
	c_EnemyBullet = GetEnemyBullet();
	c_EnemySummon = GetEnemySummon();
	c_Sword = GetSword();
	c_Ball = GetBall();
	c_Explosion = GetExplosion();
	c_SkyDome = GetSkyDome();
	return S_OK;
}

void UpdateCollision()
{
	if (c_Player->GetUse() == true)
	{
		if (c_Player->DistanceFrom(c_SkyDome) > c_SkyDome->GetSize().x - 1.8f)
		{
			c_Player->OutOfBounds = true;

			//D3DXVECTOR3 mov = c_Player->GetPlayerMoveSpeed();
			//mov.y = 0.01f;
			//D3DXVec3Normalize(&mov, &mov);
			//mov *= -1;

			D3DXVECTOR3 mov2 = c_Player->MoveTowardsR(c_SkyDome);
			mov2.y = 0.0f;
			D3DXVec3Normalize(&mov2, &mov2);
			mov2 *= c_Player->GetSpeed()*5.0f;

			//c_Player->SetPlayerMoveSpeed(mov*c_Player->GetSpeed()*3.0f);
			mov2.y = 0.01f;
			c_Player->SetPlayerMoveSpeed(mov2);

			c_Player->FaceTowardsRD(c_SkyDome, 180.0f);
			//c_Player->SetRotation(D3DXVECTOR3(c_Player->GetRotation().x, c_Player->GetRotation().y + 180.0f, c_Player->GetRotation().z));

			PlayReadSound(SE_PLAYER_WALL_COLLISION, SE);
		}
	}

	if (GetPause() == false)
	{
		//プレーヤー
		if (c_Player->GetUse() == true)
		{
			//ENEMY
			for (int i = 0; i < ENEMY_MAX; i++)
			{
				if (c_Enemy[i].GetUse() == true)
				{
					//if (CollisionBS(c_Player->GetPosition(), c_Player->GetCollisionSize().x * 3 / 4, c_Enemy[i].GetPosition(), c_Enemy[i].GetCollisionSize().x * 3 / 4))
					//{
					//	c_Player->Damage(10);
					//	c_Enemy[i].Damage(c_Enemy[i].HP);
					//}
					if (CollisionBB(c_Player->GetPosition(), c_Player->GetCollisionSize() * 3 / 4, c_Enemy[i].GetPosition(), c_Enemy[i].GetCollisionSize() * 3 / 4))
					{
						c_Player->Damage(20);
						c_Enemy[i].Damage(c_Enemy[i].HP);
					}
				}
			}
			//ENEMYBULLET
			for (int i = 0; i < ENEMYBULLET_MAX; i++)
			{
				if (c_EnemyBullet[i].GetUse() == true)
				{
					if (CollisionBS(c_Player->GetPosition(), c_Player->GetCollisionSize().x * 3 / 4, c_EnemyBullet[i].GetPosition(), c_EnemyBullet[i].GetCollisionSize().x * 3 / 4))
					{
						c_Player->Damage(8);
						c_EnemyBullet[i].Destroy();
					}
				}
			}
			//ENEMYSUMMON
			for (int i = 0; i < ENEMYSUMMON_MAX; i++)
			{
				if (c_EnemySummon[i].GetUse() == true)
				{
					if (CollisionBS(c_Player->GetPosition(), c_Player->GetCollisionSize().x * 3 / 4, c_EnemySummon[i].GetPosition(), c_EnemySummon[i].GetCollisionSize().x * 3 / 4))
					{
						c_Player->Damage(14);
						c_EnemySummon[i].Destroy();
					}
				}
			}
			//BALL
			for (int i = 0; i < BALL_MAX; i++)
			{
				if (c_Ball[i].GetUse() == true)
				{
					if (CollisionBS(c_Ball[i].GetPosition(), c_Ball[i].GetCollisionSize().x * 3 / 4, c_Player->GetPosition(), c_Player->GetCollisionSize().x * 3 / 4))
					{
						//SetExplosion(c_Ball[i].GetPosition(), D3DXVECTOR3(1.0f,0.0f,0.0f), EXPLOSION_TYPE::NORMAL, 1.0f);
						if (c_Ball[i].Type == BALL_TYPE::EXP) { c_Player->GainExperience(16); PlayReadSound(SE_ITEM_COLLECT_XP, SE); }
						else if (c_Ball[i].Type == BALL_TYPE::HEALTH) { c_Player->GainHealth(c_Player->hpMax / 5); PlayReadSound(SE_ITEM_COLLECT_HP, SE); }
						c_Player->SetDamage(true);
						c_Player->SetLight(false);
						c_Ball[i].SetUse(false);
					}
				}
			}
			////EXPLOSION
			//for (int i = 0; i < EXPLOSION_MAX; i++)
			//{
			//	if (c_Explosion->GetUse() == true)
			//	{
			//		if (c_Explosion->Type == EXPLOSION_TYPE::DAMAGE)
			//		{
			//			if (CollisionBS(c_Explosion[i].GetPosition(), c_Explosion[i].GetCollisionSize().x * 3 / 4, c_Player->GetPosition(), c_Player->GetCollisionSize().x * 3 / 4))
			//			{
			//				c_Explosion->SetUse(false);
			//				c_Player->Damage(GetPlayer()->damageRecieveAmount * 10);
			//			}
			//		}
			//	}
			//}
			////SKYDOME
			//if (c_SkyDome->GetUse() == true)
			//{
			//	if (!CollisionBB(c_Player->GetPosition(), c_Player->GetCollisionSize() * 3 / 4, c_SkyDome->GetPosition(), c_SkyDome->GetCollisionSize()))
			//	{
			//		D3DXVECTOR3 temp;
			//		D3DXVec3Normalize(&temp, &c_Player->PlayerMoveSpeed);
			//		if (c_Player->forward == true || c_Player->backward)
			//		{
			//			c_Player->PlayerMoveSpeed = D3DXVECTOR3(c_Player->PlayerMoveSpeed.x, c_Player->PlayerMoveSpeed.y, -temp.z);
			//			c_Player->boundX = true;
			//		}
			//		else if (c_Player->right == true || c_Player->left)
			//		{
			//			c_Player->PlayerMoveSpeed = D3DXVECTOR3(-temp.x, c_Player->PlayerMoveSpeed.y, c_Player->PlayerMoveSpeed.z);
			//			c_Player->boundX = true;
			//		}
			//	}
			//	else
			//	{
			//		c_Player->boundX = false;
			//	}
			//}
		}

		//SWORD
		if (c_Sword->GetUse() == true)
		{
			//ENEMY
			for (int i = 0; i < ENEMY_MAX; i++)
			{
				if (c_Enemy[i].GetUse() == true)
				{
					//if (CollisionBB(c_Sword, &c_Enemy[i])) { c_Enemy[i].SetUse(false); }
					if (CollisionBS(c_Sword->GetPosition(), c_Sword->GetCollisionSize().x * 3 / 4, c_Enemy[i].GetPosition(), c_Enemy[i].GetCollisionSize().x * 3 / 4) && c_Enemy[i].collide == false)
					{
						c_Enemy[i].collide = true;
						c_Enemy[i].Damage(1);
					}
				}
			}
			//ENEMYBULLET
			for (int i = 0; i < ENEMYBULLET_MAX; i++)
			{
				if (c_EnemyBullet[i].GetUse() == true)
				{
					//if (CollisionBB(c_Sword, &c_Enemy[i])) { c_Enemy[i].SetUse(false); }
					if (CollisionBS(c_Sword->GetPosition(), c_Sword->GetCollisionSize().x * 3 / 4, c_EnemyBullet[i].GetPosition(), c_EnemyBullet[i].GetCollisionSize().x * 3 / 4))
					{
						c_EnemyBullet[i].Destroy();
					}
				}
			}
			//ENEMYSUMMON
			for (int i = 0; i < ENEMYSUMMON_MAX; i++)
			{
				if (c_EnemySummon[i].GetUse() == true)
				{
					//if (CollisionBB(c_Sword, &c_Enemy[i])) { c_Enemy[i].SetUse(false); }
					if (CollisionBS(c_Sword->GetPosition(), c_Sword->GetCollisionSize().x * 3 / 4, c_EnemySummon[i].GetPosition(), c_EnemySummon[i].GetCollisionSize().x * 3 / 4))
					{
						c_EnemySummon[i].Destroy();
					}
				}
			}
		}
	}
}


bool CollisionBB(D3DXVECTOR3 Pos1, D3DXVECTOR3 Size1, D3DXVECTOR3 Pos2, D3DXVECTOR3 Size2)
{
	//各軸方向のBOXの最大値と最低値を計算しておく
	D3DXVECTOR3 OBJ1_Max;
	D3DXVECTOR3 OBJ1_Min;
	D3DXVECTOR3 OBJ2_Max;
	D3DXVECTOR3 OBJ2_Min;
	//OBJECT1のBOX
	OBJ1_Max.x = Pos1.x + (Size1.x / 2.0f);
	OBJ1_Max.y = Pos1.y + (Size1.y / 2.0f);
	OBJ1_Max.z = Pos1.z + (Size1.z / 2.0f);

	OBJ1_Min.x = Pos1.x - (Size1.x / 2.0f);
	OBJ1_Min.y = Pos1.y - (Size1.y / 2.0f);
	OBJ1_Min.z = Pos1.z - (Size1.z / 2.0f);

	//OBJECT2のBOX
	OBJ2_Max.x = Pos2.x + (Size2.x / 2.0f);
	OBJ2_Max.y = Pos2.y + (Size2.y / 2.0f);
	OBJ2_Max.z = Pos2.z + (Size2.z / 2.0f);
				 		   
	OBJ2_Min.x = Pos2.x - (Size2.x / 2.0f);
	OBJ2_Min.y = Pos2.y - (Size2.y / 2.0f);
	OBJ2_Min.z = Pos2.z - (Size2.z / 2.0f);

	if ((OBJ1_Max.x > OBJ2_Min.x) && (OBJ1_Min.x < OBJ2_Max.x))	//X軸の判定
	{
		if ((OBJ1_Max.y > OBJ2_Min.y) && (OBJ1_Min.y < OBJ2_Max.y))	//Y軸の判定
		{
			if ((OBJ1_Max.z > OBJ2_Min.z) && (OBJ1_Min.z < OBJ2_Max.z))	//Z軸の判定
			{
				return true;
			}
		}
	}

	return false;
}
//当たり判定の検知関数
bool CollisionBB(OBJECT* obj1, OBJECT* obj2)
{
	//各軸方向のBOXの最大値と最低値を計算しておく
	D3DXVECTOR3 OBJ1_Max;
	D3DXVECTOR3 OBJ1_Min;
	D3DXVECTOR3 OBJ2_Max;
	D3DXVECTOR3 OBJ2_Min;
	//OBJECT1のBOX
	OBJ1_Max.x = obj1->GetPosition().x + (obj1->GetCollisionSize().x / 2.0f);
	OBJ1_Max.y = obj1->GetPosition().y + (obj1->GetCollisionSize().y / 2.0f);
	OBJ1_Max.z = obj1->GetPosition().z + (obj1->GetCollisionSize().z / 2.0f);

	OBJ1_Min.x = obj1->GetPosition().x - (obj1->GetCollisionSize().x / 2.0f);
	OBJ1_Min.y = obj1->GetPosition().y - (obj1->GetCollisionSize().y / 2.0f);
	OBJ1_Min.z = obj1->GetPosition().z - (obj1->GetCollisionSize().z / 2.0f);

	//OBJECT2のBOX
	OBJ2_Max.x = obj2->GetPosition().x + (obj2->GetCollisionSize().x / 2.0f);
	OBJ2_Max.y = obj2->GetPosition().y + (obj2->GetCollisionSize().y / 2.0f);
	OBJ2_Max.z = obj2->GetPosition().z + (obj2->GetCollisionSize().z / 2.0f);
											 
	OBJ2_Min.x = obj2->GetPosition().x - (obj2->GetCollisionSize().x / 2.0f);
	OBJ2_Min.y = obj2->GetPosition().y - (obj2->GetCollisionSize().y / 2.0f);
	OBJ2_Min.z = obj2->GetPosition().z - (obj2->GetCollisionSize().z / 2.0f);

	if ((OBJ1_Max.x > OBJ2_Min.x) && (OBJ1_Min.x < OBJ2_Max.x))	//X軸の判定
	{
		if ((OBJ1_Max.y > OBJ2_Min.y) && (OBJ1_Min.y < OBJ2_Max.y))	//Y軸の判定
		{
			if ((OBJ1_Max.z > OBJ2_Min.z) && (OBJ1_Min.z < OBJ2_Max.z))	//Z軸の判定
			{
				return true;
			}
		}
	}

	return false;
}

bool CollisionBS(D3DXVECTOR3 Pos1, float Radius1, D3DXVECTOR3 Pos2, float Radius2)
{
	D3DXVECTOR3 dist = Pos1 - Pos2;		//双法の中心同士をつなぐベクトル
	float length = D3DXVec3Length(&dist);	//ベクトルの長さを計算
	//float length = D3DXVec3LengthSq(&dist);	//√を使わないバージョン
	float size = Radius1 + Radius2;

	//判定
	if (length < size) { return true; }
	return false;
}

bool CollisionBS(D3DXVECTOR3 Pos1, D3DXVECTOR3 Radius1, D3DXVECTOR3 Pos2, D3DXVECTOR3 Radius2)
{
	D3DXVECTOR3 dist = Pos1 - Pos2;		//双法の中心同士をつなぐベクトル
	float length = D3DXVec3Length(&dist);	//ベクトルの長さを計算
	//float length = D3DXVec3LengthSq(&dist);	//√を使わないバージョン
	D3DXVECTOR3 size = Radius1 + Radius2;

	//判定
	if (length < size.x && length < size.y && length < size.z) { return true; }
	return false;
}

bool CollisionBB_Right(D3DXVECTOR3 Position1, D3DXVECTOR3 Size1, D3DXVECTOR3 Position2, D3DXVECTOR3 Size2)
{
	

	return	false;
}