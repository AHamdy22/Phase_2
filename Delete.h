#ifndef DELETE_H
#define DELETE_H

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