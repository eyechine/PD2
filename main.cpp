#include <iostream>
#include "app.h"

using className = App;

#if !defined(IOS) && !defined(TVOS)
int RunApplication()
{
    Urho3D::SharedPtr<Urho3D::Context> context(new Urho3D::Context());
    Urho3D::SharedPtr<className> application(new className(context));
    return application->Run();
}
#else
int RunApplication()
{
    Urho3D::Context* context = new Urho3D::Context();
    className* application = new className(context);
    return application->Run();
}
#endif

#if defined(_WIN32) && !defined(URHO3D_WIN32_CONSOLE)
#include <Urho3D/Core/MiniDump.h>
#include <windows.h>
#ifdef _MSC_VER
#include <crtdbg.h>
#endif
#endif

// Platform-specific main function, which in turn executes the user-defined function

// MSVC debug mode: use memory leak reporting
#if defined(_MSC_VER) && defined(_DEBUG) && !defined(URHO3D_WIN32_CONSOLE)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    Urho3D::ParseArguments(GetCommandLineW());
    return RunApplication();
}



// MSVC release mode: write minidump on crash
#elif defined(_MSC_VER) && defined(URHO3D_MINIDUMPS) && !defined(URHO3D_WIN32_CONSOLE)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
    Urho3D::ParseArguments(GetCommandLineW());
    int exitCode;
    __try
    {
        exitCode = function;
    }
    __except(Urho3D::WriteMiniDump("Urho3D", GetExceptionInformation()))
    {
    }
    return exitCode;
}




// Other Win32 or minidumps disabled: just execute the function
#elif defined(_WIN32) && !defined(URHO3D_WIN32_CONSOLE)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
    Urho3D::ParseArguments(GetCommandLineW());
    return RunApplication();
}
// Android or iOS or tvOS: use SDL_main
#elif defined(__ANDROID__) || defined(IOS) || defined(TVOS)
extern "C" int SDL_main(int argc, char** argv);
int SDL_main(int argc, char** argv)
{
    Urho3D::ParseArguments(argc, argv);
    return RunApplication();
}




// Linux or OS X: use main
#else
int main(int argc, char** argv)
{
    Urho3D::ParseArguments(argc, argv);
    std::cout << "hello you <3" << std::endl;
    return RunApplication();
}
#endif
