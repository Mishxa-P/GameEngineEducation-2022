// GameEngine.cpp : Defines the entry point for the application.
//

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif
#include <INIReader.h>   

#include "GameEngine.h"
#include "RenderEngine.h"
#include "RenderThread.h"
#include "CubeGameObject.h"
#include "GameTimer.h"
   

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

    GameObject* cube = new CubeGameObject();
    renderThread->EnqueueCommand(RC_CreateCubeRenderObject, cube->GetRenderProxy());

    MSG msg = { 0 };

    timer.Start();
    timer.Reset();

    float posX = 0.0f;
    float posY = 0.0f;
    char moveLeft = 'A';
    char moveRight = 'D';
    char moveUp = 'W';
    char moveDown = 'S';

    INIReader reader("actionmap.ini");
    if (reader.ParseError() != -1)
    {
        moveLeft = reader.Get("Keyboard", "MoveLeft", "A").at(0);
        moveRight = reader.Get("Keyboard", "MoveRight", "D").at(0);
        moveUp = reader.Get("Keyboard", "MoveUp", "W").at(0);
        moveDown = reader.Get("Keyboard", "MoveDown", "S").at(0);
    }
 
    // Main message loop:
    while (msg.message != (WM_QUIT | WM_CLOSE))
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            switch (msg.message)
            {
            case WM_KEYDOWN:
                if ((GetAsyncKeyState(moveLeft)))
                {
                    posX -= 1.0f;
                    cube->SetPosition(posX, posY, 0.0f);
                }
                if ((GetAsyncKeyState(moveRight)))
                {
                    posX += 1.0f;
                    cube->SetPosition(posX, posY, 0.0f);
                }
                if ((GetAsyncKeyState(moveUp)))
                {
                    posY += 1.0f;
                    cube->SetPosition(posX, posY, 0.0f);
                }
                if ((GetAsyncKeyState(moveDown)))
                {
                    posY -= 1.0f;
                    cube->SetPosition(posX, posY, 0.0f);
                }
                break;
            } 
        }
        else
        {
            float t = 0;
            timer.Tick();
            renderThread->OnEndFrame();
        }
    }

    return (int) msg.wParam;
}
