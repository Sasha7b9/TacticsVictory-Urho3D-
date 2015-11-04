#pragma once


class Movinator : public ULogicComponent
{
    OBJECT(Movinator);
    
public:
    Movinator(UContext *context);

    void SetMoveSpeed(float speed);
    void SetCenter(const Vector3 &vec);
    virtual void Update(float time);

private:
    Movinator& operator=(const Movinator&) {};
    float speed = 0.0f;
    float angle = 0.0f;
    Vector3 center;
};