#ifndef VALIDATE_H
#define VALIDATE_H

#include "Action.h"
#include "..\Statements\Statement.h"

class Validate : public Action
{
public:
	Validate(ApplicationManager* pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();

private:
	int GetStatementIndex(Statement* pStat);
};

#endif
