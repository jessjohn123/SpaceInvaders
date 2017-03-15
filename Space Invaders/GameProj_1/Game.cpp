#include "stdafx.h"
#include "Game.h"
#include "MenuState.h"
#include "PlayState.h"
#include "Cell.h"
#include "Player.h"
#include "HighScores.h"

BaseState* Game::currentState;
BaseState** Game::states;
char Game::cheats = 1;

bool Game::play = true;

void Game::SetPlay(bool _play)
{
	if (_play)
	{
		cheats |= ALIVE_BIT;
	}
	else
	{
		cheats &= ~ALIVE_BIT;
	}
}

Game::Game()
{
	states = new BaseState *[MAX_STATES];
	states[MENU_STATE] = new MenuState();
	states[PLAY_STATE] = new PlayState();
	states[HIGH_SCORE] = new HighScores();
	int i = 0;
	for (; i < MAX_STATES; i++)
	{
		states[i]->Init();
	}
	currentState = states[MENU_STATE];
}


Game::~Game()
{
	
	int i = 0;
	for (; i < MAX_STATES; i++)
	{
		delete states[i];
	}
	delete[] states;
	
}

void Game::Play()
{
#if 0
#pragma region Init Code
	card = new Base("          ,-----.         \n 		',_/_|_\\_.'       \n   /<<::8[0]::>\\      \n __|-----------|__     \n ::|  |  ====-=-  |  |::  \n ::|  |  ====-=-  |  |::  \n ::\\  |   ::::|()||  /:: \n ::| |   ....|()|| |::  \n | |___________| |    \n | |\\_________/| |    \n /  \\  /  \\   /  \\   \n `---'  `---'   `---'   \n", (ConsoleColor)12, (ConsoleColor)15);
	Base* dice;
	dice = new Base("           _,--=--._             \n ,'    _    `.           \n -    _(_)_o   -          \n ____'    /_  _/]    `____     \n ===::(+):::::::::::::::::(+)::===\n (+).""""""""""""",(+)     \n .           ,          \n `  -=-  '             \n", (ConsoleColor)0, (ConsoleColor)15);
		int temp1 = strlen("+---+\n|A  |\n| H |\n|  A|\n+---+");
	//cout << card->GetWidth() << " " << card->GetHeight() << "\n\n";
	cout << "Before:\n";
	card->SetX(0);
	card->SetY(1);
	card->Show(); cout << '\n';
	dice->SetX(0);
	dice->SetY(7);

	dice->Show(); cout << '\n';
	Base *temp = card;
	card = dice;
	dice = temp;
	cout << "After:\n";
	card->SetX(0);
	card->SetY(12);
	card->Show(); cout << '\n';
	dice->SetX(0);
	dice->SetY(16);
	dice->Show(); cout << '\n';


	system("pause");
	Base *ship;
	ship = new Base("__            \n | \           \n =[_|H)--._____\n =[+--,-------'\n [|_/""        \n", (ConsoleColor)8, (ConsoleColor)0);
	int userInput;
	system("cls");
	for (;;)
	{
		cout << "How many ships would you like to have?";
		if (cin >> userInput)
		{
			cin.sync();
			break;
		}
		cin.clear();
		cin.sync();
	}



	Base *numofbases = new Base[userInput];


	for (int i = 0; i < userInput; i++)
	{
		numofbases[i].SetWidth(3);
		numofbases[i].SetX(2 * i + i);
		numofbases[i].SetY(2);
		numofbases[i].SetFG((ConsoleColor)8);
		numofbases[i].SetBG((ConsoleColor)0);
		numofbases[i].SetText("|O|");
		numofbases[i].Show();
	}
	cout << "\n\n";
	system("pause");
	int _left = Console::CursorLeft();
	int _top = Console::CursorTop();

	delete[] numofbases;

	Base ** ar = new Base*[3];
	/*ar[0] = card;
	ar[1] = dice;
	ar[2] = ship;*/
#endif
#pragma region Dead Save Code
#if 0
	fstream fout;
	fout.open("save.txt", ios_base::out);

	if (fout.is_open())
	{
		fout << 3 << '\n';
		for (int i = 0; i < 3; i++)
		{
			fout << ar[i]->GetText() << '\t' << ar[i]->GetFG() << '\t' << ar[i]->GetBG() << '\n';
		}
		fout.close();
	}
#endif
#pragma region Dead Read Code
#if 0
	system("cls");

	ifstream fin;
	fin.open("save.txt");

	if (fin.is_open())
	{
		int count = 0;
		int fg, bg;

		char buffer[32];
		fin >> count;
		int i = 0;
		for (; i < count; ++i)
		{
			fin.ignore(INT_MAX, '\n');
			fin.getline(buffer, INT_MAX, '\t');
			fin >> fg >> bg;
			//Base *p = new Base((ConsoleColor)fg, (ConsoleColor)bg, buffer);
			ar[i] = new Base((ConsoleColor)fg, (ConsoleColor)bg, buffer);
			ar[i]->SetX(0);
			ar[i]->SetY(Console::CursorTop() + 2);
			ar[i]->Show();

		}
		char userName[32];
		cin.ignore(INT_MAX, '\n');
		for (;;)
		{
			Console::SetCursorPosition(0, 14);
			cout << "Please enter in your name: ";
			if (cin.get(userName, 32) && strlen(userName) > 3)
			{
				cin.sync();
				break;
			}
			else if (strlen(userName) <= 3)
			{
				strcpy_s(userName, 32, "Player");
				cin.clear();
				cin.sync();
				break;
			}
		}
		int userInput, userInput1;
		for (;;)
		{
			Console::SetCursorPosition(0, 16);
			cout << "What would you like to set as your players?(1-3)";
			if (cin >> userInput && userInput > 3)
			{
				continue;
			}
			else if (userInput > 0 || userInput <= 3)
			{
				break;
			}
		}
		for (;;)
		{
			Console::SetCursorPosition(0, 18);
			cout << "What would you like to set as your enemy?(1-3)";
			if (cin >> userInput1 && userInput1 > 3)
			{
				continue;
			}
			else if (userInput1 > 0 || userInput1 <= 3)
			{
				break;
			}
		}
		baseObj[0] = new Player(ConsoleColor::Blue, ConsoleColor::Yellow, ar[userInput - 1]->GetText(), 0, 100, "Player");
		baseObj[0]->SetX(10);
		baseObj[0]->SetY(Console::WindowHeight() >> 1);

		//Console::SetCursorPosition(0, 16);
		baseObj[1] = new Enemy(ConsoleColor::DarkCyan, ConsoleColor::Red, ar[userInput1 - 1]->GetText());
		baseObj[1]->SetX(Console::WindowWidth() - 10);
		baseObj[1]->SetY(Console::WindowHeight() >> 1);
		system("pause");
#pragma endregion
		fin.close();
		for (int i = 0; i < 3; i++)
		{
			delete ar[i];
		}
		delete dice;
		delete ship;
		delete[] ar;
		delete card;
		temp = NULL;
	}
#endif
	Console::EOLWrap(false);

	for (; cheats & ALIVE_BIT; ++frame)
	{
		Input();
		Update(frame);
		if (play)
			Render();
	}

	Console::EOLWrap(true);
}

void Game::Input()
{
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		play = false;
		cheats &= ~ALIVE_BIT;
		currentState->Exit();
	}
	if (GetAsyncKeyState(VK_F1))
	{
		cheats ^= MOVE_BIT;
	}
	if (GetAsyncKeyState(VK_F2))
	{
		cheats ^= POINTS_BIT;
	}
	if (GetAsyncKeyState(VK_F3))
	{
		cheats ^= GHOST_BIT;
	}
	if (GetAsyncKeyState(VK_F4))
	{
		cheats ^= SHOOT_BIT;
	}
	currentState->Input();

	if ((cheats & ALIVE_BIT) == 0)
	{
		if (currentState == states[PLAY_STATE])
		{
			cheats = 1;

			currentState = states[MENU_STATE];
			currentState->Enter();
		}
	}
}

void Game::Update(int _frame)
{
	currentState->Update(_frame);
}

void Game::Render() const
{
	Console::Lock(true);
	Console::Clear();

	int i = 7;
	for (; i >= 0; --i)
	{
		cout << ((cheats >> i) & 1);
	}

	currentState->Render();

	Console::Lock(false);
	Sleep(50);

}

void Game::ChangeState(STATE_IDS state)
{
	currentState->Exit();
	currentState = states[state];
	currentState->Enter();
}