#ifndef CUT_H
#define CUT_H

#include "Actions\Action.h"

class Cut : public Action
{

public:

	Cut(ApplicationManager* pAppManager);

	void ReadActionParameters();

	void Execute();

};

#endif