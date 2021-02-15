#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Rotator : public LogicComponent
{
    URHO3D_OBJECT(Rotator, LogicComponent);
    
public:
    Rotator(Context* context);
    
    void SetRotationSpeed(const Vector3& speed);
    virtual void Update(float timeStep);
    
    const Vector3& GetRotationSpeed() const { return rotationSpeed; }
    
private:
    Vector3 rotationSpeed;

    DEFAULT_MEMBERS(Rotator);
};