#pragma once


enum
{
    Hit_Missile
};


URHO3D_EVENT(E_HIT, AmmoEvent)
{
    URHO3D_PARAM(P_TYPE, AmmoEventType);
    URHO3D_PARAM(P_OBJECT, GameObject);
}
