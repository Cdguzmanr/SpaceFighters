
#include "BioEnemyShip.h"


BioEnemyShip::BioEnemyShip()
{

	SetSpeed(150);
	SetMaxHitPoints(1);
	SetCollisionRadius(20);
	SetKillAddPoints(2);
}


void BioEnemyShip::Update(const GameTime *pGameTime)
{
	if (IsActive()) // Check if enemy ship is active
	{

		// Calculate the x position based on a sine wave that varies with time
		// and the index of the enemy ship object. This is used to make the ship
		// move in a wavy pattern.  
		// => This is a basic movement patter based on math graphical sin function
		float x = sin(pGameTime->GetTotalTime() * Math::PI + GetIndex());

		// Scale the x value by the ship's speed and the elapsed time since the last update.
		// The result is multiplied by 0.4f to slow down the ship's movement slightly.
		x *= GetSpeed() * pGameTime->GetTimeElapsed() * 0.4f; 
		
		// Change the x and y position on the ship based on the calculations.
		TranslatePosition(x, GetSpeed() * pGameTime->GetTimeElapsed());

		// Check if the ship is off screen to deactivate it.
		if (!IsOnScreen()) Deactivate();
	}

	// Call the Update method of the base EnemyShip class to handle other updates.
	EnemyShip::Update(pGameTime);
}


void BioEnemyShip::Draw(SpriteBatch *pSpriteBatch)
{
	if (IsActive())
	{
		pSpriteBatch->Draw(m_pTexture, GetPosition(), Color::White, m_pTexture->GetCenter(), Vector2::ONE, Math::PI, 1);
	}
}
