#pragma once


class SideCube : public Object
{
    URHO3D_OBJECT(SideCube, Object);

public:
    SideCube(Context *context = gContext);

private:
    SideCube& operator=(const SideCube&)
    {};
};