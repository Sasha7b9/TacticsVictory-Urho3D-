#pragma once


#include "Game/Objects/Units/UnitObject.h"


class Robot : public UnitObject
{
public:
    Robot(Context *context = gContext);

private:
    Robot& operator=(const Robot&)
    {};
};