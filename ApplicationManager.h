#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "Defs.h"
#include "GUI\Output.h"
#include "GUI\Input.h"
#include "Actions\Action.h"
#include "Components\Component.h"

//Main class that manages everything in the application.
class ApplicationManager
{

	enum { MaxCompCount = 200 };	//Max no of Components	

private:
	int CompCount;		//Actual number of Components
	Component* CompList[MaxCompCount];	//List of all Components (Array of pointers)

	Output* OutputInterface; //pointer to the Output Clase Interface
	Input* InputInterface; //pointer to the Input Clase Interface

	// --- NEW MEMBER: Selected Component Pointer ---
	Component* m_SelectedComponent;


public:
	ApplicationManager(); //constructor

	//Reads the required action from the user and returns the corresponding action type
	ActionType GetUserAction();

	//Creates an action and executes it
	void ExecuteAction(ActionType);

	void UpdateInterface();	//Redraws all the drawing window

	//Gets a pointer to Input / Output Object
	Output* GetOutput();
	Input* GetInput();

	//Adds a new component to the list of components
	void AddComponent(Component* pComp);

	//Finds the component at the specified coordinates (x, y)
	Component* GetComponentAt(int x, int y);

	//Deletes a specific component from the list
	void DeleteComponent(Component* pComp);
	Component* GetComponentAt(int x, int y) const;

	// --- NEW FUNCTIONS: Selected Component Accessors ---
	Component* GetSelectedComponent() const { return m_SelectedComponent; }
	void SetSelectedComponent(Component* pComp) { m_SelectedComponent = pComp; }

	//destructor
	~ApplicationManager();
};

#endif