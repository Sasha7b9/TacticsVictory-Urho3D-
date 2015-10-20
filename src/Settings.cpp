#include <stdafx.h>

bool operator==(const lSettings::IntKey & keyleft, const lSettings::IntKey& keyright)
{
    return keyleft.str == keyright.str;
}

bool operator==(const lSettings::FloatKey & keyLeft, const lSettings::FloatKey& keyRight)
{
    return keyLeft.str == keyRight.str;
}

bool lSettings::Load()
{
    nameFile = String("settings.xml");

    mapIntChild[IntKey(TV_SCREEN_WIDTH)] = SET::WINDOW::WIDTH;
    mapIntChild[IntKey(TV_SCREEN_HEIGHT)] = SET::WINDOW::HEIGHT;
    mapIntChild[IntKey(TV_LANGUAGE)] = 1;
    mapIntChild[IntKey(TV_TEXTURE_QUALITY)] = 2;
    mapIntChild[IntKey(TV_BRIGHTNESS)] = 50;
    mapIntChild[IntKey(TV_VOLUME)] = 50;
    mapIntChild[IntKey(TV_MAX_OCCLUDER_TRIANGLES)] = 5000;
    mapIntChild[IntKey(TV_TEXTURE_ANISOTROPY)] = 3;
    mapIntChild[IntKey(TV_MATERIAL_QUALITY)] = 3;
    mapIntChild[IntKey(TV_SHADOW_DRAW)] = 1;
    mapIntChild[IntKey(TV_SPECULAR_LIGHTING)] = 1;
    mapIntChild[IntKey(TV_SHADOW_MAP_SIZE)] = 4;
    mapIntChild[IntKey(TV_PANEL_BOTTOM_BUTTON_WIDTH)] = SET::PANEL::BOTTOM::BUTTON::WIDTH;
    mapIntChild[IntKey(TV_PANEL_BOTTOM_BUTTON_HEIGHT)] = SET::PANEL::BOTTOM::BUTTON::HEIGHT;
    mapIntChild[IntKey(TV_PANEL_BOTTOM_HEIGHT)] = SET::PANEL::BOTTOM::HEIGHT;
    mapIntChild[IntKey(TV_PANEL_MAP_WIDTH)] = SET::PANEL::MAP::WIDTH;
    mapIntChild[IntKey(TV_PANEL_BOTTOM_BUTTON_Y)] = 3;

    mapFloatChild[FloatKey(TV_PANEL_SPEED)] = SET::PANEL::SPEED;

    File inFile(gContext);
    if(inFile.Open(nameFile, Urho3D::FILE_READ))
    {
        file = new XMLFile(gContext);
        bool begined = file->BeginLoad(inFile);
        if(begined)
        {
            root = file->GetRoot();
            if(root != XMLElement::EMPTY)
            {
                return true;
            }
        }
    }
    if (file == nullptr)
    {
        file = new XMLFile(gContext);
    }
    root = file->CreateRoot("settings");
    return false;
}

int lSettings::GetInt(char *elem, char *name)
{
    int retValue = mapIntChild[IntKey(elem, name)];
    if(!GetIntFromChild(elem, name, &retValue))
    {
        SetInt(elem, name, retValue);
    }
    return retValue;
}

int lSettings::GetInt(char *name)
{
    int retValue = mapIntChild[IntKey(name)];
    if(!GetIntFromChild(name, &retValue))
    {
        SetInt(name, retValue);
    }
    return retValue;
}

float lSettings::GetFloat(char *elem, char *name)
{
    float retValue = mapFloatChild[FloatKey(elem, name)];
    if (!GetFloatFromChild(elem, name, &retValue))
    {
        SetFloat(elem, name, retValue);
    }
    return retValue;
}

#define COMMON_BLOCK                                    \
    XMLElement child = root.GetChild(category);         \
    if (child == 0)                                     \
    {                                                   \
        child = root.CreateChild(category);             \
    }                                                   \
    XMLElement childName = child.GetChild(name);        \
    if (childName == 0)                                 \
    {                                                   \
        childName = child.CreateChild(name);            \
    }                                                   \
    childName.SetValue(String(value));

void lSettings::SetInt(char *category, char *name, int value)
{
    COMMON_BLOCK;
}

void lSettings::SetFloat(char *category, char *name, float value)
{
    COMMON_BLOCK;
}

void lSettings::SetInt(char *name, int value)
{
    XMLElement child = root.GetChild(name);
    if (child == 0)
    {
        child = root.CreateChild(name);
    }
    
    child.SetValue(String(value));
}

void lSettings::Save()
{
    File outFile(gContext);
    outFile.Open(nameFile, Urho3D::FILE_WRITE);
    file->Save(outFile);
}

bool lSettings::GetIntFromChild(char *category, char *name, int *value)
{
    if (!root.HasChild(category))
    {
        return false;
    }

    XMLElement child = root.GetChild(category);
    if (!child.HasChild(name))
    {
        return false;
    }

    *value = Urho3D::ToInt(child.GetChild(name).GetValue());
    return true;
}

bool lSettings::GetFloatFromChild(char *category, char *name, float *value)
{
    if (!root.HasChild(category))
    {
        return false;
    }
    XMLElement child = root.GetChild(category);
    if (!child.HasChild(name))
    {
        return false;
    }
    *value = Urho3D::ToFloat(child.GetChild(name).GetValue());
    return true;
}

bool lSettings::GetIntFromChild(char *name, int *value)
{
    if (!root.HasChild(name))
    {
        return false;
    }
    *value = Urho3D::ToInt(root.GetChild(name).GetValue());
    return true;
}


const float SET::PANEL::SPEED = 1000.0f;
const IntVector2 SET::WINDOW::SIZE = {SET::WINDOW::WIDTH, SET::WINDOW::HEIGHT};
const IntVector2 SET::PANEL::BOTTOM::SIZE = {SET::PANEL::BOTTOM::WIDTH, SET::PANEL::BOTTOM::HEIGHT};
const IntVector2 SET::PANEL::MAP::SIZE = {SET::PANEL::MAP::WIDTH, SET::PANEL::MAP::HEIGHT};
const IntVector2 SET::PANEL::MAIN::SIZE = {SET::PANEL::MAIN::WIDTH, SET::PANEL::MAIN::HEIGHT};
const IntVector2 SET::MENU::SLIDER::SIZE = {SET::MENU::SLIDER::WIDTH, SET::MENU::SLIDER::HEIGHT};
const IntVector2 SET::MENU::DDLIST::SIZE = {SET::MENU::DDLIST::WIDTH, SET::MENU::DDLIST::HEIGHT};
const IntVector2 SET::MENU::TEXT::SIZE = {SET::MENU::TEXT::WIDTH, SET::MENU::TEXT::HEIGHT};
const IntVector2 SET::MENU::GOVERNOR::CELL::SIZE = {SET::MENU::GOVERNOR::CELL::WIDTH, SET::MENU::GOVERNOR::CELL::HEIGHT};
const char* SET::MENU::FONT::NAME = "Fonts/tech.fnt";
const char* SET::MENU::ELEM::WINDOW::STYLE = "WindowNoBorder";