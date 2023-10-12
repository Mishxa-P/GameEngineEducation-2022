#include "ScriptProxy.h"
#include "InputHandler.h"

#include <fstream>


void ScriptProxy::InitMove(const char* filename)
{
    std::ifstream file(filename);
    std::stringstream strStream;
    strStream << file.rdbuf();
    std::string luaCode = strStream.str();
    input = new InputHandler();
    lua_script.new_usertype<InputHandler>("InputHandler", "TestInput", &InputHandler::Test);
    lua_script.script(luaCode.c_str());

}

float ScriptProxy::UpdateMove(float deltaTime, float speed)
{
    input->Update();
    lua_script["input"] = input;
    sol::protected_function move = lua_script["UpdateMove"];
    sol::optional<float> value = move(deltaTime, speed);
    if (value)
    {
        float vel = value.value();
        return vel;
    }
    else
    {
        return 0.f;
    }   
}
