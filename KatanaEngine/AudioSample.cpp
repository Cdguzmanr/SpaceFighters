
/*
	 ██╗  ██╗  █████╗  ████████╗  █████╗  ███╗   ██╗  █████╗
	 ██║ ██╔╝ ██╔══██╗ ╚══██╔══╝ ██╔══██╗ ████╗  ██║ ██╔══██╗
	 █████╔╝  ███████║    ██║    ███████║ ██╔██╗ ██║ ███████║
	 ██╔═██╗  ██╔══██║    ██║    ██╔══██║ ██║╚██╗██║ ██╔══██║
	 ██║  ██╗ ██║  ██║    ██║    ██║  ██║ ██║ ╚████║ ██║  ██║
	 ╚═╝  ╚═╝ ╚═╝  ╚═╝/\  ╚═╝    ╚═╝  ╚═╝ ╚═╝  ╚═══╝ ╚═╝  ╚═╝
   /vvvvvvvvvvvvvvvvvvv \=========================================,
   `^^^^^^^^^^^^^^^^^^^ /---------------------------------------"
		Katana Engine \/ © 2012 - Shuriken Studios LLC
				http://www.shurikenstudios.com
*/

#include "KatanaEngine.h"

namespace KatanaEngine
{
	bool AudioSample::s_alAddonInitialized = false;

	AudioSample::AudioSample()
	{
		if (!s_alAddonInitialized)
		{
			al_install_audio();
			al_init_acodec_addon();
			s_alAddonInitialized = true;
		}
	}

	AudioSample::~AudioSample()
	{
		al_destroy_sample(m_pSample);

		m_pSample = nullptr;
	}


	bool AudioSample::Load(const std::string& path, ResourceManager* pManager)
	{
		ALLEGRO_SAMPLE* pTemp = al_load_sample(path.c_str());

		SetSample(pTemp);

		return m_pSample;
	}

	bool AudioSample::Play()
	{
		return al_play_sample(m_pSample, m_volume, 0, 1, m_playMode, NULL);
	}

	void AudioSample::SetLooping(const bool loop)
	{
		m_playMode = loop ? ALLEGRO_PLAYMODE_LOOP : ALLEGRO_PLAYMODE_ONCE;
	}

	void AudioSample::SetVolume(const float volume)
	{
		m_volume = Math::Clamp(0, 1, volume);
	}


	void AudioSample::SetSample(ALLEGRO_SAMPLE* pSample)
	{
		if (pSample)
		{
			m_pSample = pSample;
		}
	}
}