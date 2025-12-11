#ifndef DEL_H
#define DEL_H

#include "Actions\Action.h"

class Delete : public Action
{
private:

	Point Position;

public:
	Delete(ApplicationManager* pAppManager);

	
	void ReadActionParameters();

	
	void Execute();

};

#endif