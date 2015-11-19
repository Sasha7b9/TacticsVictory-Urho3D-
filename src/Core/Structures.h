#pragma once


#include "Game/Objects/Terrain/Terrain.h"


#pragma warning(push)
#pragma warning(disable:4520)
struct Coord
{
    Coord(uint row_ = 0U, uint col_ = 0U) : row(row_), col(col_)
    {}

    uint row = 0;
    uint col = 0;

    bool operator ==(const Coord& rhs) const
    {
        return row == rhs.row && col == rhs.col;
    }
    Coord& operator =(const Coord& rhs)
    {
        row = rhs.row;
        col = rhs.col;
        return *this;
    }

    Vector3 ToVector3() const
    {
        Vector3 retValue;

        retValue.x_ = (float)col + 0.5f;
        retValue.y_ = gTerrain->GetHeight(row, col);
        retValue.z_ = -(float)row - 0.5f;

        return retValue;
    }
};
#pragma warning(pop)