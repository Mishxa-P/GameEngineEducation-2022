#pragma once
#include "flecs.h"

struct Gun {};
struct Bullet {};
struct ShootCooldown { float val; };
struct CurrentShootCooldown { float val; };
struct Reload { float val; };
struct CurrentReload { float val; };
struct MaxAmmo { int val; };
struct CurrentAmmo { int val; };
struct AmmoBuff { int val; };
struct BulletSpeed { float val; };
struct BulletLifeTime { float val; };
struct ShouldBeDestroyed { };


void register_ecs_gun_systems(flecs::world& ecs);