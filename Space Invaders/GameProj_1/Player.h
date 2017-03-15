#pragma once
#include "Base.h"

class Missile;

struct PlayerInfo
{
	int score, diff;
	char name[32];
};
class Player :
	public Base
{
private:
	string nameOfThePlayer;
	int score;
	int difficultyLevel;
	int LifeCount = 3;
	int HealthCount = 10;
	//Missile *m;
	
public:
	Player(ConsoleColor _fg, ConsoleColor _bg, const char* const _text, int _score, int _diff, const char* const _name);
	Player(Player const& _obj);
	Player& operator=(Player const& _obj);
	Player();
	~Player();

	//Accessors
	int GetScore() const { return score; }
	int GetDiff() const { return difficultyLevel; }
	const char* const GetName() const { return nameOfThePlayer.c_str(); }
	int GetLife() const { return LifeCount; }
	int GetHealth() const { return HealthCount; }
	//Mutators
	void SetScore(int _score) { score = _score; }
	void SetDiff(int _diff) { difficultyLevel = _diff; }
	void SetName(const char* const _name) { nameOfThePlayer = _name; }
	void SetLife(int _lifeCount) { LifeCount -= _lifeCount; }
	void SetHealth(int _healthCount) { HealthCount += _healthCount; }
	//void SetMissile(Missile* _m) { m = _m; }
	//void Input(vector<Base*>baseObj);
	void Input(DList<Base*> &baseObj);
	void Update(int _frame);
	void Render() const;
};

