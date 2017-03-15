#include "stdafx.h"
#include "Enemy.h"
#include "Missile.h"
#include "Game.h"
#include "PlayState.h"

int Enemy::moveDir = 1;

Enemy::Enemy(ConsoleColor _fg, ConsoleColor _bg, const char* _text) : Base(_fg, _bg, _text)
{

}

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::Input(DList<Base*> &baseObj)
{
	int newX = GetX() + moveDir;
	for (int i = 0; i < 2; i++)
	{
		if (baseObj[i] != this)
		{
			if (newX > baseObj[i]->GetX() + baseObj[i]->GetWidth() || GetY() > baseObj[i]->GetY() + baseObj[i]->GetHeight() || baseObj[i]->GetX() > newX + GetWidth() || baseObj[i]->GetY() > GetY() + GetHeight())
				continue;
			else
			{
				check = false;
				return;
			}
		}
	}
	check = true;

	/*if (newX < 0 || newX > Console::WindowWidth() - GetWidth() - 1)
		moveDir = -moveDir;*/

	if (CollidesBoundary(newX, GetY(), GetWidth(), GetHeight()))
		moveDir = -moveDir;
}
void Enemy::Update(int _frame)
{
	if (!(Game::GetCheats() & MOVE_BIT))
	{
		if (_frame % speed == 0 && check)
		{
			/*if (GetX() < 0 || GetX() + GetWidth() > Console::WindowWidth())
				moveDir = -moveDir;*/
			SetX(GetX() + moveDir);
		}
	}
}

void Enemy::Render() const
{
	Base::Render();
}

void Enemy::ShotToPlayer(int _frame)
{
	if (!(Game::GetCheats() & SHOOT_BIT))
	{
		if (_frame % 8 == 0)
		{
			Missile* m = new Missile();
			m->SetVelocity(0, 1);
			m->SetHoming(false);
			m->SetTarget(PlayState::GetObjects()[0]);
			m->SetOwner(this);
			m->SetX(GetX() + (GetWidth() >> 1));
			m->SetY(GetY());
			m->SetAlive(true);
			m->SetID(ENEMY_MISSILE);

			PlayState::GetObjects().push_back(m);
		}
	}
}