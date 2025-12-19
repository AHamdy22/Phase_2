#pragma once
#ifndef LOAD_H
#define LOAD_H
#include "Actions\Action.h"

//Save Action class
class Load : public Action
{
private:
	string FileName;	//The name of the file to load the flowchart
public:
	Load(ApplicationManager* pAppManager);
	//Read Save action parameters
	void ReadActionParameters();
	//Execute Save action
	void Execute();

};
#endif