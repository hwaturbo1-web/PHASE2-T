#ifndef _COMPONENT_H
#define _COMPONENT_H
#include "..\Defs.h"
#include "..\GUI\Output.h"
class OutputPin;
class InputPin;
class Component {
private:
    string m_Label;
    // --- NEW MEMBER: Selection State ---
    bool m_Selected;
protected:
    GraphicsInfo m_GfxInfo;
public:
    Component(const GraphicsInfo& r_GfxInfo);
    Component();
    // Label functions
    void SetLabel(string label);
    string GetLabel() const;
    // Graphics
    GraphicsInfo GetGraphicsInfo() const;
    // Boundaries
    int GetX1() const { return m_GfxInfo.x1; }
    int GetX2() const { return m_GfxInfo.x2; }
    int GetY1() const { return m_GfxInfo.y1; }
    int GetY2() const { return m_GfxInfo.y2; }

    // --- NEW FUNCTIONS: Selection/Movement ---
    void SetSelected(bool s) { m_Selected = s; }
    bool IsSelected() const { return m_Selected; }

    // Virtual function for moving the component
    // DeltaX and DeltaY are the change in position
    virtual void Move(int deltaX, int deltaY) {
        m_GfxInfo.x1 += deltaX;
        m_GfxInfo.x2 += deltaX;
        m_GfxInfo.y1 += deltaY;
        m_GfxInfo.y2 += deltaY;
    }
    // ***************************************

    // *** CRITICAL: This MUST have "virtual" keyword ***
    virtual bool IsInside(int x, int y) const
    {
        return (x >= m_GfxInfo.x1 && x <= m_GfxInfo.x2 &&
            y >= m_GfxInfo.y1 && y <= m_GfxInfo.y2);
    }
    // Virtual functions
    virtual void Operate() = 0;
    virtual void Draw(Output* pOut) = 0;
    virtual int GetOutPinStatus() = 0;
    virtual int GetInputPinStatus(int n) = 0;
    virtual void setInputPinStatus(int n, STATUS s) = 0;
    // Pin functions (implemented in .cpp)
    virtual OutputPin* GetOutputPin();
    virtual InputPin* GetInputPin(int index);
    virtual int GetInputPinCount() const { return 0; }
    virtual ~Component();
};
#endif