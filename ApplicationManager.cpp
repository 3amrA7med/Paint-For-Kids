#include "ApplicationManager.h"
#include "Actions\AddRectAction.h"
#include "Actions\SelectAction.h"
#include "Actions\AddLineAction.h"
#include "Actions\AddCircAction.h"
#include "Actions\AddTrigAction.h"
#include "SaveAction.h"
//#include "CMUgraphicsLib\colors.cpp"
#include "Actions\ChngDrawClrAction.h"
#include "Actions\ChngFillClrAction.h"
#include "Actions\ToPlayAction.h"
#include "PickByColor.h"
#include "PickByType.h"
#include "PickByBoth.h"
#include"LoadAction.h"
#include"ExitAction.h"

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	
	FigCount = 0;
	SelectedFig = NULL;
	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
		FigList[i] = NULL;	
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_RECT:
			pAct = new AddRectAction(this);
			break;

		case DRAW_LINE:
			pAct = new AddLineAction(this);
			break;

		case DRAW_CIRC:
			pAct = new AddCircAction(this);
			break;

		case DRAW_TRIG:
			pAct = new AddTrigAction(this);
			break;
			
		case CHNG_DRAW_CLR:
			pAct = new ChngDrawClrAction(this);
			break;

		case CHNG_FILL_CLR:
			pAct = new ChngFillClrAction(this);
			break;

		case SELECT:
			pAct = new SelectAction(this);
			break;

		case COPY:
			pAct = new PickByBoth(this);//this is a test
			break;

		case TO_PLAY:
			pAct = new ToPlayAction(this);//this is a test
			break;

		case EXIT:
			pAct = new ExitAction(this);
			break;

		case SAVE:
			pAct = new SaveAction(this);
			break;
		case LOAD:
			pAct = new LoadAction(this);
			break;

		
		case STATUS:	//a click on the status bar ==> no action
			return;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}

bool ApplicationManager::GetColor(color &inputColor) {
	
	bool isColor = true;
	//Creating the color toolbar
	pOut->CreateColorToolBar();

	//Inputting draw color action
	ActionType inputColorAction = pIn->GetUserAction();

	switch (inputColorAction) {
	case SET_BLACK:
		inputColor = BLACK;
		break;

	case SET_WHITE:
		inputColor = WHITE;
		break;

	case SET_RED:
		inputColor = RED;
		break;

	case SET_GREEN:
		inputColor = GREEN;
		break;

	case SET_BLUE:
		inputColor = BLUE;
		break;

	default:
		isColor = false;
	}

	//Restoring the draw toolbar
	pOut->CreateDrawToolBar();

	return isColor;
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Transfer figures in FigList to playmode
CFigure * ApplicationManager::DrawnFigs(int i) const
{
	return FigList[i];
}
//Transfer FigCount to playmode to avoid unnessecary loops
int ApplicationManager::getFigCount() const
{
	return FigCount;
}
////////////////////////////////////////////////////////////////////////////////////
//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if (FigCount < MaxFigCount)
	{
		FigList[FigCount] = pFig;
		FigList[FigCount]->SetID(FigCount);
		FigCount++;
	}
}
////////////////////////////////////////////////////////////////////////////////////
//If a figure is found return a pointer to it.
//if this point (x,y) does not belong to any figure return NULL
CFigure *ApplicationManager::GetFigure(int x, int y) const
{

	for (int i = FigCount - 1; i >= 0; i--) {
		if (FigList[i]->IsOnFig(x, y))
			return FigList[i];
	}
	return NULL;
}
////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::SetSelectedFigure(CFigure* sf) {
	SelectedFig = sf;
}
////////////////////////////////////////////////////////////////////////////////////
CFigure* ApplicationManager::GetSelectedFigure() const {
	return SelectedFig;
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	for (int i = 0; i < FigCount; i++)
	{
			FigList[i]->Draw(pOut);
	}	//Call Draw function (virtual member fn)
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }


//save function 
void ApplicationManager::SaveAll(ofstream&OutFile)
{
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->Save(OutFile);
	}
}
//clears the figlist to load from the begining
void ApplicationManager::ClearFigList()
{
	for (int i = 0; i < FigCount; i++)
	{
		delete FigList[i];
		FigList[i] = NULL;
	}
	FigCount = 0;
}

////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	ClearFigList();
	delete pIn;
	delete pOut;
}
