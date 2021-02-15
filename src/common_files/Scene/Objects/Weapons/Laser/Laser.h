#pragma once
#include "Scene/Objects/Weapons/WeaponObject.h"



class Laser : public WeaponObject
{
public:
    Laser(Context *context = TheContext);

private:
    DEFAULT_MEMBERS(Laser);
};