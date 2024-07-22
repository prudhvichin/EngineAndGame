#include "gameFramework/GameApplication.h"
#include "Level/GameLevelOne.h"
#include "Level/MainMenuLevel.h"
#include "framework/AssetManager.h"
#include "config.h"
ly::Application* GetApplication()
{
    return new ly::GameApplication{};
}

namespace ly
{
    GameApplication::GameApplication()
        : Application{ 540, 980, "Spaceship warfare x64", sf::Style::Titlebar | sf::Style::Close }
    {
        AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
        weak<MainMenuLevel> newWorld = LoadWorld<MainMenuLevel>();
    }
}

// Ensure WinMain is not inside any namespace
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    InitializeConsole();

    // Create and run the application
    ly::Application* app = GetApplication();
    app->Run(); // Assuming you have a Run method to start the application

    CleanupConsole();

    return 0;
}



