#pragma once


#include "Game/Objects/Weapons/WeaponObject.h"


class MachineGun : public WeaponObject
{
public:
    MachineGun(Context *context = gContext);

private:
    MachineGun& operator=(const MachineGun &)
    {};
};