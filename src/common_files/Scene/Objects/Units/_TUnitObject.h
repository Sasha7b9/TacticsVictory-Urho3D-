// 2021/02/22 15:46:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Scene/Objects/_TGameObject.h"


class UnitObject : public GameObject
{
    URHO3D_OBJECT(UnitObject, GameObject);

public:

    static Vector<UnitObject *> storage;

protected:

    UnitObject(Context *context);

    virtual void OnNodeSet(Node *node) override;
};
