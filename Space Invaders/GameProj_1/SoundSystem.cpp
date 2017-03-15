#include "stdafx.h"
#include "SoundSystem.h"
#include"fmod.hpp"
#include "fmod_errors.h"
#include "windows.h"
#include "fmod.h"
#include "cstdlib"

FMOD::System* SoundSystem::system;
void *SoundSystem::extradriverdata;
FMOD::Sound * SoundSystem::soundarr[MAXGAMESOUNDS];

int SoundSystem::Init()
{
	FMOD_RESULT result;
	result = FMOD::System_Create(&system);

	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
	if (result != FMOD_OK)
	{
		system->close();
		system->release();

		return 0;
	}
	createSound(&soundarr[GAME_SOUND_BEGINNING1], "ArcadeMusic 6091_58.wav");
	createSound(&soundarr[VICTORYLISTMUSIC], "Two_Steps_from_Hell_-_Heart_Of_Courage.wav");
	createSound(&soundarr[STORYMUSIC], "Two_Steps_from_Hell_-_Equus.wav");
	createSound(&soundarr[GAME_SOUND_PLAYERSHOT], "Gun-Machine-Shot-Single_GEN-HD2-30331.mp3");
	createSound(&soundarr[GAME_SOUND_ENEMYSHOT], "GunShotGun TL03_53_3.wav");


	return 1;
}

void SoundSystem::Release()
{
	system->close();
	system->release();
}

SoundSystem::SoundSystem()
{
}


SoundSystem::~SoundSystem()
{
}

void SoundSystem::createSound(SoundClass *pSound, const char* pFile)
{
	FMOD_RESULT result = system->createSound(pFile, FMOD_DEFAULT, NULL, pSound);
}


FMOD::Channel* SoundSystem::playSound(SoundClass pSound, bool bLoop)
{
	if (!bLoop)
		pSound->setMode(FMOD_LOOP_OFF);
	else
	{
		pSound->setMode(FMOD_LOOP_NORMAL);
		pSound->setLoopCount(-1);
	}

	FMOD::Channel* channel;
	system->playSound(pSound, 0, false, &channel);
	return channel;
}

void SoundSystem::releaseSound(SoundClass pSound)
{
	pSound->release();
}

void SoundSystem::Update()
{
	system->update();
}
