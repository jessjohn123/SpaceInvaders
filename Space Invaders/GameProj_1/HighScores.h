#pragma once
#include "BaseState.h"
#include "Game.h"
#include "Player.h"
class HighScores : public BaseState
{
private:
	int maxScore,minScore, maxDiff, minDiff;
	float avgScore;
	float avgDiff;
	vector<PlayerInfo> GamePlayData;
	char highScoreText[7][128];
	int highScoreNum, numHighScoreMenu;
public:
	HighScores();
	~HighScores();

	void Input();
	void Update(int _frame);
	void Render() const;
	void Enter();
	void Exit();
	void Init();
};

