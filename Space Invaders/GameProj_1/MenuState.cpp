#include "stdafx.h"
#include "MenuState.h"
#include "Game.h"
#include "SoundSystem.h"


MenuState::MenuState()
{
	menuList = NULL;
}


MenuState::~MenuState()
{
	delete[] menuList;
}

void MenuState::Input()
{
	Console::FlushKeys();
	// Doing some Input
	if (GetAsyncKeyState('W') && !keyPress)
	{
		--menuNum;
		if (menuNum < 0)
		{
			menuNum = numMenuItems - 1;
		}
		keyPress = true;
	}

	if (GetAsyncKeyState('S') && !keyPress)
	{
		++menuNum;
		if (menuNum >= numMenuItems)
		{
			menuNum = 0;
		}
		keyPress = true;
	}

	if (GetAsyncKeyState(VK_RETURN) && !keyPress && menuNum == 0)
	{
		BaseState::SetkeyPressed(true);
		Game::ChangeState(PLAY_STATE);
	}

	if (GetAsyncKeyState(VK_RETURN) && !keyPress && menuNum == 1)
	{
		BaseState::SetkeyPressed(true);
		GameInfo();
	}
	if (GetAsyncKeyState(VK_RETURN) && !keyPress && menuNum == 2)
	{
		BaseState::SetkeyPressed(true);

	}
	if (GetAsyncKeyState(VK_RETURN) && !keyPress && menuNum == 3)
	{
		BaseState::SetkeyPressed(true);
		Game::ChangeState(HIGH_SCORE);
	}
	if (GetAsyncKeyState(VK_RETURN) && !keyPress && menuNum == 4)
	{
	

	}
}

void MenuState::Update(int _frame)
{
	if (!GetAsyncKeyState(VK_RETURN) && !GetAsyncKeyState('W') && !GetAsyncKeyState('S'))
	{
		keyPress = false;
	}

	
}

void MenuState::Render() const
{
	Console::SetCursorPosition(Console::WindowWidth() / 2 - 24, 12);
	cout << "===============================================";
	Console::SetCursorPosition(Console::WindowWidth() / 2 - 24, 14);
	cout << "                  MAIN MENU                    ";
	Console::SetCursorPosition(Console::WindowWidth() / 2 - 24, 16);
	cout << "===============================================";
	int i = 0;
	for (; i < numMenuItems; i++)
	{
		if (menuNum == i)
		{
			Console::SetCursorPosition((Console::WindowWidth() >> 1) - 5, ((Console::WindowHeight() >> 1) - 4) + i);

			Console::ForegroundColor(Green);
			cout << "---->";
			Console::ResetColor();
		}
		else
			Console::SetCursorPosition(Console::WindowWidth() >> 1, ((Console::WindowHeight() >> 1) - 4) + i);
		cout << menuList[i] << '\n';
	}
	Console::SetCursorPosition(Console::WindowWidth() / 2 - 24, 25);
	cout << "==============================================="; 

}

void MenuState::Enter()
{
	menuNum = 0;
	
}

void MenuState::Exit()
{

}

void MenuState::Init()
{
	currentMusic = GAME_SOUND_BEGINNING1;
	channel = SoundSystem::playSound(SoundSystem::soundarr[currentMusic]);

	numMenuItems = 5;
	menuList = new char*[numMenuItems];
	
	//Console::SetCursorPosition((Console::WindowWidth() / 2) - 24, Console::WindowHeight() + 2);
	char textArt[7][60] = { { "__   __  ___   ______    _______  __   __  _______ " },
							{ "|  |_|  ||   | |    _ |  |       ||  |_|  ||   _   |" },
							{ "|       ||   | |   | ||  |   _   ||       ||  |_|  |" },
							{ "|       ||   | |   |_||_ |  | |  ||       ||       |" },
							{ " |     | |   | |    __  ||  |_|  ||       ||       |" },
							{ "|   _   ||   | |   |  | ||       || ||_|| ||   _   |" },
							{ "|__| |__||___| |___|  |_||_______||_|   |_||__| |__|" } };
	

	for (size_t z = 0; z < 50; z++)
	{
		Console::BackgroundColor(Black);
		for (int i = 0; i < 7; i++)
		{

			Console::SetCursorPosition(45, i);
			if (z % 2)
				Console::ForegroundColor(rand() % 14 + 1);
			
			
			for (int j = 0; j < 60; j++)
			{
				cout << textArt[i][j] ;
			}
			//cout << endl;
			//Console::SetCursorPosition(Console::WindowWidth() / 2 - 24, Console::CursorTop());
		}
	}

	char alienArt[17][150] = { { "                   ______                     " },
	                           { "              ,-'          '-,                " },
	                           { "             /  o         o   \\              " },
	                           { "            /    \\       /     \\            " },
	                           { "           /      ) -'- (       \\            " },
	                           { "          /      ( 6   6 )       \\           " },
	                           { "         /        \\  '  /         \\         " },
	                           { "        /          ) = (           \\         " },
	                           { "       /   o   .---' - '---.   o    \\        " },
	                           { "      /    I  /    -     -  \\  I     \\      " },
	                           { "  .--(    (_}y/\\           /\\y{_)     )--.  " },
	                           { " (  '.___ 1\\/__\\_________/__\\/1___.'      )" },
	                           { " \\                                       /   " },
	                           { "  '-.       o O o O o O o O o O      ,-'      " },
	                           { "     '--Y--.__________________.--Y--'         " },
	                           { "        |==.__________________.==|            " },
	                           { "        '==.__________________.=='            " } };

	for (size_t z = 0; z < 30; z++)
	{
	     Console::BackgroundColor(Black);
	     Console::SetCursorPosition(Console::WindowWidth() / 2 - 24, Console::WindowHeight() / 2 - 3);
	
		for (int i = 0; i < 17; i++)
		{
			if (z%2)
				Console::ForegroundColor(rand() % 14 + 1);
			else
				Console::ForegroundColor(White);

			for (int j = 0; j < 150; j++)
			{
				cout << alienArt[i][j];
			}

			Console::ResetColor();
        	Console::SetCursorPosition(Console::WindowWidth() / 2 - 24, Console::CursorTop());
		}
	}

	Sleep(100);
	//system("pause");
	Console::Clear();
	
	menuList[0] = "Battle";
	menuList[1] = "HomeLand Of Xiroma";
	menuList[2] = "Hidden Powers";
	menuList[3] = "Victory of Xiroma";
	menuList[4] = "Quit";

	menuNum = 0;
}


void MenuState::GameInfo()
{
	string gameinfo;
	Console::Clear();

	Console::ForegroundColor(White);
	cout << "V'Zacran: Welcome To XIROMA\n";
	gameinfo = { "Our Mission - As soon as turn on Battle, you will be at war with our brutal invaders ESS Roanake.\n"
		"They are threatening the lives of XIROMA civilisation in order to capture THE ALPHA_OMEGA, that has celestial power,\n" "to bring back life in dead souls and yes if used with Grenade can use unimaginable destruction. \n"
		"Your aim is to destroy these species before you lose three ultimate lives.\n"
		"Our scientific Dr.Sermons, has created ZF-1, that helps to trace the target, and its hidden ability is that when shoot,\n" "it dissoles the gas released by nano-tetryon torpedoes."
		"Your long tem objective is to combat fiercly and destroy the diseased planet Erushasslons\n\n" };


	for (unsigned i = 0; i < gameinfo.length(); i++)
	{
		cout << gameinfo[i];
		if ((i + 1) < gameinfo.length() && gameinfo[i + 1] != '\n')
			cout << char(129);
		Sleep(100);
		if ((i + 1) < gameinfo.length() && gameinfo[i + 1] != '\n')
			cout << char(8);

	}
	cout << ' ' << char(8);
	cin.get();

	Game::ChangeState(MENU_STATE);

}