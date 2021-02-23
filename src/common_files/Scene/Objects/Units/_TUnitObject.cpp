// 2021/02/22 15:46:30 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/_TUnitObject.h"


Vector<UnitObject *> UnitObject::storage;


UnitObject::UnitObject(Context *context) : GameObject(context)
{
}


void UnitObject::OnNodeSet(Node *node)
{
    if (node)
    {
        node->SetVar("isUnit", true);
    }
}
