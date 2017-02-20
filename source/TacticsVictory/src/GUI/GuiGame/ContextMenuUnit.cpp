#include <stdafx.h>


#include "ContextMenuUnit.h"
#include "GUI/Elements/Label.h"
#include "Game/Objects/Units/UnitObject.h"
#include "GUI/Elements/ButtonToggled.h"
#include "GUI/GuiGame/WindowTarget.h"


ContextMenuUnit::ContextMenuUnit(Context *context) :
    lWindow(context)
{
    SetDefaultStyle(gCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    SetStyle("WindowBorder");

    SetLayout(Urho3D::LM_VERTICAL, 3, IntRect(3, 3, 3, 3));
    title = Label::Create("", 8);
    title->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_TOP);
    AddChild(title);
}

void ContextMenuUnit::Create(GameObject *object_)
{
    object = object_;
    title->SetText(object->GetName());

    if(object->GetGameObjectType() == GameObject::Unit)
    {
        CreateForUnit();
    }
}

void ContextMenuUnit::CreateForUnit()
{
    SharedPtr<ButtonToggled> button(new ButtonToggled(nullptr, "Field View", 100));
    SubscribeToEvent(button, Urho3D::E_TOGGLED, URHO3D_HANDLER(ContextMenuUnit, HandleToggledFiedView));
    AddChild(button);
}

void ContextMenuUnit::HandleToggledFiedView(StringHash, VariantMap& eventData)
{
    bool state = (bool)eventData[Urho3D::Toggled::P_STATE].GetBool();

    gWindowTarget->SetVisible(state);

    UnitObject::SetViewTargetView(state);
}