// 2021/02/27 10:04:52 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Accessories/Engine/Logic_.h"


EngineAlgorithm *EngineCalculator::Calculate(const PhysicsComponent *component, CommandEngine::E command)
{
    EngineAlgorithm *result = new EngineAlgorithm();

    Step step(Step::Type::Move);

    step.start = component->position;
    step.end = step.start;

    if (command == CommandEngine::MoveToNorth)
    {
        step.end.x_ -= 1.0f;
    }
    else if (command == CommandEngine::MoveToEast)
    {
        step.end.z_ += 1.0f;
    }
    else if (command == CommandEngine::MoveToSouth)
    {
        step.end.x_ += 1.0f;
    }
    else if (command == CommandEngine::MoveToWest)
    {
        step.end.z_ -= 1.0f;
    }

    result->steps.Push(step);

    result->current = component->position;

    return result;
}


void EngineExecutor::Execute(SharedPtr<EngineAlgorithm> _algorithm)
{
    algorithm = _algorithm;
}
