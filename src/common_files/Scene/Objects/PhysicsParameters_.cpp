// 2021/03/05 20:39:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/PhysicsParameters_.h"


Vector3 PositionPP::Get() const
{
    return object->GetObjectNode()->GetPosition() /*- object->shift->position*/;
}


void PositionPP::Set(const Vector3 &position)
{
    object->GetObjectNode()->SetPosition(position /* + object->shift->position*/);
}


Vector3 DirectionPP::Get() const
{
    return { -1.0f, 0.0f, 0.0f };
}
