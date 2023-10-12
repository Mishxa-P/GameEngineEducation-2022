#pragma once

#include "flecs.h"
#include "RenderEngine.h"
#include "ScriptProxy.h"

class EntitySystem
{
public:
	EntitySystem() = delete;
	EntitySystem(RenderEngine* renderEngine, ScriptProxy* scriptProxy);

	void Update();
private:
	flecs::world ecs;
};

