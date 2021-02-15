#pragma once
#include "Game/Path/WaveAlgorithm.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PathIndicator
{
public:
    PathIndicator();

    void Init();
    void Update();
    void Enable(bool enable);
    void SetStartPosition(const Coord &start);
    void Stop();

    PODVector<Coord> &GetPath();

private:
    WaveAlgorithm pathFinder;
    bool enabled = false;
    Coord start;
    PODVector<Coord> path;

    DEFAULT_MEMBERS(PathIndicator);
};