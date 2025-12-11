#include "SWITCH.h"
#include "GUI/Output.h"

SWITCH::SWITCH(const GraphicsInfo& r_GfxInfo) : Component(r_GfxInfo), m_OutputPin(5)
{
	// Initialize switch to OFF (LOW)
	m_OutputPin.setStatus(LOW);

	// IMPORTANT: Associate the output pin with this component
	m_OutputPin.setComponent(this);
}

void SWITCH::Operate()
{
	// Switch doesn't perform operations
	// Its output status is controlled by Toggle() method
}

void SWITCH::Draw(Output* pOut)
{
	// Draw the switch - highlighted if ON (HIGH)
	bool isOn = (m_OutputPin.getStatus() == HIGH);
	pOut->DRAWSWITCH(m_GfxInfo, isOn);
}

int SWITCH::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}

int SWITCH::GetInputPinStatus(int n)
{
	// Switch has no input pins
	return -1;
}

void SWITCH::setInputPinStatus(int n, STATUS s)
{
	// Switch has no input pins - do nothing
}

// NEW METHOD: Return pointer to output pin
OutputPin* SWITCH::GetOutputPin()
{
	return &m_OutputPin;
}

void SWITCH::Toggle()
{
	if (m_OutputPin.getStatus() == LOW)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}