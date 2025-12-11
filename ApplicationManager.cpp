#include "ApplicationManager.h"
#include "Actions\AddANDgate2.h"
#include "Actions\AddORgate2.h"
#include "AddNANDgate2.h"
#include "AddNORgate2.h"
#include "AddXORgate2.h"
#include "AddXNORgate2.h"
#include "AddINVgate1.h"
#include "AddBUFFgate1.h"
#include "AddANDgate3.h"
#include "AddXORgate3.h"
#include "AddNORgate3.h"
#include "AddLED.h"
#include "AddSWITCH.h"
#include "Delete.h"
#include "AddConnection.h"
#include "EditLabel.h"

#include "C:\Users\abdal\AppData\Local\Temp\01ec32f5-93b0-4333-873a-0ad0a0267204_PHASE-2-saved.zip.PHASE-2-saved.zip\PHASE-2-saved\Components\Connection.h"   

ApplicationManager::ApplicationManager()
{
	CompCount = 0;

	for (int i = 0; i < MaxCompCount; i++)
		CompList[i] = NULL;

	// --- NEW INITIALIZATION ---
	m_SelectedComponent = nullptr;

	//Creates the Input / Output Objects & Initialize the GUI
	OutputInterface = new Output();
	InputInterface = OutputInterface->CreateInput();
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	CompList[CompCount++] = pComp;
}
////////////////////////////////////////////////////////////////////

ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is reuired from the user
	return InputInterface->GetUserAction();
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;
	switch (ActType)
	{
	case ADD_AND_GATE_2:
		pAct = new AddANDgate2(this);
		break;
	case ADD_OR_GATE_2:
		pAct = new AddORgate2(this);
		break;
	case ADD_NAND_GATE_2:
		pAct = new AddNANDgate2(this);
		break;
	case ADD_NOR_GATE_2:
		pAct = new AddNORgate2(this);
		break;
	case ADD_XOR_GATE_2:
		pAct = new AddXORgate2(this);
		break;
	case ADD_XNOR_GATE_2:
		pAct = new AddXNORgate2(this);
		break;
	case ADD_INV:
		pAct = new AddINVgate1(this);
		break;
	case ADD_Buff:
		pAct = new AddBUFFgate1(this);
		break;
	case ADD_AND_GATE_3:
		pAct = new AddANDgate3(this);
		break;
	case ADD_XOR_GATE_3:
		pAct = new AddXORgate3(this);
		break;
	case ADD_NOR_GATE_3:
		pAct = new AddNORgate3(this);
		break;
	case ADD_LED:
		pAct = new AddLED(this);
		break;
	case ADD_Switch:
		pAct = new AddSWITCH(this);
		break;


	case DEL:
		pAct = new Delete(this);
		break;

	case ADD_CONNECTION:
		pAct = new AddConnection(this);
		break;
	case EDIT_Label:
		pAct = new EditLabel(this);
		break;



	case EXIT:
		///TODO: create ExitAction here
		break;
	}
	if (pAct)
	{
		pAct->Execute();
		delete pAct;
		pAct = NULL;
	}
}

void ApplicationManager::UpdateInterface()
{
	// Clear the drawing area first to remove old labels
	OutputInterface->ClearDrawingArea();

	// Redraw all components with updated labels
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] != NULL)
			CompList[i]->Draw(OutputInterface);
	}
}
////////////////////////////////////////////////////////////////////
Input* ApplicationManager::GetInput()
{
	return InputInterface;
}

////////////////////////////////////////////////////////////////////
Output* ApplicationManager::GetOutput()
{
	return OutputInterface;
}

////////////////////////////////////////////////////////////////////
Component* ApplicationManager::GetComponentAt(int x, int y)
{
	// Loop through all components from top to bottom (reverse order)
	// This ensures we get the component drawn on top if overlapping
	for (int i = CompCount - 1; i >= 0; i--)
	{
		if (CompList[i] != NULL)
		{
			// Check if the click is inside this component's boundaries
			if (CompList[i]->IsInside(x, y))
			{
				return CompList[i];
			}
		}
	}
	return NULL;
}

////////////////////////////////////////////////////////////////////
void ApplicationManager::DeleteComponent(Component* pComp)
{
	if (pComp == NULL) return;

	// Check if the component to delete is itself a Connection
	Connection* targetConn = dynamic_cast<Connection*>(pComp);

	if (targetConn)
	{
		// It's a connection - just delete it and clean up pins
		OutputPin* sPin = targetConn->getSourcePin();
		InputPin* dPin = targetConn->getDestPin();

		// Deregister from source output pin
		if (sPin)
		{
			sPin->RemoveConnection(targetConn);
		}

		// Deregister from destination input pin
		if (dPin)
		{
			dPin->setConnection(nullptr);
		}

		// Remove from list
		for (int i = 0; i < CompCount; i++)
		{
			if (CompList[i] == targetConn)
			{
				delete CompList[i];

				// Shift remaining components
				for (int j = i; j < CompCount - 1; j++)
					CompList[j] = CompList[j + 1];

				CompList[CompCount - 1] = NULL;
				CompCount--;
				return; // Done!
			}
		}
	}
	else
	{
		// It's a gate/LED/switch - delete all connections referencing it first
		for (int i = 0; i < CompCount; /*increment inside*/)
		{
			Connection* conn = dynamic_cast<Connection*>(CompList[i]);
			if (conn)
			{
				OutputPin* sPin = conn->getSourcePin();
				InputPin* dPin = conn->getDestPin();

				bool refersToTarget = false;
				if (sPin && sPin->getComponent() == pComp) refersToTarget = true;
				if (dPin && dPin->getComponent() == pComp) refersToTarget = true;

				if (refersToTarget)
				{
					// Deregister connection from source output pin (if any)
					if (sPin)
					{
						sPin->RemoveConnection(conn);
					}

					// Deregister connection from destination input pin (if any)
					if (dPin)
					{
						dPin->setConnection(nullptr);
					}

					// Delete connection component and compact list
					delete CompList[i];
					for (int j = i; j < CompCount - 1; j++)
						CompList[j] = CompList[j + 1];
					CompList[CompCount - 1] = NULL;
					CompCount--;
					continue; // stay on same index because list shifted
				}
			}
			i++;
		}

		// Now delete the gate/LED/switch itself
		for (int i = 0; i < CompCount; i++)
		{
			if (CompList[i] == pComp)
			{
				delete CompList[i];

				// Shift remaining
				for (int j = i; j < CompCount - 1; j++)
					CompList[j] = CompList[j + 1];

				CompList[CompCount - 1] = NULL;
				CompCount--;
				break;
			}
		}
	}
}


////////////////////////////////////////////////////////////////////
ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < CompCount; i++)
		delete CompList[i];
	delete OutputInterface;
	delete InputInterface;
}

////////////////////////////////////////////////////////////////////
Component* ApplicationManager::GetComponentAt(int x, int y) const
{
	// Loop through all components from top to bottom (reverse order)
	for (int i = CompCount - 1; i >= 0; i--)
	{
		if (CompList[i] != NULL && CompList[i]->IsInside(x, y))
			return CompList[i];
	}
	return nullptr;
}