#pragma once


#include "Game/Objects/Ammo/AmmoObject.h"


class Mine : public AmmoObject
{
public:
    Mine(Context *context = gContext);

private:
    Mine& operator=(const Mine&)
    {};
};