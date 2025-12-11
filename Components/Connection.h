#ifndef _CONNECTION_H
#define _CONNECTION_H
#include "Component.h"

class OutputPin;
class InputPin;

class Connection : public Component
{
private:
    OutputPin* SrcPin;
    InputPin* DstPin;
public:
    Connection(const GraphicsInfo& r_GfxInfo, OutputPin* pSrcPin, InputPin* pDstPin);
    void setSourcePin(OutputPin* pSrcPin);
    OutputPin* getSourcePin();
    void setDestPin(InputPin* pDstPin);
    InputPin* getDestPin();

    // Override IsInside to make connections clickable
    virtual bool IsInside(int x, int y) const;

    virtual void Operate();
    virtual void Draw(Output* pOut);
    virtual int GetOutPinStatus();
    virtual int GetInputPinStatus(int n);
    virtual void setInputPinStatus(int n, STATUS s);
};
#endif