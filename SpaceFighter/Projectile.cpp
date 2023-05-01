
#include "Projectile.h"

Texture *Projectile::s_pTexture = nullptr;

Projectile::Projectile()
{
	SetSpeed(500); // 
	SetDamage(1);
	SetDirection(-Vector2::UNIT_Y);
	SetCollisionRadius(9);

	m_drawnByLevel = true;
}

void Projectile::Update(const GameTime *pGameTime)
{
	// Check if the projectile is active
	if (IsActive())
	{
		// Calculate the translation vector based on the direction and speed of the projectile
		// and the elapsed time since the last update.
		Vector2 translation = m_direction * m_speed * pGameTime->GetTimeElapsed();

		// Move the projectile by the calculated amount.
		TranslatePosition(translation);

		// Get the current position and size of the projectile's texture.
		Vector2 position = GetPosition();
		Vector2 size = s_pTexture->GetSize();

		// Check if the projectile is off the screen in any direction to deactivate it.
		if (position.Y < -size.Y) Deactivate();
		else if (position.X < -size.X) Deactivate();
		else if (position.Y > Game::GetScreenHeight() + size.Y) Deactivate();
		else if (position.X > Game::GetScreenWidth() + size.X) Deactivate();
	}

	// Call the Update method of the base GameObject class for other updates.
	GameObject::Update(pGameTime);
}

void Projectile::Draw(SpriteBatch *pSpriteBatch)
{
	if (IsActive())
	{
		pSpriteBatch->Draw(s_pTexture, GetPosition(), Color::White, s_pTexture->GetCenter());
	}
}

void Projectile::Activate(const Vector2 &position, bool wasShotByPlayer)
{
	m_wasShotByPlayer = wasShotByPlayer;
	SetPosition(position);

	GameObject::Activate();
}

std::string Projectile::ToString() const
{
	return ((WasShotByPlayer()) ? "Player " : "Enemy ") + GetProjectileTypeString();
}

CollisionType Projectile::GetCollisionType() const
{
	CollisionType shipType = WasShotByPlayer() ? CollisionType::PLAYER : CollisionType::ENEMY;
	return (shipType | GetProjectileType());
}