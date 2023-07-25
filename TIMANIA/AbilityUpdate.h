#pragma once
#include "player.h"
#include "Abilities.h"

#define LEVELUP_PERCENTAGE 0.1f
#define HP_ADD 10

PLAYER* setPlayer;
void SetAbility(int value)
{
	setPlayer = GetPlayer();
	setPlayer->GainHealth(20);
	
	if		(value == LEVELUP::HP_UP) { setPlayer->hpMax += setPlayer->hpMax / 10; setPlayer->GainHealth(setPlayer->hpMax / 10); }
	else if (value == LEVELUP::EXPERIENCE_UP) { setPlayer->experienceAmount += 2; }
	else if (value == LEVELUP::MOVEMENT_SPEED_UP) { setPlayer->SetSpeed(setPlayer->GetSpeed() + setPlayer->PlayerSpeed * LEVELUP_PERCENTAGE); }
	else if (value == LEVELUP::ATTACK_COOLDOWN_DOWN) { setPlayer->attackCoolDownMax -= setPlayer->AttackCoolDown * LEVELUP_PERCENTAGE; }
	else if (value == LEVELUP::ATTACK_RANGE_UP) { setPlayer->range += setPlayer->AttackRange * LEVELUP_PERCENTAGE; }
	else if (value == LEVELUP::ATTACK_KNOCKBACK_UP) { setPlayer->attackKnockBack += setPlayer->AttackKnockBack * LEVELUP_PERCENTAGE; }
	else if (value == LEVELUP::STOP_COOLDOWN_DOWN) { setPlayer->stop.CoolDownTimerMax -= setPlayer->StopCoolDown * LEVELUP_PERCENTAGE; }
	else if (value == LEVELUP::SLOW_COOLDOWN_DOWN) { setPlayer->slow.CoolDownTimerMax -= setPlayer->SlowCoolDowm * LEVELUP_PERCENTAGE; }
	else if (value == LEVELUP::STOP_TIME_UP) { setPlayer->stop.CounterMax += setPlayer->StopTime * LEVELUP_PERCENTAGE; }
	else if (value == LEVELUP::SLOW_TIME_UP) { setPlayer->slow.CounterMax += setPlayer->SlowTime * LEVELUP_PERCENTAGE; }

}