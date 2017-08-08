#ifndef APP_H
#define APP_H

#define eventParams U::StringHash stringHash, U::VariantMap& eventData

#include <Urho3D/Engine/Application.h>

namespace U = Urho3D;



class App : public U::Application
{
    URHO3D_OBJECT(App, U::Application)

public:
    App(U::Context* context);

    /// Setup before engine initialization. Modifies the engine parameters.
    virtual void Setup();
    /// Setup after engine initialization. Creates the logo, console & debug HUD.
    virtual void Start();
    /// Cleanup after the main loop. Called by Application.
    virtual void Stop();

private:
    void onSceneUpdate(eventParams);
    void onKeyDown(eventParams);
    void onKeyUp(eventParams);

};

#endif // APP_H
