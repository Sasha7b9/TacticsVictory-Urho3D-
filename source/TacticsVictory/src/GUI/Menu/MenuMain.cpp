#include <stdafx.h>


#include "MenuMain.h"
#include "GUI/GUI.h"
#include "GUI/Elements/ButtonMain.h"
#include "GUI/Elements/ButtonSwitch.h"
#include "GUI/Elements/Cursor.h"
#include "GUI/Elements/Label.h"
#include "GUI/Menu/WindowConfirmExit.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MenuMain::MenuMain(Context *) :
    WindowRTS()
{
    SetLayout(LM_VERTICAL, 6, IntRect(6, 6, 6, 6));
    SetName("Main menu");

    SharedPtr<Label> text(Label::Create("Tactics Victory", 20, -1, -1));
    AddChild(text);
    
    buttonNewGame  = new ButtonMain(this, "New game");
    buttonEditor = new ButtonMain(this, "Editor");
    buttonOptions = new ButtonMain(this, "Options");
    buttonLanguage = new ButtonSwitch(this, "Language : EN");
    buttonLanguage->AddState("Language : RU");
    buttonLanguage->SetState((uint)gSet->GetInt(TV_LANGUAGE));
    buttonExit = new ButtonMain(this, "Exit");

    buttons.Push(buttonNewGame);
    buttons.Push(buttonEditor);
    buttons.Push(buttonOptions);
    buttons.Push(buttonLanguage);
    buttons.Push(buttonExit);

    SubscribeToEvent(buttonOptions, E_RELEASED, URHO3D_HANDLER(MenuMain, HandleButtonRelease));
    SubscribeToEvent(buttonEditor, E_RELEASED, URHO3D_HANDLER(MenuMain, HandleButtonRelease));
    SubscribeToEvent(buttonNewGame, E_RELEASED, URHO3D_HANDLER(MenuMain, HandleButtonRelease));
    SubscribeToEvent(buttonExit, E_RELEASED, URHO3D_HANDLER(MenuMain, HandleButtonRelease));
    SubscribeToEvent(buttonLanguage, E_RELEASED, URHO3D_HANDLER(MenuMain, HandleButtonRelease));

    text->SetWidth(GetWidth());

    mapButtonsActions[buttonNewGame] = MenuEvent_NewGame;
    mapButtonsActions[buttonOptions] = MenuEvent_MenuOptionsOpen;
    mapButtonsActions[buttonEditor] = MenuEvent_OpenEditor;
    mapButtonsActions[buttonExit] = MenuEvent_ExitInOS;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void MenuMain::RegisterObject(Context* context)
{
    context->RegisterFactory<MenuMain>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(WindowRTS);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void MenuMain::HandleButtonRelease(StringHash, VariantMap& eventData)
{
    Button *button = (Button*)eventData[Released::P_ELEMENT].GetPtr();

    if (button == buttonExit)
    {
        gEngine->Exit();

        gMenuMain->SetDisabled();
        gGUI->SetVisibleMenu(gWindowConfirmExit, true);
    
    }
    else if (button == buttonLanguage)
    {
        gLocalization->SetLanguage(buttonLanguage->GetState() == 0 ? "en" : "ru");
        gSet->SetInt(TV_LANGUAGE, (int)buttonLanguage->GetState());
    }
    else
    {
        eventData = GetEventDataMap();
        eventData[MenuEvent::P_TYPE] = mapButtonsActions[button];
        SendEvent(E_MENU, eventData);

        if (button == buttonNewGame)
        {
            buttonExit->SetText("Exit from game");
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void MenuMain::HandleKeyDown(StringHash, VariantMap& eventData)
{
    using namespace KeyDown;

    int key = eventData[P_KEY].GetInt();

    if (key == KEY_UP)
    {
        SetFocusedPrev();
    }
    else if (key == KEY_DOWN)
    {
        SetFocusedNext();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void MenuMain::SetEnabled()
{
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(MenuMain, HandleKeyDown));
    SetVisible(true);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void MenuMain::SetDisabled()
{
    UnsubscribeFromEvent(E_KEYDOWN);
    SetVisible(false);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void MenuMain::SetFocusedNext()
{
    int numButton = (NumFocusedButton() + 1) % buttons.Size();
    buttons[numButton]->SetFocus(true);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void MenuMain::SetFocusedPrev()
{
    int numButton = NumFocusedButton() - 1;
    if (numButton < 0)
    {
        numButton = buttons.Size() - 1;
    }
    buttons[numButton]->SetFocus(true);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int MenuMain::NumFocusedButton()
{
    for (int i = 0; i < buttons.Size(); i++)
    {
        if(buttons[i]->HasFocus())
        {
            return i;
        }
    }
    return -1;
}
