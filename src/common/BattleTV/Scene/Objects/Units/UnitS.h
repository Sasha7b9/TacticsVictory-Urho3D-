// 2021/02/26 16:01:57 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/ObjectS.h"


class UnitObjectSpecificS : public GameObjectSpecificS
{
    URHO3D_OBJECT(UnitObjectSpecificS, GameObjectSpecificS);

public:

    UnitObjectSpecificS(UnitObject *object) : GameObjectSpecificS(object), unit(object) {}

protected:

    virtual void Update(float timeStep) override;

private:

    UnitObject *unit = nullptr;
};