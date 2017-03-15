#include "stdafx.h"
#include "PlayState.h"
#include "Player.h"
#include "Enemy.h"
#include "Missile.h"
#include "Cell.h"
#include "DList.h"
#include "SoundSystem.h"

//vector<Base*> PlayState::baseObj;
DList<Base*> PlayState::baseObj;

PlayState::PlayState()
{
	
}


PlayState::~PlayState()
{
	/*if (!baseObj)
		return;
	for (int i = 0; i < numOfObjects; i++)
	{
		delete baseObj[i];
	}
	delete[] baseObj;*/

	decltype(baseObj.size()) i = 0;
	for (; i < baseObj.size(); i++)
		delete baseObj[i];

	delete[] cellText;
}

void PlayState::Input()
{
	/*int i = 0;
	for (; i < numOfObjects; i++)
	{
		baseObj[i]->Input(baseObj, numOfObjects);
	}*/

	decltype(baseObj.size()) i = 0;
	for (; i < baseObj.size(); i++)
		baseObj[i]->Input(baseObj);
}

void PlayState::Update(int _frame)
{
	/*int i = 0;
	for (; i < numOfObjects; i++)
	{
		baseObj[i]->Update(_frame);
	}*/

	decltype(baseObj.size()) i = 0;
	for (; i < baseObj.size(); i++)
			baseObj[i]->Update(_frame);

	if (_frame % 20 == 0)
	{
		dynamic_cast<Enemy*>(baseObj[rand() % 5 + 1])->ShotToPlayer(_frame);
	}
	

	//Dead Loop
	//vector<Base*>::iterator iter = baseObj.begin();
	/*while (iter != baseObj.end())
	{
		if (!(*iter)->GetAlive())
		{
			delete *iter;
			baseObj.erase(iter--);
		}
		++iter;
	}*/

	DList<Base*> dlist;
	for (int i = 0; i < dlist.size(); i++)
	{
		if (!dlist[i]->GetAlive())
		{
			delete dlist[i];
			dlist.erase(i--);
		}
	}

	for (int i = 0; i < noOfCells; i++)
	{
		cellText[i].SetY(cellText[i].GetY() + 1);

		if (cellText[i].GetY() >= Console::WindowHeight() - 2)
		{
			cellText[i].SetY(0);
			cellText[i].SetX(rand() % Console::WindowWidth() - 2);
		}
	}
}

void PlayState::Render() const
{
	/*int i = 0;
	for (; i < numOfObjects; i++)
	{
		baseObj[i]->Render();
	}*/



	Console::DrawBox(0, 1, Console::WindowWidth(), Console::WindowHeight() - 2, true);

	for (int i = 0; i < noOfCells; i++)
	{
		cellText[i].Show(0, 0);

	}

	decltype(baseObj.size()) i = 0;
	for (; i < baseObj.size(); i++)
		baseObj[i]->Render();
}

void PlayState::Enter()
{
	Console::FlushKeys();
	system("cls");

	UserChoice();
}

void PlayState::Exit()
{
	Console::Clear();
	
	cout << "V'Zacran: " << dynamic_cast<Player*>(baseObj[0])->GetName() << ",you saved Xiroma from brutal invaders(ESS Roanake) and terrible\n"
	<<"/tdestruction by nano-Tetryon Torpedoes that could have blowed the \n"
	<<"/tentire civilization of Xiroma. You are LifeSaver! " << endl << endl;
	cout << "System:   You scored around " << dynamic_cast<Player*>(baseObj[0])->GetScore() << " points and played with " << dynamic_cast<Player*>(baseObj[0])->GetDiff() << " difficulty.";

#pragma region Saving out in Binary
#if 1
	//code to save in scores
	Player* pl = dynamic_cast<Player*>(baseObj[0]);
	PlayerInfo pl_info;
	vector<PlayerInfo> scoresStats;

	//Actual Player
	pl_info.score = pl->GetScore();
	pl_info.diff = pl->GetDiff();
	strcpy_s(pl_info.name, 32, pl->GetName());
	scoresStats.push_back(pl_info);

	fstream bout;
	bout.open("scores.bin", ios_base::binary |ios_base::app);
	//saving out the scores
	if (bout.is_open())
	{
		//inefficient way of doing it
		/*bout.write((char*)&score, sizeof(int));
		  bout.write((char*)&diff, sizeof(int));
		  bout.srite((char*)&buffer, 32);*/

		//Efficient way of doing it
		/*bout.write((char*)&pl_info, sizeof(PlayerInfo);

		//vec.data() returns the memory add to the beg of the contigous memory array in the vector

		bout.write((char*)scoresStats.data(), sizeof(PlayerInfo) * scoresStats.size());

		*/

		bout.write((char*)&scoresStats[0], sizeof(PlayerInfo) * scoresStats.size());

		bout.close();
	}
#endif

#pragma region Reading in In Binary
#if 1
	scoresStats.clear();
		fstream bin;
		bin.open("Scores.bin", ios_base::binary | ios_base::app | ios_base::in);
		
		if (bin.is_open())
		{
			bin.seekg(0, ios_base::end);
			int count = (int)bin.tellg();
			count /= sizeof(PlayerInfo);
			scoresStats.resize(count);
			bin.seekg(0, ios_base::beg);

			//Loop Way
			/* unsigned int i = 0;
			   for(; i < count; i++)
			   {
			    PlayerInfo temp;
				bin.read((char*)&temp, sizeof(PlayerInfo));
				scoresStats.push_back(temp)*/

			bin.read((char*)scoresStats.data(), (sizeof(PlayerInfo) * count));
			bin.close();
			unsigned int  i = 0;
			for (; i < scoresStats.size(); i++)
			{
				cout << scoresStats[i].name << "scored " << scoresStats[i].score << " on difficulty " << scoresStats[i].diff << '\n';
			}
		}
#endif
		unsigned int i = 0;
		for (; i < baseObj.size(); i++)
		{
			delete baseObj[i];
		}

		baseObj.clear();

}
	
void PlayState::Init()
{
	noOfCells = 20;
	if (noOfCells % 2)
	{
		noOfCells++;
	}

	cellText = new Cell <int, char>[noOfCells];
	for (int i = 0; i < noOfCells; i++)
	{

		cellText[i].SetX(rand() % Console::WindowWidth());
		cellText[i].SetY(rand() % Console::WindowHeight());
		for (int j = 0; j < i; j++)
		{
			if (cellText[i].GetX() == cellText[j].GetX() && cellText[i].GetY() == cellText[j].GetY())
			{
				i--;
				break;
			}

		}

	}
	
	for (int i = 0; i < noOfCells; i++)
	{
		int color = rand() % 16;
		int color2 = ConsoleColor::Black;
		cellText[i].SetFg((ConsoleColor)color);
		cellText[i].SetBg((ConsoleColor)color2);
		if (cellText[i].GetFg() == cellText[i].GetBg())
		{
			i--;
			continue;
		}
		cellText[i].SetText('o');
		cout << cellText[i].GetText() << endl;

	}
}
void PlayState::UserChoice()
{
	//baseObj = new Base*[numOfObjects];

	//baseObj.resize(2);
	Base** ar = new Base*[3];
	ifstream fin;
	fin.open("save.txt");

	if (fin.is_open())
	{
		int count = 0;
		int fg, bg;

		char buffer[2800];
		fin >> count;
		int i = 0;
		for (; i < count; ++i)
		{
			fin.ignore(INT_MAX, '\n');
			fin.getline(buffer, 2800, '\t');
			fin >> fg >> bg;
			//Base *p = new Base((ConsoleColor)fg, (ConsoleColor)bg, buffer);
			ar[i] = new Base((ConsoleColor)fg, (ConsoleColor)bg, buffer);
			ar[i]->SetX(0);
			ar[i]->SetY(Console::CursorTop() + 2);
			ar[i]->Show();

		}
		Console::SetCursorPosition(0, 34);
		cout << "PRESS ENTER TO CONTINUE......";
		char userName[32];
		cin.ignore(INT_MAX, '\n');
	
		for (;;)
		{
			Console::SetCursorPosition(0, 36);
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
		int userInput, userInput1, userDiff;

		for (;;)
		{
			Console::SetCursorPosition(0, 38);
			cout << "Enter in what difficulty level you would like to play in GamePlay?";

			if (cin >> userDiff, userDiff >= 0, userDiff < 500)
			{
				cin.sync();
				break;
			}
			cin.clear();
			cin.sync();
		}
		for (;;)
		{
			Console::SetCursorPosition(0, 40);
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
			Console::SetCursorPosition(0, 42);
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

		//before baseobj[0]
		Base *player = new Player(ConsoleColor::White, ConsoleColor::Black, ar[userInput - 1]->GetText(), 0, userDiff, userName);
		player->SetX(5);
		player->SetY(Console::WindowHeight() >> 1);
		player->SetID(PLAYER);

		Base *enemy = new Enemy(ConsoleColor::White, ConsoleColor::Black, ar[userInput1 - 1]->GetText());
		//enemy->SetX(Console::WindowWidth() - 50);
		enemy->SetX(25);
		enemy->SetY(2);
		enemy->SetID(ENEMY);
		//system("pause");

		Base *enemy1 = new Enemy(ConsoleColor::White, ConsoleColor::Black, ar[userInput1 - 1]->GetText());
		enemy1->SetX(50);
		enemy1->SetY(2);
		enemy1->SetID(ENEMY);

		Base *enemy2 = new Enemy(ConsoleColor::White, ConsoleColor::Black, ar[userInput1 - 1]->GetText());
		//enemy2->SetX(enemy1->GetX() - enemy->GetWidth());
		enemy2->SetX(75);
		enemy2->SetY(2);
		enemy2->SetID(ENEMY);

		Base *enemy3 = new Enemy(ConsoleColor::White, ConsoleColor::Black, ar[userInput1 - 1]->GetText());
		enemy3->SetX(95);
		enemy3->SetY(2);
		enemy3->SetID(ENEMY);

		Base *enemy4 = new Enemy(ConsoleColor::White, ConsoleColor::Black, ar[userInput1 - 1]->GetText());
		//enemy4->SetX(Console::WindowWidth() - 50);
		enemy4->SetX(125);
		enemy4->SetY(2);
		enemy4->SetID(ENEMY);

		baseObj.push_back(player);
		baseObj.push_back(enemy);
		baseObj.push_back(enemy1);
		baseObj.push_back(enemy2);
		baseObj.push_back(enemy3);
		baseObj.push_back(enemy4);
		fin.close();

		for (int i = 0; i < 3; i++)
		{
			delete ar[i];
		}
		delete[] ar;
	}
	Console::CursorVisible(false);

	baseObj[0]->SetAlive(true);
	baseObj[1]->SetAlive(true);

	/*baseObj.push_back(new Missile());

	//update all objects after creattion
	Missile* m = dynamic_cast<Missile*>(baseObj[2]);
	Player* p = dynamic_cast<Player*>(baseObj[0]);

	p->SetMissile(m);
	m->SetTarget(baseObj[1]);
	m->SetOwner(p);*/

}