#pragma once


#include "GUI/Elements/Window.h"


class lImage;


class PanelMap : public lWindow
{
    URHO3D_OBJECT(PanelMap, lWindow);

public:
    PanelMap(Context *context = gContext);

    static void RegisterObject(Context *context = gContext);

    virtual void Update(float timeStep);

private:
    PanelMap& operator=(const PanelMap&)
    {};

    Vector<Vector<float> > map;
    SharedPtr<lImage> imageMap;
    int x0 = 0;
    int y0 = 0;
    float scale = 0.0f;
    bool redrawMap = true;

    void HandleMouseDown(StringHash eventType, VariantMap &eventData);
    void HandleMouseMove(StringHash eventType, VariantMap &eventData);
    void HandleMapChanged(StringHash, VariantMap&);

    float GetMapHeight(uint x, uint y);
    float GetMaxHeight();
    uint SizeXMap();
    uint SizeYMap();
    bool FindIntersectionX0Z(const Vector2 &screenPoint, Vector2 &hitPoint);
};