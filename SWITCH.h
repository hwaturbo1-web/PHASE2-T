#ifndef _SWITCH_H
#define _SWITCH_H

#include "Components/Component.h"
#include "Components/OutputPin.h"

class SWITCH : public Component
{
private:
	OutputPin m_OutputPin;  // Switch has only one output pin

public:
	SWITCH(const GraphicsInfo& r_GfxInfo);

	virtual void Operate();	// Switch toggles its output status
	virtual void Draw(Output* pOut);	// Draws the Switch

	virtual int GetOutPinStatus();	// Returns status of the output pin
	virtual int GetInputPinStatus(int n);  // Returns -1 (no inputs)
	virtual void setInputPinStatus(int n, STATUS s);  // Does nothing (no inputs)

	// NEW: Return pointer to output pin for connections
	virtual OutputPin* GetOutputPin();

	// Toggle the switch state (call this when user clicks the switch in simulation)
	void Toggle();
};

#endif