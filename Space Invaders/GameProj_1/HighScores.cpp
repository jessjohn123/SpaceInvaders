#include "stdafx.h"
#include "HighScores.h"
#include "Game.h"
#include "PlayState.h"
#include "MenuState.h"
#include "Player.h"


HighScores::HighScores()
{
}


HighScores::~HighScores()
{
	
}

//sorting predicate
bool AlphasortAscend(PlayerInfo& a, PlayerInfo& b)
{
	if (_stricmp(a.name, b.name) < 0)
		return true;
	else
		return false;
}

// Adding other predicates(takes in n number of parameters and returns a bool)
bool AlphasortDescend(PlayerInfo& a, PlayerInfo& b)
{
	if (_stricmp(a.name, b.name) > 0)
		return true;

	return false;
}

bool NumberDescend(PlayerInfo& a, PlayerInfo& b)
{
	return a.score > b.score;
}

bool diffDescend(PlayerInfo& a, PlayerInfo& b)
{
	return a.diff > b.diff;
}

//Display function
void DisplayScore(PlayerInfo& _score)
{
	cout << _score.name << "\tscored " << _score.score << "\ton difficulty " << _score.diff << '\n';
}

void HighScores::Exit()
{

}

void HighScores::Init()
{
	numHighScoreMenu = 7;
	//highScoreText = new char*[numHighScoreMenu];

	strcpy_s(highScoreText[0], 128, "Victory list of our LifeSavers in (Ascending Order)");
	strcpy_s(highScoreText[1], 128, "Victory list of our LifeSavers in(Descending Order)" );
	strcpy_s(highScoreText[2], 128, "Tough Combat(HighScores)");
	strcpy_s(highScoreText[3], 128, "Levels of Battle(Difficulty levels)");
	strcpy_s(highScoreText[4], 128, "Best of All Time");
	strcpy_s(highScoreText[5], 128, "Save To Text" );
	strcpy_s(highScoreText[6], 128, "Return To Main Menu");

	highScoreNum = 0;
}

void HighScores::Enter()
{
	//Display all my highscores
	fstream bin;
	bin.open("scores.bin", ios_base::binary | ios_base::in | ios_base::out);

	//Read in all the scores from a binary file
	if (bin.is_open())
	{
		bin.seekg(0, ios_base::end);
		int count = (int)bin.tellg();
		bin.seekg(0, ios_base::beg);

		count /= sizeof(PlayerInfo);

		GamePlayData.resize(count);
		for (int i = 0; i < count; i++)
		{
			bin.read((char*)&GamePlayData[i], sizeof(PlayerInfo));
		}

		bin.close();
	}

	fstream bout;
	bout.open("scores.bin", ios_base::binary | ios_base::out | ios_base::trunc);

	//Read in all the scores from a binary file
	if (bout.is_open())
	{
		for (int i = 0; i < (int)GamePlayData.size(); i++)
		{
			bout.write((char*)&GamePlayData[i], sizeof(PlayerInfo));
		}
		bout.close();
	}
	//declaring data for high-score stats(min, max, average)
	int sum = 0;
	int sumDiff = 0;
	unsigned int i = 0;
	maxScore = GamePlayData[0].score;
	maxDiff = GamePlayData[0].diff;
	minScore = GamePlayData[0].score;
	minDiff = GamePlayData[0].diff;
	
	
	for (; i < GamePlayData.size(); i++)
	{
		sum += GamePlayData[i].score;
		sumDiff += GamePlayData[i].diff;
	}
	avgScore = sum / GamePlayData.size();
	avgDiff = sumDiff / GamePlayData.size();
	for (; i < GamePlayData.size(); i++)
	{
		if (GamePlayData[i].score > maxScore)
		{
			maxScore = GamePlayData[i].score;
		}
		if (GamePlayData[i].score < minScore)
		{
			minScore = GamePlayData[i].score;
		}
		if (GamePlayData[i].diff > maxDiff)
		{
			maxDiff = GamePlayData[i].diff;
		}
		if (GamePlayData[i].diff < minDiff)
		{
			minDiff = GamePlayData[i].diff;
		}
	}
}

void HighScores::Input()
{
	if (GetAsyncKeyState('W') && !BaseState::GetkeyPressed())
	{
		--highScoreNum;
		if (highScoreNum < 0)
		{
			highScoreNum = numHighScoreMenu - 1;
		}
		BaseState::SetkeyPressed(true);
	}
	if (GetAsyncKeyState('S') && !BaseState::GetkeyPressed())
	{
		++highScoreNum;
		if (highScoreNum >= numHighScoreMenu)
		{
			highScoreNum = 0;
		}

		BaseState::SetkeyPressed(true);
	}
	if (GetAsyncKeyState(VK_RETURN) && highScoreNum == 6 && !BaseState::GetkeyPressed())
	{
		BaseState::SetkeyPressed(true);
		Game::ChangeState(MENU_STATE);

	}

	//bunch of predicate sorts
	if (GetAsyncKeyState(VK_RETURN) && highScoreNum == 0 && !BaseState::GetkeyPressed())
	{
		BaseState::SetkeyPressed(true);
		Console::Clear();

		sort(GamePlayData.begin(), GamePlayData.end(), AlphasortAscend);
		for_each(GamePlayData.begin(), GamePlayData.end(), DisplayScore);
		cout << endl;
		Console::FlushKeys();
		system("pause");
	}

	if (GetAsyncKeyState(VK_RETURN) && highScoreNum == 1 && !BaseState::GetkeyPressed())
	{
		BaseState::SetkeyPressed(true);
		Console::Clear();

		sort(GamePlayData.begin(), GamePlayData.end(), AlphasortDescend);
		for_each(GamePlayData.begin(), GamePlayData.end(), DisplayScore);
		cout << endl;
		Console::FlushKeys();
		system("pause");
	}

	if (GetAsyncKeyState(VK_RETURN) && highScoreNum == 2 && !BaseState::GetkeyPressed())
	{
		BaseState::SetkeyPressed(true);
		Console::Clear();

		sort(GamePlayData.begin(), GamePlayData.end(), NumberDescend);
		for_each(GamePlayData.begin(), GamePlayData.end(), DisplayScore);
		Console::FlushKeys();
		system("pause");
	}

	if (GetAsyncKeyState(VK_RETURN) && highScoreNum == 3 && !BaseState::GetkeyPressed())
	{
		BaseState::SetkeyPressed(true);
		Console::Clear();

		sort(GamePlayData.begin(), GamePlayData.end(), diffDescend);
		_For_each(GamePlayData.begin(), GamePlayData.end(), DisplayScore);
		cout << endl;
		Console::FlushKeys();
		system("pause");
	}

	if (GetAsyncKeyState(VK_RETURN) && highScoreNum == 4 && !BaseState::GetkeyPressed())
	{
		BaseState::SetkeyPressed(true);
		Console::Clear();

		cout << "Maxium Score of Alltime: " << maxScore << endl;
		cout << "Minimum Score of Alltime:" << minScore << endl;
		cout << "Average Score of Alltime:" << avgScore << endl;
		cout << "Maxium Difficulty of Alltime: " << maxDiff << endl;
		cout << "Minimum Difficulty of Alltime:" << minDiff << endl;
		cout << "Average Difficulty of Alltime:" << avgDiff << endl;
		cout << endl;
		Console::FlushKeys();
		system("pause");

	}

	if (GetAsyncKeyState(VK_RETURN) && highScoreNum == 5 && !BaseState::GetkeyPressed())
	{
		BaseState::SetkeyPressed(true);
		Console::Clear();
		Console::FlushKeys();

		cout << "What file name would like to save in ?" << endl;
		string userInput;
		cin >> userInput;
		userInput.append(".txt");

		for (;;)
		{
			cout << "How many entries of score would you like to save ?" << endl;
			int userEntries;
			cin >> userEntries;
			if (userEntries >= 1 && userEntries < (int)GamePlayData.size())
			{
				GamePlayData.resize(userEntries);
				break;
			}
			else
			{
				cout << "Invalid Input :(" << endl;
				cin.clear();
				cin.sync();
			}
		}

		fstream fout;
		fout.open(userInput, ios_base::out);

		if (fout.is_open())
		{
			for (unsigned int i = 0; i < GamePlayData.size(); i++)
			{
				fout << GamePlayData[i].name << '\t' << GamePlayData[i].diff << '\t' << GamePlayData[i].score << '\n';
			}
			fout.close();
		}
		cout << endl;
		Console::FlushKeys();
		system("pause");
	}
}

void HighScores::Update(int _frame)
{
	if (!GetAsyncKeyState(VK_RETURN) && !GetAsyncKeyState('W') && !GetAsyncKeyState('S'))
	{
		BaseState::SetkeyPressed(false);
	}
	
}


void HighScores::Render() const
{
	int i = 0;
	for (; i < numHighScoreMenu; ++i)
	{

		if (highScoreNum == i)
		{
			Console::SetCursorPosition((Console::WindowWidth() >> 1) - 5, ((Console::WindowHeight() >> 1) - 4) + i);

			Console::ForegroundColor(Green);
			cout << "---->";
			Console::ResetColor();
		}
		else
			Console::SetCursorPosition(Console::WindowWidth() >> 1, ((Console::WindowHeight() >> 1) - 4) + i);


		cout << highScoreText[i] << '\n';
	}
}