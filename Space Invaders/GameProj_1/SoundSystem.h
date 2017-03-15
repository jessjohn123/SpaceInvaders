#pragma once
#include "fmod.hpp"
#include "fmod_errors.h"
typedef FMOD::Sound* SoundClass;

enum GAME_SOUNDS { GAME_SOUND_BEGINNING1, VICTORYLISTMUSIC, STORYMUSIC, GAME_SOUND_PLAYERSHOT, GAME_SOUND_ENEMYSHOT, MAXGAMESOUNDS };

class SoundSystem
{
public:
	SoundSystem();
	~SoundSystem();

	static FMOD::Sound *soundarr[MAXGAMESOUNDS];

	static void createSound(SoundClass *pSound, const char* pFile);
	static FMOD::Channel* playSound(SoundClass pSound, bool bLoop = false);
	static void releaseSound(SoundClass pSound);

	static FMOD::System * system;
	static void *extradriverdata;

	static int Init();
	static void Release();
	static void Update();
};

