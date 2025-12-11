#ifndef EDIT_H
#define EDIT_H

#include "Actions\Action.h"

class Edit : public Action
{

public:

	Edit(ApplicationManager* pAppManager);

	void ReadActionParameters();

	void Execute();

};

#endif