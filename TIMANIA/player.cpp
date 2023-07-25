#include "player.h"
#include "inputx.h"
#include "mouse.h"
#include "Explosion.h"
#include "enemy.h"
#include "ball.h"
#include "FloatRing.h"

#define EXPERIENCE_BAR_LENGTH 0.5f
#define EXPERIENCE_BAR_LENGTH_CONTROLLER 0.5f

#define FIRST_ZOOM 4
#define SECOND_ZOOM 10

static bool pressed = false;
ENEMY* pEnemy;
bool close[ENEMY_MAX] = { false };

void PLAYER::Prepare()
{
	Initialize();
	pEnemy = GetEnemy();
	enemyCloseNum = 0;
	called_1 = false;
	called_2 = false;
	for (int i = 0; i < ENEMY_MAX; i++) { close[i] = false; }

	D3DXVECTOR3 at = D3DXVECTOR3(Position.x, Y_AXIS + 0.5f, Position.z);
	SetCameraATDelay(at);

	if (GetChosenPlayer() == 0)
	{
		PlayerHP = PLAYER_HP;
		PlayerSpeed = MOVE_SPEED;
		AttackCoolDown = ATTACK_COOLDOWN;
		AttackRange = ATTACK_RANGE;
		AttackKnockBack = ATTACK_KNOCKBACK;
		StopTime = STOP_TIME;
		StopCoolDown = STOP_COOLDOWN;
		SlowTime = SLOW_TIME;
		SlowCoolDowm = SLOW_COOLDOWN;
	}
	else if (GetChosenPlayer() == 1)
	{
		PlayerHP = PLAYER_HP + 20;
		PlayerSpeed = MOVE_SPEED * 0.8f;
		AttackCoolDown = ATTACK_COOLDOWN + 6;
		AttackRange = ATTACK_RANGE * 1.2f;
		AttackKnockBack = ATTACK_KNOCKBACK * 1.2f;
		StopTime = STOP_TIME;
		StopCoolDown = STOP_COOLDOWN * 12 / 10;
		SlowTime = SLOW_TIME;
		SlowCoolDowm = SLOW_COOLDOWN * 12 / 10;
	}
	else if (GetChosenPlayer() == 2)
	{
		PlayerHP = PLAYER_HP - 20;
		PlayerSpeed = MOVE_SPEED * 1.144f;
		AttackCoolDown = ATTACK_COOLDOWN - 3;
		AttackRange = ATTACK_RANGE * 0.8f;
		AttackKnockBack = ATTACK_KNOCKBACK * 0.8f;
		StopTime = STOP_TIME * 7 / 10;
		StopCoolDown = STOP_COOLDOWN;
		SlowTime = SLOW_TIME * 7 / 10;
		SlowCoolDowm = SLOW_COOLDOWN;
	}
	//LoadModel((char*)"data/MODEL/player.obj", &Model);

	//TopDown Effect
	topDown = false;
	topDownChange = false;
	topDownAngle = 25.50f;
	angleChanger = 0.0f;
	normalAngle = 5.50f;
	angleChangeCounter = 0;
	defeated = 0;

	PlayerMoveSpeed = D3DXVECTOR3(0.0f, 0.01f, 0.0f);
	Speed = PlayerSpeed;
	hpMax = PlayerHP;
	hp = hpMax;
	lowHP = false;
	move = false;
	moveDiagonal = false;
	rotationFix = 0;
	damage = false;
	attack = false;
	attackCoolDown = 0;
	attackCoolDownMax = AttackCoolDown;
	range = AttackRange;
	attackKnockBack = AttackKnockBack;
	level = 1;
	nextLevel = level;
	experienceMax = 10 * level;
	experience = 0;
	experienceMaxBackUp = experienceMax;

	experienceAmount = (GetStage() == 0 ? 0 : (GetStage() == 1 ? 2 : 4));
	damageRecieveAmount = (GetStage() == 0 ? 0 : (GetStage() == 1 ? 0 : 0));

	//TimeShade
	{
		TimeShade.SetText(LoadTexture((char*)"data/TEXTURE/fade.png"), D3DXVECTOR3(0.0f, -0.3f + GAME_UI_ERROR, -UI_Z*2), D3DXVECTOR2(5.27f, 3.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.1f));
		TimeShade.use = false;
	}
	//HP Bar
	{
		HP.Prepare();
		HP.TextNo = LoadTexture((char*)"data/TEXTURE/hp.png");
		HP.Offset = D3DXVECTOR3(-1.4f, 0.26f + GAME_UI_ERROR, UI_Z);
		HP.Size = D3DXVECTOR2(0.8f, 0.07f);
		HP.left = (1.0f / (float)hpMax) * (float)(hp - hpMax);
	}
	//HP Container Bar
	{
		HP_Container.Prepare();
		HP_Container.TextNo = HP.TextNo;
		HP_Container.Offset = D3DXVECTOR3(HP.Offset.x, HP.Offset.y, HP.Offset.z);
		HP_Container.Size = D3DXVECTOR2(HP.Size.x + 0.06f, HP.Size.y + 0.03f);
		HP_Container.Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		HP_Container.left = HP.left;
	}
	//Blood
	{
		Blood.Prepare();
		Blood.TextNo = LoadTexture((char*)"data/TEXTURE/cracks.png");
		Blood.Offset = D3DXVECTOR3(0.0f, -0.2f + GAME_UI_ERROR, UI_Z);
		Blood.Size = D3DXVECTOR2(4.4f, 4.0f);
		//Blood.left = hpMax - hp;
	}

	//Time Stop Ability Icon
	{
		stop.UseBool = false;
		stop.Counter = 0;
		stop.CounterMax = StopTime;
		stop.CoolDownBool = false;
		stop.CoolDownTimer = StopCoolDown;
		stop.CoolDownTimerMax = StopCoolDown;
		stop.meter.Prepare();
		stop.meter.TextNo = LoadTexture((char*)"data/TEXTURE/Stop.png");
		stop.meter.Offset = D3DXVECTOR3(-1.7f, 0.03f + GAME_UI_ERROR, UI_Z);
		stop.meter.Size = D3DXVECTOR2(0.21f, 0.21f);
	}

	//Time Slow Ability Icon
	{
		slow.UseBool = false;
		slow.Counter = 0;
		slow.CounterMax = SlowTime;
		slow.CoolDownBool = false;
		slow.CoolDownTimer = SlowCoolDowm;
		slow.CoolDownTimerMax = SlowCoolDowm;
		slow.meter.Prepare();
		slow.meter.TextNo = LoadTexture((char*)"data/TEXTURE/Slow.png");
		slow.meter.Offset = D3DXVECTOR3(-1.486f, 0.03f + GAME_UI_ERROR, UI_Z);
		slow.meter.Size = D3DXVECTOR2(0.21f, 0.21f);
	}

	//Experience Bar
	{
		Experience.Prepare();
		Experience.TextNo = LoadTexture((char*)"data/TEXTURE/hp.png");
		Experience.Offset = D3DXVECTOR3(-1.4f, 0.18f + GAME_UI_ERROR, UI_Z);
		Experience.Size = D3DXVECTOR2(0.8f, 0.02f);
		Experience.Color = D3DXCOLOR(0.53f, 0.86f, 1.0f, 1.0f);
		Experience.left = (1.0f / (float)experienceMax * EXPERIENCE_BAR_LENGTH) * (float)(experience - experienceMax) - EXPERIENCE_BAR_LENGTH_CONTROLLER;
	}

	//Experience Container Bar
	{
		Experience_Container.Prepare();
		Experience_Container.TextNo = Experience.TextNo;
		Experience_Container.Offset = D3DXVECTOR3(Experience.Offset.x, Experience.Offset.y, Experience.Offset.z);
		Experience_Container.Size = D3DXVECTOR2(Experience.Size.x + 0.06f, Experience.Size.y + 0.02f);
		Experience_Container.Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		Experience_Container.left = (1.0f / (float)experienceMax * EXPERIENCE_BAR_LENGTH) * (float)(experienceMax)-EXPERIENCE_BAR_LENGTH_CONTROLLER;
	}

	//Level Text
	{
		LVL.SetText(LoadTexture((char*)"data/TEXTURE/lvl.png"), D3DXVECTOR3(-1.2f, 0.1f + GAME_UI_ERROR, UI_Z), D3DXVECTOR2(0.16f, 0.051f));
		LVL.use = true;
	}

	//Level Number
	{
		Level.SetText(D3DXVECTOR3(-1.06f, 0.1f + GAME_UI_ERROR, UI_Z), D3DXVECTOR2(0.08f, 0.08f));
	}

	Size = D3DXVECTOR3(0.3f, 0.3f, 0.3f);
	CollisionSize = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Shadow.SetScaling(5.0f);
	Position.y = Y_AXIS;
	use = true;

	death = false;
	deathEffect = false;
	deathCounter = 0;
	deathSoundDelay = 0;
	control = true;

	if (GetChosenPlayer() == 0)
	{
		pModel = GetReadModel(READ_MODEL::RM_PLAYER_1);
		SetFloatRing(this, D3DXVECTOR3(0.5f, 0.5f, 0.5f), 1.5f, READ_MODEL::RM_FLOATRING_PLAYER_1);
	}
	else if (GetChosenPlayer() == 1)
	{
		pModel = GetReadModel(READ_MODEL::RM_PLAYER_2);
		SetFloatRing(this, D3DXVECTOR3(0.5f, 0.5f, 0.5f), 1.5f, READ_MODEL::RM_FLOATRING_PLAYER_2);
	}
	else if (GetChosenPlayer() == 2)
	{
		pModel = GetReadModel(READ_MODEL::RM_PLAYER_3);
		SetFloatRing(this, D3DXVECTOR3(0.5f, 0.5f, 0.5f), 1.5f, READ_MODEL::RM_FLOATRING_PLAYER_3);
	}
	//PlayReadSound(SE_HOVER, BGM);
}


void PLAYER::Update()
{
	//CAMERA *cam = GetCamera();

	//if ((GetKeyboardTrigger(DIK_I) || GetControllerTrigger("Y") == true) && GetPause() == false)
	if (defeated >= (GetStage() == 0 ? 20 : 10))
	{
		topDown = true;
		angleChanger = 1.0f;
		topDownChange = true;
		angleChangeCounter = 600;
		defeated = 0;
	}

	if (angleChangeCounter == 0 && topDown == true)
	{
		topDown = false;
		angleChanger = 1.0f;
		topDownChange = true;
	}
	if (angleChangeCounter > 0) { angleChangeCounter--; }
	else { angleChangeCounter = 0; }

	if (topDownChange == true)
	{
		if (topDown == true)
		{
			if (GetCamera()->pos.y <= topDownAngle) { GetCamera()->pos.y += angleChanger; angleChanger *= 0.97f; }
			else { GetCamera()->pos.y = topDownAngle; topDownChange = false; }
		}
		else
		{
			if (GetCamera()->pos.y >= normalAngle) { GetCamera()->pos.y -= angleChanger; angleChanger *= 0.97f; }
			else { GetCamera()->pos.y = normalAngle; topDownChange = false; }
		}
	}

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (DistanceFrom(&pEnemy[i]) < 40.0f && pEnemy[i].GetUse() == true) { close[i] = true; }
		else { close[i] = false; }
	}
	int number = 0;
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (close[i] == true) { number++; }
	}
	enemyCloseNum = number;
	
	if (enemyCloseNum >= FIRST_ZOOM && enemyCloseNum < SECOND_ZOOM && called_1 == false) { GetCamera()->SetZoom(true); called_1 = true; }
	if (enemyCloseNum >= SECOND_ZOOM && called_1 == true && called_2 == false) { GetCamera()->SetZoom(true, 0.5f); called_2 = true; }
	if (enemyCloseNum <= 0 && called_1 == true) { GetCamera()->SetZoom(false); called_1 = false; }
	if (enemyCloseNum < SECOND_ZOOM && called_2 == true) { GetCamera()->SetZoom(false, 0.5f); called_2 = false; }

	if (deathCounter == 100)
	{
		deathSoundDelay++;
		if (deathSoundDelay == 70)
		{
			death = true;
		}
	}
	if (use == true)
	{
		if (death == false)
		{
			Counter++;
			if (Counter % 30 == 0) { PlayerMoveSpeed.y *= -1; Counter = 0; }
		}

		if (damage == true) { DamageCounter++; }
		if (damage == true && DamageCounter > DAMAGE_EFFECT_TIME) { damage = false; black = true; DamageCounter = 0; }
		//PlayerMoveSpeed.x = PlayerMoveSpeed.y = PlayerMoveSpeed.z = 0.0f;
		if (hp < hpMax * 0.25f && lowHP == false) { PlayReadSound(SE_PLAYER_LOW_HP, BGM); lowHP = true; }
		else if (lowHP == true && hp >= hpMax * 0.25f) { StopReadSound(SE_PLAYER_LOW_HP); lowHP = false; }

		HP_Container.Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		HP.left = (1.0f/ (float)hpMax) * (float)(hp - hpMax);
		HP.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		Blood.Color.a = (float)(hpMax - hp)/(float)hpMax +0.15f;

		if (GetEnemyNumber() <= 0) { HP.Color = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f); black = false; damage = true; }

		//死
		{
			if (hp > hpMax) { hp = hpMax; }
			if (hp < 0 || GetRemainingTime() <= 0 && control == true) { hp = 0; death = false; deathEffect = true; control = false; PlayerMoveSpeed = D3DXVECTOR3(0.05f, 0.0f, 0.0f); StopReadSound(SE_PLAYER_LOW_HP); topDown = false; topDownChange = true; angleChanger = 1.0f; }
			if (deathEffect == true && GetEnemyNumber > 0)
			{
				hp = 0;
				if (deathCounter < 80) { deathCounter++; }
				if (deathCounter % 5 == 0) { PlayerMoveSpeed.x *= -(1.0f + ((float)deathCounter / 160.0f)); }
				if (deathCounter % 7 == 0) { damage = true; }
				if (deathCounter % 14 == 0) { PlayReadSound(SE_PLAYER_SCREAM, SE); }

				stop.UseBool = true;
				TimeShade.use = false;
				stop.Counter = 0;

				//if (deathSoundDelay < 40) { deathSoundDelay++; }
				if (deathCounter == 60) { PlayReadSound(SE_PLAYER_DEATH, SE); }

				if (deathCounter == 80)
				{
					stop.UseBool = false;
					TimeShade.use = false;
					stop.CoolDownTimer = 0;
					SetExplosion(Position, D3DXVECTOR3(1.0f, 0.0f, 0.0f), EXPLOSION_TYPE::NORMAL, 3.0f, READ_SOUND_NONE);
					deathEffect = false;
					use = false;
					deathCounter = 100;
					SetCameraAT(D3DXVECTOR3(Position.x, 0.7f + 0.5f, Position.z));
				}
			}
		}

		//経験値とレベルの処理
		{
			experienceMax = (int)((float)level / 2.0f + 0.5f) * experienceMaxBackUp;

			Experience.left = (1.0f / (float)experienceMax * EXPERIENCE_BAR_LENGTH) * (float)(experience - experienceMax) - EXPERIENCE_BAR_LENGTH_CONTROLLER;
			if (experience - experienceMax >= experienceMax && nextLevel < 10) 
			{ 
				nextLevel++;
				experience = 0;
			}

			if (level == 10) { experience = experienceMax + experienceMax;  LVL.TextNo = LoadTexture((char*)"data/TEXTURE/max.png"); Level.use = false; }

			Level.SetNumber(level);
			Level.Update();
		}

		if (OutOfBounds == true)
		{
			if (fabs(PlayerMoveSpeed.x) <= 0.1f && fabs(PlayerMoveSpeed.z) <= 0.1f)
			{
				OutOfBounds = false;
			}
		}

		//入力
		{
			if (death == false && deathEffect == false && control == true && OutOfBounds == false)
			{
				if (rotationFix == 0)
				{
					if (GetKeyboardPress(DIK_LEFT)) { PlayerMoveSpeed.x = -Speed;	RotationDirection.y = 270; move = true;}
					else if (GetKeyboardPress(DIK_RIGHT)) { PlayerMoveSpeed.x = Speed;	RotationDirection.y = 90;  move = true;}
					if (GetKeyboardPress(DIK_UP)) { PlayerMoveSpeed.z = Speed;	RotationDirection.y = 0;  move = true;}
					else if (GetKeyboardPress(DIK_DOWN)) { PlayerMoveSpeed.z = -Speed;	RotationDirection.y = 180;  move = true;}
				}

				if (GetKeyboardPress(DIK_UP) && GetKeyboardPress(DIK_LEFT)) { RotationDirection.y = 315;  move = true; moveDiagonal = true;			PlayerMoveSpeed.x = -Speed/1.41f; PlayerMoveSpeed.z =  Speed/1.41f; }
				else if (GetKeyboardPress(DIK_UP) && GetKeyboardPress(DIK_RIGHT)) { RotationDirection.y = 45;  move = true; moveDiagonal = true;	PlayerMoveSpeed.x =  Speed/1.41f; PlayerMoveSpeed.z =  Speed/1.41f; }
				if (GetKeyboardPress(DIK_DOWN) && GetKeyboardPress(DIK_LEFT)) { RotationDirection.y = 225;  move = true; moveDiagonal = true;		PlayerMoveSpeed.x = -Speed/1.41f; PlayerMoveSpeed.z = -Speed/1.41f; }
				else if (GetKeyboardPress(DIK_DOWN) && GetKeyboardPress(DIK_RIGHT)) { RotationDirection.y = 135;  move = true; moveDiagonal = true;	PlayerMoveSpeed.x =  Speed/1.41f; PlayerMoveSpeed.z = -Speed/1.41f; }

				if ((GetKeyboardTrigger(DIK_Z)||GetControllerTrigger("X") == true) && GetPause() == false) { if (stop.CoolDownBool == false) { stop.UseBool = true; stop.CoolDownBool = true; PlayReadSound(SE_STOP, SE); } else { PlayReadSound(SE_PLAYER_ATTACK_BLOCK, SE); } TimeShade.Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, ALPHA_LOWEST*1.1f); }
				if ((GetKeyboardTrigger(DIK_X)||GetControllerTrigger("B") == true) && GetPause() == false) { if (slow.CoolDownBool == false) { slow.UseBool = true; slow.CoolDownBool = true;  PlayReadSound(SE_SLOW, SE); } else { PlayReadSound(SE_PLAYER_ATTACK_BLOCK, SE); } TimeShade.Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, ALPHA_LOWEST*1.1f); }

				if (move == true) { RotationDirection.x = MOVE_ROTATION; }
				else { RotationDirection.x = 0.0f; }

				if (moveDiagonal == true) { if (rotationFix <= 30) { rotationFix++; } }

				if (GetKeyBoardBool() == false)
				{
					PlayerMoveSpeed.x = Speed * GetStickL().x;
					PlayerMoveSpeed.z = Speed * GetStickL().y;
					//FaceTowards(GetStickL());
					if (GetStickL().x > 0 || GetStickL().x < 0 || GetStickL().y > 0 || GetStickL().y < 0)
					{
						move = true;
						if (move == true) { RotationDirection.x = MOVE_ROTATION * (GetStickL().x*GetStickL().x + GetStickL().y*GetStickL().y); }
						else { RotationDirection.x = 0.0f; }
						//if (GetStickL().y < 0) { RotationDirection.y = D3DXToDegree(atanf(fabs(GetStickL().x) / fabs(GetStickL().y))) + 180.0f; }
						//else if (GetStickL().y > 0) { RotationDirection.y = D3DXToDegree(atanf(fabs(GetStickL().x) / fabs(GetStickL().y))); }
						D3DXVECTOR3 mov = D3DXVECTOR3(GetStickL().x, 0.0f, GetStickL().y);
						D3DXVec3Normalize(&mov, &mov);

						RotationDirection.y = -atan2(GetStickL().y, GetStickL().x)*180.0f / 3.14f + 90.0f;
					}

				}
			}
			
#ifdef DEBUG
			if (GetKeyboardPress(DIK_W)) { GainExperience(1 - experienceAmount); }
			if (GetKeyboardPress(DIK_S)) { GainExperience(-1 - experienceAmount); }

			if (GetKeyboardPress(DIK_D)) { GainHealth(1); }
			if (GetKeyboardPress(DIK_A)) { Damage(1 - damageRecieveAmount); }

			if (GetKeyboardTrigger(DIK_F)) { Speed *= 2.0f; }
			if (GetKeyboardTrigger(DIK_G)) { Speed /= 2.0f; }

			if (GetKeyboardTrigger(DIK_B)) { GetCamera()->SetZoom(true); }
			//if (GetKeyboardTrigger(DIK_N)) { GetCamera()->SetZoom(false); }

			if (GetKeyboardPress(DIK_R)) { SetBall(D3DXVECTOR3(Position.x, Y_AXIS, Position.z + 2.0f), BALL_TYPE::HEALTH); }
#endif
		}

		//クールダウンの処理
		{
			float colorChange1 = (1.0f - (((float)stop.Counter / (float)stop.CounterMax)));
			stop.meter.Color = D3DXCOLOR(1.0f, colorChange1, colorChange1, 1.0f);
			if (stop.CoolDownBool == true && stop.UseBool == false && GetPause() == false)
			{
				stop.CoolDownTimer -= (int)(1.0f / (float)GetSlowNum());
				float colorChange = (1.0f - (((float)stop.CoolDownTimer / (float)stop.CoolDownTimerMax)));
				stop.meter.Color = D3DXCOLOR(1.0f, colorChange, colorChange, 1.0f);
				if (stop.CoolDownTimer <= 0)
				{
					stop.meter.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					stop.CoolDownBool = false;
					stop.CoolDownTimer = stop.CoolDownTimerMax;
					PlayReadSound(SE_COOLDOWN_FINISH, SE);
				}
			}

			if (stop.UseBool == false)
			{
				float colorChange2 = (1.0f - ((float)slow.Counter / (float)slow.CounterMax));
				slow.meter.Color = D3DXCOLOR(1.0f, colorChange2, colorChange2, 1.0f);

				if (slow.CoolDownBool == true && slow.UseBool == false && GetPause() == false)
				{
					slow.CoolDownTimer--;
					float colorChange = (1.0f - ((float)slow.CoolDownTimer / (float)slow.CoolDownTimerMax));
					slow.meter.Color = D3DXCOLOR(1.0f, colorChange, colorChange, 1.0f);
					if (slow.CoolDownTimer <= 0)
					{
						slow.meter.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						slow.CoolDownBool = false;
						slow.CoolDownTimer = slow.CoolDownTimerMax;
						PlayReadSound(SE_COOLDOWN_FINISH, SE);
					}
				}
			}
		}

		//回転の処理
		if(GetKeyBoardBool() == true)
		{
			float rot = (RotationDirection.y - Rotation.y);	//回転角度の差分
			float rotX = (RotationDirection.x - Rotation.x);
			if (rot > 90) { rot = rot - 360; }
			if (rot < -90) { rot = rot + 360; }

			if (fabs(rot) < D3DXToRadian(2)) { Rotation.y = RotationDirection.y; }
			else { Rotation.y += rot * 0.3f; }

			if (fabs(rotX) < D3DXToRadian(2)) { Rotation.x = RotationDirection.x; }
			else { Rotation.x += rotX * 0.3f; }
		}
		else
		{
			float rot = (RotationDirection.y - Rotation.y);	//回転角度の差分
			float rotX = (RotationDirection.x - Rotation.x);
			if (rot > 90) { rot = rot - 360; }
			if (rot < -90) { rot = rot + 360; }

			if (fabs(rot) < D3DXToRadian(2)) { Rotation.y = RotationDirection.y; }
			else { Rotation.y += rot * 0.3f; }
			if (fabs(rotX) < D3DXToRadian(2)) { Rotation.x = RotationDirection.x; }
			else { Rotation.x += rotX * 0.3f; }
		}

		//移動処理
		{
			//if (boundX == false)
			{
				Position.x += PlayerMoveSpeed.x;
				Position.y += PlayerMoveSpeed.y;
				Position.z += PlayerMoveSpeed.z;
			}
			if (death == false && deathEffect == false && ((!GetKeyboardTrigger(DIK_UP) && !GetKeyboardTrigger(DIK_DOWN) && !GetKeyboardTrigger(DIK_RIGHT) && !GetKeyboardTrigger(DIK_LEFT))||(fabs(GetStickL().x) <= 0.01f && fabs(GetStickL().y) <= 0.01f))) 
			{ 
				PlayerMoveSpeed.x *= 0.9f; 
				PlayerMoveSpeed.z *= 0.9f; 
				move = false; 
				moveDiagonal = false; 
				if (rotationFix > 0) { rotationFix--; } 
			}
			//else { PlayerMoveSpeed = MoveInDirection() * Speed; }
		}

		//攻撃のクールダウン処理
		{
			if ((GetKeyboardTrigger(DIK_SPACE) || GetControllerTrigger("A") == true) && attackCoolDown <= 0)
			{
				//Rotation.y += 720;
				attack = true;
				attackCoolDown = 0;
				PlayReadSound(SE_PLAYER_ATTACK, SE);
				//SetBullet(Position, MoveInDirection());
			}
			if (attack == true) { attackCoolDown++; }
			else if (attackCoolDown > 0) { attackCoolDown--; if (GetKeyboardTrigger(DIK_SPACE) || GetControllerTrigger("A") == true) { PlayReadSound(SE_PLAYER_ATTACK_BLOCK, SE); } }
		}

		//カメラの向き
		{
			D3DXVECTOR2 look = GetStickR();
			D3DXVECTOR3 at = D3DXVECTOR3(Position.x + look.x*3, 0.7f + 0.5f + look.y*2, Position.z);
			SetCameraATDelay(at);
		}
		

		//影の更新処理
		{
			Shadow.Update();
			Shadow.SetPosition(D3DXVECTOR3(Position.x, SHADOW_ERROR, Position.z));
		}
	}

#ifdef DEBUG	// デバッグ情報を表示する
	char* str = GetDebugStr();
	sprintf(&str[strlen(str)], "     Number : %d", enemyCloseNum);
	sprintf(&str[strlen(str)], "     Defeated : %d", defeated);
	sprintf(&str[strlen(str)], "     Camera | X : %.2f - Y : %.2f - Z : %.2f |", GetCamera()->pos.x, GetCamera()->pos.y, GetCamera()->pos.z);
	//sprintf(&str[strlen(str)], "     R_D.y : %.2f, Rotation.y : %.2f", RotationDirection.y, Rotation.y);
	//sprintf(&str[strlen(str)], "     X : %.2f, Y : %.2f", GetStickL().x, GetStickL().y);
	//sprintf(&str[strlen(str)], "     PlayerMoveSpeed.x : %.2f", PlayerMoveSpeed.x);
	//sprintf(&str[strlen(str)], "     HP : %d", hp);
	//sprintf(&str[strlen(str)], "     HP.left : %.2f", HP.left);
	//sprintf(&str[strlen(str)], "     P Rot Y : %.2f", Rotation.y);
	//sprintf(&str[strlen(str)], "     ENEMY DISTANCE : %.2f", DistanceFrom(GetEnemy()));
	//sprintf(&str[strlen(str)], " rotY:%.2f", Rotation.y);
	//sprintf(&str[strlen(str)], " Stop.CoolDownTimer : %d, Stop.CoolDownBool : %d", stop.CoolDownTimer, stop.CoolDownBool);
	//sprintf(&str[strlen(str)], "     HP : %d", hp);
	//sprintf(&str[strlen(str)], "     AttackCoolDown : %d", attackCoolDown);
	//sprintf(&str[strlen(str)], "     attack : %d", attack);
	//sprintf(&str[strlen(str)], "     experience : %d", experience);
	//sprintf(&str[strlen(str)], "     experienceMax : %d", experienceMax);
	//sprintf(&str[strlen(str)], "     Position.x : %.2f, Position.y : %.2f, Position.z : %.2f", Position.x, Position.y, Position.z);
	//sprintf(&str[strlen(str)], "     Speed : %.2f", Speed);
#endif
}
