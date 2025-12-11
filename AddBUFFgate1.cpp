#include "AddBUFFgate1.h"
#include "ApplicationManager.h"
#include "Actions/Action.h"

AddBUFFgate1::AddBUFFgate1(ApplicationManager* pApp) :Action(pApp)
{
}

AddBUFFgate1::~AddBUFFgate1(void)
{
}

void AddBUFFgate1::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("1-Input BUFFER Gate: Click to add the gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddBUFFgate1::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();

	//Calculate the rectangle Corners
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the BUFF1 gate

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	BUFF1* pA = new BUFF1(GInfo, AND2_FANOUT);
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

void AddBUFFgate1::Undo()
{
}

void AddBUFFgate1::Redo()
{
}

