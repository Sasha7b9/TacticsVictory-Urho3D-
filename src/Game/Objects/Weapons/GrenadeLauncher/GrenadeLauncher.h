#pragma once


#include "Game/Objects/Weapons/WeaponObject.h"


class GrenadeLauncher : public WeaponObject
{
public:
    GrenadeLauncher(Context *context = gContext);

private:
    GrenadeLauncher& operator=(const GrenadeLauncher&)
    {};
};