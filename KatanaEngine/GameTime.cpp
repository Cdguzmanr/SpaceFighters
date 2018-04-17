﻿
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

	GameTime::GameTime()
	{
		m_previousTotalTime = al_get_time();
		m_currentTotalTime = al_get_time();
		m_elapsedTime = 0.0;
	}

	// Updates the timing values
	void GameTime::Update()
	{
		m_previousTotalTime = m_currentTotalTime;
		m_currentTotalTime = al_get_time();

		if (m_currentTotalTime - m_previousTotalTime <= 0.2)
		{
			m_elapsedTime = (m_currentTotalTime - m_previousTotalTime);
		}
		else
		{
			std::cout << "Hopefully you were debugging!" << std::endl;
		}
	}
}