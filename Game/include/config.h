#pragma once

#include <windows.h>
#include <string>

#ifdef _DEBUG
#include <iostream>
#endif

void InitializeConsole() {
#ifdef _DEBUG
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    std::cout << "Debug mode: Console window is open." << std::endl;
#endif
}

void CleanupConsole() {
#ifdef _DEBUG
    FreeConsole();
#endif
}

std::string GetResourceDir() {
#ifdef NDEBUG // Release build
    return "assets/";
#else // Debug build
    return "C:/Users/Prudhvi Chintada/Desktop/Spaceship Warfare/Spaceship Warfare/Game/assets/";
#endif
}
