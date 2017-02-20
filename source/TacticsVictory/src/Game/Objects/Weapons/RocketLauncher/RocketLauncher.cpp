#include <stdafx.h>


#include "RocketLauncher.h"
#include "Game/Objects/Units/Tank/Tank.h"
#include "Game/Objects/GameObjectEvents.h"
#include "Game/Objects/Ammo/Rocket/Rocket.h"


RocketLauncher::RocketLauncher(Context *context, Tank *tank) :
    WeaponObject(context)
{
    this->tank = tank;
}

void RocketLauncher::Init()
{
    timeElapsedAfterShoot = Random(timeRecharge);
}

void RocketLauncher::Update(float deltaStep)
{
    if(timeElapsedAfterShoot != 0.0f)
    {
        timeElapsedAfterShoot += deltaStep;
    }

    if(timeElapsedAfterShoot > timeRecharge)
    {
        for(auto target : gTanks)
        {
            if(target != tank)
            {
                float distance = (tank->GetPosition() - target->GetPosition()).Length();

                if(distance < radiusDetect)
                {
                    if(TargetInPointView(target))
                    {
                        break;
                    }
                }
            }
        }
    }
}

bool RocketLauncher::TargetInPointView(Tank* target)
{
    if(timeElapsedAfterShoot >= timeRecharge && (gTime->GetElapsedTime() - timePrevRaycast) > 0.5f)
    {
        timePrevRaycast = gTime->GetElapsedTime();

        Vector3 position = tank->GetNode()->GetComponent<StaticModel>()->GetWorldBoundingBox().Center();
        Vector3 posTarget = target->GetNode()->GetComponent<StaticModel>()->GetWorldBoundingBox().Center();

        Vector3 direction = posTarget - position;
        direction.Normalize();

        Ray ray(position, direction);

        PODVector<RayQueryResult> results;
        RayOctreeQuery query(results, ray, Urho3D::RAY_TRIANGLE, radiusDetect * 2.0f, Urho3D::DRAWABLE_GEOMETRY, VIEW_MASK_FOR_MISSILE);
        gScene->GetComponent<Octree>()->Raycast(query);

        while(results.Size() && results[0].drawable_->GetNode() == tank->GetNode())
        {
            results.Erase(0, 1);
        }

        if(results.Size() && results[0].drawable_->GetNode() == target->GetNode())
        {
            SharedPtr<Rocket> rocket(Rocket::Create(tank->GetSpeed(), tank->GetPosition(), target));
            timeElapsedAfterShoot = 1e-6f;
            return true;
        }
    }
    return false;
}