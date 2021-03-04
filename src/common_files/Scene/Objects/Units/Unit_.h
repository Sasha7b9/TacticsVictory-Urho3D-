// 2021/02/22 15:46:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Scene/Objects/Object_.h"
#include "Scene/Objects/Units/Accessories/Engine/Engine_.h"


class UnitObject;


//----------------------------------------------------------------------------------------------------------------------
namespace UnitObjectSpecific
{
    ObjectSpecific *Create(UnitObject *object);
};


//----------------------------------------------------------------------------------------------------------------------
class UnitObject : public ObjectT
{
    URHO3D_OBJECT(UnitObject, ObjectT);

public:

    static Vector<UnitObject *> storage;

    virtual void Update(float timeStep) override;

    SharedPtr<EngineT> engine;

    virtual void Compress(VectorBuffer &buffer) override;

    virtual void Decompress(MemoryBuffer &buffer) override;

protected:

    UnitObject(Context *);

    virtual void Start() override;
};