#pragma once

#include <sol/sol.hpp>

#include "Common.h"
#include "InputHandler.h"

class SCRIPTSYSTEM_API ScriptProxy
{
public:
	void InitMove(const char* filename);
	float UpdateMove(float deltaTime, float speed);

private:
	sol::state lua_script;
	InputHandler* input;
};

