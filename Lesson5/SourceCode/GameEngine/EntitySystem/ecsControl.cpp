#include "ecsControl.h"
#include "ecsSystems.h"
#include "ecsPhys.h"
#include "flecs.h"
#include "ScriptProxy.h"
void register_ecs_control_systems(flecs::world &ecs)
{
  static auto scriptQuery = ecs.query<ScriptProxyPtr>();
  ecs.system<Velocity, const Speed, const Controllable>()
    .each([&](flecs::entity e, Velocity &vel, const Speed &spd, const Controllable &)
    {
       scriptQuery.each([&](ScriptProxyPtr script)
      {
        vel.x += script.ptr->UpdateMove(e.delta_time(), spd);
      });
    });
}

