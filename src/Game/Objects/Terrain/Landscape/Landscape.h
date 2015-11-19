#pragma once


#include "LayerLandscape.h"


class Landscape : public Object
{
    URHO3D_OBJECT(Landscape, Object);

public:
    Landscape(Context *context = gContext);
    ~Landscape();


    void CreateFromVector(Vector<Vector<float>> &level);

    void SaveToFile(char *nameFile);

private:
    Landscape& operator=(const Landscape&)
    {};

    Vector<SharedPtr<LayerLandscape>> ground;          // Height (0, 1, 2, 3, ...)
    Vector<SharedPtr<LayerLandscape>> underGround;     // Height [0, -1, -2, ...)

    void AddCube(SharedPtr<CubeLandscape> &cube);
    void CreateLayers();
    void Build();
};