#pragma once


#include "SideCube.h"
#include "CornerCube.h"
#include "EdgeCube.h"


class Terrain;


class CubeTerrain : public Object
{
    URHO3D_OBJECT(CubeTerrain, Object);

public:

    enum SIDE
    {
        S_LEFT = 0,
        S_TOP = 1,
        S_RIGHT = 2,
        S_DOWN = 3
    };

    enum CORNER
    {
        C_TOPLEFT = 0,
        C_TOPRIGHT = 1,
        C_DOWNRIGHT = 2,
        C_DOWNLEFT = 3
    };

    enum EDGE
    {
        E_TOP = 0,
        E_DOWN = 1
    };

public:
    CubeTerrain(Context *context = gContext);
    CubeTerrain(uint row, uint col, float height);  // Create cube with one

    void Create();

    void BuildVertexes(PODVector<float> &vertexes, PODVector<uint> &indexes);

    Vector3& GetEdgeCoord(EDGE edge, CORNER corner);

    SharedPtr<SideCube>     sides[4];
    SharedPtr<CornerCube>   corners[4];
    SharedPtr<EdgeCube>     edges[2];

    uint row = 0;
    uint col = 0;
    uint layer = 0;
    bool underGround = false;

    static Terrain *terrain;

private:

    PODVector<float> *vertexes = nullptr;
    PODVector<uint>  *indexes = nullptr;

    CubeTerrain& operator=(const CubeTerrain&)
    {};

    void CreateEdges();
    void CreateEdgeTop();
    void CreateEdgeDown();

    void CreateSides();
    void CreateSideLeft();
    void CreateSideTop();
    void CreateSideRight();
    void CreateSideDown();

    void PushPoint(PointPlane &point);

    void BuildPlaneVerexes(PlaneCube &plane);
};

/*                     Corner_0              Corner_1
                          |                    |                                                      
                          |   Edge_0           |                                                      
                          |     |              |                                                      
                          |     |              |                                                      
                          |     |              |                                                      
                          /-----+--------------/
                        /       |            / |                           /|\ Y
                      /         |          /   |                            |
                    /                    /     |                            |    -/| Z
                  /                  / |       |                            |    /
                 |----------------| /  |       |                            |   /
                 |                |    |       |                            |  /
                 |                |    |       |                            | /         
                 |                |    |       |                            |/----------+
                 |                |    |      /                                          X
                 |                |    |    /
                 |       |        |    |   /
                 |       |        |    | /
                 |       |        |  / |/
                 |-------+--------|/  \
                         |             \
                         |              \
                         |            Corner_2
                       Side_3
*/                       