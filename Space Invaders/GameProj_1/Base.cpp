#include "stdafx.h"
#include "Base.h"


Base::Base( ConsoleColor _fg, ConsoleColor _bg, const char* const _text)
{
	//text = NULL; // 0, nullptr

	
	SetFG(_fg);
	SetBG(_bg);
	SetText(_text);
}

Base::Base(Base const& _obj)
{
	//text = NULL;

	SetX(_obj.x);
	SetY(_obj.y);
	SetFG(_obj.fg);
	SetBG(_obj.bg);
	SetText(_obj.text.c_str());
}

Base& Base::operator=(Base const& _obj)
{
	if (&_obj != this)
	{
		SetX(_obj.x);
		SetY(_obj.y);
		SetFG(_obj.fg);
		SetBG(_obj.bg);
		SetText(_obj.text.c_str());
	}
	return *this;
}
Base::Base()
{
	
}


Base::~Base()
{
	
}

void Base::SetText(const char* const _text)
{
	//delete[] text;
	text = _text;
	//text = _strdup(_text);
	//Checking for newline
	bool gotWidth = false;
	int i = 0, j = 0;
	for (i; text[i]; i++)
	{
		if (text[i] == '\n' || text[i] == '\t')
		{
			if (!gotWidth)
			{
				//if it reads a newline or tab, we want to push back the cursor pointing to the last character
				gotWidth = true;
				width = i - 1;
			}
			j++;
		}
		
	}
	//this is for checking if there is single text, we dont want it to reas the newline
	if (!gotWidth)
		width = i - 1;
	height = j;
}

void Base::Show()
{
	Console::ForegroundColor(fg);
	Console::BackgroundColor(bg);

	Console::SetCursorPosition(x, y);
	int currLine = Console::CursorTop();
	for (int i = 0; text[i]; i++)
	{

		if (text[i] == '\n')
		{
			++currLine;
			Console::SetCursorPosition(x, currLine);

		}
		else
			cout << text[i];
	}

	Console::ResetColor();
}

void Base::Input(DList<Base*> &baseObj)
{

}

void Base::Update(int _frame)
{

}

void Base::Render() const
{
	Console::ForegroundColor(fg);
	Console::BackgroundColor(bg);

	Console::SetCursorPosition(x, y);
	int currLine = Console::CursorTop();
	for (int i = 0; text[i]; i++)
	{

		if (text[i] == '\n')
		{
			++currLine;
			Console::SetCursorPosition(x, currLine);
		}
		else
		{
			cout << text[i];
		}
	}
	Console::SetCursorPosition(0, 0);
	Console::ResetColor();
}

bool Base::CollidesBoundary(int _x, int _y, int _width, int _height) const
{
	if (_x >= 1 && _x < Console::WindowWidth() - _width - 2 && _y >= 2 && _y < Console::WindowHeight() - _height - 2)
	{
		return false;
	}
	return true;
}