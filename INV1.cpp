#include "INV1.h"

INV1::INV1(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void INV1::Operate()
{
	//caclulate the output status as the ANDing of the two input pins

	//Add you code here
}


// Function Draw
// Draws 2-input AND gate
void INV1::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawINV1(m_GfxInfo);
	string label = GetLabel();
	if (label != "")
	{
		int labelX = (m_GfxInfo.x1 + m_GfxInfo.x2) / 2 - 20;
		int labelY = m_GfxInfo.y1 - 15;
		pOut->DrawText(labelX, labelY, label);
	}
}

//returns status of outputpin
int INV1::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int INV1::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void INV1::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
