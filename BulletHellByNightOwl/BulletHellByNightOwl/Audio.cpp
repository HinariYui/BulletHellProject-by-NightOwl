#include "SDL_timer.h"
#include "Audio.h"
#include <iostream>

void SoundEffect::play(int loop)
{
	if (Mix_PlayChannel(-1, m_chunk, loop) == -1)
	{
		std::cout << "Mix_PlayChannel Error " << std::string(Mix_GetError());
	}

	//Mix_Volume(-1, 0 - 128);

}

void Music::play(int loop)
{
	//Mix_PlayMusic(m_music, loop);



	// play music forever, fading in over 2 seconds
	// Mix_Music *music; // I assume this has been loaded already
	if (Mix_FadeInMusic(m_music, -1, 2000) == -1) {
		printf("Mix_FadeInMusic: %s\n", Mix_GetError());
		// well, there's no music, but most games don't break without music...
	}



	//Mix_VolumeMusic(0 - 128)
}

void Music::pause()
{
	Mix_PauseMusic();
}

void Music::stop()
{
	//Mix_HaltMusic();
	// fade out music to finish 3 seconds from now
	while (!Mix_FadeOutMusic(3000) && Mix_PlayingMusic()) {
		// wait for any fades to complete
		//SDL_Delay(100);
	}
}

void Music::resume()
{
	Mix_ResumeMusic();
}

AudioEngine::AudioEngine()
{
}

AudioEngine::~AudioEngine()
{
}

void AudioEngine::init()
{
	if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1)
	{
		std::cout << "Mix_Init Error " << std::string(Mix_GetError());
	}

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		std::cout << "Mix_Init Error " << std::string(Mix_GetError());
	}

	isInit = true;
}

void AudioEngine::destroy()
{
	if (isInit)
	{
		isInit = false;
		Mix_Quit();
	}
}

SoundEffect AudioEngine::loadSoundEffect(const std::string & filePath)
{
	//Try to find sound in cache
	auto it = m_effectMap.find(filePath);

	SoundEffect effect;

	if (it == m_effectMap.end())
	{
		//Not found sound in cache
		Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());
		if (chunk == nullptr)
		{
			std::cout << "Mix_LoadWAV Error " << std::string(Mix_GetError());
		}
		effect.m_chunk = chunk;
		m_effectMap[filePath] = chunk;
	}
	else
	{
		//Find sound in cache
		effect.m_chunk = it->second;
	}


	return effect;
}

Music AudioEngine::loadMusic(const std::string & filePath)
{
	//Try to find sound in cache
	auto it = m_musicMap.find(filePath);

	Music music;

	if (it == m_musicMap.end())
	{
		//Not found sound in cache
		Mix_Music* mixMusic = Mix_LoadMUS(filePath.c_str());
		if (mixMusic == nullptr)
		{
			std::cout << "Mix_LoadMUS Error " << std::string(Mix_GetError());
		}
		music.m_music = mixMusic;
		m_musicMap[filePath] = mixMusic;
	}
	else
	{
		//Find sound in cache
		music.m_music = it->second;
	}


	return music;
}
