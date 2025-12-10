#include "Statement.h"

int Statement::NextID = 1;

Statement::Statement()	
{ 
	//TODO: set the ID with a unique value
	ID = NextID++;
	Text = "";
	Selected = false;
	pOutConn = nullptr;
	ConnCount = 0;
	for (int i = 0; i < 10; i++)
	{
		pInConnList[i] = nullptr;
	}
}

void Statement::SetSelected(bool s)
{	Selected = s; }

bool Statement::IsSelected() const
{	return Selected; }

void Statement::setOutConnector(Connector* pConn)
{
    pOutConn = pConn;
}

Connector* Statement::getOutConnector() const
{
    return pOutConn;
}

void Statement::addInConnector(Connector* pConn)
{
    // Check bounds before accessing the array
    if (pConn == nullptr || ConnCount >= 3)
    {
        return;  // Don't add null connectors
    }

    // Now it's safe to add
    pInConnList[ConnCount] = pConn;
    ConnCount++;
}

Connector* Statement::getInConnector(int index) const
{
    if (index >= 0 && index < ConnCount)
    {
        return pInConnList[index];
    }
    else return nullptr;
}

int Statement::getInConnectorCount() const
{
    return ConnCount;
}

void Statement::Move(int x, int y)
{
    LeftCorner.x += x;
    LeftCorner.y += y;
}
