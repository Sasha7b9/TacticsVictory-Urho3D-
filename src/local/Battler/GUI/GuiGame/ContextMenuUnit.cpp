// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdafx.h>
#include "ContextMenuUnit.h"
#include "GUI/Controls/Label.h"
#include "Game/Objects/Units/UnitObject.h"
#include "GUI/Controls/ButtonToggled.h"
#include "GUI/GuiGame/WindowTarget.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ContextMenuUnit::ContextMenuUnit(Context *context) :
    WindowRTS(context)
{
    SetDefaultStyle(gCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    SetStyle("WindowBorder");

    SetLayout(LM_VERTICAL, 3, IntRect(3, 3, 3, 3));
    title = Label::Create("", true, 8);
    title->SetAlignment(HA_CENTER, VA_TOP);
    AddChild(title);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ContextMenuUnit::Create(GameObject *object_)
{
    object = object_;
    title->SetText(object->GetName());

    if(object->GetGameObjectType() == GameObject::Unit)
    {
        CreateForUnit();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ContextMenuUnit::CreateForUnit()
{
    SharedPtr<ButtonToggled> button(new ButtonToggled(nullptr, "Field View", 100));
    SubscribeToEvent(button, E_TOGGLED, URHO3D_HANDLER(ContextMenuUnit, HandleToggledFiedView));
    AddChild(button);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ContextMenuUnit::HandleToggledFiedView(StringHash, VariantMap& eventData) //-V2009
{
    bool state = (bool)eventData[Toggled::P_STATE].GetBool();

    gWindowTarget->SetVisible(state);

    UnitObject::SetViewTargetView(state);
}