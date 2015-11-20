#pragma once


#include "CubeLandscape.h"


class LayerLandscape : public Object
{
    URHO3D_OBJECT(LayerLandscape, Object);

public:
    LayerLandscape(Context *context = gContext);

    void AddCube(SharedPtr<CubeLandscape> &cube);

    void Create();

    void Build();

    Vector<SharedPtr<CubeLandscape>> cubes;

private:
    LayerLandscape& operator=(const LayerLandscape&)
    {};

    SharedPtr<Geometry> geometry;
    SharedPtr<Model> model;
    SharedPtr<StaticModel> object;
};