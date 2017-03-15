#pragma once
#include "BaseState.h"
#include "SoundSystem.h"
class MenuState :
	public BaseState
{
private:
	bool keyPress = false;
	char** menuList;
	int menuNum, numMenuItems;
public:
	MenuState();
	~MenuState();

	void Input();
	void Update(int _frame);
	void Render() const;
	void GameInfo();
	void Enter();
	void Exit();
	void Init();
};

