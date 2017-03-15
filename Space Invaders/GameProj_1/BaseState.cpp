#include "stdafx.h"
#include "BaseState.h"

bool BaseState::keyPressed = false;
FMOD::Channel*BaseState::channel;
int BaseState::currentMusic;

BaseState::BaseState()
{
}


BaseState::~BaseState()
{
}
