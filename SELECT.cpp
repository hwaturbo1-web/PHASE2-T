#include "Select.h"
#include "ApplicationManager.h"
#include "Components\Component.h"
#include "GUI\Input.h"
#include "GUI\Output.h"

Select::Select(ApplicationManager* pApp) : Action(pApp)
{
}

void Select::ReadActionParameters()
{
    // Get a Pointer to the Input Interface
    Input* pIn = pManager->GetInput();
    pIn->GetPointClicked(x, y);
}

void Select::Execute()
{
    ReadActionParameters();

    Component* clickedComp = pManager->GetComponentAt(x, y);
    Component* selectedComp = pManager->GetSelectedComponent();
    Output* pOut = pManager->GetOutput();

    // Case 1: Clicked on the currently selected component (to unselect it)
    if (clickedComp && clickedComp == selectedComp)
    {
        clickedComp->SetSelected(false);
        pManager->SetSelectedComponent(nullptr);
        pOut->PrintMsg("Component unselected.");
    }
    // Case 2: Clicked on a NEW component (to select it)
    else if (clickedComp)
    {
        // Unselect the old one first, if any
        if (selectedComp)
        {
            selectedComp->SetSelected(false);
        }
        // Select the new one
        clickedComp->SetSelected(true);
        pManager->SetSelectedComponent(clickedComp);
        pOut->PrintMsg("Component selected. Now you can use the MOVE action.");
    }
    // Case 3: Clicked on empty space (unselect existing if any)
    else if (selectedComp)
    {
        selectedComp->SetSelected(false);
        pManager->SetSelectedComponent(nullptr);
        pOut->PrintMsg("Component unselected. Click on a component to select it.");
    }
    else
    {
        pOut->PrintMsg("No component at this location.");
    }

    pManager->UpdateInterface(); // Redraw the interface to show selection status
}