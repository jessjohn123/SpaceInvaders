#pragma once
#define Enemy_GROUP ENEMY | MISSILE

enum CLASS_ID {PLAYER = 0, ENEMY, MISSILE, ENEMY_MISSILE, FINAL_ID};

class Base
{
private:
	string text;
	ConsoleColor fg, bg;
	int x, y;
	unsigned short width;
	unsigned short height;
	bool alive;
	CLASS_ID id;

public:
	Base( ConsoleColor _fg, ConsoleColor _bg, const char* const _text);
	Base(Base const& _obj);
	Base& operator=(Base const& _obj);

	Base();
	virtual ~Base();

	//Accessors
	int GetX() const{ return x; };
	int GetY() const { return y; };
	const char * const GetText() const { return text.c_str(); };
	ConsoleColor GetFG() { return fg; };
	ConsoleColor GetBG() { return bg; };
	unsigned short GetWidth() const { return width; }
	unsigned short GetHeight() const { return height; }
	bool GetAlive() const { return alive; }
	CLASS_ID GetID() const { return id; }

	//Mutators
	void SetX(int _x) { x = _x; }
	void SetY(int _y) { y = _y; };
	void SetFG(ConsoleColor _fg) { fg = _fg; }
	void SetBG(ConsoleColor _bg) { bg = _bg; };
	void SetText(const char* const _text);
	void SetWidth(short _width) { width = _width; }
	void SetHeight(short _height){ height = _height; }
	void Show();
	void SetAlive(bool is_alive){ alive = is_alive; }
	void SetID(CLASS_ID _id) { id = _id; }


	/*virtual void Input(Base ** objects, int numObjects);*/
	//virtual void Input(vector<Base*> baseObj);
	virtual void Input(DList<Base*> &baseObj);
	virtual void Update(int _frame);
	virtual void Render() const;

	bool CollidesBoundary(int _x, int _y, int _width, int _height) const;
};

