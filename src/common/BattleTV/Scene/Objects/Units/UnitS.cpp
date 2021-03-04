// 2021/02/26 17:28:47 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/ObjectS.h"
#include "Scene/Objects/Units/Accessories/Accessories_.h"
#include "Scene/Objects/Units/Ground/Tank/Tank_.h"
#include "Scene/Objects/Units/UnitS.h"


ObjectSpecific *UnitObjectSpecific::Create(UnitObject *object)
{
    return new UnitObjectSpecificS(object);
}


void UnitObjectSpecificS::Update(float timeStep)
{
    EngineT *engine = unit->engine;

    engine->Update(timeStep);

    if (engine->algorithm.IsFinished())
    {
        int direct = Rand() % 4;

        engine->GiveCommand((CommandEngine::E)(direct + 1));
    }

    GameObjectSpecificS::Update(timeStep);
}