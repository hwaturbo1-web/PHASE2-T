#include "Component.h"
Component::Component(const GraphicsInfo& r_GfxInfo)
{
    m_GfxInfo.x1 = r_GfxInfo.x1;
    m_GfxInfo.y1 = r_GfxInfo.y1;
    m_GfxInfo.x2 = r_GfxInfo.x2;
    m_GfxInfo.y2 = r_GfxInfo.y2;
    m_Label = "";
    // --- NEW INITIALIZATION ---
    m_Selected = false;
}
Component::Component()
{
    m_Label = "";
    // --- NEW INITIALIZATION ---
    m_Selected = false;
}
void Component::SetLabel(string label)
{
    m_Label = label;
}
string Component::GetLabel() const
{
    return m_Label;
}
GraphicsInfo Component::GetGraphicsInfo() const
{
    return m_GfxInfo;
}
OutputPin* Component::GetOutputPin()
{
    return nullptr;
}
InputPin* Component::GetInputPin(int index)
{
    return nullptr;
}
Component::~Component()
{
}