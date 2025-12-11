#include "AddINVgate1.h"
#include "ApplicationManager.h"
#include "Actions/Action.h"

AddINVgate1::AddINVgate1(ApplicationManager* pApp) :Action(pApp)
{
}

AddINVgate1::~AddINVgate1(void)
{
}

void AddINVgate1::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("1-Input INVERTER Gate: Click to add the gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddINVgate1::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();

	//Calculate the rectangle Corners
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the INV1 gate

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	INV1* pA = new INV1(GInfo, AND2_FANOUT);
	// ADDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMsg("Enter AND2 label (or press ESC to skip):");
	string label = pIn->GetSrting(pOut);

	if (label != "")  // If user didn't press ESC
	{
		pA->SetLabel(label);
	}
	//ADDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
	pManager->AddComponent(pA);
}

void AddINVgate1::Undo()
{
}

void AddINVgate1::Redo()
{
}

