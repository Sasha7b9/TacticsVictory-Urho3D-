#pragma once


#include "Game/Objects/Ammo/AmmoObject.h"


class RollingBomb : public AmmoObject
{
public:
    RollingBomb(Context *context = gContext);

private:
    RollingBomb& operator=(const RollingBomb&)
    {};
};