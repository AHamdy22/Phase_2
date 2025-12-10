#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "GUI\UI_Info.h"
#include "GUI\output.h"
class Statement;

class Connector	//a connector that connects two statements (Source & Destination)
{
private:
	Statement *SrcStat;	//The source statement of the connector
	Statement *DstStat;	//The destination statement of the connector
	Point Start;	//Start point of the connector
	Point End;		//End point of the connector
	int OutletBranch; // 0 : Normal , 1: yes branch , 2: no branch
	bool Selected; 
public:
	Connector(Statement* Src, Statement* Dst);

	void		setSrcStat(Statement *Src);
	Statement*	getSrcStat();	
	void		setDstStat(Statement *Dst);
	Statement*	getDstStat();
	
	void setStartPoint(Point P);
	Point getStartPoint();

	void setEndPoint(Point P);
	Point getEndPoint();

	void SetSelected(bool s);

	void Draw(Output* pOut) const;

	void setOutletBranch(int branch);
	int getOutletBranch() const;
	
	void Save(ofstream& OutFile);
	void Load(ifstream& Infile, Statement** StatList, int StatCount);
};

#endif