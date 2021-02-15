// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdafx.h>
#include "Slider.h"



lSlider::lSlider(Context *context) :
    Slider(context)
{

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void lSlider::RegisterObject(Context *context)
{
    context->RegisterFactory<lSlider>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(Slider);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
SharedPtr<lSlider> lSlider::Create(Window *window, char *text_)
{
    SharedPtr<Text> text(new Text(gContext));
    text->SetText(gLocalization->Get(text_));
    text->SetStyle("MainMenuButton");
    window->AddChild(text);

    SharedPtr<lSlider> slider(gUIRoot->CreateChild<lSlider>());
    slider->SetMinHeight(15);
    window->AddChild(slider);
    slider->SetRange(1.0f);
    slider->SetStyle("Slider");
    window->AddChild(slider);
    return slider;
}
