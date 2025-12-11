#include "Delete.h"
#include "ApplicationManager.h"
#include "Components\Connection.h"
#include "GUI/Input.h"
#include "GUI/Output.h"

Delete::Delete(ApplicationManager* pApp) : Action(pApp)
{
}

Delete::~Delete(void)
{
}

void Delete::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("Click on the component or connection you want to delete");
    pIn->GetPointClicked(Cx, Cy);
    pOut->ClearStatusBar();
}

void Delete::Execute()
{
    ReadActionParameters();

    Component* pComp = pManager->GetComponentAt(Cx, Cy);
    Output* pOut = pManager->GetOutput();

    if (pComp != NULL)
    {
        // Check if it's a connection
        Connection* conn = dynamic_cast<Connection*>(pComp);

        if (conn)
        {
            // It's a connection - delete just the connection
            pManager->DeleteComponent(conn);
            pOut->PrintMsg("Connection deleted successfully");
        }
        else
        {
            // It's a gate/LED/switch - delete it and all its connections
            pManager->DeleteComponent(pComp);
            pOut->PrintMsg("Component deleted successfully");
        }

        pManager->UpdateInterface();
    }
    else
    {
        pOut->PrintMsg("No component found at this position");
    }
}

void Delete::Undo()
{
}

void Delete::Redo()
{
}