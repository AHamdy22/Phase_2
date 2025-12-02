#include "Output.h"

Output::Output()
{
	//Initialize user interface parameters
	UI.width = 1510;
	UI.height = 800;
	UI.wx = 0;
	UI.wy = 0;

	UI.AppMode = DESIGN;	//Design Mode is the default mode

	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 48;
	UI.MenuItemWidth = 60;
	UI.DrawingAreaWidth = 0.85 * UI.width;

	UI.DrawColor = BLUE;
	UI.HighlightColor = RED;
	UI.MsgColor = NAVY;

	UI.ASSGN_WDTH = 165;
	UI.ASSGN_HI = 50;
	UI.START_WDTH = 100;
	UI.START_HI = 50;
	UI.READ_WDTH = 100;
	UI.READ_HI = 50;

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Design Flow Chart");
	
	pWind->SetPen(RED,3);

	CreateDesignToolBar();
	CreateStatusBar();
	ClearDrawArea();
	ClearOutputBar();
}


Input* Output::CreateInput()
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y)
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar()
{
	pWind->DrawLine(0, UI.height-UI.StatusBarHeight, UI.width, UI.height-UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
//TODO: Complete this function
void Output::CreateDesignToolBar() //Draws the Design Menu
{
	UI.AppMode = DESIGN;	//Design Mode

	string MenuItemImages[DSN_ITM_CNT];
	MenuItemImages[ITM_START] = "images\\start.jpg";
	MenuItemImages[ITM_DECLARE] = "images\\declare.jpg";
	MenuItemImages[ITM_VALUE_ASSIGN] = "images\\valueassign.jpg";
	MenuItemImages[ITM_VARIABLE_ASSIGN] = "images\\variableassign.jpg";
	MenuItemImages[ITM_OPERATOR_ASSIGN] = "images\\operatorassign.jpg";
	MenuItemImages[ITM_COND] = "images\\condition.jpg";
	MenuItemImages[ITM_READ] = "images\\read.jpg";
	MenuItemImages[ITM_WRITE] = "images\\write.jpg";
	MenuItemImages[ITM_CONNECTOR] = "images\\connector.jpg";
	MenuItemImages[ITM_END] = "images\\end.jpg";
	MenuItemImages[ITM_SELECT] = "images\\select.jpg";
	MenuItemImages[ITM_EDIT] = "images\\edit.jpg";
	MenuItemImages[ITM_DELETE] = "images\\delete.jpg";
	MenuItemImages[ITM_COPY] = "images\\copy.jpg";
	MenuItemImages[ITM_CUT] = "images\\cut.jpg";
	MenuItemImages[ITM_PASTE] = "images\\paste.jpg";
	MenuItemImages[ITM_SWITCH_TO_SIM] = "images\\switchtosim.jpg";
	MenuItemImages[ITM_SAVE] = "images\\save.jpg";
	MenuItemImages[ITM_LOAD] = "images\\load.jpg";
	MenuItemImages[ITM_EXIT1] = "images\\exit.jpg";


	//Draw menu item one image at a time
	for (int i = ITM_START; i < ITM_SELECT; i++)
		pWind->DrawImage(MenuItemImages[i], i *65, 5, UI.MenuItemWidth, 40);
	//Draw the next 7 icons after a gap
	int j = 0;
	for (int i = ITM_SELECT; i < ITM_SAVE; i++)
	{
		pWind->DrawImage(MenuItemImages[i], 780 + 65 * j, 5, UI.MenuItemWidth, 40);
		//where 780 is 650(The first 10 icons) + 130(the gap,which is equal to the size of 2 icons) 
		j++;
	}
	int k = 0;
	for (int i = ITM_SAVE; i < DSN_ITM_CNT; i++)
	{
		pWind->DrawImage(MenuItemImages[i], 1300 + 65 * k, 5, UI.MenuItemWidth, 40);
		//where 1300 is 1235(The first 17 icons and the first gap) + 65(the second gap,which is equal to the size of 1 icon)
		k++;
	}
	//Draw a line under the toolbar
	pWind->SetPen(DODGERBLUE, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreateSimulationToolBar() //Draws the Simulation Menu
{
	UI.AppMode = SIMULATION;	//Simulation Mode
	ClearDesignToolBar();

	string SimMenuItemImages[SIM_ITM_CNT];
	SimMenuItemImages[ITM_VALIDATE] = "images\\validate.jpg";
	SimMenuItemImages[ITM_RUN] = "images\\run.jpg";
	SimMenuItemImages[ITM_SWITCH_TO_DESIGN] = "images\\switchtodesign.jpg";
	SimMenuItemImages[ITM_EXIT2] = "images\\exit.jpg";

	for (int i = 0; i < SIM_ITM_CNT - 1; i++)
		pWind->DrawImage(SimMenuItemImages[i], i * 65, 5, UI.MenuItemWidth, 40);
	//Draw Exit button at the far right
	pWind->DrawImage(SimMenuItemImages[ITM_EXIT2], 22 * 65, 5, UI.MenuItemWidth, 40);

	//Draw a line under the toolbar
	pWind->SetPen(DODGERBLUE, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(DODGERBLUE, 2);
	pWind->SetBrush(POWDERBLUE);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearDrawArea()
{
	pWind->SetPen(DODGERBLUE, 2);
	pWind->SetBrush(LIGHTCYAN);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.DrawingAreaWidth, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearOutputBar()
{
	//Create output bar by drawing a filled rectangle
	pWind->SetPen(DODGERBLUE, 2);
	pWind->SetBrush(LIGHTCYAN);
	pWind->DrawRectangle(UI.DrawingAreaWidth, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}
void Output::ClearDesignToolBar()
{
	//Clear Design tool bar by drawing a filled rectangle after switching to Simulation mode
	pWind->SetPen(WHITE, 2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}
void Output::ClearSimulationToolBar()
{
	//Clear Simulation tool bar by drawing a filled rectangle after switching to Design mode
	pWind->SetPen(WHITE, 2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::PrintMessage(string msg)	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(25, BOLD , BY_NAME, "Cascadia Code");   
	pWind->DrawString(10, UI.height - (int) (UI.StatusBarHeight/1.1), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(iX, iY, Text);
}
//////////////////////////////////////////////////////////////////////////////////////////

//======================================================================================//
//								Statements Drawing Functions								//
//======================================================================================//

//Draw assignment statement and write the "Text" on it
int stringwidth, stringheight;

void Output::DrawAssign(Point Left, int width, int height, string Text, bool Selected)
{
	if(Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor,3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor,3);	//use normal color

	//Draw the statement block rectangle
	pWind->DrawRectangle(Left.x, Left.y, Left.x + width, Left.y + height,FRAME);
		
	//Write statement text
	pWind->SetPen(BLACK, 2);

	pWind->GetStringSize(stringwidth, stringheight, Text);
	pWind->DrawString(Left.x + (width / 2) - (stringwidth / 2), Left.y + (height / 2) - (stringheight / 2), Text);
	
}

//TODO: Add similar functions for drawing all other statements.
//		e.g. DrawDeclareStat(.....), DrawCondtionalStat(......), DrawStart(......), DrawEnd(.......), ...etc
//		Decide the parameters that should be passed to each of them
	
void Output::DrawDeclare(Point Left, int width, int height, string Text, bool Selected)
{
	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3);


	pWind->DrawRectangle(Left.x, Left.y, Left.x + width, Left.y + height);


	pWind->SetPen(BLACK, 2);

	pWind->GetStringSize(stringwidth, stringheight, Text);
	pWind->DrawString(Left.x + (width / 2) - (stringwidth / 2), Left.y + (height / 2) - (stringheight / 2), Text);
}


void Output::DrawStart(Point Left, int width, int height, string Text, bool Selected)
{
	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3);


	pWind->DrawEllipse(Left.x, Left.y, Left.x + width, Left.y + height, FRAME);


	pWind->SetPen(BLACK, 2);


	pWind->GetStringSize(stringwidth, stringheight, Text);
	pWind->DrawString(Left.x + (width / 2) - (stringwidth / 2), Left.y + (height / 2) - (stringheight / 2), Text);

}


void Output::DrawEnd(Point Left, int width, int height, string Text, bool Selected)
{
	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3);


	pWind->DrawEllipse(Left.x, Left.y, Left.x + width, Left.y + height, FRAME);


	pWind->SetPen(BLACK, 2);
	pWind->GetStringSize(stringwidth, stringheight, Text);
	pWind->DrawString(Left.x + (width / 2) - (stringwidth / 2), Left.y + (height / 2) - (stringheight / 2), Text);
}

void Output::DrawRead(Point Left, int width, int height, string Text, bool Selected=false)
{
	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3);

	int X[4] = { Left.x,Left.x + width,Left.x + width - (width / 4),Left.x - (width / 4) };

	int Y[4] = { Left.y,Left.y,Left.y + height, Left.y + height };

	pWind->DrawPolygon(X, Y, 4, FRAME);

	pWind->SetPen(BLACK, 2);

	pWind->GetStringSize(stringwidth, stringheight, Text);
	pWind->DrawString(Left.x + (width / 2) - (stringwidth / 1.5), Left.y + (height / 2) - (stringheight / 2), Text);
}

void Output::DrawWrite(Point Left, int width, int height, string Text, bool Selected=false)
{
	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3);

	int X[4] = { Left.x,Left.x + width,Left.x + width - (width / 4),Left.x - (width / 4) };

	int Y[4] = { Left.y,Left.y,Left.y + height, Left.y + height };

	pWind->DrawPolygon(X, Y, 4, FRAME);

	pWind->SetPen(BLACK, 2);

	pWind->GetStringSize(stringwidth, stringheight, Text);
	pWind->DrawString(Left.x + (width / 2) - (stringwidth / 1.5), Left.y + (height / 2) - (stringheight / 2), Text);
}

void Output::DrawCondition(Point Top, int width, int height, string Text, bool Selected = false)
{
	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3);

	int X[4] = { Top.x,Top.x + (width / 2),Top.x ,Top.x - (width / 2) };

	int Y[4] = { Top.y,Top.y + (height / 2),Top.y + height, Top.y + (height / 2) };

	pWind->DrawPolygon(X, Y, 4, FRAME);

	pWind->SetPen(BLACK, 2);

	pWind->GetStringSize(stringwidth, stringheight, Text);
	pWind->DrawString(Top.x - (stringwidth / 2), Top.y + (height / 2) - (stringheight / 2), Text);

}


void Output::DrawConnector(Point start, Point end, direction d, bool Selected)
{
	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3);
	if (d == UP)
	{
		pWind->DrawLine(start.x, start.y, end.x, end.y);
		pWind->DrawTriangle(end.x, end.y, end.x + 10, end.y + 10, end.x - 10, end.y + 10, FILLED);
	}
	else if (d == DOWN)
	{
		pWind->DrawLine(start.x, start.y, end.x, end.y);
		pWind->DrawTriangle(end.x, end.y, end.x + 10, end.y - 10, end.x - 10, end.y - 10, FILLED);
	}
	else if(d==RIGHT)
	{
		pWind->DrawLine(start.x, start.y, end.x, end.y);
		pWind->DrawTriangle(end.x, end.y, end.x - 10, end.y - 10, end.x - 10, end.y + 10, FILLED);
	}
	else if (d == LEFT)
	{
		pWind->DrawLine(start.x, start.y, end.x, end.y);
		pWind->DrawTriangle(end.x, end.y, end.x + 10, end.y - 10, end.x + 10, end.y + 10, FILLED);
	}
	else if (d == NoDirection)
	{
		pWind->DrawLine(start.x, start.y, end.x, end.y);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}