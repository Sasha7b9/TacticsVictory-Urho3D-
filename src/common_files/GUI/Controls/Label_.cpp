// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


Label::Label(Context *context) :
    Text(context)
{
    SubscribeToEvent(E_CHANGELANGUAGE, URHO3D_HANDLER(Label, HandleChangeLanguage));
}


void Label::RegisterObject(Context *context)
{
    context->RegisterFactory<Label>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(Text);
}


SharedPtr<Label> Label::Create(char *text_, bool center, int sizeFont, int width, int height)
{
    SharedPtr<Label> text(new Label());
    text->text = text_;
    text->SetFont(TheFont, (float)sizeFont);
    if (center)
    {
        text->SetAlignment(HA_CENTER, VA_CENTER);
    }

    if(width == -1 && height == -1)
    {

    }
    else if(height == -1)
    {
        text->SetFixedWidth(width);
    }
    else if(width == -1)
    {
        text->SetFixedHeight(height);
    }
    else
    {
        text->SetFixedSize(width, height);
    }

    text->SetText(text_);

    return text;
}


void Label::SetText(char *t)
{
    text = t;

    Text::SetText(TheLocalization->Get(text));
}


void Label::HandleChangeLanguage(StringHash, VariantMap&)
{
    Text::SetText((char*)TheLocalization->Get(text).CString());
}
