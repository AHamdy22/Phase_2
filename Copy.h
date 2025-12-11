#ifndef COPY_H
#define COPY_H

#include "Actions\Action.h"

class Copy : public Action
{

public:

	Copy(ApplicationManager* pAppManager);

	void ReadActionParameters();

	void Execute();

};

#endif