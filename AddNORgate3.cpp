#include "AddNORgate3.h"
#include "ApplicationManager.h"
#include "Actions/Action.h"

AddNORgate3::AddNORgate3(ApplicationManager* pApp) :Action(pApp)
{
}

AddNORgate3::~AddNORgate3(void)
{
}

void AddNORgate3::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("3-Input NOR Gate: Click to add the gate");

	//Wait fNOR User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddNORgate3::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();

	//Calculate the rectangle CNORners
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the NOR3 gate

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	NOR3* pA = new NOR3(GInfo, AND2_FANOUT);
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

void AddNORgate3::Undo()
{
}

void AddNORgate3::Redo()
{
}