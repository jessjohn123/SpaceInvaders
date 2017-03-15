#include "stdafx.h"
#include "Missile.h"
#include "Player.h"
#include "Game.h"
#include "PlayState.h"

Missile::Missile()
{
	SetText("#");
	SetFG(ConsoleColor::White);

	velVec.resize(2);
	velVec[0] = 0;
	velVec[1] = 0;

	SetAlive(false);
}


Missile::~Missile()
{
}

void Missile::Input()
{

}

void Missile::Update(int _frame)
{
	if (GetAlive())
	{
		int newX = GetX() + velX;
		int newY = GetY() + velY;

		if (is_homing)
		{
			SetTarget(PlayState::GetObjects()[1]);
			if (GetX() < target->GetX())
				velX = 1;
			else
				velX = -1;
			if (GetY() < target->GetY())
				velY = 1;
			else
				velY = -1;
		}

		if (Collides())
			return;

		/*if (newX >= 0 && newX < Console::WindowWidth())
			SetX(newX);
		else
			SetAlive(false);
		if (newY >= 0 && newY < Console::WindowHeight())
			SetY(newY);
		else*/
		if (CollidesBoundary(newX, newY, 0, 0))
		{
			SetAlive(false);
		}
		else
		{
			SetX(newX);
			SetY(newY);
		}
			
	}
}

void Missile::Render() const
{
	if (GetAlive())
		Base::Render();
}

bool Missile::Collides()
{
	/*if (GetX() >= target->GetX() && GetX() <= target->GetX() + 50)
		if (GetY() == target->GetY())
		{
		SetAlive(false);
		owner->SetScore(owner->GetScore() + 50);
		return true;
		}
	return false; */

	//vector<Base*>& temp = PlayState::GetObjects();
	DList<Base*> &temp = PlayState::GetObjects();

	int i = 0;
	for (; i < temp.size(); i++)
	{
		Base* t = temp[i];

		if ((Game::GetCheats() & GHOST_BIT) && this->owner->GetID() == ENEMY)
		{
			continue;
		}
		if (t->GetID() == MISSILE || t->GetID() == ENEMY_MISSILE)
			continue;

		if (t == this->owner)
			continue;

		if (GetX() > t->GetX() + t->GetWidth() || GetX() + GetWidth() <= t->GetX() ||
			GetY() > t->GetY() + t->GetHeight() || GetY() + GetHeight() < t->GetY())
			continue;
		else
		{
			SetAlive(false);
			if (t->GetID() == ENEMY)
			{
				//vector<Base*> search = PlayState::GetObjects();
				DList<Base*> &search = PlayState::GetObjects();
				for (int x = 0; x < search.size(); ++x)
				{
					if (search[x]->GetID() == PLAYER)
						dynamic_cast<Player*>(search[x])->SetScore(dynamic_cast<Player*>(search[x])->GetScore() + 50);
				}
			}

			else
			{
				if (t->GetID() == PLAYER)
				{
					Player * x = dynamic_cast<Player*>(t);

					x->SetHealth(-1);

					if (x->GetHealth() < 0)
					{
						x->SetLife(1);
						x->SetHealth(10);

						if (x->GetLife() <= 0)
						{
							Game::ChangeState(MENU_STATE);
						}
					}
				}

			}
			
		}
		return true;
	}
	return false;
}