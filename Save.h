#pragma once
#ifndef SAVE_H
#define SAVE_H
#include "Actions\Action.h"

//Save Action class
class Save : public Action
{
private:
	string FileName;	//The name of the file to save the flowchart
public:
	Save(ApplicationManager* pAppManager);
	//Read Save action parameters
	void ReadActionParameters();
	//Execute Save action
	void Execute();

};
#endif