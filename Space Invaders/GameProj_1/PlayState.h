#pragma once
#include "BaseState.h"
#include "Cell.h"
#include "SoundSystem.h"
#define numOfObjects 2

class Base;
class PlayState :
	public BaseState
{
	//Base** baseObj;
	//static vector<Base*> baseObj;
	static DList<Base*> baseObj;

	Cell<int, char> *cellText;
	int noOfCells;
	FMOD::Channel *channel;
	bool bitwiseSwitch;
public:
	PlayState();
	~PlayState();

	void Input();
	void Update(int _frame);
	void Render() const;

	void Enter();
	void Exit();
	void Init();

	void UserChoice();
	//static vector<Base*>& GetObjects() { return baseObj; }
	static DList<Base*> & GetObjects() {
		return baseObj;
	}
};
