#pragma once

class BaseState;

enum STATE_IDS { MENU_STATE, PLAY_STATE, HIGH_SCORE, MAX_STATES};

#define ALIVE_BIT 1 << 0
#define MOVE_BIT 1 << 1
#define POINTS_BIT 1 << 2
#define GHOST_BIT 1 << 3
#define SHOOT_BIT 1 << 4

class Game 
{
private:
	static BaseState* currentState;
	static BaseState** states;
	static char cheats;
	int frame = 0;
	static bool play;
public:
	Game();
	~Game();
	void Play();

	void Input();
	void Update(int _frame);
	void Render() const;

	static void ChangeState(STATE_IDS state);
	static void SetPlay(bool _play);
	static const char GetCheats() { return cheats; }
};

