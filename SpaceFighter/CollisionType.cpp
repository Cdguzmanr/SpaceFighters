
#include "CollisionType.h"

const CollisionType CollisionType::NONE			= CollisionType(0);//0 exponential increase
const CollisionType CollisionType::PLAYER		= CollisionType(1 << 0);//1
const CollisionType CollisionType::ENEMY		= CollisionType(1 << 1);//2
const CollisionType CollisionType::SHIP			= CollisionType(1 << 2);//4
const CollisionType CollisionType::PROJECTILE	= CollisionType(1 << 3);//8
const CollisionType CollisionType::POWERUP		= CollisionType(1 << 4);//16