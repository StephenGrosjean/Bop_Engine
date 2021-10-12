#pragma once
#include "AssetManager.h"
#include "Game.h"

class AudioManager
{
public:
	AudioManager()
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096 < 0))
		{
			printf("Mixer Initialization error");
		}
	};

	~AudioManager()
	{
		Mix_Quit();
	}

	void PlayMusic(std::string filename, int loops = -1)
	{
		Mix_PlayMusic(Game::assetManager->GetMusic(filename), loops);
	}

	void PauseMusic()
	{
		if (Mix_PlayingMusic() != 0)
			Mix_PausedMusic();
	}

	void ResumeMusic()
	{

		if (Mix_PausedMusic() != 0)
			Mix_ResumeMusic();
	}

	void PlaySFX(std::string filename, int loops = 0, int channel = 0)
	{
		Mix_PlayChannel(channel, Game::assetManager->GetSFX(filename), loops);
	}
};