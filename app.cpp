#include "app.h"
#include <Urho3D/Input/Input.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Engine/EngineDefs.h>
#include <Urho3D/Engine/DebugHud.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>

#include <iostream>


#define out(a) std::cout << a << std::endl;

App::App(U::Context* context) :
    U::Application(context)
{

}

void App::Setup()
{
    // Modify engine startup parameters
    engineParameters_[U::EP_WINDOW_TITLE] = GetTypeName();
    engineParameters_[U::EP_LOG_NAME]     = GetSubsystem<U::FileSystem>()->GetAppPreferencesDir("urho3d", "logs") + GetTypeName() + ".log";
    engineParameters_[U::EP_FULL_SCREEN]  = false;
    engineParameters_[U::EP_HEADLESS]     = false;
    engineParameters_[U::EP_SOUND]        = false;

    // Construct a search path to find the resource prefix with two entries:
    // The first entry is an empty path which will be substituted with program/bin directory -- this entry is for binary when it is still in build tree
    // The second and third entries are possible relative paths from the installed program/bin directory to the asset directory --
    //these entries are for binary when it is in the Urho3D SDK installation location
    if (!engineParameters_.Contains(U::EP_RESOURCE_PREFIX_PATHS))
        engineParameters_[U::EP_RESOURCE_PREFIX_PATHS] = ";../share/Resources;../share/Urho3D/Resources";

}

void App::Start()
{
    // Subscribe key down event
    SubscribeToEvent(U::E_KEYDOWN, URHO3D_HANDLER(App, onKeyDown));
    // Subscribe key up event
    SubscribeToEvent(U::E_KEYUP, URHO3D_HANDLER(App, onKeyUp));
    // Subscribe scene update event
    SubscribeToEvent(U::E_SCENEUPDATE, URHO3D_HANDLER(App, onSceneUpdate));
}

void App::Stop()
{
    engine_->DumpResources(true);
}

void App::onSceneUpdate(U::StringHash, U::VariantMap& eventData)
{

}

void App::onKeyDown(U::StringHash, U::VariantMap& eventData)
{
    namespace K = U::KeyDown;
    int key = eventData[K::P_KEY].GetInt();

    switch(key)
    {
        case U::KEY_UP :
            out("up");
            break;
        case U::KEY_DOWN :
            out("down");
            break;
        case U::KEY_LEFT :
            out("left")
            break;
        case U::KEY_RIGHT :
            out("right")
            break;
        default :
            out("other")
    }

}

void App::onKeyUp(U::StringHash, U::VariantMap& eventData)
{
    out("released");
}

