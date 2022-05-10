
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

#pragma once

namespace KatanaEngine
{
	/** @brief Represents a 2D grid of texels. */
	class AudioSample : public Resource
	{

	public:

		AudioSample();
		virtual ~AudioSample();

		static void ReserveSamples(int count) { al_reserve_samples(count); }

		/** @brief Load the desired font into memory.
			@param path The path to the desired font.
			@param pManager A pointer to the ResourceManager that will manage the font.
			@return Returns true if the font was loaded, false otherwise. */
		virtual bool Load(const std::string& path, ResourceManager* pManager);

		/** @brief Used to determine if the texture is cloneable.
			@return Returns true if the texture is clonable, false otherwise.
			@remark Textures should usually not be cloneable. */
		virtual bool IsCloneable() const { return true; }


		virtual bool Play();

		virtual void SetLooping(const bool loop = true);

		virtual void SetVolume(const float volume);


	protected:

		virtual void SetSample(ALLEGRO_SAMPLE* pSample);


	private:

		static bool s_alAddonInitialized;

		ALLEGRO_SAMPLE* m_pSample = nullptr;
		ALLEGRO_PLAYMODE m_playMode = ALLEGRO_PLAYMODE_ONCE;

		float m_volume = 1;
	};

}