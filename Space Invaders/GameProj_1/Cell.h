#pragma once
#include"Base.h"

template<typename offset, typename symbol>
struct Cell
{
	offset oX, oY;
	ConsoleColor fg, bg;
	symbol sym;

	Cell() { }
	Cell(offset _x, offset _y, ConsoleColor _fg, ConsoleColor _bg, symbol _sym);
	bool Show(int _left, int _top) const;
	int GetX() const { return oX; }
	int GetY() const { return oY; }
	char GetText() const
	{
		return sym;
	}
	System::ConsoleColor GetFg() const
	{
		return fg;
	}
	System::ConsoleColor GetBg() const
	{
		return bg;
	}
	void SetX(offset _x) { oX = _x; }
	void SetY(offset _y) { oY = _y; }
	void SetFg(System::ConsoleColor _fg) { fg = _fg; }
	void SetBg(System::ConsoleColor _bg)
	{
		bg = _bg;
	}
	void SetText(char _sym)
	{
		sym = _sym;
	}

	int operator[](int _indexX);
	const int operator[](int _indexY)const;


};


template<typename offset, typename symbol>
Cell<offset, symbol>::Cell(offset _x, offset _y, ConsoleColor _fg, ConsoleColor _bg, symbol _sym)
{
	SetX(_x);
	SetY(_y);
	SetFg(_fg);
	SetBg(_bg);
	SetText(_sym);
}


template<typename offset, typename symbol>
bool Cell<offset, symbol>::Show(int _left, int _top) const
{
	offset posX = _left + oX;
	offset posY = _top + oY;
	if (posX > Console::WindowWidth() - 1 || posX < 1 || posY > Console::WindowHeight() - 3 || posY < 2)
	{
		return false;
	}

	Console::ForegroundColor(fg);
	Console::BackgroundColor(bg);
	Console::SetCursorPosition(posX, posY);

	cout << sym;
	Console::ResetColor();

	return true;
}


template<typename offset, typename symbol>
int Cell<offset, symbol>::operator[](int _indexX)
{
	if (_indexX == 0)
	{
		return oX;
	}
	if (_indexX == 1)
	{
		return oY;
	}
	return 0;
}

template<typename offset, typename symbol>
const int Cell<offset, symbol> :: operator[](int _indexY)const
{
	if (_indexY == 0)
	{
		return oX;
	}
	if (_indexY == 1)
	{
		return oY;
	}
	return 0;
}
