#pragma once
#include "Game/Objects/Ammo/AmmoObject.h"



class AirBomb : public AmmoObject
{
public:
    AirBomb(Context *context = gContext);

private:
    DEFAULT_MEMBERS(AirBomb);
};
