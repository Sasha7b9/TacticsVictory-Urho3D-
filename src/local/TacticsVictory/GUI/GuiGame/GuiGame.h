// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class PanelBottom;
class PanelMap;
class PanelMain;
class ButtonRTS;


class GuiGame : public Object
{
    URHO3D_OBJECT(GuiGame, Object);
public:
    GuiGame(Context *context = TheContext);

    bool CheckOnDeadZoneForCursorBottomScreen(int x);
    bool IsInside(const IntVector2 &position);
    bool IsVisible();
    void SetVisible(bool visible);

private:
    SharedPtr<ButtonRTS> buttonInterface;
    SharedPtr<ButtonRTS> buttonMenu;

    SharedPtr<PanelBottom> panelBottom;
    SharedPtr<PanelMap>    panelMap;
    SharedPtr<PanelMain>   panelMain;

    bool IntersectionX(const ButtonRTS *button, int x);
    void ToggleInterfacePanels();

    void CreatePanels();
    void CreateTabs();
    void CreateTabInfo();
    void CreateTabUnits();
    void CreateTabPlatoons();
    void CreateTabBuildings();
    void CreateTabDebug();

    void HandleButtonRelease(StringHash, VariantMap&);
    void HandleKeyDown(StringHash, VariantMap&);
};