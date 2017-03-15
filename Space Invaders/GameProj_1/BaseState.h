#pragma once
class BaseState
{
protected:
	static FMOD::Channel *channel;
	static int currentMusic;
public:
	static bool keyPressed;
	BaseState();
	virtual ~BaseState() = 0;
	static void SetkeyPressed(bool _keyPressed)
	{
		keyPressed = _keyPressed;
	}
	bool GetkeyPressed() const { return keyPressed; }
	virtual void Init() = 0;

	virtual void Input() = 0;
	virtual void Update(int _frame) = 0;
	virtual void Render() const = 0;
	 
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	
};

