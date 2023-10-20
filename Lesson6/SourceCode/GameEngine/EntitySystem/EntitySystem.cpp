#include "EntitySystem.h"
#include "ecsSystems.h"
#include "ecsMesh.h"
#include "ecsControl.h"
#include "ecsPhys.h"
#include "tinyxml2.h"

EntitySystem::EntitySystem(RenderEngine* renderEngine, ScriptProxy* scriptProxy)
{
    ecs.entity("scriptProxy")
        .set(ScriptProxyPtr{ scriptProxy });

    ecs.entity("renderEngine")
        .set(RenderEnginePtr{ renderEngine });

    register_ecs_mesh_systems(ecs);
    register_ecs_control_systems(ecs);
    register_ecs_phys_systems(ecs);

    auto cubeFromXML = MakeEntityFromXML("../../../Assets/XML/Entity.xml", ecs);
}

void EntitySystem::Update()
{
    ecs.progress();
}

flecs::entity EntitySystem::MakeEntityFromXML(const char* filename, flecs::world& ecs)
{
    tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
    doc->LoadFile(filename);

    auto newEntity = ecs.entity();
    tinyxml2::XMLElement* entity = doc->FirstChildElement("ENTITY");
    if (entity != nullptr)
    {
        tinyxml2::XMLElement* pos = entity->FirstChildElement("Position");
        if (pos != nullptr)
        {
            float x, y, z = 0.f;
            pos->QueryFloatAttribute("x", &x);
            pos->QueryFloatAttribute("y", &y);
            pos->QueryFloatAttribute("z", &z);
            newEntity.set(Position{ x, y, z });
        }

        tinyxml2::XMLElement* vel = entity->FirstChildElement("Velocity");
        if (vel != nullptr)
        {
            float velX, velY, velZ = 0.f;
            vel->QueryFloatAttribute("velX", &velX);
            vel->QueryFloatAttribute("velY", &velY);
            vel->QueryFloatAttribute("velZ", &velZ);
            newEntity.set(Velocity{ velX, velY, velZ });
        }

        tinyxml2::XMLElement* speed = entity->FirstChildElement("Speed");
        if (speed != nullptr)
        {
            float spd = 0.f;
            speed->QueryFloatAttribute("value", &spd);
           
            newEntity.set(Speed{ spd });
        }

        tinyxml2::XMLElement* frictionAmount = entity->FirstChildElement("FrictionAmount");
        if (frictionAmount != nullptr)
        {
            float frAmount = 0.f;
            frictionAmount->QueryFloatAttribute("value", &frAmount);

            newEntity.set(FrictionAmount{ frAmount });
        }

        tinyxml2::XMLElement* gravity = entity->FirstChildElement("Gravity");
        if (gravity != nullptr)
        {
            float valueX, valueY, valueZ = 0.f;
            gravity->QueryFloatAttribute("valueX", &valueX);
            gravity->QueryFloatAttribute("valueY", &valueY);
            gravity->QueryFloatAttribute("valueZ", &valueZ);
            newEntity.set(Gravity{ valueX, valueY, valueZ });
        }

        tinyxml2::XMLElement* bouncePlane = entity->FirstChildElement("BouncePlane");
        if (bouncePlane != nullptr)
        {
            float valueX, valueY, valueZ, valueW = 0.f;
            bouncePlane->QueryFloatAttribute("valueX", &valueX);
            bouncePlane->QueryFloatAttribute("valueY", &valueY);
            bouncePlane->QueryFloatAttribute("valueZ", &valueZ);
            bouncePlane->QueryFloatAttribute("valueW", &valueW);
            newEntity.set(BouncePlane{ valueX, valueY, valueZ, valueW });
        }

        tinyxml2::XMLElement* controllable = entity->FirstChildElement("Controllable");
        if (controllable != nullptr)
        {
            newEntity.add<Controllable>();
        }

        tinyxml2::XMLElement* cubeMesh = entity->FirstChildElement("CubeMesh");
        if (cubeMesh != nullptr)
        {
            newEntity.add<CubeMesh>();
        }

    }

    return newEntity;
}
