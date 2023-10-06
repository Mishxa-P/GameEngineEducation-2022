#include "EntitySystem.h"
#include "ecsSystems.h"
#include "ecsMesh.h"
#include "ecsGun.h"
#include "ecsControl.h"
#include "ecsPhys.h"

EntitySystem::EntitySystem(RenderEngine* renderEngine, InputHandler* inputHandler)
{
    ecs.entity("inputHandler")
        .set(InputHandlerPtr{ inputHandler });
    ecs.entity("renderEngine")
        .set(RenderEnginePtr{ renderEngine });

    auto cubeGun = ecs.entity()
        .set(Position{ 0.f, 0.f, 0.f })
        .set(MaxAmmo{ 6 })
        .set(CurrentAmmo{ 6 })
        .set(BulletSpeed{ 40.f })
        .set(Reload{ 1.0f })
        .set(CurrentReload{ 1.0f })
        .set(ShootCooldown{ 0.1f })
        .set(CurrentShootCooldown{ 0.1f })
        .add<Gun>()
        .add<CubeMesh>();

    auto cubeDestroyable1 =  ecs.entity()
            .set(Position{ 50.f, 15.f, 0.f})
            .set(AmmoBuff{ 2 })
            .add<Destroyable>()
            .add<CubeMesh>();

    auto cubeDestroyable2 = ecs.entity()
        .set(Position{ 25.f, -5.f, 0.f })
        .set(AmmoBuff{ 2 })
        .add<Destroyable>()
        .add<CubeMesh>();
  
    for (int i = 5; i < 35; i++)
    {
        ecs.entity()
            .set(Position{ 5.f + i * 2, -25.f, 0.f })
            .add<Platform>()
            .add<CubeMesh>();
    }

    register_ecs_mesh_systems(ecs);
    register_ecs_gun_systems(ecs);
    register_ecs_phys_systems(ecs);  
}

void EntitySystem::Update()
{
    ecs.progress();
}
