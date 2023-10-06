#include "ecsControl.h"
#include "ecsSystems.h"
#include "ecsPhys.h"
#include "ecsMesh.h"
#include "ecsGun.h"
#include "flecs.h"
#include "../InputHandler.h"


void register_ecs_gun_systems(flecs::world& ecs)
{
    static auto inputQuery = ecs.query<InputHandlerPtr>();

    ecs.system<Position, const Gun>()
        .each([&](Position& pos, const Gun&)
            {
                inputQuery.each([&](InputHandlerPtr input)
                    {
                        if (input.ptr->GetInputState().test(eIC_GoUp))
                        {
                            if (pos.y < 25)
                            {
                                pos.y += 0.5f;
                            }
                        }
                           
                        if (input.ptr->GetInputState().test(eIC_GoDown))
                        {
                            if (pos.y > -18)
                            {
                                pos.y -= 0.5f;
                            }
                        }       
                    });
            });

    ecs.system <const Position, const Gun, const BulletSpeed, CurrentAmmo, const ShootCooldown, CurrentShootCooldown>()
        .each([&](flecs::entity e, const Position& pos, const Gun& gun, const BulletSpeed& speed,
            CurrentAmmo& ammo, const ShootCooldown& cd, CurrentShootCooldown& currentCd)
            {
                inputQuery.each([&](InputHandlerPtr input)
                    {
                        if (input.ptr->GetInputState().test(eIC_Fire))
                        {
                            currentCd.val -= e.delta_time();
                            if (currentCd.val <= 0.f && ammo.val > 0)
                            {
                                currentCd.val = cd.val;
                                e.world().entity()
                                    .set(Position{ pos.x + 2.f, pos.y, pos.z })
                                    .set(Velocity{ speed.val, 0.f, 0.f })
                                    .set(FrictionAmount{ 0.001f })
                                    .set(Gravity{ 0.f, -12.f, 0.f })
                                    .set(BulletLifeTime{ 5.0f })
                                    .add<Bullet>()
                                    .add<CubeMesh>();
                                ammo.val -= 1;
                            }
                        }
                    });
            });

    ecs.system<const Gun, const Reload, CurrentReload, const MaxAmmo, CurrentAmmo>()
        .each([&](flecs::entity e, const Gun& gun, const Reload& reload, CurrentReload& curReload, const MaxAmmo& maxAmmo, CurrentAmmo& ammo)
            {
                if (ammo.val <= 0)
                {
                    curReload.val -= e.delta_time();
                    if (curReload.val <= 0.f)
                    {
                        curReload.val = reload.val;
                        ammo.val = maxAmmo.val;
                    }
                }
            });

    static auto PlatformQuery = ecs.query<const Position, const Platform>();

    ecs.system<Velocity, Position, const Bullet, Gravity>()
        .each([&](flecs::entity e, Velocity& vel, Position& bulletPos, const Bullet& bullet, Gravity& grav)
            {
                PlatformQuery.each([&](const Position& platformPos, const Platform& platform)
                    {
                        if (abs(platformPos.y - bulletPos.y) < 2.2f && (abs(platformPos.x - bulletPos.x) < 2.2f) 
                            && abs(platformPos.z - bulletPos.z) < 2.2f)
                        {
                            vel.x = 0;
                            vel.y = 0;
                            vel.z = 0;
                            grav.y = 0;
                            if (!e.has<ShouldBeDestroyed>())
                            {
                                e.add<ShouldBeDestroyed>();
                            };
                        }
                    });
            });

    ecs.system<const Bullet, BulletLifeTime, RenderProxyPtr, const ShouldBeDestroyed>()
        .each([&](flecs::entity e, const Bullet& bullet, BulletLifeTime& lifetime, RenderProxyPtr& renderProxy, const ShouldBeDestroyed &destroy)
            {
                lifetime.val -= e.delta_time();
            
                if (lifetime.val <= 0.f)
                {
                    delete renderProxy.ptr;
                    e.destruct();
                } 
            });


    static auto BulletQuery = ecs.query<const Position, const Bullet>();

    ecs.system<const Position, const Destroyable>()
        .each([&](flecs::entity e, const Position& pos, const Destroyable& destroyable)
            {
                BulletQuery.each([&](const Position& bulletPos, const Bullet& bullet)
                    {
                        if (abs(bulletPos.y - pos.y) < 2.2f && (abs(bulletPos.x - pos.x) < 2.2f) 
                            && (abs(bulletPos.z - pos.z) < 2.2f))
                        {
                            if (!e.has<ShouldBeDestroyed>())
                            {
                                e.add<ShouldBeDestroyed>();
                            };
                        }
                    });
            });

    static auto ShouldBeDestroyedQuery = ecs.query < const Destroyable, const ShouldBeDestroyed, const AmmoBuff> ();

    ecs.system<const Gun, MaxAmmo, CurrentAmmo>()
        .each([&](const Gun&gun, MaxAmmo& maxAmmo, CurrentAmmo& ammo)
            {
                ShouldBeDestroyedQuery.each([&](const Destroyable& destroy, const ShouldBeDestroyed &shouldBeDestroyed, const AmmoBuff& buff)
                    {
                        maxAmmo.val += buff.val;
                        ammo.val += buff.val;
                    });
            });


    ecs.system<const Destroyable, const ShouldBeDestroyed, RenderProxyPtr>()
        .each([&](flecs::entity e, const Destroyable& destroyable, const ShouldBeDestroyed& destroy, RenderProxyPtr& renderProxy)
            {
                delete renderProxy.ptr;
                e.destruct();
            });

}
