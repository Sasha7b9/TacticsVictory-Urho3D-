#pragma once


class vImage : public Resource
{
    OBJECT(vImage);
public:
    vImage(int width, int height);

    SharedPtr<Image> GetImage();

    void Clear(const Color &color);
    void SetPoint(uint x, uint y, const Color& color);
    void DrawLine(int x0, int y0, int x1, int y1, const Color &color);
    void DrawRectangle(int x, int y, int width, int height, const Color &color);
    void FillRectangle(int x, int y, int width, int height, const Color &color);
    void FillRegion(int x, int y, const Color &color);
    void FillRegion(int x, int y, const Color &color, const Color &colorBound);
    int GetWidth();
    int GetHeight();
    void DrawPolyline(const Color &color, int numPoints, int *xy);
    void DrawCircle(float x, float y, float radius, const Color &color, float step = 1.0f);
    IntVector2 GetHotSpot();
    void SetHotSpot(int x, int y);

private:
    vImage& operator=(const vImage&)
    {};
    SharedPtr<Image> image;

    void Replace4Points(int x, int y, const Color &color);
    void Replace4PointsBound(int x, int y, const Color &color);
    
    Color replacedColor;
    Color boundingColor;
    IntVector2 hotSpot;
};