// 2021/02/17 13:13:02 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Audio/Sounds.h"
#include "Game/Particles.h"
#include "GUI/Cursor.h"
#include "GUI/GuiGame/WindowTarget.h"
#include "Scene/SceneC.h"


CScene::CScene(Context *context) : SceneT(context)
{
    CreateComponent<Octree>();

    ThePhysicsWorld = CreateComponent<PhysicsWorld>();

    ThePhysicsWorld->SetGravity(Vector3::ZERO);
}


CScene::~CScene()
{
    delete TheWindowTarget;
}


void CScene::Create()
{
    SceneT::Create();

    Particles::Init();

    Sounds::Init();

    TheRenderer->SetShadowMapSize(2048);

    TheWindowTarget = new WindowTarget();
    TheUIRoot->AddChild(TheWindowTarget);
    TheWindowTarget->SetVisible(false);
}
