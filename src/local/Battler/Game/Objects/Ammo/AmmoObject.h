#pragma once
#include "Game/Objects/GameObject.h"



class AmmoObject : public GameObject
{
public:
    AmmoObject(Context *context = gContext);

private:
    DEFAULT_MEMBERS(AmmoObject);
};
