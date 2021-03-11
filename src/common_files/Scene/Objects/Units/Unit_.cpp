// 2021/02/22 15:46:30 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Ground/Tank/Tank_.h"
#include "Scene/Objects/Units/Unit_.h"


Vector<Unit *> Unit::storage;


Unit::Unit(Context *context, const MinPP &min, const MaxPP &max) : ObjectT(context, min, max)
{
    storage.Push(this);
}


void Unit::Start()
{
    ObjectT::Start();

    node_->SetVar(VAR_NODE_IS_UNIT, true);
}


void Unit::Update(float timeStep)
{
    ObjectT::Update(timeStep);
}


void Unit::Compress(VectorBuffer &buffer)
{
    ObjectT::Compress(buffer);
}


void Unit::Decompress(MemoryBuffer &buffer)
{
    ObjectT::Decompress(buffer);
}


bool Unit::CanMoveTo(float rowX, float colZ) const
{
    if (colZ < 0.0f || rowX < 0.0f || colZ >= TheTerrain->WidthZ() || rowX >= TheTerrain->HeightX())
    {
        return false;
    }

    if (IsFlying())
    {
        if (physics->pos.GetAltitude() >= TheTerrain->GetHeight(physics->pos.GetCoord()))
        {
            return true;
        }
    }

    return TheTerrain->GetHeight(physics->pos.GetWorld().x_, physics->pos.GetWorld().z_) ==
        TheTerrain->GetHeight(rowX, colZ);
}
