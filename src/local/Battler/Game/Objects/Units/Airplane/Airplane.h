#pragma once
#include "Game/Objects/Units/UnitObject.h"



class Airplane : public UnitObject
{
public:
    Airplane(Context *context = gContext);

private:
    DEFAULT_MEMBERS(Airplane);
};
