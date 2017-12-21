#include "ChngDrawClrAction.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

ChngDrawClrAction::ChngDrawClrAction(ApplicationManager *pApp) :Action(pApp)
{}

void ChngDrawClrAction::ReadActionParameters() {
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Initialise local SelectedFigs and selectedCount 
	SelectedFigs = pManager->GetSelectedFigures();
	selectedCount = pManager->GetSelectedCount();
	
	//Prints a custom message depending on whether a figure is selected
	string message;

	if (!IsSelectedFig)
		message = "Please pick the current draw color";
	else
		message = "What draw color do you want to change the selected figure(s) to ?";

	pOut->PrintMessage(message);

	//Sets IsColor and DrawClr
	if (!pManager->GetColor(DrawClr))
		IsColor = false;
	else
		IsColor = true;

	pOut->ClearStatusBar();
}

void ChngDrawClrAction::Execute() {
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Reads the input draw color
	ReadActionParameters();

	//Executes only if a figure is selected
	if (IsColor) {
		//Changes current draw color if no figure is selected
		if (!IsSelectedFig)
			pOut->setCrntDrawColor(DrawClr);

		//Changes selected figure draw color
		else {
			for (int i = 0; i < selectedCount; i++)
				SelectedFigs[i]->ChngDrawClr(DrawClr);
		}
	}
}