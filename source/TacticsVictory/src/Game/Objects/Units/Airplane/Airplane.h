#pragma once


#include "Game/Objects/Units/UnitObject.h"


class Airplane : public UnitObject
{
public:
    Airplane(Context *context = gContext);

private:
    Airplane& operator=(const Airplane&)
    {};
};