#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CubeTerrain;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class LayerTerrain : public Object
{
    URHO3D_OBJECT(LayerTerrain, Object);

public:
    LayerTerrain(Context *context = gContext);
    ~LayerTerrain();
    void AddCube(const SharedPtr<CubeTerrain> &cube);
    void Create();
    void Build();
    CubeTerrain* GetCube(uint row, uint col);

    Vector<SharedPtr<CubeTerrain>> cubes;

private:
    SharedPtr<Geometry> geometry;
    SharedPtr<Model> model;
    SharedPtr<StaticModel> object;

    DEFAULT_MEMBERS(LayerTerrain);
};