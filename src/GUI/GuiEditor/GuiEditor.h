#pragma once


class lWindow;

class GuiEditor : public UIElement
{
    URHO3D_OBJECT(GuiEditor, UIElement);

public:
    GuiEditor(Context* context = gContext);

    static void RegisterObject(Context *context = gContext);

    bool CheckOnDeadZoneForCursorBottomScreen(int x);
    bool IsInside(IntVector2 &position);

    enum ModeSelect
    {
        ModeSelect_Plane,
        ModeSelect_Edge
    } modeSelect = ModeSelect_Plane;

private:
    GuiEditor& operator=(const GuiEditor&) {};

    SharedPtr<ButtonMain> buttonInterface;
    SharedPtr<ButtonMain> buttonMenu;

    SharedPtr<ButtonMain> btnNewMap;

    SharedPtr<PanelBottom> panelBottom;
    SharedPtr<PanelMap>    panelMap;
    SharedPtr<PanelMain>   panelMain;

    SharedPtr<lWindow>      windowNewMap;
    SharedPtr<lWindow>      windowMenu;
    SharedPtr<lWindow>      windowConfirmExit;
    SharedPtr<SliderWithTextAndButtons> sliderSizeNewMapX;
    SharedPtr<SliderWithTextAndButtons> sliderSizeNewMapY;

    int width = 100;
    int height = 19;
    int dY = 27;
    int y = 10;
    int x = 10;

    bool IntersectionX(ButtonMain *button, int x);
    void CreateWindows();
    void ToggleInterfacePanels();

    void CreatePanels();
    void CreateTabs();
    void CreateTabFile();
    void CreateTabEdit();
    void CreateTabLandscape();
    void CreateTabObjects();

    // Tab "File"
    void HandleFileLoad(StringHash, VariantMap&);
    void HandleFileSave(StringHash, VariantMap&);
    void HandleFileSelectorLoadLandscape(StringHash, VariantMap&);
    void HandleFileSelectorSaveLandscape(StringHash, VariantMap&);

    // Tab "Edit"
    void HandleEditUndo(StringHash, VariantMap&);
    void HandleEditRedo(StringHash, VariantMap&);

    // Tab "Landscape"
    void HandleLandscapeCreateNewMap(StringHash, VariantMap&);
    void HandleLandscapeClearTerrain(StringHash, VariantMap&);
    void HandleLandscapeModeSelectChanged(StringHash, VariantMap&);

    // Tab "Objects"
    void HandleObjectsAdd(StringHash, VariantMap&);

    void HandleMouseDown(StringHash, VariantMap&);
    void HandleButtonRelease(StringHash, VariantMap&);
    void HandleExit(StringHash, VariantMap&);
    void HandleOptions(StringHash, VariantMap&);
    void HandleExitOk(StringHash, VariantMap&);
    void HandleExitCancel(StringHash, VariantMap&);
    void HandleKeyDown(StringHash, VariantMap&);
};