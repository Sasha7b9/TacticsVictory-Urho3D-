﻿// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Battle.h"
#include "Game/Logic/Rotator_.h"
#include "Game/Logic/SunEngine_.h"
#include "Scene/Level_.h"
#include "Scene/Scene_.h"
#include "Utils/Log_.h"
#include "Utils/Settings.h"


#pragma warning(push)
#pragma warning(disable:4100)
URHO3D_DEFINE_APPLICATION_MAIN(Battle)
#pragma warning(pop)


Battle::Battle(Context* context) :
    Application(context)
{
    TheContext = context;
}


void Battle::Setup()
{
    TheBattle = this;

    GetSubsystems();

    OpenLog();

    TheSet = new Settings();

    TheSet->Load();

    TuneEngineParameters();  
}


void Battle::GetSubsystems()
{
    TheCache = GetSubsystem<ResourceCache>();
    TheFileSystem = GetSubsystem<FileSystem>();
    TheTime = GetSubsystem<Time>();
    TheProfiler = GetSubsystem<Profiler>();
    TheEngine = GetSubsystem<Engine>();
    TheLocalization = GetSubsystem<Localization>();

    CreateScriptSystem();
}


void Battle::TuneEngineParameters()
{
    engineParameters_[EP_LOG_NAME] = GetSubsystem<FileSystem>()->GetAppPreferencesDir("urho3d", "logs") + GetTypeName() + ".log";
    engineParameters_[EP_HEADLESS] = true;

    if (!engineParameters_.Contains(EP_RESOURCE_PREFIX_PATHS))
#ifdef DEBUG
        engineParameters_[EP_RESOURCE_PREFIX_PATHS] = ";../../../../../../out/debug";
#else
        engineParameters_[EP_RESOURCE_PREFIX_PATHS] = ";../../../../../../out/release";
#endif

    TheCache->AddResourceDir(RESOURCES_DIR);
}


void Battle::Start()
{
    PROFILER_FUNC_ENTER();

    GetSubsystems();

    Application::Start();

    SetLocalization();

    RegistrationComponets();

    TheScene = new SceneT();

    TheScene->CreateComponent<Octree>();
    ThePhysicsWorld = TheScene->CreateComponent<PhysicsWorld>();
    ThePhysicsWorld->SetGravity(Vector3::ZERO);
    scene = new SceneT();

    CreateScriptSystem();

    RegistrationComponets();

    scene->Create();

    LOGINFO("Загружаю настройки");
    
    TheLevel = new Level();

    SubscribeToEvents();

    PROFILER_FUNC_LEAVE();
}


void Battle::Stop()
{
    engine_->DumpResources(true);
    //engine_->DumpProfiler();
    delete TheScene;
    delete scene;
    delete TheLevel;
    TheSet->Save();
    delete TheSet;
    TheLog->Close();
    delete TheLog;
}


void Battle::SetLocalization()
{
    TheLocalization = GetSubsystem<Localization>();
    TheLocalization->LoadJSONFile("Strings.json");
    TheLocalization->SetLanguage("ru");
}


static void MessageCallback(const asSMessageInfo *msg, void *)
{
    const char *type = "AS ERROR ";
    if (msg->type == asMSGTYPE_WARNING)
        type = "AS WARN ";
    else if (msg->type == asMSGTYPE_INFORMATION)
        type = "AS INFO ";

    LOGINFOF("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message); //-V111
}


void Battle::CreateScriptSystem()
{
    TheContext->RegisterSubsystem(new Script(TheContext));
    TheScript = GetSubsystem<Script>();
    TheScript->GetScriptEngine()->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);
}


void Battle::RegistrationComponets()
{
    SunEngine::RegisterObject();
    Rotator::RegisterObject();

    SceneT::RegisterObject();
}


void Battle::SubscribeToEvents()
{
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Battle, HandleUpdate));
    SubscribeToEvent(E_POSTUPDATE, URHO3D_HANDLER(Battle, HandlePostUpdate));
}


void Battle::OpenLog()
{
    TheLog = new TLog();
    char buffer[50];
    srand(static_cast<uint>(time(static_cast<time_t*>(0)))); //-V202

    sprintf_s(buffer, 50, "TV.log");

    TheLog->Open(buffer);
    TheLog->SetLevel(LOG_DEBUG);
}
