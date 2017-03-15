#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "Missile.h"
#include "PlayState.h"

Player::Player(ConsoleColor _fg, ConsoleColor _bg, const char* const _text, int _score, int _diff, const char* const _name) : Base(_fg, _bg, _text)
{
	//nameOfThePlayer = NULL;
	SetID(PLAYER);
	SetScore(_score);
	SetDiff(_diff);
	SetName(_name);

	SetAlive(true);
}

Player::Player(Player const& _obj) : Base(_obj)
{
	SetID(PLAYER);
	//nameOfThePlayer = NULL;
	SetScore(_obj.score);
	SetDiff(_obj.difficultyLevel);
	SetName(_obj.nameOfThePlayer.c_str());
}
Player& Player::operator=(Player const& _obj) 
{
	if (this != &_obj)
	{
		Base::operator=(_obj);

		SetScore(_obj.score);
		SetDiff(_obj.difficultyLevel);
		SetName(_obj.nameOfThePlayer.c_str());
	}
	return *this;
}
Player::Player()
{
	
}


Player::~Player()
{
	
}

void Player::Input(DList<Base*> &baseObj)
{
	int dx, dy;
	dx = dy = 0;

	//if (GetAsyncKeyState('W')) dy = -1;
	if (GetAsyncKeyState('A')) dx = -1;
	//if (GetAsyncKeyState('S')) dy = 1;
	if (GetAsyncKeyState('D')) dx = 1;

	if (dx || dy)
	{
		//movement code
		int newX = GetX() + dx;
		//int newY = GetY() + dy;//use get y
		for (int i = 0; i < 2; i++)
		{
			if (baseObj[i] != this)
			{
				if (newX > baseObj[i]->GetX() + baseObj[i]->GetWidth() || GetY() > baseObj[i]->GetY() + baseObj[i]->GetHeight() || baseObj[i]->GetX() > newX + GetWidth() || baseObj[i]->GetY() > GetY() + GetHeight())
				{
					continue;
				}
				else
				{
					return;
				}
			}
		}
		
		/*if (newX >= 0 && newX + GetWidth() < Console::WindowWidth())
			SetX(newX);
		if (newY >= 1 && newY + GetHeight() < Console::WindowHeight())
			SetY(newY);*/
		if (!CollidesBoundary(newX, GetY(),GetWidth(), GetHeight()))
		{
			SetX(newX);
			//SetY(newY);
		}
	}
	
	//Shooting the missiles

	if (GetAsyncKeyState(VK_NUMPAD8))
	{
		Missile* m = new Missile();
		m->SetVelocity(0, -1);
		m->SetX(GetX() + GetWidth()/2);
		m->SetY(GetY() + GetHeight()/2);
		m->SetHoming(false);
		m->SetAlive(true);
		m->SetOwner(this);
		

		//Another Way
		/*vector<Base*>& temp = PlayState::GetObjects();
		temp.push_back(m);*/

		PlayState::GetObjects().push_back(m);
	}

	if (GetAsyncKeyState(VK_NUMPAD7))
	{
		Missile* m = new Missile();
		m->SetVelocity(-1, -1);
		m->SetX(GetX() + 1);
		m->SetY(GetY());
		m->SetHoming(false);
		m->SetAlive(true);
		m->SetOwner(this);
		
		PlayState::GetObjects().push_back(m);
	}

	if (GetAsyncKeyState(VK_NUMPAD9))
	{
		Missile *m = new Missile();
		m->SetVelocity(1, -1);
		m->SetX(GetX() + GetWidth());
		m->SetY(GetY());
		m->SetHoming(false);
		m->SetAlive(true);
		m->SetOwner(this);
		
		PlayState::GetObjects().push_back(m);
	}
	if (GetAsyncKeyState(VK_NUMPAD6) )
	{
		Missile *m = new Missile();
		m->SetVelocity(1, 0);
		m->SetX(GetX() + 1);
		m->SetY(GetY());
		m->SetHoming(false);
		m->SetAlive(true);
		m->SetOwner(this);
		

		PlayState::GetObjects().push_back(m);
	}

	if (GetAsyncKeyState(VK_NUMPAD4))
	{
		Missile *m = new Missile;
		m->SetVelocity(1, 0);
		m->SetX(GetX() + 1);
		m->SetY(GetY());
		m->SetHoming(true);
		m->SetAlive(true);
		m->SetOwner(this);
		
		PlayState::GetObjects().push_back(m);
	}

	if (GetAsyncKeyState(VK_NUMPAD5))
	{
		Missile*m1 = new Missile();
		Missile*m2 = new Missile();
		Missile*m3 = new Missile();
		Missile*m4 = new Missile();
		Missile*m5 = new Missile();
		Missile*m6 = new Missile();
		Missile*m7 = new Missile();
		Missile*m8 = new Missile();

		//Up
		m1->SetVelocity(0, -1);
		m1->SetHoming(false);
		m1->SetX(GetX() + GetWidth()/2);
		m1->SetY(GetY());
		m1->SetAlive(true);
		m1->SetOwner(this);

		//Up right
		m2->SetVelocity(1, -1);
		m2->SetHoming(false);
		m2->SetX(GetX() + GetWidth());
		m2->SetY(GetY());
		m2->SetAlive(true);
		m2->SetOwner(this);

		//Up left
		m3->SetVelocity(-1, -1);
		m3->SetHoming(false);
		m3->SetX(GetX());
		m3->SetY(GetY());
		m3->SetAlive(true);
		m3->SetOwner(this);

		//Left
		m4->SetVelocity(-1, 0);
		m4->SetHoming(false);
		m4->SetX(GetX());
		m4->SetY(GetY() + GetHeight()/2);
		m4->SetAlive(true);
		m4->SetOwner(this);

		//Right
		m5->SetVelocity(1, 0);
		m5->SetHoming(false);
		m5->SetX(GetX() + GetWidth());
		m5->SetY(GetY() + GetHeight()/2);
		m5->SetAlive(true);
		m5->SetOwner(this);

		//Down left
		m6->SetVelocity(-1, 1);
		m6->SetHoming(false);
		m6->SetX(GetX());
		m6->SetY(GetY() + GetHeight());
		m6->SetAlive(true);
		m6->SetOwner(this);

		//Down
		m7->SetVelocity(0, 1);
		m7->SetHoming(false);
		m7->SetX(GetX() >> 2);
		m7->SetY(GetY() + GetHeight());
		m7->SetAlive(true);
		m7->SetOwner(this);

		//Down right
		m8->SetVelocity(1, 1);
		m8->SetHoming(false);
		m8->SetX(GetX() + GetWidth());
		m8->SetY(GetY() + GetHeight());
		m8->SetAlive(true);
		m8->SetOwner(this);

		PlayState::GetObjects().push_back(m1);
		PlayState::GetObjects().push_back(m2);
		PlayState::GetObjects().push_back(m3);
		PlayState::GetObjects().push_back(m4);
		PlayState::GetObjects().push_back(m5);
		PlayState::GetObjects().push_back(m6);
		PlayState::GetObjects().push_back(m7);
		PlayState::GetObjects().push_back(m8);

	}

}

void Player::Update(int _frame)
{
	if (Game::GetCheats() & POINTS_BIT)
	{
		SetScore(GetScore() + 20);
	}
}

void Player::Render() const
{
	Console::SetCursorPosition(0, 0);
	Console::ForegroundColor(ConsoleColor::Magenta);
	cout << "Name: " << nameOfThePlayer;

	Console::SetCursorPosition((Console::WindowWidth() >> 1) - 45, 0);
	Console::ForegroundColor(ConsoleColor::Cyan); cout << "Score: " << score;

	Console::SetCursorPosition(Console::WindowWidth() - 85, 0);
	Console::ForegroundColor(ConsoleColor::Yellow);
	cout << "Diff: " << difficultyLevel;
	
	Console::SetCursorPosition(Console::WindowWidth() - 48, 0);
	Console::ForegroundColor(ConsoleColor::Green);
	cout << "LifeCount: ";
	for (int i = 0; i < LifeCount; i++)
	{
		Console::ForegroundColor(ConsoleColor::Red);
		cout << '\x3';
	}
	Console::SetCursorPosition(Console::WindowWidth() - 18, 0);
	Console::ForegroundColor(ConsoleColor::Cyan);
	cout << "HP: " << HealthCount;
	Base::Render();
}