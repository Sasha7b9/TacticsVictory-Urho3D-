// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdafx.h>
#include "Rocket.h"
#include "Core/Math.h"
#include "Game/Objects/Units/Tank/Tank.h"
#include "Game/Objects/GameObjectEvents.h"
#include "Core/Camera.h"
#include "Game/Sounds.h"
#include "Game/Particles.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ThreadRocket : public Thread
{
public:
    ThreadRocket() : Thread()
    {
        //Run();
    };
    virtual void ThreadFunction();
    void SetParameters(uint startIndex, uint endIndex);
    bool InProcess()
    {
        return inProcess;
    }
    void Execute()
    {
        execute = true;
    }
    
private:
    uint start = 0;
    uint end = 0;
    bool inProcess = false;
    bool execute = false;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static PODVector<Rocket*> rockets;
static ThreadRocket threads[8];


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Rocket::Rocket(Context *context)
    : AmmoObject(context)
{
    if (rockets.Size() == 0)
    {
//        SubscribeToEvent(E_POSTRENDERUPDATE, URHO3D_HANDLER(Rocket, HandlePostRenderUpdate));
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Rocket::~Rocket()
{
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Rocket::RegisterObject(Context *context)
{
    context->RegisterFactory<Rocket>();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Rocket::Init(const Vector3 &speedShooter, const Vector3 &position_, Tank *target_)
{
    state = Begin;
    time = 0.0f;
    attackedUnit = nullptr;
    collisionWithTerrain = false;

    if (!model)
    {
        LoadFromFile();
        Normalize();
        CreateSmoke();
    }

    target = target_;
    position = position_;
    absSpeed = speedShooter.Length() * startSpeedKoeff;
    if(absSpeed < fabs(0.1f))
    {
        absSpeed = startSpeedKoeff;
    }
    speed = Vector3(speedShooter.x_, absSpeed, speedShooter.z_);

    rotate = Quaternion(Vector3::UP, Vector3::UP);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
SharedPtr<Rocket> Rocket::Create(const Vector3 &speedShooter, const Vector3 &position, Tank *target)
{
    SharedPtr<Rocket> rocket;

    uint size = rockets.Size();
    for(uint i = 0; i < size; i++)
    {
        Rocket* rock = rockets[i];
        if(!rock->node_->IsEnabled())
        {
            rocket = rock;
            rocket->Init(speedShooter, position, target);
            gScene->AddChild(rocket->node_);
            rocket->smokeNode->SetEnabled(true);
            rocket->node_->SetEnabled(true);
            break;
        }
    }

    if (rocket == nullptr)
    {
        SharedPtr<Node> node(gScene->CreateChild("Rocket"));
        if (rockets.Size())
        {
            rocket = dynamic_cast<Rocket*>(node->CloneComponent(rockets[0]->node_->GetComponent<Rocket>()));
        }
        else
        {
            rocket = node->CreateComponent<Rocket>();
        }
        rocket->Init(speedShooter, position, target);
        rockets.Push(rocket);
    }

    return rocket;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Rocket::LoadFromFile()
{
    if (rockets.Size())
    {
        model = dynamic_cast<StaticModel*>(node_->CloneComponent(rockets[0]->node_->GetComponent<StaticModel>()));
    }
    if (!model)
    {
        model = node_->CreateComponent<StaticModel>();
        model->SetModel(gCache->GetResource<Model>("Models/Rocket.mdl"));
        model->ApplyMaterialList("Models/Rocket.txt");
    }
    model->SetViewMask(VIEW_MASK_FOR_EFFECTS);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Rocket::Normalize()
{
    node_->SetPosition({0.0f, 0.0f, 0.0f});
    node_->SetScale(1.0f);

    BoundingBox box = model->GetModel()->GetBoundingBox();

    Vector3 delta = box.max_ - box.min_;

    float divider = Math::Max(delta.x_, delta.y_, delta.z_);

    float k = 0.4f;
    scale = {k / divider, k / divider, k / divider};

    deltaPos.y_ = -box.min_.y_ / divider * k;
    deltaPos.z_ = -(box.max_.z_ + box.min_.z_) / 2.0f / divider * k;
    deltaPos.x_ = (box.max_.x_ + box.min_.x_) / 2.0f / divider * k;

    node_->SetScale(scale);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Rocket::UpdateBegin()
{
    position += speed * dT;

    time += dT;

    if(position.y_ > heightBeginExcortTarget)
    {
        state = EscortTarget;

        speed.x_ = 0.0f;
        speed.z_ = 0.0f;
        speed.y_ = absSpeed;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Rocket::UpdateEscortTarget()
{
    // Calculate necessary angle to target
    Vector3 dirToTarget = target->GetPosition() + Vector3(0.0f, 0.25f, 0.0f) - position;
    dirToTarget.Normalize();

    Vector3 dir = speed;
    dir.Normalize();

    float angleNeed = dir.Angle(dirToTarget);

    float angleCan = rotateSpeed * dT;

    time += dT;

    Vector3 axisRotate = dir.CrossProduct(dirToTarget);

    if(angleCan >= angleNeed)
    {
        rotate = Quaternion(Vector3::UP, dirToTarget);

        Quaternion qutRotate(angleNeed, axisRotate);
        speed = qutRotate * speed;
    }
    else
    {
        Quaternion qutRotate(angleCan, axisRotate);
        speed = qutRotate * speed;

        rotate = Quaternion(Vector3::UP, speed);
    }

    position += speed * dT;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Rocket::CreateSmoke()
{
    const uint NUM_BILLBOARDS = 50;

    smokeNode = node_->CreateChild("Smoke");
    smokeNode->SetScale(1.0f);

    billboardObjectSmoke = smokeNode->CreateComponent<BillboardSet>();
    billboardObjectSmoke->SetViewMask(VIEW_MASK_FOR_EFFECTS);
    billboardObjectSmoke->SetNumBillboards(NUM_BILLBOARDS);
    billboardObjectSmoke->SetMaterial(gCache->GetResource<Material>("Materials/RocketSmoke.xml"));
    billboardObjectSmoke->SetSorted(false);

    for(uint j = 0; j < NUM_BILLBOARDS; ++j)
    {
        Billboard *bb = billboardObjectSmoke->GetBillboard(j);
        bb->position_ = Vector3(Random(10.0f) - 5.0f, Random(10.0f) - 5.0f, Random(10.0f) - 5.0f);
        bb->size_ = Vector2(Random(2.0f) + 3.0f, Random(2.0f) + 3.0f);
        bb->rotation_ = Random() * 360.0f;
        bb->enabled_ = true;

        billboardsSmoke.Push(bb);
        rotBillboardSmoke.Push(bb->rotation_);
    }

    billboardObjectSmoke->Commit();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Rocket::CalculateAnimate()
{
    const float BILLBOARD_ROTATION_SPEED = 500.0f;

    for (float &rotation : rotBillboardSmoke)
    {
        rotation += BILLBOARD_ROTATION_SPEED * dT;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Rocket::AnimateSmoke()
{
    uint size = billboardsSmoke.Size();
    for(uint i = 0; i < size; i++)
    {
        billboardsSmoke[i]->rotation_ = rotBillboardSmoke[i];
    }

    /*
    Vector3 scale = billboardObjectSmoke->GetNode()->GetScale();

    float min = 0.8f;
    float max = 2.0f;

    do
    {
        scale *= Random(0.9f, 1.1f);
    } while((scale.x_ < min || scale.x_ > max) &&
        (scale.y_ < min || scale.y_ > max) &&
            (scale.z_ , min || scale.z_ > max));
    billboardObjectSmoke->GetNode()->SetScale(scale);
    */

    billboardObjectSmoke->Commit();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Rocket::UpdateOn()
{
    if(!isCalculated)
    {
        typedef void(Rocket::* FuncUpdate)();
        static FuncUpdate funcs[] =
        {
            &Rocket::UpdateBegin,
            &Rocket::UpdateEscortTarget
        };

        if(state != Begin && (gTime->GetElapsedTime() - timePrevRaycast) > 0.2f)
        {
            timePrevRaycast = gTime->GetElapsedTime();
            VerifyOnIntersectionTerrain();
        }

        FuncUpdate func = funcs[static_cast<int>(state)];
        (this->*func)();

        CalculateAnimate();
        
        isCalculated = true;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ThreadRocket::SetParameters(uint startIndex, uint endIndex)
{
    start = startIndex;
    end = endIndex;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ThreadRocket::ThreadFunction()
{
    if(IN_PAUSE)
    {
        return;
    }
    /*
    while(true)
    {
        while(!execute)
        {
            Sleep(1);
        };

        execute = false;

        inProcess = true;
        */

        for(uint i = start; i <= end; i++)
        {
            Rocket *rocket = rockets[i];

            if(rocket->mutex.TryAcquire())
            {
                if(rocket->node_->IsEnabled())
                {
                    rocket->UpdateOn();
                }
                rocket->mutex.Release();
            }
        }
        /*

        inProcess = false;
    }
    */
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Rocket::SetParameters(float timeStep)
{
    dT = timeStep;
    
    node_->SetPosition(position);
    node_->SetRotation(rotate);
    
    AnimateSmoke();

    if (collisionWithTerrain || (time > rangeTime))
    {
        Sounds::Play(Sound_Explosion, position);

        Particles::EmittingStatic(Explosion_Terrain, node_->GetPosition());

        smokeNode->SetEnabled(false);
        node_->SetEnabled(false);
    }
    else if (attackedUnit)
    {
        Sounds::Play(Sound_Explosion, position);
    
        VariantMap eventData = GetEventDataMap();
        eventData[AmmoEvent::P_TYPE] = Hit_Missile;
        eventData[AmmoEvent::P_OBJECT] = attackedUnit;
        SendEvent(E_HIT, eventData);
        smokeNode->SetEnabled(false);
        node_->SetEnabled(false);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Rocket::StopAllThreads()
{
    static uint numCPU = 1; // GetNumLogicalCPUs();

    for(uint i = 0; i < numCPU; i++)
    {
        while(threads[i].InProcess())
        {
        };
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Rocket::UpdateAll(float timeStep)
{
    gProfiler->BeginBlock("Rocket::UpdateAll");

    static uint numCPU = 1; // GetNumLogicalCPUs();

    uint size = rockets.Size();

    for(uint i = 0; i < size; i++)
    {
        rockets[i]->isCalculated = false;
        if (rockets[i]->node_->IsEnabled())
        {
            rockets[i]->SetParameters(timeStep);
        }
    }

    if(size > 0)
    {
        for(uint i = 0; i < numCPU; i++)
        {
            threads[i].SetParameters(0, size - 1);
            threads[i].ThreadFunction();
            //threads[i].Execute();
        }
    }

    //StopAllThreads();

    gProfiler->EndBlock();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Rocket::VerifyOnIntersectionTerrain()
{
    Vector3 direction = speed;
    direction.Normalize();
    Ray ray(position, direction);
    PODVector<RayQueryResult> results;
    RayOctreeQuery query(results, ray, RAY_TRIANGLE, 0.5f, DRAWABLE_GEOMETRY, VIEW_MASK_FOR_MISSILE);
    gScene->GetComponent<Octree>()->Raycast(query);

    if (results.Size())
    {
        for (auto result : results)
        {
            String node = result.drawable_->GetNode()->GetName();
            if (node == NODE_TANK)
            {
                attackedUnit = dynamic_cast<Tank*>(result.drawable_->GetNode()->GetVar("PointerTank").GetPtr());
                return;
            }
            else if (node == NODE_TERRAIN)
            {
                collisionWithTerrain = true;
                return;
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Rocket::HandlePostRenderUpdate(StringHash, VariantMap&)
{
    for (uint i = 0; i < rockets.Size(); i++)
    {
        if (rockets[i]->node_->IsEnabled())
        {
//            Rocket *rocket = rockets[i];
            //gDebugRenderer->AddSphere(Sphere(rockets[i]->node_->GetPosition(), 0.3f), Color::BLUE);

        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Rocket::DeleteAll()
{
    static uint numCPU = GetNumLogicalCPUs();

    for(uint i = 0; i < numCPU; i++)
    {
        if(threads[i].InProcess())
        {
        };
    }
}