#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "GUI\UI_Info.h"
#include "GUI\output.h"
class Statement;

class Connector	//a connector that connects two statements (Source & Destination)
{
private:
	Statement* SrcStat;	//The source statement of the connector
	Statement* DstStat;	//The destination statement of the connector
	mutable Point Start;	//Start point of the connector
	mutable Point End;		//End point of the connector
	// We made the 2 points mutable to be able to modify them in const functions, specifically in Draw() 
	int OutletBranch; // 0 : Normal , 1: yes branch , 2: no branch
	bool Selected; //true if the connector is selected on the flowchart
public:
	Connector(Statement* Src, Statement* Dst);

	void		setSrcStat(Statement* Src);
	Statement* getSrcStat();
	void		setDstStat(Statement* Dst);
	Statement* getDstStat();

	void setStartPoint(Point P);
	Point getStartPoint();

	void setEndPoint(Point P);
	Point getEndPoint();

	void SetSelected(bool s);

	void Draw(Output* pOut) const;

	void setOutletBranch(int branch);
	int getOutletBranch() const;

	void Save(ofstream& OutFile);

};

#endif