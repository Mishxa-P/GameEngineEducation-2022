// GameEngine.cpp : Defines the entry point for the application.
//

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif
#include <random>
#include "GameEngine.h"
#include "RenderEngine.h"
#include "RenderThread.h"
#include "CubeGameObject.h"
#include "GameTimer.h"
#include "InputHandler.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // Enable run-time memory check for debug builds.
#if defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    GameTimer timer;

    RenderEngine* renderEngine = new RenderEngine(hInstance);
    RenderThread* renderThread = renderEngine->GetRT();
    InputHandler* inputHandler = new InputHandler();

    std::list<GameObject*> gameObjects;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, 2); 

    float x = -25.0;
    float z = -20.0;

    for (int i = 0; i < 100; i++)
    {
        if (x < 25.0f)
        {
            x += 5.0f;
        }
        else
        {
            z += 5.0f;
            x = -20.0f;
        }

        switch (distr(gen))
        {
        case JumpingCube:
            gameObjects.push_back(new CubeGameObject(JumpingCube, x, 0.0f, z));
            break;
        case ControllableCube:
            gameObjects.push_back(new CubeGameObject(ControllableCube, x, 0.0f, z));
            break;
        case MovableCube:
            gameObjects.push_back(new CubeGameObject(MovableCube, x, 0.0f, z));
            break;
        }
    }
    for (GameObject* object : gameObjects)
    {
        renderThread->EnqueueCommand(RC_CreateCubeRenderObject, object->GetRenderProxy());
    }

    MSG msg = { 0 };

    timer.Start();
    timer.Reset();

    float newPositionX = 0.0f;

    // Main message loop:
    while (msg.message != (WM_QUIT | WM_CLOSE))
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            inputHandler->Update();
            timer.Tick();
            if (inputHandler->GetInputState().test(eIC_GoLeft))
            {
                for (GameObject* object : gameObjects)
                {
                    object->MoveLeft(timer.DeltaTime());
                }
            }
            if (inputHandler->GetInputState().test(eIC_GoRight))
            {
                for (GameObject* object : gameObjects)
                {
                    object->MoveRight(timer.DeltaTime());
                }
            }
            for (GameObject* object : gameObjects)
            {
                object->Update(timer.DeltaTime());
            }
            renderThread->OnEndFrame();
        }
    }

    return (int) msg.wParam;
}
