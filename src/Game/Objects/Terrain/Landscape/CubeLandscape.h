#pragma once


#include "SideCube.h"
#include "CornerCube.h"
#include "EdgeCube.h"


class CubeLandscape : public Object
{
    URHO3D_OBJECT(CubeLandscape, Object);

public:
    CubeLandscape(Context *context = gContext);
    CubeLandscape(uint row, uint col, float height);  // Create cube with one

    void Create();

    SharedPtr<SideCube>     sides[4];
    SharedPtr<CornerCube>   corners[4];
    SharedPtr<EdgeCube>     edges[2];

    uint row = 0;
    uint col = 0;
    uint layer = 0;
    bool underGround = false;
    
private:

    #define S_LEFT      0
    #define S_TOP       1
    #define S_RIGHT     2
    #define S_DOWN      3
    
    #define C_TOPLEFT   0
    #define C_TOPRIGHT  1
    #define C_DOWNRIGHT 2
    #define C_DOWNLEFT  3
    
    #define E_TOP       0
    #define E_DOWN      1
    
    CubeLandscape& operator=(const CubeLandscape&)
    {};

    void Init();

    void CreateEdges();
    void CreateEdgeTop();
    void CreateEdgeDown();
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