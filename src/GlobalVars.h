#pragma once


class lCamera;
class lConsole;
class lCursor;
class Editor;
class GUI;
class GuiEditor;
class GuiGame;
class Hint;
class Level;
class MenuMain;
class MenuOptions;
class SegmentLandscape;
class Settings;
class Tank;
class lTerrain;
class lWindow;
class WindowConfirmExit;
class WindowTarget;
class WindowVariables;



extern Audio            *gAudio;
extern Localization     *gLocalization;
extern UI               *gUI;
extern UIElement        *gUIRoot;
extern ResourceCache    *gCache;
extern Engine           *gEngine;
extern Input            *gInput;
extern Renderer         *gRenderer;
extern DebugRenderer    *gDebugRenderer;
extern Context          *gContext;
extern Urho3D::Scene    *gScene;
extern Urho3D::Console  *gEngineConsole;
extern DebugHud         *gDebugHud;
extern Graphics         *gGraphics;
extern FileSystem       *gFileSystem;
extern PhysicsWorld     *gPhysicsWorld;
extern Font             *gFont;
extern Time             *gTime;
extern FileSelector     *gFileSelector;
extern Urho3D::Log      *gLog;
extern Profiler         *gProfiler;

extern lCamera          *gCamera;
extern lCursor          *gCursor;
extern Editor           *gEditor;
extern Settings         *gSet;
extern Level            *gLevel;
extern lTerrain         *gTerrain;
extern SegmentLandscape *gLandscape;

extern GUI                  *gGUI;
extern lConsole             *gConsole;
extern WindowVariables      *gWindowVars;
extern MenuMain             *gMenuMain;
extern GuiGame              *gGuiGame;
extern GuiEditor            *gGuiEditor;
extern MenuOptions          *gMenuOptions;
extern WindowConfirmExit    *gWindowConfirmExit;
extern Hint                 *gHint;
extern int                  *gCounterHint;
extern Vector<lWindow*>     gOpenedWindow;
extern PODVector<Tank*>     gTanks;
extern WindowTarget         *gWindowTarget;
