#include "AddSWITCH.h"
#include "ApplicationManager.h"
#include "Actions/Action.h"
#include "GUI/Input.h"
#include "GUI/Output.h"


AddSWITCH::AddSWITCH(ApplicationManager* pApp) : Action(pApp)
{
}

AddSWITCH::~AddSWITCH()
{
}

void AddSWITCH::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	pOut->PrintMsg("Click to place the switch");
	pIn->GetPointClicked(Cx, Cy);      // store position
	pOut->ClearStatusBar();
}

void AddSWITCH::Execute()
{
	ReadActionParameters();

	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	GraphicsInfo GInfo;
	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;

	SWITCH* pS = new SWITCH(GInfo);
	// ADDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMsg("Enter AND2 label (or press ESC to skip):");
	string label = pIn->GetSrting(pOut);

	if (label != "")  // If user didn't press ESC
	{
		pS->SetLabel(label);
	}
	//ADDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
	pManager->AddComponent(pS);
}

void AddSWITCH::Undo()
{
}

void AddSWITCH::Redo()
{
}