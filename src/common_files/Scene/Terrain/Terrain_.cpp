// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/GameObject_.h"
#include "Scene/Terrain/SegmentTerrain_.h"


Vector<Vector<PODVector<CubeTerrain*>>> TTerrain::columnsCubes;


TTerrain::TTerrain(Context *context) : Object(context)
{
}


TTerrain::~TTerrain()
{
    for(auto &row : columnsCubes)
    {
        for(auto &col : row)
        {
            for(auto &cube : col)
            {
                cube = nullptr;
            }
        }
    }
}


void TTerrain::CreateFromVector(const Vector<Vector<float>> &lev)
{
    float time = TheTime->GetElapsedTime();

    level = lev;

    CubeTerrain::terrain = this;

    uint heightX = SegmentTerrain::HEIGHT_X;
    uint widthZ = SegmentTerrain::WIDTH_Z;

    uint allRows = level.Size();
    uint allCols = level[0].Size();

    uint segmentsInX = allRows / heightX + ((allRows % heightX) == 0 ? 0 : 1);  // ������� ��������� �� X (� ������)

    uint segmentsInZ = allCols / widthZ + ((allCols % widthZ) == 0 ? 0 : 1);    // ������� ��������� �� Z (� ������)

    columnsCubes.Resize(allRows);

    for(auto &row : columnsCubes)
    {
        row.Resize(allCols);
    }

    segments.Resize(segmentsInZ);

    for(uint row0 = 0; row0 < allRows; row0 += widthZ)
    {
        uint i = row0 / widthZ;

        segments[i].Resize(segmentsInX);

        for(uint col0 = 0; col0 < allCols; col0 += heightX)
        {
            uint numRows = (row0 + widthZ > allRows) ? (allRows - row0) : widthZ;
            uint numCols = (col0 + heightX > allCols) ? (allCols - col0) : heightX;

            uint j = col0 / heightX;

            segments[i][j] = new SegmentTerrain();

            segments[i][j]->CreateFromVector(level, row0, col0, numRows, numCols);
        }
    }

    for(uint z = 0; z < segmentsInZ; z++)
    {
        for(uint x = 0; x < segmentsInX; x++)
        {
            SegmentTerrain *segment = segments[z][x];
            if(x > 0)
            {
                segment->neighbours[SegmentTerrain::LEFT] = segments[z][x - 1];
            }
            if(z > 0)
            {
                segment->neighbours[SegmentTerrain::TOP] = segments[z - 1][x];
            }
            if(x < segmentsInX - 1)
            {
                segment->neighbours[SegmentTerrain::RIGHT] = segments[z][x + 1];
            }
            if(z < segmentsInZ - 1)
            {
                segment->neighbours[SegmentTerrain::BOTTOM] = segments[z + 1][x];
            }
        }
    }

    for(auto row : segments)
    {
        for(SegmentTerrain* segment : row)
        {
            segment->Build();
        }
    }

    URHO3D_LOGINFOF("time create terrain %f sec", TheTime->GetElapsedTime() - time);
}


float TTerrain::GetHeight(uint colZ, uint rowX)
{
    return level[rowX][colZ];
}


void TTerrain::SetHeight(uint row, uint col, float height)
{
    level[row][col] = height;
}


uint TTerrain::HeightX()
{
    return level.Size();
}


uint TTerrain::WidthZ()
{
    return level[0].Size();
}


bool TTerrain::Empty()
{
    return level.Empty();
}


TPlane TTerrain::GetIntersectionPlane(Ray& /*ray*/)
{
    return TPlane::ZERO;
}


Line TTerrain::GetIntersectionEdge(Ray &/*ray*/)
{
    return Line::ZERO;
}


TPlane TTerrain::GetPlane(uint /*row*/, uint /*col*/)
{
    return TPlane::ZERO;
}


Vector<Vector<float>> TTerrain::GetMap()
{
    return level;
}


PODVector<CubeTerrain*>* TTerrain::GetColumnCubes(const CubeTerrain *cube, DIR::E dir)
{
    const int dRow[8] = { 0, -1, -1, -1, 0, 1, 1,  1};
    const int dCol[8] = {-1, -1,  0,  1, 1, 1, 0, -1};

    uint row = (uint)((int)cube->row + dRow[dir]);
    uint col = (uint)((int)cube->col + dCol[dir]);

    if(row > HeightX() - 1 || col > WidthZ() - 1)
    {
        return nullptr;
    }

    return &columnsCubes[row][col];
}


SegmentTerrain* TTerrain::GetSegmentForCoord(uint row, uint col)
{
    return segments[row / SegmentTerrain::WIDTH_Z][col / SegmentTerrain::HEIGHT_X];
}


void TTerrain::PutIn(GameObject *object, uint colZ, uint rowX)
{
    float height = GetHeight(colZ, rowX);

    object->SetPosition({ (float)rowX, height, (float)colZ });
}