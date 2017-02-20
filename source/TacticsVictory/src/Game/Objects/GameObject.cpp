#include <stdafx.h>


#include "GameObject.h"
#include "GUI/Elements/Cursor.h"
#include "Core/Math.h"


GameObject::GameObject(Context *context) 
    : LogicComponent(context)
{
    deltaPos = Vector3::ZERO;
}

void GameObject::Update(float)
{

}

void GameObject::EnableContextMenu()
{
    if(contextMenu == nullptr)
    {
        contextMenu = new ContextMenuUnit();
        if(type == Unit)
        {
            contextMenu->Create(this);
        }
    }
    contextMenu->SetPosition(gCursor->GetCursor()->GetPosition());
    gUIRoot->AddChild(contextMenu);
    SubscribeToEvent(Urho3D::E_MOUSEBUTTONDOWN, URHO3D_HANDLER(GameObject, HandleOnMouseDown));
}

void GameObject::HandleOnMouseDown(StringHash, VariantMap&)
{
    if(!contextMenu->UnderCursor())
    {
        UnsubscribeFromEvent(Urho3D::E_MOUSEBUTTONDOWN);

        gUIRoot->RemoveChild(contextMenu);
    }
}

char *GameObject::GetName()
{
    return name;
}

GameObject::Type GameObject::GetGameObjectType()
{
    return type;
}

void GameObject::SetSelected(bool selected_)
{
    selected = selected_;
}

bool GameObject::IsSelected()
{
    return selected;
}

Vector3 GameObject::GetPosition()
{
    return node_->GetPosition() - deltaPos;
}

void GameObject::SetPosition(const Vector3& pos)
{
    node_->SetPosition(pos + deltaPos);
}

void GameObject::Normalize(float k)
{
    Vector3 pos = GetPosition();
    node_->SetPosition({0.0f, 0.0f, 0.0f});
    node_->SetScale(1.0f);

    BoundingBox box = modelObject->GetModel()->GetBoundingBox();

    Vector3 delta = box.max_ - box.min_;

    float divider = Math::Max(delta.x_, delta.y_, delta.z_);

    Vector3 scale = {k / divider, k / divider, k / divider};

    deltaPos.y_ = -box.min_.y_ / divider * k;
    deltaPos.z_ = -(box.max_.z_ + box.min_.z_) / 2.0f / divider * k;
    deltaPos.x_ = (box.max_.x_ + box.min_.x_) / 2.0f / divider * k;

    node_->SetScale(scale);

    SetPosition(pos);
}

Node* GameObject::GetNode()
{
    return node_;
}

void GameObject::SetCoord(const Coord& coord)
{
    SetPosition(coord.ToVector3());
}