#include"SaveAction.h"
#include "../paintforkids/ApplicationManager.h"

#include "../paintforkids/GUI/Input.h"
#include "../paintforkids/GUI/output.h"

SaveAction::SaveAction(ApplicationManager *pApp) :Action(pApp)
{
}
void SaveAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Enter the name of the file without spaces ");


	fileName = pIn->GetSrting(pOut) + ".txt";
	//Clear the status bar
	OutFile.open(fileName);
	//to check if the file is opened
	if (OutFile.is_open())
	{
		pOut->PrintMessage("Your file has been successfully saved");
	}
	else {
		pOut->PrintMessage("Save failed");
	}
}

void SaveAction::Execute()
{
	ReadActionParameters();
	//to check if the file is opened
	if (OutFile.is_open())
	{
		//it take the current draw and fill color then the number of the figures
		int numberOfFiguers = pManager->getFigCount();
		string DrawClr = getColorName(UI.DrawColor);
		string FillClr = getColorName(UI.FillColor);
		OutFile << DrawClr;
		OutFile << '\t' << FillClr << endl;
		OutFile << numberOfFiguers << endl;
		pManager->SaveAll(OutFile);
		OutFile.close();
	}
}
//utility fn to return a string of the color 
string SaveAction::getColorName(color a)const
{

	if (a == RED)
	{
		return "RED";
	}

	if (a == BLACK)
	{
		return "BLACK";
	}

	if (a == BLUE)
	{
		return "BLUE";
	}

	if (a == GREEN)
	{
		return "GREEN";
	}

	if (a == WHITE)
	{
		return "WHITE";
	}
	return "NO";
}