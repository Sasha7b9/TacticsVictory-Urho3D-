/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include "stdafx.h"
#include "MilitaryPlant.h"



MilitaryPlant::MilitaryPlant(Context *context) :
    BuildingObject(context)
{

}


void MilitaryPlant::RegisterObject(Context *context)
{
    context->RegisterFactory<MilitaryPlant>();
}


SharedPtr<MilitaryPlant> MilitaryPlant::Create()
{
    SharedPtr<Node> node(TheScene->CreateChild());
    SharedPtr<MilitaryPlant> plant(node->CreateComponent<MilitaryPlant>());
    plant->Init();
    return plant;
}


void MilitaryPlant::Init()
{
    LoadFromFile();
    Normalize(2.0f);
}


void MilitaryPlant::LoadFromFile()
{
    char *fileName = "Models\\Buildings\\MilitaryPlant\\MilitaryPlant.mdl";
    char *materialsName = "Models\\Buildings\\MilitaryPlant\\MilitaryPlant.txt";

    modelObject = node_->CreateComponent<StaticModel>();
    modelObject->SetViewMask(VIEW_MASK_FOR_MISSILE);
    modelObject->SetModel(TheCache->GetResource<Model>(fileName));
    modelObject->ApplyMaterialList(materialsName);
    modelObject->SetCastShadows(true);
}
