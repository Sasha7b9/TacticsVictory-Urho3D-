#pragma once


#include "Game/Objects/Buildings/BuildingObject.h"


class Shaft : public BuildingObject
{
public:
    Shaft(Context *context = gContext);

private:
    Shaft& operator=(const Shaft&)
    {};
};