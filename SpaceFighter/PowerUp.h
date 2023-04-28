#pragma once
#include "GameObject.h"
#include "Blaster.h"
class PowerUp : public Blaster
{
//protected:
public:
	static float RapidFireRate;//unsure if it should be static
public:
	enum powerUp {
		RapidFire,
		SpeedBoost
	};

	//todo get the methods built
	
	PowerUp();
	virtual void Draw();//Andres
	virtual void Update();
	virtual void Activate(); //Gerald
	static void SetCooldownSeconds();//don't think should be static
	static void  RapidFiring();//don't think should be static
	virtual void SpeedBoosting();
	


	 
private:
	float PowerUpTimer;
	static const int min = 117;//unsure if it should be static
	static const int max = 2625;//unsure if it should be static
	//line 58 of blaster.h was made static not sure if it should be

};

