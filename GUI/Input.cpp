#include <sstream>
#include "Input.h"
#include "Output.h"

Input::Input(window* pW)
{
	pWind = pW; // Point to the passed window
}

void Input::GetPointClicked(Point& P) const
{
	pWind->WaitMouseClick(P.x, P.y);	// Wait for mouse click
}

string Input::GetString(Output* pO) const
{
	string Label;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	  // ESCAPE key is pressed
			return "";	  // Returns nothing as user has cancelled label
		if (Key == 13)	  // ENTER key is pressed
			return Label;
		if ((Key == 8) && (Label.size() >= 1))	// BackSpace is pressed
			Label.resize(Label.size() - 1);
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}

double Input::GetValue(Output* pO) const
{
	// Read double value from the user

	pO->PrintMessage("Please enter a value");
	string value;
	while (1)
	{
		value = GetString(pO);
		if (IsValue(value))
			return stod(value);
		pO->PrintMessage("Please enter a valid value");
	}
}

string Input::GetVariable(Output* pO) const
{
	// To read a “variable name” from the user (from the keyboard)
	// It does not return before taking a valid variable name

	pO->PrintMessage("Please enter a variable name");
	string name;
	while (1)
	{
		name = GetString(pO);
		if (IsVariable(name))
			return name;
		pO->PrintMessage("Please enter a valid name");
	}
}

char Input::GetArithOperator(Output* pO) const
{
	// To read an arithmetic operator (+, -, * or /) from the user
	// It does not return before taking a valid arithmetic operator

	pO->PrintMessage("Please enter an arithmetic operator");
	string Operator;
	while (1)
	{
		Operator = GetString(pO);
		if (Operator.size() == 1 && (Operator[0] == '+' || Operator[0] == '-' || Operator[0] == '*' || Operator[0] == '/'))
			return Operator[0];
		pO->PrintMessage("Please enter a valid arithmetic operator");
	}
}

string Input::GetCompOperator(Output* pO) const
{
	// Similar to the previous function but for comparison operators (==, !=, <, <=, > or >=)

	pO->PrintMessage("Please enter a comparison operator");
	string Comparison;
	while (1)
	{
		Comparison = GetString(pO);
		if (Comparison == "==" || Comparison == "!=" || Comparison == "<" || Comparison == "<=" || Comparison == ">" || Comparison == ">=")
			return Comparison;
		pO->PrintMessage("Please enter a valid comparison operator");
	}
}

ActionType Input::GetUserAction() const
{	
	// This function reads the position where the user clicks to determine the desired action
	int x,y;
	pWind->WaitMouseClick(x, y);	// Get the coordinates of the user click

	if(UI.AppMode == DESIGN )	// Application is in design mode
	{
		// [1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			// Check which Menu item was clicked
			// This assumes that menu items are lined up horizontally
			int ClickedItem = (x / 65);

			// Divide x coord of the point clicked by the menu item width (int division)
			// If division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
			switch (ClickedItem)
			{
			case ITM_START:return ADD_START;
			case ITM_DECLARE:return ADD_DECLARE_VARIABLE;
			case ITM_VALUE_ASSIGN: return ADD_VALUE_ASSIGN;
			case ITM_VARIABLE_ASSIGN: return ADD_VAR_ASSIGN;
			case ITM_OPERATOR_ASSIGN: return ADD_OPER_ASSIGN;
			case ITM_COND: return ADD_CONDITION;
			case ITM_READ: return ADD_READ;
			case ITM_WRITE: return ADD_WRITE;
			case ITM_CONNECTOR: return ADD_CONNECTOR;
			case ITM_END: return ADD_END;
			case ITM_SELECT + 2:return SELECT;	// Where 2 is the gap between the first 10 icons & the following 7 icons
			case ITM_EDIT + 2:return EDIT_STAT;
			case ITM_DELETE + 2:return DEL;
			case ITM_COPY + 2:return COPY;
			case ITM_CUT + 2:return CUT;
			case ITM_PASTE + 2:return PASTE;
			case ITM_SWITCH_TO_SIM + 2:return SWITCH_SIM_MODE;
			case ITM_SAVE + 3:return SAVE;	// Where 3 is the total gap in the design tool bar
			case ITM_LOAD + 3:return LOAD;
			case ITM_EXIT1 + 3:return EXIT;
			default: return DSN_TOOL;
			}

		}
	
		// [2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			if (x <= UI.DrawingAreaWidth)
				return DRAWING_AREA;	
			else
				return OUTPUT_AREA;
		}
		
		// [3] User clicks on the status bar
		return STATUS;
	}
	else	// Application is in Simulation mode
	{
		// [1] User clicks on the tool bar
		if (y >= 0 && y < UI.ToolBarHeight)
		{

			int ClickedItem = (x / 65);

			switch (ClickedItem)
			{
			case ITM_VALIDATE:return VALIDATE;
			case ITM_RUN:return RUN;
			case ITM_SWITCH_TO_DESIGN:return SWITCH_DSN_MODE;
			case ITM_EXIT2 + 19:return EXIT; //where 19 is the gap between the switch icon and the exit icon
			default: return SIM_TOOL;
			}
		}
		// [2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			if (x <= UI.DrawingAreaWidth)
				return DRAWING_AREA;
			else
				return OUTPUT_AREA;
		}

		// [3] User clicks on the status bar
		return STATUS;
	}
}


Input::~Input()
{
}
