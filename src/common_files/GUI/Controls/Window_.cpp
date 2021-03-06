﻿// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Cursor.h"
#include "GUI/Controls/ButtonSwitch_.h"
#include "GUI/Controls/ButtonToggled_.h"
#include "GUI/Controls/DropDownListWithTextAndButton_.h"
#include "GUI/Controls/SliderWithTextAndButtons_.h"


WindowT::WindowT(Context *context) :
    Window(context)
{
    SetDefaultStyle(TheCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    SetStyle("Window");
    SetMovable(true);
}


void WindowT::RegisterObject(Context *context)
{
    context->RegisterFactory<WindowT>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(Window);
}


bool WindowT::IsChildOfParent()
{
    return TheUIRoot->FindChild(this) != M_MAX_UNSIGNED;
}


void WindowT::Toggle()
{
    if(translator)
    {
        translator->Toggle();
    }
}


SharedPtr<LineTranslator2D> WindowT::GetTranslator()
{
    return translator;
}


bool WindowT::UnderCursor()
{
    return Window::IsInside(TheCursor->GetCursor()->GetPosition(), true);
}


SharedPtr<TButton> WindowT::AddButton(char *text, int x, int y, int width, int height)
{
    SharedPtr<TButton> retButton(new TButton(this, text, width, height));
    if (x != -1 && y != -1)
    {
        retButton->SetPosition(x, y);
    }
    AddChild(retButton);
    return retButton;
}


SharedPtr<Label> WindowT::AddLabel(char *text, bool center, int x, int y, int width, int height)
{
    SharedPtr<Label> label(Label::Create(text, center, 20, width, height));
    if (x != -1 && y != -1)
    {
        label->SetPosition(x, y);
    }
    AddChild(label);
    return label;
}


SharedPtr<ButtonToggled> WindowT::AddButtonToggled(char *text, int x, int y, int width, int height)
{
    SharedPtr<ButtonToggled> retButton(new ButtonToggled(this, text, width, height));
    retButton->SetPosition(x, y);
    AddChild(retButton);
    return retButton;
}


SharedPtr<SliderWithTextAndButtons> WindowT::AddSlider(char *text, int min, int max, int step, int x, int y, int widthText, int widthRoller)
{
    SharedPtr<SliderWithTextAndButtons> slider(new SliderWithTextAndButtons(this, text, min, max, step, widthText, widthRoller));
    AddChild(slider);
    if (x != -1 && y != -1)
    {
        slider->SetPosition(x, y);
    }
    return slider;
}


SharedPtr<DropDownListWithTextAndButton> WindowT::AddDDList(char *text, int widthText, int widthDDList, int numItems, char *items[], int x, int y)
{
    SharedPtr<DropDownListWithTextAndButton> ddList(DropDownListWithTextAndButton::Create(this, text, widthText, widthDDList, numItems, items));
    if (x != -1 && y != -1)
    {
        ddList->SetPosition(x, y);
    }
    return ddList;
}


void WindowT::SetEnabled()
{
    SetVisible(true);
}


void WindowT::SetDisabled()
{
    SetVisible(false);
}
