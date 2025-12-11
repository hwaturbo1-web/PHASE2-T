#include "EditLabel.h"
#include "ApplicationManager.h"

EditLabel::EditLabel(ApplicationManager* pApp) : Action(pApp)
{
}

EditLabel::~EditLabel(void)
{
}

void EditLabel::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("Click on the component you want to edit its label");
    pIn->GetPointClicked(Cx, Cy);
    pOut->ClearStatusBar();
}

void EditLabel::Execute()
{
    ReadActionParameters();

    // Find the component at the clicked position
    Component* pComp = pManager->GetComponentAt(Cx, Cy);

    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    if (pComp != NULL)
    {
        // Ask for new label
        pOut->PrintMsg("Enter new label (or press ESC to cancel):");
        newLabel = pIn->GetSrting(pOut);

        if (newLabel != "")  // If user didn't press ESC
        {
            pComp->SetLabel(newLabel);
            pOut->PrintMsg("Label updated successfully");

            // ADD THIS LINE - Force redraw to clear old label
            pManager->UpdateInterface();
        }
        else
        {
            pOut->PrintMsg("Edit cancelled");
        }
    }
    else
    {
        pOut->PrintMsg("No component found at this position");
    }
}

void EditLabel::Undo()
{
}

void EditLabel::Redo()
{
}