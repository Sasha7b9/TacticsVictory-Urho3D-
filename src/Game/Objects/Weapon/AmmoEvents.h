#pragma once


enum
{
    Hit_Missile
};


URHO3D_EVENT(E_HIT, AmmunitionEvent)
{
    URHO3D_PARAM(P_TYPE, AmmunitionEventType);
    URHO3D_PARAM(P_OBJECT, GameObject);
}