#include "PowerUp.h"
#include <random>
#include "Blaster.h"


 void PowerUp::Activate() {
 
 }

 void PowerUp::Draw() {

 }

 void PowerUp::RapidFiring() {
	 std::random_device rd;
	 std::mt19937 gen(rd());
	 std::uniform_int_distribution<>dis(min, max);
	 RapidFireRate  = static_cast<float> (dis(gen)) / 10000.0f;
	 SetCooldownSeconds();
 }

 void PowerUp::SpeedBoosting() {

 }

 void PowerUp::Update() {

 }

 void PowerUp::SetCooldownSeconds() {
	 Blaster::m_cooldownSeconds = RapidFireRate;
 }