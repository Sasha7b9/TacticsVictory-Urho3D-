#pragma once


#pragma warning(push)

#pragma warning(disable:4365)
#pragma warning(disable:4820)
#pragma warning(disable:4625)
#pragma warning(disable:4626)
#pragma warning(disable:4640)
#pragma warning(disable:4668)
#pragma warning(disable:4100)
#pragma warning(disable:4266)


typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;


#include <Urho3D/Engine/Application.h>
#include <Urho3D/Engine/DebugHud.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Engine/Console.h>

#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Graphics/Geometry.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/IndexBuffer.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/Graphics/Texture.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/VertexBuffer.h>
#include <Urho3D/Graphics/Zone.h>

#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>

#include <Urho3D/Math/MathDefs.h>

#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/Cursor.h>
#include <Urho3D/UI/DropDownList.h>
#include <Urho3D/UI/LineEdit.h>
#include <Urho3D/UI/ScrollBar.h>
#include <Urho3D/UI/Sprite.h>
#include <Urho3D/UI/Slider.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/Window.h>
#include <Urho3D/UI/CheckBox.h>
#include <Urho3D/UI/UIEvents.h>

#include <Urho3D/IO/File.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/IO/Log.h>

#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Physics/RigidBody.h>

#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Resource/XMLFile.h>
#include <Urho3D/Resource/Localization.h>

#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>

#include <Urho3D/Core/Timer.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Core/ProcessUtils.h>

#include <Urho3D/DebugNew.h>

#include <cfloat>

using Urho3D::BiasParameters;
using Urho3D::BoundingBox;
using Urho3D::Button;

using Urho3D::Camera;
using Urho3D::CascadeParameters;
using Urho3D::CheckBox;
using Urho3D::CollisionShape;
using Urho3D::Color;
using Urho3D::Console;
using Urho3D::Context;
using Urho3D::Cos;
using Urho3D::Cursor;

using Urho3D::DebugHud;
using Urho3D::DebugRenderer;
using Urho3D::DropDownList;

using Urho3D::Engine;

using Urho3D::File;
using Urho3D::FileSystem;
using Urho3D::Font;

using Urho3D::Geometry;
using Urho3D::Graphics;

using Urho3D::HashMap;

using Urho3D::Image;
using Urho3D::IndexBuffer;
using Urho3D::Input;
using Urho3D::IntRect;
using Urho3D::IntVector2;

using Urho3D::Light;
using Urho3D::LineEdit;
using Urho3D::Localization;
using Urho3D::LogicComponent;

using Urho3D::Material;
using Urho3D::Model;

using Urho3D::Node;

using Urho3D::Object;
using Urho3D::Octree;

using Urho3D::PhysicsWorld;
using Urho3D::Plane;
using Urho3D::PODVector;

using Urho3D::Quaternion;

using Urho3D::Random;
using Urho3D::Ray;
using Urho3D::Renderer;
using Urho3D::Resource;
using Urho3D::ResourceCache;
using Urho3D::RigidBody;

using Urho3D::Scene;
using Urho3D::ScrollBar;
using Urho3D::SharedPtr;
using Urho3D::Slider;
using Urho3D::Sin;
using Urho3D::StaticModel;
using Urho3D::String;
using Urho3D::StringHash;

using Urho3D::Technique;
using Urho3D::Texture;
using Urho3D::Texture2D;
using Urho3D::Time;
using Urho3D::Text;

using Urho3D::VariantMap;
using Urho3D::Vector;
using Urho3D::Vector2;
using Urho3D::Vector3;
using Urho3D::VertexBuffer;
using Urho3D::Viewport;

using Urho3D::Window;

using Urho3D::UI;
using Urho3D::UIElement;

using Urho3D::XMLElement;
using Urho3D::XMLFile;

using Urho3D::Zone;

using Urho3D::E_SLIDERCHANGED;
using Urho3D::E_PRESSED;
using Urho3D::E_RELEASED;
using Urho3D::E_UPDATE;
using Urho3D::E_POSTRENDERUPDATE;
using Urho3D::E_KEYDOWN;
using Urho3D::E_UIMOUSECLICK;
using Urho3D::E_UIMOUSECLICKEND;
using Urho3D::E_MOUSEMOVE;
using Urho3D::E_MOUSEBUTTONDOWN;
using Urho3D::E_MOUSEBUTTONUP;
using Urho3D::E_DRAGBEGIN;
using Urho3D::E_DRAGMOVE;
using Urho3D::E_DRAGEND;
using Urho3D::E_ITEMSELECTED;
using Urho3D::E_TEXTFINISHED;
using Urho3D::E_HOVERBEGIN;
using Urho3D::E_HOVEREND;

using Urho3D::Corner;

#include <d3d9types.h>

#pragma warning(pop)

#include "defines.h"

class vButton;
class vButtonToggled;

class vCamera;
class vConsole;
class vCursor;
class vCursorShapes;

class vDropDownListWithTextAndButton;

class vEditor;

class vGovernorFloat;
class vGUI;

class vImage;

class vLabel;
class vLineTranslator1D;
class vLineTranslator2D;

class vMenu;
class vMenuGame;
class vMenuEditor;
class vMenuMain;
class vMenuOptions;

class vPanelBottom;
class vPanelMain;
class vPanelMap;
class vPlane;

class vSettings;
class vSliderWithTextAndButtons;

class vTab;
class vTerrain;
class vTerrainBlock;
class vTriangle;

class vWindowVariables;

#include "SettingsTypes.h"
#include "GlobalVars.h"
#include "Settings.h"
