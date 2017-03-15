#pragma once
#include "Base.h"

#define velX velVec[0]
#define velY velVec[1]

class Player;

class Missile : public Base
{
private:
	vector<int> velVec;
	Base* target;
	Base* owner;
	bool is_homing = false;
public:
	Missile();
	~Missile();

	void Input();
	void Update(int _frame);
	void Render() const;
	//A's
	int GetXVel() const { return velX; }
	int GetYvel() const { return velY; }
	void GetVelocity(int& _x, int& _y){ _x = velX; _y = velY; }
	Base* GetTarget() const { return target; }
	Base* GetOwner() const { return owner; }
	bool GetHoming() const { return is_homing; }

	//M's
	void SetXVel(int _x) { velX = _x; }
	void SetYVel(int _y) { velY = _y; }
	void SetVelocity(int _x, int _y) { velX = _x; velY = _y; }
	void SetTarget(Base* _target) { target = _target;}
	void SetOwner(Base* _owner) { owner = _owner;}
	void SetHoming(bool _homing) { is_homing = _homing; }

	bool Collides();
};

