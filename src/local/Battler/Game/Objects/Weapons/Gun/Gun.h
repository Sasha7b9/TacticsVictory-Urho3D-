#pragma once
#include "Game/Objects/Weapons/WeaponObject.h"



class Gun : public WeaponObject
{
public:
    Gun(Context *context = gContext);

private:
    DEFAULT_MEMBERS(Gun);
};
