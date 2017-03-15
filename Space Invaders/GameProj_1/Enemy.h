#pragma once
#include "Base.h"
class Enemy :
	public Base
{
private:
	int speed = 5;
	static int moveDir;
	bool check = true;
public:
	Enemy(ConsoleColor _fg, ConsoleColor _bg, const char* const _text);
	Enemy();
	~Enemy();

	//void Input(vector<Base*>baseObj);
	void Input(DList<Base*> &baseObj);
	void Update(int _frame);
	void Render() const;
	void ShotToPlayer(int _frame);
};

