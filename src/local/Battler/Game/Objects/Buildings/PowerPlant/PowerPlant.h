#pragma once
#include "Game/Objects/Buildings/BuildingObject.h"



class PowerPlant : public BuildingObject
{
public:
    PowerPlant(Context *context = gContext);

private:
    DEFAULT_MEMBERS(PowerPlant);
};
